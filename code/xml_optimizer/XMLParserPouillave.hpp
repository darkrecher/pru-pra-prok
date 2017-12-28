#ifndef XML_PARSER_INCLUDED_PAYE_TA_CHATTE__
#define XML_PARSER_INCLUDED_PAYE_TA_CHATTE__


#include <string>
#include <fstream>
#include <stdlib.h>
#include <iostream>

using namespace std;


class XMLParser
{

  private:

        struct Baliz {
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

        int ReadTextValue(string balizName, string *textValue);

};


#endif
