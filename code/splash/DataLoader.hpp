//oulà! ça en fait du bordel!! Faut croire que y'a vraiment besoin de tout ça, ouais.


#include "SE_Square.hpp"
#include "ME_Sprite_childrens.hpp"
#include "ME_Scene_childrens.hpp"
#include "ImagePlayer.hpp"
#include "ME_Sound.hpp"
#include "SoundPlayer.hpp"

#include "ChainListOfImg.hpp"
#include "ChainListOf_ListOfImg.hpp"
#include "ChainListOfSprite.hpp"
#include "ChainListOfMovieEvent.hpp"
#include "FileLoader.hpp"
#include "ChainListOfProcedure.hpp"
#include "ME_BreakPoint.hpp"
#include "PercentageBar.hpp"


#include <iostream.h>


//c'est l'histoire de deux cailloux qui se parlent
// caillou 1 : Hey, je voulais te dire : 110110111000110101
// caillou 2 : Ah c'est intéressant. J'en prend note. En ce qui me concerne : 0110110101100
// caillou 1 : Oh c'est chouette ça! D'aileurs, figure toi que 00100110111010111 !!
//
// Mais qu'est-ce donc? Eh bien c'est du P2P!! (pierre-to-pierre)
// Il s'agit d'une activité fortement pratiqué aux temps préhistorique,
// puisqu'à l'époque, tout le monde s'appelait Pierre. (cf RRRRrrrrrrrhhhh!!!! Le film des
// autres andouilles).



class DataLoader
{


    private:

    //pointeur vers la classe qui affichera les images du films.
        ImagePlayer *imagePlayer;

    //pointeur vers la classe qui joue les sons
        SoundPlayer *soundPlayer;

    //pointeur vers l'écran principal.
        SDL_Surface *mainScreen;

    //pointeur vers les infos de config.
        ConfigInfos *theConfigInfos;

    //liste chainée des fichiers images dans lesquels récupérer les données
        ChainListOfSDLSurface *chainListOfSDLSurface;

    //liste des sons
        ChainListOfSound *chainListOfSound;

    //pointeur vers la scène de la classe ImagePlayer (certains événements de film agissent
    //sur l'objet "Scene", donc il faut leur passer en paramètre.
        Scene *scene;

    //la liste des ImgList. Liste chaînée, pour pouvoir créer les listes d'images au fur
    //et à mesure qu'on les lit dans le fichier XML (enfin, quand y'aura le fichier XML)
        ChainListOf_ListOfImg *chainListOf_ListOfImg;

    //la liste des sprites. Liste chaînée, pareil. Pour pouvoir les créer au fur et à mesure.
        ChainListOfSprite *chainListOfSprite;

    //liste des événements du films.
        ChainListOfMovieEvent *chainListOfMovieEvent;
        
        
    //liste de procédure = liste de liste de MovieEvent, si ça vous plait pas aller vous pendre
        ChainListOfProcedure *chainListOfProcedure;

    // une classe qui lit les fichiers XML
        XMLParser XMLparser;
        
    //une classe qui permet de charger les fichiers de sons et d'images
        FileLoader fileLoader;

    //liste de sprite, qui sera rangée dans le bon ordre, selon ce qui est spécifié
    //dans le fichier de définition du film, quand y'a des balises PlanRedef
    SceneElt **sceneEltsSortedList;

    //toutes les fonctions internes. Et va y'en avoir beaucoup, bordel de merde!!
        string ReadSplashBaliz();
        string ReadImgSoundDatas();

    //les fonctions pour charger les données, avant de charger le déroulement du film
        string ReadNodeOfColor(string balizName, Uint32 *transpColor);
        string ReadCoord(string balizName, SDL_Rect *coord, int readRectCoord = 0,
                         int mustDefineAllValues = 0);
        string ReadImage(ChainListOfImg *chainListOfImgDest);
        string ReadMakeImgByZoom(ChainListOfImg *chainListOfImgDest);
        string ReadListOfImg();
        string ReadSpriteDefinition();
        string ReadFreeImgFile();

        string FillPlanOrganization(long int time, long int *_sceneEltQty);
        string Read_SpriteSetAll(ChainListOfMovieEvent *listDest, long int time);
        string Read_Sprite(ChainListOfMovieEvent *listDest, long int *time);
        string Read_SceneSetAll(ChainListOfMovieEvent *listDest, long int time);
        string Read_Swap2Plans(ChainListOfMovieEvent *listDest, long int time);

        string ReadSequence(ChainListOfMovieEvent *listDest);
        string ReadProcedure();
        string ReadProcedureExecution(ChainListOfMovieEvent *listDest, long int *time,
                                      int complexExecution = 0);
                                      
        string ReadPercentageInfos();
        string ReadMainFilm();
        
    //la barre de pourcentage, et les infos qui vont avec
        PercentageBar percentageBar;
        long int percentageInfoNbrOfFileToExtract;
        long int percentageInfoNbrOfImgListToCreate;
        long int percentageInfoNbrOfProcedureToCreate;
        long int percentageTotal;
        long int percentageProgress;
        
        void AdvanceAndShowProgress();


    public:

        DataLoader(SoundPlayer *_soundPlayer, ImagePlayer *_imagePlayer,
                   SDL_Surface *_mainScreen, ConfigInfos *_theConfigInfos, Scene *_scene);
        ~DataLoader();

        string OpenFilmXMLFile(char *scriptFileName);
        string ReadFilmXMLFile();
        void CloseFilmXMLFile();

        MovieEvent **ExtractListOfMovieEvent(int ME_typeToGet, long int *qtyExtracted);
        MovieEvent **ExtractAndDefineListOfBreakPoint(long int *qtyExtracted);

};
