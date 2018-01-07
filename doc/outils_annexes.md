# Outils annexes

L'utilisation de ces outils n'est pas nécessaire pour créer ses propres dessins animés. Mais ils facilitent leur distribution et leur transmission.

Si vous utilisez l'antivirus Avast, leur exécution risque d'émettre un message d'avertissement au premier lancement, car ce ne sont pas des fichiers .exe très répandus. Il faut juste attendre un peu que l'analyse du fichier par Avast se termine.


## concat_file

Les dessins animés avec beaucoup de contenu risquent d'avoir beaucoup de fichiers d'images et de sons, placés en désordre dans le même répertoire. L'utilitaire `concat_file` permet de régler (plus ou moins) ce problème.

### Situation initiale

Supposons un dessin animé utilisant 2 images et un sons. La partie `<ImgSoundFiles>` du fichier de description serait donc comme ceci :

    <ImgSoundFiles>
        <LoadImg> Collines </LoadImg>
        <LoadImg> Piaf </LoadImg>
        <LoadSnd> Croa </LoadSnd>
    </ImgSoundFiles>

(Les noms sont repris du dessin animé d'exemple).

### Étape 1 : définition des fichiers à compresser

Dans le répertoire du dessin animé, créer un nouveau fichier texte, ayant par exemple pour nom : `concat_1.txt`.

Ce fichier aura le contenu suivant :

    data1.cul

    Collines.png
    Piaf.png
    Croa.wav

La première ligne indique le nom du fichier compressé qui sera créé. Les lignes suivantes indiquent les noms des fichiers à compresser (l'ordre est important).

### Étape 2 : Copie de l'utilitaire

Dans le répertoire du dessin animé, copier le fichier `code/concat_files/concat_files.exe` qui se trouve dans ce repository.

### Étape 3 : Création du fichier .cul

Glisser-déplacer le fichier `concat_1.txt` sur l'utilitaire `concat_files.exe`, ou bien exécuter la commande suivante dans une console DOS :

    concat_files.exe concat_1.txt

Un fichier `data1.cul` a été créé dans le répertoire du dessin animé.

### Étape 4 : Compression du fichier

Compresser `data1.cul` au format gz, à l'aide d'un logiciel de compression (par exemple 7-zip).

Le fichier compressé doit avoir le même nom : `data1.cul`. On perd donc l'ancien fichier. Éventuellement, une sauvegarde peut être faite, mais ce n'est pas nécessaire.

### Étape 5 : Modification de la description du dessin animé

Dans la partie `<ImgSoundFiles>` du fichier de description, placer la définition des 3 fichiers dans une balise `<CompressedFile>`, comportant une sous-balise `<Name>` avec le nom du fichier compressé :

    <ImgSoundFiles>
        <CompressedFile> <Name> data1.cul </Name>
            <LoadImg> Collines </LoadImg>
            <LoadImg> Piaf </LoadImg>
            <LoadSnd> Croa </LoadSnd>
        </CompressedFile>
    </ImgSoundFiles>

L'ordre des fichiers dans `<CompressedFile>` est devenu important (il ne l'était pas initialement). Il doit correspondre à l'ordre dans le fichier `concat_1.txt`.

### Étape 6 : Vérification

Supprimer les 2 fichiers images et le fichier sons (mais pas `data1.cul`). Lancer le visionnage du dessin animé. Cela devrait fonctionner de la même manière qu'au départ.

### Ajout d'autres fichiers

Il est ensuite possible d'ajouter dans le dessin animé d'autres fichiers images et sons non compressés. Il faut ajouter les balises `<LoadImg>` et `<LoadSnd>` dans `</ImgSoundFiles>`, au début ou à la fin, mais pas dans la balise `</CompressedFile>`.

Le fichier `data1.cul` peut être recréé, en y ajoutant/modifiant/supprimant d'autres fichiers. Pour cela, reprendre les étapes précédentes.

Il est également possible d'ajouter un autre fichier compressé au dessin animé, avec d'autres images et sons. Pour cela, reprendre les étapes précédentes, mais avec un autre fichier de définition, qui pourrait s'appeler `concat_2.txt`. La balise `<ImgSoundFiles>` aura alors un contenu de ce genre :

    <ImgSoundFiles>
        <CompressedFile> <Name> data1.cul </Name>
            <LoadImg> Collines </LoadImg>
            <LoadImg> Piaf </LoadImg>
            <LoadSnd> Croa </LoadSnd>
        </CompressedFile>
        <CompressedFile> <Name> data2.cul </Name>
            <LoadImg> AutreImage </LoadImg>
            <LoadSnd> AutreSonA </LoadSnd>
            <LoadSnd> AutreSonB </LoadSnd>
        </CompressedFile>
    </ImgSoundFiles>

Une fois les fichiers .cul créés, les fichiers `concat_1.txt` et `concat_2.txt` ne sont pas nécessaire pour jouer le dessin animé.


## extract_files

Cet outil permet de reprendre les fichiers sons et images à partir des fichiers .cul.

### Situation initiale

Un dessin animé qui fonctionne, avec un ou plusieurs fichiers .cul, ainsi qu'un fichier de description. Les fichiers originaux d'images et de sons ne sont pas présents.

### Étape 1 : Création du fichier de définition d'extraction

Dans le répertoire du dessin animé, copier le fichier de description, en lui donnant le nom : `List_ImgSons.zob`. Il faut que ce soit obligatoirement ce nom là, désolé.

Éventuellement, supprimer dans ce fichier les balises `<LoadData>`, `<Procedure>`, `<Film>` et leur contenu. Elles ne sont pas nécessaires pour l'extraction.

### Étape 2 : Copie de l'utilitaire

Dans le répertoire du dessin animé, copier le fichier `code/extract_files/extract_files.exe` qui se trouve dans ce repository. Le fichier `zlib1.dll` est également nécessaire. Mais si le dessin animé fonctionne, il est déjà présent dans le répertoire.

### Étape 3 : Exécution de l'extraction

Double-cliquer sur le fichier `extract_files.exe` précédemment copié.

À la fin de l'exécution, un sous-répertoire `FilmData` a été créé dans le répertoire du desin animé, contenant les fichiers images et sons qui ont été extraits de tous les fichiers .cul.


## xml_optimizer

Cet outil permet de diminuer la taille des fichiers XML de description de dessin animé, et de permettre un chargement initial plus rapide. Attention, cette optimisation rend le fichier très difficilement lisible pour des humains. Si vous effectuez cette optimisation, il est conseillé de distribuer les deux versions du fichier XML : l'optimisée et la normale.

À noter qu'avec les performances des ordinateurs actuels, cette optimisation n'a plus vraiment de raison d'être.

De plus, l'optimisation nécessite une opération manuelle pour corriger le fichier.

## Situation initiale

Un dessin animé qui fonctionne, avec des fichiers images et sons qui peuvent être compressés ou pas. Pour l'exemple, on dira que le fichier de description s'appelle `example.xml`

### Étape 1 : Copie de l'utilitaire

Dans le répertoire du dessin animé, copier le fichier `code/xml_optimizer/xml_optimizer.exe` qui se trouve dans ce repository.

### Étape 2 : Exécution de l'optimisation

Ouvrir une console de commande DOS, et exécuter les instructions suivantes

    cd {le_repertoire_du_dessin_anime}
    xml_optimizer.exe example.xml example_optim.xml

Un nouveau fichier a été créé `example_optim.xml`. Il s'agit du fichier de description du film, optimisé.

Le seul problème étant que ce fichier n'est pas immédiatement fonctionnel.

### Étape 3 : Correction du fichier optimisé

Ouvrir `example_optim.xml` avec un éditeur de texte, et effectuer les modifications suivantes :

1) Remplacer la chaîne `a<SPLASH>` par `<SPLASH>`. (Il faut enlever le "a")

