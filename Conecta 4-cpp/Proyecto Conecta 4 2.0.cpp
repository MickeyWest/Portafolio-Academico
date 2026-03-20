#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <unistd.h> // Para usar usleep
//Variables Globales
int motriz1 [6][7];
int motriz2 [7][8];
int motriz3 [9][9];

//Funciones a usar por Tablero...

//Funciones para mostrar el tablero
void imprimirMatriz1(int matriz[6][7], int filas, int columnas) {
    // Imprimir la fila superior de la matriz
    printf("\t\t\t\t ");
    for(int j = 0; j < columnas+1; ++j) {
        printf("----");
    }
    printf("-\n");

    // Imprimir las filas de la matriz con colores
    for(int i = 0; i < filas; ++i) {
        printf("\t\t\t\t|");
        for(int j = 0; j < columnas; ++j) {
            if(matriz[i][j] == 1) {
                printf(" \033[0;31m%2d\033[0m |", matriz[i][j]); // Rojo
            } else if(matriz[i][j] == 2) {
                printf(" \033[0;33m%2d\033[0m |", matriz[i][j]); // Amarillo
            } else {
                printf(" %2d |", matriz[i][j]); // Color por defecto
            }
        }
        printf("\n\t\t\t\t ");

        // Imprimir la línea divisoria entre filas
        for(int j = 0; j < columnas+1; ++j) {
            printf("----");
        }
        printf("---\n");
    }
    

    
    
    
    printf("\033[35m\t\t\t\t-> 0    1    2    3    4    5    6\n"); // Morado
    printf("\033[0m"); // Restaurar el color original
    

    
    
}
void imprimirMatriz2(int matriz[7][8], int filas, int columnas) {
    // Imprimir la fila superior de la matriz
    printf("\t\t\t\t ");
    for(int j = 0; j < columnas+1; ++j) {
        printf("----");
    }
    printf("-\n");

    // Imprimir las filas de la matriz con colores
    for(int i = 0; i < filas; ++i) {
        printf("\t\t\t\t|");
        for(int j = 0; j < columnas; ++j) {
            if(matriz[i][j] == 1) {
                printf(" \033[0;31m%2d\033[0m |", matriz[i][j]); // Rojo
            } else if(matriz[i][j] == 2) {
                printf(" \033[0;33m%2d\033[0m |", matriz[i][j]); // Amarillo
            } else {
                printf(" %2d |", matriz[i][j]); // Color por defecto
            }
        }
        printf("\n\t\t\t\t ");

        // Imprimir la línea divisoria entre filas
        for(int j = 0; j < columnas+1; ++j) {
            printf("----");
        }
        printf("---\n");
    }
    
    printf("\033[35m\t\t\t\t-> 0    1    2    3    4    5    6    7\n");
    printf("\033[0m"); // Restaurar el color original
    
}
void imprimirMatriz3(int matriz[9][9], int filas, int columnas) {
    // Imprimir la fila superior de la matriz
    printf("\t\t\t\t ");
    for(int j = 0; j < columnas+1; ++j) {
        printf("----");
    }
    printf("-\n");

    // Imprimir las filas de la matriz con colores
    for(int i = 0; i < filas; ++i) {
        printf("\t\t\t\t|");
        for(int j = 0; j < columnas; ++j) {
            if(matriz[i][j] == 1) {
                printf(" \033[0;31m%2d\033[0m |", matriz[i][j]); // Rojo
            } else if(matriz[i][j] == 2) {
                printf(" \033[0;33m%2d\033[0m |", matriz[i][j]); // Amarillo
            } else {
                printf(" %2d |", matriz[i][j]); // Color por defecto
            }
        }
        printf("\n\t\t\t\t ");

        // Imprimir la línea divisoria entre filas
        for(int j = 0; j < columnas+1; ++j) {
            printf("----");
        }
        printf("---\n");
    }
    
        
    printf("\033[35m\t\t\t\t-> 0    1    2    3    4    5    6    7    8\n");
    printf("\033[0m"); // Restaurar el color original
    
}

// Función para comprobar si todas las celdas están llenas
int tableroLleno1(int matriz[6][7], int filas, int columnas) {
    for(int i = 0; i < filas; ++i)
        for(int j = 0; j < columnas; ++j)
            if(matriz[i][j] == 0)
                return 0;
    return 1;
}
int tableroLleno2(int matriz[7][8], int filas, int columnas) {
    for(int i = 0; i < filas; ++i)
        for(int j = 0; j < columnas; ++j)
            if(matriz[i][j] == 0)
                return 0;
    return 1;
}
int tableroLleno3(int matriz[9][9], int filas, int columnas) {
    for(int i = 0; i < filas; ++i)
        for(int j = 0; j < columnas; ++j)
            if(matriz[i][j] == 0)
                return 0;
    return 1;
}

