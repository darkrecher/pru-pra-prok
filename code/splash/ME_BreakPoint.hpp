#ifndef MOVIE_EVENT_BREAKPOINT_INCLUDED_PAYE_TA_CHATTE__
#define MOVIE_EVENT_BREAKPOINT_INCLUDED_PAYE_TA_CHATTE__


#include "MovieEvent.hpp"


class ME_BreakPoint : public MovieEvent
{

    private :

        long int cursorME_Image;
        long int cursorME_Sound;
        int breakPointLevel;

//vide dans ma t�te, pas de cr�ation pour l'instant.
//Tout est calme sur le rebord sulfureux int�rieur vert de ma folie.
//J'ach�te l'attention des gens et la revend � des publicitaires,
//j'oublie mon esprit dans la beaut� tentaculaire d'un building de verre.
//La tension du fil, funambule, sur la ville, tout en haut,
//il fait pas si froid, regarde en bas.
//
//L'oeil int�rieur est tomb� dans l'estomac. Goinfre de la mort, mon costard est mon armure.
//Fossoyeur des bosses et des creux, je rouleaucompresse au ciment rose,
//avec des petits coeurs rouges. De l'amour � la cha�ne dans les �lectrons
//sur la paroi de verre sur le plateau du pra�me sur le gel de Benji
//sur les candidat stress�s sur la voiture trois-pi�ces � gagner un voyage en mozambie,
//yo ho ho! yo ho ho!

	public:

        ME_BreakPoint(long int _actTime, int _breakPointLevel,
                      long int _cursorME_Image = 0, long int _cursorME_Sound = 0);

		~ME_BreakPoint();

		void Act();
		MovieEvent *Copy(long int timeToAdd);
		long int GetActTime();

		void SetCursors(long int _cursorME_Image, long int _cursorME_Sound);
		long int GetCursorMe_Image();
		long int GetCursorMe_Sound();
		int GetLevel();

};


#endif
