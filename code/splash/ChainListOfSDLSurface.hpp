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
  
//Heureuse la rivière qui, comme l'étudiant, peut ne pas suivre son cours, rester dans
//son lit et ingurgiter tout un tas de liquides délétères sans jamais être polluée.

	public:

		ChainListOfSDLSurface();
		~ChainListOfSDLSurface();
		
		void AddElement(SDL_Surface *_SDL_Surface, string _name);
		SDL_Surface *GetElement(string eltName);
		int FreeElement(string eltName);
		long int GetQtyOfElement();  //peut-être inutile
		void FreeAllSurfaces();
		
};
