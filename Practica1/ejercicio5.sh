#!/bin/bash
#liste todos los ficheros que se encuentren dentro de dicho directorio que hayan sido modificados en las N horas anteriores
#./ejercicio5.sh <ruta_directorio> <num_horas>
let n=$2*60
find $1 -type f -mmin -$n
