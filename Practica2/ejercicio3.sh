#!/bin/bash
#script que reciba como argumento el nombre de un fichero de texto y extraiga cada palabra  ́unica que aparezca en ese fichero
z=0
array=($(cat /home/francis/Escritorio/Programacion/PAS/P2/ficherosPractica/texto.txt))
for i in "${array[@]}"
do
	chars=$(echo ""${array[$z]}" " | wc -m)
	let chars=$chars-2
	echo ""${array[$z]}"   $chars" | grep -E '([a-zA-Z]+)' -o
	let z=$z+1
done | sort -f -u | nl -n ln 
