#include "ListOfImg.hpp"
#include <string>

// http://stackoverflow.com/questions/15194395/c-errors-string-does-not-name-a-type#35731684
// Euh... ouais bof. C'est quand m�me bizarre de mettre �a juste une fois ici, et que �a fasse marcher tout le reste.
using namespace std;


class ChainListOfImg
{

    private:

        struct EltImgZoomable {
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
