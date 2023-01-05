# Project Mansuba


>## Sommaire
>
>- [Description du projet](#description-du-projet)
>- [Prérequis](#prérequis)
>- [Installation](#installation)
>- [Utilisation](#utilisation)
>    - [Compilation](#compilation)
>    - [Execution](#execution)
>    - [Tests](#tests)
>    - [Nettoyage](#nettoyage)
>- [Remerciements](#tests)

---


## Description du projet

Ce projet à pour but de créer un "proto-jeu" de plateaux permettant de jouer des parties de jeux de plateaux divers. L'objectif étant d'obtenir un jeu générique très facilement modifiable et paramétrable.
Il répond au [sujet Mansuba](https://www.labri.fr/perso/renault/working/teaching/projets/2022-23-S5-Mansuba.php) réalisé dans le cadre du projet de semestre 5 proposés aux étudiants de l'ENSEIRB-MATMECA.
Le dépot est disponible sur la [forge de l'école](
https://thor.enseirb-matmeca.fr/ruby/projects/projetss5).


## Prérequis

Ce projet necessite l'installation de `git`, `make` ainsi que le compilateur `gcc`.
```sh
sudo apt-get install git
sudo apt-get install make
sudo apt-get install gcc
```


## Installation

Avant de commencer, il est neccessaire de cloner le dépot git disponible sur la forge de l'ENSEIRB-MATMECA.
```sh
git clone https://<user>@thor.enseirb-matmeca.fr/git/projetss5-17132
cd projetss5-17132
```


## Utilisation


### Compilation

Par défaut, les dimenssions du monde sont de 10 par 10. Cependant il est possible d'indiquer des dimensions personnaliséés durant la compilation :
```sh
make project WIDTH=<width> HEIGHT=<height>
```
Une fois la compilation effectué, un executable est disponible sous le nom de `project`.


### Execution

Plusieurs options sont disponibles lors de l'éxecution, si les arguments des options sont incorrectes, le programme prendra en compte les valeurs par défaut.
```
-s <entier>: Initialise le générateur aléatoire.            (défaut: aléatoire)
-t <s/c>: Fixe le type de victoire.                         (défaut: simple)
-m <entier>: Fixe le nombre maximal de tours.               (défaut: 2 fois la taille du monde)
-e <entier>: Active/Désactive les changements de terrains.  (défaut: racine carrée de la taille du monde)
```

Elle sont à spécifier après le nom de l'executable.
```sh
./project [Options]
```


### Tests

Des tests sont disponibles afin de vérifier le bon fonctionement du logiciel. Ils sont regroupés par fichiers et peuvent être lancées **individuelements** ou **ensemble**. \
Pour les lancer individuelements, on peut utiliser les commandes.
```sh
make test_<fichier>
./test_<fichier>
```
Les différents fichiers testables sont :
- geometry
- world
- neighbors
- sets
- pawns
- players
- world_ext
- game

Pour **compiler** et **éxectuer** tout les tests en même temps, on utilisera la commande :
```sh
make test
```

### Nettoyage

Les fichiers de compilations ainsi que les executables peuvent être supprimé du dépot avec la commande :
```sh
make clean
```

## Remerciements
