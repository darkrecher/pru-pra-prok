#include "DataLoader.hpp"



DataLoader::DataLoader(SoundPlayer *_soundPlayer, ImagePlayer *_imagePlayer,
                       SDL_Surface *_mainScreen, ConfigInfos *_theConfigInfos, Scene *_scene)
{
    imagePlayer = _imagePlayer;
    soundPlayer = _soundPlayer;
    mainScreen = _mainScreen;
    theConfigInfos = _theConfigInfos;
    scene = _scene;
    XMLparser = XMLParser(theConfigInfos->GetShowFilmXMLComments());

    chainListOf_ListOfImg = new ChainListOf_ListOfImg();
    chainListOfSprite = new ChainListOfSprite();
    chainListOfMovieEvent = new ChainListOfMovieEvent();
    chainListOfSDLSurface = new ChainListOfSDLSurface();
    chainListOfSound = new ChainListOfSound();
    chainListOfProcedure = new ChainListOfProcedure();

    percentageBar = PercentageBar(mainScreen);
    percentageTotal = -1;
    fileLoader = FileLoader(chainListOfSDLSurface, chainListOfSound,
                            &XMLparser, &percentageBar);
}


DataLoader::~DataLoader()
{
    chainListOfMovieEvent->DeleteAllEvents();
    delete chainListOfMovieEvent;
    if (chainListOfProcedure != NULL) {
        chainListOfProcedure->deleteAllProcedures();
        delete chainListOfProcedure;
    }

    chainListOfSprite->DeleteAllSprite();
    delete chainListOfSprite;

    chainListOf_ListOfImg->FreeAllImages();
    delete chainListOf_ListOfImg;

    chainListOfSound->FreeAllSound();
    delete chainListOfSound;

    if (chainListOfSDLSurface != NULL) {
        chainListOfSDLSurface->FreeAllSurfaces();
        delete chainListOfSDLSurface;
    }
}


string DataLoader::OpenFilmXMLFile(char *scriptFileName)
{
    if (!XMLparser.OpenXMLFile(scriptFileName)) {
        return XMLparser.GetErrorMessage();
    }
    return "";
}


void DataLoader::CloseFilmXMLFile()
{
    XMLparser.CloseXMLFile();
}


void DataLoader::AdvanceAndShowProgress()
{
    if (percentageTotal > 0) {
        percentageProgress++;
        percentageBar.RefreshValueAndShowOnScreen(percentageProgress, percentageTotal);
        percentageBar.FlipMainScreen();
    }
}


string DataLoader::ReadFilmXMLFile()
{
    if (!XMLparser.ReadNextNode())
        { return XMLparser.GetErrorMessageHeader() + XMLparser.GetErrorMessage(); }
    if (!XMLparser.GotAStartBaliz("SPLASH"))
        { return XMLparser.GetErrorMessageHeader() + "il faut une balise <SPLASH> au début"; }
    string result = ReadSplashBaliz();   // this is what is important
    if (result != "") { return XMLparser.GetErrorMessageHeader() + result; }
    if (!XMLparser.IsFileEntirelyParsed())
        { return XMLparser.GetErrorMessageHeader() + XMLparser.GetErrorMessage(); }

    //je vire les trucs que j'ai pas besoin. Ca libère de la mémoire avant de
    //commencer de jouer le film
    chainListOfSDLSurface->FreeAllSurfaces();
    delete chainListOfSDLSurface;
    chainListOfSDLSurface = NULL;
    chainListOfProcedure->deleteAllProcedures();
    delete chainListOfProcedure;
    chainListOfProcedure = NULL;
    return "";
}


string DataLoader::ReadSplashBaliz()
{
    string result;

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    if (XMLparser.GotAStartBaliz("ProgressBarInfo")) { result = ReadPercentageInfos(); }
    if (result != "") { return result; }

    if (percentageTotal <= 0) {
        percentageBar.RefreshValueAndShowOnScreen(0, 3);
        percentageBar.FlipMainScreen();
    }

    if (!XMLparser.GotAStartBaliz("ImgSoundFiles"))
        { return "Il faut une balise <ImgSoundFiles>, pour indiquer les fichiers à charger."; }
    result = fileLoader.LoadImgSoundFiles();
    if (result != "") { return result; }

    if (percentageTotal > 0) {
        percentageProgress = fileLoader.GetPercentageProgress();
    } else {
        percentageBar.RefreshValueAndShowOnScreen(1, 3);
        percentageBar.FlipMainScreen();
    }

    if (!XMLparser.GotAStartBaliz("LoadData"))
        { return "Il faut une balise <LoadData>, pour spécifier les images et les sons."; }
    result = ReadImgSoundDatas();
    if (result != "") { return result; }

    sceneEltsSortedList = new SceneElt *[chainListOfSprite->GetQtyOfElement()];

    if (percentageTotal <= 0) {
        percentageBar.RefreshValueAndShowOnScreen(2, 3);
        percentageBar.FlipMainScreen();
    }

    int timeToShowPercentage = 0;
    while (XMLparser.GotAStartBaliz("Procedure")) {
        result = ReadProcedure();
        if (result != "") { return result; }
        timeToShowPercentage++;
        if (timeToShowPercentage >= 10) {
            AdvanceAndShowProgress();
            timeToShowPercentage = 0;
        }
    }

    //placement du breakpoint initial. C'est obligé que y'en ai un.
    MovieEvent *newMovieEvent = (MovieEvent *) new ME_BreakPoint(0, 0, 0, 0);
    chainListOfMovieEvent->AddElement(newMovieEvent,ChainListOfMovieEvent::ME_TYPE_BREAKPOINT);

    if (percentageTotal <= 0) {
        percentageBar.RefreshValueAndShowOnScreen(3, 3);
        percentageBar.FlipMainScreen();
    }

    if (!XMLparser.GotAStartBaliz("Film"))
        { return "Ici, il faut une balise <Film>, pour décrire le déroulement du film."; }
    result = ReadMainFilm();
    if (result != "") { return result; }

    if (!XMLparser.GotAnEndBaliz("SPLASH"))
        { return "erreur pendant la lecture de la balise SPLASH"; }
    if (XMLparser.ReadNextNode()) { return "Cela devrait être la fin du fichier"; }
    return "";
}


