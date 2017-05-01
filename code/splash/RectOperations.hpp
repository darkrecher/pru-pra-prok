#ifndef RECT_OPERATIONS_INCLUDED__

#include <SDL.h>

inline void SetRectXY(SDL_Rect *rect, Sint16 x, Sint16 y) {
    rect->x = x;
    rect->y = y;
}

//  haïkus. série numéro 1
//
//
//une musique d'attente
//d'un standard téléphonique
//n'as plus besoin d'être piraté
//
//
//si tu sais pas lire
//comment différencier ton gel douche
//et ton shampoing
//
//
//(le nombre de syllabe n'est pas respecté, mais je m'en branle)

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
