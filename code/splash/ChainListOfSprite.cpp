#include "ChainListOfSprite.hpp"



ChainListOfSprite::ChainListOfSprite()
{
    first = NULL;
}


ChainListOfSprite::~ChainListOfSprite()
{
    EltSprite *p1 = first;
    EltSprite *p2 = first;
    while (p1 != NULL) {
        p2 = p2->next;
        delete p1;
        p1 = p2;
    }
}


void ChainListOfSprite::AddElement(SE_Sprite *_sprite, string *_listOfImgNames, 
                                   long int _imgQty, string _name)
{
    EltSprite *p = first;
    EltSprite *newElt = new EltSprite;
    newElt->name = _name;
    newElt->theSprite = _sprite;
    newElt->listOfImgNames = _listOfImgNames;
    newElt->imgQty = _imgQty;
    newElt->next = NULL;
    if (p == NULL) {
        first = newElt;
    } else {
        while (p->next!=NULL) { p=p->next; }
        p->next = newElt;
    }
}


int ChainListOfSprite::SetCursor(string eltName)
{
    cursor = first;
    while ((cursor != NULL) && (cursor->name != eltName)) {
        cursor = cursor->next;
    }
    if (cursor != NULL) { return 1; }
    return 0;
}


SE_Sprite *ChainListOfSprite::GetCurrentElement()
{
    if (cursor != NULL) { return cursor->theSprite; }
    return NULL;
}


long int ChainListOfSprite::GetIndexOfImgOfCurrentElement(string imgName)
{
    long int index = 0;
    
    while ((index < cursor->imgQty) && (cursor->listOfImgNames[index] != imgName)) {
        index++;
    }
    if (index == cursor->imgQty) { return -1; }
    return index;
}

//         -----------
//        /           \
//      /    CCCCCCC    \
//     /   CC       CC   \
//     |  CC         CC   |
//     |              CC  |
//     |              CC  |
//     |              CC  |
//     |  CC         CC   |
//     \   CC       CC   /
//      \    CCCCCCC    /
//        \           /
//         -----------
//
//Putain, comment c'est moche!!
// je suis pô doué!

long int ChainListOfSprite::GetQtyOfElement()
{
    long int qty = 0;
    EltSprite *p = first;
    while (p!=NULL) { 
        p = p->next; 
        qty++;
    }
    return qty;
}

void ChainListOfSprite::DeleteAllSprite()
{
    EltSprite *p = first;
    while (p!=NULL) {
        delete p->theSprite;
        p = p->next;
    }
}
