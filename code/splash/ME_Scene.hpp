#ifndef MOVIE_EVENT_SCENE_INCLUDED__


#include "Scene.hpp"
#include "MovieEvent.hpp"


class ME_Scene : public MovieEvent
{

//Si j'ai une id�e super g�niale, je dois la mettre ici tout de suite, pour le fun?
//Ou est-ce que je dois la garder pour plus tard?
//Doit-on �conomiser ses id�es, en vue de pouvoir faire d'autres cr�ations apr�s?
//Ou doit-on au contraire mettre toutes les id�es qu'on a dans la cr�ation qu'on
//est en train de faire, afin que celle-ci soit plus intense, en se disant qu'on
//aura d'autres id�es plus tard?
//Si la quantit� d'id�es qu'on peut avoir est quasi infinie, on peut d�penser sans
//probl�mes toutes celles qu'on a maintenant. Est-ce que je suis suffisamment
//imaginatif pour me permettre �a? J'en sais rien. Pour l'instant je me suis
//gard� des id�es pour plus tard. Lalalilala


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

