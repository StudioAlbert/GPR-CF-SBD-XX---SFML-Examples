# GPR-CF-SBD — Exemples SFML

Le code des séances SBD : dix-neuf petits programmes SFML 3, un par idée, chacun dans son
répertoire avec sa cible CMake.

## Compiler

```bash
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

SFML 3.1.0 vient de **vcpkg**, comme dans les projets des étudiants : `vcpkg.json` dit ce qu'il
faut, et vcpkg l'installe à la configuration. Comptez quelques minutes la première fois, puis
c'est en cache. Il faut CMake 3.28 ou plus récent, vcpkg, et un compilateur C++23 (MSVC ici).

Sous CLion, le panneau **Vcpkg** met la toolchain en place et la ligne `-DCMAKE_TOOLCHAIN_FILE`
devient inutile.

Une seule cible à la fois :

```bash
cmake --build build --target Events-a
```

L'exécutable sort dans `build/<Cible>/`, avec le `data/` de la cible copié à côté — les chemins
du code sont relatifs au répertoire de l'exécutable.

## Les cibles

| Séance | Cible | Ce qu'elle montre | Au clavier |
|---|---|---|---|
| SBD-01 | `HelloWorld` | la fenêtre, la boucle de jeu, la fermeture propre | `Échap` |
| SBD-01 | `Graphics` | une forme, son contour, son origine ; la souris la déplace | — |
| SBD-02 | `Events-a` | la boucle d'événements : fermeture, focus, redimensionnement | — |
| SBD-02 | `Events-b` | la souris : position, clic, et un déplacement lissé | clic : change la forme |
| SBD-02 | `Events-c` | l'état du clavier lu directement, hors boucle d'événements | flèches |
| SBD-02 | `Events-d` | la manette : axes, zone morte, découpe d'une tuile | manette 0 |
| SBD-02 | `Audio` | une musique en flux, deux effets, le volume | `↑` `↓` `Espace` `X` `Shift+X` |
| SBD-02 | `Sound` | la même chose avec un seul `sf::Sound` dont on change le buffer | `↑` `↓` `Espace` `X` `Shift+X` |
| SBD-03 | `TimeClock` | `sf::Clock`, le temps écoulé, la remise à zéro (console, pas de fenêtre) | — |
| SBD-03 | `Animation` | seize textures et une horloge : l'animation à la main | `Échap` |
| SBD-03 | `AnimationClass` | la même animation, rangée dans une classe | `Espace` : pause, `Échap` |
| SBD-03 | `MoveAndJump` | forces, vitesse, position ; un saut et une collision résolue à la main | `←` `→` `Espace`, clic : téléporte |
| SBD-05 | `Views` | la caméra : on déplace et on zoome la vue, pas le monde | `←` `→`, molette |
| SBD-05 | `Motor` | un shoot'em up minimal : moteur, entités, managers, collisions | flèches, `Espace` : tire, `E` : ennemi |
| SBD-06 | `LevelEditor/01_basic_tilemap_editor` | une tilemap de booléens, éditée à la souris | clic gauche / droit |
| SBD-06 | `LevelEditor/02_player_movement` | le joueur avance case à case et bute sur les murs | `W` `A` `S` `D` |
| SBD-06 | `LevelEditor/03_save_load` | sauvegarder et recharger le niveau en binaire | `F5` : sauve, `F9` : charge |
| — | `OOPHero` | un héros qui est un `sf::Drawable` et un `sf::Transformable` | flèches, `Échap` |
| — | `ConstMethods` | ce qu'une méthode `const` peut et ne peut pas (sans SFML) | — |

`_Resources/sprites/` est la réserve d'images commune : elle ne porte aucune cible.

## Structure

La racine ne porte que `CMakeLists.txt`, `README.md`, `.gitignore` et `.clang-format`. Chaque
répertoire est un programme et une cible, avec son `CMakeLists.txt` d'une ligne utile, son
`data/` s'il en a besoin, et rien d'autre.
