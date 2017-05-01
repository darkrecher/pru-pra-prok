#include "ImageZoomable.hpp"



ImageZoomable::ImageZoomable(SDL_Surface *imageSource, SDL_Rect *sourceRect,
                             SDL_Rect *_hotPoint, Uint32 _transpColor, int _isKeyTransparent,
                             Uint32 _surfaceTypeOfImage, Uint32 _surfaceTypeOfZoomedImage)
{
    theImage = NULL;
    isKeyTransparent = 0;
    surfaceTypeOfZoomedImage = _surfaceTypeOfZoomedImage;

    if (imageSource != NULL) {

        Uint16 imgWidth;
        Uint16 imgHeight;
        if (sourceRect == NULL) {
            imgWidth = imageSource->w;
            imgHeight = imageSource->h;
        } else {
            imgWidth = sourceRect->w;
            imgHeight = sourceRect->h;
        }

        theImage = SDL_CreateRGBSurface(_surfaceTypeOfImage, imgWidth, imgHeight, 32,0,0,0,0);
        SDL_BlitSurface(imageSource, sourceRect, this->GetImage(), NULL);
        this->SetHotPoint(_hotPoint);
        if (_isKeyTransparent) {
            isKeyTransparent = 1;
            transpColor = _transpColor;
            SDL_SetColorKey(theImage, SDL_SRCCOLORKEY, transpColor);
        } else {
            isKeyTransparent = 0;
        }
    }
}


ImageZoomable::ImageZoomable(Uint16 imgWidth, Uint16 imgHeight,
                             Uint32 _surfaceTypeOfImage, Uint32 _surfaceTypeOfZoomedImage)
{
    surfaceTypeOfZoomedImage = _surfaceTypeOfZoomedImage;
    theImage = SDL_CreateRGBSurface(_surfaceTypeOfImage, imgWidth,imgHeight,32,0,0,0,0);
    SetHotPoint(NULL);
    isKeyTransparent = 0;
}


ImageZoomable::~ImageZoomable()
{
    if (theImage != NULL) { SDL_FreeSurface(theImage); }
}


Sint16 ImageZoomable::GetHotPointX() { return hotPoint.x; }
Sint16 ImageZoomable::GetHotPointY() { return hotPoint.y; }
SDL_Surface *ImageZoomable::GetImage() { return theImage; }
Uint32 ImageZoomable::GetTranspColor() { return transpColor; }
int ImageZoomable::GetIsKeyTransparent() { return isKeyTransparent; }


void ImageZoomable::SetHotPoint(SDL_Rect *_hotPoint)
{
    if (_hotPoint != NULL) {
        SetRectXY(&hotPoint, _hotPoint->x, _hotPoint->y);
    } else {
        SetRectXY(&hotPoint, 0, 0);
    }
}


void ImageZoomable::Blit(SDL_Rect *sourceRect, SDL_Surface *dest, SDL_Rect *destRect)
{
    SDL_Rect destRect2;
    if (destRect == NULL) {
        SetRectXY(&destRect2, -hotPoint.x, -hotPoint.y);
    } else {
       SetRectXY(&destRect2, destRect->x-hotPoint.x, destRect->y-hotPoint.y);
    }
    SDL_BlitSurface(theImage, sourceRect, dest, &destRect2);
}


