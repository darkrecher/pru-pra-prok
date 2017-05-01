#ifndef XML_PARSER_INCLUDED_PAYE_TA_CHATTE__
#define XML_PARSER_INCLUDED_PAYE_TA_CHATTE__


#include <string>
#include <fstream>
#include <stdlib.h>
#include <iostream.h>
#include <SDL.h>


class XMLParser
{

  private:

        typedef struct Baliz {
            string balizName;
            Baliz *next;
        };
        Baliz *firstOpenedBaliz;

        string fileName;
        ifstream *XMLfile;
        string fileLine;
        long int lineCursor;
        long int qtyOfLineRead;
        char currentChar;

		string errorMessage;
		int fileEntirelyParsed;

        int readingFirstNode;
        string currentNodeValue;
        long int currentNodeValue_i;
        double currentNodeValue_f;
        int currentNodeType;

        int showCommentNodes;

		void AddOpenedBaliz(string _balizName);
		int RemoveLastBaliz(string _balizName);

		string ConversionIToA(long int value);
		char GetNextChar();

        int AnalyseNode(string Node, int readAsNumber = 0);
        int ConvertNodeToNumeric();

	public:

        static const int NODE_TYPE_UNDEFINED = 0;
        static const int NODE_TYPE_INCORRECT = -1;
        static const int NODE_TYPE_TEXT = 1;
        static const int NODE_TYPE_BALIZ_START = 2;
        static const int NODE_TYPE_BALIZ_END = 3;
        static const int NODE_TYPE_BALIZ_ALONE = 4;
        static const int NODE_TYPE_INT = 5;
        static const int NODE_TYPE_FLOAT = 6;
        static const int NODE_TYPE_COMMENT = 7;

//Seule une tr�s petite partie (environ 10%) de vos pens�es vous appartiennent r�ellement
//et ont �t� cr��es par vous-m�me.
//Le reste vient d'�l�ments ext�rieurs (dialogue avec d'autres gens, films, livres,
//publicit�s, instinct naturel, �ducation...)
//A partir de l�, il devient absurde de vouloir interdire la copie, la diffusion,
//la transformation, etc... d'une oeuvre auquel vous n'auriez particip� que de mani�re infime.
//Je ne fait qu'appliquer ce raisonnement � moi-m�me. Et je m'en servirait pour me moquer
//des artistes idiots qui veulent pas qu'on copie leur musique.
//
//Oh, une derni�re chose. Le fait que seuls 10% de vos pens�es vous appartiennent
//n'a rien � voir avec le fait que les humains n'utilisent que 10% de leur cerveau.
//En plus il para�t que c'est m�me pas vrai cette histoire de cerveau inexploit�.

		XMLParser(int _showCommentNodes = 0);
		~XMLParser();

		int OpenXMLFile(char *_fileName);
		void CloseXMLFile();

		int ReadNextNode(int readAsNumber = 0);

		string GetListOfOpenedBaliz();
		string GetCurrentNodeValue();
        int GetCurrentNodeType();
        long int GetCurrentNodeValueI();
        float GetCurrentNodeValueF();

		string GetErrorMessageHeader();
		string GetErrorMessage();
		int IsFileEntirelyParsed();

		int GotAnEndBaliz(string balizName);
        int GotAStartBaliz(string balizName);
        int GotASingleBaliz(string balizName);

        int ReadNumericValue(string balizName, Sint32 *numericValue,
                             Sint32 minValue = 0, Sint32 maxValue = 0,
                             int testValue = 0);

        int ReadTextValue(string balizName, string *textValue);
        int ReadNodeOfColor(string balizName, Uint8 *_red, Uint8 *_green, Uint8 *_blue);

};


#endif
