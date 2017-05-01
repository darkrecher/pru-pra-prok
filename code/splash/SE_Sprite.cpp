#include "SE_Sprite.hpp"



SE_Sprite::SE_Sprite(ListOfImg *_listOfImg)
{
    listOfImg = _listOfImg;
    SetRectXY(&position, 0, 0);
    curImg = 0;
    zoomSprite = 1024;
    portionToDraw = NULL;
}


SE_Sprite::~SE_Sprite()
{
    if (portionToDraw != NULL) { delete portionToDraw; }
}


void SE_Sprite::SetAllInfos(SDL_Rect *_position, long int _curImg, SDL_Rect *_portionToDraw,
                            long int _zoomSprite/* = 1024*/)
{
    SetPosition(_position);
    curImg = _curImg;
    SetPortionToDraw(_portionToDraw);
    zoomSprite = _zoomSprite;
}


void SE_Sprite::SetZoomSprite(long int _zoomSprite) { zoomSprite = _zoomSprite; }


void SE_Sprite::SetPortionToDraw(SDL_Rect *_portionToDraw) {
    if (_portionToDraw == NULL) {
        if (portionToDraw != NULL) { delete portionToDraw; }
        portionToDraw = NULL;
    } else {
        if (portionToDraw == NULL) { portionToDraw = new SDL_Rect; }
        *portionToDraw = *_portionToDraw;
    }
}


void SE_Sprite::SetCurImg(long int _curImg) { curImg = _curImg; }


void SE_Sprite::SetPosition(SDL_Rect *_position) {
    if (_position == NULL) {
        SetRectXY(&position, 0, 0);
    }else {
        SetRectXY(&position, _position->x, _position->y);
    }
}


void SE_Sprite::Move(SDL_Rect *_dist)
{
    if (_dist != NULL) {
        SetRectXY(&position, position.x + _dist->x, position.y + _dist->y);
    }
}


void SE_Sprite::DrawOnScene(SDL_Surface *SceneSurface)
{

    ImageZoomable *imgToDraw = listOfImg->GetImageZoomable(curImg);
    if (imgToDraw == NULL) { return; }

    if (zoomSprite == 1024) {
        imgToDraw->Blit(portionToDraw, SceneSurface, &position);
    } else {
        imgToDraw->ZoomAndBlit(portionToDraw, SceneSurface, &position, zoomSprite);
    }

}


SDL_Rect *SE_Sprite::GetOccupiedSpace()
{
// ce code est pas à jour. Faudra le recontrôler si y'a besoin d'utiliser cette fonction
// (notamment l'histoire du zoomSprite qui est maintenant en virgule pas-flottante).

//Ouahou putain quand je raconte des trucs sérieusement, ça le fait de trop. Vous avez vu
//le commentaire que j'ai mis juste au-dessus? Ca me donne un air hyper intelligent,
//compétent et organisé. Eh vous croyez que je pourrais emballer des nanas en discutant
//comme ça avec elle, et tout ça.
//Euh non peut-être pas en fait. Même les moches en fait.
//Ben à vrai dire je m'en fout un peu pour l'instant donc voilà. De toutes façons après
//je deviendrais riche et célèbre, et je pourrais me taper toute les filles moches que je veux.
//
//Préparez vos vagins mesdemoiselles!!

    ImageZoomable *imgToDraw = listOfImg->GetImageZoomable(curImg);
    if (imgToDraw == NULL) { return NULL; }

    SDL_Rect portionToDraw2;
    if (portionToDraw == NULL) {
        SetRect(&portionToDraw2, 0, 0, imgToDraw->GetImage()->w, imgToDraw->GetImage()->h);
    } else {
        portionToDraw2 = *portionToDraw;
    }

    if (zoomSprite == 1) {
        SetRect(&occupiedSpace, position.x - imgToDraw->GetHotPointX() + portionToDraw2.x,
                                position.y - imgToDraw->GetHotPointY() + portionToDraw2.y,
                                portionToDraw2.w, portionToDraw2.h);
    } else {
        SetRect(&occupiedSpace,
                (Sint16) (position.x-(imgToDraw->GetHotPointX()+portionToDraw2.x)*zoomSprite),
                (Sint16) (position.y-(imgToDraw->GetHotPointY()+portionToDraw2.y)*zoomSprite),
                (Sint16) (portionToDraw2.w * zoomSprite),
                (Sint16) (portionToDraw2.h * zoomSprite));
    }

    return &occupiedSpace;

}
