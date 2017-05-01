#include "ME_Sprite_childrens.hpp"



ME_Sprite_SetAllInfos::ME_Sprite_SetAllInfos(long int _actTime, SE_Sprite *_affectedSprite,
                                             long int _newImg, SDL_Rect *_newPosition,
                                             SDL_Rect *_newPortionToDraw,
                                             long int _newZoom = 1024)
    : ME_Sprite(_actTime, _affectedSprite)
{
    newImg = _newImg;
    newZoom = _newZoom;
    if (_newPosition == NULL) {
        newPosition = NULL;
    } else {
        newPosition = new SDL_Rect;
        SetRectXY(newPosition, _newPosition->x, _newPosition->y);
    }
    if (_newPortionToDraw == NULL) {
        newPortionToDraw = NULL;
    } else {
        newPortionToDraw = new SDL_Rect;
        SetRect(newPortionToDraw, _newPortionToDraw->x, _newPortionToDraw->y,
                                   _newPortionToDraw->w, _newPortionToDraw->h);
    }
}

ME_Sprite_SetAllInfos::~ME_Sprite_SetAllInfos()
{
    if (newPortionToDraw != NULL) { delete newPortionToDraw; }
    if (newPosition != NULL) { delete newPosition; }
}

void ME_Sprite_SetAllInfos::Act()
{
    if (affectedSprite != NULL) {
        affectedSprite->SetAllInfos(newPosition, newImg, newPortionToDraw, newZoom);
    }
}

MovieEvent *ME_Sprite_SetAllInfos::Copy(long int timeToAdd)
{
	return (MovieEvent *) new ME_Sprite_SetAllInfos(
		                       actTime+timeToAdd, affectedSprite, newImg,
							   newPosition, newPortionToDraw, newZoom);
}

//--------------------------------------------------------------------------

ME_Sprite_SetPos::ME_Sprite_SetPos(long int _actTime, SE_Sprite *_affectedSprite,
                                   SDL_Rect *_newPosition)
    : ME_Sprite(_actTime, _affectedSprite)
{
    if (_newPosition == NULL) {
        newPosition = NULL;
    } else {
        newPosition = new SDL_Rect;
        SetRectXY(newPosition, _newPosition->x, _newPosition->y);
    }
}

ME_Sprite_SetPos::~ME_Sprite_SetPos()
{
    if (newPosition != NULL) { delete newPosition; }
}

void ME_Sprite_SetPos::Act()
{
    if (affectedSprite != NULL) { affectedSprite->SetPosition(newPosition); }
}

MovieEvent *ME_Sprite_SetPos::Copy(long int timeToAdd)
{
	return (MovieEvent *) new ME_Sprite_SetPos(actTime+timeToAdd, affectedSprite, newPosition);
}

//-----------------------------------------

ME_Sprite_Move::ME_Sprite_Move(long int _actTime, SE_Sprite *_affectedSprite,
                               SDL_Rect *_dist)
    : ME_Sprite(_actTime, _affectedSprite)
{
    if (_dist == NULL) {
        dist = NULL;
    } else {
        dist = new SDL_Rect;
        SetRectXY(dist, _dist->x, _dist->y);
    }
}

//Eh bien nous revoici donc avec nos probl�mes et nos plaques de plastique grise
//�a compte pas de dire des trucs qu'on a devant soi. Ca fait pas de l'�criture spontan�e.
//Ouais mais y'a que des vieux qui me viennent en t�te quand j'essaie de penser � rien,
//alors c'est pas �vident d'avoir des briques rouges ou des lemmings arm�s de
//chewing gum verts dans la t�te. la journ�e continue, mais en anglais, �a se traduit pas
//par "the journey continue" wiiizzz!! Et le grand a l'accent du midi. Ouais c'est un mec cool.
//Tu crois qu'on arrivera � quelque chose? j'esp�re bien que oui. De toutes fa�ons,
//sinon, il reste la folie. Mille fois �a plut�t que de regarder la t�l� comme
//une vieille loque. M�me si personne n'aime ce que je fais.
//L� y'a de la musique sympa qui passe dans ma cha�ne hifi st�r�o ta-chatte.
//Me rappelle mes anne�s coll�ges. C'�tait sp�cial.
//Hmmm... Les splendides fesses rebondies de Virginie. Bataille de sac de sport.
//
//Bon, eh bien c'�tait un essai d'�criture spontan�e, mais je sais pas si c'est super r�ussi.

ME_Sprite_Move::~ME_Sprite_Move()
{
    if (dist != NULL) { delete dist; }
}

void ME_Sprite_Move::Act()
{
    if (affectedSprite != NULL) { affectedSprite->Move(dist); }
}

MovieEvent *ME_Sprite_Move::Copy(long int timeToAdd)
{
	return (MovieEvent *) new ME_Sprite_Move(actTime+timeToAdd, affectedSprite, dist);
}

//-----------------------------------------

ME_Sprite_SetCurImg::ME_Sprite_SetCurImg(long int _actTime, SE_Sprite *_affectedSprite,
                                         long int _newImg)
    : ME_Sprite(_actTime, _affectedSprite)
{
    newImg = _newImg;
}

ME_Sprite_SetCurImg::~ME_Sprite_SetCurImg() { }

void ME_Sprite_SetCurImg::Act()
{
    if (affectedSprite != NULL) { affectedSprite->SetCurImg(newImg); }
}

MovieEvent *ME_Sprite_SetCurImg::Copy(long int timeToAdd)
{
	return (MovieEvent *) new ME_Sprite_SetCurImg(actTime+timeToAdd, affectedSprite, newImg);
}

//----------------------------------------------

ME_Sprite_SetPortionToDraw::ME_Sprite_SetPortionToDraw(long int _actTime,
                                                     SE_Sprite *_affectedSprite,
                                                     SDL_Rect *_newPortionToDraw)
    : ME_Sprite(_actTime, _affectedSprite)
{
    if (_newPortionToDraw == NULL) {
        newPortionToDraw = NULL;
    } else {
        newPortionToDraw = new SDL_Rect;
        SetRect(newPortionToDraw, _newPortionToDraw->x, _newPortionToDraw->y,
                                   _newPortionToDraw->w, _newPortionToDraw->h);
    }
}

ME_Sprite_SetPortionToDraw::~ME_Sprite_SetPortionToDraw()
{
    if (newPortionToDraw != NULL) { delete newPortionToDraw; }
}

void ME_Sprite_SetPortionToDraw::Act()
{
    if (affectedSprite != NULL) { affectedSprite->SetPortionToDraw(newPortionToDraw); }
}

MovieEvent *ME_Sprite_SetPortionToDraw::Copy(long int timeToAdd)
{
	return (MovieEvent *) new
        ME_Sprite_SetPortionToDraw(actTime+timeToAdd, affectedSprite, newPortionToDraw);
}

//-------------------------------------------------

ME_Sprite_SetZoomSprite::ME_Sprite_SetZoomSprite(long int _actTime,
                                                 SE_Sprite *_affectedSprite,
                                                 long int _newZoom)
    : ME_Sprite(_actTime, _affectedSprite)
{
    newZoom = _newZoom;
}

ME_Sprite_SetZoomSprite::~ME_Sprite_SetZoomSprite() { }

void ME_Sprite_SetZoomSprite::Act()
{
    if (affectedSprite != NULL) { affectedSprite->SetZoomSprite(newZoom); }
}

MovieEvent *ME_Sprite_SetZoomSprite::Copy(long int timeToAdd)
{
	return (MovieEvent *) new
        ME_Sprite_SetZoomSprite(actTime+timeToAdd, affectedSprite, newZoom);
}