string DataLoader::ReadPercentageInfos()
{
    string resultat;
    int stop = 0;
    percentageInfoNbrOfFileToExtract = 0;
    percentageInfoNbrOfImgListToCreate = 0;
    percentageInfoNbrOfProcedureToCreate = 0;
    Sint32 valueRead;

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    while (!stop) {
        if (XMLparser.GotAStartBaliz("FileToExtract")) {

            if (!XMLparser.ReadNumericValue("FileToExtract", &valueRead))
                { return XMLparser.GetErrorMessage(); }
            percentageInfoNbrOfFileToExtract = valueRead;

        } else if (XMLparser.GotAStartBaliz("ImgListToCreate")) {

            if (!XMLparser.ReadNumericValue("ImgListToCreate", &valueRead))
                { return XMLparser.GetErrorMessage(); }
            percentageInfoNbrOfImgListToCreate = valueRead;

        } else if (XMLparser.GotAStartBaliz("ProcedureToCreate")) {

            if (!XMLparser.ReadNumericValue("ProcedureToCreate", &valueRead))
                { return XMLparser.GetErrorMessage(); }
            percentageInfoNbrOfProcedureToCreate = valueRead;

        } else {
            stop = 1;
        }
    }

    if (!XMLparser.GotAnEndBaliz("ProgressBarInfo"))
        { return "erreur pendant la lecture de la balise ProgressBarInfo"; }

    percentageTotal = percentageInfoNbrOfFileToExtract + percentageInfoNbrOfImgListToCreate
                      + percentageInfoNbrOfProcedureToCreate/10;
    if (percentageTotal == 0) { percentageTotal = -1; }
    percentageProgress = 0;
    fileLoader.SetPercentageTotal(percentageTotal);

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    return "";
}


string DataLoader::ReadCoord(string balizName, SDL_Rect *coord, int readRectCoord/* = 0*/,
                             int mustDefineAllValues/* = 0*/)
{
    Sint32 X = 0;
    Sint32 Y = 0;
    Sint32 W = 0;
    Sint32 H = 0;
    int whatIsDefined;   // 1 : X    2 : Y    4 : W    8 : H
    int stop = 0;

    if (readRectCoord) { whatIsDefined = 0; } else { whatIsDefined = 12; }

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    while (!stop) {
        if (XMLparser.GotAStartBaliz("X")) {

            if (whatIsDefined & 1) { return "L'abscisse est déjà défini"; }
            if (!XMLparser.ReadNumericValue("X", &X))
                { return XMLparser.GetErrorMessage(); }
            whatIsDefined = whatIsDefined | 1;

        } else if (XMLparser.GotAStartBaliz("Y")) {

            if (whatIsDefined & 2) { return "L'ordonnée est déjà définie"; }
            if (!XMLparser.ReadNumericValue("Y", &Y))
                { return XMLparser.GetErrorMessage(); }
            whatIsDefined = whatIsDefined | 2;

        } else if (XMLparser.GotAStartBaliz("W")) {

            if (whatIsDefined & 4) {
                if (readRectCoord) { return "La largeur est déjà définie"; }
                return "Inutile de définir la largeur";
            }
            if (!XMLparser.ReadNumericValue("W", &W, 0, 100000, 1))
                { return XMLparser.GetErrorMessage(); }
            whatIsDefined = whatIsDefined | 4;

//C'est la fête ce code source, vous trouvez pas? Hahahahaaa! Bienvenue à n'importequoi-land
//Yeeeeeeeeeeeeeeppeeeeeeeeeeeee!!!
//HHHAAAGAAAGAAAAAAA Je programme comme un vieux porc et j'aime ça! Rien à foutre!
//Le premier qui vient me dire : "ça il aurait fallu le faire comme ça!"
//Eh bien ça va être la mort par bétonnière!!!
//
//Ouééééééééé!! Téléchargez-moi légalement!
//Et ne payez pas un rond pour ça!! (Renaud, va te faire momifier, t'es devenu trop vieux
//dans ta tête. Désolé!!)
//Et puis de toutes façons les éditeurs, majors, société de médias et etc... ne servent pas
//à grand chose quand tu es dans les débuts de ta création artistique. Parce que c'est
//super dur d'obtenir des contrats auprès d'eux quand on est pas connus. (Nan j'ai pas
//essayé et je m'en branle). C'est que après qu'ils consentent à te filer plein de fric
//pour ce que tu fais. Et quand ils sont pleins de fric, les artistes passent
//leur temps à se défoncer la gueule et ils font plus rien de leur vie.
//Si on me paye pas, j'ai plus de chances de garder cette esprit "n'importe-quoi-badaboum!!"
//que l'on a quand on est dans ses débuts.
//
//Ceci dit j'aimerais bien ne pas avoir à bosser 8h par jour à mon vrai boulot, et consacrer
//la majeure partie de mon temps à des trucs débiles comme ce dessin animé.
//Faudrait que je gagne au TacOTac. 2000 euros par mois à vie!!!
//Passez le reste de votre vie à pouvoir vous branler la nouille sans jamais tomber dans la
//perversion d'avoir un gros paquet de fric d'un coup!! Ca c'est bon!!
//Nan je leur fait pas de pub. Je dis juste que c'est une bonne idée. Je peux bien exprimer
//mon avis non?

        } else if (XMLparser.GotAStartBaliz("H")) {

            if (whatIsDefined & 8) {
                if (readRectCoord) { return "La longueur est déjà définie"; }
                return "Inutile de définir la longueur";
            }
            if (!XMLparser.ReadNumericValue("H", &H, 0, 100000, 1))
                { return XMLparser.GetErrorMessage(); }
            whatIsDefined = whatIsDefined | 8;

        } else {
            stop = 1;
        }
    }

    if (!XMLparser.GotAnEndBaliz(balizName))
        { return "erreur pendant la lecture de la balise de coordonnées " + balizName; }

    if (mustDefineAllValues && (whatIsDefined < 15))
        { return "toutes les coordonnées n'ont pas été définies"; }

    SetRect(coord, X, Y, W, H);

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    return "";
}


