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

//pfioouuuuuu!!! c'est quand m�me super long � faire de programmer et de faire le dessin anim�
//apr�s. Evidemment, je n'arr�te pas de me dire que je suis stupide et que je devrais le faire
//en Flash. Mais maintenant que j'ai commenc� avec �a, je vais pas laisser tomber. Enfin
//c'est quand m�me super d�bile.
//Ouais, mais une fois que j'aurais fini, y'a des tas de gens qui vont le voir. Alors
//tant pis si �a prend du temps. Il faut se lancer! whizzz!!!!
//
//Un film ou un dessin anim� vaut le coup d'�tre fait quand la relation suivante
//est respect�e ;
// temps du dessin anim� * nombre de gens qui vont le voir > temps mis � faire le dessin anim�
//voil� voil�.

	public:

		ChainListOfSound();
		~ChainListOfSound();

		void AddElement(Mix_Chunk *_Sound, string _name);
		Mix_Chunk *GetElement(string eltName);
		long int GetQtyOfElement();  //peut �tre inutile

		void FreeAllSound();

};
