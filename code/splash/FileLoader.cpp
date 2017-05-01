#include "FileLoader.hpp" // class's header file



FileLoader::FileLoader()
{
	buffer = NULL;
	bufferSize = 0;
}


FileLoader::FileLoader(ChainListOfSDLSurface *_chainListOfSDLSurface,
                   ChainListOfSound *_chainListOfSound, XMLParser *_XMLparser,
                   PercentageBar *_percentageBar)
{
	buffer = NULL;
	bufferSize = 0;
    chainListOfSDLSurface = _chainListOfSDLSurface;
    chainListOfSound = _chainListOfSound;
    XMLparser = _XMLparser;
    percentageBar = _percentageBar;
    percentageProgress = 0;
    percentageTotal = -1;
}


FileLoader::~FileLoader()
{
	if (buffer != NULL) { delete buffer; }
}


long int FileLoader::GetPercentageProgress() { return percentageProgress; }

void FileLoader::SetPercentageTotal(long int _percentageTotal)
{
    percentageTotal = _percentageTotal;
}


void FileLoader::AdvanceAndShowProgress()
{
    if (percentageTotal > 0) {
        percentageProgress++;
        percentageBar->RefreshValueAndShowOnScreen(percentageProgress, percentageTotal);
        percentageBar->FlipMainScreen();
    }
}


string FileLoader::ExtractNextFileAndFillBuffer()
{
	sizeOfFileExtracted = 0;
    unsigned char oneByte;
	long int offset = 1;
	for (int i=0 ; i < sizeof(long int) ; i++) {
		if (!gzread(currentCompressedFile, &oneByte, 1))
            { return "Le fichier de donn�e " + currentCompressedFileName + " est incorrect"; }
		sizeOfFileExtracted += (int) (oneByte) * offset;
		offset *= 256;
	}

	if (sizeOfFileExtracted > bufferSize) {
		if (buffer != NULL) { delete buffer; }
		buffer = new unsigned char[sizeOfFileExtracted];
		bufferSize = sizeOfFileExtracted;
	}

	if (!gzread(currentCompressedFile, buffer, sizeOfFileExtracted))
        { return "Le fichier de donn�e " + currentCompressedFileName + " est incorrect"; }

    return "";
}

//Quand j'�tais petit, j'ai mis �norm�ment de temps � admettre qu'un gla�on pouvait fondre
//et se transformer en eau. Ca me paraissait tout simplement impossible.
//Et � chaque fois qu'on me le disait, je refusais de le croire.
//Autre chose d'amusant. A la maternelle on faisait des rondes, fallait tourner et tout.
//Ce qu'il se passait, c'est que je voyais les gens en face de moi commencer d'aller
//dans une direction. Je me disais : faut aller dans la m�me direction qu'eux,
//et l�, paf! Les deux personnes de part et d'autre de moi me tiraient
//dans la direction oppos�, et je comprenais pas du tout pourquoi.
//Plut�t rigolo non?
//J'ai froid, pourtant j'ai mis un pull et dehors il fait pas trop froid et mon radiateur
//est � "moyen".
//J'ai parfois vraiment l'impression de perdre mon temps � faire ce dessin anim�. Mais
//j'aurais encore plus l'impression de le perdre si je faisais d'autres trucs d�biles, comme
//regarder des films ou jouer � des jeux vid�os.

