#include <iostream>
#include "funkcje.h"

using namespace std;

int getIndex(int x, int y, int customWidth) {
    return x + y * customWidth;
}

void initialize(field board[], rectangle* r1, rectangle* r2, int BOARD_W, int BOARD_H) {
    for (int yy = 0; yy < BOARD_H; yy++) {
        for (int xx = 0; xx < BOARD_W; xx++) {
            board[getIndex(xx, yy, BOARD_W)].state = ' ';
        }
    }

    (*r1).x1 = 0;
    (*r1).y1 = 0;
    (*r1).x2 = 9;
    (*r1).y2 = 9;

    (*r2).x1 = 1;
    (*r2).y1 = 0;
    (*r2).x2 = 20;
    (*r2).y2 = 9;

}

int getSizeOfShip(char type[3]) {
    if (!strcmp("CAR", type)) return 5;
    else if (!strcmp("BAT", type)) return 4;
    else if (!strcmp("DES", type)) return 2;
    else return 3;
}

void incrementShipCounter(char shipClass[3], ShipCounter* shipCounter) {

    if (!strcmp("CAR", shipClass)) {
        (*shipCounter).carIn();
    }
    else if (!strcmp("BAT", shipClass)) {
        (*shipCounter).batIn();
    }
    else if (!strcmp("DES", shipClass)) {
        (*shipCounter).desIn();
    }
    else if (!strcmp("CRU", shipClass)) {
        (*shipCounter).cruIn();
    }
}

bool ifShipAlreadyPresent(char shipClass[3], int numberOfShip, ShipCounter* shipCounter) {
    if ((!strcmp("CAR", shipClass) && numberOfShip + 1 <= (*shipCounter).getCAR()) ||
        (!strcmp("BAT", shipClass) && numberOfShip + 1 <= (*shipCounter).getBAT()) ||
        (!strcmp("DES", shipClass) && numberOfShip + 1 <= (*shipCounter).getDES()) ||
        (!strcmp("CRU", shipClass) && numberOfShip + 1 <= (*shipCounter).getCRU()))
        return true;
    return false;
}

bool ifAllShipOfTheClassAlreadySet(ShipCounter shipCounter, char shipClass[3], ShipCounter max) {
    if ((!strcmp("CAR", shipClass) && shipCounter.getCAR() == max.getCAR())
        || (!strcmp("BAT", shipClass) && shipCounter.getBAT() == max.getBAT())
        || (!strcmp("DES", shipClass) && shipCounter.getDES() == max.getDES())
        || (!strcmp("CRU", shipClass) && shipCounter.getCRU() == max.getCRU())) return true;

    return false;
}

bool ifAllShipsAlreadySet(ShipCounter shipCounter, ShipCounter max) {
    if ((shipCounter.getCAR() == max.getCAR())
        && (shipCounter.getBAT() == max.getBAT())
        && (shipCounter.getDES() == max.getDES())
        && (shipCounter.getCRU() == max.getCRU())) {
        return true;
    }
    else
        return false;
}

void shoot(field board[], int x, int y, int boardWith) {

    if ((board[getIndex(x, y, boardWith)]).state == '+')
        board[getIndex(x, y, boardWith)].state = 'x';
}

int howManyRemaining(field board[], char player, int BOARD_W, int BOARD_H) {
    int howMany = 0;
    for (int yy = 0; yy < BOARD_H; yy++) {
        for (int xx = 0; xx < BOARD_W; xx++) {
            if (board[getIndex(yy, xx, BOARD_H)].state == '+' && board[getIndex(yy, xx, BOARD_H)].player == player) howMany++;
        }
    }

    return howMany;
}

int howManyDestroyed(field board[], char player, int BOARD_H, int BOARD_W) {
    int howMany = 0;
    for (int yy = 0; yy < BOARD_H; yy++) {
        for (int xx = 0; xx < BOARD_W; xx++) {
            if (board[getIndex(xx, yy, BOARD_W)].state == 'x' && board[getIndex(xx, yy, BOARD_W)].player == player) howMany++;
        }
    }
    return howMany;
}

void print0(field board[], int BOARD_H, int BOARD_W) {
    for (int yy = 0; yy < BOARD_H; yy++) {
        for (int xx = 0; xx < BOARD_W; xx++) {
            cout << board[getIndex(xx, yy, BOARD_W)].state;
        }
        cout << endl;
    }
}

