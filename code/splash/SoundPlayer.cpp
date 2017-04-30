#include "SoundPlayer.hpp"



SoundPlayer::SoundPlayer(ConfigInfos *theConfigInfos)
{
    mixChannelQty = theConfigInfos->GetMixChannelQty();
    mixFrequency = theConfigInfos->GetMixFrequency();
    outputSoundChannelsQty = theConfigInfos->GetOutputSoundChannelsQty();
    chunkSize = theConfigInfos->GetChunkSize();

    cursor_ME = 0;
    SoundDeviceInitiated = 0;
}


SoundPlayer::~SoundPlayer()
{
    if (SoundDeviceInitiated) {
        Mix_HaltChannel(-1);
        Mix_CloseAudio();
    }
    
    delete listOfMovieEvent;
}

//je fais bien de relire mes commentaires débiles, parceque des fois je met vraiment
//des trucs bizarres. Et après je me dis qu'il vaut mieux que je les enlève.
//Hopla. Au revoir!!

int SoundPlayer::InitSoundDevice()
{
    if (Mix_OpenAudio(mixFrequency, MIX_DEFAULT_FORMAT, outputSoundChannelsQty, chunkSize)==-1)
    { 
        return 0; 
    }
    Mix_AllocateChannels(mixChannelQty);
    SoundDeviceInitiated = 1;
    SetVolumeAbsolute(100);
    mute = 0;
    return 1;
}


void SoundPlayer::SetListOfMovieEvent(MovieEvent **_listOfMovieEvent, long int _movieEventQty)
{
    listOfMovieEvent = _listOfMovieEvent;
    movieEventQty = _movieEventQty;
}


void SoundPlayer::SetDeltaTime(long int _deltaTime) { deltaTime = _deltaTime; }


void SoundPlayer::PlaceCursor_ME(long int ME_pos)
{
    if (ME_pos < movieEventQty) {
        cursor_ME = ME_pos;
    } else {
        cursor_ME = movieEventQty;
    }
}


void SoundPlayer::DoOneLoop()
{
    long int TimeOfFilm = SDL_GetTicks() - deltaTime;
    while ( (cursor_ME < movieEventQty) &&
            (listOfMovieEvent[cursor_ME] != NULL) &&
            (TimeOfFilm > listOfMovieEvent[cursor_ME]->GetActTime()) )
    {
        listOfMovieEvent[cursor_ME]->Act();
        cursor_ME++;
    }
}

void SoundPlayer::GoToBreakPoint(long int ME_pos) 
{
    Mix_HaltChannel(-1);
    PlaceCursor_ME(ME_pos);
}

void SoundPlayer::RefreshVolumeValue()
{
    if (volumePercentage > 100) { volumePercentage = 100; }
    if (volumePercentage < 0) { volumePercentage = 0; }
    Mix_Volume(-1, (int) ((volumePercentage * MIX_MAX_VOLUME) / 100));
}

int SoundPlayer::SetVolumeAbsolute(int newVolume)
{
    volumePercentage = newVolume;
    RefreshVolumeValue();
    mute = 0;
    return volumePercentage;
}


int SoundPlayer::SetVolumeRelative(int volumeToAdd)
{
    volumePercentage += volumeToAdd;
    RefreshVolumeValue();
    mute = 0;
    return volumePercentage;
}

int SoundPlayer::ToggleMute()
{
    if (mute)
    {
        RefreshVolumeValue();
        mute = 0;
        return volumePercentage;
    } else {
        Mix_Volume(-1, 0);
        mute = 1;
        return 0;
    }
}