SDL_Surface *ImageZoomable::GetZoomedImage(SDL_Rect *sourceRect, long int zoomFactor,
                                           SDL_Rect *imgResultLimits = NULL)
{

    SDL_Rect sourceRect2;

    if (sourceRect == NULL) {
        SetRect(&sourceRect2, 0, 0, theImage->w, theImage->h);
    } else {
        if (sourceRect->x < 0) {
            sourceRect2.x = 0;
        } else {
            sourceRect2.x = sourceRect->x;
        }
        if (sourceRect->x+sourceRect->w > theImage->w) {
            sourceRect2.w = theImage->w - sourceRect->x;
        } else {
            sourceRect2.w = sourceRect->w;
        }
        if (sourceRect->y < 0) {
            sourceRect2.y = 0;
        } else {
            sourceRect2.y = sourceRect->y;
        }
        if (sourceRect->y+sourceRect->h > theImage->h) {
            sourceRect2.h = theImage->h - sourceRect->y;
        } else {
            sourceRect2.h = sourceRect->h;
        }
    }

    long int sourceXOffset = 0;  //valeur en virgule pas-flottante (10 bit après la virgule)
    long int sourceYOffset = 0;  //valeur en virgule pas-flottante (10 bit après la virgule)

    SDL_Rect imgResultLimits2;
    if (imgResultLimits == NULL) {
        SetRect(&imgResultLimits2, 0, 0, (Uint16) ((sourceRect2.w*zoomFactor)>>10),
                                         (Uint16) ((sourceRect2.h*zoomFactor)>>10));
    } else {
        imgResultLimits2 = *imgResultLimits;
        if (imgResultLimits2.x+imgResultLimits2.w > ((sourceRect2.w*zoomFactor)>>10)) {
            imgResultLimits2.w = (Uint16) (
                                           ((sourceRect2.w*zoomFactor) >> 10)
                                           - imgResultLimits2.x
                                          );
        }
        if (imgResultLimits2.y+imgResultLimits2.h > ((sourceRect2.h*zoomFactor)>>10)) {
            imgResultLimits2.h = (Uint16) (
                                           ((sourceRect2.h*zoomFactor) >> 10)
                                           - imgResultLimits2.y
                                          );
        }
        sourceXOffset = imgResultLimits2.x << 10;
        sourceYOffset = imgResultLimits2.y << 10;
        while ((sourceXOffset >= zoomFactor) && (sourceRect2.w > 0)) {
            sourceXOffset -= zoomFactor;
            sourceRect2.x++;
            sourceRect2.w--;
        }
        if (sourceRect2.w == 0) { return NULL; }
        while ((sourceYOffset >= zoomFactor) && (sourceRect2.h > 0)) {
            sourceYOffset -= zoomFactor;
            sourceRect2.y++;
            sourceRect2.h--;
        }
        if (sourceRect2.h == 0) { return NULL; }
    }

    SDL_Surface* zoomedImage = SDL_CreateRGBSurface(surfaceTypeOfZoomedImage,
                                                    imgResultLimits2.w, imgResultLimits2.h,
                                                    32, 0, 0, 0, 0);

    Uint16 sourcePitch = theImage->pitch;
    Uint16 destPitch = zoomedImage->pitch;
    Uint8 *sourceP;
    Uint8 *destP;
    Uint32 pixelColor;
    Sint16 sourceCursorY = sourceRect2.y;
    Uint16 destCursorX;
    Uint16 destCursorY;
    long int stepSourceX;                 //valeur en virgule pas-flottante
    long int stepSourceY = sourceYOffset; //valeur en virgule pas-flottante

    SDL_LockSurface(theImage);
    SDL_LockSurface(zoomedImage);

    for ( destCursorY=0 ; destCursorY<imgResultLimits2.h ; destCursorY++ ) {

        sourceP = (Uint8 *) theImage->pixels + sourceCursorY*sourcePitch + sourceRect2.x*4;
        destP = (Uint8 *) zoomedImage->pixels + destCursorY*destPitch;
        stepSourceX = sourceXOffset;

        for ( destCursorX=0 ; destCursorX<imgResultLimits2.w ; destCursorX++ ) {
                pixelColor = *(Uint32 *)sourceP;
                *(Uint32 *)destP = pixelColor;
                stepSourceX +=1024;
                while (stepSourceX >= zoomFactor) {
                    stepSourceX -= zoomFactor;
                    sourceP += 4;
                }
                destP += 4;
        }

        stepSourceY +=1024;
        while (stepSourceY >= zoomFactor) {
            stepSourceY -= zoomFactor;
            sourceCursorY += 1;
        }

    }

    SDL_UnlockSurface(theImage);
    SDL_UnlockSurface(zoomedImage);
    if (isKeyTransparent) { SDL_SetColorKey(zoomedImage, SDL_SRCCOLORKEY, transpColor); }

    return zoomedImage;
}


