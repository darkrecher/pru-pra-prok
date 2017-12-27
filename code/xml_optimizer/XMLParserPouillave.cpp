#include "XMLParserPouillave.hpp"



XMLParser::XMLParser(int _showCommentNodes = 0)
{
    showCommentNodes = _showCommentNodes;
    firstOpenedBaliz = NULL;
    XMLfile = NULL;
}


XMLParser::~XMLParser()
{
    CloseXMLFile();
}


int XMLParser::OpenXMLFile(char *_fileName)
{
    CloseXMLFile();
    fileName = string(_fileName);
    XMLfile = new ifstream(_fileName);

    fileLine = "";
    lineCursor = -1;
    currentChar = 'Z';  //valeur à la con
    errorMessage == "";
    qtyOfLineRead = 0;
    currentChar = GetNextChar();
    
    if (currentChar != '\0') {
        readingFirstNode = 1;
        fileEntirelyParsed = 0;
        return ReadNextNode();
    } else {
        errorMessage = "impossible de trouver le fichier " + fileName;
        delete XMLfile;
        return 0;
    }
}


void XMLParser::CloseXMLFile()
{
    Baliz *p1 = firstOpenedBaliz;
    Baliz *p2 = firstOpenedBaliz;
    while (p1 != NULL) {
        p2 = p2->next;
        delete p1;
        p1 = p2;
    }
    
    if (XMLfile != NULL) { delete XMLfile; }
    currentChar = '\0';
    firstOpenedBaliz = NULL;
    XMLfile = NULL;
}



void XMLParser::AddOpenedBaliz(string _balizName)
{
    Baliz *p = firstOpenedBaliz;
    Baliz *newElt = new Baliz;
    newElt->balizName = _balizName;
    newElt->next = NULL;
    if (p == NULL) {
        firstOpenedBaliz = newElt;
    } else {
        while (p->next!=NULL) { p=p->next; }
        p->next = newElt;
    }
}


int XMLParser::RemoveLastBaliz(string _balizName)
{
    if (firstOpenedBaliz == NULL) {
        errorMessage = "impossible de fermer la balize " + _balizName + " car il n'y a pas " +
                       "encore de balise d'ouverte.";
        return 0;
    }
    
    Baliz *p = firstOpenedBaliz;
    Baliz *precedentOfP = NULL;
    
    while (p->next != NULL) {
        precedentOfP = p;
        p = p->next;
    }
    
    if (p->balizName == _balizName) {
        delete p;
        if (precedentOfP == NULL) {
            firstOpenedBaliz = NULL;
        } else {
            precedentOfP->next = NULL;
        }
        return 1;
    }
    errorMessage = "impossible de fermer la balize " + _balizName + " car elle n'est pas "+
                   "la dernière balise ouverte.";
    return 0;
}


string XMLParser::GetListOfOpenedBaliz()
{
    Baliz *p = firstOpenedBaliz;
    string listOfBaliz = "";
    while (p!=NULL) {
        listOfBaliz += p->balizName + " ";
        p = p->next;  
    }
    return listOfBaliz;
}


char XMLParser::GetNextChar()
{
    if (currentChar == '\0') { return '\0'; }
    
    if (lineCursor >= fileLine.length()) {
        fileLine = "";
        while (fileLine == "") {
            if (!getline(*XMLfile, fileLine)) { return '\0'; }
            qtyOfLineRead++;
        }
        lineCursor = 0;
    }
    
    char Result = fileLine[lineCursor];
    lineCursor++;
    return Result;
}


string XMLParser::GetCurrentNodeValue() { return currentNodeValue; }
long int XMLParser::GetCurrentNodeValueI() { return currentNodeValue_i; }
float XMLParser::GetCurrentNodeValueF() { return currentNodeValue_f; }
int XMLParser::GetCurrentNodeType() { return currentNodeType; }
int XMLParser::IsFileEntirelyParsed() { return fileEntirelyParsed; }


string XMLParser::ConversionIToA(long int value)
{
    string result = "";
    int neg;
    if (value <0) {
        neg = 1;
        value = -value;
    } else {
        neg = 0;
    }
    while (value>0) {
        result = (char) ((value%10) + (int) '0') + result;
        value = value /10;
    }
    if (neg) { result = string("-") + result; }
    if (result == "") { result = "0"; }
    return result;
}


string XMLParser::GetErrorMessageHeader()
{
    if (fileEntirelyParsed || (qtyOfLineRead == 0)) {
        return "";
    } else {
        return string("erreur à la ligne numéro ")
               + ConversionIToA(qtyOfLineRead)
               + " du fichier " + fileName + " : \n";
    }
}


