#include "ME_Scene.hpp"



class ME_Scene_SetAllInfos : public ME_Scene
{

private:

    Uint16 SizeX;
    Uint16 SizeY;
    SDL_Rect *newCamPos;
    SceneElt **sceneEltsSortedList;
    long int sceneEltQty;
    long int zoomScene;
    int mustBeCleared;
    Uint32 clearColor;
    Uint32 surfaceTypeOfScene;
    Uint32 surfaceTypeOfZoomedScene;

public:

    ME_Scene_SetAllInfos(long int _actTime, Scene *_affectedScene,
                         Uint16 sceneSizeX, Uint16 sceneSizeY,
                         SceneElt **_sceneEltsSortedList, long int _sceneEltQty,
                         Uint32 _surfaceTypeOfScene, Uint32 _surfaceTypeOfZoomedScene,
                         SDL_Rect *_newCamPos = NULL, long int _zoomScene = 1024,
                         int _mustBeCleared = 0, Uint32 _clearColor = 0);

    ~ME_Scene_SetAllInfos();
    void Act();
    MovieEvent *Copy(long int timeToAdd);

};

//-------------------------------------------

class ME_Scene_SetCameraPos : public ME_Scene
{

private:

    SDL_Rect *newCamPos;

public:

    ME_Scene_SetCameraPos(long int _actTime, Scene *_affectedScene, SDL_Rect *_newCamPos);
    ~ME_Scene_SetCameraPos();
    void Act();
	MovieEvent *Copy(long int timeToAdd);

};

//-------------------------------------------

class ME_Scene_Swap2Plans : public ME_Scene
{

private:

    SceneElt *SceneElt1;
    SceneElt *SceneElt2;

public:

    ME_Scene_Swap2Plans(long int _actTime, Scene *_affectedScene,
                          SceneElt *_SceneElt1, SceneElt *_SceneElt2);

    ~ME_Scene_Swap2Plans();
    void Act();
	MovieEvent *Copy(long int timeToAdd);

};

//-------------------------------------------

class ME_Scene_SetSceneEltToDraw : public ME_Scene
{

//Le feu de tes genoux sur ta robe de paille. Des kiwis pleins les oreilles
//Y'a pas de rose dans le soleil qui se lève de la montagne. Je l'escalade pour
//le simple plaisir de fermer les yeux une fois arrivé en haut et faire raler les
//gens autour de moi et les désespérer. C'est si bon de faire des efforts pour obtenir
//quelque chose et refuser cette chose au dernier moment. Je ne veux pas d'une vie
//
//c'est difficile de faire de l'écriture spontanée sans tout ramener à des "je je je"
//
//JE m'en fiche. Si c'est moi qui suis là, et qu'il n'y a rien d'autre, ne venez pas me
//le reprocher, parce que je m'en fiche. Vous n'avez pas le droit de dire que c'est nul.
//Pasque vous existez pas, grâce au "je je je".


private:

    SceneElt **sceneEltsSortedList;
    long int sceneEltQty;

public:

    ME_Scene_SetSceneEltToDraw(long int _actTime, Scene *_affectedScene,
                               SceneElt **_sceneEltsSortedList, long int _sceneEltQty);

    ~ME_Scene_SetSceneEltToDraw();
    void Act();
	MovieEvent *Copy(long int timeToAdd);

};

//-------------------------------------------

class ME_Scene_SetZoomScene : public ME_Scene
{

private:

    long int zoomScene;

public:

    ME_Scene_SetZoomScene(long int _actTime, Scene *_affectedScene, long int _zoomScene);

    ~ME_Scene_SetZoomScene();
    void Act();
	MovieEvent *Copy(long int timeToAdd);

};

//-------------------------------------------

class ME_Scene_SetSceneClearance : public ME_Scene
{

private:

    int mustBeCleared;
    Uint32 clearColor;

public:

    ME_Scene_SetSceneClearance(long int _actTime, Scene *_affectedScene,
                               int _mustBeCleared, Uint32 _clearColor = 0);

    ~ME_Scene_SetSceneClearance();
    void Act();
	MovieEvent *Copy(long int timeToAdd);

};
