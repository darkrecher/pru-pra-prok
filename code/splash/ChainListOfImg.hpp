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

//  ha�kus. s�rie num�ro 6
//
//
//Au d�but de ta vie,
//tu n'es pas un, mais deux.
//Ovule, spermatozoide
//
//
//Une calvitie, c'est
//moins de cheveux � peigner
//mais plus de figure � laver
//
//
//(le nombre de syllabe n'est pas respect�, mais je m'en branle)

	public:

		ChainListOfImg();
		~ChainListOfImg();

		void AddElement(ImageZoomable *_imageZoomable, string _name);
		ImageZoomable *GetElement(string eltName);  //peut �tre inutile
		long int GetQtyOfElement();
		void ExtractListOfImg(ListOfImg *listOfImgToFill, string *listOfImgNamesToFill);

};
