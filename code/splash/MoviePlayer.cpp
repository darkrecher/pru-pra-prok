#include "MoviePlayer.hpp"



MoviePlayer::MoviePlayer(SDL_Surface *_mainScreen, ConfigInfos *_theConfigInfos)
{
    mainScreen = _mainScreen;
    theConfigInfos = _theConfigInfos;
    imagePlayer = NULL;
    soundPlayer = NULL;
    dataLoader = NULL;
    percentageBar = NULL;

    currentAction = PLAYING_FILM;
    listOfBreakPoint = NULL;
    breakPointQty = 0;
    cursorBreakPointToGo = -1;
}


MoviePlayer::~MoviePlayer()
{
    if (soundPlayer != NULL) { delete soundPlayer; }
    if (imagePlayer != NULL) { delete imagePlayer; }
    if (dataLoader != NULL) { delete dataLoader; }

    if (listOfBreakPoint != NULL) { delete listOfBreakPoint; }
    if (percentageBar != NULL) { delete percentageBar; }
}


int MoviePlayer::LoadData(char *scriptFileName)
{
    percentageBar = new PercentageBar(mainScreen);
    imagePlayer = new ImagePlayer(mainScreen, theConfigInfos, percentageBar);

    soundPlayer = new SoundPlayer(theConfigInfos);
    if (!soundPlayer->InitSoundDevice()) {
        cerr << "Impossible d'initialiser le son : " << Mix_GetError() << endl;
        if (theConfigInfos->GetStopIfSoundFail()) { return 0; }
    }

    dataLoader = new DataLoader(soundPlayer, imagePlayer,
                                mainScreen, theConfigInfos, imagePlayer->GetScene());

    string loadingFilmErrorMessage = dataLoader->OpenFilmXMLFile(scriptFileName);
    if (loadingFilmErrorMessage == "") {
        loadingFilmErrorMessage = dataLoader->ReadFilmXMLFile();
    }
    if (loadingFilmErrorMessage != "") {
        cerr << loadingFilmErrorMessage << endl;
        return 0;
    }

    dataLoader->CloseFilmXMLFile();

    listOfBreakPoint = (ME_BreakPoint **)
                       (dataLoader->ExtractAndDefineListOfBreakPoint(&breakPointQty));

    MovieEvent **listOfMovieEvent;
    long int movieEventQty;

    listOfMovieEvent = dataLoader->ExtractListOfMovieEvent(
                                  ChainListOfMovieEvent::ME_TYPE_IMAGE,
                                  &movieEventQty);

    imagePlayer->SetListOfMovieEvent(listOfMovieEvent, movieEventQty);
    long int lastDateOfImageEvent;
    if (movieEventQty > 0)
        { lastDateOfImageEvent = listOfMovieEvent[movieEventQty-1]->GetActTime(); }
    else
        { lastDateOfImageEvent = 0; }

    listOfMovieEvent = dataLoader->ExtractListOfMovieEvent(
                                  ChainListOfMovieEvent::ME_TYPE_SOUND,
                                  &movieEventQty);

    soundPlayer->SetListOfMovieEvent(listOfMovieEvent, movieEventQty);
    long int lastDateOfSoundEvent;
    if (movieEventQty > 0)
        { lastDateOfSoundEvent = listOfMovieEvent[movieEventQty-1]->GetActTime(); }
    else
        { lastDateOfSoundEvent = 0; }

    if (lastDateOfSoundEvent > lastDateOfImageEvent)
        { totalTimeOfFilm = lastDateOfSoundEvent; }
    else
        { totalTimeOfFilm = lastDateOfImageEvent; }

    cout << "La lecture du film a été effectuée. Durée totale : "
         << totalTimeOfFilm << " ms" << endl;
    cout << "Date de fin de chargement : " << SDL_GetTicks() << " ms" << endl << endl;
    return 1;
}


int MoviePlayer::TimeOfFilmIsAfterLastBreakPoint()
{
    if (listOfBreakPoint == NULL) { return 1; }
    if (SDL_GetTicks()-deltaTime > listOfBreakPoint[breakPointQty-1]->GetActTime()) {
        return 1;
    }
    return 0;
}


