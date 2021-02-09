/*
 * NaskBot.cpp
 *
 * Autor: Sergio Azañón Cantero 
 */

#include "NaskBot.h"

#include <string>
#include <cstdlib>
#include <iostream>
#include <climits>

using namespace std;


NaskBot::NaskBot() {
	// Inicializar las variables necesarias para ejecutar la partida

}

NaskBot::~NaskBot() {
	// Liberar los recursos reservados (memoria, ficheros, etc.)
}

void NaskBot::initialize() {
	// Inicializar el bot antes de jugar una partida
}

string NaskBot::getName() {
	return "NaskBot"; // Sustituir por el nombre del bot
}

int Heuristica (const GameState &nod){

	int score=0;
	Player turn=nod.getCurrentPlayer();

	int diferencia;

	if(turn==0)
		diferencia=(nod.getScore(turn)-nod.getScore( (Player) 1));
	else
		diferencia=(nod.getScore(turn)-nod.getScore( (Player) 0));

	if(nod.getWinner()==turn){	// Si el jugador del nodo ha ganado
		score+=100;
		score+=abs(diferencia);
	}
	else if(nod.getWinner()!=turn && nod.getWinner()!=2){ // Si ha perdido (El 2 lo pongo porque entraria en la condicion si no hubiera ningun ganador)
		score-=100;
		score-=abs(diferencia);
	}
	else if(nod.getWinner()==2){ // No hay ganador aun
		score+=diferencia; // Sumamos la diferencia de semillas con el rival (ya sea negativa o positiva)
		for(int i=1;i<=6;i++)
			score+=(int) nod.getSeedsAt(nod.getCurrentPlayer(), (Position) i);

		
	}

	return (score);
	

}

int funcion_MIN_MAX(const GameState &nod,bool min,int profundidad,int alfa,int beta){

	
	if (nod.isFinalState() || profundidad==MAX_PROF)
		return(Heuristica(nod));
	

	int valor;

	if(min)
		valor=INT_MAX;
	else
		valor=INT_MIN;
	

	//Generamos las posibles acciones que podemos realizar
	for(int i=1; i<=6;i++){

		if( (int) nod.getSeedsAt(nod.getCurrentPlayer(), (Position) i) >0){ // Solo generamos si tiene semillas la casilla
			int tmp;
			GameState hijo;

			hijo=nod.simulateMove( (Move) i);
	
		
			if( (!min && hijo.getCurrentPlayer()!=nod.getCurrentPlayer()) || (min && hijo.getCurrentPlayer()==nod.getCurrentPlayer()) ){
				tmp=funcion_MIN_MAX(hijo,true,profundidad+1,alfa,beta);
			}
			else if( (min && hijo.getCurrentPlayer()!=nod.getCurrentPlayer()) || (!min && hijo.getCurrentPlayer()==nod.getCurrentPlayer()) ){
				tmp=funcion_MIN_MAX(hijo,false,profundidad+1,alfa,beta);
			}
		
			
			if(min){
				if(tmp < valor)
					valor=tmp;

				if(valor <= alfa)
					return valor;
			
				if(valor > beta)
					beta=valor;
			}
			else{
				if(tmp > valor)
					valor=tmp;
			
				if(valor >= beta)
					return valor;

				if(valor > alfa)
					alfa=valor;
			}

		}

	

	}

	return valor;
}


Move NaskBot::nextMove(const vector<Move> &adversary, const GameState &state) {


	Player turno= this->getPlayer(); // Turno actual 
	

	int profundidad=0;
	
	Move mov=M_NONE; // Inicializamos su movimiento a ninguno, es decir, M_NONE
	
	int valor_act=INT_MIN;	
	int alfa= INT_MIN;
	int beta=INT_MAX;		  			


	//Generamos las posibles acciones que podemos realizar
	for(int i=1; i<=6;i++){

		if( (int) state.getSeedsAt(state.getCurrentPlayer(), (Position) i) >0) {// Solo generamos si tiene semillas la casilla
			GameState hijo;
			hijo=state.simulateMove( (Move) i);
			
	
			int tmp; 

			if(turno!=hijo.getCurrentPlayer()){	// Somos el J1 o J2, y el siguiente turno es del otro jugador
				tmp=funcion_MIN_MAX(hijo,true,profundidad+1,alfa,beta); // Y la funcion devolverá un struct
			}
			else if(turno==hijo.getCurrentPlayer())	// Si somos J1 o J2 y tendra turno extra
				tmp=funcion_MIN_MAX(hijo,false,profundidad+1,alfa,beta); 


			if(tmp>valor_act){// Si el valor devuelto es mayor que el que tenemos guardado
				valor_act=tmp;
				mov=(Move) i;
			}
			
			if(valor_act > alfa)
				alfa=valor_act;

			
		}
	}


	return (mov);
}



























