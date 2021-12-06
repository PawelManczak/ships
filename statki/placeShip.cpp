#include <iostream>
#include "placeShip.h"

using namespace std;

void placeShipN(field board[], int x, int y, int sizeOfShip, int boardSizeX, char currentPlayer, int numberOfShip, char shipClass[3], char direction) {

    for (int i = 0; i < sizeOfShip; i++) {
        board[getIndex(y, x + i, boardSizeX)].state = '+';
        board[getIndex(y, x + i, boardSizeX)].player = currentPlayer;
        board[getIndex(y, x + i, boardSizeX)].numberI = numberOfShip;
        strcpy_s(board[getIndex(y, x + i, boardSizeX)].classOfShip, shipClass);
        board[getIndex(y, x + i, boardSizeX)].direction = direction;
        if (i == 1) board[getIndex(y, x + i, boardSizeX)].cannon = true;
        if (i == 0) board[getIndex(y, x + i, boardSizeX)].radar = true;
        if (i == sizeOfShip - 1) board[getIndex(y, x + i, boardSizeX)].engine = true;
    }
}

void placeShipS(field board[], int x, int y, int sizeOfShip, int boardSizeX, char currentPlayer, int numberOfShip, char shipClass[3], char direction) {

    for (int i = 0; i < sizeOfShip; i++) {
        board[getIndex(y, x - i, boardSizeX)].state = '+';
        board[getIndex(y, x - i, boardSizeX)].player = currentPlayer;
        board[getIndex(y, x - i, boardSizeX)].numberI = numberOfShip;
        strcpy_s(board[getIndex(y, x - i, boardSizeX)].classOfShip, shipClass);
        board[getIndex(y, x - i, boardSizeX)].direction = direction;
        if (i == 1) board[getIndex(y, x - i, boardSizeX)].cannon = true;
        if (i == 0) board[getIndex(y, x - i, boardSizeX)].radar = true;
        if (i == sizeOfShip - 1) board[getIndex(y, x - i, boardSizeX)].engine = true;
    }
}

void placeShipW(field board[], int x, int y, int sizeOfShip, int boardSizeX, char currentPlayer, int numberOfShip, char shipClass[3], char direction) {

    for (int i = 0; i < sizeOfShip; i++) {
        board[getIndex(y + i, x, boardSizeX)].state = '+';
        board[getIndex(y + i, x, boardSizeX)].player = currentPlayer;
        board[getIndex(y + i, x, boardSizeX)].numberI = numberOfShip;
        strcpy_s(board[getIndex(y + i, x, boardSizeX)].classOfShip, shipClass);
        board[getIndex(y + i, x, boardSizeX)].direction = direction;
        if (i == 1) board[getIndex(y + i, x, boardSizeX)].cannon = true;
        if (i == 0) board[getIndex(y + i, x, boardSizeX)].radar = true;
        if (i == sizeOfShip - 1) board[getIndex(y + i, x, boardSizeX)].engine = true;
    }
}

void placeShipE(field board[], int x, int y, int sizeOfShip, int boardSizeX, char currentPlayer, int numberOfShip, char shipClass[3], char direction) {

    for (int i = 0; i < sizeOfShip; i++) {
        board[getIndex(y - i, x, boardSizeX)].state = '+';
        board[getIndex(y - i, x, boardSizeX)].player = currentPlayer;
        board[getIndex(y - i, x, boardSizeX)].numberI = numberOfShip;
        strcpy_s(board[getIndex(y - i, x, boardSizeX)].classOfShip, shipClass);
        board[getIndex(y - i, x, boardSizeX)].direction = direction;
        if (i == 1) board[getIndex(y - i, x, boardSizeX)].cannon = true;
        if (i == 0) board[getIndex(y - i, x, boardSizeX)].radar = true;
        if (i == sizeOfShip - 1) board[getIndex(y - i, x, boardSizeX)].engine = true;
    }
}