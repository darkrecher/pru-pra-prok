#include <SDL_image.h>
#include "ChainListOfSDLSurface.hpp"
#include "ChainListOfSound.hpp"
#include "XMLParser.hpp"
#include <zlib.h>
#include "PercentageBar.hpp"

#include <iostream.h>  //pour tester et faire du d�boguage

class FileLoader
{


    private:

    //buffer qui va contenir les fichiers images et sons d�compress�s
    	unsigned char *buffer;
    	long int bufferSize;

    	gzFile currentCompressedFile;
    	string currentCompressedFileName;
    	long int sizeOfFileExtracted;


    //liste chain�e des fichiers images dans lesquels r�cup�rer les donn�es
        ChainListOfSDLSurface *chainListOfSDLSurface;
    //liste des sons
        ChainListOfSound *chainListOfSound;
    //le m�me parser XML que le DataLoader
        XMLParser *XMLparser;

    //�a, c'est les fonctions pour r�cup�rer des donn�es � partir des fichiers compress�s
        string ExtractNextFileAndFillBuffer();
        string LoadDataFromACompressedFile();

    //pointeur vers la barre de pourcentage
        PercentageBar *percentageBar;

        long int percentageTotal;
        long int percentageProgress;

	public:

////////////////////////////////////////
//L'histoire de Toto qui va acheter du saucisson
////////////////////////////////////////
//
//C'est l'histoire de Toto qui va acheter du saucisson.
//Et le marchand lui dit, "tiens, voil� du saucisson".
//Alors Toto il paie le marchand et il rentre chez lui.
//Et 75 ans plus tard, il meurt.

        long int GetPercentageProgress();
        void SetPercentageTotal(long int _percentageTotal);
        void AdvanceAndShowProgress();

        string LoadImgSoundFiles();

        FileLoader();

		FileLoader(ChainListOfSDLSurface *_chainListOfSDLSurface,
                   ChainListOfSound *_chainListOfSound, XMLParser *_XMLparser,
                   PercentageBar *_percentageBar);

		~FileLoader();

};