int MoviePlayer::TimeOfFilmIsBeforeFirstBreakPoint()
{
    if (listOfBreakPoint == NULL) { return 1; }
    if (SDL_GetTicks()-deltaTime < listOfBreakPoint[0]->GetActTime()) {
        return 1;
    }
    return 0;
}


void MoviePlayer::CursorBreakPointGoBack(int breakPointLevel)
{
    if (cursorBreakPointToGo == -1) {

        long int timeOfFilm = SDL_GetTicks() - deltaTime;
        long int precedentCursorBreakPoint = breakPointQty-1;
        while ((precedentCursorBreakPoint > 0) &&
               (listOfBreakPoint[precedentCursorBreakPoint]->GetActTime() > timeOfFilm))
        {
            precedentCursorBreakPoint--;
        }
        cursorBreakPointToGo = precedentCursorBreakPoint;

    } else {

        if (cursorBreakPointToGo > 0) { cursorBreakPointToGo--; }

    }

    while ((cursorBreakPointToGo > 0) &&
           (listOfBreakPoint[cursorBreakPointToGo]->GetLevel() > breakPointLevel))
    {
        cursorBreakPointToGo--;
    }
}


void MoviePlayer::CursorBreakPointGoAhead(int breakPointLevel)
{
    if (cursorBreakPointToGo == -1) {

        long int timeOfFilm = SDL_GetTicks() - deltaTime;
        long int nextCursorBreakPoint = 0;
        while ((nextCursorBreakPoint < breakPointQty-1) &&
               (listOfBreakPoint[nextCursorBreakPoint]->GetActTime() < timeOfFilm))
        {
            nextCursorBreakPoint++;
        }
        cursorBreakPointToGo = nextCursorBreakPoint;

    } else {

        if (cursorBreakPointToGo < breakPointQty-1) {
           cursorBreakPointToGo++;
        }

    }

    while ((cursorBreakPointToGo < breakPointQty-1) &&
           (listOfBreakPoint[cursorBreakPointToGo]->GetLevel() > breakPointLevel))
    {
        cursorBreakPointToGo++;
    }
}


