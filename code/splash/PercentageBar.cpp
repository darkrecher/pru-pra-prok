#include "PercentageBar.hpp"


PercentageBar::PercentageBar()
{
}

//  ha�kus. s�rie num�ro 2
//
//
//de la soupe sans sel
//n'est pas de la bonne soupe
//mais du sel sans soupe est du sel
//
//
//le gars qui mate les jolies filles
//passer dans la rue
//voit aussi les moches
//
//(le nombre de syllabe n'est pas respect�, mais je m'en branle)
//
//(de plus, le dernier n'est pas de moi mais j'aime bien.
//Ca vient d'un certain Daniel Safon, un mec qui �crit des trucs sur Internet.
//C'est parfois tr�s chiant, et parfois tr�s rigolo, mais bien souvent tr�s caca.)

PercentageBar::PercentageBar(SDL_Surface *_mainScreen)
{

    mainScreen = _mainScreen;
    mustShowOnScreen = 0;

    borderColor = SDL_MapRGB(mainScreen->format, 
                             borderColorRed, borderColorGreen, borderColorBlue);
    noBarColor = SDL_MapRGB(mainScreen->format, 
                            noBarColorRed, noBarColorGreen, noBarColorBlue);
    barColor = SDL_MapRGB(mainScreen->format, 
                            barColorRed, barColorGreen, barColorBlue);

    SetRect(&borderLeft, posX, posY, borderWidth, totalHeight);
    SetRect(&borderRight, posX+totalWidth-borderWidth, posY, borderWidth, totalHeight);
    SetRect(&borderUp, posX, posY, totalWidth, borderHeight);
    SetRect(&borderDown, posX, posY+totalHeight-borderHeight, totalWidth, borderHeight);
    
    totalBarWidth = totalWidth - 2*borderWidth;
    SetRect(&noBarRect, posX+borderWidth, posY+borderHeight, 
                        totalBarWidth, totalHeight-2*borderHeight);
    SetRect(&barRect, posX+borderWidth, posY+borderHeight, 
                      totalBarWidth, totalHeight-2*borderHeight);
    
}


PercentageBar::~PercentageBar()
{
}


void PercentageBar::RefreshValueAndShowOnScreen(long int percentageValue,
                                                long int percentageProportion)
{
    long int barWidth = (percentageValue * totalBarWidth) / percentageProportion;
    if (barWidth > totalBarWidth) { barWidth = totalBarWidth; }
    if (barWidth < 0) { barWidth = 0; }
    barRect.w = barWidth;
    noBarRect.x = posX + borderWidth + barWidth;
    noBarRect.w = totalBarWidth - barWidth;
    
    ShowOnScreen();
    SDL_UpdateRect(mainScreen, posX, posY, totalWidth, totalHeight);
    mustShowOnScreen = 1;
    //ajout � l'arrache, pour que la barre de pourcentage s'affiche � chque rafraichissement
    //plus qu'� esp�rer que �a fasse pas des bugs bizarres � d'autres endroits du code.
    //Je vois pas trop comment le v�rifier
    FlipMainScreen();
}


void PercentageBar::StopShowOnScreen() { mustShowOnScreen = 0; }


int PercentageBar::GetMustShowOnScreen()
{
    return mustShowOnScreen;
}


void PercentageBar::ShowOnScreen()
{
    SDL_FillRect(mainScreen, &borderRight, borderColor);
    SDL_FillRect(mainScreen, &borderLeft, borderColor);
    SDL_FillRect(mainScreen, &borderUp, borderColor);
    SDL_FillRect(mainScreen, &borderDown, borderColor);
    SDL_FillRect(mainScreen, &noBarRect, noBarColor);
    SDL_FillRect(mainScreen, &barRect, barColor);
}

void PercentageBar::FlipMainScreen()
{
    SDL_Flip(mainScreen);
}
