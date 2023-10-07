#!/bin/bash
#simule la creacion de nuevos usuarios
#./ejercicio6.sh Francisco
crear_usuario()
{
echo "$1" >>  users.txt
cp -r skel/  /home/francis/Escritorio/Programacion/PAS/homes/$1
echo "Se ha creado el fichero $1"
}

STR=1
array=($(cat users.txt))
for i in "${array[@]}"
do
	if [ "${array[$STR]}" == $1 ];
	then
		echo "El usuario ya existe"
		exit 1
	fi
	let STR=$STR+1
done

crear_usuario $1
