#ifndef LIST_OF_IMAGE_INCLUDED__


#include "ImageZoomable.hpp"
#include <string>


class ListOfImg
{


private:

    ImageZoomable **theImgList;
    long int imgQty;


public:


//Note pour plus tard : les banderolles kronenbourg, c'est vachement utile comme couverture
//dans des concerts où on s'endort tout saoul.

    ListOfImg(long int _imgQty);
    ~ListOfImg();

    long int GetImgQty();

    void SetImageZoomable(ImageZoomable *_imageZoomable, long int index);

    //à changer de nom, car il est moche.
    ImageZoomable *GetImageZoomable(long int index);

};


#define LIST_OF_IMAGE_INCLUDED__


#endif
