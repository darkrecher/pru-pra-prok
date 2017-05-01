#ifndef IMAGE_ZOOMABLE_INCLUDED__

#include <SDL.h>
#include "RectOperations.hpp"


class ImageZoomable
{


private:

    SDL_Rect hotPoint;
    SDL_Surface *theImage;
    Uint32 transpColor;
    int isKeyTransparent;
    Uint32 surfaceTypeOfZoomedImage;


public:

    ImageZoomable(SDL_Surface *imageSource, SDL_Rect *sourceRect, SDL_Rect *_hotPoint,
                  Uint32 _transpColor, int _isKeyTransparent,
                  Uint32 _surfaceTypeOfImage, Uint32 _surfaceTypeOfZoomedImage);

    ImageZoomable(Uint16 imgWidth, Uint16 imgHeight,
                  Uint32 _surfaceTypeOfImage, Uint32 _surfaceTypeOfZoomedImage);

    ~ImageZoomable();

//  trucs qui ressemblent à tout sauf des haïkus. série numéro log(k.k.pi.pi)
//
//
//Dégustation de bouffe
//au supermarché :
//repas du soir chaotique
//
//
//On ne tue pas un sanglier,
//c'est le tue qui se sanglier
//
//ça veut rien dire. Mais des fois ça donne des trucs qui font cultivé et "ho ho! comment que
//je suis espiègle et malicieux avec mes petits mots d'esprits" de faire des phrases en
//inversant des mots.
//
//C'est ce que Larcenet disait dans une de ses BD, je sais plus laquelle. Mais lui, sa phrase
//qui tue, c'était : "On n'habite pas la ville, c'est la ville qui vous habite"
//Ca a plus de gueule que ma phrase à moi, mais ça veut pas dire plus grand-chose.


    Sint16 GetHotPointX();
    Sint16 GetHotPointY();
    SDL_Surface *GetImage();
    Uint32 GetTranspColor();
    int GetIsKeyTransparent();

    void SetHotPoint(SDL_Rect *_hotPoint);

    void Blit(SDL_Rect *sourceRect, SDL_Surface *dest, SDL_Rect *destRect);

    SDL_Surface *GetZoomedImage(SDL_Rect *sourceRect, long int zoomFactor,
                                SDL_Rect *imgResultLimits = NULL);

    void ZoomAndBlit(SDL_Rect *sourceRect,
                     SDL_Surface *dest, SDL_Rect *destRect,
                     long int zoomFactor, SDL_Rect *destLimits = NULL);

};

#define IMAGE_ZOOMABLE_INCLUDED__

#endif
