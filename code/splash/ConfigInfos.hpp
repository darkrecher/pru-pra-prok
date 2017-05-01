#ifndef CONFIGURATION_INFOS_INCLUDED_PAYE_TA_CHATTE__
#define CONFIGURATION_INFOS_INCLUDED_PAYE_TA_CHATTE__


#include <SDL.h>
#include <string>

//cette classe là elle est sacrément poubelle. Faudra refaire le code à l'occasion
//parce que là c'est très très moche.
//pfou je doute que quelqu'un aura le courage de reprendre tout ça. En tout cas,
//ce sera pas moi


class ConfigInfos
{

    private:

        Uint32 surfaceTypeOfMainScreen;
        Uint32 surfaceTypeOfBuffers;
        Uint32 surfaceTypeOfImages;
        Uint32 surfaceTypeOfZoomedImages;
        Uint32 surfaceTypeOfScene;
        Uint32 surfaceTypeOfZoomedScene;

        Uint8   keyTransparencyRed;
        Uint8   keyTransparencyGreen;
        Uint8   keyTransparencyBlue;
        Uint32  keyTransparencyColor;

        long int bufferScreenQty;
        long int bufferScreenToLoadAtBeginning;

        int mixChannelQty;
        int mixFrequency;
        int outputSoundChannelsQty;
        int chunkSize;

        int showFilmXMLComments;
        int fullScreen;
        int stopIfSoundFail;
        int showDetails;

        int ModeEditionOfConfig;

    public:

        ConfigInfos();

        ~ConfigInfos();

        void StopModeEditionOfConfig();

        void SetSurfaceTypeOfZoomedImages(Uint32 _surfaceTypeOfZoomedImages);
        void SetSurfaceTypeOfImages(Uint32 _surfaceTypeOfImages);
        void SetSurfaceTypeOfBuffers(Uint32 _surfaceTypeOfBuffers);
        void SetSurfaceTypeOfMainScreen(Uint32 _surfaceTypeOfMainScreen);
        void SetSurfaceTypeOfScene(Uint32 _surfaceTypeOfScene);
        void SetSurfaceTypeOfZoomedScene(Uint32 _surfaceTypeOfZoomedScene);
        void SetBufferScreenQty(long int _bufferScreenQty);
        void SetBufferScreenToLoadAtBeginning(long int _bufferScreenToLoadAtBeginning);
        void SetKeyTransparencyColorRGB(Uint8 _red, Uint8 _green, Uint8 _blue);
        void SetKeyTransparencyColor32BitValue(SDL_PixelFormat *fmt);
        void SetChunkSize(int _chunkSize);
        void SetOutputSoundChannelsQty(int _outputSoundChannelsQty);
        void SetMixFrequency(int _mixFrequency);
        void SetMixChannelQty(int _mixChannelQty);
        void SetShowFilmXMLComments(int _showFilmXMLComments);
        void SetStopIfSoundFail(int _stopIfSoundFail);
        void SetFullScreen(int _fullScreen);
        void SetShowDetails(int _showDetails);

        Uint32 GetSurfaceTypeOfMainScreen();
        Uint32 GetSurfaceTypeOfBuffers();
        Uint32 GetSurfaceTypeOfImages();
        Uint32 GetSurfaceTypeOfZoomedImages();
        Uint32 GetSurfaceTypeOfScene();
        Uint32 GetSurfaceTypeOfZoomedScene();

        long int GetBufferScreenQty();
        long int GetBufferScreenToLoadAtBeginning();
        Uint32 GetKeyTransparencyColor();
        int GetChunkSize();
        int GetOutputSoundChannelsQty();
        int GetMixFrequency();
        int GetMixChannelQty();
        int GetShowFilmXMLComments();
        int GetStopIfSoundFail();
        int GetFullScreen();
        int GetShowDetails();

//        string GetConfigDescription();
//        string SurfaceTypeToString(Uint32 surfaceType);

};


#endif
