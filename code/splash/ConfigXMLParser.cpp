#include "ConfigXMLParser.hpp"



ConfigXMLParser::ConfigXMLParser(int _showCommentNodes = 0)
{
    XMLparser = XMLParser(_showCommentNodes);
    theConfigInfos = ConfigInfos();
}


ConfigXMLParser::~ConfigXMLParser()
{
}


string ConfigXMLParser::OpenConfigXMLFile(char *XMLFileName)
{
    if (!XMLparser.OpenXMLFile(XMLFileName)) {
        return XMLparser.GetErrorMessage();
    }
    return "";
}


void ConfigXMLParser::CloseConfigXMLFile()
{
    XMLparser.CloseXMLFile();
    theConfigInfos.StopModeEditionOfConfig();
}


string ConfigXMLParser::ReadConfigXMLFile()
{
    if (!XMLparser.ReadNextNode())
        { return XMLparser.GetErrorMessageHeader() + XMLparser.GetErrorMessage(); }
    if (!XMLparser.GotAStartBaliz("SPLASH"))
        { return XMLparser.GetErrorMessageHeader() + "il faut une balise <SPLASH> au d�but"; }
    if (!XMLparser.ReadNextNode())
        { return XMLparser.GetErrorMessageHeader() + XMLparser.GetErrorMessage(); }
    string result = ReadSplashBaliz();   // this is what is important
    if (result != "") { return XMLparser.GetErrorMessageHeader() + result; }
    return "";
}


string ConfigXMLParser::ReadSplashBaliz()
{
    //si y'a pas de config du tout, on consid�re pas �a commme une erreur.
    //On garde les valeurs par d�faut.
    if (!XMLparser.GotAStartBaliz("Config")) { return ""; }  
    string result = ReadConfigBaliz(); //here is what is important
    if (result != "") { return result; }
    if (!XMLparser.GotAnEndBaliz("SPLASH"))
        { return "erreur pendant la lecture de la balise SPLASH"; }
    if (XMLparser.ReadNextNode()) { return "Cela devrait �tre la fin du fichier"; }
    if (!XMLparser.IsFileEntirelyParsed()) { return XMLparser.GetErrorMessage(); }
    return "";
}

//notre soci�t� proc�de � des sp�cialisations de plus en plus pouss�es. Vous pouvez
//sous-traiter votre m�nage, votre cuisine (en allant au restau), l'�ducation de vos
//enfants (nourrice, psychologue pour enfants, prof � domicile...), la prise en charge de
//vos vieux (maisons de retraite). Vous pouvez aussi
//sous-traiter l'�volution de votre carri�re professionnelle, (avec les "coach"), et
//l'�volution de votre vie elle-m�me, avec les trucs de d�veloppement personnel ou
//je-ne-sais-quoi. Vous sous-traitez l'�laboration de vos loisirs, avec les
//croisi�res toute faites all-inclusive, ainsi que vos performances sexuelles, (si vous
//laissez votre partenaire prendre un amant ou une ma�tresse).
//Pour payer toutes ces sous-traitances, il faut beaucoup d'argent, heureusement, vous en
//avez � la pelle, parce que vous aussi vous �tes super sp�cialis�, vous bossez comme un
//dingue dans un boulot que peu d'autres gens savent faire.
//
//Cette sp�cialisation � outrance marche � fond pour un programme informatique, une
//cha�ne de production automatis�e, ou des trucs de ce genre. Chaque module est ind�pendant,
//et a une t�che bien pr�cise.
//Mais je ne suis pas sur que cela marche bien pour des humains. Certains trucs (pas tout
//evidemment!) il faut les faire soi-m�me.
//Commencez par arr�tez de sous-traiter votre cr�ativit�. Achetez un peu moins de livres et
//de DVD, et passer du temps � inventer des histoires par vous-m�mes. Pourquoi pas, hmmm??

