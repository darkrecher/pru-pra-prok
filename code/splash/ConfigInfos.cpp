#include "ConfigInfos.hpp"



//paye ton code-poubelle de merde!! Ouais rien à branler.
//Je referais ça mieux une autre fois.


ConfigInfos::ConfigInfos()
{
    surfaceTypeOfMainScreen = SDL_HWSURFACE;
    surfaceTypeOfBuffers = SDL_HWSURFACE;
    surfaceTypeOfImages = SDL_SWSURFACE;
    surfaceTypeOfZoomedImages = SDL_HWSURFACE;
    surfaceTypeOfScene = SDL_HWSURFACE;
    surfaceTypeOfZoomedScene = SDL_SWSURFACE;
    bufferScreenQty = 10;
    bufferScreenToLoadAtBeginning = 10;
    keyTransparencyRed = 0;
    keyTransparencyBlue = 0;
    keyTransparencyGreen = 0;
    keyTransparencyColor = 0;
    
    mixChannelQty = 3;
    mixFrequency = 22050;
    outputSoundChannelsQty = 2;
    chunkSize = 1024;
    
    showFilmXMLComments = 0;
    fullScreen = 0;
    stopIfSoundFail = 0;
    showDetails = 0;
    
    ModeEditionOfConfig = 1;
}

                
ConfigInfos::~ConfigInfos()
{
}


void ConfigInfos::StopModeEditionOfConfig()
{
    if (bufferScreenToLoadAtBeginning > bufferScreenQty) {
        bufferScreenToLoadAtBeginning = bufferScreenQty;
    }
    ModeEditionOfConfig = 0;
}


Uint32 ConfigInfos::GetSurfaceTypeOfMainScreen() { return surfaceTypeOfMainScreen; }
Uint32 ConfigInfos::GetSurfaceTypeOfBuffers() { return surfaceTypeOfBuffers; }
Uint32 ConfigInfos::GetSurfaceTypeOfImages() { return surfaceTypeOfImages; }
Uint32 ConfigInfos::GetSurfaceTypeOfZoomedImages() { return surfaceTypeOfZoomedImages; }
Uint32 ConfigInfos::GetKeyTransparencyColor() { return keyTransparencyColor; }
Uint32 ConfigInfos::GetSurfaceTypeOfScene() { return surfaceTypeOfScene; }
Uint32 ConfigInfos::GetSurfaceTypeOfZoomedScene() { return surfaceTypeOfZoomedScene; }
int ConfigInfos::GetMixChannelQty() { return mixChannelQty; }
int ConfigInfos::GetMixFrequency() { return mixFrequency; }
int ConfigInfos::GetOutputSoundChannelsQty() { return outputSoundChannelsQty; }
int ConfigInfos::GetChunkSize() { return chunkSize; }
int ConfigInfos::GetShowFilmXMLComments() { return showFilmXMLComments; }
int ConfigInfos::GetStopIfSoundFail() { return stopIfSoundFail; }
int ConfigInfos::GetFullScreen() { return fullScreen; }
int ConfigInfos::GetShowDetails() { return showDetails; }

long int ConfigInfos::GetBufferScreenQty() { return bufferScreenQty; }

long int ConfigInfos::GetBufferScreenToLoadAtBeginning()
{ return bufferScreenToLoadAtBeginning; }


void ConfigInfos::SetSurfaceTypeOfMainScreen(Uint32 _surfaceTypeOfMainScreen)
{
    if (ModeEditionOfConfig) { surfaceTypeOfMainScreen = _surfaceTypeOfMainScreen; }
}

void ConfigInfos::SetSurfaceTypeOfBuffers(Uint32 _surfaceTypeOfBuffers)
{
    if (ModeEditionOfConfig) { surfaceTypeOfBuffers = _surfaceTypeOfBuffers; }
}

void ConfigInfos::SetSurfaceTypeOfImages(Uint32 _surfaceTypeOfImages)
{
    if (ModeEditionOfConfig) { surfaceTypeOfImages = _surfaceTypeOfImages; }
}

void ConfigInfos::SetSurfaceTypeOfZoomedImages(Uint32 _surfaceTypeOfZoomedImages)
{
    if (ModeEditionOfConfig) { surfaceTypeOfZoomedImages= _surfaceTypeOfZoomedImages; }
}

void ConfigInfos::SetBufferScreenQty(long int _bufferScreenQty)
{
    if (ModeEditionOfConfig) { bufferScreenQty = _bufferScreenQty; }
}

void ConfigInfos::SetBufferScreenToLoadAtBeginning(long int _bufferScreenToLoadAtBeginning)
{
    if (ModeEditionOfConfig) { bufferScreenToLoadAtBeginning=_bufferScreenToLoadAtBeginning; }
}

