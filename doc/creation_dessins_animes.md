# Comment créer ses dessins animés

## Sommaire

 - [Préparation de l'environnement](#pr%C3%A9paration-de-lenvironnement)
 - [Syntaxe du fichier de description](#syntaxe-du-fichier-de-description)
 - [Visionnage du dessin animé](#visionnage-du-dessin-anim%C3%A9)
 - [Correction des erreurs](#correction-des-erreurs)
 - [Infos de log](#infos-de-log)


## Préparation de l'environnement

Copier le répertoire `movies/pru-pra-prok_episode_2` et son contenu dans un autre répertoire. Pour l'exemple, on suppose que le contenu sera placé dans `C:\autre_splash`.

Dans `C:\autre_splash` :

 - Supprimer tous les fichiers *.cul, ainsi que `film1.zob` et `film2.zob`.
 - Au choix :
     + Créer un nouveau fichier texte, qui contiendra la description de votre dessin animé. L'extension du fichier n'a pas d'importance, mais par convention, on utilise .xml ou .zob.
     + Ou bien copier `movies/example/example.xml`, ainsi que les images `movies/example/*.png` et les sons `movies/example/*.wav`. Cela permet de partir d'un dessin animé existant, et de modifier progressivement son contenu.
 - Facultatif : copier le fichier `movies/example/config.txt` (en écrasant le fichier `config.txt` existant). Cela permet de lancer le visionneur en mode fenêtré, plutôt qu'en plein écran, ce qui est plus pratique durant une création.
 - Éditer/modifier le fichier de description du dessin animé. Il permet de définir la liste des fichiers images et sons utilisés ; la création des sprites et de leurs images ; les instructions de placement des sprites, de la caméra, du zoom, de l'émission des sons, etc.


## Syntaxe du fichier de description

Voir les commentaires du fichier d'exemple : [../movies/example/example.xml](../movies/example/example.xml).

Puis, voir le fichier XML de référence : [reference_fichier_splash.md](reference_fichier_splash.md).


## Visionnage du dessin animé

Il est fortement conseillé de tester le visionnage de votre dessin animé au fur et à mesure de sa création, afin de corriger les erreurs de syntaxe du fichier, les bugs de positionnement, etc.

Pour le visionner, prenez le fichier de description (par exemple, `C:\autre_splash\example.xml`), et glisser-le sur le fichier `C:\autre_splash\splash.exe`.

Ou sinon, vous pouvez utiliser les commandes DOS suivantes :

    cd C:\autre_splash
    splash.exe example.xml


## Correction des erreurs

Si le fichier de description est incorrect, le visionneur affichera un gros point d'interrogation rouge, ou bien le message suivant :

> impossible de jouer le film.
> Consulter le fichier stderr.txt,
> dans le répertoire du film,
> pour le détail des messages d'erreur.

Dans ce cas, ouvrir le fichier `C:\autre_splash\stderr.txt` pour savoir où est l'erreur.

Exemple de contenu de stderr :

> erreur à la ligne numéro 84 du fichier C:\autre_splash\example.xml :
> Image source inconnu, ou libéré précédemment : Piafz

Attention, le numéro de ligne indiqué est approximatif. L'erreur se situe parfois plusieurs lignes avant.


## Infos de log

Après avoir visionné un fichier de description correct, quelques informations de logs sont indiquées dans le fichier `C:\autre_splash\stdout.txt`.

Exemple :

> La lecture de la configuration a été correctement effectuée.
> La lecture du film a été effectuée. Durée totale : 4100 ms
> Date de fin de chargement : 519 ms
> Fin de la projection.
> Alarrachitude cumulée : 0 ms
> Nombre d'images alarrachée : 0
> Glanditude cumulée : 0 ms
> Fin du programme. Date : 7449

Le terme "alarrachitude" désigne les ralentissements durant le visionnage. Certaines séquences peuvent être un peu longue à calculer (s'il y a beaucoup de grandes images à afficher, des zooms, etc). Un précalcul est effectué sur un buffer d'une dizaine d'images, mais parfois cela ne suffit pas.

Si vous observez des ralentissements, vérifier les valeurs "Alarrachitude cumulée" et "Nombre d'images alarrachée". Si elles sont trop grandes, essayez de simplifier votre dessin animé, de pré-zoomer des images, etc. Cela dépend également des performances de votre ordinateur.

Le terme "Glanditude" indique le temps durant lequel le visionneur a précalculé le maximum d'images, et attend que l'image suivante soit affichée pour avoir un peu de mémoire disponible et refaire des précalculs. Si cette valeur est haute, c'est plutôt bon signe.


## Fichiers de description de Pru-Pra-Prok

Les fichiers définissant ce dessin animé ont été optimisés. Ils sont difficilement lisible par un humain.

Une version "human-readable" (avant optimisation) est disponible dans ce repository.

[Partie 1](../movies/version_human_readable/film1_lisible.zob)

[Partie 2](../movies/version_human_readable/film2_lisible.zob)
