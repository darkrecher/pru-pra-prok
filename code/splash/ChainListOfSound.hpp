#include <SDL_mixer.h>
#include <string>



class ChainListOfSound
{

    private:

        typedef struct EltSound {
            string name;
            Mix_Chunk *theSound;
            EltSound *next;
        };

        EltSound *first;

//pfioouuuuuu!!! c'est quand même super long à faire de programmer et de faire le dessin animé
//après. Evidemment, je n'arrête pas de me dire que je suis stupide et que je devrais le faire
//en Flash. Mais maintenant que j'ai commencé avec ça, je vais pas laisser tomber. Enfin
//c'est quand même super débile.
//Ouais, mais une fois que j'aurais fini, y'a des tas de gens qui vont le voir. Alors
//tant pis si ça prend du temps. Il faut se lancer! whizzz!!!!
//
//Un film ou un dessin animé vaut le coup d'être fait quand la relation suivante
//est respectée ;
// temps du dessin animé * nombre de gens qui vont le voir > temps mis à faire le dessin animé
//voilà voilà.

	public:

		ChainListOfSound();
		~ChainListOfSound();

		void AddElement(Mix_Chunk *_Sound, string _name);
		Mix_Chunk *GetElement(string eltName);
		long int GetQtyOfElement();  //peut être inutile

		void FreeAllSound();

};
