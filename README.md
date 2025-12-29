# Simple Shell

## Description
Simple Shell est une implémentation basique d’un interpréteur de commandes UNIX.
Il permet d’exécuter des programmes en mode interactif ou non interactif,
de la même manière que `/bin/sh`.

Ce projet a été réalisé dans le cadre du cursus Holberton School.

## Fonctionnalités
- Exécution de commandes avec chemins absolus
- Recherche des commandes via la variable d’environnement `PATH`
- Mode interactif
- Mode non interactif
- Gestion des erreurs similaire à `/bin/sh`

## Compilation
Le shell est compilé avec :

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