string DataLoader::ReadNodeOfColor(string balizName, Uint32 *transpColor)
{
    Uint8 red;
    Uint8 green;
    Uint8 blue;

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }

    if (!XMLparser.ReadNodeOfColor(balizName, &red, &green, &blue))
        { return XMLparser.GetErrorMessage(); }

    *transpColor = SDL_MapRGB(mainScreen->format, red, green, blue);
    return "";
}


string DataLoader::ReadImage(ChainListOfImg *chainListOfImgDest)
{
    SDL_Rect hotPoint;
    int hotPointDefined = 0;

    SDL_Rect *sourceRectReal = NULL;
    SDL_Rect sourceRectData;
    int sourceRectDefined = 0;

    Uint32 transpColor;
    int isKeyTransparent = -1;

    string imgName = "";
    string imgSourceName = "";
    SDL_Surface *imgSource;
    int stop = 0;
    string errorMessage;
    ImageZoomable *img;

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    while (!stop) {
        if (XMLparser.GotAStartBaliz("Name")) {

            if (imgName != "") { return "Le nom de l'image est déjà défini"; }
            if (!XMLparser.ReadTextValue("Name", &imgName))
                { return XMLparser.GetErrorMessage(); }
            if (chainListOfImgDest->GetElement(imgName) != NULL)
                { return "une autre image de la même liste a déjà le nom : " + imgName; }

        } else if (XMLparser.GotAStartBaliz("ImageSource")) {

            if (imgSourceName != "") { return "Le nom de l'image source est déjà défini"; }
            if (!XMLparser.ReadTextValue("ImageSource", &imgSourceName))
                { return XMLparser.GetErrorMessage(); }

        } else if (XMLparser.GotAStartBaliz("SquareSource")) {

            if (sourceRectDefined) { return "la portion d'image à prendre est déjà définie"; }
            errorMessage = ReadCoord("SquareSource", &sourceRectData, 1, 1);
            if (errorMessage != "") { return errorMessage; }
            sourceRectDefined = 1;
            sourceRectReal = &sourceRectData;

        } else if (XMLparser.GotASingleBaliz("SquareSourceAllImage")) {

            if (sourceRectDefined) { return "la portion d'image à prendre est déjà définie"; }
            sourceRectDefined = 1;
            if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }

        } else if (XMLparser.GotAStartBaliz("HotPoint")) {

            if (hotPointDefined) { return "le hotpoint est déjà définie"; }
            errorMessage = ReadCoord("HotPoint", &hotPoint, 0, 1);
            if (errorMessage != "") { return errorMessage; }
            hotPointDefined = 1;

        } else if (XMLparser.GotASingleBaliz("DefaultKeyTransparent")) {

            if (isKeyTransparent != -1) { return "la transparence est déjà définie"; }
            isKeyTransparent = 1;
            transpColor = theConfigInfos->GetKeyTransparencyColor();
            if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }

        } else if (XMLparser.GotASingleBaliz("NotKeyTransparent")) {

            if (isKeyTransparent != -1) { return "la transparence est déjà définie"; }
            isKeyTransparent = 0;
            transpColor = 0;
            if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }

        } else if (XMLparser.GotAStartBaliz("KeyTransparency")) {

            if (isKeyTransparent != -1) { return "la transparence est déjà définie"; }
            errorMessage = ReadNodeOfColor("KeyTransparency", &transpColor);
            if (errorMessage != "") { return errorMessage; }
            isKeyTransparent = 1;

        } else {
            stop = 1;
        }
    }

    if (!XMLparser.GotAnEndBaliz("Img"))
        { return "erreur pendant la lecture de la balise Img"; }

    if (!sourceRectDefined) { return "la portion d'image à prendre n'est pas définie"; }
    if (!hotPointDefined) { return "le hotpoint n'est pas définie"; }
    if (imgName == "") { return "Le nom de l'image n'est pas défini"; }
    if (imgSourceName == "") { return "Le nom de l'image source n'est pas défini"; }
    imgSource = chainListOfSDLSurface->GetElement(imgSourceName);
    if (imgSource == NULL) {
        return string ("Image source inconnu, ou libéré précédemment : ") + imgSourceName; }
    if (isKeyTransparent == -1) {
        isKeyTransparent = 1;
        transpColor = theConfigInfos->GetKeyTransparencyColor();
    }

    img = new ImageZoomable(imgSource, sourceRectReal, &hotPoint,
                            transpColor, isKeyTransparent,
                            theConfigInfos->GetSurfaceTypeOfImages(),
                            theConfigInfos->GetSurfaceTypeOfZoomedImages());

    chainListOfImgDest->AddElement(img, imgName);

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    return "";
}


