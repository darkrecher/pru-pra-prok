#include "Scene.hpp"



Scene::Scene() 
{
    theScene = NULL;
    sceneEltsSortedList = NULL;
    sceneEltQty = 0;
    zoomScene = 1024;
    mustBeCleared = 0;
}

    
Scene::~Scene() 
{
    if (theScene != NULL) { delete theScene; }
    if (sceneEltsSortedList != NULL) { delete sceneEltsSortedList; }
}


void Scene::NewScene(Uint16 sceneSizeX, Uint16 sceneSizeY,
                     SceneElt **_sceneEltsSortedList, long int _sceneEltQty, 
                     Uint32 surfaceTypeOfScene, Uint32 surfaceTypeOfZoomedScene,
                     SDL_Rect *_hotPoint = NULL, long int _zoomScene = 1024,
                     int _mustBeCleared = 0, Uint32 _clearColor = 0)
{
    if (theScene != NULL) { delete theScene; }
    
    theScene = new ImageZoomable(sceneSizeX, sceneSizeY,
                                 surfaceTypeOfScene, surfaceTypeOfZoomedScene);
    SetHotPoint(_hotPoint);

    SetSceneEltsSortedList(_sceneEltsSortedList, _sceneEltQty);
    SetZoomScene(_zoomScene);
    SetSceneClearance(_mustBeCleared, _clearColor);
    nextSceneEltToDraw = 0;
}


void Scene::SetSceneEltsSortedList(SceneElt **_sceneEltsSortedList, long int _sceneEltQty)
{
    if (_sceneEltsSortedList == NULL) {
        sceneEltsSortedList = NULL;
        sceneEltQty = 0;
    } else {
        if (sceneEltsSortedList != NULL) { delete sceneEltsSortedList; }
        sceneEltQty = _sceneEltQty;
        sceneEltsSortedList = new SceneElt *[sceneEltQty];
        for (long int i=0 ; i<sceneEltQty ; i++) { 
            sceneEltsSortedList[i] = _sceneEltsSortedList[i]; 
        }
    }    
}

    
void Scene::SetZoomScene(long int  _zoomScene) { zoomScene = _zoomScene; }


void Scene::SetSceneClearance(int _mustBeCleared, Uint32 _clearColor = 0) {
    mustBeCleared = _mustBeCleared;
    clearColor = _clearColor;
}

    
void Scene::SetHotPoint(SDL_Rect *_hotPoint) 
{
    //correction de bug à l'arrache (putain-bordel, rien qu'en corrigeant ce petit bout de
    //truc, je me dis que le code est mal foutu. J'imagine même pas ce que ça donnerait
    //si je recontrôlais tout. Whizz!!
    if (theScene == NULL) { return; }
    
    if (_hotPoint == NULL) {
        SDL_Rect hotPoint2;
        SetRectXY(&hotPoint2, SCREEN_MIDDLE_X, SCREEN_MIDDLE_Y);
        theScene->SetHotPoint(&hotPoint2);
    } else {
        theScene->SetHotPoint(_hotPoint);
    }
}


void Scene::Swap2Plans(SceneElt *sceneElt1, SceneElt *sceneElt2) 
{
    long int SceneElt1Pos = -1;
    long int SceneElt2Pos = -1;
    long int i = 0;
    while ( ((SceneElt1Pos==-1) && (SceneElt2Pos==-1)) || (i<sceneEltQty) ) { 
        if (sceneEltsSortedList[i] == sceneElt1) { SceneElt1Pos = i; }
        if (sceneEltsSortedList[i] == sceneElt2) { SceneElt2Pos = i; }
        i++; 
    }
    if ((SceneElt1Pos!=-1) && (SceneElt2Pos!=-1)) {
        SceneElt *StockValue = sceneEltsSortedList[SceneElt2Pos];
        sceneEltsSortedList[SceneElt2Pos] = sceneEltsSortedList[SceneElt1Pos];
        sceneEltsSortedList[SceneElt1Pos] = StockValue;
    }
}


//Sur le ciel vaguement bleu orangé un papillon se découpe,
//se prépare à se battre en duel contre son père ennemi,
//sort une bouteille d'absinthe de sa poche réverbère et envoie paître
//les vaches brouter à la SNCF tout est possible n'est pas français
//à moins que si on mettait Paris en bouteille ça sentirait la roche qui pue du métro.
    
    
int Scene::DrawNextSceneElt()
{
    if (nextSceneEltToDraw < sceneEltQty) {
        SceneElt *eltToDraw = sceneEltsSortedList[nextSceneEltToDraw];
        eltToDraw->DrawOnScene(theScene->GetImage());
        nextSceneEltToDraw++;
    } 
    if (nextSceneEltToDraw >= sceneEltQty) { return 0; }
    return 1;
}


int Scene::MoreSceneEltToDraw()
{
    if (nextSceneEltToDraw >= sceneEltQty) { return 0; }
    return 1;
}


void Scene::RestartDrawing() {
    if (mustBeCleared) {
        SDL_FillRect(theScene->GetImage(), NULL, clearColor);
    }
    nextSceneEltToDraw = 0;
}

    
void Scene::ClearScene() {
    SDL_FillRect(theScene->GetImage(), NULL, 0);
    RestartDrawing();
}
    
    
void Scene::GetScreenToShow(SDL_Surface *ScreenToShow)
{
    SDL_Rect destRect;
    SetRectXY(&destRect, SCREEN_MIDDLE_X, SCREEN_MIDDLE_Y);
    if (zoomScene == 1024) {
        theScene->Blit(NULL, ScreenToShow, &destRect);
    } else {
        theScene->ZoomAndBlit(NULL, ScreenToShow, &destRect, zoomScene);
    }
}

