#ifndef funkcje_h
#define funkcje_h

struct field {
    char player;
    char state;
    bool reef, cannon, engine, radar, avaibleForPlayer, spyA, spyB;
    int numberI;
    char classOfShip[4];
    char direction;
};

struct rectangle {
    int x1, x2, y1, y2;
};

class ShipCounter {
public:
    int CAR, BAT, DES, CRU;

    ShipCounter(int car, int bat, int des, int cru) {
        CAR = car;
        BAT = bat;
        DES = des;
        CRU = cru;
    }
    void carIn() {
        CAR++;
    }
    int getCAR() {
        return CAR;
    }
    int getBAT() {
        return BAT;
    }
    void batIn() {
        BAT++;
    }
    int getDES() {
        return DES;
    }
    void desIn() {
        DES++;
    }
    int getCRU() {
        return CRU;
    }
    void cruIn() {
        CRU++;
    }

    void setAll(int car, int bat, int des, int cru) {
        CAR = car;
        BAT = bat;
        DES = des;
        CRU = cru;
    }
};

class MovesDone {
    int* car;
    int* bat;
    int* des;
    int* cru;
private:
    void setAmounts(ShipCounter maxAmount);

public:
    MovesDone(ShipCounter maxAmount);
    void changePlayer(ShipCounter maxAmount);
    bool moveCanBeMade(int numberOfShip, char classOfShip[3]);
    bool shotCanBeFired(int numberOfShip, char classOfShip[3]);
};

int getIndex(int x, int y, int customWidth);

void initialize(field board[], rectangle* r1, rectangle* r2, int BOARD_W, int BOARD_H);

int getSizeOfShip(char type[3]);

void incrementShipCounter(char shipClass[3], ShipCounter* shipCounter);

bool ifShipAlreadyPresent(char shipClass[3], int numberOfShip, ShipCounter* shipCounter);

bool ifAllShipOfTheClassAlreadySet(ShipCounter shipCounter, char shipClass[3], ShipCounter max);

bool ifAllShipsAlreadySet(ShipCounter shipCounter, ShipCounter max);

void shoot(field board[], int x, int y, int boardWith);

int howManyRemaining(field board[], char player, int BOARD_W, int BOARD_H);

int howManyDestroyed(field board[], char player, int BOARD_H, int BOARD_W);

void print0(field board[], int BOARD_H, int BOARD_W);

void print1(field board[], int BOARD_H, int BOARD_W);

bool isInRectangle(int x, int y, rectangle r);

bool ifTooCloseToOthers(int x, int y, int i, int shipSize, field board[], int boardSizeX, int boardSizeY);

bool isSbAround(field board[], int x, int y, char player, int BOARD_H, int BOARD_W);

int getIndexOfCannon(field board[], char classOfShip[], int nummberOfShip, char player, int BOARD_W, int BOARD_H, bool xy);

void printPlayerPerspective(field board[], int boardSizeX, int boardSizeY, char player);

void spy(field board[], int x, int y, int boardSizeX, int boardSizeY, char player);

#endif