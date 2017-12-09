#include "ListOfImg.hpp"
#include <string>

// http://stackoverflow.com/questions/15194395/c-errors-string-does-not-name-a-type#35731684
// Euh... ouais bof. C'est quand même bizarre de mettre ça juste une fois ici, et que ça fasse marcher tout le reste.
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
