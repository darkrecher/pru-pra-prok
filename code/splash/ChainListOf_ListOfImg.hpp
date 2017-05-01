#include "ListOfImg.hpp"
#include <string>

using namespace std;


class ChainListOf_ListOfImg
{

    private:

      typedef struct EltListOfImg {
            string name;
            ListOfImg *theListOfImg;
            string *listOfImgNames;
            EltListOfImg *next;
        };

        EltListOfImg *first;
        EltListOfImg *cursor;


//  haïkus. série numéro 7
//
//
//Que tu y crois ou pas,
//les vampires s'il veulent
//exister, sont là.
//
//
//"Que fait ici cette
//barrière de caoutchouc?"
//Pense le spermatozoide.
//
//(le nombre de syllabe n'est pas respecté, mais je m'en branle)


	public:

		ChainListOf_ListOfImg();
		~ChainListOf_ListOfImg();

		void AddElement(ListOfImg *_theListOfImg, string *_listOfImgNames, string _name);
		int SetCursor(string eltName);
		ListOfImg *GetCurrentListOfImg();
		string *GetCurrentListOfImgNames();
		long int GetQtyOfElement();  //peut-être inutile
		void FreeAllImages();

};
