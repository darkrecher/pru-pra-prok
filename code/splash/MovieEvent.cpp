#include "MovieEvent.hpp"



MovieEvent::MovieEvent(long int _actTime) { actTime = _actTime; }

MovieEvent::~MovieEvent() {};
    
long int MovieEvent::GetActTime() { return actTime; }

//gn���hh���h����!! Les aventures de mini-bout-de-code.
//
//C'est l'histoire d'un tout petit fichier de code de rien du tout, qui r�ve d'�tre
//un gigantesque fichier pleins d'algorithme et de trucs complexe.
//Et � ce moment l�, y'a madame Modularit� et madame Keep-It-Simple-Stupid qui lui disent :
//"Mais non petit fichier de code, tu dois rester tel que tu es, sinon l'ensemble du
//projet va �tre super bordelique, d�j� que dans la situation actuelle, on n'arrive pas
//� retrouver o� sont les fonctions et � quoi elles servent car rien n'est document�...
//Alors soit fier, petit fichier de code, car tu es la d�finition d'une classe tr�s g�n�rique,
//et sans toi, les diff�rentes parties du projet ne sauraient pas se parler entre elles.
//Et surtout, reste simple et accessible, n'essaie pas de grandir."
//
//Alors le petit fichier de code s'en retourne dans le r�pertoire du projet, tout heureux
//de sa condition et de sons statut.
//Ensuite, il va retrouver sa fianc�e, qui s'appelle MovieEvent.hpp, et qui est la d�claration
//de la classe. Et ils se mari�rent et eurent beaucoup de petits bugs.
