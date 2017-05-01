#include "ListOfImg.hpp"
#include <string>



class ChainListOfImg
{

    private:

        typedef struct EltImgZoomable {
            string name;
            ImageZoomable *theImageZoomable;
            EltImgZoomable *next;
        };

        EltImgZoomable *first;

//  haïkus. série numéro 6
//
//
//Au début de ta vie,
//tu n'es pas un, mais deux.
//Ovule, spermatozoide
//
//
//Une calvitie, c'est
//moins de cheveux à peigner
//mais plus de figure à laver
//
//
//(le nombre de syllabe n'est pas respecté, mais je m'en branle)

	public:

		ChainListOfImg();
		~ChainListOfImg();

		void AddElement(ImageZoomable *_imageZoomable, string _name);
		ImageZoomable *GetElement(string eltName);  //peut être inutile
		long int GetQtyOfElement();
		void ExtractListOfImg(ListOfImg *listOfImgToFill, string *listOfImgNamesToFill);

};
