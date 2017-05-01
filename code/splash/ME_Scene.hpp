#ifndef MOVIE_EVENT_SCENE_INCLUDED__


#include "Scene.hpp"
#include "MovieEvent.hpp"


class ME_Scene : public MovieEvent
{

//Si j'ai une idée super géniale, je dois la mettre ici tout de suite, pour le fun?
//Ou est-ce que je dois la garder pour plus tard?
//Doit-on économiser ses idées, en vue de pouvoir faire d'autres créations après?
//Ou doit-on au contraire mettre toutes les idées qu'on a dans la création qu'on
//est en train de faire, afin que celle-ci soit plus intense, en se disant qu'on
//aura d'autres idées plus tard?
//Si la quantité d'idées qu'on peut avoir est quasi infinie, on peut dépenser sans
//problèmes toutes celles qu'on a maintenant. Est-ce que je suis suffisamment
//imaginatif pour me permettre ça? J'en sais rien. Pour l'instant je me suis
//gardé des idées pour plus tard. Lalalilala


protected:

    Scene *affectedScene;

public:

    ME_Scene(long int _actTime, Scene *_affectedScene);
    ~ME_Scene();
    virtual void Act() = 0;
	virtual MovieEvent *Copy(long int timeToAdd) = 0;

};


#define MOVIE_EVENT_SCENE_INCLUDED__

#endif

