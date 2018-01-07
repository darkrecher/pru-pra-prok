# Outils annexes

L'utilisation de ces outils n'est pas nécessaire pour créer ses propres dessins animés. Mais ils facilitent leur distribution et leur transmission.


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

Si vous utilisez l'antivirus Avast, il risque d'émettre un message d'avertissement au premier lancement, car ce n'est pas un .exe très répandu. Dans ce cas, il faut attendre un peu que l'analyse du fichier se termine.

À la fin de l'exécution, un sous-répertoire `FilmData` a été créé dans le répertoire du desin animé, contenant les fichiers images et sons qui ont été extraits de tous les fichiers .cul.