string DataLoader::ReadMakeImgByZoom(ChainListOfImg *chainListOfImgDest)
{
    string imgName = "";
    string imgSourceName = "";
    Sint32 zoom = -1;
    int stop = 0;
    string errorMessage;
    ImageZoomable *img;
    ImageZoomable *imgSource = NULL;

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    while (!stop) {
        if (XMLparser.GotAStartBaliz("Name")) {

            if (imgName != "") { return "Le nom de l'image est déjà défini"; }
            if (!XMLparser.ReadTextValue("Name", &imgName))
                { return XMLparser.GetErrorMessage(); }
            if (chainListOfImgDest->GetElement(imgName) != NULL)
                { return "une autre image de la même liste a déjà le nom : " + imgName; }

        } else if (XMLparser.GotAStartBaliz("Original")) {

            if (imgSource != NULL) { return "Le nom de l'image original est déjà défini"; }
            if (!XMLparser.ReadTextValue("Original", &imgSourceName))
                { return XMLparser.GetErrorMessage(); }
            imgSource = chainListOfImgDest->GetElement(imgSourceName);
            if (imgSource == NULL)
                { return "La liste n'a pas d'image de nom " + imgSourceName; }

        } else if (XMLparser.GotAStartBaliz("Zoom")) {

            if (zoom != -1) { return "Le zoom est déjà défini"; }
            if (!XMLparser.ReadNumericValue("Zoom", &zoom, 0, 100000, 1))
                { return XMLparser.GetErrorMessage(); }

        } else {
            stop = 1;
        }
    }

    if (!XMLparser.GotAnEndBaliz("MakeImgByZoom"))
        { return "erreur pendant la lecture de la balise MakeImgByZoom"; }

    if (zoom == -1) { return "Il faut une balise Zoom avec une valeur numérique dedans"; }
    if (imgSource == NULL) { return "Il faut définir l'image source (balise <Original>)"; }
    if (imgName == "") { return "Le nom de l'image n'est pas défini"; }

    //tiens, ça c'est un peu fait à l'arrache comme code.
    //Boh, c'est pô grave!
    SDL_Surface *zoomedImg = imgSource->GetZoomedImage(NULL, zoom * 1024, NULL);
    SDL_SetColorKey(zoomedImg, 0, 0);
    SDL_Rect newHotPoint;
    SetRectXY(&newHotPoint, imgSource->GetHotPointX()*zoom, imgSource->GetHotPointY()*zoom);
    int CopiedIsKeyTransparent = imgSource->GetIsKeyTransparent();
    Uint32 CopiedTranspColor = imgSource->GetTranspColor();

    img = new ImageZoomable(zoomedImg, NULL, &newHotPoint,
                            CopiedTranspColor, CopiedIsKeyTransparent,
                            theConfigInfos->GetSurfaceTypeOfImages(),
                            theConfigInfos->GetSurfaceTypeOfZoomedImages());

    chainListOfImgDest->AddElement(img, imgName);
    SDL_FreeSurface(zoomedImg);

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    return "";
}


string DataLoader::ReadListOfImg()
{
    string imgListName;
    ChainListOfImg *chainListOfImg = new ChainListOfImg();
    string errorMessage;
    int stop = 0;

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    if (!XMLparser.GotAStartBaliz("Name"))
        { return "erreur dans <ImgListDef> : il faut commencer par une balise <Name>"; }
    if (!XMLparser.ReadTextValue("Name", &imgListName))
        { return XMLparser.GetErrorMessage(); }
    if (chainListOf_ListOfImg->SetCursor(imgListName) != 0)
        { return "une autre image de la même liste a déjà le nom : " + imgListName; }

    while (!stop) {
        if (XMLparser.GotAStartBaliz("Img")) {
            errorMessage = ReadImage(chainListOfImg);
            if (errorMessage != "") { return errorMessage; }
        } else if (XMLparser.GotAStartBaliz("MakeImgByZoom")) {
            errorMessage = ReadMakeImgByZoom(chainListOfImg);
            if (errorMessage != "") { return errorMessage; }
        } else {
            stop = 1;
        }
    }

    if (!XMLparser.GotAnEndBaliz("ImgListDef"))
        { return "erreur pendant la lecture de la balise LoadImgList"; }
    if (chainListOfImg->GetQtyOfElement() == 0)
        { return "il faut au moins une image dans la liste"; }

    ListOfImg *listOfImg = new ListOfImg(chainListOfImg->GetQtyOfElement());
    string *listOfImgNames = new string[chainListOfImg->GetQtyOfElement()];
    chainListOfImg->ExtractListOfImg(listOfImg, listOfImgNames);
    chainListOf_ListOfImg->AddElement(listOfImg, listOfImgNames, imgListName);

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    AdvanceAndShowProgress();
    return "";
}


string DataLoader::ReadSpriteDefinition()
{
    string listOfImgOfSpriteName;
    string spriteName;

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    if (!XMLparser.GotAStartBaliz("Name"))
        { return "erreur dans <SpriteDef> : il faut commencer par une balise <Name>"; }
    if (!XMLparser.ReadTextValue("Name", &spriteName))
        { return XMLparser.GetErrorMessage(); }
    if (chainListOfSprite->SetCursor(spriteName) != 0)
        { return "un autre sprite porte déjà le nom : " + spriteName; }

    if (!XMLparser.GotAStartBaliz("ImgList"))
        { return "erreur dans <SpriteDef> : il faut une balise <ImgList>"; }
    if (!XMLparser.ReadTextValue("ImgList", &listOfImgOfSpriteName))
        { return XMLparser.GetErrorMessage(); }
    if (chainListOf_ListOfImg->SetCursor(listOfImgOfSpriteName) == 0)
        {return "La liste d'image spécifiée est inconnue"; }

    if (!XMLparser.GotAnEndBaliz("SpriteDef"))
        { return "erreur pendant la lecture de la balise SpriteDef"; }

    long int imgQty = chainListOf_ListOfImg->GetCurrentListOfImg()->GetImgQty();
    SE_Sprite *newSprite = new SE_Sprite(chainListOf_ListOfImg->GetCurrentListOfImg());
    chainListOfSprite->AddElement(newSprite, chainListOf_ListOfImg->GetCurrentListOfImgNames(),
                                  imgQty, spriteName);

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    return "";
}


