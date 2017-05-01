#include "XMLParser.hpp"
#include "ConfigInfos.hpp"


class ConfigXMLParser
{

//Michel Vaillant est un gros naze
//Le mec qui a fait cette bandes dessinées devait être un bon psychotique.
//Nan, j'veux dire. Raconter deux ou trois histoires à propos de formule 1, c'est faisable.
//Mais là, le mec il en a fait dans les quanrante-douze! Déjà en vrai, les courses de
//teuf-teuf, c'est lassant, donc dans une bande dessinée, pareil!
//J'en ai lu que très peu, des Michel Vaillant, mais c'est toujours la même chose.
//
//Tiens, je vous fait un résumé :
//VROOOOOOOOOOOOOUUUUUUUUUUUMMMMMMMMMMMMM!!!
//VVVVVVVVVRRRRRROOOOOOOOOOOOOIIIOOOOOOOOOOOUUUUUUUUIIIIMMMMMMMM!!
//Steve Warson! Enculé de ta soeur!
//VVVRRRROOOOMMMMMMMMMM hiiii!! (arrêt au stand)
//Mais bordel sortez vous les mains du cul tas de feignasses! Foutez-moi du jus dans
//cette chignole que je puisse avancer! Quoi! Pute Foutre!
//VVRRRRRRRRRRRRROOOOAAAAAAAAAAAAARRRRRRRRRR
//Arg! Qui m'a foutu un déséquilibré mental au milieu de la route avec un drapeau en échiquier!
//J'm'en vais lui tailler ses roubignolles en tétraèdre, à cet enlardé!
//CRAAAAAAAAAAC!!!!!!!
//Ouais, j'ai gaaaaagné!! Amenez les jeroboam de champ' à 500 000 balles la bouteille, que
//j'en balance sur tout ces cons de journalistes et de fans! Faut bien que je montre que
//j'ai du fric à plus savoir qu'en foutre et que j'en ai rien à carrer de gaspiller
//du bon alcool! YYYEEEEEEEEEEEEEPPEEEEEEEEEEEEEEEEEEEE!!!
//
//prochain épisode : Michel Vaillant fait bouffer du béton à Steve Warson
//prochain prochain épisode : Michel Vaillant se fait tuner sa Formule 1.
//prochain prochain prochain épisode : Michel Vaillant est handicapé à vie et organise
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

