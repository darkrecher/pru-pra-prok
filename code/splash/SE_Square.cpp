#include "SE_Square.hpp"



SE_Square::SE_Square(SDL_Rect *_position, Uint32 _color, Uint32 _width, Uint32 _height)
{
    position.x = _position->x;
    position.y = _position->y;
    color = _color;
    width = _width;
    height = _height;
}


SE_Square::~SE_Square()
{
}

//  trucs qui ressemblent � tout sauf des ha�kus. s�rie num�ro 51,69
//
//
//Tout n'est qu'essai
//Fais-le ou fais-le
//D'autres viendront apr�s
//
//moutons de panurge :
//
//Laissez-moi crever
//avec mes potes
//si je veux
//
//
//(�a devient vraiment n'importe quoi ces esp�ces de ha�kus)

SDL_Rect *SE_Square::GetOccupiedSpace()
{
    SDL_Rect *square = new SDL_Rect();
    occupiedSpace.x = position.x;
    occupiedSpace.y = position.y;
    occupiedSpace.w = width;
    occupiedSpace.h = height;
    return &occupiedSpace;
}

    
void SE_Square::DrawOnScene(SDL_Surface *SceneSurface)
{
    SDL_Rect square;
    square.x = position.x;
    square.y = position.y;
    square.w = width;
    square.h = height;
    SDL_FillRect(SceneSurface, &square, color);
}
