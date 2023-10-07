#!/bin/bash
#muestre la siguiente informaci  ́on obtenida a partir del fichero /etc/group:
#nombre:x:gid:lista de usuarios

echo "1) Grupos que contengan al menos 1 usuario ademas del usuario principal"
more /etc/group | grep -E '[^:]+[:]+[^:]+[:]+[^:]+[:]+[^ ]+'

echo -e "\n2) Grupos cuyo nombre empiece por u y acabe en s."
more /etc/group | grep -E '^u.*s[:]+[^:]+[:]+[^:]+[:]+'

echo -e "\n3) Grupos que no contengan ningun usuario adicional"
more /etc/group | grep -E '[^:]+[:]+[^:]+[:]+[^:]+[:]$'

echo -e "\n4) Grupos con GID menor que 100"
more /etc/group | grep -E '[^:]+[:]+[^:]+[:]+(..:)+'

