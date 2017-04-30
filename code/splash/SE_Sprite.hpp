#ifndef SCENE_ELEMENT_SPRITE_INCLUDED__


#include "SceneElt.hpp"
#include "ListOfImg.hpp"


class SE_Sprite : public SceneElt
{


private:

    ListOfImg *listOfImg;
    long int curImg;
    SDL_Rect *portionToDraw;
    long int zoomSprite; //virgule pas-flottante (*1024)
    

//Vous allez avoir besoin de quelques trucs pour survivre en bas,
//commencer par vous procurer un rouleau de scotch.
//Ca peut servir comme rouleau de scotch, et aussi comme papier toilette d'urgence.


public:

    SE_Sprite(ListOfImg *_listOfImg);
    ~SE_Sprite();
    
    
    void DrawOnScene(SDL_Surface *SceneSurface);
    SDL_Rect *GetOccupiedSpace();
    
    void SetAllInfos(SDL_Rect *_position, long int _curImg, SDL_Rect *_portionToDraw, 
                     long int _zoomSprite = 1024);
                     
    void SetZoomSprite(long int  _zoomSprite);
    void SetPortionToDraw(SDL_Rect *portionToDraw);
    void SetCurImg(long int _curImg);
    void SetPosition(SDL_Rect *_position);
    void Move(SDL_Rect *_dist);
    
};


#define SCENE_ELEMENT_SPRITE_INCLUDED__


#endif
