#!/bin/bash
#script que reciba como argumento un fichero de texto que contendr ́a una serie
#de direcciones IP de servidores DNS y realizar ́a un ping a cada uno de ellos para comprobar la
#latencia media de los mismos. Adem ́as, se pasar ́an otros dos argumentos que indicar ́an el n  ́umero
#de pings realizados a cada IP y el timeout.
#ping -c 1 8.8.8.8
#./ejercicio2.sh ips.txt 1 1

array=($(cat /home/francis/Escritorio/Programacion/PAS/P2/ficherosPractica/$1))

declare -a array1
declare -a array2
declare -a array3
STR=0
STR1=0
STR4=0
x=0
z=0
for i in "${array[@]}"
do
	array1[$STR]=$(timeout $3 ping -c $2 "${array[$STR]}" | sed -r -n -e 's/^([^ ]+)[ ]+([^ ]+)[ ]+([^ ]+)[ ]+([^:]+)[: ]+([^ ]+)[ ]+([^ ]+)[ ]+([^=]+)[=]+([^\.]+)[\.]+([^ ]+)/\4  \8,\9/p')
	
	if [ "${array1[$STR]}" ];
	then 
	array3[$STR4]=$(echo "${array1[$STR]}")
	let STR4=$STR4+1
	else 
		STR3=($(echo ""${array[$STR]}""))
		array2[$STR1]=$(echo "$STR3")
		
		let STR1=$STR1+1
	fi
	
	let STR=$STR+1
done 

for i in "${array3[@]}"
do
	echo ""${array3[$z]}" "
	let z=$z+1
done | sort -n -k 2


for i in "${array2[@]}"
do
	echo "La IP "${array2[$x]}" no respondio en $2 segundos."
	let x=$x+1
done
