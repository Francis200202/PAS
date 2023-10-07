#!/bin/bash
#listar todos los ficheros de un directorio sin mostrar los sub- directorios pero incluyendo los ficheros que estos puedan contener
#./ejercicio4.sh CarpetaEjemplo | nl -n ln

STR1="$(find $1 -name "*.*")"
array=($(echo "$STR1"))

for i in "${array[@]}" 
do
	chars=$(echo "$(basename "$i")" | wc -m)
	let chars=$chars-1
	echo "$(basename "$i")		$chars" 
		
done
