#include <iostream>
using namespace std;

const int MAX_CAR = 1;
const int MAX_BAT = 2;
const int MAX_DES = 4;
const int MAX_CRU = 3;
const int SIZEX = 10;
const int SIZEY = 21;

struct field {
    char player;
    char state;
    bool reef;
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


void initialize(field board[21][10], rectangle* r1, rectangle* r2) {
    for (int yy = 0; yy < 21; yy++) {
        for (int xx = 0; xx < 10; xx++) {
            board[yy][xx].state = ' ';
        }
    }

    (*r1).x1 = 0;
    (*r1).y1 = 0;
    (*r1).x2 = 9;
    (*r1).y2 = 9;

    (*r2).x1 = 11;
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

void printError(char text[30]) {
    cout << "INVALID OPERATION ";
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
    if (!strcmp("CAR", shipClass)) {
        if (numberOfShip + 1 <= (*shipCounter).getCAR()) {
            return true;
        }
        // (*shipCounter).carIn();
    }
    else if (!strcmp("BAT", shipClass)) {
        if (numberOfShip + 1 <= (*shipCounter).getBAT()) {
            return true;
        }
        // (*shipCounter).batIn();
    }
    else if (!strcmp("DES", shipClass)) {
        if (numberOfShip + 1 <= (*shipCounter).getDES()) {
            return true;
        }
        //(*shipCounter).desIn();
    }
    else if (!strcmp("CRU", shipClass)) {
        if (numberOfShip + 1 <= (*shipCounter).getCRU()) {
            return true;
        }
        //(*shipCounter).cruIn();
    }

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
void shoot(field board[21][10], int x, int y) {

    if ((board[x][y]).state == '+')
        board[x][y].state = 'x';
}

int howManyRemaining(field board[21][10], char player) {
    int howMany = 0;
    for (int yy = 0; yy < 21; yy++) {
        for (int xx = 0; xx < 10; xx++) {
            if (board[yy][xx].state == '+' && board[yy][xx].player == player) howMany++;
        }
    }

    return howMany;
}
int howManyDestroyed(field board[21][10], char player) {
    int howMany = 0;
    for (int yy = 0; yy < 21; yy++) {
        for (int xx = 0; xx < 10; xx++) {
            if (board[yy][xx].state == 'x' && board[yy][xx].player == player) howMany++;
        }
    }
    return howMany;
}
void print0(field board[21][10]) {
    for (int yy = 0; yy < 21; yy++) {
        for (int xx = 0; xx < 10; xx++) {
            cout << board[yy][xx].state;
        }
        cout << endl;
    }
}
bool isInRectangle(int x, int y, rectangle r) {
    if (x >= r.x1 && x <= r.x2 && y >= r.y1 && y <= r.y2) return true;
    return false;
}
bool ifTooCloseToOthers(int y, int x, int i, int shipSize, field board[21][10], int boardSizeX, int boardSizeY) {

    int ile = 0;
    if (board[x][y].state == '+') return true;

    /*board[x][y].state = '%';
     print0(board);
     board[x][y].state = ' ';*/
    if (x != 0 and board[x - 1][y].state == '+') { ile++; }
    if (x != boardSizeY - 1 and board[x + 1][y].state == '+') { ile++; }
    if (y != 0 and board[x][y - 1].state == '+') { /*cout << " left " << i << endl;*/ ile++; }
    if (y != boardSizeX - 1 and board[x][y + 1].state == '+') { ile++; }

    if (i == 0) { ile++; }
    //cout << ile;
    if (ile > 1) return true;
    return false;
}
bool isSbAround(field board[21][10], int x, int y, char player) {

    char oponent;
    player == 'A' ? oponent = 'B' : oponent = 'A';

    if (board[y + 1][x].player == oponent || board[y - 1][x].player == oponent
        || board[y][x + 1].player == oponent || board[y][x - 1].player == oponent)
        return true;
    else return false;
}
int main()
{
    field board[21][10];
    int boardSizeY = 10;
    int boardSizeX = 21;
    char command[16], shipClass[4], lastCommand[16];
    int x, y, numberOfShip;
    char direction, mode;
    bool error = false;
    bool tooCloseError = false, onReefError = false, wentFromBoardError = false;
    bool flag;

    char currentPlayer = 'A';
    //temp
    char playerTemp;

    ShipCounter shipCounterA(0, 0, 0, 0);
    ShipCounter shipCounterB(0, 0, 0, 0);
    ShipCounter maxAmountOfShipA(1, 2, 4, 3);
    ShipCounter maxAmountOfShipB(1, 2, 4, 3);

    rectangle rectangleA, rectangleB;
    initialize(board, &rectangleA, &rectangleB); //zerowanie i stawianie spacji


    while (cin >> command && error == false) {

        if (strcmp("PLACE_SHIP", command) == 0) {
            cin >> x >> y >> direction >> numberOfShip >> shipClass;
            int sizeOfShip = getSizeOfShip(shipClass);

            if (((currentPlayer == 'A') && (!isInRectangle(x, y, rectangleA) || (direction == 'N' && !isInRectangle(x + sizeOfShip - 1, y, rectangleA)))
                || ((currentPlayer == 'B') && (!isInRectangle(x, y, rectangleB) || (direction == 'S' && !isInRectangle(x - sizeOfShip + 1, y, rectangleB)))))) {
                cout << "INVALID OPERATION \"PLACE_SHIP " << x << " " << y << " " << direction << " " << numberOfShip << " " << shipClass << "\": NOT IN STARTING POSITION" << endl;
                error = true;
                break;
            }

            if (direction == 'N') {
                for (int i = 0; i < sizeOfShip; i++) {
                    if (ifTooCloseToOthers(y, x + i, i, sizeOfShip, board, SIZEX, SIZEY)) tooCloseError = true;
                    if (board[x + i][y].reef == true) onReefError = true;
                    board[x + i][y].state = '+';
                    board[x + i][y].player = currentPlayer;
                    board[x + i][y].numberI = numberOfShip;
                    strcpy_s(board[x + i][y].classOfShip, shipClass);
                    board[x + i][y].direction = direction;
                }
            }
            else if (direction == 'S') {
                for (int i = 0; i < sizeOfShip; i++) {
                    if (ifTooCloseToOthers(y, x - i, i, sizeOfShip, board, SIZEX, SIZEY)) tooCloseError = true;
                    if (board[x - i][y].reef == true) onReefError = true;
                    board[x - i][y].state = '+';
                    board[x - i][y].player = currentPlayer;
                    board[x - i][y].numberI = numberOfShip;
                    strcpy_s(board[x - i][y].classOfShip, shipClass);
                    board[x - i][y].direction = direction;
                }
            }
            else if (direction == 'W') {
                for (int i = 0; i < sizeOfShip; i++) {
                    if (ifTooCloseToOthers(y + i, x, i, sizeOfShip, board, SIZEX, SIZEY)) tooCloseError = true;
                    if (board[x][y + i].reef == true) onReefError = true;
                    board[x][y + i].state = '+';
                    board[x][y + i].player = currentPlayer;
                    board[x][y + i].numberI = numberOfShip;
                    strcpy_s(board[x][y + i].classOfShip, shipClass);
                    board[x][y + i].direction = direction;
                }
            }
            else {
                for (int i = 0; i < sizeOfShip; i++) {
                    if (ifTooCloseToOthers(y - i, x, i, sizeOfShip, board, SIZEX, SIZEY)) tooCloseError = true;
                    if (board[x][y - i].reef == true) onReefError = true;
                    board[x][y - i].state = '+';
                    board[x][y - i].player = currentPlayer;
                    board[x][y - i].numberI = numberOfShip;
                    strcpy_s(board[x][y - i].classOfShip, shipClass);
                    board[x][y - i].direction = direction;
                }
            }
            //print0(board);
            if (tooCloseError) {
                cout << "INVALID OPERATION \"PLACE_SHIP " << x << " " << y << " " << direction << " " << numberOfShip << " " << shipClass << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
                break;
            }
            if (onReefError) {
                cout << "INVALID OPERATION \"PLACE_SHIP " << x << " " << y << " " << direction << " " << numberOfShip << " " << shipClass << "\": PLACING SHIP ON REEF" << endl;
                break;
            }

            if (currentPlayer == 'B') {

                //czy pokolej stawiane
                if (ifShipAlreadyPresent(shipClass, numberOfShip, &shipCounterB)) {
                    cout << "INVALID OPERATION \"PLACE_SHIP " << x << " " << y << " " << direction << " " << numberOfShip << " " << shipClass << "\": SHIP ALREADY PRESENT" << endl;
                    error = true;
                    break;
                }
                //czy mamskymalna ilosc
                if (ifAllShipOfTheClassAlreadySet(shipCounterB, shipClass, maxAmountOfShipB)) {
                    cout << "INVALID OPERATION \"PLACE_SHIP " << x << " " << y << " " << direction << " " << numberOfShip << " " << shipClass << "\": ALL SHIPS OF THE CLASS ALREADY SET" << endl;
                    error = true;
                    break;
                }

                incrementShipCounter(shipClass, &shipCounterB);
            }
            else { //player a


            //czy pokolej stawiane
                if (ifShipAlreadyPresent(shipClass, numberOfShip, &shipCounterA)) {
                    cout << "INVALID OPERATION \"PLACE_SHIP " << x << " " << y << " " << direction << " " << numberOfShip << " " << shipClass << "\": SHIP ALREADY PRESENT" << endl;
                    error = true;
                    break;
                }
                //czy mamskymalna ilosc
                if (ifAllShipOfTheClassAlreadySet(shipCounterA, shipClass, maxAmountOfShipA)) {
                    cout << "INVALID OPERATION \"PLACE_SHIP " << x << " " << y << " " << direction << " " << numberOfShip << " " << shipClass << "\": ALL SHIPS OF THE CLASS ALREADY SET" << endl;
                    error = true;
                    break;
                }
                incrementShipCounter(shipClass, &shipCounterA);
            }
        }

        else if (strcmp("PRINT", command) == 0) {
            cin >> mode;
            if (mode == '0') print0(board);

            if (!strcmp("[state]", lastCommand)) {
                cout << "PARTS REMAINING:: A : " << howManyRemaining(board, 'A') << " B : " << howManyRemaining(board, 'B') << endl;
            }
        }
        else if (strcmp("[playerA]", command) == 0) {
            currentPlayer = 'A';
            if (!strcmp("[playerA]", lastCommand)) {
                cout << "INVALID OPERATION \"[playerA] \": THE OTHER PLAYER EXPECTED" << endl;
                break;
            }

        }
        else if (strcmp("[playerB]", command) == 0) {
            currentPlayer = 'B';
            if (!strcmp("[playerB]", lastCommand)) {
                cout << "INVALID OPERATION \"[playerB] \": THE OTHER PLAYER EXPECTED" << endl;
                break;
            }

        }
        else if (!strcmp("SHOOT", command)) {
            cin >> x >> y;

            if (!ifAllShipsAlreadySet(shipCounterA, maxAmountOfShipA) || !ifAllShipsAlreadySet(shipCounterB, maxAmountOfShipB)) {
                cout << "INVALID OPERATION \"SHOOT " << x << " " << y << "\": NOT ALL SHIPS PLACED" << endl;
                break;
            }

            if (x <= boardSizeX && y <= boardSizeY)
                shoot(board, x, y);
            else {
                cout << "INVALID OPERATION \"SHOOT " << x << " " << y << "\": FIELD DOES NOT EXIST" << endl;
                break;
            }
        }
        else if (!strcmp("SET_FLEET", command)) {

            int car, bat, des, cru;
            cin >> playerTemp >> car >> bat >> cru >> des;

            if (playerTemp == 'A') maxAmountOfShipA.setAll(car, bat, des, cru);
            else maxAmountOfShipB.setAll(car, bat, des, cru);
        }
        else if (!strcmp("SHIP", command)) {

            cin >> playerTemp >> x >> y >> direction >> numberOfShip >> shipClass;
            int sizeOfShip = getSizeOfShip(shipClass);
            char* sequence = new char[sizeOfShip];
            cin >> sequence;

            if (direction == 'N') {
                for (int i = 0; i < sizeOfShip; i++) {
                    if (ifTooCloseToOthers(y, x + i, i, sizeOfShip, board, SIZEX, SIZEY)) tooCloseError = true;
                    if (board[x + i][y].reef == true) onReefError = true;
                    sequence[i] == '1' ? board[x + i][y].state = '+' : board[x + i][y].state = 'x';
                    board[x + i][y].player = playerTemp;
                    board[x + i][y].direction = direction;
                }
            }
            else if (direction == 'S') {
                for (int i = 0; i < sizeOfShip; i++) {
                    if (ifTooCloseToOthers(y, x - i, i, sizeOfShip, board, SIZEX, SIZEY)) tooCloseError = true;
                    if (board[x - i][y].reef == true) onReefError = true;
                    sequence[i] == '1' ? board[x - i][y].state = '+' : board[x - i][y].state = 'x';
                    board[x - i][y].player = playerTemp;
                    board[x - i][y].direction = direction;
                }
            }
            else if (direction == 'W') {
                for (int i = 0; i < sizeOfShip; i++) {
                    if (ifTooCloseToOthers(y + i, x, i, sizeOfShip, board, SIZEX, SIZEY)) tooCloseError = true;
                    if (board[x][y + i].reef == true) onReefError = true;
                    sequence[i] == '1' ? board[x][y + i].state = '+' : board[x][y + i].state = 'x';
                    board[x][y + i].player = playerTemp;
                    board[x][y + i].direction = direction;
                }
            }
            else {
                for (int i = 0; i < sizeOfShip; i++) {
                    if (ifTooCloseToOthers(y - i, x, i, sizeOfShip, board, SIZEX, SIZEY)) tooCloseError = true;
                    if (board[x][y - i].reef == true) onReefError = true;
                    sequence[i] == '1' ? board[x][y - i].state = '+' : board[x][y - i].state = 'x';
                    board[x][y - i].player = playerTemp;
                    board[x][y - i].direction = direction;
                }
            }

            if (tooCloseError) {
                cout << "INVALID OPERATION \"SHIP " << playerTemp << " " << x << " " << y << " " << direction << " " << numberOfShip << " " << shipClass << " " << sequence << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
                break;
            }
            if (onReefError) {
                cout << "INVALID OPERATION \"SHIP " << playerTemp << " " << x << " " << y << " " << direction << " " << numberOfShip << " " << shipClass << " " << sequence << "\": PLACING SHIP ON REEF" << endl;
                break;
            }


            {
                if (playerTemp == 'B') {

                    //czy pokolej stawiane
                    if (ifShipAlreadyPresent(shipClass, numberOfShip, &shipCounterB)) {
                        cout << "INVALID OPERATION \"PLACE_SHIP " << x << " " << y << " " << direction << " " << numberOfShip << " " << shipClass << "\": SHIP ALREADY PRESENT" << endl;
                        error = true;
                        break;
                    }
                    //czy mamskymalna ilosc
                    if (ifAllShipOfTheClassAlreadySet(shipCounterB, shipClass, maxAmountOfShipB)) {
                        cout << "INVALID OPERATION \"PLACE_SHIP " << x << " " << y << " " << direction << " " << numberOfShip << " " << shipClass << "\": ALL SHIPS OF THE CLASS ALREADY SET" << endl;
                        error = true;
                        break;
                    }
                    incrementShipCounter(shipClass, &shipCounterB);
                }
                else { //player a


                //czy pokolej stawiane
                    if (ifShipAlreadyPresent(shipClass, numberOfShip, &shipCounterA)) {
                        cout << "INVALID OPERATION \"PLACE_SHIP " << x << " " << y << " " << direction << " " << numberOfShip << " " << shipClass << "\": SHIP ALREADY PRESENT" << endl;
                        error = true;
                        break;
                    }
                    //czy mamskymalna ilosc
                    if (ifAllShipOfTheClassAlreadySet(shipCounterA, shipClass, maxAmountOfShipA)) {
                        cout << "INVALID OPERATION \"PLACE_SHIP " << x << " " << y << " " << direction << " " << numberOfShip << " " << shipClass << "\": ALL SHIPS OF THE CLASS ALREADY SET" << endl;
                        error = true;
                        break;
                    }
                    incrementShipCounter(shipClass, &shipCounterA);
                }
            }
            // print0(board);

        }
        else if (!strcmp("NEXT_PLAYER", command)) {
            cin >> currentPlayer;
        }
        else if (!strcmp("INIT_POSITION", command)) {
            cin >> playerTemp;
            if (playerTemp == 'A')
                cin >> rectangleA.x1 >> rectangleA.y1 >> rectangleA.x2 >> rectangleA.y2;
            else
                cin >> rectangleB.x1 >> rectangleB.y1 >> rectangleB.x2 >> rectangleB.y2;
        }
        else if (!strcmp("REEF", command)) {
            cin >> x >> y;
            board[x][y].reef = true;
        }
        else if (!strcmp("MOVE", command)) {
            cin >> numberOfShip >> shipClass >> direction;

            field copy[21][10];

            for (int yy = 0; yy < 21; yy++) {
                for (int xx = 0; xx < 10; xx++) {
                    copy[yy][xx] = board[yy][xx];
                    if (board[yy][xx].numberI == numberOfShip && !strcmp(board[yy][xx].classOfShip, shipClass) && board[yy][xx].player == currentPlayer) {
                        copy[yy][xx].state = 'j';
                        board[yy][xx].player = ' ';
                        board[yy][xx].state = ' ';
                        strcpy_s(board[yy][xx].classOfShip, " ");
                        board[yy][xx].numberI = -1;
                        board[yy][xx].direction = ' ';
                    }
                }
            }
            /*cout << "copy  ------------------" << endl;
            print0(copy);
            cout << "------------------" << endl;*/


            if (direction == 'F') {

                for (int yy = 0; yy < 21; yy++) {
                    for (int xx = 0; xx < 10; xx++) {

                        if (copy[yy][xx].numberI == numberOfShip && !strcmp(copy[yy][xx].classOfShip, shipClass) && copy[yy][xx].player == currentPlayer) {
                            if (/*yy < 20 &&*/ copy[yy][xx].state == 'j') {
                                if (copy[yy][xx].direction == 'N') {
                                    if (isSbAround(board, xx, yy-1, currentPlayer)) tooCloseError = true;
                                    board[yy - 1][xx] = copy[yy][xx];
                                    board[yy - 1][xx].state = '+';
                                }
                                else if (copy[yy][xx].direction == 'W') {
                                    if (isSbAround(board, xx-1, yy, currentPlayer)) tooCloseError = true;
                                    if (yy <0 || xx - 1 < 0 || xx - 1 > SIZEX || yy>SIZEY) wentFromBoardError = true;
                                    board[yy][xx - 1] = copy[yy][xx];
                                    board[yy][xx - 1].state = '+';
                                }
                                else if (copy[yy][xx].direction == 'E') {
                                    if (isSbAround(board, xx + 1, yy, currentPlayer)) tooCloseError = true;
                                    board[yy][xx + 1] = copy[yy][xx];
                                    board[yy][xx + 1].state = '+';
                                }
                                else if (copy[yy][xx].direction == 'S') {
                                    if (isSbAround(board, xx, yy + 1, currentPlayer)) tooCloseError = true;
                                    board[yy + 1][xx] = copy[yy][xx];
                                    board[yy + 1][xx].state = '+';
                                }
                            }
                        }
                    }
                }

            }
            else if (direction == 'L') {
                flag = true;
                for (int yy = 0; yy < 21 && flag; yy++) {
                    for (int xx = 0; xx < 10; xx++) {
                        if (copy[yy][xx].numberI == numberOfShip && !strcmp(copy[yy][xx].classOfShip, shipClass) && copy[yy][xx].player == currentPlayer) {
                            for (int i = 0; i < getSizeOfShip(shipClass); i++) {
                                if (copy[yy][xx].direction == 'N') {
                                    if (isSbAround(board, xx - i, yy, currentPlayer)) tooCloseError = true;
                                    board[yy][xx - i] = copy[yy][xx];
                                    board[yy][xx - i].direction = 'E';
                                    board[yy][xx - i].state = '+';
                                }
                                else if (copy[yy][xx].direction == 'E') {
                                    if (isSbAround(board, xx -1, yy + i, currentPlayer)) tooCloseError = true;
                                    board[yy + i][xx - 1] = copy[yy][xx];
                                    board[yy + i][xx - 1].direction = 'S';
                                    board[yy + i][xx - 1].state = '+';
                                }
                                else if (copy[yy][xx].direction == 'S') {
                                    if (isSbAround(board, xx + 1 + i, yy, currentPlayer)) tooCloseError = true;
                                    board[yy][xx + 1 + i] = copy[yy][xx];
                                    board[yy][xx + 1 + i].direction = 'W';
                                    board[yy][xx + 1 + i].state = '+';
                                }
                                else if (copy[yy][xx].direction == 'W') {
                                    if (isSbAround(board, xx, yy - i + 1, currentPlayer)) tooCloseError = true;
                                    board[yy - i + 1][xx] = copy[yy][xx];
                                    board[yy - i + 1][xx].direction = 'N';
                                    board[yy - i + 1][xx].state = '+';
                                }
                            }
                            flag = false;
                            break;
                        }
                    }
                }
            }
            else if (direction == 'R') {
                flag = true;
                for (int yy = 0; yy < 21 && flag; yy++) {
                    for (int xx = 0; xx < 10; xx++) {
                        if (copy[yy][xx].numberI == numberOfShip && !strcmp(copy[yy][xx].classOfShip, shipClass) && copy[yy][xx].player == currentPlayer) {
                            for (int i = 0; i < getSizeOfShip(shipClass); i++) {
                                if (copy[yy][xx].direction == 'N') {
                                    if (isSbAround(board, xx+1, yy, currentPlayer)) tooCloseError = true;
                                    board[yy][xx + i] = copy[yy][xx];
                                    board[yy][xx + i].direction = 'W';
                                    board[yy][xx + i].state = '+';
                                }
                                if (copy[yy][xx].direction == 'W') {
                                    if (isSbAround(board, xx + 1, yy -i, currentPlayer)) tooCloseError = true;
                                    board[yy - i][xx + 1] = copy[yy][xx];
                                    board[yy - i][xx + 1].direction = 'N';
                                    board[yy - i][xx + 1].state = '+';
                                }//_________________________________________ TO NIE DZIALA WGL
                                if (copy[yy][xx].direction == 'S') {
                                    if (isSbAround(board, xx + 1, yy - i, currentPlayer)) tooCloseError = true;
                                    board[yy - i][xx + 1] = copy[yy][xx];
                                    board[yy - i][xx + 1].direction = 'N';
                                    board[yy - i][xx + 1].state = '+';
                                }
                                if (copy[yy][xx].direction == 'E') {
                                    if (isSbAround(board, xx + 1, yy - i, currentPlayer)) tooCloseError = true;
                                    board[yy - i][xx + 1] = copy[yy][xx];
                                    board[yy - i][xx + 1].direction = 'N';
                                    board[yy - i][xx + 1].state = '+';
                                }//____________________________
                            }
                            flag = false;
                            break;
                        }
                    }
                }
            }
            /*cout << "real  ------------------" << endl;
                           print0(board);
                           cout << "------------------" << endl;*/
            if (tooCloseError) {
                cout << "INVALID OPERATION \"MOVE " << numberOfShip << " " << shipClass << " " << direction<< "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
                break;
            }
            if (wentFromBoardError) {
                cout << "INVALID OPERATION \"MOVE " << numberOfShip << " " << shipClass << " " << direction << "\": SHIP WENT FROM BOARD" << endl;
                break;
            }

        }

        strncpy_s(lastCommand, command, 16);
        //chceck if sb won
        if (howManyRemaining(board, 'A') == 0 && howManyDestroyed(board, 'A') > 0) {
            cout << "B won" << endl;
            break;
        }
        if (howManyRemaining(board, 'B') == 0 && howManyDestroyed(board, 'B') > 0) {
            cout << "A won" << endl;
            break;
        }
    }

}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