// Función para comprobar si un jugador ha ganado
int jugadorGana1(int matriz[6][7], int filas, int columnas, int color) {
    // Comprobar filas
    for(int i = 0; i < filas; ++i) {
        for(int j = 0; j < columnas - 3; ++j) {
            if(matriz[i][j] == color && matriz[i][j+1] == color && matriz[i][j+2] == color && matriz[i][j+3] == color) {
                return 1;
            }
        }
    }

    // Comprobar columnas
    for(int j = 0; j < columnas; ++j) {
        for(int i = 0; i < filas - 3; ++i) {
            if(matriz[i][j] == color && matriz[i+1][j] == color && matriz[i+2][j] == color && matriz[i+3][j] == color) {
                return 1;
            }
        }
    }

    // Comprobar diagonales ascendentes
    for(int i = 3; i < filas; ++i) {
        for(int j = 0; j < columnas - 3; ++j) {
            if(matriz[i][j] == color && matriz[i-1][j+1] == color && matriz[i-2][j+2] == color && matriz[i-3][j+3] == color) {
                return 1;
            }
        }
    }

    // Comprobar diagonales descendentes
    for(int i = 0; i < filas - 3; ++i) {
        for(int j = 0; j < columnas - 3; ++j) {
            if(matriz[i][j] == color && matriz[i+1][j+1] == color && matriz[i+2][j+2] == color && matriz[i+3][j+3] == color) {
                return 1;
            }
        }
    }

    return 0;
}
int jugadorGana2(int matriz[7][8], int filas, int columnas, int color) {
    // Comprobar filas
    for(int i = 0; i < filas; ++i) {
        for(int j = 0; j < columnas - 3; ++j) {
            if(matriz[i][j] == color && matriz[i][j+1] == color && matriz[i][j+2] == color && matriz[i][j+3] == color) {
                return 1;
            }
        }
    }

    // Comprobar columnas
    for(int j = 0; j < columnas; ++j) {
        for(int i = 0; i < filas - 3; ++i) {
            if(matriz[i][j] == color && matriz[i+1][j] == color && matriz[i+2][j] == color && matriz[i+3][j] == color) {
                return 1;
            }
        }
    }

    // Comprobar diagonales ascendentes
    for(int i = 3; i < filas; ++i) {
        for(int j = 0; j < columnas - 3; ++j) {
            if(matriz[i][j] == color && matriz[i-1][j+1] == color && matriz[i-2][j+2] == color && matriz[i-3][j+3] == color) {
                return 1;
            }
        }
    }

    // Comprobar diagonales descendentes
    for(int i = 0; i < filas - 3; ++i) {
        for(int j = 0; j < columnas - 3; ++j) {
            if(matriz[i][j] == color && matriz[i+1][j+1] == color && matriz[i+2][j+2] == color && matriz[i+3][j+3] == color) {
                return 1;
            }
        }
    }

    return 0;
}
int jugadorGana3(int matriz[9][9], int filas, int columnas, int color) {
    // Comprobar filas
    for(int i = 0; i < filas; ++i) {
        for(int j = 0; j < columnas - 3; ++j) {
            if(matriz[i][j] == color && matriz[i][j+1] == color && matriz[i][j+2] == color && matriz[i][j+3] == color) {
                return 1;
            }
        }
    }

    // Comprobar columnas
    for(int j = 0; j < columnas; ++j) {
        for(int i = 0; i < filas - 3; ++i) {
            if(matriz[i][j] == color && matriz[i+1][j] == color && matriz[i+2][j] == color && matriz[i+3][j] == color) {
                return 1;
            }
        }
    }

    // Comprobar diagonales ascendentes
    for(int i = 3; i < filas; ++i) {
        for(int j = 0; j < columnas - 3; ++j) {
            if(matriz[i][j] == color && matriz[i-1][j+1] == color && matriz[i-2][j+2] == color && matriz[i-3][j+3] == color) {
                return 1;
            }
        }
    }

    // Comprobar diagonales descendentes
    for(int i = 0; i < filas - 3; ++i) {
        for(int j = 0; j < columnas - 3; ++j) {
            if(matriz[i][j] == color && matriz[i+1][j+1] == color && matriz[i+2][j+2] == color && matriz[i+3][j+3] == color) {
                return 1;
            }
        }
    }

    return 0;
}

// Función para verificar si una columna está llena
int columnaLlena1(int matriz[6][7] , int filas, int columna) {
    for(int i = 0; i < filas; ++i) {
        if(matriz[i][columna] == 0) {
            return 0; // La columna no está llena
        }
    }
    return 1; // La columna está llena
}
int columnaLlena2(int matriz[7][8] , int filas, int columna) {
    for(int i = 0; i < filas; ++i) {
        if(matriz[i][columna] == 0) {
            return 0; // La columna no está llena
        }
    }
    return 1; // La columna está llena
}
int columnaLlena3(int matriz[9][9] , int filas, int columna) {
    for(int i = 0; i < filas; ++i) {
        if(matriz[i][columna] == 0) {
            return 0; // La columna no está llena
        }
    }
    return 1; // La columna está llena
}

//Funcion Guardado 
void guardar1(int matriz[6][7] , int filas, int columnas, int columna){
	   for(int i = 0; i < filas; ++i) {
        for(int j = 0; j < columnas; ++j){
        	
        	motriz1[i][j] = matriz[i][j];
        	
		}
         
    }
	
}
void guardar2(int matriz[7][8] , int filas, int columnas, int columna){
	   for(int i = 0; i < filas; ++i) {
        for(int j = 0; j < columnas; ++j){
        	
        	motriz2[i][j] = matriz[i][j];
        	
		}
         
    }
	
}
void guardar3(int matriz[9][9] , int filas, int columnas, int columna){
	   for(int i = 0; i < filas; ++i) {
        for(int j = 0; j < columnas; ++j){
        	
        	motriz3[i][j] = matriz[i][j];
        	
		}
         
    }
	
}

//Funcion Slot
bool motriz_vacio1(int filas, int columnas){
	
	  for(int i = 0; i < filas; ++i) {
        for(int j = 0; j < columnas; ++j){
        	
        
        if(motriz1[i][j]!=0){
        	return false;
		}
        	
		}
        
         
        
        
    }
	return true; 
}
bool motriz_vacio2(int filas, int columnas){
	
	  for(int i = 0; i < filas; ++i) {
        for(int j = 0; j < columnas; ++j){
        	
        
        if(motriz2[i][j]!=0){
        	return false;
		}
        	
		}
        
         
        
        
    }
	return true; 
}
bool motriz_vacio3(int filas, int columnas){
	
	  for(int i = 0; i < filas; ++i) {
        for(int j = 0; j < columnas; ++j){
        	
        
        if(motriz3[i][j]!=0){
        	return false;
		}
        	
		}
        
         
        
        
    }
	return true; 
}


//Funcion Cargado
void cargar1(int matriz[6][7] , int filas, int columnas){
	
	  for(int i = 0; i < filas; ++i) {
        for(int j = 0; j < columnas; ++j)
          matriz[i][j] = motriz1[i][j];
        
    }
	
	
}
void cargar2(int matriz[7][8] , int filas, int columnas){
	
	  for(int i = 0; i < filas; ++i) {
        for(int j = 0; j < columnas; ++j)
          matriz[i][j] = motriz2[i][j];
        
    }
	
	
}
void cargar3(int matriz[9][9] , int filas, int columnas){
	
	  for(int i = 0; i < filas; ++i) {
        for(int j = 0; j < columnas; ++j)
          matriz[i][j] = motriz3[i][j];
        
    }
	
	
}


