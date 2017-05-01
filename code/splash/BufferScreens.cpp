#include "BufferScreens.hpp"



BufferScreens::BufferScreens(int _bufferQty, Uint32 _surfaceTypeOfBuffers)
{
    bufferQty = _bufferQty;
    cursor_ScreenInWork = 0;
    cursor_NextScreenToShow = 0;
    distBetweenCursors = 0;
    timeOfNextScreenToShow = -1;
    screens = new SDL_Surface *[bufferQty];
    timesToShowScreens = new long int[bufferQty];
    for (int i=0 ; i<bufferQty ; i++) {
        screens[i] = SDL_CreateRGBSurface(_surfaceTypeOfBuffers,
                                          SCREEN_SIZE_X, SCREEN_SIZE_Y, 32,0,0,0,0);
    }
}

//    "Le piratage nuit � la cr�ation artistique"
//c'est ce qui �tait �crit dans un d�pliant explicatif de wanadoo-france-t�l�com.
//Parce que avoir du haut d�bit Internet, c'est bien, mais l'utiliser pour faire
//du t�l�chargement ill�gal, c'est maaaaaaal!!!
//Hahaha!! Je n'ai pas ce probl�me l�. Le piratage n'a pas de sens pour moi. Puisque j'ai mis
//mes histoires � disposition de tout le monde. Gratoche. De plus, je suis sur qu'il y a moyen
//de se faire un nom et de se faire conna�tre en ne faisant que de l'Art Libre.
//Vu que c'est une notion encore assez nouvelle, �a devrait attirer des gens.
//On verra bien comment les b�tises que j'imagine �voluent plus tard...
//Voulez-vous venir avec moi? et d�couvrir ensemble ce qu'on peut fabriquer en ne vendant rien?


BufferScreens::~BufferScreens()
{
    for (int i=0 ; i<bufferQty ; i++) { SDL_FreeSurface(screens[i]); }
    delete screens;
    delete timesToShowScreens;
}

int BufferScreens::CanPutNewScreenInBuffers()
{
    if (distBetweenCursors < bufferQty) { return 1; }
    return 0;
}


int BufferScreens::CanHaveNextScreenToShow()
{
    if (distBetweenCursors > 0) { return 1; }
    return 0;
}


SDL_Surface *BufferScreens::GetNextScreenToShow() {
    if (distBetweenCursors == 0) {
        return NULL;
    } else {
        return screens[cursor_NextScreenToShow];
    }
}


int BufferScreens::GetTimeOfNextScreenToShow() { return timeOfNextScreenToShow; }


int BufferScreens::AdvanceNextScreenToShow()
{
    if (distBetweenCursors > 0) {
        cursor_NextScreenToShow++;
        if (cursor_NextScreenToShow == bufferQty) { cursor_NextScreenToShow = 0; }
        distBetweenCursors--;
        timeOfNextScreenToShow = timesToShowScreens[cursor_NextScreenToShow];
        return 1;
    } else {
        timeOfNextScreenToShow = -1;
        return 0;
    }
}


int BufferScreens::AddScreenInBuffers(Scene *sceneWithBuffer, long int TimeToShow) {
    if (CanPutNewScreenInBuffers()) {
        sceneWithBuffer->GetScreenToShow(screens[cursor_ScreenInWork]);
        timesToShowScreens[cursor_ScreenInWork] = TimeToShow;
        cursor_ScreenInWork++;
        if (cursor_ScreenInWork == bufferQty) { cursor_ScreenInWork = 0; }
        distBetweenCursors++;
        if (timeOfNextScreenToShow == -1) {
            timeOfNextScreenToShow = timesToShowScreens[cursor_NextScreenToShow];
        }
        return 1;
    } else {
        return 0;
    }
}


void BufferScreens::ResetBuffers()
{
    cursor_ScreenInWork = 0;
    cursor_NextScreenToShow = 0;
    distBetweenCursors = 0;
    timeOfNextScreenToShow = -1;
}
