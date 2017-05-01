#include <SDL.h>
#include "ScreenConst.hpp"
#include "Scene.hpp"



class BufferScreens
{


private:

    SDL_Surface **screens;
    long int *timesToShowScreens;

    int bufferQty;
    int cursor_ScreenInWork;
    int cursor_NextScreenToShow;
    int distBetweenCursors;

    long int timeOfNextScreenToShow;

//Comprenons-nous bien monsieur l'ingénieur, si nous vous engageons, ce n'est pas du tout
//pour vos capacités de réflexion, de création ou de management. Notre entreprise est
//suffisamment automatisée pour qu'il n'y ait presque plus besoin de gestion de la part
//d'un humain. Vous pouvez donc dès à présent vous enfoncer vos diplômes dans le cul.
//
//Non. Si on vous engage, c'est grâce à votre capacité à vous vendre durant l'entretien
//d'embauche, à paraître bien, correctement habillé, et civilisé. Cela montre clairement
//que vous avez su rentrer dans le système, et que vous êtes donc capable de lécher le cul
//de n'importe lequel de vos supérieurs. C'est de cela dont nous avons besoin. Et aussi,
//accessoirement, de pouvoir écrire sur nos plaquettes de présentation, sans trop mentir :
//"Notre entreprise embauche plus de 200 ingénieurs par an."
//Vous pouvez donc aller à votre cellule de travail pour y dormir. Je vous appellerais
//quand je ressentirais le besoin d'avoir le cul léché.

public:

    BufferScreens(int _bufferQty, Uint32 _surfaceTypeOfBuffers);
    ~BufferScreens();

    int CanPutNewScreenInBuffers();
    int CanHaveNextScreenToShow();
    SDL_Surface *GetNextScreenToShow();
    int GetTimeOfNextScreenToShow();

    int AdvanceNextScreenToShow();
    int AddScreenInBuffers(Scene *sceneWithBuffer, long int TimeToShow);
    void ResetBuffers();

};

