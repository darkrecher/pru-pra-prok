#include <string>
#include <iostream.h>
#include <fstream>
#include <zlib.h>
#include <dir.h>
#include "XMLParserPouillave.hpp"



class FileExtractor
{


private:

	unsigned char *buffer;
	long int bufferSize;
	XMLParser XMLparser;

	int ReadLong(long int *_value, gzFile *fichier_in);
    int ExtractOneFile(gzFile *fichier_in, string destFileName);
    int ExtractAllFromOneCompressedFile(string listFileName, string descriptionFileName);


public:

	FileExtractor();
	~FileExtractor();
	int ExtractAllData(string descriptionFileName);

};



FileExtractor::FileExtractor()
{
	buffer = NULL;
	bufferSize = 0;
	XMLparser = XMLParser(0);
}


FileExtractor::~FileExtractor()
{
	if (buffer != NULL) { delete buffer; }
}


int FileExtractor::ReadLong(long int *_value, gzFile *fichier_in)
{
	unsigned char oneByte;
	long int value = 0;
	long int offset = 1;
	for (int i=0 ; i < sizeof(long int) ; i++) {
		if (!gzread(*fichier_in, &oneByte, 1)) { return 0; }
		value += (int) (oneByte) * offset;
		offset *= 256;
	}
	*_value = value;
	return 1;
}


int FileExtractor::ExtractOneFile(gzFile *fichier_in, string destFileName)
{
	cout << "     Extraction de " << destFileName << "   ";
	string destFilePathName = "FilmData\\" + destFileName;
	ofstream fichier_out(destFilePathName.c_str(), ios::out|ios::binary|ios::trunc);
	if (fichier_out == 0) {
		cout << "ERREUR : impossible de créer le fichier de sortie" << endl;
		return 0;
	}

	long int appendedFileSize;
	if (!ReadLong(&appendedFileSize, fichier_in)) {
		cout << "ERREUR : impossible de lire la taille du fichier à extraire" << endl;
		return 0;
	}
	cout << "taille : " << appendedFileSize << "   ";

	if (appendedFileSize > bufferSize) {
		if (buffer != NULL) { delete buffer; }
		buffer = new unsigned char[appendedFileSize];
		bufferSize = appendedFileSize;
	}
	
    if (!gzread(*fichier_in, buffer, appendedFileSize)) {
        cout << "ERREUR : impossible de lire tout le fichier à extraire" << endl;
		return 0;
    }

	fichier_out.write(buffer, appendedFileSize);
	fichier_out.close();
	cout << "OK." << endl;
	return 1;
}


int FileExtractor::ExtractAllFromOneCompressedFile(string compressedFileName,
                                                   string descriptionFileName)
{
	int stop = 0;
    string nameOfFileToExtract;
    gzFile compressedFile;
    int XMLFileOK = 1;
    
    compressedFile = gzopen(compressedFileName.c_str(), "rb");
	if (compressedFile == 0) {
		cout << "ERREUR : impossible d'ouvrir le fichier " << compressedFileName << endl;
		return 0;
	}
	cout << "Extraction depuis le fichier : " << compressedFileName << endl;
	
    while (!stop) {
    
        if (XMLparser.GotAStartBaliz("LoadImg")) {
            if (!XMLparser.ReadTextValue("LoadImg", &nameOfFileToExtract)) {
                cout << "ERREUR : le fichier de description " << descriptionFileName
                     << " est incorrect" << endl;
                cout << "Essayez de visionner le film pour trouver le problème" << endl;
                return 0;
            }
            nameOfFileToExtract = nameOfFileToExtract + ".png";
            if (!ExtractOneFile(&compressedFile, nameOfFileToExtract)) { return 0; }

        } else if (XMLparser.GotAStartBaliz("LoadSnd")) {
            if (!XMLparser.ReadTextValue("LoadSnd", &nameOfFileToExtract)) {
                cout << "ERREUR : le fichier de description " << descriptionFileName
                     << " est incorrect" << endl;
                cout << "Essayez de visionner le film pour trouver le problème" << endl;
                return 0;
            }
            nameOfFileToExtract = nameOfFileToExtract + ".wav";
            if (!ExtractOneFile(&compressedFile, nameOfFileToExtract)) { return 0; }
            
        } else {
            stop = 1;
        }
        
    }
    gzclose(compressedFile);
	return 1;
}


