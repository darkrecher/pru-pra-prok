#include "ImagePlayer.hpp"



ImagePlayer::ImagePlayer(SDL_Surface *_mainScreen, ConfigInfos *_theConfigInfos,
                         PercentageBar *_percentageBar)
{
    mainScreen = _mainScreen;
    theConfigInfos = _theConfigInfos;
    percentageBar = _percentageBar;
       
    bufferScreens = new BufferScreens(theConfigInfos->GetBufferScreenQty(), 
                                      theConfigInfos->GetSurfaceTypeOfBuffers());
    scene = new Scene();
    
//    showDetails = 0;
    totalLateTime = 0;
    lateImagesQty = 0;
    totalWaitingTime = 0;
    dateOfPeriodOfWaiting = -1;
}


ImagePlayer::~ImagePlayer()
{
    delete scene;    
    delete bufferScreens;
    delete listOfMovieEvent;
}


void ImagePlayer::SetListOfMovieEvent(MovieEvent **_listOfMovieEvent, long int _movieEventQty)
{
    listOfMovieEvent = _listOfMovieEvent;
    movieEventQty = _movieEventQty;
}


Scene *ImagePlayer::GetScene() { return scene; }


void ImagePlayer::SetDeltaTime(long int _deltaTime) { deltaTime = _deltaTime; }


int ImagePlayer::GoToBreakPoint(long int cursor_ME_Index)
{
    bufferScreens->ResetBuffers();
    cursor_ME = cursor_ME_Index;
    int i = 0;
    int ArrivedAtEndOfFilm = 0;
    
    //ajout de code l'arrache. C'est pour la correction du bug que y'a tout qui tout plante
    //quand un breakpoint est situ� apr�s la fin du film. (ce que j'interdit
    //� un autre endroit du code, car c'est d�bile). Mais avec �a, m�me si on a un breakpoint
    //apr�s la fin, �a plante pas.
    if (cursor_ME >= movieEventQty) {
        ArrivedAtEndOfFilm = 1;
    } else {
        timeOfWorkingScreen = listOfMovieEvent[cursor_ME]->GetActTime();
    }
    //timeOfWorkingScreen = listOfMovieEvent[cursor_ME]->GetActTime();


    //re-ajout de code � l'arrache, pour autre chose.
    //correction du bug � la con qui arrive quand on passe d'une sc�ne � l'autre
    //qui ont pas le m�me zoom, ou la m�me CamPos, ou d'autres trucs.
    if (scene != NULL) {
        SDL_Rect centerOfScene;
        SetRectXY(&centerOfScene, SCREEN_MIDDLE_X, SCREEN_MIDDLE_Y);
        scene->SetHotPoint(&centerOfScene);
        scene->SetZoomScene(1024);
        scene->SetSceneClearance(0, 0);
    }

    while ( (i < theConfigInfos->GetBufferScreenToLoadAtBeginning()) && 
            (!ArrivedAtEndOfFilm) )
    {
        while ( (cursor_ME < movieEventQty) &&
                (listOfMovieEvent[cursor_ME] != NULL) && 
                (listOfMovieEvent[cursor_ME]->GetActTime() == timeOfWorkingScreen) ) 
        {       
            listOfMovieEvent[cursor_ME]->Act();        
            cursor_ME++;
        }
        
        scene->RestartDrawing();
        while (scene->MoreSceneEltToDraw()) { scene->DrawNextSceneElt(); }
        bufferScreens->AddScreenInBuffers(scene, timeOfWorkingScreen);
        
        if ( (cursor_ME >= movieEventQty) || (listOfMovieEvent[cursor_ME] == NULL) ) {
            ArrivedAtEndOfFilm = 1;
        } else {
            timeOfWorkingScreen = listOfMovieEvent[cursor_ME]->GetActTime();
        }
        i++;    
    }
    
    if (ArrivedAtEndOfFilm) {
        currentAction = FINISHED_IMAGE_GENERATION;
    } else {
        currentAction = APPLYING_EVENT;
    }
    return ArrivedAtEndOfFilm;
}


void ImagePlayer::ShowNextScreen()
{
    SDL_BlitSurface(bufferScreens->GetNextScreenToShow(), NULL, mainScreen, NULL);
    //affichage de la barre de pourcentage si y'a besoin
    if (percentageBar->GetMustShowOnScreen()) { percentageBar->ShowOnScreen(); }    
    SDL_Flip(mainScreen);
}


