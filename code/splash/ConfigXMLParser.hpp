#include "XMLParser.hpp"
#include "ConfigInfos.hpp"


class ConfigXMLParser
{

//Michel Vaillant est un gros naze
//Le mec qui a fait cette bandes dessin�es devait �tre un bon psychotique.
//Nan, j'veux dire. Raconter deux ou trois histoires � propos de formule 1, c'est faisable.
//Mais l�, le mec il en a fait dans les quanrante-douze! D�j� en vrai, les courses de
//teuf-teuf, c'est lassant, donc dans une bande dessin�e, pareil!
//J'en ai lu que tr�s peu, des Michel Vaillant, mais c'est toujours la m�me chose.
//
//Tiens, je vous fait un r�sum� :
//VROOOOOOOOOOOOOUUUUUUUUUUUMMMMMMMMMMMMM!!!
//VVVVVVVVVRRRRRROOOOOOOOOOOOOIIIOOOOOOOOOOOUUUUUUUUIIIIMMMMMMMM!!
//Steve Warson! Encul� de ta soeur!
//VVVRRRROOOOMMMMMMMMMM hiiii!! (arr�t au stand)
//Mais bordel sortez vous les mains du cul tas de feignasses! Foutez-moi du jus dans
//cette chignole que je puisse avancer! Quoi! Pute Foutre!
//VVRRRRRRRRRRRRROOOOAAAAAAAAAAAAARRRRRRRRRR
//Arg! Qui m'a foutu un d�s�quilibr� mental au milieu de la route avec un drapeau en �chiquier!
//J'm'en vais lui tailler ses roubignolles en t�tra�dre, � cet enlard�!
//CRAAAAAAAAAAC!!!!!!!
//Ouais, j'ai gaaaaagn�!! Amenez les jeroboam de champ' � 500 000 balles la bouteille, que
//j'en balance sur tout ces cons de journalistes et de fans! Faut bien que je montre que
//j'ai du fric � plus savoir qu'en foutre et que j'en ai rien � carrer de gaspiller
//du bon alcool! YYYEEEEEEEEEEEEEPPEEEEEEEEEEEEEEEEEEEE!!!
//
//prochain �pisode : Michel Vaillant fait bouffer du b�ton � Steve Warson
//prochain prochain �pisode : Michel Vaillant se fait tuner sa Formule 1.
//prochain prochain prochain �pisode : Michel Vaillant est handicap� � vie et organise
//des courses de fauteuil roulant.

    private:

        XMLParser XMLparser;

		string ReadSplashBaliz();
        string ReadConfigBaliz();
        string ReadNodeOfSurfaceType(string balizName, Uint32 *MemoryType);
        string ReadNodeOfTransparentColor();

        ConfigInfos theConfigInfos;

	public:
		ConfigXMLParser(int _showCommentNodes = 0);
		~ConfigXMLParser();

        string ConfigXMLParser::OpenConfigXMLFile(char *XMLFileName);
        void ConfigXMLParser::CloseConfigXMLFile();

        string ReadConfigXMLFile();
		ConfigInfos *GetConfigInfos();

};

