#ifndef RECT_OPERATIONS_INCLUDED__

#include <SDL.h>

inline void SetRectXY(SDL_Rect *rect, Sint16 x, Sint16 y) {
    rect->x = x;
    rect->y = y;
}

//  ha�kus. s�rie num�ro 1
//
//
//une musique d'attente
//d'un standard t�l�phonique
//n'as plus besoin d'�tre pirat�
//
//
//si tu sais pas lire
//comment diff�rencier ton gel douche
//et ton shampoing
//
//
//(le nombre de syllabe n'est pas respect�, mais je m'en branle)

inline void SetRectWH(SDL_Rect *rect, Uint16 width, Uint16 height) {
    rect->w = width;
    rect->h = height;
}

inline void SetRect(SDL_Rect *rect, Sint16 x, Sint16 y, Uint16 width, Uint16 height) {
    rect->x = x;
    rect->y = y;
    rect->w = width;
    rect->h = height;
}


#define RECT_OPERATIONS_INCLUDED__

#endif
