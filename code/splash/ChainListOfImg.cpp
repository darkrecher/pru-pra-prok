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

//A l'heure actuelle, dans notre pays, on a des tas de moyens d'accéder à de l'art ou de
//se distraire. Nous avons la téloche, avec son cortège d'émissions intelligentes ou débiles,
//des livres et des bandes dessinées, le théâtre, certains jeux vidéos, la musique qui vient
//à nous sous des formes diverses, etc...
//C'est très bien tout cela. Il faut en profiter, d'autant plus que c'est facile d'accès et
//ça ne coute pas forcément très cher. Mais, est-ce que ça n'est pas un peu trop pour une
//seule petite vie? En s"intéressant à trop de choses, on n'a plus le temps d'en fabriquer
//soi-même. Quand on veut imaginer et raconter des histoires, il faut parfois s'isoler
//du reste du monde, s'enterrer chez soi pour écrire, dessiner, programmer, ou autre chose.
//
//D'un autre côté, si on s'isole trop, au bout d'un moment, on n'a plus d'idées.
//Car les idées s'attrappent en parlant aux gens, et en absorbant les notions
//qui volent autour de nous.
//
//Il faut alterner les deux actions. On s'enferme pour créer, puis on se rouvre et on
//alimente le cerveau, et on recommence. Ca fait un peu comme une respiration.
//
//Est-ce que vous laissez votre âme respirer?

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
