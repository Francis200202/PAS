/*Implemente un programa en C usando tuberías similar a los existentes en los ficheros
pipe.c y pipe2.c, pero en este caso que un proceso genere dos números aleatorios flotantes
y envie la suma de ellos al otro proceso para que éste muestre su resultado.*/
#include <stdio.h>
#include <stdlib.h> //exit, rand, srand
#include <unistd.h> //pipe, close, fork, usleep, read, write, getpid, getppid
#include <time.h>
#include <sys/wait.h> //wait
#include <errno.h> //Control de errores
#include <string.h> //strerror

int main() 
{
	// Para realizar el fork
	pid_t rf;
	int flag, status;
	// Para controlar los valores devueltos por las funciones (control de errores)
	int resultado;
	// Lo que vamos a leer y escribir de la tubería
	float numeroAleatorio;
	float suma = 0;
	// Descriptores de los dos extremos de la tubería
	int fileDes[2];
	// Iterador
	int i=0;

	// Creamos la tubería
	resultado = pipe(fileDes);
	if(resultado==-1)
	{
		printf("\nERROR al crear la tubería.\n");
		exit(1);
	}
	
	rf = fork();
	switch (rf)
	{
		case -1:
			printf ("No se ha podido crear el proceso hijo...\n");
			exit(EXIT_FAILURE);
		case 0:
			printf ("[HIJO]: Mi PID es %d y mi PPID es %d\n", getpid(), getppid());
			
			close(fileDes[1]);
	
			//Recibimos un mensaje a través de la cola
			resultado = read( fileDes[0], &suma, sizeof(float));
				
			if(resultado != sizeof(float))
			{
				printf("\n[HIJO]: ERROR al leer de la tubería...\n");
				exit(EXIT_FAILURE);
			}
			// Imprimimos el campo que viene en la tubería
			printf("[HIJO]: Leo la suma %f de dos numeros aleatorios de la tubería.\n", suma);

			// Cerrar el extremo que he usado
			printf("[HIJO]: Tubería cerrada ...\n");
			close(fileDes[0]);
			break;

		default:
			printf ("[PADRE]: Mi PID es %d y el PID de mi hijo es %d \n", getpid(), rf);
			
			close(fileDes[0]);
			
			srand(time(NULL)); // Semilla de los números aleatorios establecida a la hora actual
			
			for(i=0; i<2; i++)
			{			
				// Rellenamos los campos del mensaje que vamos a enviar
				numeroAleatorio = (float)(rand()%5000)/(float)(rand()%50); //Número aleatorio entre 0 y 4999
				suma = numeroAleatorio + suma;
				
				printf("[PADRE]: Genero un número aleatorio %f en la tubería...\n", numeroAleatorio);
			}

			printf("[PADRE]: Escribo la suma %f de 2 numeros aleatorios en la tubería...\n", suma);
			// Mandamos el mensaje
			resultado = write( fileDes[1], &suma, sizeof(float));
				
			if(resultado != sizeof(float))
			{
				printf("\n[PADRE]: ERROR al escribir en la tubería...\n");
				exit(EXIT_FAILURE);
			}
			
			
			// Cerrar el extremo que he usado
			close(fileDes[1]);
			printf("[PADRE]: Tubería cerrada...\n");
			
			/*Espera del padre a los hijos*/
	        while ( (flag=waitpid(-1,&status,WUNTRACED | WCONTINUED)) > 0 ) 
			{
    			if (WIFEXITED(status)) 
    			{
	    			printf("Proceso Padre %d, hijo con PID %ld finalizado, status = %d\n", getpid(), (long int)flag, WEXITSTATUS(status));
    			} 
    			else if (WIFSIGNALED(status))  
    			{
	   			printf("Proceso Padre %d, hijo con PID %ld finalizado al recibir la señal %d\n", getpid(), (long int)flag, WTERMSIG(status));
    			} 
    			else if (WIFSTOPPED(status))  //Para cuando se para un proceso. Con wait() no nos serviria.
    			{
	    			printf("Proceso Padre %d, hijo con PID %ld parado al recibir la señal %d\n", getpid(), (long int)flag,WSTOPSIG(status));
    			} 
    			else if (WIFCONTINUED(status))  //Para cuando se reanuda un proceso parado. Con wait() no nos serviria.
    			{
	    			printf("Proceso Padre %d, hijo con PID %ld reanudado\n", getpid(), (long int) flag);		  
    			}
			}

			if (flag==(pid_t)-1 && errno==ECHILD)
			{
    			printf("Proceso Padre %d, no hay mas hijos que esperar. Valor de errno = %d, definido como: %s\n", getpid(), errno, strerror(errno));
			}
			else
			{
    			printf("Error en la invocacion de wait o waitpid. Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
    			exit(EXIT_FAILURE);
			}				 
	}
	exit(EXIT_SUCCESS);
}