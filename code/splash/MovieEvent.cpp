#include "MovieEvent.hpp"



MovieEvent::MovieEvent(long int _actTime) { actTime = _actTime; }

MovieEvent::~MovieEvent() {};
    
long int MovieEvent::GetActTime() { return actTime; }

//gnéééhhéééhéééé!! Les aventures de mini-bout-de-code.
//
//C'est l'histoire d'un tout petit fichier de code de rien du tout, qui rêve d'être
//un gigantesque fichier pleins d'algorithme et de trucs complexe.
//Et à ce moment là, y'a madame Modularité et madame Keep-It-Simple-Stupid qui lui disent :
//"Mais non petit fichier de code, tu dois rester tel que tu es, sinon l'ensemble du
//projet va être super bordelique, déjà que dans la situation actuelle, on n'arrive pas
//à retrouver où sont les fonctions et à quoi elles servent car rien n'est documenté...
//Alors soit fier, petit fichier de code, car tu es la définition d'une classe très générique,
//et sans toi, les différentes parties du projet ne sauraient pas se parler entre elles.
//Et surtout, reste simple et accessible, n'essaie pas de grandir."
//
//Alors le petit fichier de code s'en retourne dans le répertoire du projet, tout heureux
//de sa condition et de sons statut.
//Ensuite, il va retrouver sa fiancée, qui s'appelle MovieEvent.hpp, et qui est la déclaration
//de la classe. Et ils se marièrent et eurent beaucoup de petits bugs.