string DataLoader::ReadFreeImgFile()
{
    string imgFileName;

    if (!XMLparser.ReadTextValue("FreeImgFile", &imgFileName))
        { return XMLparser.GetErrorMessage(); }

    if (chainListOfSDLSurface->FreeElement(imgFileName) == 0)
        { return "impossible de libérer la mémoire du fichier image " + imgFileName; }

    return "";
}


string DataLoader::ReadImgSoundDatas()
{
    string result;
    int stop = 0;

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    while (!stop) {
        if (XMLparser.GotAStartBaliz("ImgListDef")) {
            result = ReadListOfImg();
            if (result != "") { return result; }
        } else if (XMLparser.GotAStartBaliz("SpriteDef")) {
            result = ReadSpriteDefinition();
            if (result != "") { return result; }
        } else if (XMLparser.GotAStartBaliz("FreeImgFile")) {
            result = ReadFreeImgFile();
            if (result != "") { return result; }
        } else {
            stop = 1;
        }
    }

    if (!XMLparser.GotAnEndBaliz("LoadData"))
        { return "erreur pendant la lecture de la balise SourceFiles"; }
    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    return "";
}


string DataLoader::FillPlanOrganization(long int time, long int *_sceneEltQty)
{
    long int sceneEltQty = 0;
    string spriteName;
    int stop = 0;
    long int spriteQty = chainListOfSprite->GetQtyOfElement();

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    while (!stop) {
        if (XMLparser.GetCurrentNodeType() != XMLParser::NODE_TYPE_TEXT)
            { return "Indiquez le nom d'un sprite, ou fermez la balise <PlanRedef>"; }
        spriteName = XMLparser.GetCurrentNodeValue();
        if (!chainListOfSprite->SetCursor(spriteName))
            { return "nom de sprite inconnu : " + spriteName; }
        sceneEltsSortedList[sceneEltQty] = (SceneElt *) chainListOfSprite->GetCurrentElement();
        sceneEltQty++;
        if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
        if (XMLparser.GotASingleBaliz("Next")) {
            if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
        } else {
            stop = 1;
        }
        if (sceneEltQty > spriteQty) { return "trop de sprite spécifiés dans <PlanRedef>"; }
    }
    if (!XMLparser.GotAnEndBaliz("PlanRedef"))
        { return "erreur pendant la lecture de la balise <PlanRedef>"; }
    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    *_sceneEltQty = sceneEltQty;
    return "";
}


string DataLoader::Read_SpriteSetAll(ChainListOfMovieEvent *listDest, long int time)
{
    string result;
    int stop = 0;
    SE_Sprite *sprite = chainListOfSprite->GetCurrentElement();
    string spriteImgName;
    long int indexOfImgToShow = -1;  //default pas accepté
    Sint32 zoom = -1;   //default accepté (1024)
    SDL_Rect pos;   //default pas accepté
    int posIsDefined = 0;
    SDL_Rect portion;
    SDL_Rect *realPortion = NULL;  //default accepté (NULL)

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    while (!stop) {
        if (XMLparser.GotAStartBaliz("Img")) {
            if (indexOfImgToShow != -1) { return "l'image du sprite est déjà définie"; }
            if (!XMLparser.ReadTextValue("Img", &spriteImgName))
                { return XMLparser.GetErrorMessage(); }
            indexOfImgToShow = chainListOfSprite->GetIndexOfImgOfCurrentElement(spriteImgName);
            if (indexOfImgToShow == -1) { return "nom d'image inconnu : " + spriteImgName; }
        } else if (XMLparser.GotAStartBaliz("Zoom")) {
            if (zoom != -1) { return "la valeur du zoom est déjà définie"; }
            if (!XMLparser.ReadNumericValue("Zoom", &zoom))
                { return XMLparser.GetErrorMessage(); }
        } else if (XMLparser.GotAStartBaliz("Pos")) {
            if (posIsDefined) { return "la position du sprite est déjà définie"; }
            result = ReadCoord("Pos", &pos, 0, 1);
            if (result != "") { return result; }
            posIsDefined = 1;
        } else if (XMLparser.GotAStartBaliz("Portion")) {
            if (realPortion != NULL) { return "la portion d'image est déjà définie"; }
            result = ReadCoord("Portion", &portion, 1, 1);
            if (result != "") { return result; }
            realPortion = &portion;
        } else {
            stop = 1;
        }
    }

    if (!XMLparser.GotAnEndBaliz("SetAllSpriteInfos"))
        { return "erreur pendant la lecture de la balise SetAllInfos"; }

    if (indexOfImgToShow == -1) { return "l'image du sprite n'est pas définie"; }
    if (zoom == -1) { zoom = 1024; }
    if (!posIsDefined) { return "la position du sprite n'est pas définie"; }

    MovieEvent *newMovieEvent = (MovieEvent *) new
                ME_Sprite_SetAllInfos(time, sprite, indexOfImgToShow, &pos, realPortion, zoom);

    listDest->AddElement(newMovieEvent, ChainListOfMovieEvent::ME_TYPE_IMAGE);

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    return "";
}


