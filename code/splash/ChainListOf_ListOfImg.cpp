#include "ChainListOf_ListOfImg.hpp"



ChainListOf_ListOfImg::ChainListOf_ListOfImg()
{
    first = NULL;
    cursor = NULL;
}


ChainListOf_ListOfImg::~ChainListOf_ListOfImg()
{
    EltListOfImg *p1 = first;
    EltListOfImg *p2 = first;
    while (p1 != NULL) {
        p2 = p2->next;
        delete p1;
        p1 = p2;
    }
}


void ChainListOf_ListOfImg::AddElement(ListOfImg *_theListOfImg, string *_listOfImgNames,
                                       string _name)
{

    EltListOfImg *p = first;
    EltListOfImg *newElt = new EltListOfImg;
    newElt->name = _name;
    newElt->theListOfImg = _theListOfImg;
    newElt->listOfImgNames = _listOfImgNames;
    newElt->next = NULL;
    if (p == NULL) {
        first = newElt;
    } else {
        while (p->next!=NULL) { p=p->next; }
        p->next = newElt;
    }
}


int ChainListOf_ListOfImg::SetCursor(string eltName)
{
    cursor = first;
    while ((cursor != NULL) && (cursor->name != eltName)) {
        cursor = cursor->next;
    }
    if (cursor != NULL) { return 1; }
    return 0;
}

//Réponse de l'ingénieur :
//Merci pour vos explications mais elles étaient inutiles. Nous savons cela depuis longtemps
//Que croyez-vous qu'on m'ait appris durant mes années d'études?
//Cours de rédaction de CV, exercices d'entretiens d'embauches, comment associer les couleurs
//de sa cravate avec son teint de peau et son sourire, etc... et surtout beaucoup de leçons
//de léchage de cul. Le tout avec un habile conditionnement mental, qui me laisse croire
//que si je travaille et lèche comme un dingue, un jour, ce sera moi qui sera chef, et ma vie
//en deviendra hautement plus intéressante. Ce dont je suis persuadé, c'est qu'une carrière
//professionnelle, c'est quelque chose qui vaut vraiment le coup, on peut y consacrer sa vie.
//Je suis donc votre homme pour tout ce dont vous avez besoin. Ma langue est prête.
//Vos fesses-le-sont-elles?


ListOfImg *ChainListOf_ListOfImg::GetCurrentListOfImg()
{
    if (cursor != NULL) { return cursor->theListOfImg; }
    return NULL;
}


string *ChainListOf_ListOfImg::GetCurrentListOfImgNames()
{
    if (cursor != NULL) { return cursor->listOfImgNames; }
    return NULL;
}


long int ChainListOf_ListOfImg::GetQtyOfElement()
{
    long int qty = 0;
    EltListOfImg *p = first;
    while (p!=NULL) {
        p = p->next;
        qty++;
    }
    return qty;
}


void ChainListOf_ListOfImg::FreeAllImages()
{
    EltListOfImg *p = first;

    long int i;
    while (p!=NULL) {
        for (i=0 ; i < p->theListOfImg->GetImgQty() ; i++) {
            delete (p->theListOfImg->GetImageZoomable(i));
        }
        delete p->theListOfImg;
        p = p->next;
    }
}
