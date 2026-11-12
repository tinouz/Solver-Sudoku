# Solver-Sudoku

Un solveur de Sudoku en C qui résout une grille 9×9 en appliquant des règles de déduction logique, comme le ferait un humain. Si ces règles ne suffisent pas, il termine par une recherche exhaustive (backtracking).

Deux modes d'exécution sont proposés :

- **Mode classique** : affiche directement la grille résolue.
- **Mode « pas à pas »** : affiche la grille à chaque case remplie (la case modifiée est en couleur), pour suivre le raisonnement étape par étape.

## Prérequis

- `gcc` (C99)
- `make`
- Un terminal qui gère les codes couleur ANSI (Linux, macOS, WSL…)

## Compilation

```bash
make
```

Cette commande produit l'exécutable `sudo`. Pour supprimer les fichiers objets et l'exécutable :

```bash
make clean
```

## Utilisation

### À partir d'un fichier

```bash
./sudo Grilles/V1.txt
```

### Saisie manuelle

```bash
./sudo
```

Le programme demande alors les 81 valeurs une par une, de la case 0 (en haut à gauche) à la case 80 (en bas à droite), ligne par ligne.

Une fois la grille chargée, choisissez le mode :

- `1` puis Entrée : mode classique
- `2` puis Entrée : mode pas à pas (appuyez sur Entrée pour passer à l'étape suivante)

## Format des grilles

Un fichier de grille contient 81 entiers séparés par des espaces ou des retours à la ligne. Les cases vides valent `0`.

```text
0 8 7 0 0 0 5 2 0
9 1 0 5 0 2 0 4 6
2 0 0 0 0 0 0 0 7
0 9 0 0 2 0 0 1 0
0 0 0 1 0 6 0 0 0
0 4 0 0 9 0 0 8 0
6 0 0 0 0 0 0 0 3
5 7 0 3 0 1 0 6 8
0 3 8 0 0 0 9 5 0
```

Le dossier [Grilles/](Grilles/) contient des grilles de test classées par difficulté :

| Fichier | Difficulté |
| --- | --- |
| `V1.txt` | Facile |
| `V2.txt`, `V2_2.txt` | Moyenne |
| `V3.txt`, `V3_2.txt`, `V3_3.txt` | Difficile |
| `diabolique1.txt` à `diabolique3.txt` | Très difficile |
| `grille_pleine.txt` | Grille déjà complète |

## Méthode de résolution

Chaque case vide garde une liste de **candidats** (les chiffres encore possibles). Le solveur applique les règles suivantes en boucle tant qu'elles modifient la grille :

| Règle | Principe |
| --- | --- |
| **R1** – Candidat unique | Une case qui n'a plus qu'un seul candidat prend cette valeur. |
| **R2** – Élimination directe | On retire des candidats d'une case les chiffres déjà placés sur sa ligne, sa colonne et sa région. |
| **R3** – Candidat caché | Si un chiffre n'est possible que dans une seule case d'une ligne, d'une colonne ou d'une région, il y est placé. |
| **R4** – Interaction région / ligne-colonne | Si, dans une région, un candidat n'apparaît que sur une seule ligne (ou colonne), on le retire du reste de cette ligne (ou colonne), hors de la région. |
| **R5** – Configuration en « X » (X-Wing) | Si un candidat n'apparaît que deux fois dans deux lignes (ou colonnes, ou régions) et forme un rectangle, on l'élimine des autres cases des colonnes (ou lignes) concernées. N'est appliquée que lorsque R1 à R4 ne progressent plus. |

Si la grille n'est toujours pas complète, une **recherche exhaustive** récursive (backtracking) termine la résolution.

## Structure du projet

```text
Solver-Sudoku/
├── Src/
│   ├── main.c       # Chargement de la grille, choix du mode, boucle de résolution
│   ├── case.c/.h    # Structure T_case (valeur + candidats) et outils d'indexation
│   ├── grille.c/.h  # Structure T_sudoku, saisie, affichage, vérifications
│   ├── regles.c/.h  # Règles R1 à R5 et recherche exhaustive
│   └── annexe.c/.h  # Couleurs ANSI, effacement de l'écran, vidage de stdin
├── Grilles/         # Grilles de test
├── Sujet_projet.pdf # Énoncé du projet
└── makefile
```