void ConfigInfos::SetSurfaceTypeOfScene(Uint32 _surfaceTypeOfScene)
{
    if (ModeEditionOfConfig) { surfaceTypeOfScene = _surfaceTypeOfScene; }
}

void ConfigInfos::SetSurfaceTypeOfZoomedScene(Uint32 _surfaceTypeOfZoomedScene)
{
    if (ModeEditionOfConfig) { surfaceTypeOfZoomedScene = _surfaceTypeOfZoomedScene; }
}

void ConfigInfos::SetKeyTransparencyColorRGB(Uint8 _red, Uint8 _green, Uint8 _blue)
{
    if (ModeEditionOfConfig) {
        keyTransparencyRed = _red;
        keyTransparencyGreen = _green;
        keyTransparencyBlue = _blue;
    }
}

//Internet est ma maison de production, mon éditeur.
//Le gros désavantage, c'est qu'il ne me paie pas. Je ne peux pas gagner ma vie avec cet
//éditeur. Mais les gros avantages, c'est qu'il ne m'impose pas de délais et ne me donne pas
//de consignes pour la création de mes histoires. En plus, il diffuse ce que je fais
//de manière très large, et gratuitement. (Enfin presque gratuitement, vous devez quand
//même payer l'accès à Internet)
//Tout cela est plutôt cool non?

void ConfigInfos::SetKeyTransparencyColor32BitValue(SDL_PixelFormat *fmt)
{
    if (ModeEditionOfConfig) {
        keyTransparencyColor =
            SDL_MapRGB(fmt, keyTransparencyRed, keyTransparencyGreen, keyTransparencyBlue);
    }
}

void ConfigInfos::SetMixChannelQty(int _mixChannelQty)
{
    if (ModeEditionOfConfig) { mixChannelQty = _mixChannelQty; }
}

void ConfigInfos::SetMixFrequency(int _mixFrequency)
{
    if (ModeEditionOfConfig) { mixFrequency = _mixFrequency; }
}

void ConfigInfos::SetOutputSoundChannelsQty(int _outputSoundChannelsQty)
{
    if (ModeEditionOfConfig) { outputSoundChannelsQty = _outputSoundChannelsQty; }
}

void ConfigInfos::SetChunkSize(int _chunkSize)
{
    if (ModeEditionOfConfig) { chunkSize = _chunkSize; }
}

void ConfigInfos::SetShowFilmXMLComments(int _showFilmXMLComments)
{
    if (ModeEditionOfConfig) { showFilmXMLComments = _showFilmXMLComments; }
}

void ConfigInfos::SetStopIfSoundFail(int _stopIfSoundFail)
{
    if (ModeEditionOfConfig) { stopIfSoundFail = _stopIfSoundFail; }
}

void ConfigInfos::SetFullScreen(int _fullScreen)
{
    if (ModeEditionOfConfig) {
        if (_fullScreen) { fullScreen = SDL_FULLSCREEN; } else { fullScreen = 0; }
    }
}

void ConfigInfos::SetShowDetails(int _showDetails)
{
    if (ModeEditionOfConfig) { showDetails = _showDetails; }
}

/*   //c'était des fonctions pour tester si les valeurs étaient bien enregistrées.
string ConfigInfos::SurfaceTypeToString(Uint32 surfaceType)
{
    switch (surfaceType) {
        case SDL_HWSURFACE :
            return "Hardware";
        case SDL_SWSURFACE :
            return "Software";
        default :
            return "Unknown";
        break;
    }
}


string ConfigInfos::GetConfigDescription()
{
    cout << "mixChannelQty : " << mixChannelQty << "       mixFrequency : " << mixFrequency
    << "      outputSoundChannelsQty : " << outputSoundChannelsQty << "      chunkSize : "
    << chunkSize << endl;

    return  string(" ** configuration ** \n")
        + "Ecran principal : " + SurfaceTypeToString(surfaceTypeOfMainScreen) + "\n"
        + "Buffers : " + SurfaceTypeToString(surfaceTypeOfBuffers) + "\n"
        + "Images : " + SurfaceTypeToString(surfaceTypeOfImages) + "\n"
        + "Images zoomées : " + SurfaceTypeToString(surfaceTypeOfZoomedImages) + "\n"
        + "scene : " + SurfaceTypeToString(surfaceTypeOfScene) + "\n"
        + "scene zoomées: " + SurfaceTypeToString(surfaceTypeOfZoomedScene) + "\n"
        + "le reste j'ai pas envie de l'écrire, alors débrouillez-vous";
}*/
