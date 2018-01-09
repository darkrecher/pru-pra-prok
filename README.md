# Pru-pra-prok

Pour ceux qui connaissent déjà, y'aura rien de plus que ce que j'avais fait à l'époque. C'est juste que je le met sur github.

Pour ceux qui ne connaissent pas : c'est en cours. Et c'est de très bon goût. Il y a un épisode 2, mais pas d'épisode 1.

Ce bidule à plus de 10 ans, quand même...


## Comment visionner le dessin animé

Cliquez sur le bouton vert "Clone or download" (en haut à droite de la page web de github), puis sur "Download ZIP".

Décompressez le fichier téléchargé.

Double-cliquez sur le fichier `pru_pra_prok_partie_1.bat`. Le dessin animé devrait démarrer automatiquement, en plein écran.

Si vous avez l'antivirus Avast, il est possible que celui-ci émette un avertissement, car le visionneur de dessin animé n'est pas un programme suffisamment répandu.

Dans ce cas, le premier lancement échouera. Appuyez sur Echap pour quitter, attendez un peu que l'analyse d'Avast se termine, puis relancez le .bat.

Lorsque la première partie est terminée, double-cliquez sur le fichier `pru_pra_prok_partie_2.bat`

Touches de fonction :

 - flèche du haut/flèche du bas : avance rapide / retour arrière entre les séquences.
 - page up/page down : avance rapide / retour arrière entre les scènes (plus rapide qu'avec les séquences).
 - "+" / "-" du pavé numérique : augmenter / baisser le son.
 - 0 du pavé numérique : couper / remettre le son.
 - P : play / pause
 - Echap : quitter
 - F1 : copie d'écran dans un fichier "screenshot.bmp" (on ne peut en faire qu'une seule à la fois).

Si ça ne fonctionne pas bien, essayez de modifier le fichier [movies/pru-pra-prok_episode_2/config.txt](movies/pru-pra-prok_episode_2/config.txt). Les explications sont directement dedans, sous forme de commentaires. Résultat non garanti, si ça ne fonctionne pas, il est fort possible qu'il n'y ait pas de solution.


## Récupération des images et des sons

Télécharger et décompresser le repository comme décrit dans le chapitre précédent.

Copier le fichier `code/extract_files/extract_files.exe`, dans le répertoire `movies/pru-pra-prok_episode_2`

Exécuter le fichier copié.

Une fenêtre de commande DOS s'ouvre, affichant quelques informations de log.

Lorsque l'exécution est terminée, un répertoire `movies/pru-pra-prok_episode_2/FilmData` a été créé, contenant les images .png et les sons .wav du dessin animé.


## Création de vos propres dessins animés

Presque fini. À relire.

Voir : [doc/creation_dessins_animes.md](doc/creation_dessins_animes.md)

Puis, voir [doc/outils_annexes.md](doc/outils_annexes.md), pour les utilitaires de compression/décompression/optimisation. (Ils ne sont pas indispensables).


## Recompilation, reconstruction du projet, etc.

Presque fini. À relire.

TODO : expliquer à quoi sert basicimg.zob. Et que ça fait un message s'il n'est pas présent.

Voir : [doc/reconstruction_projet.md](doc/reconstruction_projet.md)


## TODO :

 X comment jouer le film, les touches du player, ajouter les .bat
 X comment extraire les images et les sons
 X doc rapide pour expliquer comment créer ses propres dessins animés
 X fichier de référence des XML
 X doc un peu plus détaillé pour `concat_files`, `extract_files`, `xml_optimizer`
 - relire `reconstruction_projet.md` et les autres docs.
 - gif animé du film d'exemple
 - ajouter les bonus, avec mini-texte d'explications (Gerontalia, les dessins)
 - le film pru-pra-prok au format lisible
 - chercher et terminer les TODO dans le code et la doc
 - vérifier si je n'ai pas oublié des choses sur mon disque et sur la version SourceForge.
 - finir le README avec tous les liens.


## Crédits

Créé par Réchèr.

Le code, le dessin animé et cette doc sont sous la double licence : Art Libre ou Creative Commons CC-BY (au choix).

Repository : https://github.com/darkrecher/pru-pra-prok

Mon blog : http://recher.wordpress.com
