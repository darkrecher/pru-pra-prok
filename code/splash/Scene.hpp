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

//Voil�, alors le probl�me avec cette cour de r�cr�ation, c'est qu'elle est pleine de mites.
//Et vous qui �tes allergique � ce genre de choses bizarres. Eh bien vous feriez peut �tre
//mieux d'aller voire des bi�res. Que pensez-vous du mot "feriez"? Il semble assez int�ressant.
//Mais nous ne sommes pas l� pour parler de �a. Qu'est-ce que vous pouvez savoir, que
//d'autres ne pourraient pas, et qui ne pourraient pas �tre d�duit automatiquement en
//collant du rouge � l�vres sur des rats? C'est ce qu'il va vous falloir essayer de
//d�velopper. Le reste n'est que du fantasme, ou alors des souvenirs oubli�s de
//bonshommes "sur des �tag�res" qui essayent de choper des bonbons et de sauter sur des
//cr�tins de m�chant. Ha! Comme si on avait pas d�j� fait �a mille fois!
//C'est un peu comme les �glises, ont en a d�j� fait mille, mais on en refait encore.


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
