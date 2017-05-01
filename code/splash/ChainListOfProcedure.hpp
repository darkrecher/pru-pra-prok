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


//  ha�kus. s�rie num�ro quarante-douze
//
//
//Eponge d'ange
//Songes de singe
//Ta gueule et mange
//
//
//Maquillage :
//
//Rouge tes l�vres
//Bleus tes yeux
//Mais toujours noir ton anus
//
//
//(�a devient vraiment n'importe quoi ces esp�ces de ha�kus)


	public:

		ChainListOfProcedure();
		~ChainListOfProcedure();

		void AddElement(ChainListOfMovieEvent *chainListOfMovieEvent, string _name);
        ChainListOfMovieEvent *GetProcedureListOfMovieEvent(string eltName);
		long int GetQtyOfElement();

		void deleteAllProcedures();

};