void MoviePlayer::Play()
{
    int quit = 0;
    SDL_Event event;
    imagePlayer->GoToBreakPoint(0);
    deltaTime = SDL_GetTicks();
    imagePlayer->SetDeltaTime(deltaTime);
    soundPlayer->SetDeltaTime(deltaTime);

    while (!quit)
    {
        if (currentAction == PLAYING_FILM) {
            imagePlayer->DoOneLoop();
            soundPlayer->DoOneLoop();
        }

        if ((percentageBar->GetMustShowOnScreen()) &&
            (SDL_GetTicks() > timeToStopShowPercentage))
        {
            percentageBar->StopShowOnScreen();
        }

        if (currentAction == WAITING_USER_COMMAND) {
            if (SDL_GetTicks() > timeToResumeFilm) {
                currentAction = PLAYING_FILM;
                if (cursorBreakPointToGo >= 0) {

                    imagePlayer->GoToBreakPoint(
                        listOfBreakPoint[cursorBreakPointToGo]->GetCursorMe_Image());

                    soundPlayer->GoToBreakPoint(
                        listOfBreakPoint[cursorBreakPointToGo]->GetCursorMe_Sound());

                    deltaTime = SDL_GetTicks()
                                 - listOfBreakPoint[cursorBreakPointToGo]->GetActTime();

                    imagePlayer->SetDeltaTime(deltaTime);
                    soundPlayer->SetDeltaTime(deltaTime);
                }
                cursorBreakPointToGo = -1;
            } else {
                SDL_Delay(4);
            }
        }

        while (SDL_PollEvent (&event)) {
            if (event.type == SDL_KEYDOWN) {
                if(event.key.state==SDL_PRESSED) {
                    switch (event.key.keysym.sym) {

                        case SDLK_ESCAPE :
                            quit = 1;
                            cout << "Fin de la projection." << endl;
                            imagePlayer->WriteStatistics();
                        break;

                        case SDLK_p :
                            if (currentAction == PLAYING_FILM) {
                                timeOfFilmBeforePause = SDL_GetTicks() - deltaTime;
                                currentAction = PAUSED;
                            } else {
                                deltaTime = SDL_GetTicks() - timeOfFilmBeforePause;
                                imagePlayer->SetDeltaTime(deltaTime);
                                soundPlayer->SetDeltaTime(deltaTime);
                                currentAction = PLAYING_FILM;
                            }
                        break;

                        case SDLK_UP :
                        case SDLK_PAGEUP :
                            if ((cursorBreakPointToGo >= 0) ||
                                (!TimeOfFilmIsBeforeFirstBreakPoint()))
                            {
                                timeToResumeFilm = SDL_GetTicks() + 500;
                                if (event.key.keysym.sym == SDLK_PAGEUP) {
                                    CursorBreakPointGoBack(0);
                                } else {
                                    CursorBreakPointGoBack(1);
                                }
                                currentAction = WAITING_USER_COMMAND;
                                percentageBar->RefreshValueAndShowOnScreen(
                                          listOfBreakPoint[cursorBreakPointToGo]->GetActTime(),
                                          totalTimeOfFilm
                                      );
                                timeToStopShowPercentage = SDL_GetTicks() + 500;
                            }
                        break;

//OUAAAAAAAAAAAAAIIIIIIIIIIIISSSS!!!! Quand on met quelque chose sur Internet, il est
//à disposition du monde entier! C'est trop bien! Les créations générés par notre cerveau
//circulent à travers toute la planète, et chaque personne peut la regarder, l'écouter,
//l'apprécier. Ce sont des morceaux de toi-même qui voyagent dans l'immensité du cyberespace
//pour arriver à portée de main de tout un chacun.
//
//Oh oui! Comment c'est trop bien!!
//
//Sauf que tout ceci est complètement FAUX!!!! Ca n'est pas du tout mis à la disposition
//du monde entier. Les clochards, les africains, les vieux grabataires et les ouvriers chinois
//n'en ont strictement rien à foutre d'Internet. Tout ce dont ils ont besoin c'est de la
//bouffe et un peu de vie dans leur vie.
//
//Alors arrêtez de nous bassiner comme le monde sera beau grâce à Internet. Il n'en rend
//beau qu'une petite partie.
//Bon et on fait quoi pour le reste alors?


                        case SDLK_DOWN :
                        case SDLK_PAGEDOWN :
                            if ((cursorBreakPointToGo >= 0) ||
                                (!TimeOfFilmIsAfterLastBreakPoint()))
                            {
                                timeToResumeFilm = SDL_GetTicks() + 500;
                                if (event.key.keysym.sym == SDLK_PAGEDOWN) {
                                    CursorBreakPointGoAhead(0);
                                } else {
                                    CursorBreakPointGoAhead(1);
                                }
                                currentAction = WAITING_USER_COMMAND;
                                percentageBar->RefreshValueAndShowOnScreen(
                                          listOfBreakPoint[cursorBreakPointToGo]->GetActTime(),
                                          totalTimeOfFilm
                                      );
                                timeToStopShowPercentage = SDL_GetTicks() + 500;
                            }
                        break;

                        case SDLK_F1 :
                            SDL_SaveBMP(mainScreen,"screenshot.bmp");
                        break;

                        int currentVolume;

                        case SDLK_KP_MINUS :
                            currentVolume = soundPlayer->SetVolumeRelative(-5);
                            percentageBar->RefreshValueAndShowOnScreen(currentVolume, 100);
                            timeToStopShowPercentage = SDL_GetTicks() + 500;
                        break;

                        case SDLK_KP_PLUS :
                            currentVolume = soundPlayer->SetVolumeRelative(+5);
                            percentageBar->RefreshValueAndShowOnScreen(currentVolume, 100);
                            timeToStopShowPercentage = SDL_GetTicks() + 500;
                        break;

                        case SDLK_KP0 :
                            currentVolume = soundPlayer->ToggleMute();
                            percentageBar->RefreshValueAndShowOnScreen(currentVolume, 100);
                            timeToStopShowPercentage = SDL_GetTicks() + 500;
                        break;

                    }
                }
            }
        }

    }
}
