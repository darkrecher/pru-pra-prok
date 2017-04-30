#include "ChainListOfSDLSurface.hpp"



ChainListOfSDLSurface::ChainListOfSDLSurface()
{
    first = NULL;
}


ChainListOfSDLSurface::~ChainListOfSDLSurface()
{
    EltSDL_Surface *p1 = first;
    EltSDL_Surface *p2 = first;
    while (p1 != NULL) {
        p2 = p2->next;
        delete p1;
        p1 = p2;
    }
}


void ChainListOfSDLSurface::AddElement(SDL_Surface *_SDL_Surface, string _name)
{
    EltSDL_Surface *p = first;
    EltSDL_Surface *newElt = new EltSDL_Surface;
    newElt->name = _name;
    newElt->theSDL_Surface = _SDL_Surface;
    newElt->next = NULL;
    if (p == NULL) {
        first = newElt;
    } else {
        while (p->next!=NULL) { p=p->next; }
        p->next = newElt;
    }
}


SDL_Surface *ChainListOfSDLSurface::GetElement(string eltName)
{
    EltSDL_Surface *p = first;
    while ((p!=NULL) && (p->name!=eltName)) { p=p->next; }
    if (p != NULL) { return p->theSDL_Surface; }
    return NULL;
}

//  (suite et fin)
//
//Je continue ma promenade et je croise un type quelconque
//  [
//"Pom popom popom. J'ai fini ma journée de boulot et je rentre chez moi retrouver
//ma jolie petite femme. Popom popom.
//Mais que se passe-t-il, j'ai l'impression que ma peau commence à bronzer instantanément,
//Pourtant le temps est nuageux. AAAAIIIEEE J'ai un gros coup de soleil.
//AAAHH Je suis brulé au troisième degré!! AAHHRR FFRRSSSCCHHHHHHHHHH!!
//(combustion spontanéééééééééééé!!!)
//  ]
//
//Je continue ma promenade dans la rue et il n'y a plus de rue et il n'y a plus de ville
//et il n'y a plus de Terre. Il n'y a plus que moi. Flottant dans l'air.
//
//Je me coupe la langue avec mes dents et je m'étouffe dans mon propre sang.


int ChainListOfSDLSurface::FreeElement(string eltName)
{
    EltSDL_Surface *p = first;
    while ((p!=NULL) && (p->name!=eltName)) { p=p->next; }
    if (p != NULL) {
        if (p->theSDL_Surface == NULL) { return 0; }
        SDL_FreeSurface(p->theSDL_Surface);
        p->theSDL_Surface = NULL;
        return 1;
    }
    return 0;
}

long int ChainListOfSDLSurface::GetQtyOfElement()  //peut-être inutile
{
    long int qty = 0;
    EltSDL_Surface *p = first;
    while (p!=NULL) { 
        p = p->next; 
        qty++;
    }
    return qty;
}

void ChainListOfSDLSurface::FreeAllSurfaces()
{
    EltSDL_Surface *p = first;
    while (p!=NULL) {
        if (p->theSDL_Surface != NULL) { SDL_FreeSurface(p->theSDL_Surface); }
        p = p->next;
    }
}
