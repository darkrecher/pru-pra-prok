#include "ChainListOfProcedure.hpp"


ChainListOfProcedure::ChainListOfProcedure()
{
    first = NULL;
    cursor = NULL;
}


ChainListOfProcedure::~ChainListOfProcedure()
{
    EltProcedure *p1 = first;
    EltProcedure *p2 = first;
    while (p1 != NULL) {
        p2 = p2->next;
        delete p1;
        p1 = p2;
    }
}


void ChainListOfProcedure::AddElement(ChainListOfMovieEvent *chainListOfMovieEvent,
                                      string _name)
{
    EltProcedure *p = first;
    EltProcedure *newElt = new EltProcedure;
    newElt->name = _name;
    newElt->procedureListOfMovieEvent = chainListOfMovieEvent;
    newElt->next = NULL;
    if (p == NULL) {
        first = newElt;
    } else {
        while (p->next!=NULL) { p=p->next; }
        p->next = newElt;
    }
}


ChainListOfMovieEvent *ChainListOfProcedure::GetProcedureListOfMovieEvent(string eltName)
{
    EltProcedure *p = first;
    while ((p!=NULL) && (p->name!=eltName)) { p=p->next; }
    if (p != NULL) { return p->procedureListOfMovieEvent; }
    return NULL;
}


long int ChainListOfProcedure::GetQtyOfElement()
{
    long int qty = 0;
    EltProcedure *p = first;
    while (p!=NULL) {
        p = p->next;
        qty++;
    }
    return qty;
}

//  (suite)
//
//Je continue ma promenade et je croise une jolie petite fille.
//  [
//"Lalalala. Je vais aller cueillir des fleurs. J'aime les fleurs.
//Aaahh!! Mon ventre gonfle, je viens de grossir de 10 kilos.
//Aaahh, mes vêtements se craquent. Arr, 20 kilos de plus
//Au secours! Je commence à avoir des bourrelets. PPbbrfff!! 50 kilos en plus!
//Je peux plus avancer, je suis obèse! GGllrrgg!! Non pas encore. HHhhrrbbgg!!
//PLLORRFFGLBLEUAAARGGLL"
//(explosion de chair et de sang)
//  ]
//
//(à suivre)


void ChainListOfProcedure::deleteAllProcedures()
{
    EltProcedure *p = first;
    while (p!=NULL) {
        p->procedureListOfMovieEvent->DeleteAllEvents();
        delete p->procedureListOfMovieEvent;
        p = p->next;
    }
}
