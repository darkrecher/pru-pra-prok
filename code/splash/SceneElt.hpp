#ifndef SCENE_ELEMENT_INCLUDED__


#include <SDL.h>


class SceneElt
{

private:

protected:

    SDL_Rect position;
    SDL_Rect occupiedSpace;

//Allez, je vais me balader un peu et je reviens.
//Iou gatte tou breule itte!!
//rifr�djour�torze!!!!
//l'I feel never people sing, l'i feel stand up!!
//Life will never be the same. Life is changing.
//On comprend vraiment rien � ces putains de chansons anglaises. Ils parlent n'importe comment.
//Fooouuuuffe on your rator!!!!  (Smooth operator)
//Je me demande si les anglais comprennent leurs propres chansons des fois.
//D'un autre c�t�, parfois, les chansons fran�aises...
//J'��� trop saign����!! sur Mel Gibson!!!!!

public:

    SceneElt();
    ~SceneElt();

    virtual void DrawOnScene(SDL_Surface *SceneSurface) = 0;
    virtual SDL_Rect *GetOccupiedSpace() = 0;

};


#define SCENE_ELEMENT_INCLUDED__


#endif
