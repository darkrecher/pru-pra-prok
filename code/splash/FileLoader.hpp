#include <SDL_image.h>
#include "ChainListOfSDLSurface.hpp"
#include "ChainListOfSound.hpp"
#include "XMLParser.hpp"
#include <zlib.h>
#include "PercentageBar.hpp"

#include <iostream.h>  //pour tester et faire du déboguage

class FileLoader
{


    private:

    //buffer qui va contenir les fichiers images et sons décompressés
    	unsigned char *buffer;
    	long int bufferSize;

    	gzFile currentCompressedFile;
    	string currentCompressedFileName;
    	long int sizeOfFileExtracted;


    //liste chainée des fichiers images dans lesquels récupérer les données
        ChainListOfSDLSurface *chainListOfSDLSurface;
    //liste des sons
        ChainListOfSound *chainListOfSound;
    //le même parser XML que le DataLoader
        XMLParser *XMLparser;

    //ça, c'est les fonctions pour récupérer des données à partir des fichiers compressés
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
//Et le marchand lui dit, "tiens, voilà du saucisson".
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

