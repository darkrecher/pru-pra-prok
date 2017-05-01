#ifndef MOVIE_EVENT_SPRITE_INCLUDED__


#include "SE_Sprite.hpp"
#include "MovieEvent.hpp"


class ME_Sprite : public MovieEvent
{

protected:

    SE_Sprite *affectedSprite;

//  trucs qui ressemblent � tout sauf des ha�kus. s�rie num�ro -0.008421
//
//
//Macho de garde
//ni tantouze
//ni tapettes!
//
//
//
//La r�cursivit�
//du chou-fleur
//a pas bon go�t
//
//
//(�a devient vraiment n'importe quoi ces esp�ces de ha�kus)

public:

    ME_Sprite(long int _actTime, SE_Sprite *_affectedSprite);
    ~ME_Sprite();

    virtual void Act() = 0;
	virtual MovieEvent *Copy(long int timeToAdd) = 0;

};


#define MOVIE_EVENT_SPRITE_INCLUDED__

#endif

