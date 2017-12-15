#include <string>
#include <iostream.h>
#include <fstream>



class FileAppender
{

private:

	unsigned char *buffer;
	long int bufferSize;

	long int GetFileSize(ifstream *fichier);
	void writeLong(long int value, ofstream *fichier_out);
	int AppendOneFile(string sourceFile, ofstream *fichier_out);

public:

	FileAppender();
	~FileAppender();
	int AppendAll(string listFileName);

};



FileAppender::FileAppender()
{
	buffer = NULL;
	bufferSize = 0;
}


FileAppender::~FileAppender()
{
	if (buffer != NULL) { delete buffer; }
}


long int FileAppender::GetFileSize(ifstream *fichier)
{
	//se placer en fin de fichier
	fichier->seekg(0, std::ios::end);
	//récupérer la nouvelle position = la taille du fichier
	long int size = fichier->tellg();
	//revenir au début du fichier
	fichier->seekg(0, ios::beg);
	return size;
}


void FileAppender::writeLong(long int value, ofstream *fichier_out)
{
	for (int i=0 ; i < sizeof(long int) ; i++) {
		fichier_out->put((unsigned char) (value & 255));
		value /= 256;
	}
}


int FileAppender::AppendOneFile(string sourceFile, ofstream *fichier_out)
{
	cout << "ajout de " << sourceFile << "   ";
	ifstream fichier_in(sourceFile.c_str(), ios::in|ios::binary);
	if (fichier_in == 0) {
		cout << "ERREUR : impossible d'ouvrir le fichier source." << endl;
		return 0;
	}

	long int fileSize = GetFileSize(&fichier_in);
	writeLong(fileSize, fichier_out);
	cout << "taille : " << fileSize << "   ";


	if (fileSize > bufferSize) {
		if (buffer != NULL) { delete buffer; }
		buffer = new unsigned char[fileSize];
		bufferSize = fileSize;
	}
	fichier_in.read(buffer, fileSize);
	fichier_out->write(buffer, fileSize);

	fichier_in.close();
	cout << "OK." << endl;
	return 1;
}


int FileAppender::AppendAll(string listFileName)
{
	int fileSourceCorrect = 1;
	string line;
	string destFileName ;

    ifstream fileList(listFileName.c_str());
    if (!fileList) {
		cout << "ERREUR : impossible d'ouvrir le fichier " << listFileName << endl;
		return 0;
	}

	if (!getline(fileList, destFileName)) { destFileName = ""; }
	if (destFileName == "") {
		cout << "ERREUR : la première ligne du fichier " << listFileName
             << " doit donner le nom du fichier de sortie." << endl;
		return 0;
	}

	ofstream fichier_out(destFileName.c_str(), ios::out|ios::binary|ios::trunc);
	if (fichier_out == 0) {
		cout << "ERREUR : impossible de créer le fichier de sortie" << endl;
		return 0;
	}

	cout << "Rassemblement de fichiers vers '"<< destFileName << "'" << endl;

    while ((getline(fileList, line)) && fileSourceCorrect) {
		if (line != "") { fileSourceCorrect = AppendOneFile(line, &fichier_out); }
    }

	if (fileSourceCorrect) {
        cout << "Fin du rassemblement des fichiers." << endl;
        cout << "Vous devez maintenant compresser le fichier de sortie au format .gz" << endl;
    }
	fichier_out.close();
	return fileSourceCorrect;
}



int main(int argc, char *argv[])
{
    int resultValue;
    
    if (argc < 2) {
        cout << "Il faut indiquer le nom d'un fichier texte." << endl;
        cout << "La première ligne de ce fichier indique le nom du fichier de sortie." << endl;
        cout << "Les lignes suivantes indiquent les noms de fichiers qu'il faut coller."<<endl;
        resultValue = 0;
    } else {
        FileAppender fileAppender = FileAppender();
        int resultValue = fileAppender.AppendAll(argv[1]);
    }
    cout << endl;
	system("PAUSE");
	return resultValue;
}
