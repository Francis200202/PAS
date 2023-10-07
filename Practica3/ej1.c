/*Implemente un programa que obtenga e imprima información sobre usuarios del sistema
(todos los campos de la estructura passwd) e información sobre grupos del sistema (GID y
nombre del grupo mediante la estructura group), según las opciones recibidas por la línea de
argumentos.*/
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool esdigito(const char *value)
{
    int i=0;
    while(value[i] != '\0'){
        if(!isdigit(value[i])){
            return false;
        }
        i++;
    }
    return true;

}

int main(int argc, char *argv[]){

    FILE* f;

    char *uvalue = NULL;
    char *gvalue = NULL;
    char *avalue = NULL;
    char *nombre = NULL;
    char *apell1 = NULL;
    char group[255];
    char *nombregrupo = NULL;
    bool aflag = false;
    bool mflag = false;
    bool sflag = false;
    bool hflag = false;
    int u;
    int g;
    int ngp; //Numero de grupo principal
    struct passwd *pw;
    struct group *gr;

    int c;

     static struct option long_options[] = {/* Opciones que no van a actuar sobre un flag */
    //  {<nombre largo>, <recibe/no recibe argumento>, NULL, <nombre corto>}
        {"user", required_argument, NULL, 'u'},
        {"group", required_argument, NULL, 'g'},
        {"active", no_argument, NULL, 'a'},
        {"maingroup", no_argument, NULL, 'm'},
        {"allgroups", no_argument, NULL, 's'},
        {"help", no_argument, NULL, 'h'},
        /* Necesario para indicar el final de las opciones */
        {0, 0, 0, 0}
	};

    
    	while ( (c= getopt_long(argc, argv, "u:g:amsh", long_options, NULL)) != -1) {
        switch (c) {
        case 'u':
            uvalue = optarg;
            break;

        case 'g':
            gvalue = optarg;
            break;

        case 'a':
            aflag = true;
            break;

        case 'm':
            mflag = true;
            break;

        case 's':
            sflag = true;
            break;

        case 'h':
            hflag = true;
            break;


        case '?':
            hflag = true;
            /* getopt_long ya imprime su mensaje de error, no es necesario hacer
             * nada */
            /* Si queremos imprimir nuestros propios errores, debemos poner
            opterr=0, y hacer algo como lo que se expone a continuacion.  if (optopt == 'c')
                    fprintf (stderr, "La opción %c requiere un argumento.\n",
            optopt);*/
            break;

        default:
            abort();
        }
        
    }

    if(hflag == true){
        printf("\nUso del programa: ejercicio1 [opciones]\n");
        printf("Opciones:\n");
        printf("-h, --help                   Imprimir esta ayuda\n");
        printf("-u, --user (<nombre>|<uid>)  Información sobre el usuario\n");
        printf("-a, --active                 Información sobre el usuario activo actual\n");
        printf("-m, --maingroup              Además de info de usuario, imprimir la info de su grupo principal\n");
        printf("-g, --group (<nombre>|<gid>) Información sobre el grupo\n");
        printf("s, --allgroups               Muestra info de todos los grupos del sistema\n\n");
    }

    if(argc < 2){
        aflag = true;
        mflag = true;
    }

    if(uvalue != NULL){
        if(esdigito(uvalue) == false){
                if ((pw = getpwnam(uvalue)) == NULL) //DEVUELVE LA ESTRUCTURA TRAS RECIBIR uvalue COMO PARÁMETRO
                {
                    fprintf(stderr, "Fallo al obtener información de usuario.\n");
                    exit(1);
                }
            }
            else{
                u = atoi(uvalue);
                if ((pw = getpwuid(u)) == NULL) //DEVUELVE LA ESTRUCTURA TRAS RECIBIR uvalue COMO PARÁMETRO
                {
                    fprintf(stderr, "Fallo al obtener información de usuario.\n");
                    exit(1);
                }
            }

            printf("\nUsuario:\n"); 
            printf("Nombre: %s\n", pw->pw_gecos); //No es lo mismo el nombre de usuario asociado a un login que el propio login
            printf("Login: %s\n", pw->pw_name);
            printf("Password: %s\n", pw->pw_passwd);
            printf("UID: %d\n", pw->pw_uid);
            printf("Home: %s\n", pw->pw_dir);
            printf("Shell: %s\n", pw->pw_shell);
            printf("Número de grupo principal: %d\n\n", pw->pw_gid);
            ngp = pw->pw_gid;
    }


    if(gvalue != NULL){
        if(esdigito(gvalue) == false){
                if ((gr = getgrnam(gvalue)) == NULL) //DEVUELVE LA ESTRUCTURA TRAS RECIBIR uvalue COMO PARÁMETRO
                {
                    fprintf(stderr, "Fallo al obtener información de grupo.\n");
                    exit(1);
                }
            }else{
                g = atoi(gvalue);
                if ((gr = getgrgid(g)) == NULL) //DEVUELVE LA ESTRUCTURA TRAS RECIBIR uvalue COMO PARÁMETRO
                {
                    fprintf(stderr, "Fallo al obtener información de grupo.\n");
                    exit(1);
                }
            }

            printf("Grupo:\n"); 
            printf("Nombre del grupo: %s\n", gr->gr_name); 
            printf("GID: %d\n", gr->gr_gid);
            printf("Miembros secundarios: %s\n", *gr->gr_mem);
    }


    if(aflag == true){
        if ((avalue = getenv("USER")) == NULL || (pw = getpwnam(avalue)) == NULL) {
                fprintf(stderr, "Fallo al obtener información de usuario.\n");
                exit(1);
            }
            printf("Usuario:\n"); 
            printf("Nombre: %s\n", pw->pw_gecos); //No es lo mismo el nombre de usuario asociado a un login que el propio login
            printf("Login: %s\n", pw->pw_name);
            printf("Password: %s\n", pw->pw_passwd);
            printf("UID: %d\n", pw->pw_uid);
            printf("Home: %s\n", pw->pw_dir);
            printf("Shell: %s\n", pw->pw_shell);
            printf("Número de grupo principal: %d\n\n", pw->pw_gid);
            ngp = pw->pw_gid;
    }

    if(mflag == true){
        if ((gr = getgrgid(ngp)) == NULL) //DEVUELVE LA ESTRUCTURA TRAS RECIBIR uvalue COMO PARÁMETRO
            {
                    fprintf(stderr, "Fallo al obtener información de grupo.\n");
                    exit(1);
            }

            printf("Grupo:\n"); 
            printf("Nombre del grupo: %s\n", gr->gr_name); 
            printf("GID: %d\n", gr->gr_gid);
            printf("Miembros secundarios: %s\n", *gr->gr_mem);
    }

    if(sflag == true){
        if((f=fopen("/etc/group", "r"))==NULL){
                fprintf(stderr, "\nError: no pudo abrirse el fichero</etc/group>");
                exit(-1);
            }
            while(fgets(group, 255, f) != NULL){

                nombregrupo = strtok(group, ":");
                if ((gr = getgrnam(nombregrupo)) == NULL) //DEVUELVE LA ESTRUCTURA TRAS RECIBIR uvalue COMO PARÁMETRO
                {
                    fprintf(stderr, "Fallo al obtener información de grupo.\n");
                    exit(1);
                }
                printf("\nGrupo:\n"); 
                printf("Nombre del grupo: %s\n", gr->gr_name); 
                printf("GID: %d\n", gr->gr_gid);
                printf("Miembros secundarios: %s\n", *gr->gr_mem);
                
            }

            fclose(f);
    }

    

}