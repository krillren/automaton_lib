#!/usr/bin/env bash

if [ "$#" != 1 ]; then
    echo "Saisir le nom du test en argument"
    exit 1
fi

echo "Copie du test : '$1'"

cp ../testfa.cc ./test/$1.cc

echo "Vous pouvez maintenant trouver votre fichier de test partageable dans le dossier test"
echo "Bisous"