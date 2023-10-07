#!/bin/bash
#copia de seguridad de un determinado directorio y almacenarla en un fichero comprimido.
#./ejercicio3.sh dirEjercicio1 CarpetaTar

STR1="$(date +"%Y%m%d")"
NAME=$1"_"$STR1".tar.gz"
NAMEZIP=$2"/"$NAME
STR2=$(find -name "*$NAME")
STR3=$(pwd)"/"$2
echo $STR3
if [ $STR2 ];
	then
	echo "Ya se ha realizado esta copia hoy ($STR2)"
else
	if [ -d $STR3 ];
	then
	echo " "
	else
		mkdir $2
	fi
	tar -zcvf $NAMEZIP $1
	echo "Copia realizada en $NAMEZIP"
fi