int FileExtractor::ExtractAllData(string descriptionFileName) {

    int stop = 0;
    int XMLFileOK = 1;
    string compressedFileName;

    if (!XMLparser.OpenXMLFile(descriptionFileName.c_str())) {
        cout << "ERREUR : impossible de trouver le fichier de description "
             << descriptionFileName << endl;
        return 0;
    }

    XMLFileOK = XMLFileOK && (XMLparser.ReadNextNode());
    XMLFileOK = XMLFileOK && (XMLparser.GotAStartBaliz("SPLASH"));
    XMLFileOK = XMLFileOK && (XMLparser.ReadNextNode());
    if (XMLparser.GotAStartBaliz("ProgressBarInfo")) {
        while (!XMLparser.GotAnEndBaliz("ProgressBarInfo")) {
            XMLFileOK = XMLFileOK && (XMLparser.ReadNextNode());
        }
        XMLFileOK = XMLFileOK && (XMLparser.ReadNextNode());
    }
    XMLFileOK = XMLFileOK && (XMLparser.GotAStartBaliz("ImgSoundFiles"));
    XMLFileOK = XMLFileOK && (XMLparser.ReadNextNode());
                
    if (!XMLFileOK) {
        cout << "ERREUR : le fichier de description " << descriptionFileName
             << " est incorrect" << endl;
        cout << "Essayez de visionner le film pour trouver le problème" << endl;
        return 0;
    }
    
    while (!stop) {
        if (XMLparser.GotAStartBaliz("CompressedFile")) { 
        
            XMLFileOK = XMLFileOK && (XMLparser.ReadNextNode());
            XMLFileOK = XMLFileOK && (XMLparser.GotAStartBaliz("Name"));
            XMLFileOK = XMLFileOK
                        && (XMLparser.ReadTextValue("Name", &compressedFileName));
            if (XMLFileOK) {
                if (!ExtractAllFromOneCompressedFile(compressedFileName,descriptionFileName)) {
                    return 0;
                }
            }
            XMLFileOK = XMLFileOK && (XMLparser.GotAnEndBaliz("CompressedFile"));
            XMLFileOK = XMLFileOK && (XMLparser.ReadNextNode());
            
        } else if ((XMLparser.GotAStartBaliz("LoadImg"))
                   || (XMLparser.GotAStartBaliz("LoadSnd"))) {
                   
            //rien à foutre des fichiers de données qui sont pas compressés
            XMLFileOK = XMLFileOK && (XMLparser.ReadNextNode());
            XMLFileOK = XMLFileOK && (XMLparser.ReadNextNode());
            XMLFileOK = XMLFileOK && (XMLparser.ReadNextNode());
            
        } else {
            stop = 1;
        }
        
        if (!XMLFileOK) {
            cout << "ERREUR : le fichier de description " << descriptionFileName
                 << " est incorrect" << endl;
            cout << "Essayez de visionner le film pour trouver le problème" << endl;
            return 0;
        }
    }
    
    XMLparser.CloseXMLFile();
    if (!XMLparser.GotAnEndBaliz("ImgSoundFiles")) {
        cout << "ERREUR : le fichier de description " << descriptionFileName
             << " est incorrect" << endl;
        cout << "Essayez de visionner le film pour trouver le problème" << endl;
        return 0;
    }
    
    return 1;
}


int main(int argc, char *argv[])
{
    cout << "ajout du dossier FilmData" << endl;
    mkdir("FilmData");

	FileExtractor fileExtractor = FileExtractor();
//	int returnValue = fileExtractor.ExtractAllData("film1.zob");
	int returnValue = fileExtractor.ExtractAllData("List_ImgSons.zob");
	cout << endl;
	
	if (returnValue) {
        cout << "Extraction correcte de tous les fichiers d'images et et de sons." << endl;
        cout << "Ils sont dans le dossier FilmData" << endl;
        cout << endl;
    	system("PAUSE");
        return 0;
    } else {
    	system("PAUSE");
        return 1;
    }
}
