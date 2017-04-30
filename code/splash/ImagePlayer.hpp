#include "SE_Sprite.hpp"
#include "MovieEvent.hpp"
#include "ConfigInfos.hpp"
#include "BufferScreens.hpp"
#include "PercentageBar.hpp"


          
class ImagePlayer
{


private:

//donnée des images
    
//    ListOfImg **listOfListOfImg;  //si le nom ne vous plait pas, allez vous pendre.
 //   long int listOfImgQty;
    
//    SE_Sprite **listOfSprite;
//    long int spriteQty;
    
//la liste des modifications de sprites (pour construire les écrans au fur et à mesure)    
    MovieEvent **listOfMovieEvent;
//le nombre total de ces modifications, ainsi que le curseur qui pointe sur la modif courante.
    long int movieEventQty;
    long int cursor_ME;
    
//la classe contenant les écrans construits à l'avance.
    BufferScreens *bufferScreens;

    Scene *scene;
    
//pointeur vers l'écran principal
    SDL_Surface *mainScreen;
    
//classe regroupant les infos sur la configuration
    ConfigInfos *theConfigInfos;
    
//valeur de décalage (en millisecondes) pour passer du "temps de film" 
//au "temps de l'éxecution"
    long int deltaTime;
//date de l'écran en train d'être construit.
    long int timeOfWorkingScreen;
//date de l'écran qui vient d'être construit 
//(faut s'en souvenir entre un passage de boucle et le suivant
    long int timeOfBuiltScreen;
//action en cours (pareil, faut s'en souvenir entre un passage de boucle et le suivant)    
    int currentAction;
    
    static const int APPLYING_EVENT = 1;
    static const int PLACING_ELEMENT = 2;
    static const int RESETTING_SCENE = 3;
    static const int COPYING_SCENE = 4;
    static const int WAITING = 5;
    static const int TESTING_FILM_ENDED = 6;
    static const int FINISHED_IMAGE_GENERATION = 7;
    static const int FINISHED_FILM = 8;
    
    PercentageBar *percentageBar;
    
    long int totalLateTime;
    long int lateImagesQty;
    long int totalWaitingTime;
    long int dateOfPeriodOfWaiting;
//    int showDetails;

public:

//loi d'Hofstadter : il faut toujours plus de temps que prévu,
//même en tenant compte de la loi d'Hofstadter.


    ImagePlayer(SDL_Surface *_mainScreen, ConfigInfos *_theConfigInfos, 
                PercentageBar *_percentageBar);
    
    ~ImagePlayer();
    
    void SetOneMovieEvent(MovieEvent *movieEvent, long int positionInList);
    void SetListOfMovieEvent(MovieEvent **_listOfMovieEvent, long int _movieEventQty);  
    Scene *GetScene();
    void SetDeltaTime(long int _deltaTime);
    
    int GoToBreakPoint(long int cursor_ME_Index);
    
    void ShowNextScreen();
    
    void DoOneLoop();
    
    void WriteStatistics();
    
};
