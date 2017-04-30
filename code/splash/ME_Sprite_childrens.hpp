#include "ME_Sprite.hpp"



class ME_Sprite_SetAllInfos : public ME_Sprite
{
  
private:

    long int newImg;
    SDL_Rect *newPosition;
    SDL_Rect *newPortionToDraw;
    long int newZoom;

public:

    ME_Sprite_SetAllInfos(long int _actTime, SE_Sprite *_affectedSprite, long int _newImg, 
                          SDL_Rect *_newPosition, SDL_Rect *_newPortionToDraw, 
                          long int _newZoom = 1024);
    
    ~ME_Sprite_SetAllInfos();
    void Act();
	MovieEvent *Copy(long int timeToAdd);

};


//------------------------------------------------------


class ME_Sprite_SetPos : public ME_Sprite
{
  
private:

    SDL_Rect *newPosition;

public:

    ME_Sprite_SetPos(long int _actTime, SE_Sprite *_affectedSprite, SDL_Rect *_newPosition);
    ~ME_Sprite_SetPos();
    void Act();
	MovieEvent *Copy(long int timeToAdd);

};

//-----------------------------------------


class ME_Sprite_Move : public ME_Sprite
{
  
private:

    SDL_Rect *dist;

public:

    ME_Sprite_Move(long int _actTime, SE_Sprite *_affectedSprite, SDL_Rect *_dist);
    ~ME_Sprite_Move();
    void Act();
	MovieEvent *Copy(long int timeToAdd);

};


//-----------------------------------------


class ME_Sprite_SetCurImg : public ME_Sprite
{
  
private:

    long int newImg;

public:

    ME_Sprite_SetCurImg(long int _actTime, SE_Sprite *_affectedSprite, long int _newImg);    
    ~ME_Sprite_SetCurImg();
    void Act();
	MovieEvent *Copy(long int timeToAdd);

};

//----------------------------------------------


class ME_Sprite_SetPortionToDraw : public ME_Sprite
{
  
private:

    SDL_Rect *newPortionToDraw;

public:

    ME_Sprite_SetPortionToDraw(long int _actTime, SE_Sprite *_affectedSprite, 
                               SDL_Rect *_newPortionToDraw);
                               
    ~ME_Sprite_SetPortionToDraw();
    void Act();
	MovieEvent *Copy(long int timeToAdd);

//Je ne sais pas manger correctement avec des slips. Il me faut mes doigts.

};


//-------------------------------------------------


class ME_Sprite_SetZoomSprite : public ME_Sprite
{
  
private:

    long int newZoom;

public:

    ME_Sprite_SetZoomSprite(long int _actTime, SE_Sprite *_affectedSprite, long int _newZoom);
    ~ME_Sprite_SetZoomSprite();
    void Act();
	MovieEvent *Copy(long int timeToAdd);

};
