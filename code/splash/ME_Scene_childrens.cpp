#include "ME_Scene_childrens.hpp"



ME_Scene_SetAllInfos::ME_Scene_SetAllInfos(long int _actTime, Scene *_affectedScene,
                      Uint16 sceneSizeX, Uint16 sceneSizeY,
                      SceneElt **_sceneEltsSortedList, long int _sceneEltQty,
                      Uint32 _surfaceTypeOfScene, Uint32 _surfaceTypeOfZoomedScene,
                      SDL_Rect *_newCamPos/* = NULL*/, long int _zoomScene/* = 1024*/,
                      int _mustBeCleared/* = 0*/, Uint32 _clearColor/* = 0*/)
    : ME_Scene(_actTime, _affectedScene)
{
    SizeX = sceneSizeX;
    SizeY = sceneSizeY;
    sceneEltQty = _sceneEltQty;
    zoomScene = _zoomScene;
    mustBeCleared = _mustBeCleared;
    clearColor = _clearColor;
    surfaceTypeOfScene = _surfaceTypeOfScene;
    surfaceTypeOfZoomedScene = _surfaceTypeOfZoomedScene;
    if (_newCamPos == NULL) {
        newCamPos = NULL;
    } else {
        newCamPos = new SDL_Rect;
        SetRectXY(newCamPos, _newCamPos->x, _newCamPos->y);
    }
    if (_sceneEltsSortedList != NULL ) {
        sceneEltsSortedList = new SceneElt *[sceneEltQty];
        for (long int i=0 ; i<sceneEltQty ; i++) {
            sceneEltsSortedList[i] = _sceneEltsSortedList[i];
        }
    } else {
        sceneEltsSortedList = NULL;
    }
}

ME_Scene_SetAllInfos::~ME_Scene_SetAllInfos() {
    if (newCamPos != NULL) { delete newCamPos; }
    if (sceneEltsSortedList != NULL) { delete sceneEltsSortedList; }
}

void ME_Scene_SetAllInfos::Act()
{
    if (affectedScene != NULL) {
        affectedScene->NewScene(SizeX, SizeY,
                                sceneEltsSortedList, sceneEltQty,
                                surfaceTypeOfScene, surfaceTypeOfZoomedScene,
                                newCamPos, zoomScene, mustBeCleared, clearColor);
        }
}

MovieEvent *ME_Scene_SetAllInfos::Copy(long int timeToAdd)
{
	return (MovieEvent *) new
        ME_Scene_SetAllInfos(actTime+timeToAdd, affectedScene, SizeX, SizeY,
							 sceneEltsSortedList, sceneEltQty,
							 surfaceTypeOfScene, surfaceTypeOfZoomedScene,
							 newCamPos, zoomScene, mustBeCleared, clearColor);
}

//-------------------------------------------


ME_Scene_SetCameraPos::ME_Scene_SetCameraPos(long int _actTime,
                                             Scene *_affectedScene, SDL_Rect *_newCamPos)
    : ME_Scene(_actTime, _affectedScene)
{
    if (_newCamPos == NULL) {
        newCamPos = NULL;
    } else {
        newCamPos = new SDL_Rect;
        SetRectXY(newCamPos, _newCamPos->x, _newCamPos->y);
    }
}

ME_Scene_SetCameraPos::~ME_Scene_SetCameraPos()
{
    if (newCamPos != NULL) { delete newCamPos; }
}

void ME_Scene_SetCameraPos::Act()
{
    if (affectedScene != NULL) { affectedScene->SetHotPoint(newCamPos); }
}

MovieEvent *ME_Scene_SetCameraPos::Copy(long int timeToAdd)
{
	return (MovieEvent *) new
        ME_Scene_SetCameraPos(actTime+timeToAdd, affectedScene, newCamPos);
}

//-------------------------------------------

ME_Scene_Swap2Plans::ME_Scene_Swap2Plans(long int _actTime, Scene *_affectedScene,
                                         SceneElt *_SceneElt1, SceneElt *_SceneElt2)
    : ME_Scene(_actTime, _affectedScene)
{
    SceneElt1 = _SceneElt1;
    SceneElt2 = _SceneElt2;
}