void print1(field board[], int BOARD_H, int BOARD_W) {

    cout << "  ";
    for (int i = 0; i < BOARD_W; i++) cout << i;
    cout << endl;

    for (int yy = 0; yy < BOARD_H; yy++) {
        if (yy < 10) cout << "0" << yy;
        else cout << yy;
        for (int xx = 0; xx < BOARD_W; xx++) {

            if (board[getIndex(xx, yy, BOARD_W)].state == 'x') cout << 'x';
            else {
                if (board[getIndex(xx, yy, BOARD_W)].radar == true) cout << "@";
                else if (board[getIndex(xx, yy, BOARD_W)].engine == true) cout << "%";
                else if (board[getIndex(xx, yy, BOARD_W)].cannon == true) cout << "!";
                else
                    cout << board[getIndex(xx, yy, BOARD_W)].state;
            }

        }
        cout << endl;
    }
}

bool isInRectangle(int x, int y, rectangle r) {
    if (x >= r.x1 && x <= r.x2 && y >= r.y1 && y <= r.y2) return true;
    return false;
}

bool ifTooCloseToOthers(int x, int y, int i, int shipSize, field board[], int boardSizeX, int boardSizeY) {

    int ile = 0;
    if (board[getIndex(x, y, boardSizeX)].state == '+') return true;
    if (x != 0 and board[getIndex(x - 1, y, boardSizeX)].state == '+') { ile++; }
    if (x != boardSizeX - 1 and board[getIndex(x + 1, y, boardSizeX)].state == '+') { ile++; }
    if (y != 0 and board[getIndex(x, y - 1, boardSizeX)].state == '+') { ile++; }
    if (y != boardSizeY - 1 and board[getIndex(x, y + 1, boardSizeX)].state == '+') { ile++; }


    if (i == 0) { ile++; }
    if (ile > 1) return true;
    return false;
}

bool isSbAround(field board[], int x, int y, char player, int BOARD_H, int BOARD_W) {

    char oponent;
    player == 'A' ? oponent = 'B' : oponent = 'A';

    if (board[getIndex(x, y + 1, BOARD_W)].player == oponent || board[getIndex(x, y - 1, BOARD_W)].player == oponent
        || board[getIndex(x + 1, y, BOARD_W)].player == oponent || board[getIndex(x - 1, y, BOARD_W)].player == oponent)
        return true;
    else return false;
}

int getIndexOfCannon(field board[], char classOfShip[], int nummberOfShip, char player, int BOARD_W, int BOARD_H, bool xy) {
    for (int yy = 0; yy < BOARD_H; yy++) {
        for (int xx = 0; xx < BOARD_W; xx++) {
            if (board[getIndex(xx, yy, BOARD_W)].player == player
                && board[getIndex(xx, yy, BOARD_W)].numberI == nummberOfShip
                && !strcmp(classOfShip, board[getIndex(xx, yy, BOARD_W)].classOfShip)
                && board[getIndex(xx, yy, BOARD_W)].cannon == true) {

                if (xy) return xx;
                else return yy;
            }

        }
    }

    return -1;
}

void printPlayerPerspective(field board[], int boardSizeX, int boardSizeY, char player) {
    bool* boardTemp = new bool[boardSizeX * boardSizeY];

    for (int i = 0; i < boardSizeX * boardSizeY; i++) {
        board[i].player == player ? boardTemp[i] = true : boardTemp[i] = false;
        if (board[i].spyA == true && player == 'A') boardTemp[i] = true;
        if (board[i].spyB == true && player == 'B') boardTemp[i] = true;
    }
    for (int i = 0; i < boardSizeX * boardSizeY; i++) {
        if (board[i].player == player && board[i].radar == true) {
            int range = getSizeOfShip(board[i].classOfShip);
            int x = i % boardSizeX;
            int y = i / boardSizeX;
            float distance;

            for (int yy = 0; yy < boardSizeY; yy++) {
                for (int xx = 0; xx < boardSizeX; xx++) {

                    distance = sqrt(pow(abs(y - yy), 2) + pow(abs(x - xx), 2));
                    if (distance <= range) {
                        boardTemp[getIndex(xx, yy, boardSizeX)] = true;
                    }
                }
            }

        }
    }

    for (int yy = 0; yy < boardSizeY; yy++) {
        for (int xx = 0; xx < boardSizeX; xx++) {
            if (boardTemp[getIndex(xx, yy, boardSizeX)])
                cout << board[getIndex(xx, yy, boardSizeX)].state;
            else cout << "?";
        }
        cout << endl;
    }

    delete[] boardTemp;
}

