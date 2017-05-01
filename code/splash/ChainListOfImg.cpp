#include "ChainListOfImg.hpp"



ChainListOfImg::ChainListOfImg()
{
    first = NULL;
}


ChainListOfImg::~ChainListOfImg()
{
    EltImgZoomable *p1 = first;
    EltImgZoomable *p2 = first;
    while (p1 != NULL) {
        p2 = p2->next;
        delete p1;
        p1 = p2;
    }
}


void ChainListOfImg::AddElement(ImageZoomable *_imageZoomable, string _name)
{
    EltImgZoomable *p = first;
    EltImgZoomable *newElt = new EltImgZoomable;
    newElt->name = _name;
    newElt->theImageZoomable = _imageZoomable;
    newElt->next = NULL;
    if (p == NULL) {
        first = newElt;
    } else {
        while (p->next!=NULL) { p=p->next; }
        p->next = newElt;
    }
}


ImageZoomable *ChainListOfImg::GetElement(string eltName)
{
    EltImgZoomable *p = first;
    while ((p!=NULL) && (p->name!=eltName)) { p=p->next; }
    if (p != NULL) { return p->theImageZoomable; }
    return NULL;
}


long int ChainListOfImg::GetQtyOfElement()
{
    long int qty = 0;
    EltImgZoomable *p = first;
    while (p!=NULL) {
        p = p->next;
        qty++;
    }
    return qty;
}

//A l'heure actuelle, dans notre pays, on a des tas de moyens d'acc�der � de l'art ou de
//se distraire. Nous avons la t�loche, avec son cort�ge d'�missions intelligentes ou d�biles,
//des livres et des bandes dessin�es, le th��tre, certains jeux vid�os, la musique qui vient
//� nous sous des formes diverses, etc...
//C'est tr�s bien tout cela. Il faut en profiter, d'autant plus que c'est facile d'acc�s et
//�a ne coute pas forc�ment tr�s cher. Mais, est-ce que �a n'est pas un peu trop pour une
//seule petite vie? En s"int�ressant � trop de choses, on n'a plus le temps d'en fabriquer
//soi-m�me. Quand on veut imaginer et raconter des histoires, il faut parfois s'isoler
//du reste du monde, s'enterrer chez soi pour �crire, dessiner, programmer, ou autre chose.
//
//D'un autre c�t�, si on s'isole trop, au bout d'un moment, on n'a plus d'id�es.
//Car les id�es s'attrappent en parlant aux gens, et en absorbant les notions
//qui volent autour de nous.
//
//Il faut alterner les deux actions. On s'enferme pour cr�er, puis on se rouvre et on
//alimente le cerveau, et on recommence. Ca fait un peu comme une respiration.
//
//Est-ce que vous laissez votre �me respirer?

void ChainListOfImg::ExtractListOfImg(ListOfImg *listOfImgToFill, string *listOfImgNamesToFill)
{
    EltImgZoomable *p = first;
    int index = 0;
    while (p!=NULL) {
        listOfImgToFill->SetImageZoomable(p->theImageZoomable, index);
        listOfImgNamesToFill[index] = p->name;
        index++;
        p = p->next;
    }
}