2) Pour tous les fichiers compressés .cul mentionnés, remplacer les chaînes `<CompressedFile><Name>{identifiant_bidon}</Name>` par `<CompressedFile><Name>{nom_original_du_fichier_cul}</Name>`. `{identifiant_bidon}` est une suite quelconque de lettres/chiffres, et `{nom_original_du_fichier_cul}` est le nom du fichier compressés tel qu'il était écrit au départ.

3) Pour tous les fichiers images non compressées, remplacer les chaînes `<LoadImg>{identifiant_bidon}</LoadImg>` par `<LoadImg>{nom_original_du_fichier_png}</LoadImg>`. Attention, il faut reporter ce remplacement dans toutes les balises `<ImageSource>{identifiant_bidon}</ImageSource>`. Chaque "identifiant bidon" correspond à un "nom original de .png", il faut refaire les correspondances.

4) Pour tous les fichiers sons non compressée, remplacer les chaînes `<LoadSnd>{identifiant_bidon}</LoadSnd>` par `<LoadSnd>{nom_original_du_fichier_wav}</LoadSnd>`. Attention, il faut reporter ce remplacement dans toutes les balises `<PlaySound>{identifiant_bidon}</PlaySound>`. Chaque "identifiant bidon" correspond à un "nom original de .wav", il faut refaire les correspondances.

Lorsque ces opérations sont terminés, le dessin animé peut être visionné avec le fichier `example_optim.xml`.

