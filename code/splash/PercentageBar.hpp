#ifndef PERCENTAGE_BAR_INCLUDED_PAYE_TA_CHATTE__
#define PERCENTAGE_BAR_INCLUDED_PAYE_TA_CHATTE__


#include <SDL.h>
#include "RectOperations.hpp"


class PercentageBar
{

    private:

        static const int posX = 220;
        static const int posY = 350;
        static const int totalWidth = 200;
        static const int totalHeight = 40;
        static const int borderHeight = 5;
        static const int borderWidth = 10;

        static const int borderColorRed = 0;
        static const int borderColorBlue = 0;
        static const int borderColorGreen = 0;
        static const int noBarColorRed = 0;
        static const int noBarColorBlue = 0;
        static const int noBarColorGreen = 100;
        static const int barColorRed = 100;
        static const int barColorBlue = 100;
        static const int barColorGreen = 255;

        Uint32 borderColor;
        Uint32 noBarColor;
        Uint32 barColor;

        Uint32 totalBarWidth;

        SDL_Rect borderRight;
        SDL_Rect borderLeft;
        SDL_Rect borderUp;
        SDL_Rect borderDown;
        SDL_Rect noBarRect;
        SDL_Rect barRect;

        SDL_Surface *mainScreen;

//Ce n'est pas exactement ce que vous avez envie de faire. Mais vous le faites quand m�me.
//Vous n'�tes pas en train de vous amuser comme les petits chevreaux, vous �tes juste
//des morceaux de patate qui volent dans le milieu en ayant faim. Comment rentrer dans
//tout ce violet, et ce rose. Il ne faut pas s'en inqui�ter tant que �a. Bon, OK, le rose
//c'est la couleur du cube num�rique, mais faut rien �xagerer. On n'a pas forc�ment atteint
// un niveau sup�rieur de connerie. On en a juste d�couvert un nouvel �lot.
//Et puis arr�tez de dire que vous boycottez ce genre de trucs! Le simple fait de dire �a
//montre leur victoire sur votre cerveau. Dites juste que vous vous en branlez � deux mains!
//Tcheu!!! Hoy!!!

        int mustShowOnScreen;

	public:

        PercentageBar();
		PercentageBar(SDL_Surface *_mainScreen);
		~PercentageBar();
		void RefreshValueAndShowOnScreen(long int percentageValue,
                                         long int percentageProportion);
		void StopShowOnScreen();
		int GetMustShowOnScreen();
		void ShowOnScreen();
		void FlipMainScreen();

};


#endif