void spy(field board[], int x, int y, int boardSizeX, int boardSizeY, char player) {

    if (x >= 0 && y + 1 >= 0 && x < boardSizeX && y + 1 < boardSizeY)
        player == 'A' ? board[getIndex(x, y + 1, boardSizeX)].spyA = true : board[getIndex(x, y + 1, boardSizeX)].spyB = true;
    if (x - 1 >= 0 && y + 1 >= 0 && x - 1 < boardSizeX && y + 1 < boardSizeY)
        player == 'A' ? board[getIndex(x - 1, y + 1, boardSizeX)].spyA = true : board[getIndex(x - 1, y + 1, boardSizeX)].spyB = true;
    if (x + 1 >= 0 && y + 1 >= 0 && x + 1 < boardSizeX && y + 1 < boardSizeY)
        player == 'A' ? board[getIndex(x + 1, y + 1, boardSizeX)].spyA = true : board[getIndex(x + 1, y + 1, boardSizeX)].spyB = true;
    if (x - 1 >= 0 && y >= 0 && x - 1 < boardSizeX && y < boardSizeY)
        player == 'A' ? board[getIndex(x - 1, y, boardSizeX)].spyA = true : board[getIndex(x - 1, y, boardSizeX)].spyB = true;
    if (x + 1 >= 0 && y >= 0 && x + 1 < boardSizeX && y < boardSizeY)
        player == 'A' ? board[getIndex(x + 1, y, boardSizeX)].spyA = true : board[getIndex(x + 1, y, boardSizeX)].spyB = true;
    if (x >= 0 && y >= 0 && x < boardSizeX && y < boardSizeY)
        player == 'A' ? board[getIndex(x, y, boardSizeX)].spyA = true : board[getIndex(x, y, boardSizeX)].spyB = true;
    if (x >= 0 && y - 1 >= 0 && x < boardSizeX && y - 1 < boardSizeY)
        player == 'A' ? board[getIndex(x, y - 1, boardSizeX)].spyA = true : board[getIndex(x, y - 1, boardSizeX)].spyB = true;
    if (x + 1 >= 0 && y - 1 >= 0 && x + 1 < boardSizeX && y - 1 < boardSizeY)
        player == 'A' ? board[getIndex(x + 1, y - 1, boardSizeX)].spyA = true : board[getIndex(x + 1, y - 1, boardSizeX)].spyB = true;
    if (x - 1 >= 0 && y - 1 >= 0 && x - 1 < boardSizeX && y - 1 < boardSizeY)
        player == 'A' ? board[getIndex(x - 1, y - 1, boardSizeX)].spyA = true : board[getIndex(x - 1, y - 1, boardSizeX)].spyB = true;

}

//MOVES DONE METHODS

void MovesDone::setAmounts(ShipCounter maxAmount) {
    car = new int[maxAmount.getCAR()];
    bat = new int[maxAmount.getBAT()];
    des = new int[maxAmount.getDES()];
    cru = new int[maxAmount.getCRU()];

    for (int i = 0; i < maxAmount.getCAR(); i++) car[i] = 0;
    for (int i = 0; i < maxAmount.getBAT(); i++) bat[i] = 0;
    for (int i = 0; i < maxAmount.getDES(); i++) des[i] = 0;
    for (int i = 0; i < maxAmount.getCRU(); i++) cru[i] = 0;
}

MovesDone::MovesDone(ShipCounter maxAmount) {
    setAmounts(maxAmount);
}

void MovesDone::changePlayer(ShipCounter maxAmount) {
    delete[] car;
    delete[] bat;
    delete[] des;
    delete[] cru;
    setAmounts(maxAmount);
}

bool MovesDone::moveCanBeMade(int numberOfShip, char classOfShip[3]) {

    if (!strcmp(classOfShip, "CAR")) {
        car[numberOfShip]++;
        if (car[numberOfShip] > 2)
            return false;
    }
    if (!strcmp(classOfShip, "BAT")) {
        bat[numberOfShip]++;
        if (bat[numberOfShip] > 3)
            return false;
    }
    if (!strcmp(classOfShip, "DES")) {
        des[numberOfShip]++;
        if (des[numberOfShip] > 3)
            return false;
    }
    if (!strcmp(classOfShip, "CRU")) {
        cru[numberOfShip]++;
        if (cru[numberOfShip] > 3)
            return false;
    }

    return true;
}

bool MovesDone::shotCanBeFired(int numberOfShip, char classOfShip[3]) {

    if (!strcmp(classOfShip, "CAR")) {
        car[numberOfShip]++;
        if (car[numberOfShip] > getSizeOfShip(classOfShip))
            return false;
    }
    if (!strcmp(classOfShip, "BAT")) {
        bat[numberOfShip]++;
        if (bat[numberOfShip] > getSizeOfShip(classOfShip))
            return false;
    }
    if (!strcmp(classOfShip, "DES")) {
        des[numberOfShip]++;
        if (des[numberOfShip] > getSizeOfShip(classOfShip))
            return false;
    }
    if (!strcmp(classOfShip, "CRU")) {
        cru[numberOfShip]++;
        if (cru[numberOfShip] > getSizeOfShip(classOfShip))
            return false;
    }

    return true;
}