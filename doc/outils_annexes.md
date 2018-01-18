# Outils annexes

L'utilisation de ces outils n'est pas nécessaire pour créer ses propres dessins animés. Mais ils facilitent leur distribution et leur transmission.

Si vous utilisez l'antivirus Avast, le premier lancement de chacun de ces outils risque d'émettre un message d'avertissement, car ce ne sont pas des .exe très répandus. Il faut juste attendre un peu que l'analyse de l'exécutable par Avast se termine.


## Sommaire

 - [**concat_file**](#concat_file)
     + [Situation initiale](#situation-initiale)
     + [Étape 1 : définition des fichiers à compresser](#%C3%89tape-1--d%C3%A9finition-des-fichiers-%C3%A0-compresser)
     + [Étape 2 : Copie de l'utilitaire](#%C3%89tape-2--copie-de-lutilitaire)
     + [Étape 3 : Création du fichier .cul](#%C3%89tape-3--cr%C3%A9ation-du-fichier-cul)
     + [Étape 4 : Compression du fichier](#%C3%89tape-4--compression-du-fichier)
     + [Étape 5 : Modification de la description du dessin animé](#%C3%89tape-5--modification-de-la-description-du-dessin-anim%C3%A9)
     + [Étape 6 : Vérification](#%C3%89tape-6--v%C3%A9rification)
     + [Ajout d'autres fichiers](#ajout-dautres-fichiers)
 - [**extract_files**](#extract_files)
     + [Situation initiale](#situation-initiale-1)
     + [Étape 1 : Création du fichier de définition d'extraction](#%C3%89tape-1--cr%C3%A9ation-du-fichier-de-d%C3%A9finition-dextraction)
     + [Étape 2 : Copie de l'utilitaire](#%C3%89tape-2--copie-de-lutilitaire-1)
     + [Étape 3 : Exécution de l'extraction](#%C3%89tape-3--ex%C3%A9cution-de-lextraction)
 - [**xml_optimizer**](#xml_optimizer)
     + [Situation initiale](#situation-initiale-2)
     + [Étape 1 : Copie de l'utilitaire](#%C3%89tape-1--copie-de-lutilitaire)
     + [Étape 2 : Exécution de l'optimisation](#%C3%89tape-2--ex%C3%A9cution-de-loptimisation)
     + [Étape 3 : Correction du fichier optimisé](#%C3%89tape-3--correction-du-fichier-optimis%C3%A9)


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

La première ligne indique le nom du fichier compressé à créer. Les lignes suivantes indiquent les noms des fichiers à compresser, l'ordre est important.

### Étape 2 : Copie de l'utilitaire

Le fichier `code/concat_files/concat_files.exe` qui se trouve dans ce repository doit être copié dans le répertoire du dessin animé à compresser.

### Étape 3 : Création du fichier .cul

Glisser-déplacer le fichier `concat_1.txt` sur l'utilitaire `concat_files.exe`, ou bien exécuter la commande suivante dans une console DOS :

    concat_files.exe concat_1.txt

Un fichier `data1.cul` a été créé dans le répertoire du dessin animé.

### Étape 4 : Compression du fichier

Compresser `data1.cul` au format gz, à l'aide de 7-zip (ou d'un autre logiciel).

Le fichier compressé doit avoir le même nom : `data1.cul`. On perd donc l'ancien fichier. Une sauvegarde peut être faite, mais ce n'est pas nécessaire.

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

Supprimer les 2 fichiers images et le fichier sons, mais pas `data1.cul`. Lancer le visionnage du dessin animé. Cela devrait fonctionner de la même manière qu'initialement.

### Ajout d'autres fichiers

Un dessin animé peut comporter à la fois des images/sons compressés et non compressés. Les balises `<LoadImg>` et `<LoadSnd>` des fichiers non compressés peuvent être placés n'importe où dans `</ImgSoundFiles>`, mais pas dans une balise `</CompressedFile>`.

Le fichier `data1.cul` peut être recréé, en y ajoutant/modifiant/supprimant d'autres fichiers. Pour cela, reprendre les étapes précédentes.

Il est également possible d'ajouter d'autres fichiers compressés. La balise `<ImgSoundFiles>` pourrait alors ressembler à ceci :

    <ImgSoundFiles>

        <CompressedFile> <Name> data1.cul </Name>
            <LoadImg> Collines </LoadImg>
            <LoadImg> Piaf </LoadImg>
            <LoadSnd> Croa </LoadSnd>
        </CompressedFile>

        <LoadImg> Image_pas_compresse </LoadImg>
        <LoadSnd> Son_pas_compresse </LoadSnd>

        <CompressedFile> <Name> data2.cul </Name>
            <LoadImg> Autre_Image </LoadImg>
            <LoadSnd> Autre_Son_A </LoadSnd>
            <LoadSnd> Autre_Son_B </LoadSnd>
        </CompressedFile>

    </ImgSoundFiles>

Une fois les fichiers .cul créés, les fichiers de définition de compression (`concat_1.txt` et autres) ne sont pas nécessaire pour jouer le dessin animé.


## extract_files

Cet outil permet de reprendre les fichiers sons et images à partir des fichiers .cul.

### Situation initiale

Un dessin animé qui fonctionne, avec un ou plusieurs fichiers .cul. Les fichiers originaux d'images et de sons ne sont pas présents.

### Étape 1 : Création du fichier de définition d'extraction

Copier le fichier de description du dessin animé, en lui donnant le nom : `List_ImgSons.zob`. Il doit être dans le même répertoire, et doit avoir obligatoirement ce nom, désolé.

Éventuellement, supprimer dans ce fichier les balises `<LoadData>`, `<Procedure>`, `<Film>` et leur contenu. Elles ne sont pas nécessaires pour l'extraction.

### Étape 2 : Copie de l'utilitaire

Le fichier `code/extract_files/extract_files.exe` qui se trouve dans ce repository doit être copié dans le répertoire du dessin animé.

Le fichier `zlib1.dll` est également nécessaire. Mais si le dessin animé fonctionne, il est déjà présent.

### Étape 3 : Exécution de l'extraction

Double-cliquer sur le fichier `extract_files.exe`.

À la fin de l'exécution, un sous-répertoire `FilmData` a été créé dans le répertoire du desin animé, contenant les fichiers images et sons extraits à partir de tous les fichiers .cul.


## xml_optimizer

Cet outil permet de diminuer la taille des fichiers XML de description de dessin animé, et de permettre un chargement initial plus rapide. Attention, cette optimisation rend le fichier très difficilement lisible pour des humains. Si vous l'effectuez, il est conseillé de distribuer les deux versions du fichier XML : l'optimisée et la normale.

À noter qu'avec les performances des ordinateurs actuels, cette optimisation n'a plus vraiment de raison d'être.

De plus, elle nécessite des opérations manuelles pour corriger le fichier.

### Situation initiale

Un dessin animé qui fonctionne, avec des fichiers images et sons qui peuvent être compressés ou pas. Supposons que le fichier de description s'appelle `example.xml`

### Étape 1 : Copie de l'utilitaire

Le fichier `code/xml_optimizer/xml_optimizer.exe` qui se trouve dans ce repository doit être copié dans le répertoire du dessin animé à optimiser.

### Étape 2 : Exécution de l'optimisation

Ouvrir une console de commande DOS, et exécuter les instructions suivantes

    cd {le_repertoire_du_dessin_anime}
    xml_optimizer.exe example.xml example_optim.xml

Un nouveau fichier a été créé : `example_optim.xml`. Il s'agit du fichier de description du film, optimisé.

Malheureusement, l'optimiseur n'est pas tout à fait au point, et ce fichier n'est pas immédiatement fonctionnel.

### Étape 3 : Correction du fichier optimisé

Ouvrir `example_optim.xml` avec un éditeur de texte, et effectuer les modifications suivantes :

1) Remplacer la chaîne `a<SPLASH>` par `<SPLASH>`. (Il faut enlever le "a")

2) Pour tous les fichiers compressés .cul, remplacer les chaînes `<CompressedFile><Name>{identifiant_bidon}</Name>` par `<CompressedFile><Name>{nom_original_du_fichier_cul}</Name>`. `{identifiant_bidon}` est une suite quelconque de lettres/chiffres, et `{nom_original_du_fichier_cul}` est le nom du fichier compressé tel qu'il était écrit au départ, avec l'extension ".cul".

3) Pour tous les fichiers images non compressées, remplacer les chaînes `<LoadImg>{identifiant_bidon}</LoadImg>` par `<LoadImg>{nom_original_du_fichier_png}</LoadImg>`. Attention, il faut reporter ce remplacement dans toutes les balises `<ImageSource>{identifiant_bidon}</ImageSource>`. Chaque "identifiant bidon" correspond à un "nom original de .png", il faut refaire les correspondances. L'extension ".png" ne doit pas être écrite.

4) Pour tous les fichiers sons non compressée, remplacer les chaînes `<LoadSnd>{identifiant_bidon}</LoadSnd>` par `<LoadSnd>{nom_original_du_fichier_wav}</LoadSnd>`. Attention, il faut reporter ce remplacement dans toutes les balises `<PlaySound>{identifiant_bidon}</PlaySound>`. Chaque "identifiant bidon" correspond à un "nom original de .wav", il faut refaire les correspondances. L'extension ".wav" ne doit pas être écrite.

Lorsque ces opérations sont terminées, le dessin animé peut être visionné avec le fichier `example_optim.xml`.

