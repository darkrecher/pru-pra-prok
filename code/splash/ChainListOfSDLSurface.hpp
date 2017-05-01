#include <SDL.h>
#include <string>



class ChainListOfSDLSurface
{

    private:

      typedef struct EltSDL_Surface {
            string name;
            SDL_Surface *theSDL_Surface;
            EltSDL_Surface *next;
        };
    
        EltSDL_Surface *first;
  
//Heureuse la rivi�re qui, comme l'�tudiant, peut ne pas suivre son cours, rester dans
//son lit et ingurgiter tout un tas de liquides d�l�t�res sans jamais �tre pollu�e.

	public:

		ChainListOfSDLSurface();
		~ChainListOfSDLSurface();
		
		void AddElement(SDL_Surface *_SDL_Surface, string _name);
		SDL_Surface *GetElement(string eltName);
		int FreeElement(string eltName);
		long int GetQtyOfElement();  //peut-�tre inutile
		void FreeAllSurfaces();
		
};
