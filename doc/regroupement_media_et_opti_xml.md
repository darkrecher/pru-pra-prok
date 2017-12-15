**********************
**    Concatfile    **
**********************

Permet de cr�er des fichiers au format .cul (format de compression genre tar.gz mais pas exactement)

Reprenons l'exemple du film d'exemple. (Tiens c'est marrant cette phrase.)

Vers le d�but du film, on a ceci :

	<LoadImg> Collines </LoadImg>
	<LoadImg> Piaf </LoadImg>	
	<LoadSnd> Croa </LoadSnd>

Ca indique quels fichiers il faut charger pour jouer le film. Le probl�me c'est qu'ils sont mis en vrac dans le m�me r�pertoire que le film, et si on a Watt-mille fichiers d'images et de sons, �a devient le bronx.

Pour �viter �a, voici les trucs � faire : 


 - 1 -
cr�er un fichier list_concat.txt, contenant le texte suivant : 

dataN.cul

Collines.png
Piaf.png
Croa.wav

(fin du fichier)


 - 2 -
Mettez ce fichier nouvellement cr�� + les 3 fichiers d'images et de sons + concatfile.exe dans un m�me r�pertoire. Ex�cutez la commande : 
ConcatFile list_concat.txt

cela cr�e un fichier dataN.cul


 - 3 -
compressez ce fichier au format gz, avec le logiciel que vous voulez. (7-zip est tr�s bien)
Vous obtenez un fichier "dataN.cul.gz". Renommer-le en data.cul.


 - 4 -
Mettez ce fichier compress� dans le r�pertoire o� se trouve le film d'exemple.


 - 5 -
Dans le script exemple.zob, �crivez ceci :

<CompressedFile> <Name> data.cul </Name>
	<LoadImg> Collines </LoadImg>
	<LoadImg> Piaf </LoadImg>	
	<LoadSnd> Croa </LoadSnd>
</CompressedFile>

(� la place de la liste initiale des 3 fichiers)

Attention, l'ordre dans lequel les fichiers sont sp�cifi�s dans le script est important. Il faut que ce soit le m�me ordre que dans list_concat.txt.


Voil�, maintenant vous pouvez visionner le film. Il n'y a plus besoin des 3 fichiers d'images et de sons, il faut seulement avoir le fichier data.cul.


 - 6 -
Pour avoir la possibilit� de re-extraire les fichiers images et sons, cr�ez un fichier nomm� "List_ImgSons.zob", contenant seulement le d�but du script du film (jusqu'� la fin de la balise </ImgSoundFiles>). Ensuite, mettez l'ex�cutable ExtractFile.exe dans le r�pertoire du film d'exemple et ex�cutez-le.

Vous retrouverez vos trois fichiers d'images et de sons dans un r�pertoire "FilmData"



Voil�. Certes, �a fait faire un tas de trucs compliqu�s pour finalement obtenir pas grand chose de plus. Vous ais-je dit que j'en avais rien � faire? Oui surement. De toutes fa�ons, qui ira lire toutes ces explications d�biles? HAhahahaha!!!


Attention si vous optimisez un script de film avec l'utilitaire de merde xmloptimizer.exe. Ca vire le nom de fichier dans les balises <CompressedFile>. Du coup faut reprendre le script et r��crire "data.cul" dedans. Vous avez rien compris? Pas moi, j'ai tout compris. Normal, c'est moi qu'ai tout fait. H�h�������������!!


Le format de compression .cul est un tout petit peu plus efficace que le tar.gz. Tout simplement parce que les .cul ne conserve pas tout un tas d'infos dont j'ai rien � foutre, genre le nom de chaque fichier, les dates de cr�ation-modification-derni�re sodomie, etc etc...


J'avais un autre truc � dire mais je sais plus quoi.

Ah oui! 

Ah ben non j'ai vraiment oubli�.


