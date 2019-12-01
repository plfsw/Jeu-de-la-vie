# Jeu de la vie v0.2.0

Implémentation en C du jeu de la vie, l'automate cellulaire de [John Conway](https://fr.wikipedia.org/wiki/John_Horton_Conway).  

## Principe du jeu de la vie 
Le jeu de la vie n'est pas un jeu dans le sens habituel du terme puisque le joueur
ne fait qu'établir les règles du jeu ainsi que la grille de départ. Les cellules
de la grille évoluent ensuite en suivant des règles très simples:
* Une cellule morte devient vivante au tour suivant si et seulement si trois de 
ses voisines sont vivantes.
* Une cellule vivante reste vivante au tour suivant si et seulement si deux ou 
trois de ses voisines sont vivnates ou si elle a été vivante huit tours de suite.

A partir de ces règles initiales simples, on arrive à observer d'structures,
certaines capables de se déplacer, d'autres de générer d'autres structures, etc...

Il a été découvert que le jeu de la vie est capable d'implémenter des machines de
turing dans le jeu de la vie à partir des grilles initiales d'une complexité évidente. 
Il est alors possible d'implémenter [le jeu de la vie dans le jeu de la vie](https://youtu.be/xP5-iIeKXE8)...

## Utilisation

Compiler le jeu de la vie:
```bash
make
```

Vous pouvez aussi compiler en mode texte si vous n'avez pas la bibliothèque cairo sur votre machine:
```bash
make MODE=TEXT 
```




Supprimer les fichiers générés par la compilation:
```bash
make clean
```
Si vous désirez compiler en mode texte mais que vous avez par avant compilé en mode graphique ou vice versa, il est nécessaire de supprimer ces fichiers.

Supprimer la bibliothèque générée:
```bash
make cleanlib
```

Lancer le jeu de la vie:
```bash
./main grilles/grilleX.txt
```
Pour faire évoluer la grille, appuyez sur `clique gauche` ou sur `entrée` en mode texte.   
![Demonstration de l'evolution](https://i.imgur.com/j7sQv6W.gif)  
Pour charger une nouvelle grille, appuyez sur `n`. Ensuite, le chemin vers la nouvelle grille.   
![Demonstration du changement de grille](https://i.imgur.com/HRa5B03.gif)    
Pour activer/désactiver le mode cyclique, appuyez sur `c`.  
![Demonstration du mode cyclique](https://i.imgur.com/Jpg5Bvc.gif)  
Pour activer/désactiver le mode vieillissement, appuyez sur `v`.   
![Demonstration du vieillissement](https://i.imgur.com/8WMKHHX.gif)  
Pour afficher la périodicité d'une grille, appuyez sur `o`.  
![Demonstration du calcul de la période](https://i.imgur.com/EdJ5a97.gif)  
Pour quitter le jeu de la vie, appuyez sur `clique droit` ou sur `q` en mode texte.  
## Nom des versions

vX.Y.Z  

X: Nouvelle version majeure  
Y: Ajouts majeurs  
Z: Ajouts mineurs   
