<h1 align="center">QuickSQL compilateur</h1>

<h4 align="center">
 "QuickSQL" Un langage simple pour générer des scripts SQL à l'aide d'une syntaxe simplifiée et intuitive.
<br>
Made during second year of engineering school.
</h4>

<p align="center">
    <img src="https://i.imgur.com/otIz6Hu.png" alt="screenshot">
</p>

## Syntaxe

* Table :
```
NomDeLaTable    [directivesDeLaTable1] [directivesDeLaTable2]

        // les directives des tables servent a definir des prefixes aux noms des colones 
        //ou faire une requete sql simple de select apres la creation de la table
        
        nomColonne1 [type] [contrainte1]  [contrainte2] ....
        nomColonne2 [type] [contrainte1]  [contrainte2] ....
        
        // declaration des colones
```
* View :
```
view  nomDeLaVue  nomTable1  nomTable2 ....
```
Pour plus de details sur la grammaire de langage voir le fichier `QuickSQL_grammar`

## Quelques caractéristiques

* Syntaxe simple.
* Simple à utiliser.
* Vous donne beaucoup d'informations sur vos erreurs pour vous aider à les corriger. 
* Compilation rapide.

## Installation

Vous devez avoir installé **Make** et **GCC** sur votre ordinateur pour compiler le programme.

Pour compiler et exécuter :
* **Sous Linux et Mac :**

1. Exécutez la commande `make` dans le dossier qui contient le `Makefile` pour créer le fichier binaire.
2. Ensuite, vous pouvez lancer le compilateur avec la commande :`./quicksql input_file_path output_file_name`

Par exemple : `./quicksql inputFile.txt output` , cette commande va générer `output.sql` contenant du code SQL.

* **Sous Windows :**
1. Changez la première ligne du fichier `makefile` en `OS := Windows_NT`
2. Exécutez la commande `make` dans le repertoire qui contient le `makefile` pour créer le fichier binaire.
3. Ensuite, vous pouvez lancer le compilateur avec la commande :`./quicksql.exe input_file_path output_file_name`.


Par exemple : `./quicksql.exe inputFile.txt output` , cette commande va générer `output.sql` contenant du code SQL.
