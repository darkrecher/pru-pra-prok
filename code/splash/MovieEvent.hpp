#ifndef MOVIE_EVENT_INCLUDED__



class MovieEvent
{

private:

protected:

    long int actTime;

//Bonjour, moi je suis un fichier de code de sexe féminin. Et mon fiancée il s'appelle :
//MovieEvent.cpp. Je l'aime beaucoup, mais des fois il a un peu la folie des grandeurs.
//Il voudrait être en mesure de définir des tas et des tas de fonctions, hyper-complexe
//et hyper bien foutu. Mais moi je préfère quand les choses restent simples, et
//le plus succint possible. Enfin de toutes façons, c'est pas moi qui décide de tout ça.
//
//Au fait, qui décide de tout ça? Qui m'a créé, qui a créé mon fiancé??

public:

    MovieEvent(long int _actTime);// { actTime = _actTime; }
    ~MovieEvent();// {};

    virtual void Act() = 0;
	virtual MovieEvent *Copy(long int timeToAdd) = 0;
    long int GetActTime();// { return actTime; }

};


#define MOVIE_EVENT_INCLUDED__


#endif
