#ifndef SCENE_INCLUDED__


#include "SceneElt.hpp"
#include "ImageZoomable.hpp"
#include "ScreenConst.hpp"


class Scene
{

private:

    ImageZoomable *theScene;
    SceneElt **sceneEltsSortedList;  
    long int sceneEltQty;
    long int zoomScene;  //virgule pas-flottante  (*1024)
    long int nextSceneEltToDraw;
    int mustBeCleared;
    Uint32 clearColor;

//Voilà, alors le problème avec cette cour de récréation, c'est qu'elle est pleine de mites.
//Et vous qui êtes allergique à ce genre de choses bizarres. Eh bien vous feriez peut être
//mieux d'aller voire des bières. Que pensez-vous du mot "feriez"? Il semble assez intéressant.
//Mais nous ne sommes pas là pour parler de ça. Qu'est-ce que vous pouvez savoir, que
//d'autres ne pourraient pas, et qui ne pourraient pas être déduit automatiquement en
//collant du rouge à lèvres sur des rats? C'est ce qu'il va vous falloir essayer de
//développer. Le reste n'est que du fantasme, ou alors des souvenirs oubliés de
//bonshommes "sur des étagères" qui essayent de choper des bonbons et de sauter sur des
//crétins de méchant. Ha! Comme si on avait pas déjà fait ça mille fois!
//C'est un peu comme les églises, ont en a déjà fait mille, mais on en refait encore.


public:

    Scene();
    ~Scene();

    void NewScene(Uint16 sceneSizeX, Uint16 sceneSizeY,
                  SceneElt **_sceneEltsSortedList, long int _sceneEltQty, 
                  Uint32 surfaceTypeOfScene, Uint32 surfaceTypeOfZoomedScene,
                  SDL_Rect *_hotPoint = NULL, long int _zoomScene = 1024,
                  int _mustBeCleared = 0, Uint32 _clearColor = 0);

    void SetSceneEltsSortedList(SceneElt **_sceneEltsSortedList, long int _sceneEltQty);
    void SetZoomScene(long int _zoomScene);
    void SetHotPoint(SDL_Rect *_hotPoint);
    void Swap2Plans(SceneElt *sceneElt1, SceneElt *sceneElt2);
    void SetSceneClearance(int _mustBeCleared, Uint32 _clearColor = 0);
    
    int DrawNextSceneElt();
    int MoreSceneEltToDraw();
    void ClearScene();
    void RestartDrawing();
    void GetScreenToShow(SDL_Surface *ScreenToShow);

};


#define SCENE_INCLUDED__


#endif
