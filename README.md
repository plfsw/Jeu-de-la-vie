# Jeu de la vie v0.2.0

Implémentation en C du jeu de la vie, l'automate cellulaire de [John Conway](https://fr.wikipedia.org/wiki/John_Horton_Conway).

## Utilisation

Compiler le jeu de la vie:
```bash
make
```
Supprimer les fichiers générés par la compilation:
```bash
make clean
```

Lancer le jeu de la vie:
```bash
./main grilles/grilleX.txt
```
Pour faire évoluer la grille, appuyez sur `entrée`.   
![Demonstration de l'evolution](https://images2.imgbox.com/ff/fc/g2xzQ6SB_o.gif)  
Pour charger une nouvelle grille, appuyez sur `n`. Ensuite, tapez `grilles/grilleX.txt`.   
![Demonstration du changement de grille](https://images2.imgbox.com/8e/85/FSpPV2Jg_o.gif)    
Pour activer/désactiver le mode cyclique, appuyez sur `c`.  
![Demonstration du mode cyclique](https://images2.imgbox.com/c8/3b/UAVhQbbG_o.gif)  
Pour activer/désactiver le mode vieillissement, appuyez sur `v`.   
![Demonstration du vieillissement](https://images2.imgbox.com/7e/b5/HQpNTakO_o.gif)  
## Nom des versions

vX.Y.Z  

X: Nouvelle version majeure  
Y: Ajouts majeurs  
Z: Ajouts mineurs   