void ImagePlayer::DoOneLoop()
{
    long int loopStartDate;
    long int timeOfTreatment;
    long int timeOfFilm = SDL_GetTicks() - deltaTime;
    
    while ( (bufferScreens->CanHaveNextScreenToShow()) && 
            (timeOfFilm >= bufferScreens->GetTimeOfNextScreenToShow()) ) 
    {
    
        if (dateOfPeriodOfWaiting != -1) {
            totalWaitingTime += SDL_GetTicks() - dateOfPeriodOfWaiting;
            dateOfPeriodOfWaiting = -1;
        }
        if (timeOfFilm > bufferScreens->GetTimeOfNextScreenToShow()) {
            totalLateTime += timeOfFilm - bufferScreens->GetTimeOfNextScreenToShow();
            lateImagesQty++;
        }
        if (theConfigInfos->GetShowDetails()) {
            cout << "Affichage � la date " << timeOfFilm << " de l'image de date = ";
            cout  << bufferScreens->GetTimeOfNextScreenToShow() <<endl;
        }
        
        ShowNextScreen();
        bufferScreens->AdvanceNextScreenToShow();
        if (currentAction == WAITING) { 
            currentAction = COPYING_SCENE;
        }
        if ( (currentAction == FINISHED_IMAGE_GENERATION) &&
             (!bufferScreens->CanHaveNextScreenToShow()) )
        {
            currentAction = FINISHED_FILM;
        }
        timeOfFilm = SDL_GetTicks() - deltaTime;
    }
    
//Merci d'avoir fait de moi un �tre humain.
//Merci de m'avoir donn� du savoir, pour que je m'int�gre dans un m�tier
//Merci d'avoir vid� mon esprit, pour que je puisse jouer des r�les en soci�t�
//Merci de me rappeler sans cesse mon ignorance, pour que ma soif ne s'apaise jamais
//Merci de m'avoir donn� la folie, pour voir la soci�t� autrement
//Merci d'avoir rempli mon �me, pour avoir des choses terribles � raconter
//Merci de m'avoir fait na�tre en ces temps troubl�s, pour donner un sens � ma vie
//Merci de m'offrir un minuscule espace dans l'une des pages encore blanche de l'histoire
//
//
//Et je ne m'adresse pas � Dieu, mais simplement au hasard. Peut �tre que le hasard est Dieu.
    
    loopStartDate = SDL_GetTicks();
    
    switch (currentAction) {
        
        case APPLYING_EVENT :
            listOfMovieEvent[cursor_ME]->Act();
            cursor_ME++;
            if ( (cursor_ME >= movieEventQty) ||
                 (listOfMovieEvent[cursor_ME] == NULL))
            {
                currentAction = RESETTING_SCENE;
                timeOfBuiltScreen = timeOfWorkingScreen;
            } 
            else 
            {
                if (timeOfWorkingScreen != listOfMovieEvent[cursor_ME]->GetActTime()) 
                {
                    currentAction = RESETTING_SCENE;
                    timeOfBuiltScreen = timeOfWorkingScreen;
                    timeOfWorkingScreen = listOfMovieEvent[cursor_ME]->GetActTime();
                }
            }
        break;
        
        case RESETTING_SCENE :
            scene->RestartDrawing();
            currentAction = PLACING_ELEMENT;
            if (theConfigInfos->GetShowDetails()) {
                timeOfTreatment = SDL_GetTicks() - loopStartDate;
                cout << "r�initialisation de la sc�ne. dur�e = " << timeOfTreatment << endl;
            }
        break;

        
        case PLACING_ELEMENT :
            scene->DrawNextSceneElt();
            if (!scene->MoreSceneEltToDraw()) {
                currentAction = COPYING_SCENE;
            }
            if (theConfigInfos->GetShowDetails()) {
                timeOfTreatment = SDL_GetTicks() - loopStartDate;
                cout << "affichage d'un sprite.        dur�e = " << timeOfTreatment << endl;
            }
        break;
                    
        case COPYING_SCENE :
            if (bufferScreens->CanPutNewScreenInBuffers()) {
                bufferScreens->AddScreenInBuffers(scene, timeOfBuiltScreen);
                currentAction = TESTING_FILM_ENDED;
                if (theConfigInfos->GetShowDetails()) {
                    timeOfTreatment = SDL_GetTicks() - loopStartDate;
                    cout << "copie de la sc�ne.            dur�e = " << timeOfTreatment<<endl;
                }
            } else {
                currentAction = WAITING;
                if (theConfigInfos->GetShowDetails()) { cout << "je glande" << endl; }
                dateOfPeriodOfWaiting = SDL_GetTicks();
            }
        break;
        
        case TESTING_FILM_ENDED :
            if ( (cursor_ME >= movieEventQty) || (listOfMovieEvent[cursor_ME] == NULL) ) {
                if (!bufferScreens->CanHaveNextScreenToShow()) {
                    currentAction = FINISHED_FILM;
                } else {
                    currentAction = FINISHED_IMAGE_GENERATION;
                }
            } else {
                currentAction = APPLYING_EVENT;
            }
        break;
        
        case WAITING :
            if (bufferScreens->GetTimeOfNextScreenToShow()-timeOfFilm > 6) { SDL_Delay(4); }
        break;
        
        case FINISHED_IMAGE_GENERATION :
            if (bufferScreens->GetTimeOfNextScreenToShow()-timeOfFilm > 6) { SDL_Delay(4); }
        break;
        
    }
}


void ImagePlayer::WriteStatistics()
{
    cout << "Alarrachitude cumul�e : " << totalLateTime << " ms" << endl;
    cout << "Nombre d'images alarrach�e : " << lateImagesQty << endl;
    cout << "Glanditude cumul�e : " << totalWaitingTime << " ms" << endl << endl;
}