string DataLoader::Read_Sprite(ChainListOfMovieEvent *listDest, long int *time)
{
    string spriteName = "";
    string result;
    int stop = 0;
    Sint32 timeAddition;
    SDL_Rect rect;
    MovieEvent *newMovieEvent;

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    if (!XMLparser.GotAStartBaliz("Name"))
        { return "erreur dans <Sprite> : il faut commencer par une balise <Name>"; }
    if (!XMLparser.ReadTextValue("Name", &spriteName))
        { return XMLparser.GetErrorMessage(); }
    if (chainListOfSprite->SetCursor(spriteName) == 0)
        { return "sprite inexistant : " + spriteName; }
    SE_Sprite *sprite = chainListOfSprite->GetCurrentElement();

    while (!stop) {
        newMovieEvent = NULL;
        if (XMLparser.GotAStartBaliz("SetImg")) {
            string spriteImgName;
            long int indexOfImgToShow;
            if (!XMLparser.ReadTextValue("SetImg", &spriteImgName))
                { return XMLparser.GetErrorMessage(); }
            indexOfImgToShow = chainListOfSprite->GetIndexOfImgOfCurrentElement(spriteImgName);
            if (indexOfImgToShow == -1) { return "nom d'image inconnu : " + spriteImgName; }
            newMovieEvent = new ME_Sprite_SetCurImg(*time, sprite, indexOfImgToShow);
        } else if (XMLparser.GotAStartBaliz("SetZoom")) {
            Sint32 zoom;
            if (!XMLparser.ReadNumericValue("SetZoom", &zoom))
                { return XMLparser.GetErrorMessage(); }
            newMovieEvent = new ME_Sprite_SetZoomSprite(*time, sprite, zoom);
        } else if (XMLparser.GotAStartBaliz("SetPos")) {
            result = ReadCoord("SetPos", &rect, 0, 1);
            if (result != "") { return result; }
            newMovieEvent = (MovieEvent *) new ME_Sprite_SetPos(*time, sprite, &rect);
        } else if (XMLparser.GotAStartBaliz("Move")) {
            result = ReadCoord("Move", &rect, 0, 0);
            if (result != "") { return result; }
            newMovieEvent = (MovieEvent *) new ME_Sprite_Move(*time, sprite, &rect);
        } else if (XMLparser.GotAStartBaliz("SetPortion")) {
            result = ReadCoord("SetPortion", &rect, 1, 1);
            if (result != "") { return result; }
            newMovieEvent = (MovieEvent *) new ME_Sprite_SetPortionToDraw(*time,sprite,&rect);
        } else if (XMLparser.GotAStartBaliz("SetAllSpriteInfos")) {
            result = Read_SpriteSetAll(listDest, *time);
            if (result != "") { return result; }
        } else if (XMLparser.GotAStartBaliz("Time")) {
            if (!XMLparser.ReadNumericValue("Time", &timeAddition))
                { return "erreur pendant la lecture de la balise <Time>"; }
            *time += timeAddition;
        } else {
            stop = 1;
        }
        if (newMovieEvent != NULL)
            { listDest->AddElement(newMovieEvent, ChainListOfMovieEvent::ME_TYPE_IMAGE); }
    }

    if (!XMLparser.GotAnEndBaliz("Sprite"))
        { return "erreur pendant la lecture de la balise <Sprite> de " + spriteName; }
    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    return "";
}


string DataLoader::Read_SceneSetAll(ChainListOfMovieEvent *listDest, long int time)
{
    string result;
    int stop = 0;
    long int sceneEltQty = -1;
    int zoom = -1;
    Uint32 clearColor;
    int mustBeCleared = -1;
    SDL_Rect camPosAndSize;
    int camPosAndSizeDefined = 0;

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }

    while (!stop) {
        if (XMLparser.GotAStartBaliz("PlanRedef")) {

            if (sceneEltQty != -1)
                { return "l'ordre d'affichage des sprites est déjà défini"; }
            result = FillPlanOrganization(time, &sceneEltQty);
            if (result != "") { return result; }

        } else if (XMLparser.GotAStartBaliz("Zoom")) {

            if (zoom != -1) { return "la valeur du zoom est déjà définie"; }
            if (!XMLparser.ReadNumericValue("Zoom", &zoom))
                { return XMLparser.GetErrorMessage(); }

        } else if (XMLparser.GotASingleBaliz("ClearWithBlackColor")) {

            if (mustBeCleared != -1) { return "le mode de rafraichissement est déjà définie"; }
            mustBeCleared = 1;
            clearColor = SDL_MapRGB(mainScreen->format, 0, 0, 0);
            if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }

        } else if (XMLparser.GotASingleBaliz("NoClear")) {

            if (mustBeCleared != -1) { return "le mode de rafraichissement est déjà définie"; }
            mustBeCleared = 0;
            if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }

        } else if (XMLparser.GotAStartBaliz("ClearWithColor")) {

            if (mustBeCleared != -1) { return "le mode de rafraichissement est déjà définie"; }
            result = ReadNodeOfColor("ClearWithColor", &clearColor);
            if (result != "") { return result; }
            mustBeCleared = 1;

        } else if (XMLparser.GotAStartBaliz("CamPosAndSize")) {

            if (camPosAndSizeDefined) { return "infos de taille et de caméra déjà définies"; }
            result = ReadCoord("CamPosAndSize", &camPosAndSize, 1, 1);
            if (result != "") { return result; }
            camPosAndSizeDefined = 1;

        } else {
            stop = 1;
        }
    }

    if (!XMLparser.GotAnEndBaliz("SetAllSceneInfos"))
        { return "erreur pendant la lecture de la balise <SetAllSceneInfos>"; }

    if (sceneEltQty == -1) { return "ordre d'affichage des sprites non défini (PlanRedef)"; }
    if (!camPosAndSizeDefined) { return "infos de taille et de caméra non définies"; }
    if (zoom == -1) { zoom = 1024; }
    if (mustBeCleared == -1) { mustBeCleared = 0; }

    MovieEvent *newMovieEvent = (MovieEvent *) new ME_Scene_SetAllInfos(time, scene,
                                          camPosAndSize.w, camPosAndSize.h,
                                          sceneEltsSortedList, sceneEltQty,
                                          theConfigInfos->GetSurfaceTypeOfScene(),
                                          theConfigInfos->GetSurfaceTypeOfZoomedScene(),
                                          &camPosAndSize, zoom, mustBeCleared, clearColor);

    listDest->AddElement(newMovieEvent, ChainListOfMovieEvent::ME_TYPE_IMAGE);

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    return "";
}


