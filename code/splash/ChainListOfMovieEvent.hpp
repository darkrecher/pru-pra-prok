#ifndef CHAIN_LIST_OF_MOVIE_EVENT_INCLUDED_TA_CHATTE__


#include "ME_BreakPoint.hpp"
#include <string>

//pour tester
#include <iostream.h>

class ChainListOfMovieEvent
{

    private:

        typedef struct EltMovieEvent {
            int ME_type;
            MovieEvent *theMovieEvent;
            EltMovieEvent *next;
        };
    
        EltMovieEvent *first;


//Je me promène dans la rue et je croise un bébé :
//  [
//"gazou gazou, youpi. hihihi!!
//Oh, mais que se passe-t-il! Je viens de vieillir de 10 ans!
//Je suis maintenant un petit garçon. Argh! je viens encore de vieillir, mais de 20 ans.
//Je suis un adulte! AArrghhh, encore 50 ans de plus. Aaah! Je suis un vieillard!
//Non pas encore! Non! Ahh! Kblblblbl Blinm Blom."
//(tas d'ossement qui tombe)
//  ]
//
// (à suivre)

	public:
	
	    static const int ME_TYPE_IMAGE = 0;
	    static const int ME_TYPE_SOUND = 1;
	    static const int ME_TYPE_BREAKPOINT = 2;
	    static const int ME_TYPE_ALL = 3;

		ChainListOfMovieEvent();
		~ChainListOfMovieEvent();
		
		void AddElement(MovieEvent *_movieEvent, int _ME_type);
		MovieEvent *GetElement(long int index);  //sera inutile plus tard
		long int GetQtyOfElement(int ME_typeToCount);
		MovieEvent **ExtractListOfMovieEvent(int ME_typeToGet, long int *qtyExtracted);
		MovieEvent **ExtractAndDefineListOfBreakPoint(long int *qtyExtracted);
		
		void SortList();
		long int ConcatListOfMovieEvent(ChainListOfMovieEvent *chainListToAdd,
                                        long int timeToAdd,
                                        long int durationOfConcatenation = -1);

        void DeleteAllEvents();
//        void WriteListOfTimeForTest();

};


#define CHAIN_LIST_OF_MOVIE_EVENT_INCLUDED_TA_CHATTE__

#endif