string FileLoader::LoadDataFromACompressedFile()
{
    string errorMessage;
    string elementName;
    int stop = 0;
    SDL_Surface *ImgLoaded;
    Mix_Chunk *SndLoaded;
    SDL_RWops *rw;

    if (!XMLparser->ReadNextNode()) { return XMLparser->GetErrorMessage(); }
    if (!XMLparser->GotAStartBaliz("Name"))
        { return "Il faut une balise Name au d�but de la balise CompressedFile"; }
    if (!XMLparser->ReadTextValue("Name", &currentCompressedFileName))
                { return XMLparser->GetErrorMessage(); }
	currentCompressedFile = gzopen(currentCompressedFileName.c_str(), "rb");
    if (currentCompressedFile == 0)
        { return "impossible d'ouvrir le fichier de donn�es " + currentCompressedFileName; }

    while (!stop) {

        if (XMLparser->GotAStartBaliz("LoadImg")) {

            if (!XMLparser->ReadTextValue("LoadImg", &elementName))
                { return XMLparser->GetErrorMessage(); }
            if (chainListOfSDLSurface->GetElement(elementName) != NULL)
                { return "Une image ayant le m�me nom existe d�j� : " + elementName; }
            errorMessage = ExtractNextFileAndFillBuffer();
            if (errorMessage != "") { return errorMessage; }
            rw = SDL_RWFromMem(buffer, sizeOfFileExtracted);
            ImgLoaded = IMG_LoadPNG_RW(rw);
            if (ImgLoaded == NULL)
                { return "impossible de charger le fichier compress� : " + elementName; }
            chainListOfSDLSurface->AddElement(ImgLoaded, elementName);
            SDL_FreeRW(rw);
            AdvanceAndShowProgress();

        } else if (XMLparser->GotAStartBaliz("LoadSnd")) {

            if (!XMLparser->ReadTextValue("LoadSnd", &elementName))
                { return XMLparser->GetErrorMessage(); }
            if (chainListOfSound->GetElement(elementName) != NULL)
                { return "Un son ayant le m�me nom existe d�j� : " + elementName; }
            errorMessage = ExtractNextFileAndFillBuffer();
            if (errorMessage != "") { return errorMessage; }
            rw = SDL_RWFromMem(buffer, sizeOfFileExtracted);
            SndLoaded = Mix_LoadWAV_RW(rw, 0);
            if (SndLoaded == NULL)
                { return "impossible de charger le fichier compress� : " + elementName; }
            chainListOfSound->AddElement(SndLoaded, elementName);
            SDL_FreeRW(rw);
            AdvanceAndShowProgress();

        } else {
            stop = 1;
        }
    }

    gzclose(currentCompressedFile);
    if (!XMLparser->GotAnEndBaliz("CompressedFile"))
        { return "erreur pendant la lecture de la balise CompressedFile"; }
    if (!XMLparser->ReadNextNode()) { return XMLparser->GetErrorMessage(); }
    return "";
}


string FileLoader::LoadImgSoundFiles()
{
    string fileName;
    string elementName;
    int stop = 0;
    SDL_Surface *ImgLoaded;
    Mix_Chunk *SndLoaded;
    string errorMessage;

    if (!XMLparser->ReadNextNode()) { return XMLparser->GetErrorMessage(); }
    while (!stop) {

        if (XMLparser->GotAStartBaliz("LoadImg")) {

            if (!XMLparser->ReadTextValue("LoadImg", &elementName))
                { return XMLparser->GetErrorMessage(); }
            if (chainListOfSDLSurface->GetElement(elementName) != NULL)
                { return "Une image ayant le m�me nom existe d�j� : " + elementName; }
            fileName = elementName + ".png";
            ImgLoaded = IMG_Load(fileName.c_str());
            if (ImgLoaded == NULL)
                { return "impossible de charger le fichier : " + fileName; }
            chainListOfSDLSurface->AddElement(ImgLoaded, elementName);
            AdvanceAndShowProgress();

        } else if (XMLparser->GotAStartBaliz("LoadSnd")) {

            if (!XMLparser->ReadTextValue("LoadSnd", &elementName))
                { return XMLparser->GetErrorMessage(); }
            if (chainListOfSound->GetElement(elementName) != NULL)
                { return "Un son ayant le m�me nom existe d�j� : " + elementName; }
            fileName = elementName + ".wav";
            SndLoaded = Mix_LoadWAV(fileName.c_str());
            if (SndLoaded == NULL)
                { return "impossible de charger le fichier : " + fileName; }
            chainListOfSound->AddElement(SndLoaded, elementName);
            AdvanceAndShowProgress();

        } else if (XMLparser->GotAStartBaliz("CompressedFile")) {

            errorMessage = LoadDataFromACompressedFile();
            if (errorMessage != "") { return errorMessage; }

        } else {
            stop = 1;
        }
    }

    if (!XMLparser->GotAnEndBaliz("ImgSoundFiles"))
        { return "erreur pendant la lecture de la balise SourceFiles"; }
    if (!XMLparser->ReadNextNode()) { return XMLparser->GetErrorMessage(); }
    return "";
}
