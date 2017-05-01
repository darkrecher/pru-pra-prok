#include <SDL.h>
#include <SDL_mixer.h>
#include "MovieEvent.hpp"



class ME_PlaySound : public MovieEvent
{

  
private :

    Mix_Chunk *sample;
    int channel;
    int nbrOfTimes;


public :

    ME_PlaySound(long int _actTime, Mix_Chunk *_sample, int _channel, int _nbrOfTimes);
    ~ME_PlaySound();
    void Act();
	MovieEvent *Copy(long int timeToAdd);

};

//------------------------

class ME_StopSound : public MovieEvent
{

  
private :

    int whichChannels;

//OOOOOOOOOHHHH Festival de fleurs et de papillons dans ta gueule!! que c'est beau! Vien
//br�ler mes fleurs au centre de la glace. Le bleu du bleu revient sur le devant de la
//sc�ne intranationale.
//Alors que revient Goldorakz et son pote le petit ouistiti d�ficient qui le suit partout
//en mangeant des cheeeek cheeeek!! Le probl�me avec les gens c'est le cerveau. Le reste
//peut convenir pour un cong�lateur, ou de la chair � Napol�on. Les legos de l'espace pirate
//avec le canon qui projette des petits boulets cylindriques. ppppchouf pchouf!! MMMMM!!!
//Le calamar g�ant dans ta gueule. Vite!!! F7 pour choix du mode graphique + i. Et vlan!
//dans ta face la morphing ball. Well done, mais j'ai pas fait 100% Ce fut quand m�me une
//belle histoire. Hmmm Bolt bolt bolt! Hey David, c'est pas gentil de fouiller dans des
//papiers. Sauras tu te souvenir de �a? C'est fort possible. Et �a serait amusant que tu
//tombes sur ce bout de code. Whizzz!!


public :

    ME_StopSound(long int _actTime, int _whichChannels);
    ~ME_StopSound();
    void Act();
	MovieEvent *Copy(long int timeToAdd);

};
