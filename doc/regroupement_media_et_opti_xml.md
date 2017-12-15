**********************
**    Concatfile    **
**********************

Permet de créer des fichiers au format .cul (format de compression genre tar.gz mais pas exactement)

Reprenons l'exemple du film d'exemple. (Tiens c'est marrant cette phrase.)

Vers le début du film, on a ceci :

	<LoadImg> Collines </LoadImg>
	<LoadImg> Piaf </LoadImg>	
	<LoadSnd> Croa </LoadSnd>

Ca indique quels fichiers il faut charger pour jouer le film. Le problème c'est qu'ils sont mis en vrac dans le même répertoire que le film, et si on a Watt-mille fichiers d'images et de sons, ça devient le bronx.

Pour éviter ça, voici les trucs à faire : 


 - 1 -
créer un fichier list_concat.txt, contenant le texte suivant : 

dataN.cul

Collines.png
Piaf.png
Croa.wav

(fin du fichier)


 - 2 -
Mettez ce fichier nouvellement créé + les 3 fichiers d'images et de sons + concatfile.exe dans un même répertoire. Exécutez la commande : 
ConcatFile list_concat.txt

cela crée un fichier dataN.cul


 - 3 -
compressez ce fichier au format gz, avec le logiciel que vous voulez. (7-zip est très bien)
Vous obtenez un fichier "dataN.cul.gz". Renommer-le en data.cul.


 - 4 -
Mettez ce fichier compressé dans le répertoire où se trouve le film d'exemple.


 - 5 -
Dans le script exemple.zob, écrivez ceci :

<CompressedFile> <Name> data.cul </Name>
	<LoadImg> Collines </LoadImg>
	<LoadImg> Piaf </LoadImg>	
	<LoadSnd> Croa </LoadSnd>
</CompressedFile>

(à la place de la liste initiale des 3 fichiers)

Attention, l'ordre dans lequel les fichiers sont spécifiés dans le script est important. Il faut que ce soit le même ordre que dans list_concat.txt.


Voilà, maintenant vous pouvez visionner le film. Il n'y a plus besoin des 3 fichiers d'images et de sons, il faut seulement avoir le fichier data.cul.


 - 6 -
Pour avoir la possibilité de re-extraire les fichiers images et sons, créez un fichier nommé "List_ImgSons.zob", contenant seulement le début du script du film (jusqu'à la fin de la balise </ImgSoundFiles>). Ensuite, mettez l'exécutable ExtractFile.exe dans le répertoire du film d'exemple et exécutez-le.

Vous retrouverez vos trois fichiers d'images et de sons dans un répertoire "FilmData"



Voilà. Certes, ça fait faire un tas de trucs compliqués pour finalement obtenir pas grand chose de plus. Vous ais-je dit que j'en avais rien à faire? Oui surement. De toutes façons, qui ira lire toutes ces explications débiles? HAhahahaha!!!


Attention si vous optimisez un script de film avec l'utilitaire de merde xmloptimizer.exe. Ca vire le nom de fichier dans les balises <CompressedFile>. Du coup faut reprendre le script et réécrire "data.cul" dedans. Vous avez rien compris? Pas moi, j'ai tout compris. Normal, c'est moi qu'ai tout fait. Héhééééééééééééé!!


Le format de compression .cul est un tout petit peu plus efficace que le tar.gz. Tout simplement parce que les .cul ne conserve pas tout un tas d'infos dont j'ai rien à foutre, genre le nom de chaque fichier, les dates de création-modification-dernière sodomie, etc etc...


J'avais un autre truc à dire mais je sais plus quoi.

Ah oui! 

Ah ben non j'ai vraiment oublié.


