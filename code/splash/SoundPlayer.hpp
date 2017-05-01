#include <SDL.h>
#include "ConfigInfos.hpp"
#include "MovieEvent.hpp"
#include <SDL_mixer.h>



class SoundPlayer
{


private:

    int mixFrequency;
    int outputSoundChannelsQty;
    int chunkSize;
    int mixChannelQty;
    int SoundDeviceInitiated;

    MovieEvent **listOfMovieEvent;
    long int movieEventQty;
    long int cursor_ME;
    long int deltaTime;

    int volumePercentage;
    int mute;

//  haïkus. série numéro 3
//
//
//dans Hélène et les garçons
//ceux qu'on entend rire mécaniquement
//sont peut-être déjà mort
//
//
//une table coupé en deux
//ne donne pas deux tables,
//un morceau de beurre, si
//
//
//(le nombre de syllabe n'est pas respecté, mais je m'en branle)


    void RefreshVolumeValue();


public:

    SoundPlayer(ConfigInfos *theConfigInfos);

    ~SoundPlayer();

    int InitSoundDevice();
    void SetListOfMovieEvent(MovieEvent **_listOfMovieEvent, long int _movieEventQty);

    void SetDeltaTime(long int _deltaTime);
    void PlaceCursor_ME(long int ME_pos);
    void DoOneLoop();

    void GoToBreakPoint(long int ME_pos);
    int SetVolumeAbsolute(int newVolume);
    int SetVolumeRelative(int volumeToAdd);
    int ToggleMute();

};