string XMLParser::GetErrorMessage()
{
    if (errorMessage == "") {
        return "Erreur de nature inconnue";
    } else {
        return errorMessage;
    }
}


//putain j'y crois pas que je sois encore obligé de coder ce genre de connerie.
//y'a pas une fonction qui fait déjà ce truc? Bordel de merde!!
int XMLParser::ConvertNodeToNumeric()
{
    int inTheDecimalPart = 0;
    float decimalCoef = 1.0;
    currentNodeValue_i = 0;
    currentNodeValue_f = 0;
    int NumericValue;
    int error = 0;
    int i=0;
    int negativeValue = 0;
    
    if (currentNodeValue == "") {error = 1; }
    
    if (!error) {
        if (currentNodeValue[0] == '-') {
            negativeValue = 1;
            i++;
            if (currentNodeValue.length() <= 1) { error = 1; }
        }
    }
    
    while ((!error) && (i < currentNodeValue.length())) {
        if ((currentNodeValue[i] == '.') || (currentNodeValue[i] == ',')) {
            if (!inTheDecimalPart) { inTheDecimalPart = 1; } else { error = 1; }
        } else if ((currentNodeValue[i] >= '0') && (currentNodeValue[i] <= '9')) {
            NumericValue = (int) (currentNodeValue[i]) - (int) ('0');
            if (inTheDecimalPart) {
                decimalCoef = decimalCoef / 10;
                currentNodeValue_f += decimalCoef * NumericValue;
            } else {
                currentNodeValue_f = currentNodeValue_f*10 + NumericValue;
                currentNodeValue_i = currentNodeValue_i*10 + NumericValue;
            }
        } else {
            error = 1;
        }
        i++;
    }
    
    if (error) {
        errorMessage = currentNodeValue + " ne peut pas être converti en valeur numérique.";
        currentNodeType = NODE_TYPE_INCORRECT;
        return 0;
    }
    if (negativeValue) {
        currentNodeValue_f = -currentNodeValue_f;
        currentNodeValue_i = -currentNodeValue_i;
    }
    return 1;
}


int XMLParser::AnalyseNode(string node, int readAsNumber = 0)
{
    if (node == "") {
        errorMessage = "erreur du parseur XML";
        currentNodeType = NODE_TYPE_UNDEFINED;
        return 0;
    }
    
    int balizType;
    int nodeCursorEnd = node.length()-1;
    int nodeCursorBegin = 0;
    while ((node[nodeCursorEnd] == ' ') || (node[nodeCursorEnd] == '\t')) { nodeCursorEnd--; }
    
    if ((node[0] == '<') && (node[nodeCursorEnd] == '>')) {
        balizType = 1;
    } else if ((node[0] == '<') || (node[nodeCursorEnd] == '>')) {
        errorMessage = node + " n'est pas un nom de balise valide.";
        currentNodeType = NODE_TYPE_UNDEFINED;
        return 0;
    } else {
        balizType = 0;
    }
    
    if (balizType) {
        if ((node[1] == '/') || (node[nodeCursorEnd-1] == '/')) {
            if ((node[1] == '/') && (node[nodeCursorEnd-1] == '/')) {
                errorMessage = node+" n'est pas un nom de balise valide. (trop de signe '/')";
                currentNodeType = NODE_TYPE_UNDEFINED;
                return 0;
            } else if (node[1] == '/') {
                nodeCursorBegin = 2;
                nodeCursorEnd--;
                currentNodeType = NODE_TYPE_BALIZ_END;
            } else {
                nodeCursorBegin = 1;
                nodeCursorEnd -= 2;
                currentNodeType = NODE_TYPE_BALIZ_ALONE;
            }
        } else {
            nodeCursorBegin = 1;
            nodeCursorEnd--;
            currentNodeType = NODE_TYPE_BALIZ_START;
        }
        if (nodeCursorBegin > nodeCursorEnd) {
            errorMessage = node+" n'est pas un nom de balise valide.(nom de balise manquant)";
            currentNodeType = NODE_TYPE_UNDEFINED;
            return 0;
        }
    } else {
        currentNodeType = NODE_TYPE_TEXT;
    }

    currentNodeValue = "";
    for (int i=nodeCursorBegin ; i<=nodeCursorEnd ; i++) {
        if ((node[i] == '<') || (node[i] == '>')) {
            errorMessage = node+" n'est pas un nom de noeud XML valide.('<' ou '>' non prévu)";
            currentNodeType = NODE_TYPE_UNDEFINED;
            return 0;
        }
        currentNodeValue += node[i];
    }
    
    switch (currentNodeType) {
        case NODE_TYPE_TEXT :
            if (readAsNumber) { return ConvertNodeToNumeric(); }
        break;
        case NODE_TYPE_BALIZ_START :
            AddOpenedBaliz(currentNodeValue);
        break;
        case NODE_TYPE_BALIZ_END :
            return RemoveLastBaliz(currentNodeValue);
        break;
        default :
        break;
    }
    return 1;
}
		