int main() {
	
	srand(time(NULL));

    int turno;	  
 	int tablero_6x7[6][7]; // Tablero de 6 filas y 7 columnas
	int tablero_7x8[7][8]= {0}; // Tablero de 7 filas y 8 columnas
	 // Inicializa todos los elementos a 0
	int tablero_9x9[9][9]= {0}; // Tablero de 9 filas y 9 columnas
    int victory=0, Seleccion1;
    int filas, columnas;
	int opcion, opcion1, key, salida,Seleccion,guardaturno;
	bool Llave=false; 
	char apodo1[50]; // Asumiendo que el apodo no excederá los 49 caracteres + el carácter nulo
    char apodo2[50];
    char c;
    int ganador=0;
    int puntuacionA=0, puntuacionB=0, puntuacionC=0, puntuacionD=0;
	

    do {  
//Menu Principal


	salida=0;
	system("cls"); 
    printf("\t\t\t\t==================== MENU ====================\n");
    printf("\t\t\t\t1. Jugador VS Jugador\n");
    printf("\t\t\t\t2. Jugador VS Computadora\n");
    printf("\t\t\t\t3. Computadora VS Computadora\n");
    printf("\t\t\t\t4. Salir\n");
    printf("\t\t\t\t?. Sabias que si pulsas 99 en vez de una\n");
    printf("\t\t\t\t   columna, guardas y sales partida?\n");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\tPor favor, elige una opcion: ");
    scanf("%d", &opcion);

	 switch(opcion) {
            case 1:{ 
	system("cls"); 
	printf("\t\t\t\t=========== Jugador vs Jugador ==============\n");
	
	int c;
	do {
	    c = getchar();
	} while (c != '\n' && c != EOF);
	
	printf("\t\t\t\tIngrese el primer apodo: ");
    fgets(apodo1, sizeof(apodo1), stdin);
    apodo1[strcspn(apodo1, "\n")] = 0;    
    
    printf("\t\t\t\tIngrese el segundo apodo: ");
    fgets(apodo2, sizeof(apodo2), stdin);
    apodo2[strcspn(apodo2, "\n")] = 0;
	   

		do{
		system("cls"); 
//Menu Primario	JvsJ	
		printf("\t\t\t\t=========== Jugador vs Jugador ==============\n");
	    printf("\t\t\t\t1. Nueva Partida\n");
	    printf("\t\t\t\t2. Cargar Partida\n");
	    printf("\t\t\t\t3. Salir\n");
	    printf("\t\t\t\t==============================================\n");
	    printf("\t\t\t\tPor favor, elige una opcion: ");
	     if(Llave==false){scanf("%d", &Seleccion);}else{printf("\n");}
	    
	    
//Menu Secundario JvsJ

 if(Seleccion==1){
 	
 		system("cls"); 
 	        printf("\t\t\t\t=========== Jugador vs Jugador ==============\n");
 	       
			printf("\t\t\t\t1. Matriz de 6x7\n");
			printf("\t\t\t\t2. Matriz de 7x8\n");
			printf("\t\t\t\t3. Matriz de 9x9\n");
			printf("\t\t\t\t4. Salir\n");
			 printf("\t\t\t\t==============================================\n");
			 printf("\t\t\t\tSeleccione una opcion:");
		    if(Llave==false){scanf("%d", &opcion1);}else{printf("\n");}
	
				    switch(opcion1) {
				        case 1:
				           	Llave=false;
				            filas = 6;
            				columnas = 7;	
				           
				           if (key==0){
				           	  for(int i = 0; i < filas; ++i){
							  for(int j = 0; j < columnas; ++j){
							  tablero_6x7[i][j] = 0;}}}
				         
						           
							// Juego por turnos
							
								    turno = 1;// Jugador 1 comienza
								    
								    if (key==1){turno=guardaturno;} //Carga de Turno
								    
								    while(salida!=1){
									system("cls"); 
										printf("\t\t\t\t=========== Jugador vs Jugador ==============\n\n");
								        imprimirMatriz1(tablero_6x7, filas, columnas);
								        printf("\n\t\t\t\tJ1: %s J2: %s\n", apodo1, apodo2);
								            int color;
											if (turno == 1) {
											    color = 1;  // Jugador 1 elige amarillo (1)
											} else {
											    color = 2;  // Jugador 2 elige rojo (2)
											}
								        
								        
								        int columna;
								        printf("\t\t\t\tTurno del jugador %d.\n", turno);
								        printf("\t\t\t\tElige una columna: ");
								        scanf("%d", &columna);
								        
								        
								         if(columnaLlena1( tablero_6x7,filas,columna)!=1){
								         	
								         	 if (columna!=99){
								        	
								    // Colocar la ficha en la columna elegida
								        for(int i = filas - 1; i >= 0; --i) {
								            if(tablero_6x7[i][columna] == 0) {
								                tablero_6x7[i][columna] = color;
								                ganador = turno;
								                   turno = 3 - turno;
								                   
								                   
								                   
								                break;
								            }
								        }
								        	
										}else {
										guardar1(tablero_6x7, filas, columnas, columna);
										salida=1;
										victory=1;
										guardaturno=turno;	
										} 
								         	
										 }else{
										 	
										 	printf("\t\t\t\tEsta llena");
										
								               getch();
										 }
								       
								        // Comprobar si el tablero se llena sin que ningún jugador logre una victoria
								        if(tableroLleno1(tablero_6x7, filas, columnas)==1) {
								            printf("\t\t\t\tEmpate!\n");
								            salida=1;
								        }
								
								        // Comprobar si el último movimiento ha dado lugar a una victoria
								        if(jugadorGana1(tablero_6x7, filas, columnas, color)==1) {
								                  
								               	system("cls");
								        
								        printf("\t\t\t\t=========== Jugador vs Jugador ==============\n\n");
								        imprimirMatriz1(tablero_6x7, filas, columnas);
								        	
								        printf("\n\t\t\t\tJ1: %s J2: %s\n", apodo1, apodo2);
								        
								        //Debido al cambio por turno
								     
								        
								        printf("\t\t\t\tVictoria del jugador %d!\n", ganador);
								            salida=1;
								            victory=1;
								               getch();
								        }
								
								        // Cambiar de turno
								     key =0;
								    }
						           
				            break;
				        case 2:
				           
						        
				           	Llave=false;
				            filas = 7;
            				columnas = 8;	
				           
				           if (key==0){
				           	  for(int i = 0; i < filas; ++i){
							  for(int j = 0; j < columnas; ++j){
							    tablero_7x8[filas][columnas]= 0;}}}
				         
						           
							// Juego por turnos
							
								    turno = 1;  // Jugador 1 comienza
								    	    if (key==1){turno=guardaturno;} //Carga de Turno
								    while(salida!=1){
					system("cls"); 
								      	printf("\t\t\t\t=========== Jugador vs Jugador ==============\n\n");
								        imprimirMatriz2(tablero_7x8, filas, columnas);
								        printf("\n\t\t\t\tJ1: %s J2: %s\n", apodo1, apodo2);
								            int color;
											if (turno == 1) {
											    color = 1;  // Jugador 1 elige amarillo (1)
											} else {
											    color = 2;  // Jugador 2 elige rojo (2)
											}
								        
								        
								        int columna;
								        printf("\t\t\t\tTurno del jugador %d.\n", turno);
								        printf("\t\t\t\tElige una columna: ");
								        scanf("%d", &columna);
								        
								        
								         if(columnaLlena2( tablero_7x8,filas,columna)!=1){
								         	
								         	 if (columna!=99){
								        	
								    // Colocar la ficha en la columna elegida
								        for(int i = filas - 1; i >= 0; --i) {
								            if(tablero_7x8[i][columna] == 0) {
								                tablero_7x8[i][columna] = color;
								                ganador = turno;
								                   turno = 3 - turno;
								                break;
								            }
								        }
								        	
										}else {
										guardar2(tablero_7x8, filas, columnas, columna);
										salida=1;
										victory=1;
										guardaturno=turno;	
										} 
								         	
										 }else{
										 	
										 	
										 	printf("\t\t\t\tEsta llena");
										
								               getch();
										 }
								       
								        // Comprobar si el tablero se llena sin que ningún jugador logre una victoria
								        if(tableroLleno2(tablero_7x8, filas, columnas)==1) {
								            printf("\t\t\t\tEmpate!\n");
								            salida=1;
								        }
								
								        // Comprobar si el último movimiento ha dado lugar a una victoria
								        if(jugadorGana2(tablero_7x8, filas, columnas, color)==1) {
								              	system("cls");
								        
								        printf("\t\t\t\t=========== Jugador vs Jugador ==============\n\n");
								        imprimirMatriz2(tablero_7x8, filas, columnas);
								        	
								        printf("\n\t\t\t\tJ1: %s J2: %s\n", apodo1, apodo2);
								        
								        //Debido al cambio por turno
								     
								        
								        printf("\t\t\t\tVictoria del jugador %d!\n", ganador);
								            salida=1;
								            victory=1;
								               getch();
								        }
								
								        // Cambiar de turno
								     key =0;
								    }
				            break;
				            
				            
				        case 3:
				           	Llave=false;
				            filas = 9;
            				columnas = 9;	
				           
				           if (key==0){
				           	 
				           	  
				               for(int i = 0; i < filas; ++i)
						        for(int j = 0; j < columnas; ++j)
						           tablero_9x9[filas][columnas]= 0;
								
								}
				         
						           
							// Juego por turnos
							
								    turno = 1;  // Jugador 1 comienza
								    	    if (key==1){turno=guardaturno;} //Carga de Turno
								    while(salida!=1){
					system("cls"); 
								        	printf("\t\t\t\t=========== Jugador vs Jugador ==============\n\n");
								        imprimirMatriz3(tablero_9x9, filas, columnas);
								        printf("\n\t\t\t\tJ1: %s J2: %s\n", apodo1, apodo2);
								        
								            int color;
											if (turno == 1) {
											    color = 1;  // Jugador 1 elige amarillo (1)
											} else {
											    color = 2;  // Jugador 2 elige rojo (2)
											}
								        
								        
								        int columna;
								        printf("\t\t\t\tTurno del jugador %d.\n", turno);
								        printf("\t\t\t\tElige una columna: ");
								        scanf("%d", &columna);
								        
								        
								         if(columnaLlena3( tablero_9x9,filas,columna)!=1){
								         	
								         	 if (columna!=99){
								        	
								    // Colocar la ficha en la columna elegida
								        for(int i = filas - 1; i >= 0; --i) {
								            if(tablero_9x9[i][columna] == 0) {
								                tablero_9x9[i][columna] = color;
								                ganador = turno;
								                   turno = 3 - turno;
								                break;
								            }
								        }
								        	
										}else {
										guardar3(tablero_9x9, filas, columnas, columna);
										salida=1;
										victory=1;	
										guardaturno=turno;	
										} 
								         	
										 }else{
										 	
										 	
										 	printf("\t\t\t\tEsta llena");
										
								               getch();
										 }
								       
								        // Comprobar si el tablero se llena sin que ningún jugador logre una victoria
								        if(tableroLleno3(tablero_9x9, filas, columnas)==1) {
								            printf("\t\t\t\tEmpate!\n");
								            salida=1;
								        }
								
								        // Comprobar si el último movimiento ha dado lugar a una victoria
								        if(jugadorGana3(tablero_9x9, filas, columnas, color)==1) {
								             	system("cls");
								        
								        printf("\t\t\t\t=========== Jugador vs Jugador ==============\n\n");
								        imprimirMatriz3(tablero_9x9, filas, columnas);
								        	
								        printf("\n\t\t\t\tJ1: %s J2: %s\n", apodo1, apodo2);
								        
								        //Debido al cambio por turno
								     
								        
								        printf("\t\t\t\tVictoria del jugador %d!\n", ganador);
								            salida=1;
								            victory=1;
								               getch();
								        }
								
								        // Cambiar de turno
								     key =0;
								    }
				           
				           
				            break;
				               
				            
				        default:
				            printf("\t\t\t\tOpción no válida.\n");
				            return 1;
				    }
 	
 }

		if (Seleccion==2){
 	
 		system("cls"); 
 		printf("\t\t\t\t===========   CARGAR PARTIDA   ==============\n");
	    printf("\t\t\t\t1. Facil  (6X7)\n");
	    printf("\t\t\t\t2. Medio  (7X8)\n");
	    printf("\t\t\t\t3. Dificl (9X9)\n");
	    printf("\t\t\t\t3. Salir\n");
	    printf("\t\t\t\t==============================================\n");
	    printf("\t\t\t\tPor favor, elige una opcion: ");
	    scanf("%d", &Seleccion1);
 	
 	switch(Seleccion1){
 		
 		case 1:
 			
 		if(motriz_vacio1(6,7)==false){	        	 	
    	 	cargar1(tablero_6x7, 6, 7);
    	 	opcion1=1;
    	 	key=1;
    	 	Llave=true;
    	 	salida=0;
    	 	Seleccion=1;
    	 	victory=0;
		 }else{
		 	printf("\t\t\t\tNo hay partida a Cargar ");
		 }
 			
 			break;
 			
 		case 2:
 			
 				if(motriz_vacio2(7,8)==false){	        	 	
    	 	cargar2(tablero_7x8, 7, 8);
    	 	opcion1=2;
    	 	key=1;
    	 	Llave=true;
    	 	salida=0;
    	 	Seleccion=1;
    	 	victory=0;
		 }else{
		 	printf("\t\t\t\tNo hay partida a Cargar ");
		 }
 			
 			
 			
		 break;
		 
		 case 3:
		 	
		 			if(motriz_vacio3(9,9)==false){	        	 	
    	 	cargar2(tablero_7x8, 9, 9);
    	 	opcion1=3;
    	 	key=1;
    	 	Llave=true;
    	 	salida=0;
    	 	Seleccion=1;
    	 	victory=0;
		 }else{
		 	printf("\t\t\t\tNo hay partida a Cargar ");
		 }
		 	
		 break;
		 
		 case 4:
		 	break;
		 
		 default:
		 break;	
 		
	 }
 	
 	
 	
 	
 	  	
 	
 }
 
 
	
			
}while(victory!=1);
 if(ganador==1){
 	puntuacionA++;
 }
		
 if(ganador==2){
 	puntuacionB++;
 }	
break;

    }

	case 2:{ 
	
	int color;
		system("cls"); 
	printf("\t\t\t\t=========== Jugador vs Computadora ==============\n");
	int c;
	do {
	    c = getchar();
	} while (c != '\n' && c != EOF);
	
	printf("\t\t\t\tIngrese su apodo: ");
    fgets(apodo1, sizeof(apodo1), stdin);
    apodo1[strcspn(apodo1, "\n")] = 0;   

		do{
		
//Menu Primario	JvsJ
	system("cls"); 	
		printf("\t\t\t\t========= Jugador vs Computador =============\n");
	    printf("\t\t\t\t1. Nueva Partida\n");
	    printf("\t\t\t\t2. Cargar Partida\n");
	    printf("\t\t\t\t3. Salir\n");
	    printf("\t\t\t\t==============================================\n");
	    printf("\t\t\t\tPor favor, elige una opcion: ");
	     if(Llave==false){scanf("%d", &Seleccion);}else{printf("\n");}
	    
	    
//Menu Secundario JvsJ

 if(Seleccion==1){
 		system("cls"); 
 	        printf("\t\t\t\t========= Jugador vs Computador =============\n");
			printf("\t\t\t\t1. Matriz de 6x7\n");
			printf("\t\t\t\t2. Matriz de 7x8\n");
			printf("\t\t\t\t3. Matriz de 9x9\n");
			printf("\t\t\t\t4. Salir\n");
			 printf("\t\t\t\t==============================================\n");
			 printf("\t\t\t\tSeleccione una opcion:");
		    if(Llave==false){scanf("%d", &opcion1);}else{printf("\n");}
	
				    switch(opcion1) {
				        case 1:
				           	Llave=false;
				            filas = 6;
            				columnas = 7;	
				           
				           if (key==0){
				           	  for(int i = 0; i < filas; ++i){
							  for(int j = 0; j < columnas; ++j){
							  tablero_6x7[i][j] = 0;}}}
				         
						           
							// Juego por turnos
							
								    turno = 1;  // Jugador 1 comienza
								    while(salida!=1){
										system("cls"); 
								        printf("\t\t\t\t========= Jugador vs Computador =============\n\n");
								        imprimirMatriz1(tablero_6x7, filas, columnas);
								        printf("\n\t\t\t\tJ1: %s CPU\n", apodo1);
								         int columna;
									    		if (turno == 1) {
	            color = 1;  // Jugador 1 elige amarillo (1)
	            printf("Turno del jugador %d.\n", turno);
	            printf("Elige una columna: ");
	            scanf("%d", &columna);
	            
	        } else {
	        	color=2;
	             do {
	           columna = rand() % columnas;  // Seleccionar una columna aleatoria
	        } while(columnaLlena1(tablero_6x7, filas, columna)); // Repetir si la columna está llena
	
	        printf("\t\t\t\tTurno de la CPU.\n");
	        printf("\t\t\t\tLa CPU elige la columna: %d\n", columna);
    }
    
							
								        
								        
								         if(columnaLlena1( tablero_6x7,filas,columna)!=1){
								         	
								         	 if (columna!=99){
								        	
								    // Colocar la ficha en la columna elegida
								        for(int i = filas - 1; i >= 0; --i) {
								            if(tablero_6x7[i][columna] == 0) {
								                tablero_6x7[i][columna] = color;
								                ganador = turno;
								                   turno = 3 - turno;
								                break;
								            }
								        }
								        	
										}else {
										guardar1(tablero_6x7, filas, columnas, columna);
										salida=1;
										victory=1;	
										} 
								         	
										 }else{
										 	
										 	
										 	printf("\t\t\t\tEsta llena");
										
								               getch();
										 }
								       
								        // Comprobar si el tablero se llena sin que ningún jugador logre una victoria
								        if(tableroLleno1(tablero_6x7, filas, columnas)==1) {
								            printf("\t\t\t\tEmpate!\n");
								            salida=1;
								             system("pause");
								        }
								
								        // Comprobar si el último movimiento ha dado lugar a una victoria
								        if(jugadorGana1(tablero_6x7, filas, columnas, color)==1) {
								              	system("cls");
								        
								        printf("\t\t\t\t=========== Jugador vs Jugador ==============\n\n");
								        imprimirMatriz1(tablero_6x7, filas, columnas);
								        	
								        printf("\n\t\t\t\tJ1: %s J2: %s\n", apodo1, apodo2);
								        
								        //Debido al cambio por turno
								     
								        
								        printf("\t\t\t\tVictoria del jugador %d!\n", ganador);
								            salida=1;
								            victory=1;
								               getch();
								        }
								
								        // Cambiar de turno
								     key =0;
								    }
								   
						           
				            break;
				        case 2:
				           
						        
		
				           	Llave=false;
				            filas =7;
            				columnas = 8;	
				           
				           if (key==0){
				           	  for(int i = 0; i < filas; ++i){
							  for(int j = 0; j < columnas; ++j){
							  tablero_7x8[i][j] = 0;}}}
				         
						           
							// Juego por turnos
							
								    turno = 1;  // Jugador 1 comienza
								    while(salida!=1){
					system("cls"); 
								       printf("\t\t\t\t========= Jugador vs Computador =============\n\n");
								        imprimirMatriz2(tablero_7x8, filas, columnas);
								        printf("\n\t\t\t\tJ1: %s CPU\n", apodo1);
								         int columna;
									    		if (turno == 1) {
	            color = 1;  // Jugador 1 elige amarillo (1)
	            printf("Turno del jugador %d.\n", turno);
	            printf("Elige una columna: ");
	            scanf("%d", &columna);
	            
	        } else {
	        	color=2;
	             do {
	           columna = rand() % columnas;  // Seleccionar una columna aleatoria
	        } while(columnaLlena2(tablero_7x8, filas, columna)); // Repetir si la columna está llena
	
	        printf("\t\t\t\tTurno de la CPU.\n");
	        printf("\t\t\t\tLa CPU elige la columna: %d\n", columna);
    }
    
							
								        
								        
								         if(columnaLlena2( tablero_7x8,filas,columna)!=1){
								         	
								         	 if (columna!=99){
								        	
								    // Colocar la ficha en la columna elegida
								        for(int i = filas - 1; i >= 0; --i) {
								            if(tablero_7x8[i][columna] == 0) {
								                tablero_7x8[i][columna] = color;
								                ganador = turno;
								                   turno = 3 - turno;
								                break;
								            }
								        }
								        	
										}else {
										guardar2(tablero_7x8, filas, columnas, columna);
										salida=1;
										victory=1;	
										} 
								         	
										 }else{
										 	
										 	
										 	printf("\t\t\t\tEsta llena");
										
								               getch();
										 }
								       
								        // Comprobar si el tablero se llena sin que ningún jugador logre una victoria
								        if(tableroLleno2(tablero_7x8, filas, columnas)==1) {
								            printf("\t\t\t\tEmpate!\n");
								            salida=1;
								        }
								
								        // Comprobar si el último movimiento ha dado lugar a una victoria
								        if(jugadorGana2(tablero_7x8, filas, columnas, color)==1) {
								         	system("cls");
								        
								        printf("\t\t\t\t=========== Jugador vs Jugador ==============\n\n");
								        imprimirMatriz2(tablero_7x8, filas, columnas);
								        	
								        printf("\n\t\t\t\tJ1: %s J2: %s\n", apodo1, apodo2);
								        
								        //Debido al cambio por turno
								     
								        
								        printf("\t\t\t\tVictoria del jugador %d!\n", ganador);
								            salida=1;
								            victory=1;
								               getch();
								        }
								
								        // Cambiar de turno
								     key =0;
								    }
								     c = getch(); 
				            break;
				            
				            
				        case 3:     
		
				           	Llave=false;
				            filas =9;
            				columnas = 9;	
				           
				           if (key==0){
				           	  for(int i = 0; i < filas; ++i){
							  for(int j = 0; j < columnas; ++j){
							  tablero_9x9[i][j] = 0;}}}
				         
						           
							// Juego por turnos
							
								    turno = 1;  // Jugador 1 comienza
								    while(salida!=1){
					system("cls"); 
								          printf("\t\t\t\t========= Jugador vs Computador =============\n\n");
								        imprimirMatriz3(tablero_9x9, filas, columnas);
								        printf("\n\t\t\t\tJ1: %s CPU\n", apodo1);
								         int columna;
									    		if (turno == 1) {
	            color = 1;  // Jugador 1 elige amarillo (1)
	            printf("\t\t\t\tTurno del jugador %d.\n", turno);
	            printf("\t\t\t\tElige una columna: ");
	            scanf("%d", &columna);
	            
	        } else {
	        	color=2;
	             do {
	           columna = rand() % columnas;  // Seleccionar una columna aleatoria
	        } while(columnaLlena3(tablero_9x9, filas, columna)); // Repetir si la columna está llena
	
	        printf("\t\t\t\tTurno de la CPU.\n");
	        printf("\t\t\t\tLa CPU elige la columna: %d\n", columna);
    }
    
							
								        
								        
								         if(columnaLlena3( tablero_9x9,filas,columna)!=1){
								         	
								         	 if (columna!=99){
								        	
								    // Colocar la ficha en la columna elegida
								        for(int i = filas - 1; i >= 0; --i) {
								            if(tablero_9x9[i][columna] == 0) {
								                tablero_9x9[i][columna] = color;
								                ganador = turno;
								                   turno = 3 - turno;
								                break;
								            }
								        }
								        	
										}else {
										guardar3(tablero_9x9, filas, columnas, columna);
										salida=1;
										victory=1;	
										} 
								         	
										 }else{
										 	
										 	
										 	printf("\t\t\t\tEsta llena");
										
								               getch();
										 }
								       
								        // Comprobar si el tablero se llena sin que ningún jugador logre una victoria
								        if(tableroLleno3(tablero_9x9, filas, columnas)==1) {
								            printf("\t\t\t\tEmpate!\n");
								            salida=1;
								        }
								
								        // Comprobar si el último movimiento ha dado lugar a una victoria
								        if(jugadorGana3(tablero_9x9, filas, columnas, color)==1) {
								          	system("cls");
								        
								        printf("\t\t\t\t=========== Jugador vs Jugador ==============\n\n");
								        imprimirMatriz3(tablero_9x9, filas, columnas);
								        	
								        printf("\n\t\t\t\tJ1: %s J2: %s\n", apodo1, apodo2);
								        
								        //Debido al cambio por turno
								     
								        
								        printf("\t\t\t\tVictoria del jugador %d!\n", ganador);
								            salida=1;
								            victory=1;
								               getch();
								        }
								
								        // Cambiar de turno
								     key =0;
								    }
				            c = getch(); 
				           
				            break;
				               
				            
				        default:
				            printf("\t\t\t\tOpción no válida.\n");
				            return 1;
				    }
 	
 }

		if (Seleccion==2){
 	
 		system("cls"); 
 		printf("\t\t\t\t===========   CARGAR PARTIDA   ==============\n");
	    printf("\t\t\t\t1. Facil  (6X7)\n");
	    printf("\t\t\t\t2. Medio  (7X8)\n");
	    printf("\t\t\t\t3. Dificl (9X9)\n");
	    printf("\t\t\t\t3. Salir\n");
	    printf("\t\t\t\t==============================================\n");
	    printf("\t\t\t\tPor favor, elige una opcion: ");
	    scanf("%d", &Seleccion1);
 	
 	switch(Seleccion1){
 		
 		case 1:
 			
 		if(motriz_vacio1(6,7)==false){	        	 	
    	 	cargar1(tablero_6x7, 6, 7);
    	 	opcion1=1;
    	 	key=1;
    	 	Llave=true;
    	 	salida=0;
    	 	Seleccion=1;
    	 	victory=0;
		 }else{
		 	printf("\t\t\t\tNo hay partida a Cargar ");
		 }
 			
 			break;
 			
 		case 2:
 			
 				if(motriz_vacio2(7,8)==false){	        	 	
    	 	cargar2(tablero_7x8, 7, 8);
    	 	opcion1=2;
    	 	key=1;
    	 	Llave=true;
    	 	salida=0;
    	 	Seleccion=1;
    	 	victory=0;
		 }else{
		 	printf("\t\t\t\tNo hay partida a Cargar ");
		 }
 			
 			
 			
		 break;
		 
		 case 3:
		 	
		 			if(motriz_vacio3(9,9)==false){	        	 	
    	 	cargar2(tablero_7x8, 9, 9);
    	 	opcion1=3;
    	 	key=1;
    	 	Llave=true;
    	 	salida=0;
    	 	Seleccion=1;
    	 	victory=0;
		 }else{
		 	printf("\t\t\t\tNo hay partida a Cargar ");
		 }
		 	
		 break;
		 
		 case 4:
		 	break;
		 
		 default:
		 break;	
 		
	 }
 	
 	
 	
 	
 	  	
 	
 }
		
			
}while(victory!=1);
    }
		
		
if(ganador==1){
 	puntuacionA++;
 }
		
 if(ganador==2){
 	puntuacionC++;
 }			
		
 	break;
 	
	case 3:{ 
	
	int color;


		do{
			system("cls"); 
//Menu Primario	JvsJ	
		printf("\t\t\t\t========= Computador vs Computador =============\n");
	    printf("\t\t\t\t1. Nueva Partida\n");
	    printf("\t\t\t\t2. Cargar Partida\n");
	    printf("\t\t\t\t3. Salir\n");
	    printf("\t\t\t\t==============================================\n");
	    printf("\t\t\t\tPor favor, elige una opcion: ");
	     if(Llave==false){scanf("%d", &Seleccion);}else{printf("\n");}
	    
	    
//Menu Secundario JvsJ

 if(Seleccion==1){
 		system("cls"); 
 	        printf("\t\t\t\t========= Computador vs Computador =============\n");
			printf("\t\t\t\t1. Matriz de 6x7\n");
			printf("\t\t\t\t2. Matriz de 7x8\n");
			printf("\t\t\t\t3. Matriz de 9x9\n");
			printf("\t\t\t\t4. Salir\n");
			 printf("\t\t\t\t==============================================\n");
			 printf("\t\t\t\tSeleccione una opcion:");
		    if(Llave==false){scanf("%d", &opcion1);}else{printf("\n");}
	
				    switch(opcion1) {
				        case 1:
				           	Llave=false;
				            filas = 6;
            				columnas = 7;	
				           
				           if (key==0){
				           	  for(int i = 0; i < filas; ++i){
							  for(int j = 0; j < columnas; ++j){
							  tablero_6x7[i][j] = 0;}}}
				         
						           
							// Juego por turnos
							
								    turno = 1;  // Jugador 1 comienza
								    while(salida!=1){
					system("cls"); 
								          printf("\t\t\t\t========= Computador vs Computador =============\n\n");
								        imprimirMatriz1(tablero_6x7, filas, columnas);
								        printf("\n\t\t\t\tCPU #1 CPU #2\n", apodo1);
								         int columna;
								         usleep(150000); // Espera 0.25 segundos
							
										if (turno == 1) {
										        color = 1;  // CPU 1 elige amarillo (1)
										    } else {
										        color = 2;  // CPU 2 elige rojo (2)
										    }
										
										    // Seleccionar una columna aleatoria que no esté llena
										    do {
										        columna = rand() % columnas;
										    } while(columnaLlena1(tablero_6x7, filas, columna));
										
										    printf("\t\t\t\tTurno de la CPU %d.\n", turno);
										    printf("\t\t\t\tLa CPU %d elige la columna: %d\n", turno, columna);
    

								        
								        
								         if(columnaLlena1( tablero_6x7,filas,columna)!=1){
								         	
								         	 if (columna!=99){
								        	
								    // Colocar la ficha en la columna elegida
								        for(int i = filas - 1; i >= 0; --i) {
								            if(tablero_6x7[i][columna] == 0) {
								                tablero_6x7[i][columna] = color;
								                ganador = turno;
								                   turno = 3 - turno;
								                break;
								            }
								        }
								        	
										}else {
										guardar1(tablero_6x7, filas, columnas, columna);
										salida=1;
										victory=1;	
										} 
								         	
										 }else{
										 	
										 	
										 	printf("\t\t\t\tEsta llena");
										
										 }
								       
								        // Comprobar si el tablero se llena sin que ningún jugador logre una victoria
								        if(tableroLleno1(tablero_6x7, filas, columnas)==1) {
								        	
								        	
								        		system("cls");
								        
								        printf("\t\t\t\t========= Computador vs Computador =============\n\n");
								        imprimirMatriz1(tablero_6x7, filas, columnas);
								        	
								        printf("\n\t\t\t\tCPU #1 CPU #2\n");
								        	
								            printf("\t\t\t\tEmpate!\n");
								            salida=1;
								               getch();
								        }
								        
								        
								
								        // Comprobar si el último movimiento ha dado lugar a una victoria
								        if(jugadorGana1(tablero_6x7, filas, columnas, color)==1) {
								        	system("cls");
								        
								        printf("\t\t\t\t========= Computador vs Computador =============\n\n");
								        imprimirMatriz1(tablero_6x7, filas, columnas);
								        	
								        printf("\n\t\t\t\tCPU #1 CPU #2\n");
								        
								        //Debido al cambio por turno
								     
								        
								            printf("\t\t\t\tVictoria del jugador %d!\n", ganador);
								            salida=1;
								            victory=1;
								               getch();
								        }
								
								        // Cambiar de turno
								     key=0;
								    }
						           
				            break;
				        case 2:
				           
						        
		
				           	Llave=false;
				            filas =7;
            				columnas = 8;	
				           
				           if (key==0){
				           	  for(int i = 0; i < filas; ++i){
							  for(int j = 0; j < columnas; ++j){
							  tablero_7x8[i][j] = 0;}}}
				         
						           
							// Juego por turnos
							
								    turno = 1;  // Jugador 1 comienza
								    while(salida!=1){
							system("cls"); 
								        printf("\t\t\t\t========= Computador vs Computador =============\n\n");
								        imprimirMatriz2(tablero_7x8, filas, columnas);
								        printf("\n\t\t\t\tCPU #1 CPU #2\n", apodo1);
								         int columna;
								         		         usleep(150000); // Espera 0.25 segundos
															
										if (turno == 1) {
										        color = 1;  // CPU 1 elige amarillo (1)
										    } else {
										        color = 2;  // CPU 2 elige rojo (2)
										    }
										
										    // Seleccionar una columna aleatoria que no esté llena
										    do {
										        columna = rand() % columnas;
										    } while(columnaLlena2(tablero_7x8, filas, columna));
										
										    printf("\t\t\t\tTurno de la CPU %d.\n", turno);
										    printf("\t\t\t\tLa CPU %d elige la columna: %d\n", turno, columna);
										    

							
								        
								        
								         if(columnaLlena2( tablero_7x8,filas,columna)!=1){
								         	
								         	 if (columna!=99){
								        	
								    // Colocar la ficha en la columna elegida
								        for(int i = filas - 1; i >= 0; --i) {
								            if(tablero_7x8[i][columna] == 0) {
								                tablero_7x8[i][columna] = color;
								                   ganador = turno;
												   turno = 3 - turno;
								                break;
								            }
								        }
								        	
										}else {
										guardar2(tablero_7x8, filas, columnas, columna);
										salida=1;
										victory=1;	
										} 
								         	
										 }else{
										 	
										 	
										 	printf("\t\t\t\tEsta llena");
										
										 }
								       
								        // Comprobar si el tablero se llena sin que ningún jugador logre una victoria
								        if(tableroLleno2(tablero_7x8, filas, columnas)==1) {
								            		system("cls");
								        
								        printf("\t\t\t\t========= Computador vs Computador =============\n\n");
								        imprimirMatriz2(tablero_7x8, filas, columnas);
								        	
								        printf("\n\t\t\t\tCPU #1 CPU #2\n");
								        	
								            printf("\t\t\t\tEmpate!\n");
								            salida=1;
								               getch();
								        }
								
								        // Comprobar si el último movimiento ha dado lugar a una victoria
								        if(jugadorGana2(tablero_7x8, filas, columnas, color)==1) {
								           
								            
								            
								               	system("cls");
								        
								        printf("\t\t\t\t========= Computador vs Computador =============\n\n");
								        imprimirMatriz2(tablero_7x8, filas, columnas);
								        	
								        printf("\n\t\t\t\tCPU #1 CPU #2\n");
								        
								        //Debido al cambio por turno
								     
								        
								            printf("\t\t\t\tVictoria del jugador %d!\n", ganador);
								            salida=1;
								            victory=1;
								               getch();
								            
								            
								            
								        }
								
								        // Cambiar de turno
								     key =0;
								    }
				            break;
				            
				            
				        case 3:     
		
				           	Llave=false;
				            filas =9;
            				columnas = 9;	
				           
				           if (key==0){
				           	  for(int i = 0; i < filas; ++i){
							  for(int j = 0; j < columnas; ++j){
							  tablero_9x9[i][j] = 0;}}}
				         
						           
							// Juego por turnos
							
								    turno = 1;  // Jugador 1 comienza
								    while(salida!=1){
									system("cls"); 
								         printf("\t\t\t\t========= Computador vs Computador =============\n\n");
								        imprimirMatriz3(tablero_9x9, filas, columnas);
								        printf("\n\t\t\t\tCPU #1 CPU #2\n", apodo1);
								         int columna;
									    			         usleep(150000); // Espera 0.25 segundos
									    	
									if (turno == 1) {
									        color = 1;  // CPU 1 elige amarillo (1)
									    } else {
									        color = 2;  // CPU 2 elige rojo (2)
									    }
									
									    // Seleccionar una columna aleatoria que no esté llena
									    do {
									        columna = rand() % columnas;
									    } while(columnaLlena3(tablero_9x9, filas, columna));
									
									    printf("Turno de la CPU %d.\n", turno);
									    printf("La CPU %d elige la columna: %d\n", turno, columna);
									    

							
								        
								        
								         if(columnaLlena3( tablero_9x9,filas,columna)!=1){
								         	
								         	 if (columna!=99){
								        	
								    // Colocar la ficha en la columna elegida
								        for(int i = filas - 1; i >= 0; --i) {
								            if(tablero_9x9[i][columna] == 0) {
								                tablero_9x9[i][columna] = color;
								                ganador = turno;
								                   turno = 3 - turno;
								                break;
								            }
								        }
								        	
										}else {
										guardar3(tablero_9x9, filas, columnas, columna);
										salida=1;
										victory=1;	
										} 
								         	
										 }else{
										 	
										 	
										 	printf("\t\t\t\tEsta llena");
										
										 }
								       
								        // Comprobar si el tablero se llena sin que ningún jugador logre una victoria
								        if(tableroLleno3(tablero_9x9, filas, columnas)==1) {
								          		system("cls");
								        
								        printf("\t\t\t\t========= Computador vs Computador =============\n\n");
								        imprimirMatriz3(tablero_9x9, filas, columnas);
								        	
								        printf("\n\t\t\t\tCPU #1 CPU #2\n");
								        	
								            printf("\t\t\t\tEmpate!\n");
								            salida=1;
								               getch();
								        }
								
								        // Comprobar si el último movimiento ha dado lugar a una victoria
								        if(jugadorGana3(tablero_9x9, filas, columnas, color)==1) {
								        
								            
								               	system("cls");
								        
								        printf("\t\t\t\t========= Computador vs Computador =============\n\n");
								        imprimirMatriz3(tablero_9x9, filas, columnas);
								        	
								        printf("\n\t\t\t\tCPU #1 CPU #2\n");
								        
								        //Debido al cambio por turno
								     
								        
								            printf("\t\t\t\tVictoria del jugador %d!\n", ganador);
								            salida=1;
								            victory=1;
								               getch();
								            
								        }
								
								        // Cambiar de turno
								     key =0;
								    }
				           
				           
				            break;
				               
				            
				        default:
				            printf("\t\t\t\tOpción no válida.\n");
				            return 1;
				    }
 	
 }

		if (Seleccion==2){
 	
 		system("cls"); 
 		printf("\t\t\t\t===========   CARGAR PARTIDA   ==============\n");
	    printf("\t\t\t\t1. Facil  (6X7)\n");
	    printf("\t\t\t\t2. Medio  (7X8)\n");
	    printf("\t\t\t\t3. Dificl (9X9)\n");
	    printf("\t\t\t\t3. Salir\n");
	    printf("\t\t\t\t==============================================\n");
	    printf("\t\t\t\tPor favor, elige una opcion: ");
	    scanf("%d", &Seleccion1);
 	
 	switch(Seleccion1){
 		
 		case 1:
 			
 		if(motriz_vacio1(6,7)==false){	        	 	
    	 	cargar1(tablero_6x7, 6, 7);
    	 	opcion1=1;
    	 	key=1;
    	 	Llave=true;
    	 	salida=0;
    	 	Seleccion=1;
    	 	victory=0;
		 }else{
		 	printf("\t\t\t\tNo hay partida a Cargar ");
		 }
 			
 			break;
 			
 		case 2:
 			
 				if(motriz_vacio2(7,8)==false){	        	 	
    	 	cargar2(tablero_7x8, 7, 8);
    	 	opcion1=2;
    	 	key=1;
    	 	Llave=true;
    	 	salida=0;
    	 	Seleccion=1;
    	 	victory=0;
		 }else{
		 	printf("\t\t\t\tNo hay partida a Cargar ");
		 }
 			
 			
 			
		 break;
		 
		 case 3:
		 	
		 			if(motriz_vacio3(9,9)==false){	        	 	
    	 	cargar2(tablero_7x8, 9, 9);
    	 	opcion1=3;
    	 	key=1;
    	 	Llave=true;
    	 	salida=0;
    	 	Seleccion=1;
    	 	victory=0;
		 }else{
		 	printf("\t\t\t\tNo hay partida a Cargar ");
		 }
		 	
		 break;
		 
		 case 4:
		 	break;
		 
		 default:
		 break;	
 		
	 }
 	  	
 	
 }
		
			
}while(victory!=1);

if(ganador==1){
 	puntuacionC++;
 }
		
 if(ganador==2){
 	puntuacionD++;
 }		


    }
	
			

		
	break;
	
	case 4:
	break;
		
}

       
    }while(opcion != 4);
    
    
    	system("cls"); 
   printf("\t\t\t\t========= ESTADISTICAS FINALES =============\n\n"); 
    printf("\t\t\t\t - Jugador 1: %d \n\n", puntuacionA); 
     printf("\t\t\t\t - Jugador 2: %d \n\n", puntuacionB); 
      printf("\t\t\t\t - CPU #1: %d \n\n", puntuacionC); 
       printf("\t\t\t\t - CPU #2 1: %d \n\n", puntuacionD); 

    	
    return 0;
}

