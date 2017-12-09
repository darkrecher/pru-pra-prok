//345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345
//      10        20        30        40        50        60        70        80        90
//
//ici, on voit une ligne de 95 caractères. j'essaye de faire en sorte que mes lignes de code
//et mes lignes de commentaires ne dépassent jamais cette longueur. (Si jamais j'ai une ligne
//de code trop longue, je la coupe en morceaux, tout simplement). Ca permet de ne pas avoir à
//se faire chier à scroller horizontalement.
//Donc pour pouvoir bien consulter ce code, ça serait bien de fixer la taille de la fenêtre
//de façon à voir pile la ligne de chiffres ci dessus. Pas plus, pas moins.
//
//Si vous me prenez pour un fou et que vous trouvez ça complètement absurde, libre à vous
//d'aller vous pendre.


//Je rappelle aux égarés qui lisent ce code qu'il est sous licence Art Libre. (vous
//trouverez une copie de cette licence sur http://www.artlibre.org). MAis que si ça vous
//intéresse, vous pouvez tout prendre et le mettre sous licence GNU (à la condition de
//bien préciser que ça vient de moi au départ). Eh oui, j'assume mon code source!!
//Enfin j'essaye.


#include <stdlib.h>
#include <iostream>
#include "MoviePlayer.hpp"
#include "ConfigXMLParser.hpp"

using namespace std;


const int ERROR_WHATEVER = 1;
const int ERROR_NO_ARGUMENT = 2;

void ShowErrorOnScreen(SDL_Surface *mainScreen, int errorType = ERROR_WHATEVER)
{
    if (mainScreen == NULL) {
        mainScreen = SDL_SetVideoMode (640, 480, 32, SDL_SWSURFACE);
    }
    if (mainScreen == NULL) {
        cerr << endl << "De plus, il est impossible d'initialiser le mode vidéo." << endl;
        return;
    }

    SDL_FillRect(mainScreen, NULL, 0);
    FILE *file;
    SDL_RWops *rw;
    SDL_Surface *errorImage = NULL;
    file = fopen("basicimg.zob", "rb");
    if (file) {
        rw = SDL_RWFromFP(file, 0);
        errorImage = IMG_LoadPNG_RW(rw);
        SDL_FreeRW(rw);
    }

    if (errorImage != NULL) {
        SDL_Rect source;
        if (errorType == ERROR_NO_ARGUMENT) {
            SetRect(&source, 0, 143, 230, 94);
        } else {
            SetRect(&source, 0, 0, 448, 143);
        }
        SDL_BlitSurface(errorImage, &source, mainScreen, NULL);
        SDL_FreeSurface(errorImage);
    } else {
        cerr << endl << "De plus, il manque le fichier basicimg.zob" << endl;
        Uint32 Red = SDL_MapRGB(mainScreen->format, 255, 0, 0);
        SDL_Rect rect;
        SetRect(&rect, 305, 50, 30, 280);
        SDL_FillRect(mainScreen, &rect, Red);
        SetRect(&rect, 305, 400, 30, 30);
        SDL_FillRect(mainScreen, &rect, Red);
    }
    SDL_Flip(mainScreen);

    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent (&event)) {
            if (event.type == SDL_KEYDOWN) { quit = 1; }
        }
    }
}

int main(int argc, char *argv[])
{

    ConfigXMLParser configXMLParser(0);
    SDL_Surface *mainScreen = NULL;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0) {
        cerr << "Impossible d'initialiser la SDL : " << SDL_GetError() << endl;
        exit (1);
    }

    atexit(SDL_Quit);

    string parsingErrorMessage = configXMLParser.OpenConfigXMLFile((char *)"config.txt");
    if (parsingErrorMessage == "") {
        parsingErrorMessage = configXMLParser.ReadConfigXMLFile();
    }
    if (parsingErrorMessage != "") {
        cerr << parsingErrorMessage << endl;
        ShowErrorOnScreen(mainScreen, ERROR_WHATEVER);
        exit(2);
    }

    cout << "La lecture de la configuration a été correctement effectuée." << endl;
    ConfigInfos *theConfigInfos = configXMLParser.GetConfigInfos();

    //ça c'est juste pour montrer la config dans le fichier de sortie. On s'en fout.
   // cout << theConfigInfos->GetConfigDescription() << endl;

    mainScreen = SDL_SetVideoMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32,
                                  theConfigInfos->GetSurfaceTypeOfMainScreen()
                                     | theConfigInfos->GetFullScreen()
                                  );
    if (mainScreen == NULL) {
        cerr << "Impossible d'initialiser le mode vidéo." << endl;
        exit (3);
    }
    theConfigInfos->SetKeyTransparencyColor32BitValue(mainScreen->format);
    configXMLParser.CloseConfigXMLFile();
    SDL_ShowCursor(SDL_DISABLE);

    if (argc < 2) {
        cerr << "Pour voir la première partie du film, exécutez \"prupraprok1.bat\"" << endl;
        cerr << "Pour voir la deuxième partie, exécutez \"prupraprok2.bat\"" << endl;
        cerr << "Vous pouvez aussi utilisez les lignes de commandes suivantes : " << endl;
        cerr << "  splash.exe film1.zob" << endl;
        cerr << "  splash.exe film2.zob" << endl;
        ShowErrorOnScreen(mainScreen, ERROR_NO_ARGUMENT);
        return 1;
    }

    MoviePlayer moviePlayer = MoviePlayer(mainScreen, theConfigInfos);
    if (!moviePlayer.LoadData(argv[1])) {
        ShowErrorOnScreen(mainScreen, ERROR_WHATEVER);
        exit(4);
    }

    moviePlayer.Play();

    cout << "Fin du programme. Date : " << SDL_GetTicks() << endl;
    return 0;
}

//Alors comme ça vous voulez regarder mon code source?
//Savoir comment j'ai fait. Qu'est-ce qu'il y a l'intérieur. Peut être même en reprendre
//des bouts, ou le recompiler pour un autre système d'exploitation!!! Hahaha!!!
//Inconscients que vous êtes. Mon code est crade et moche. Y'a pas de commentaires
//d'explication, et encore moins de document annexe. Débrouillez-vous.
//Par contre, bien qu'il n'y ait pas de commentaires explicatifs, il y a des tas de
//commentaires débiles. Je vous laisse les découvrir au gré des fichiers.