int XMLParser::ReadNextNode(int readAsNumber = 0)
{
    string nodeRead;
    char stopChar;
    int stop;
    int readingComment;
    int FoundANodeWhichIsNotAComment = 0;
    
    while (!FoundANodeWhichIsNotAComment) {
    
        stop = 0;
        readingComment = 0;
        nodeRead = "";
    
        //sautage des caractères de séparation, au début.
        while ((currentChar==' ') || (currentChar=='\t')) {
            currentChar = GetNextChar();
        }
        if (currentChar=='\0') {
            if (firstOpenedBaliz == NULL) {
                errorMessage = "Fin du fichier atteinte.";
                currentNodeType = NODE_TYPE_UNDEFINED;
                fileEntirelyParsed = 1;
                return 0;
            } else {
                errorMessage = string("Certaines balises n'ont pas été fermé à la fin.") +
                               "Il reste la (les) balise(s) : " + GetListOfOpenedBaliz();
                currentNodeType = NODE_TYPE_UNDEFINED;
                fileEntirelyParsed = 0;
                return 0;
            }
        }

        if (currentChar == '<') {
            stopChar = '>';
        } else {
            stopChar = '<';
        }

        while (!stop) {
            nodeRead += currentChar;
            currentChar = GetNextChar();
            if ((nodeRead.length() == 4) && (nodeRead == "<!--")) {
                if ((currentChar == '\0') || (currentChar == stopChar)) {
                    stop = 1;
                } else {
                    readingComment = 1;
                }
            }
            if (readingComment) {
                if (   (currentChar == '\0') ||
                       (
                            (nodeRead.length()>=5) &&
                            (string(nodeRead,nodeRead.length()-2,2) == "--")
                       )
                   )
                {
                    stop = 1;
                }
            } else {
                if ((currentChar == '\0') || (currentChar == stopChar)) { stop = 1; }
            }
        }

        if (readingComment) {
            nodeRead += currentChar;
            if ((currentChar == '>') && (nodeRead.length() >= 7)) {
                currentChar = GetNextChar();
                currentNodeValue = string(nodeRead, 4, nodeRead.length()-7);
                currentNodeType = NODE_TYPE_COMMENT;
                if (showCommentNodes) {
                    cout << "commentaire : " << currentNodeValue << endl;
                }
            } else {
                currentNodeType = NODE_TYPE_UNDEFINED;
                errorMessage = nodeRead+" n'est pas un commentaire valide : " +
                               "le texte d'un commentaire ne doit pas être vide, " +
                               "et ne doit pas comporter la chaîne '--'";
                return 0;
            }
        } else {
            FoundANodeWhichIsNotAComment = 1;
        }
    }
            
    if (stopChar == '>') {
        nodeRead += currentChar;
        currentChar = GetNextChar();
    }

    //j'interprète pas le premier node, qui est normalement une ligne à la con avec
    //du "encoding blablabla".
    if (readingFirstNode) {
        readingFirstNode = 0;
        return 1;
    }
    return AnalyseNode(nodeRead, readAsNumber);
}


int XMLParser::GotAStartBaliz(string balizName)
{
    if ((currentNodeType == NODE_TYPE_BALIZ_START) &&
        (currentNodeValue == balizName))
    {
        return 1;
    }
    return 0;
}


int XMLParser::GotASingleBaliz(string balizName)
{
    if ((currentNodeType == NODE_TYPE_BALIZ_ALONE) &&
        (currentNodeValue == balizName))
    {
        return 1;
    }
    return 0;
}


int XMLParser::GotAnEndBaliz(string balizName)
{
    if ((currentNodeType == NODE_TYPE_BALIZ_END) &&
        (currentNodeValue == balizName))
    {
        return 1;
    }
    return 0;
}


int XMLParser::ReadTextValue(string balizName, string *textValue)
{
    if (!ReadNextNode()) { return 0; }
    if (currentNodeType != NODE_TYPE_TEXT) {
        errorMessage = "erreur dans la balise " + balizName;
        return 0;
    }
    *textValue = currentNodeValue;
    if (!ReadNextNode()) { return 0; }
    if (!GotAnEndBaliz(balizName)) {
        errorMessage = "erreur dans la balise " + balizName;
        return 0;
    }
    if (!ReadNextNode()) { return 0; }
    return 1;
}