void ImageZoomable::ZoomAndBlit(SDL_Rect *sourceRect,
                                   SDL_Surface *dest, SDL_Rect *destRect,
                                   long int zoomFactor, SDL_Rect *destLimits = NULL)
{
    //zoomFactor est en virgule pas flottante, avec 10 bits après la virgule.
    //Et vous aurez pas plus que ça comme commentaire explicatif! Niaar hhaar haaar haaar!!
    //Débrouillez vous tout seul bande d'autistes de hacker!!
    //Ceci dit : Vous avez pas mieux à foutre que de regarder mon code source?
    //Vous pourriez, euh... Courir nu(e) dans la campagne et cueillir des fleufleurs, non?
    //Saucisse-moutarde powaaaaaaaa!!!

    SDL_Rect sourceRect2;
    if (sourceRect == NULL) {
        SetRect(&sourceRect2, 0, 0, theImage->w, theImage->h);
    } else {
        sourceRect2 = *sourceRect;
    }

    SDL_Rect destRect2;
    if (destRect == NULL) {
        SetRectXY(&destRect2, 0, 0);
    } else {
        SetRectXY(&destRect2, destRect->x, destRect->y);
    }

    Sint16 destLimitLeft;
    Sint16 destLimitRight;
    Sint16 destLimitUp;
    Sint16 destLimitDown;
    if (destLimits == NULL) {
        destLimitLeft = 0;
        destLimitUp = 0;
        destLimitRight = dest->w;
        destLimitDown = dest->h;
    } else {
        destLimitLeft = destLimits->x;
        destLimitUp = destLimits->y;
        destLimitRight = destLimits->x + destLimits->w;
        destLimitDown = destLimits->y + destLimits->h;
    }

    Sint16 destLeft = (Sint16) (destRect2.x - ((hotPoint.x*zoomFactor)>>10));
    Sint16 destRight = (Sint16) (destRect2.x + (((sourceRect2.w-hotPoint.x)*zoomFactor)>>10));
    Sint16 destUp = (Sint16) (destRect2.y - ((hotPoint.y*zoomFactor)>>10));
    Sint16 destDown = (Sint16) (destRect2.y + (((sourceRect2.h-hotPoint.y)*zoomFactor)>>10));

    if ((destLeft > destLimitRight) || (destRight < destLimitLeft) ||
    (destUp > destLimitDown) || (destDown < destLimitUp)) {
        return;
    }

    SDL_Rect imgResultLimits;
    SDL_Rect cornerUpLeft;

    if (destLeft < destLimitLeft) {
        imgResultLimits.x = destLimitLeft - destLeft;
        cornerUpLeft.x = destLimitLeft;
        if (destRight > destLimitRight) {
            imgResultLimits.w = destLimitRight - destLimitLeft;
        } else {
            imgResultLimits.w = destRight - destLimitLeft;
        }
    } else {
        imgResultLimits.x = 0;
        cornerUpLeft.x = destLeft;
        if (destRight > destLimitRight) {
            imgResultLimits.w = destLimitRight - destLeft;
        } else {
            imgResultLimits.w = destRight - destLeft;
        }
    }

    if (destUp < destLimitUp) {
        imgResultLimits.y = destLimitUp - destUp;
        cornerUpLeft.y = destLimitUp;
        if (destDown > destLimitDown) {
            imgResultLimits.h = destLimitDown - destLimitUp;
        } else {
            imgResultLimits.h = destDown - destLimitUp;
        }
    } else {
        imgResultLimits.y = 0;
        cornerUpLeft.y = destUp;
        if (destDown > destLimitDown) {
            imgResultLimits.h = destLimitDown - destUp;
        } else {
            imgResultLimits.h = destDown - destUp;
        }
    }

    SDL_Surface* zoomedImage = GetZoomedImage(&sourceRect2, zoomFactor, &imgResultLimits);
    SDL_BlitSurface(zoomedImage, NULL, dest, &cornerUpLeft);
    SDL_FreeSurface(zoomedImage);
};