ME_Scene_Swap2Plans::~ME_Scene_Swap2Plans() {}

void ME_Scene_Swap2Plans::Act()
{
    if (affectedScene != NULL) { affectedScene->Swap2Plans(SceneElt1, SceneElt2); }
}

MovieEvent *ME_Scene_Swap2Plans::Copy(long int timeToAdd)
{
	return (MovieEvent *) new
        ME_Scene_Swap2Plans(actTime+timeToAdd, affectedScene, SceneElt1, SceneElt2);
}

//-------------------------------------------

ME_Scene_SetSceneEltToDraw::ME_Scene_SetSceneEltToDraw(long int _actTime,
                                                       Scene *_affectedScene,
                                                       SceneElt **_sceneEltsSortedList,
                                                       long int _sceneEltQty)
    : ME_Scene(_actTime, _affectedScene)
{
    sceneEltQty = _sceneEltQty;
    if (_sceneEltsSortedList != NULL ) {
        sceneEltsSortedList = new SceneElt *[sceneEltQty];
        for (long int i=0 ; i<sceneEltQty ; i++) {
            sceneEltsSortedList[i] = _sceneEltsSortedList[i];
        }
    } else {
        sceneEltsSortedList = NULL;
    }
}

ME_Scene_SetSceneEltToDraw::~ME_Scene_SetSceneEltToDraw()
{
    if (sceneEltsSortedList!=NULL) {delete sceneEltsSortedList;}
}

void ME_Scene_SetSceneEltToDraw::Act()
{
    if (affectedScene != NULL) {
        affectedScene->SetSceneEltsSortedList(sceneEltsSortedList, sceneEltQty);
    }
}

//Est-ce que je peux licencier mon anus si j'estime qu'il fout de la merde partout
//autour de lui dès que je chie. Et après je suis obligé de passer une heure à
//m'essuyer avec du papier?
//Je fait un procès à mon anus.


MovieEvent *ME_Scene_SetSceneEltToDraw::Copy(long int timeToAdd)
{
	return (MovieEvent *) new ME_Scene_SetSceneEltToDraw(
                        actTime+timeToAdd, affectedScene, sceneEltsSortedList, sceneEltQty);
}

//-------------------------------------------

ME_Scene_SetZoomScene::ME_Scene_SetZoomScene(long int _actTime, Scene *_affectedScene,
                                             long int _zoomScene)
    : ME_Scene(_actTime, _affectedScene)
{
    zoomScene = _zoomScene;
}

ME_Scene_SetZoomScene::~ME_Scene_SetZoomScene() {}

void ME_Scene_SetZoomScene::Act()
{
    if (affectedScene != NULL) { affectedScene->SetZoomScene(zoomScene); }
}

MovieEvent *ME_Scene_SetZoomScene::Copy(long int timeToAdd)
{
	return (MovieEvent *) new
        ME_Scene_SetZoomScene(actTime+timeToAdd, affectedScene, zoomScene);
}

//-------------------------------------------

ME_Scene_SetSceneClearance::ME_Scene_SetSceneClearance(long int _actTime,
                                                       Scene *_affectedScene,
                                                       int _mustBeCleared,
                                                       Uint32 _clearColor/* = 0*/)
    : ME_Scene(_actTime, _affectedScene)
{
    mustBeCleared = _mustBeCleared;
    clearColor = _clearColor;
}

ME_Scene_SetSceneClearance::~ME_Scene_SetSceneClearance() {}

void ME_Scene_SetSceneClearance::Act()
{
    if (affectedScene != NULL) {
        affectedScene->SetSceneClearance(mustBeCleared, clearColor);
    }
}

MovieEvent *ME_Scene_SetSceneClearance::Copy(long int timeToAdd)
{
	return (MovieEvent *) new ME_Scene_SetSceneClearance(
                            actTime+timeToAdd, affectedScene, mustBeCleared, clearColor);
}
