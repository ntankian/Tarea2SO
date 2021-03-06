#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Sansano.h"
#include "CartaCurso.h"
#include "lista.h"

/******** Funcion: main ********************
Descripcion: Crea los jugadores, sus mazos y ejecuta los turnos hasta que alguien 
gane o se acaben  las cartas. Finalmente libera memoria.
Parametros: No recibe parametros.
Retorno: Retorna el int 0;
************************************************/ 

int main(){
	
	Sansano *CPU, *player;
	CartaCurso *aux;

	int comando;
	int flag;
	int turno;
	int pos_Carta;
	int cant_cartas;
	int com;
	
	flag	= 1;
	turno 	= 1;
	cant_cartas =0;
	//comando = 0;
	
	char nombre[50];
	CPU = const_Player("Maquinola");
	
	srand(time(NULL));
	printf("Ingrese su nombre:[maximo 50 caracteres]\n");
	scanf("%s", nombre);
	player = const_Player(nombre);
	
	while(flag == 1){
		comando = 0;
		if (turno%2 == 1){
			if(cant_cartas >= 40){
				break;
				}
			pos_Carta = (rand())%6;
			movePos((tLista*)player->mazo, pos_Carta);
			aux = ((CartaCurso*)((tLista*)(player->mazo))->curr->sig->carta);
			while(aux->cantidad == 0){
				
				pos_Carta = (rand()+1)%6;
				movePos((tLista*)player->mazo, pos_Carta);
				aux = ((CartaCurso*)((tLista*)(player->mazo))->curr->sig->carta);
			}
			
			printf("Has sacado la carta %s. Descripcion: %s\n", aux->nombre, aux->descripcion);
			printf("-----------------------------------------------------------------------\n");
			printf("Prioridad actual:%d\t Prioridad enemiga: %d\n", player->prioridad, CPU->prioridad);
			printf("-Para curarte presiona 1\n-Para atacar presiona 2\n");

			while((comando != 2 )&&( comando != 1) ){
				printf("Ingresa una opcion valida\n");
				scanf("%d", &comando);
			}
			
			printf("-----------------------------------------------------------------------\n");
			if (comando == 1){
				aux->aprobar(aux, player);
				printf("Tu prioridad actual:%d\n",player->prioridad);
				printf("-----------------------------------------------------------------------\n");
				turno+=1;
				cant_cartas +=1;
				
			}
			else if (comando == 2){
				//printf("Prioridad enemiga:%d", CPU->prioridad);
				aux->reprobar(aux, CPU);
				printf("Prioridad enemiga:%d\n", CPU->prioridad);
				turno+=1;
				cant_cartas +=1;
				printf("-----------------------------------------------------------------------\n");
				if(CPU->prioridad <= 0){
					flag = 0;
					printf("Has ganado!!! Felicitaciones!!!\n");
					movePos((tLista*)CPU->mazo, 0);
					movePos((tLista*)player->mazo, 0);
					lista_free((tNodo*)((tLista*)(player->mazo))->curr->sig);
					lista_free((tNodo*)((tLista*)(CPU->mazo))->curr->sig);
					free((void*)(tNodo*)((tLista*)(player->mazo))->head);
					free((void*)(tNodo*)((tLista*)(CPU->mazo))->head);
					free((void*)(tLista*)(player->mazo));
					free((void*)(tLista*)(CPU->mazo));
					free((void*)player);
					free((void*)CPU);
					exit(1);
				}
			}
		}
		else{
			if(cant_cartas >= 40){
				break;
				}
			pos_Carta = (rand())%6;
			movePos((tLista*)CPU->mazo, pos_Carta);
			aux = ((CartaCurso*)((tLista*)(CPU->mazo))->curr->sig->carta);
			while(aux->cantidad == 0){
				pos_Carta = (rand()+1)%6;
				movePos((tLista*)CPU->mazo, pos_Carta);
				aux = ((CartaCurso*)((tLista*)(CPU->mazo))->curr->sig->carta);
				
			}
			printf("turno enemigo\n");
			if(CPU->prioridad > 1500){
				
				aux->reprobar(aux,player);
				cant_cartas +=1;
				printf("Te ha atacado con %s. Tu prioridad es: %d\n",aux->nombre, player->prioridad);
				turno+=1;
				printf("-----------------------------------------------------------------------\n");
				if(player->prioridad <= 0){
					flag =0;
					printf("Has perdido!!! Te ha ganado la Maquinola... Eres una decepcion para la humanidad.");
					printf("-----------------------------------------------------------------------\n");
					movePos((tLista*)CPU->mazo, 0);
					movePos((tLista*)player->mazo, 0);
					lista_free((tNodo*)((tLista*)(player->mazo))->curr->sig);
					lista_free((tNodo*)((tLista*)(CPU->mazo))->curr->sig);
					free((void*)(tNodo*)((tLista*)(player->mazo))->head);
					free((void*)(tNodo*)((tLista*)(CPU->mazo))->head);
					free((void*)(tLista*)(player->mazo));
					free((void*)(tLista*)(CPU->mazo));
					free((void*)player);
					free((void*)CPU);
					exit(1);
					
				}
			}
			else{
				aux->aprobar(aux,CPU);
				printf("Se ha curado con %s. Su prioridad es: %d\n", aux->nombre, CPU->prioridad);
				turno+=1;
				printf("-----------------------------------------------------------------------\n");
				cant_cartas +=1;
				
			}
		}	
		}
	if(player->prioridad > CPU->prioridad){
		printf("Se han acabado las cartas. Has Ganado!!! Felicitaciones!!!\n");
		}
	else if(player->prioridad < CPU->prioridad){
		printf("Se han acabado las cartas. Has Perdido!!! Te ha ganado la Maquinola... Eres una decepcion para la humanidad\n");
		}
	else{
		printf("Se han acabado las cartas. Han empatado!!! Quien lo hubiera dicho.\n");
		}
	movePos((tLista*)CPU->mazo, 0);
	movePos((tLista*)player->mazo, 0);
	lista_free((tNodo*)((tLista*)(player->mazo))->curr->sig);
	lista_free((tNodo*)((tLista*)(CPU->mazo))->curr->sig);
	free((void*)(tNodo*)((tLista*)(player->mazo))->head);
	free((void*)(tNodo*)((tLista*)(CPU->mazo))->head);
	free((void*)(tLista*)(player->mazo));
	free((void*)(tLista*)(CPU->mazo));
	free((void*)player);
	free((void*)CPU);
	return 0;
		
}
