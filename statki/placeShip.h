#ifndef placeShip_h
#define placeShip_h
#include "funkcje.h"

void placeShipN(field board[], int x, int y, int sizeOfShip, int boardSizeX, char currentPlayer, int numberOfShip, char shipClass[3], char direction);
void placeShipS(field board[], int x, int y, int sizeOfShip, int boardSizeX, char currentPlayer, int numberOfShip, char shipClass[3], char direction);
void placeShipW(field board[], int x, int y, int sizeOfShip, int boardSizeX, char currentPlayer, int numberOfShip, char shipClass[3], char direction);
void placeShipE(field board[], int x, int y, int sizeOfShip, int boardSizeX, char currentPlayer, int numberOfShip, char shipClass[3], char direction);
#endif