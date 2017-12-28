#include <string>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include "XMLParserPouillave.hpp"

using namespace std;


const int NUMBER_OF_NODE_PER_LINE = 30;
const int ALPHABET_SIZE = 26 + 26 + 10; //minuscules + majuscules + nombres

class StringReplacer
{

    private:

        struct EltStrRep {
            string oldValue;
			string replacementValue;
            EltStrRep *next;
        };

        EltStrRep *first;
		long int qtyOfElement;

		void AddElement(string _oldValue, string _replacementValue);
		string SeekReplacementValue(string _oldValue);
		string BuildReplacementValue(long int valueIndex);

	public:
		StringReplacer();
		~StringReplacer();

		string GetStringOfReplacement(string _oldValue);

};



StringReplacer::StringReplacer()
{
    first = NULL;
	qtyOfElement = 0;
}


StringReplacer::~StringReplacer()
{
    EltStrRep *p1 = first;
    EltStrRep *p2 = first;
    while (p1 != NULL) {
        p2 = p2->next;
        delete p1;
        p1 = p2;
    }
}


void StringReplacer::AddElement(string _oldValue, string _replacementValue)
{
    EltStrRep *newElt = new EltStrRep;
    newElt->oldValue = _oldValue;
    newElt->replacementValue = _replacementValue;
    newElt->next = first;
	first = newElt;
	qtyOfElement++;
}


string StringReplacer::SeekReplacementValue(string _oldValue)
{
    EltStrRep *p = first;
    while ((p!=NULL) && (p->oldValue!=_oldValue)) { p=p->next; }
    if (p != NULL) { return p->replacementValue; }
    return "";
}


string StringReplacer::BuildReplacementValue(long int valueIndex)
{
	string result = "";
	int digitValue;
	char digitChar;

	do {

		digitValue = valueIndex % ALPHABET_SIZE;
		valueIndex = valueIndex / ALPHABET_SIZE;

		if (digitValue < 26) {
			digitChar = (char) (digitValue + int('a'));
		} else if (digitValue < 26+26) {
			digitChar = (char) (digitValue - 26 + int('A'));
		} else {
			digitChar = (char) (digitValue - 26 - 26 + int('0'));
		}

		result = digitChar + result;

	} while (valueIndex != 0);

	return result;
}


string StringReplacer::GetStringOfReplacement(string _oldValue)
{
	string result = SeekReplacementValue(_oldValue);
	if (result == "") {
		result = BuildReplacementValue(qtyOfElement);
		AddElement(_oldValue, result);
	}
	return result;
}



int isNumericValue(string value)
{
	int i = 0;
	int FoundOnlyNumericCharacter = 1;

	if (value == "") { return 0; }

	if ((value[0] == '-') && (value.length() > 1)) { i++; }

	while ((i < value.length()) && (FoundOnlyNumericCharacter)) {
		if ( (value[i] < '0') || (value[i] > '9') ) {
			FoundOnlyNumericCharacter = 0;
		}
		i++;
	}
	return FoundOnlyNumericCharacter;
}



int main(int argc, char *argv[])
{

    if (argc < 2) {
        cerr << "ERREUR : 1er argument = source. 2eme argument = destination" << endl;
        system("PAUSE");
        return 1;
    }

    XMLParser XMLparser = XMLParser(0);
	StringReplacer stringReplacer = StringReplacer();  //j'adore ce genre de ligne de code!

    if (!XMLparser.OpenXMLFile(argv[1])) {
        cerr << "ERREUR : impossible de trouver le fichier XML" << argv[1] << endl;
        system("PAUSE");
        return 1;
    }

   	ofstream fichier_out(argv[2], ios::out|ios::trunc);
	if (!fichier_out) {
		cerr << "ERREUR : impossible de créer le fichier de sortie" << argv[2] << endl;
		system("PAUSE");
		return 1;
	}

	fichier_out << "<? paye ta chatte ?>";
    int writeNewLine = 1;
    int stop = 0;
	string NodeValue;

    while (!stop) {

        switch (XMLparser.GetCurrentNodeType()) {
            case XMLParser::NODE_TYPE_BALIZ_ALONE:
                fichier_out << "<" << XMLparser.GetCurrentNodeValue() << "/>";
            break;
            case XMLParser::NODE_TYPE_BALIZ_START:
                fichier_out << "<" << XMLparser.GetCurrentNodeValue() << ">";
            break;
            case XMLParser::NODE_TYPE_BALIZ_END:
                fichier_out << "</" << XMLparser.GetCurrentNodeValue() << ">";
            break;
            default:
				NodeValue = XMLparser.GetCurrentNodeValue();
				if (isNumericValue(NodeValue)) {
					fichier_out << NodeValue;
				} else {
					fichier_out << stringReplacer.GetStringOfReplacement(NodeValue);
				}
        }

        writeNewLine++;
        if (writeNewLine == NUMBER_OF_NODE_PER_LINE) {
            writeNewLine = 0;
            fichier_out << endl;
        }

        if (!XMLparser.ReadNextNode()) { stop = 1; }

    }

    int returnValue;

    if (!XMLparser.IsFileEntirelyParsed()) {
        cerr << "ERREUR : impossible d'interpréter le fichier source "  << endl;
    	cerr << XMLparser.GetErrorMessageHeader() << endl;
        cerr << XMLparser.GetErrorMessage() << endl;
        returnValue = 1;
    } else {
        cout << "Fin de la conversion. Fichier source OK." << endl;
        returnValue = 0;
    }

    fichier_out.close();
    XMLparser.CloseXMLFile();
    system("PAUSE");
    return returnValue;

}
