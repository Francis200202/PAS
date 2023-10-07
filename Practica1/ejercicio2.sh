#!/bin/bash
#configurar los permisos de los ficheros y subdirectorios de una determinada carpeta
#./ejercicio2.sh dirEjercicio1 
carpeta=$1
echo -e "Cambiando permisos de directorios...\n"
find $carpeta -not -name "*.*"
STR1="$(find $carpeta -not -name "*.*")"
array=($(echo "$STR1"))

for i in "${array[@]}"
do
	chmod u+rwx,g+rx,g-w,o-rwx $i
done
echo -e "\n"


echo -e "Añadiendo permisos de ejecucion de scripts...\n"
find $carpeta -name "*.sh"
STR2="$(find $carpeta -name "*.sh")"
array=($(echo "$STR2"))

for i in "${array[@]}"
do
	chmod u+x $i
done
echo -e "\n"


echo -e "Restringiendo permisos de ficheros de claves...\n"
find $carpeta -name "*.key"
STR3="$(find $carpeta -name "*.key")"
array=($(echo "$STR3"))

for i in "${array[@]}"
do
	chmod u+rwx,go-rwx $i
done
