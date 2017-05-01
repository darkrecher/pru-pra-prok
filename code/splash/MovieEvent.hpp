#ifndef MOVIE_EVENT_INCLUDED__



class MovieEvent
{

private:

protected:

    long int actTime;

//Bonjour, moi je suis un fichier de code de sexe f�minin. Et mon fianc�e il s'appelle :
//MovieEvent.cpp. Je l'aime beaucoup, mais des fois il a un peu la folie des grandeurs.
//Il voudrait �tre en mesure de d�finir des tas et des tas de fonctions, hyper-complexe
//et hyper bien foutu. Mais moi je pr�f�re quand les choses restent simples, et
//le plus succint possible. Enfin de toutes fa�ons, c'est pas moi qui d�cide de tout �a.
//
//Au fait, qui d�cide de tout �a? Qui m'a cr��, qui a cr�� mon fianc�??

public:

    MovieEvent(long int _actTime);// { actTime = _actTime; }
    ~MovieEvent();// {};

    virtual void Act() = 0;
	virtual MovieEvent *Copy(long int timeToAdd) = 0;
    long int GetActTime();// { return actTime; }

};


#define MOVIE_EVENT_INCLUDED__


#endif
