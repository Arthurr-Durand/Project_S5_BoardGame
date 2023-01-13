# Project Mansuba


>## Sommaire
>
>- [Description du projet](#description-du-projet)
>- [Prérequis](#prérequis)
>- [Installation](#installation)
>- [Utilisation](#utilisation)
>    - [Compilation](#compilation)
>    - [Exécution](#execution)
>    - [Tests](#tests)
>    - [Nettoyage](#nettoyage)
>- [Remerciements](#tests)

---


## Description du projet

Ce projet a pour but de créer un "proto-jeu" de plateaux permettant de jouer des parties de jeux de plateaux divers, l'objectif étant d'obtenir un jeu générique très facilement modifiable et paramétrable.
Il répond au [sujet Mansuba](https://www.labri.fr/perso/renault/working/teaching/projets/2022-23-S5-Mansuba.php) réalisé dans le cadre du projet de semestre 5 proposés aux étudiants de l'ENSEIRB-MATMECA.
Le dépôt est disponible sur la [forge de l'école](
https://thor.enseirb-matmeca.fr/ruby/projects/projetss5).


## Prérequis

Ce projet nécessite l'installation de `git`, `make` ainsi que le compilateur `gcc`.
```sh
sudo apt-get install git
sudo apt-get install make
sudo apt-get install gcc
```


## Installation

Avant de commencer, il est néccessaire de cloner le dépot git disponible sur la [forge de l'ENSEIRB-MATMECA](https://thor.enseirb-matmeca.fr/).
```sh
git clone https://<user>@thor.enseirb-matmeca.fr/git/projetss5-17132
cd projetss5-17132
```


## Utilisation


### Compilation

Par défaut, les dimensions du monde sont de 10 par 10. Cependant, il est possible d'indiquer des dimensions personnalisées durant la compilation :
```sh
make project WIDTH=<width> HEIGHT=<height>
```
Une fois la compilation effectué, un exécutable est disponible sous le nom de `project`.


### Exécution

Plusieurs options sont disponibles lors de l'exécution, si les arguments des options sont incorrects, le programme prendra en compte les valeurs par défaut.
```
-s <entier>: Initialise le générateur aléatoire.            (défaut: aléatoire)
-t <s/c>: Fixe le type de victoire.                         (défaut: simple)
-m <entier>: Fixe le nombre maximal de tours.               (défaut: 2 fois la taille du monde)
-e <entier>: Active/Désactive les changements de terrains.  (défaut: racine carrée de la taille du monde)
```

Elles sont à spécifier après le nom de l'exécutable.
```sh
./project [Options]
```


### Tests

Des tests sont disponibles afin de vérifier le bon fonctionnement du logiciel. Ils sont regroupés par fichiers et peuvent être lancés **individuellements** ou **ensemble**. \
Pour tester un fichier individuellement, on peut utiliser les commandes.
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

Pour **compiler** et **exécuter** tout les tests en même temps, on utilisera la commande :
```sh
make test
```

### Rapport

Un rapport LaTeX est disponible, il peut être compilé dans le fichier `doc/` en utilisant `pdflatex` :
```sh
cd doc/
pdflatex report.tex
```

### Nettoyage

Les fichiers de compilations ainsi que les exécutables peuvent être supprimés du dépôt avec la commande :
```sh
make clean
```

## Remerciements

Un grand merci aux équipes pédagogiques qui nous ont accompagnés dans ce projet. Vos précieux conseils nous ont permis de mener ce projet à un stade aussi avancé.
