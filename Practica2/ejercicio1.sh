#!/bin/bash
#muestre el porcentaje de uso de CPU de cada uno de los usuarios que haya conectados en el sistema. Para ello, puedes utilizar la salida del comando ps aux
#ps aux | grep -E '^([^ ]+)[ ]+[^ ]+[ ]+([^ ]+)[ ]' -o

for i in $(ps aux | sed -n -E '2, $s/(^[^ ]+)[ ]+([^ ]+)[ ]+([^ ]+)[ ]+(.*)/\1/p' | sort | uniq)
do
STR=0
	for j in $(ps aux | sed -n -E '2, $s/(^'$i')[ ]+([^ ]+)[ ]+([^ ]+)[ ]+(.*)/\3/p' | sort | uniq)
	do
	STR=$(echo "$j + $STR" | bc)
	done
	echo "El usuario $i esta haciendo un uso la cpu del $STR %"
done
