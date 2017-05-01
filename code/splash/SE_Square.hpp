#include "SceneElt.hpp"


class SE_Square : public SceneElt
{


private:

    Uint32 color;
    Uint16 width;
    Uint16 height;

//Jésus, il est né le 25 décembre de l'an 0, ou bien le -6 janvier de l'an 0 ?
//En d'autres termes, quand à-t-on commencé exactement l'an 0.

public:

    SE_Square(SDL_Rect *_position, Uint32 _color, Uint32 _width, Uint32 _height);
    ~SE_Square();

    void DrawOnScene(SDL_Surface *SceneSurface);
    SDL_Rect *GetOccupiedSpace();

};
