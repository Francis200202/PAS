#!/bin/bash
#script que, utilizando el comando df, muestre la siguiente informaci  ́on
#./ejercicio6.sh 5
#df | sed -r -n -e '2,$s/(^[^ ]+[ ]+[^ ]+[ ]+[^ ]+[ ]+[^ ]+[ ]+[^ ]+[ ]+[^ ]+)/\1/p'


echo "1) Sistemas de ficheros cuyo numero de bloques tenga al menos $1 cifras"
df | sed -r -n -e '2,$s/(^[^ ]+[ ]+[0-9]{'$1',}[ ]+[^ ]+[ ]+[^ ]+[ ]+[^ ]+[ ]+[^ ]+)/\1/p'

echo -e "\n2) Sistemas de ficheros cuyo porcentaje de uso sea inferior al 10 %"
df | sed -r -n -e '2,$s/(^[^ ]+[ ]+[^ ]+[ ]+[^ ]+[ ]+[^ ]+[ ]+.%[ ]+[^ ]+)/\1/p'

echo -e "\n3) Sistemas de ficheros cuyo porcentaje de uso sea de al menos el 90 %"
df | sed -r -n -e '2,$s/(^[^ ]+[ ]+[0-9]{1,}[ ]+[^ ]+[ ]+[^ ]+[ ]+[ 1][90][0-9]%[ ]+[^ ]+)/\1/p'
