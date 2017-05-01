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


//  ha�kus. s�rie num�ro 7
//
//
//Que tu y crois ou pas,
//les vampires s'il veulent
//exister, sont l�.
//
//
//"Que fait ici cette
//barri�re de caoutchouc?"
//Pense le spermatozoide.
//
//(le nombre de syllabe n'est pas respect�, mais je m'en branle)


	public:

		ChainListOf_ListOfImg();
		~ChainListOf_ListOfImg();

		void AddElement(ListOfImg *_theListOfImg, string *_listOfImgNames, string _name);
		int SetCursor(string eltName);
		ListOfImg *GetCurrentListOfImg();
		string *GetCurrentListOfImgNames();
		long int GetQtyOfElement();  //peut-�tre inutile
		void FreeAllImages();

};
