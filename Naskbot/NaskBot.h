/*
 * NaskBot.h
 *
 *  Autor: Sergio Azañón Cantero
 */

#include "Bot.h"
#include "list"

#ifndef NASKBOT_H_
#define NASKBOT_H_

const int MAX_PROF=12;

class NaskBot:Bot {
public:
	NaskBot();
	~NaskBot();


	void initialize();
	string getName();
	Move nextMove(const vector<Move> &adversary, const GameState &state);
};


#endif 
