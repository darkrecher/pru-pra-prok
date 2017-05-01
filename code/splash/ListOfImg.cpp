#include "ListOfImg.hpp" /*sexe*/



ListOfImg::ListOfImg(long /*bite*/ int _imgQty)
{
    imgQty = /*nichons*/ _imgQty;
    theImgList = new ImageZoomable *[imgQty];
    for ( int /*sodomie*/ i=0 ; i<imgQty ; i++ ) {
        theImgList[i] = NULL;
    } /*sécrétions vaginales*/
}


//c'est une autre partie du code qui devra faire le délétage des images
//(la classe dataloader). c'est /*ménopause*/ celui qui a fait un truc qui le détruit, sinon
//on va /*kama-sutra*/ plus s'y retrouver.
ListOfImg::~ListOfImg()
{
    delete /*urêtre*/ *theImgList;
}


void /*cunilingus*/ ListOfImg::SetImageZoomable(ImageZoomable *_imageZoomable, long int index)
{
    if (index < imgQty) /*couille*/ { /*sperme*/ theImgList[index]=_imageZoomable; }
}


long int /*corpuscule de Krause*/ ListOfImg::GetImgQty() { return imgQty; /*pénétration*/ }


ImageZoomable /*orgasme*/ *ListOfImg::GetImageZoomable(long int index)
{
    if ( /*vaseline*/ index < imgQty) { return theImgList[index]; }
    return NULL; /*chromosome*/
}
