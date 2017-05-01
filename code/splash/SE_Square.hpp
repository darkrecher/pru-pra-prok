#include "SceneElt.hpp"


class SE_Square : public SceneElt
{


private:

    Uint32 color;
    Uint16 width;
    Uint16 height;

//J�sus, il est n� le 25 d�cembre de l'an 0, ou bien le -6 janvier de l'an 0 ?
//En d'autres termes, quand �-t-on commenc� exactement l'an 0.

public:

    SE_Square(SDL_Rect *_position, Uint32 _color, Uint32 _width, Uint32 _height);
    ~SE_Square();

    void DrawOnScene(SDL_Surface *SceneSurface);
    SDL_Rect *GetOccupiedSpace();

};
