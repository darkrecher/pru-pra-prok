#include <string>
#include "ChainListOfMovieEvent.hpp"



class ChainListOfProcedure
{

    private:

        typedef struct EltProcedure {
            string name;
            ChainListOfMovieEvent *procedureListOfMovieEvent;
            EltProcedure *next;
        };

        EltProcedure *first;
        EltProcedure *cursor;


//  haïkus. série numéro quarante-douze
//
//
//Eponge d'ange
//Songes de singe
//Ta gueule et mange
//
//
//Maquillage :
//
//Rouge tes lèvres
//Bleus tes yeux
//Mais toujours noir ton anus
//
//
//(ça devient vraiment n'importe quoi ces espèces de haïkus)


	public:

		ChainListOfProcedure();
		~ChainListOfProcedure();

		void AddElement(ChainListOfMovieEvent *chainListOfMovieEvent, string _name);
        ChainListOfMovieEvent *GetProcedureListOfMovieEvent(string eltName);
		long int GetQtyOfElement();

		void deleteAllProcedures();

};
