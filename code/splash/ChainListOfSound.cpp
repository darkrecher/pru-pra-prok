#include "ChainListOfSound.hpp"



ChainListOfSound::ChainListOfSound()
{
    first = NULL;
}


ChainListOfSound::~ChainListOfSound()
{
    EltSound *p1 = first;
    EltSound *p2 = first;
    while (p1 != NULL) {
        p2 = p2->next;
        delete p1;
        p1 = p2;
    }
}


void ChainListOfSound::AddElement(Mix_Chunk *_Sound, string _name)
{
    EltSound *p = first;
    EltSound *newElt = new EltSound;
    newElt->name = _name;
    newElt->theSound = _Sound;
    newElt->next = NULL;
    if (p == NULL) {
        first = newElt;
    } else {
        while (p->next!=NULL) { p=p->next; }
        p->next = newElt;
    }
}


Mix_Chunk *ChainListOfSound::GetElement(string eltName)
{
    EltSound *p = first;
    while ((p!=NULL) && (p->name!=eltName)) { p=p->next; }
    if (p != NULL) { return p->theSound; }
    return NULL;
}

//Il semblerait qu'il ne soit pas possible de terminer 2 fois de suite
//le jeu "Gods" des Bitmap Brothers
//En le terminant une première fois, on recommence, et c'est plus dur.
//Et quand on arrive la deuxième fois au boss de fin, il a l'air invincible.
//Est-ce que quelqu'un l'a fini entièrement 2 fois de suite (ou plus)?
//Envoyez un mail si vous avez des infos à ce propos. Merci!!

long int ChainListOfSound::GetQtyOfElement()
{
    long int qty = 0;
    EltSound *p = first;
    while (p!=NULL) { 
        p = p->next; 
        qty++;
    }
    return qty;
}


void ChainListOfSound::FreeAllSound()
{
    EltSound *p = first;
    while (p!=NULL) {
        Mix_FreeChunk(p->theSound);
        p = p->next;
    }
}