string DataLoader::Read_Swap2Plans(ChainListOfMovieEvent *listDest, long int time)
{
    string spriteName;
    int stop = 0;
    SceneElt *firstPlan;
    SceneElt *secondPlan;

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    if (XMLparser.GetCurrentNodeType() != XMLParser::NODE_TYPE_TEXT)
        { return "Indiquez le nom d'un sprite"; }
    spriteName = XMLparser.GetCurrentNodeValue();
    if (!chainListOfSprite->SetCursor(spriteName))
        { return "nom de sprite inconnu : " + spriteName; }
    firstPlan = (SceneElt *) chainListOfSprite->GetCurrentElement();

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    if (!XMLparser.GotASingleBaliz("Next"))
        { return "Il faut une balise <Next/> après le nom du premier sprite"; }

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    if (XMLparser.GetCurrentNodeType() != XMLParser::NODE_TYPE_TEXT)
        { return "Indiquez le nom d'un sprite"; }
    spriteName = XMLparser.GetCurrentNodeValue();
    if (!chainListOfSprite->SetCursor(spriteName))
        { return "nom de sprite inconnu : " + spriteName; }
    secondPlan = (SceneElt *) chainListOfSprite->GetCurrentElement();

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    if (!XMLparser.GotAnEndBaliz("Swap2Plans"))
        { return "erreur pendant la lecture de la balise <PlanRedef>"; }

    MovieEvent *newMovieEvent = (MovieEvent *) new ME_Scene_Swap2Plans
                                                   (time, scene, firstPlan, secondPlan);

    listDest->AddElement(newMovieEvent, ChainListOfMovieEvent::ME_TYPE_IMAGE);

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    return "";
}


string DataLoader::ReadProcedureExecution(ChainListOfMovieEvent *listDest, long int *time,
                                          int complexExecution/* = 0*/)
{
    ChainListOfMovieEvent *procToConcat = NULL;
    string textRead;
    long int timeToAdd;
    Sint32 procedureDuration = -1;
    Sint32 realProcedureDuration;
    int addTimeOfProcedure = 0;
    int stop = 0;

    if (!complexExecution) {
        if (!XMLparser.ReadTextValue("Exec", &textRead))
           { return XMLparser.GetErrorMessage(); }
        procToConcat = chainListOfProcedure->GetProcedureListOfMovieEvent(textRead);
        if (procToConcat == NULL) { return "nom de procédure inconnue : " + textRead; }
        listDest->ConcatListOfMovieEvent(procToConcat, *time, -1);
    } else {

        if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
        while (!stop) {
            if (XMLparser.GotAStartBaliz("Name")) {
                if (!XMLparser.ReadTextValue("Name", &textRead))
                    { return XMLparser.GetErrorMessage(); }
                procToConcat = chainListOfProcedure->GetProcedureListOfMovieEvent(textRead);
                if (procToConcat == NULL) { return "nom de procédure inconnue : " + textRead; }
            } else if (XMLparser.GotAStartBaliz("Duration")) {
                if (!XMLparser.ReadNumericValue("Duration", &procedureDuration))
                    { return XMLparser.GetErrorMessage(); }
            } else if (XMLparser.GotASingleBaliz("AddTime")) {
                addTimeOfProcedure = 1;
                if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
            } else {
                stop = 1;
            }
        }

        if (!XMLparser.GotAnEndBaliz("ExecComplex"))
            { return "erreur pendant la lecture de la balise <ExecComplex>"; }
        if (procToConcat == NULL) { return "il faut spécifier un nom de procédure"; }
        realProcedureDuration = listDest->ConcatListOfMovieEvent(
                                            procToConcat, *time, procedureDuration);
        if (addTimeOfProcedure) { *time = *time + realProcedureDuration; }
        if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }

    }
    return "";
}


