#include "DataLoader.hpp"
#include "ME_BreakPoint.hpp"
#include <string>
#include <iostream.h>

#include "PercentageBar.hpp"

class MoviePlayer
{


private:

//la classe qui charge toute les donn�es au d�but. (en code-poubelle pour le moment,
//en mieux plus tard).
    DataLoader *dataLoader;

//la classe qui fait jouer le son
    SoundPlayer *soundPlayer;

//la classe qui affiche les animations � l'�cran durant le film
    ImagePlayer *imagePlayer;

//la classe permettant d'afficher une barre de pourcentage � l'�cran
//(pour le r�glage du son, ou pour avancer ou reculer dans le film
    PercentageBar *percentageBar;

//pointeur vers l'�cran principal
    SDL_Surface *mainScreen;

//classe regroupant les infos sur la configuration
    ConfigInfos *theConfigInfos;

//valeur de d�calage (en millisecondes) pour passer du "temps de film"
//au "temps de l'�xecution"
    long int deltaTime;
    long int totalTimeOfFilm;

//liste des points d'arr�t (endroit o� il faut aller dans le film quand
//l'utilisateur appuie sur la fl�che du haut, du bas, ou page up, page down
    ME_BreakPoint **listOfBreakPoint;
    long int breakPointQty;

    long int timeToStopShowPercentage;

    long int timeOfFilmBeforePause;
    long int timeToResumeFilm;
    int currentAction;

    static const int PLAYING_FILM = 0;
    static const int PAUSED = 1;
    static const int WAITING_USER_COMMAND = 2;

    long int cursorBreakPointToGo;
    int TimeOfFilmIsAfterLastBreakPoint();
    int TimeOfFilmIsBeforeFirstBreakPoint();
    void CursorBreakPointGoBack(int breakPointLevel);
    void CursorBreakPointGoAhead(int breakPointLevel);

//Et je milite pour la restauration du capital vomi. Rien � branler du pouvoir d'achat.
//C'est m�me pas un pouvoir. Je veux le pouvoir de vomi. LE POUVOIR DE VOMI!!!

public:

    MoviePlayer(SDL_Surface *_mainScreen, ConfigInfos *_theConfigInfos);
    ~MoviePlayer();

    int LoadData(char *scriptFileName);
    void Play();

};
