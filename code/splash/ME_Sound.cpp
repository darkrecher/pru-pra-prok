#include "ME_Sound.hpp"



ME_PlaySound::ME_PlaySound(long int _actTime, Mix_Chunk *_sample, 
                           int _channel, int _nbrOfTimes)
    : MovieEvent(_actTime)
{
    sample = _sample;
    channel = _channel;
    nbrOfTimes = _nbrOfTimes - 1;
}


ME_PlaySound::~ME_PlaySound() { }


void ME_PlaySound::Act()
{
    Mix_PlayChannel(channel, sample, nbrOfTimes);
}


MovieEvent *ME_PlaySound::Copy(long int timeToAdd)
{
	return (MovieEvent *) new ME_PlaySound(actTime+timeToAdd, sample, channel, nbrOfTimes+1);
}


//-------------------------------


ME_StopSound::ME_StopSound(long int _actTime, int _whichChannels)
    : MovieEvent(_actTime)
{
    whichChannels = _whichChannels;
}


ME_StopSound::~ME_StopSound() { }

//  ha�kus. s�rie num�ro 5
//
//
//une v�ritable amiti�,
//une jolie fille aux yeux noirs,
//j'esp�re la voir bient�t.
//
//
//Si ta bouteille
//est � moiti� vide,
//tu es � moiti� plein
//
//
//(le nombre de syllabe n'est pas respect�, mais je m'en branle)

void ME_StopSound::Act()
{
    Mix_HaltChannel(whichChannels);
}


MovieEvent *ME_StopSound::Copy(long int timeToAdd)
{
	return (MovieEvent *) new ME_StopSound(actTime+timeToAdd, whichChannels);
}
