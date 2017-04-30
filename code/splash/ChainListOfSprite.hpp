#include "SE_Sprite.hpp"
#include <string>



class ChainListOfSprite
{

    private:

        typedef struct EltSprite {
            string name;

            //c'est juste un pointeur, pas un tableau
            string *listOfImgNames;

            //ça répète la même info que le imgQty de la listofimg du sprite,
            //mais je m'en branle
            long int imgQty;

//tulututu tulu flouf flouf pililili tulutu
// (là y'a des paillettes qui descendent du plafond, et des lapins qui gambadent)
//tulu tutu luluuuulu glouglouglou bloumf prout prout
// (arrivée d'une danseuse en maillot de bain, saoulées à l'absinthe,
//qui s'écroule dans les lapins)
//Bon j'en ai marre d'écrire des conneries, je dois dessiner.


            SE_Sprite *theSprite;
            EltSprite *next;
        };

        EltSprite *first;
        EltSprite *cursor;

	public:


		ChainListOfSprite();
		~ChainListOfSprite();

		void AddElement(SE_Sprite *_sprite, string *_listOfImgNames,
                        long int _imgQty, string _name);

		int SetCursor(string eltName);
		SE_Sprite *GetCurrentElement();
		long int GetIndexOfImgOfCurrentElement(string imgName);
		long int GetQtyOfElement();

		void DeleteAllSprite();

};
