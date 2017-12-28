# Notes en vrac de la reconstruction du projet


## Recherche des librairies

### SDL, SDL\_image, SDL\_mixer

https://www.libsdl.org/download-1.2.php

https://www.libsdl.org/release/SDL-devel-1.2.15-mingw32.tar.gz

Ça peut s'extraire avec 7-zip.

https://www.libsdl.org/projects/SDL_image/release-1.2.html
(attention, la page est moche, on a l'impression que y'a pas de CSS)

https://www.libsdl.org/projects/SDL_image/release/SDL_image-devel-1.2.12-VC.zip

SDL_image-devel-1.2.12-VC.zip

https://www.libsdl.org/projects/SDL_mixer/release-1.2.html
(moche aussi)

https://www.libsdl.org/projects/SDL_mixer/release/SDL_mixer-devel-1.2.12-VC.zip

SDL_mixer-devel-1.2.12-VC.zip

### gzip

www.gzip.org/zlib/ ou http://www.zlib.net/

zlib source code, version 1.2.11, zipfile format (730K, SHA-256 hash d7510a8ee1918b7d0cad197a089c0a2cd4d6df05fee22389f67f115e738b178d):
http://www.zlib.net/zlib1211.zip

(Non c'est pas ça)

http://www.winimage.com/zLibDll/
http://www.winimage.com/zLibDll/zlib123dll.zip

(non plus)

http://xmlsoft.org/sources/win32/
zlib-1.2.3.win32.zip


## Recompilation de splash.exe

(le truc entre iostream et iostream.h)

http://stackoverflow.com/questions/214230/iostream-vs-iostream-h-vs-iostream-h

http://stackoverflow.com/questions/5642367/extra-qualification-error-in-c

http://stackoverflow.com/questions/15194395/c-errors-string-does-not-name-a-type#35731684

http://stackoverflow.com/questions/2545720/error-default-argument-given-for-parameter-1

    ChainListOfImg.hpp
    // http://stackoverflow.com/questions/15194395/c-errors-string-does-not-name-a-type#35731684
    // Euh... ouais bof. C'est quand même bizarre de mettre ça juste une fois ici, et que ça fasse marcher tout le reste.
    using namespace std;

Ouais bon, ça fait pas marcher tout le reste.
Mais est-ce qu'il faut le mettre partout comme un taré ? Pas sûr que ce soit une bonne pratique.

http://stackoverflow.com/questions/2545720/error-default-argument-given-for-parameter-1

    ... pru-pra-prok\code\splash>mingw32-make.exe
    g++.exe -c FileLoader.cpp -o FileLoader.o -I"../libs_includes/SDL-devel-1.2.15-mingw32/SDL-1.2.15/include/SDL" -I"../libs_includes/SDL_image-devel-1.2.12-VC/SDL_image-1.2.12/include" -I"../libs_includes/SDL_mixer-devel-1.2.12-VC/SDL_mixer-1.2.12/include" -I"../libs_includes/zlib-1.2.3.win32/include"
    In file included from FileLoader.hpp:2:0,
                     from FileLoader.cpp:1:
    ChainListOfSDLSurface.hpp:12:7: warning: 'typedef' was ignored in this declaration
           typedef struct EltSDL_Surface {
           ^~~~~~~
    In file included from FileLoader.hpp:3:0,
                     from FileLoader.cpp:1:
    ChainListOfSound.hpp:12:9: warning: 'typedef' was ignored in this declaration
             typedef struct EltSound {
             ^~~~~~~
    In file included from FileLoader.hpp:4:0,
                     from FileLoader.cpp:1:
    XMLParser.hpp:19:9: warning: 'typedef' was ignored in this declaration
             typedef struct Baliz {
             ^~~~~~~

    ... pru-pra-prok\code\splash>mingw32-make.exe
    g++.exe -c main.cpp -o main.o -I"../libs_includes/SDL-devel-1.2.15-mingw32/SDL-1.2.15/include/SDL" -I"../libs_includes/SDL_image-devel-1.2.12-VC/SDL_image-1.2.12/include" -I"../libs_includes/SDL_mixer-devel-1.2.12-VC/SDL_mixer-1.2.12/include" -I"../libs_includes/zlib-1.2.3.win32/include"
    main.cpp: In function 'int SDL_main(int, char**)':
    main.cpp:96:80: warning: ISO C++ forbids converting a string constant to 'char*' [-Wwrite-strings]
         string parsingErrorMessage = configXMLParser.OpenConfigXMLFile("config.txt");


## Recompilation des utilitaires

https://stackoverflow.com/questions/1524356/c-deprecated-conversion-from-string-constant-to-char                                  ^

https://stackoverflow.com/questions/6255339/checking-if-a-file-opened-successfully-with-ifstream

https://stackoverflow.com/questions/15266448/reading-text-from-file-to-unsigned-char-array-errors-while-trying-to-use-exampl#15266489

https://stackoverflow.com/questions/12996862/invalid-conversion-from-const-char-to-stdbasic-ostreamcharchar-type-a



