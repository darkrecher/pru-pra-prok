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
c'est pour éviter d'avoir une erreur si jamais on a besoin d'inclure ce fichier
à plusieurs endroits du projet. (Car le compilateur se met à vouloir recréer
les constantes alors qu'elles sont déjà faites, et il fait une erreur).

Par contre, je sais pas du tout si c'est la bonne méthode. Peut être que des pros de
la programmation crieront au blasphème en voyant ça, eh bien je les emmerde.

pragma once, où es tu?

*/
