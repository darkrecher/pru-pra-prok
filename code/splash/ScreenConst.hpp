#ifndef SCREEN_CONST_INCLUDED__



const int SCREEN_SIZE_X = 640;
const int SCREEN_SIZE_Y = 480;
const int SCREEN_INDEX_X = SCREEN_SIZE_X-1;
const int SCREEN_INDEX_Y = SCREEN_SIZE_Y-1;
const int SCREEN_MIDDLE_X = SCREEN_SIZE_X/2 - 1;
const int SCREEN_MIDDLE_Y = SCREEN_SIZE_Y/2 - 1;



#define SCREEN_CONST_INCLUDED__

#endif


/*

Le truc du #ifndef SCREEN_CONST, suivi du #define et du #endif,
c'est pour �viter d'avoir une erreur si jamais on a besoin d'inclure ce fichier
� plusieurs endroits du projet. (Car le compilateur se met � vouloir recr�er
les constantes alors qu'elles sont d�j� faites, et il fait une erreur).

Par contre, je sais pas du tout si c'est la bonne m�thode. Peut �tre que des pros de
la programmation crieront au blasph�me en voyant �a, eh bien je les emmerde.

pragma once, o� es tu?

*/
