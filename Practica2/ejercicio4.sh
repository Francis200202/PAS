#!/bin/bash
#script que acceda al fichero /etc/passwd y muestre
#				nombre:   password:  uid:      gid:       gecos:     home:      shell
#more /etc/passwd | grep -E '([^:]+)[:]+([^:]+)[:]+([^:]+)[:]+([^:]+)[:]+([^:]+)[:]+([^:]+)[:]+([^:]+)' -o
#more /etc/passwd | grep -E '(....)[:]+([^:]+)[:]+([^:]+)[:]+([^:]+)[:]+([^:]+)[:]+([^:]+)[:]+([^:]+)' -o

echo "1) Usuarios del grupo 46"
more /etc/passwd | grep -E '([^:]+)[:]+([^:]+)[:]+([^:]+)[:](46:)+([^:]+)[:]+([^:]+)[:]+([^:]+)' -o

echo -e "\n2) Usuarios de los grupos 33, 34 o 38"
more /etc/passwd | grep -E '([^:]+)[:]+([^:]+)[:]+([^:]+)[:]+(3[348]:)+([^:]+)[:]+([^:]+)[:]+([^:]+)' -o

echo -e "\n3) Usuarios con UID de 4 dígitos"
more /etc/passwd | grep -E '([^:]+)[:]+([^:]+)[:]+(....)[:]+([^:]+)[:]+([^:]+)[:]+([^:]+)[:]+([^:]+)' -o

echo -e "\n4) Usuarios con nombre de 4 caracteres"
more /etc/passwd | grep -E '(....)[:]+([^:]+)[:]+([^:]+)[:]+([^:]+)[:]+([^:]+)[:]+([^:]+)[:]+([^:]+)' -o