string DataLoader::ReadSequence(ChainListOfMovieEvent *listDest)
{
    MovieEvent *newMovieEvent;
    int stop = 0;
    long int time = 0;
    string result;
    Sint32 timeAddition;
    SDL_Rect pos;
    long int sceneEltQty;
    Sint32 nValueRead;
    Uint32 clearColor;
    string textRead;
    Mix_Chunk *soundToPlay;

    while (!stop) {

        if (XMLparser.GotAStartBaliz("SetCamPos")) {

            result = ReadCoord("SetCamPos", &pos, 0, 1);
            if (result != "") { return result; }
            newMovieEvent = (MovieEvent *) new ME_Scene_SetCameraPos(time, scene, &pos);
            listDest->AddElement(newMovieEvent, ChainListOfMovieEvent::ME_TYPE_IMAGE);

        } else if (XMLparser.GotAStartBaliz("Sprite")) {

            result = Read_Sprite(listDest, &time);
            if (result != "") { return result; }

        } else if (XMLparser.GotAStartBaliz("SetAllSceneInfos")) {

            result = Read_SceneSetAll(listDest, time);
            if (result != "") { return result; }

        } else if (XMLparser.GotAStartBaliz("SetZoom")) {

            if (!XMLparser.ReadNumericValue("SetZoom", &nValueRead))
                { return XMLparser.GetErrorMessage(); }
            newMovieEvent = (MovieEvent *) new ME_Scene_SetZoomScene(time, scene, nValueRead);
            listDest->AddElement(newMovieEvent, ChainListOfMovieEvent::ME_TYPE_IMAGE);

        } else if (XMLparser.GotASingleBaliz("ClearWithBlackColor")) {

            clearColor = SDL_MapRGB(mainScreen->format, 0, 0, 0);
            newMovieEvent = (MovieEvent *) new ME_Scene_SetSceneClearance
                                               (time, scene, 1, clearColor);
            listDest->AddElement(newMovieEvent, ChainListOfMovieEvent::ME_TYPE_IMAGE);
            if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }

        } else if (XMLparser.GotASingleBaliz("NoClear")) {

            newMovieEvent = (MovieEvent *) new ME_Scene_SetSceneClearance
                                               (time, scene, 0, 0);
            listDest->AddElement(newMovieEvent, ChainListOfMovieEvent::ME_TYPE_IMAGE);
            if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }

        } else if (XMLparser.GotAStartBaliz("ClearWithColor")) {

            result = ReadNodeOfColor("ClearWithColor", &clearColor);
            if (result != "") { return result; }
            newMovieEvent = (MovieEvent *) new ME_Scene_SetSceneClearance
                                               (time, scene, 1, clearColor);
            listDest->AddElement(newMovieEvent, ChainListOfMovieEvent::ME_TYPE_IMAGE);

        } else if (XMLparser.GotAStartBaliz("PlanRedef")) {

            result = FillPlanOrganization(time, &sceneEltQty);
            if (result != "") { return result; }
            newMovieEvent = (MovieEvent *) new ME_Scene_SetSceneEltToDraw
                                               (time, scene, sceneEltsSortedList, sceneEltQty);
            listDest->AddElement(newMovieEvent, ChainListOfMovieEvent::ME_TYPE_IMAGE);

        } else if (XMLparser.GotAStartBaliz("Swap2Plans")) {

            result = Read_Swap2Plans(listDest, time);
            if (result != "") { return result; }

        } else if (XMLparser.GotASingleBaliz("StopSound")) {

            newMovieEvent = new ME_StopSound(time, -1);
            listDest->AddElement(newMovieEvent, ChainListOfMovieEvent::ME_TYPE_SOUND);
            if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }

        } else if (XMLparser.GotAStartBaliz("PlaySound")) {

            if (!XMLparser.ReadTextValue("PlaySound", &textRead))
                { return XMLparser.GetErrorMessage(); }
            soundToPlay = chainListOfSound->GetElement(textRead);
            if (soundToPlay == NULL)
                { return "nom de son inconnu : " + textRead; }
            newMovieEvent = new ME_PlaySound(time, soundToPlay, -1, 1);
            listDest->AddElement(newMovieEvent, ChainListOfMovieEvent::ME_TYPE_SOUND);

        } else if (XMLparser.GotAStartBaliz("BreakPoint")) {

            if (!XMLparser.ReadNumericValue("BreakPoint", &nValueRead))
                { return XMLparser.GetErrorMessage(); }
            newMovieEvent = (MovieEvent *) new ME_BreakPoint(time, nValueRead);
            listDest->AddElement(newMovieEvent, ChainListOfMovieEvent::ME_TYPE_BREAKPOINT);

        } else if (XMLparser.GotAStartBaliz("Exec")) {

            result = ReadProcedureExecution(listDest, &time);
            if (result != "") { return result; }

        } else if (XMLparser.GotAStartBaliz("ExecComplex")) {

            result = ReadProcedureExecution(listDest, &time, 1);
            if (result != "") { return result; }

        } else if (XMLparser.GotAStartBaliz("Time")) {

            if (!XMLparser.ReadNumericValue("Time", &timeAddition))
                { return "erreur pendant la lecture de la balise <Time>"; }
                time += timeAddition;

        } else {
            stop = 1;
        }
    }

    listDest->SortList();
    return "";
}


string DataLoader::ReadMainFilm()
{
    string result;
    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    result = ReadSequence(chainListOfMovieEvent);
    if (result != "") { return result; }
    if (!XMLparser.GotAnEndBaliz("Film"))
        { return "erreur pendant la lecture de la balise Film"; }
    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    return "";
}


string DataLoader::ReadProcedure()
{
    ChainListOfMovieEvent *procedureListOfMovieEvent = new ChainListOfMovieEvent();
    string procName;
    string result;

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    if (!XMLparser.GotAStartBaliz("Name"))
        { return "erreur dans <Procedure> : il faut commencer par une balise <Name>"; }
    if (!XMLparser.ReadTextValue("Name", &procName))
        { return XMLparser.GetErrorMessage(); }
    if (chainListOfProcedure->GetProcedureListOfMovieEvent(procName) != NULL)
        { return "une autre procédure a déjà le nom : " + procName; }

    result = ReadSequence(procedureListOfMovieEvent);
    if (result != "") { return result; }
    if (!XMLparser.GotAnEndBaliz("Procedure"))
        { return "erreur pendant la lecture de la balise Procedure"; }
    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }

//    procedureListOfMovieEvent->WriteListOfTimeForTest();  //pour tester
    chainListOfProcedure->AddElement(procedureListOfMovieEvent, procName);
    return "";
}


MovieEvent **DataLoader::ExtractListOfMovieEvent(int ME_typeToGet, long int *qtyExtracted)
{
    return chainListOfMovieEvent->ExtractListOfMovieEvent(ME_typeToGet, qtyExtracted);
}


MovieEvent **DataLoader::ExtractAndDefineListOfBreakPoint(long int *qtyExtracted)
{
    return chainListOfMovieEvent->ExtractAndDefineListOfBreakPoint(qtyExtracted);
}
