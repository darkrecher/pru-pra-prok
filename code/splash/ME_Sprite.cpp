#include "ME_Sprite.hpp"



ME_Sprite::ME_Sprite(long int _actTime, SE_Sprite *_affectedSprite)
    : MovieEvent(_actTime)
{
    affectedSprite = _affectedSprite;
};

//  haïkus. série numéro 4
//
//
//offre des jouets bruyants
//aux enfants des gens
//que tu n'aimes pas.
//
//
//un léger vent de folie
//souffle sur la Terre
//car j'ai ouvert mon crâne
//
//
//(le nombre de syllabe n'est pas respecté, mais je m'en branle)




ME_Sprite::~ME_Sprite() {};