string ConfigXMLParser::ReadConfigBaliz()
{
    string result;
    int stop = 0;
    Uint32 surfaceType;
    Sint32 infoRead;

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    while (!stop) {
        if (XMLparser.GotAStartBaliz("MainScreen")) {
            result = ReadNodeOfSurfaceType("MainScreen", &surfaceType);
            if (result != "") { return result; }
            theConfigInfos.SetSurfaceTypeOfMainScreen(surfaceType);
        } else if (XMLparser.GotAStartBaliz("BufferScreens")) {
            result = ReadNodeOfSurfaceType("BufferScreens", &surfaceType);
            if (result != "") { return result; }
            theConfigInfos.SetSurfaceTypeOfBuffers(surfaceType);
        } else if (XMLparser.GotAStartBaliz("Images")) {
            result = ReadNodeOfSurfaceType("Images", &surfaceType);
            if (result != "") { return result; }
            theConfigInfos.SetSurfaceTypeOfImages(surfaceType);
        } else if (XMLparser.GotAStartBaliz("ZoomedImages")) {
            result = ReadNodeOfSurfaceType("ZoomedImages", &surfaceType);
            if (result != "") { return result; }
            theConfigInfos.SetSurfaceTypeOfZoomedImages(surfaceType);
        } else if (XMLparser.GotAStartBaliz("Scene")) {
            result = ReadNodeOfSurfaceType("Scene", &surfaceType);
            if (result != "") { return result; }
            theConfigInfos.SetSurfaceTypeOfScene(surfaceType);
        } else if (XMLparser.GotAStartBaliz("ZoomedScene")) {
            result = ReadNodeOfSurfaceType("ZoomedScene", &surfaceType);
            if (result != "") { return result; }
            theConfigInfos.SetSurfaceTypeOfZoomedScene(surfaceType);
        } else if (XMLparser.GotAStartBaliz("BufferScreenQuantity")) {
            if (!XMLparser.ReadNumericValue("BufferScreenQuantity", &infoRead))
                { return XMLparser.GetErrorMessage(); }
            theConfigInfos.SetBufferScreenToLoadAtBeginning(infoRead);
            theConfigInfos.SetBufferScreenQty(infoRead);
        } else if (XMLparser.GotAStartBaliz("ChannelQuantity")) {
            if (!XMLparser.ReadNumericValue("ChannelQuantity", &infoRead))
                { return XMLparser.GetErrorMessage(); }
            theConfigInfos.SetMixChannelQty(infoRead);
        } else if (XMLparser.GotAStartBaliz("Frequency")) {
            if (!XMLparser.ReadNumericValue("Frequency", &infoRead))
                { return XMLparser.GetErrorMessage(); }
            theConfigInfos.SetMixFrequency(infoRead);
        } else if (XMLparser.GotAStartBaliz("StereoMono")) {
            if (!XMLparser.ReadNumericValue("StereoMono", &infoRead, 1, 2, 1))
                { return XMLparser.GetErrorMessage(); }
            theConfigInfos.SetOutputSoundChannelsQty(infoRead);
        } else if (XMLparser.GotAStartBaliz("SoundPartSize")) {
            if (!XMLparser.ReadNumericValue("SoundPartSize", &infoRead))
                { return XMLparser.GetErrorMessage(); }
            theConfigInfos.SetChunkSize(infoRead);
        } else if (XMLparser.GotAStartBaliz("DefaultKeyTransparency")) {
            result = ReadNodeOfTransparentColor();
            if (result != "") { return result; }
        } else if (XMLparser.GotASingleBaliz("ShowComments")) {
            theConfigInfos.SetShowFilmXMLComments(1);
            if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
        } else if (XMLparser.GotASingleBaliz("FullScreen")) {
            theConfigInfos.SetFullScreen(1);
            if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
        } else if (XMLparser.GotASingleBaliz("StopIfSoundFail")) {
            theConfigInfos.SetStopIfSoundFail(1);
            if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
        } else if (XMLparser.GotASingleBaliz("ShowDetails")) {
            theConfigInfos.SetShowDetails(1);
            if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
        } else {
            stop = 1;
        }
    }

    if (!XMLparser.GotAnEndBaliz("Config"))
        { return "erreur pendant la lecture de la balise <Config>"; }
    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    return "";
}


string ConfigXMLParser::ReadNodeOfSurfaceType(string balizName, Uint32 *surfaceType)
{
    string infos;
    if (!XMLparser.ReadTextValue(balizName, &infos)) { return XMLparser.GetErrorMessage(); }
    if (infos == "HARDWARE") {
        *surfaceType = SDL_HWSURFACE;
    } else if (infos == "SOFTWARE") {
        *surfaceType = SDL_SWSURFACE;
    } else {
        return "Dans ce type de balise, il faut �crire HARDWARE ou SOFTWARE";
    }
    return "";
}


string ConfigXMLParser::ReadNodeOfTransparentColor()
{
    Uint8 red;
    Uint8 green;
    Uint8 blue;

    if (!XMLparser.ReadNextNode()) { return XMLparser.GetErrorMessage(); }
    
    if (!XMLparser.ReadNodeOfColor("DefaultKeyTransparency", &red, &green, &blue))
        { return XMLparser.GetErrorMessage(); }
    
    theConfigInfos.SetKeyTransparencyColorRGB(red, green, blue);
    return "";
}


ConfigInfos *ConfigXMLParser::GetConfigInfos()
{
    return &theConfigInfos;
}
