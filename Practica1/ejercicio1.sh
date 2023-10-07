#!/bin/bash 
#generar un directorio con ficheros y subdirectorios
#Ejemplo: ./ejercicio1.sh /home/francis/Escritorio/Programacion/PAS/dirEjercicio1 2 5
if [ -d $1 ];
	then
	echo "Directorio ya existente"
	rm -r -i $1
	fi
mkdir $1
echo "Directorio creado"
let i=1
while [ $i -le $2 ]; do
	STR=`tr -dc A-Za-z0-9 < /dev/urandom | head -c $3`
	STR1=$1"/"$STR
	if [ -d $STR1 ];
	then
	echo "Subdirectorio ya existente"
	rm -r -i $STR1
	fi
	mkdir $STR1
	echo "Subdirectorio creado"
	cd $STR1
	let j=1
	while [ $j -le 4 ]; do
		STR2=`tr -dc A-Za-z0-9 < /dev/urandom | head -c $3`
		case $j in
			1) STR3=$STR2".sh";;
			2) STR3=$STR2".html";;
			3) STR3=$STR2".key";;
			4) STR3=$STR2".txt";;
		esac
		touch $STR3
		let "j=$j+1"
	done
	
	let "i=$i+1"
done
echo "--Ejercicio 1 ejecutado--"

