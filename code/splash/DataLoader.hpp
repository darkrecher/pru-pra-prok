//oul�! �a en fait du bordel!! Faut croire que y'a vraiment besoin de tout �a, ouais.


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
// caillou 2 : Ah c'est int�ressant. J'en prend note. En ce qui me concerne : 0110110101100
// caillou 1 : Oh c'est chouette �a! D'aileurs, figure toi que 00100110111010111 !!
//
// Mais qu'est-ce donc? Eh bien c'est du P2P!! (pierre-to-pierre)
// Il s'agit d'une activit� fortement pratiqu� aux temps pr�historique,
// puisqu'� l'�poque, tout le monde s'appelait Pierre. (cf RRRRrrrrrrrhhhh!!!! Le film des
// autres andouilles).



class DataLoader
{


    private:

    //pointeur vers la classe qui affichera les images du films.
        ImagePlayer *imagePlayer;

    //pointeur vers la classe qui joue les sons
        SoundPlayer *soundPlayer;

    //pointeur vers l'�cran principal.
        SDL_Surface *mainScreen;

    //pointeur vers les infos de config.
        ConfigInfos *theConfigInfos;

    //liste chain�e des fichiers images dans lesquels r�cup�rer les donn�es
        ChainListOfSDLSurface *chainListOfSDLSurface;

    //liste des sons
        ChainListOfSound *chainListOfSound;

    //pointeur vers la sc�ne de la classe ImagePlayer (certains �v�nements de film agissent
    //sur l'objet "Scene", donc il faut leur passer en param�tre.
        Scene *scene;

    //la liste des ImgList. Liste cha�n�e, pour pouvoir cr�er les listes d'images au fur
    //et � mesure qu'on les lit dans le fichier XML (enfin, quand y'aura le fichier XML)
        ChainListOf_ListOfImg *chainListOf_ListOfImg;

    //la liste des sprites. Liste cha�n�e, pareil. Pour pouvoir les cr�er au fur et � mesure.
        ChainListOfSprite *chainListOfSprite;

    //liste des �v�nements du films.
        ChainListOfMovieEvent *chainListOfMovieEvent;
        
        
    //liste de proc�dure = liste de liste de MovieEvent, si �a vous plait pas aller vous pendre
        ChainListOfProcedure *chainListOfProcedure;

    // une classe qui lit les fichiers XML
        XMLParser XMLparser;
        
    //une classe qui permet de charger les fichiers de sons et d'images
        FileLoader fileLoader;

    //liste de sprite, qui sera rang�e dans le bon ordre, selon ce qui est sp�cifi�
    //dans le fichier de d�finition du film, quand y'a des balises PlanRedef
    SceneElt **sceneEltsSortedList;

    //toutes les fonctions internes. Et va y'en avoir beaucoup, bordel de merde!!
        string ReadSplashBaliz();
        string ReadImgSoundDatas();

    //les fonctions pour charger les donn�es, avant de charger le d�roulement du film
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
