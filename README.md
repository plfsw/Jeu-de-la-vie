# Jeu de la vie

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
![Demonstration de l'evolution](images/ev.gif)
Pour charger une nouvelle grille, appuyez sur `n`. Ensuite, tapez `grilles/grilleX.txt`.   
![Demonstration du changement de grille](images/n.gif)  
Pour activer/désactiver le mode cyclique, appuyez sur `c`.  
![Demonstration du mode cyclique](images/cycle.gif)
Pour activer/désactiver le mode vieillissement, appuyez sur `v`.   
![Demonstration du vieillissement](images/vi.gif)
