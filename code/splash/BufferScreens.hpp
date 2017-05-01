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

//Comprenons-nous bien monsieur l'ing�nieur, si nous vous engageons, ce n'est pas du tout
//pour vos capacit�s de r�flexion, de cr�ation ou de management. Notre entreprise est
//suffisamment automatis�e pour qu'il n'y ait presque plus besoin de gestion de la part
//d'un humain. Vous pouvez donc d�s � pr�sent vous enfoncer vos dipl�mes dans le cul.
//
//Non. Si on vous engage, c'est gr�ce � votre capacit� � vous vendre durant l'entretien
//d'embauche, � para�tre bien, correctement habill�, et civilis�. Cela montre clairement
//que vous avez su rentrer dans le syst�me, et que vous �tes donc capable de l�cher le cul
//de n'importe lequel de vos sup�rieurs. C'est de cela dont nous avons besoin. Et aussi,
//accessoirement, de pouvoir �crire sur nos plaquettes de pr�sentation, sans trop mentir :
//"Notre entreprise embauche plus de 200 ing�nieurs par an."
//Vous pouvez donc aller � votre cellule de travail pour y dormir. Je vous appellerais
//quand je ressentirais le besoin d'avoir le cul l�ch�.

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

