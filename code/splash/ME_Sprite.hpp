#ifndef MOVIE_EVENT_SPRITE_INCLUDED__


#include "SE_Sprite.hpp"
#include "MovieEvent.hpp"


class ME_Sprite : public MovieEvent
{

protected:

    SE_Sprite *affectedSprite;

//  trucs qui ressemblent à tout sauf des haïkus. série numéro -0.008421
//
//
//Macho de garde
//ni tantouze
//ni tapettes!
//
//
//
//La récursivité
//du chou-fleur
//a pas bon goût
//
//
//(ça devient vraiment n'importe quoi ces espèces de haïkus)

public:

    ME_Sprite(long int _actTime, SE_Sprite *_affectedSprite);
    ~ME_Sprite();

    virtual void Act() = 0;
	virtual MovieEvent *Copy(long int timeToAdd) = 0;

};


#define MOVIE_EVENT_SPRITE_INCLUDED__

#endif

