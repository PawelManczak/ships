#include <iostream>
#include "funkcje.h"
#include "placeShip.h"
using namespace std;

const int MAX_CAR = 1;
const int MAX_BAT = 2;
const int MAX_DES = 4;
const int MAX_CRU = 3;
const int SIZEX = 10;
const int SIZEY = 21;
const char DEFAULT_COMMAND[16] = "def";


int main()
{
    int boardSizeY = 21;
    int boardSizeX = 10;
    field* board = new field[boardSizeX * boardSizeY];

    char command[16], shipClass[4], lastCommand[16] = " ", lastLastCommand[16] = " ";
    int x, y, numberOfShip;
    char direction, mode;
    bool error = false;
    bool tooCloseError = false, onReefError = false, wentFromBoardError = false;
    bool flag;
    bool extendedShips = false;

    int cannonX, cannonY;

    char currentPlayer = 'A';
    char playerTemp;
    bool state = false;

    ShipCounter shipCounterA(0, 0, 0, 0);
    ShipCounter shipCounterB(0, 0, 0, 0);
    ShipCounter maxAmountOfShipA(1, 2, 4, 3);
    ShipCounter maxAmountOfShipB(1, 2, 4, 3);

    rectangle rectangleA, rectangleB;
    initialize(board, &rectangleA, &rectangleB, boardSizeX, boardSizeY); //zerowanie i stawianie spacji

    MovesDone md = MovesDone(maxAmountOfShipA);
    MovesDone shotsFired = MovesDone(maxAmountOfShipA);

    while (cin >> command && error == false) {


        if (strcmp("PLACE_SHIP", command) == 0) {
            cin >> x >> y >> direction >> numberOfShip >> shipClass;
            int sizeOfShip = getSizeOfShip(shipClass);

            if (((currentPlayer == 'A') && (!isInRectangle(x, y, rectangleA) || (direction == 'N' && !isInRectangle(x + sizeOfShip - 1, y, rectangleA)))
                || ((currentPlayer == 'B') && (!isInRectangle(x, y, rectangleB) || (direction == 'S' && !isInRectangle(x - sizeOfShip + 1, y, rectangleB)))))) {
                cout << "INVALID OPERATION \"PLACE_SHIP " << x << " " << y << " " << direction << " " << numberOfShip << " " << shipClass << "\": NOT IN STARTING POSITION" << endl;
                break;
            }

            if (direction == 'N') {
                for (int i = 0; i < sizeOfShip; i++) {
                    if (ifTooCloseToOthers(y, x + i, i, sizeOfShip, board, boardSizeX, boardSizeY)) tooCloseError = true;
                    if (board[getIndex(y, x + i, boardSizeX)].reef == true) onReefError = true;
                }
                placeShipN(board, x, y, sizeOfShip, boardSizeX, currentPlayer, numberOfShip, shipClass, direction);
            }
            else if (direction == 'S') {
                for (int i = 0; i < sizeOfShip; i++) {
                    if (ifTooCloseToOthers(y, x - i, i, sizeOfShip, board, boardSizeX, boardSizeY)) tooCloseError = true;
                    if (board[getIndex(y, x - i, boardSizeX)].reef == true) onReefError = true;
                }
                placeShipS(board, x, y, sizeOfShip, boardSizeX, currentPlayer, numberOfShip, shipClass, direction);
            }
            else if (direction == 'W') {
                for (int i = 0; i < sizeOfShip; i++) {
                    if (ifTooCloseToOthers(y + i, x, i, sizeOfShip, board, boardSizeX, boardSizeY)) tooCloseError = true;
                    if (board[getIndex(y + i, x, boardSizeX)].reef == true) onReefError = true;     
                }
                placeShipW(board, x, y, sizeOfShip, boardSizeX, currentPlayer, numberOfShip, shipClass, direction);
            }
            else if (direction == 'E') {
                for (int i = 0; i < sizeOfShip; i++) {
                    if (ifTooCloseToOthers(y - i, x, i, sizeOfShip, board, boardSizeX, boardSizeY)) tooCloseError = true;
                    if (board[getIndex(y - i, x, boardSizeX)].reef == true) onReefError = true;
                }
                placeShipE(board, x, y, sizeOfShip, boardSizeX, currentPlayer, numberOfShip, shipClass, direction);
            }

            if (tooCloseError) {
                cout << "INVALID OPERATION \"PLACE_SHIP " << x << " " << y << " " << direction << " " << numberOfShip << " " << shipClass << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
                break;
            }
            if (onReefError) {
                cout << "INVALID OPERATION \"PLACE_SHIP " << x << " " << y << " " << direction << " " << numberOfShip << " " << shipClass << "\": PLACING SHIP ON REEF" << endl;
                break;
            }

            if ((currentPlayer == 'B' && ifShipAlreadyPresent(shipClass, numberOfShip, &shipCounterB) == true) ||
                (currentPlayer == 'A' && ifShipAlreadyPresent(shipClass, numberOfShip, &shipCounterA) == true)) {
                cout << "INVALID OPERATION \"PLACE_SHIP " << x << " " << y << " " << direction << " " << numberOfShip << " " << shipClass << "\": SHIP ALREADY PRESENT" << endl;
                break;
            }
            if ((currentPlayer == 'B' && ifAllShipOfTheClassAlreadySet(shipCounterB, shipClass, maxAmountOfShipB) == true) ||
                (currentPlayer == 'A' && ifAllShipOfTheClassAlreadySet(shipCounterA, shipClass, maxAmountOfShipA) == true)) {
                cout << "INVALID OPERATION \"PLACE_SHIP " << x << " " << y << " " << direction << " " << numberOfShip << " " << shipClass << "\": ALL SHIPS OF THE CLASS ALREADY SET" << endl;
                break;
            }
                currentPlayer == 'A' ? incrementShipCounter(shipClass, &shipCounterA) :  incrementShipCounter(shipClass, &shipCounterB);
               
            }
          

        else if (strcmp("PRINT", command) == 0) {
            cin >> mode;
            if (mode == '0') {
                if (!state)  printPlayerPerspective(board, boardSizeX, boardSizeY, currentPlayer);
                else print0(board, boardSizeY, boardSizeX);
            }
            if (mode == '1') {
                print1(board, boardSizeY, boardSizeX);
            }

            if (!strcmp("[state]", lastCommand)) {
                cout << "PARTS REMAINING:: A : " << howManyRemaining(board, 'A', boardSizeY, boardSizeX) << " B : " << howManyRemaining(board, 'B', boardSizeY, boardSizeX) << endl;
            }
        }
        else if (strcmp("[playerA]", command) == 0) {
            md.changePlayer(maxAmountOfShipA);
            shotsFired.changePlayer(maxAmountOfShipA);
            currentPlayer = 'A';
            if (!strcmp("[playerA]", lastCommand) && !extendedShips
                || !strcmp("[playerA]", lastCommand) && extendedShips && !strcmp("[playerA]", lastLastCommand)) {
                cout << "INVALID OPERATION \"[playerA] \": THE OTHER PLAYER EXPECTED" << endl;
                break;
            }

        }
        else if (strcmp("[playerB]", command) == 0) {
            md.changePlayer(maxAmountOfShipB);
            shotsFired.changePlayer(maxAmountOfShipB);
            currentPlayer = 'B';
            if (!strcmp("[playerB]", lastCommand) && !extendedShips
                || !strcmp("[playerB]", lastCommand) && extendedShips && !strcmp("[playerB]", lastLastCommand)) {
                cout << "INVALID OPERATION \"[playerB] \": THE OTHER PLAYER EXPECTED" << endl;
                break;
            }

        }
        else if (!strcmp("SHOOT", command)) {
            if (extendedShips) cin >> numberOfShip >> shipClass;

            cin >> y >> x;

            if (!ifAllShipsAlreadySet(shipCounterA, maxAmountOfShipA) || !ifAllShipsAlreadySet(shipCounterB, maxAmountOfShipB)) {
                cout << "INVALID OPERATION \"SHOOT " << y << " " << x << "\": NOT ALL SHIPS PLACED" << endl;
                break;
            }

            if (x <= boardSizeX && y <= boardSizeY) {

                //if ship can shoot
                if (!shotsFired.shotCanBeFired(numberOfShip, shipClass)) {
                    cout << "INVALID OPERATION \"SHOOT " << numberOfShip << " " << shipClass << " " << y << " " << x << "\": TOO MANY SHOOTS" << endl;
                    break;
                }
                //if disance is ok
                if (extendedShips) {
                    cannonX = getIndexOfCannon(board, shipClass, numberOfShip, currentPlayer, boardSizeX, boardSizeY, true);
                    cannonY = getIndexOfCannon(board, shipClass, numberOfShip, currentPlayer, boardSizeX, boardSizeY, false);
                }
                if (extendedShips && strcmp("CAR", shipClass)) {

                    float distance = sqrt(pow(abs(y - cannonY), 2) + pow(abs(x - cannonX), 2));

                    if (distance > getSizeOfShip(shipClass)) {
                        cout << "INVALID OPERATION \"SHOOT " << numberOfShip << " " << shipClass << " " << y << " " << x << "\": SHOOTING TOO FAR" << endl;
                        break;
                    }
                }
                //if cannon is ok
                if (extendedShips) {
                    if (board[getIndex(cannonX, cannonY, boardSizeX)].state == 'x') {
                        cout << "INVALID OPERATION \"SHOOT " << numberOfShip << " " << shipClass << " " << y << " " << x << "\": SHIP CANNOT SHOOT" << endl;
                        break;
                    }
                }
                shoot(board, x, y, boardSizeX);

            }
            else {
                cout << "INVALID OPERATION \"SHOOT " << y << " " << x << "\": FIELD DOES NOT EXIST" << endl;
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
                    if (board[getIndex(y, x + i, boardSizeX)].reef == true) onReefError = true;
                    sequence[i] == '1' ? board[getIndex(y, x + i, boardSizeX)].state = '+' : board[getIndex(y, x + i, boardSizeX)].state = 'x';
                    board[getIndex(y, x + i, boardSizeX)].player = playerTemp;
                    board[getIndex(y, x + i, boardSizeX)].direction = direction;
                }
            }
            else if (direction == 'S') {
                for (int i = 0; i < sizeOfShip; i++) {
                    if (ifTooCloseToOthers(y, x - i, i, sizeOfShip, board, SIZEX, SIZEY)) tooCloseError = true;
                    if (board[getIndex(y, x - i, boardSizeX)].reef == true) onReefError = true;
                    sequence[i] == '1' ? board[getIndex(y, x - i, boardSizeX)].state = '+' : board[getIndex(y, x - i, boardSizeX)].state = 'x';
                    board[getIndex(y, x - i, boardSizeX)].player = playerTemp;
                    board[getIndex(y, x - i, boardSizeX)].direction = direction;
                }
            }
            else if (direction == 'W') {
                for (int i = 0; i < sizeOfShip; i++) {
                    if (ifTooCloseToOthers(y + i, x, i, sizeOfShip, board, SIZEX, SIZEY)) tooCloseError = true;
                    if (board[getIndex(y + i, x, boardSizeX)].reef == true) onReefError = true;
                    sequence[i] == '1' ? board[getIndex(y + i, x, boardSizeX)].state = '+' : board[getIndex(y + i, x, boardSizeX)].state = 'x';
                    board[getIndex(y + i, x, boardSizeX)].player = playerTemp;
                    board[getIndex(y + i, x, boardSizeX)].direction = direction;
                }
            }
            else {
                for (int i = 0; i < sizeOfShip; i++) {
                    if (ifTooCloseToOthers(y - i, x, i, sizeOfShip, board, SIZEX, SIZEY)) tooCloseError = true;
                    if (board[getIndex(y - i, x, boardSizeX)].reef == true) onReefError = true;
                    sequence[i] == '1' ? board[getIndex(y - i, x, boardSizeX)].state = '+' : board[getIndex(y - i, x, boardSizeX)].state = 'x';
                    board[getIndex(y - i, x, boardSizeX)].player = playerTemp;
                    board[getIndex(y - i, x, boardSizeX)].direction = direction;
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
            cin >> y >> x;
            board[getIndex(x, y, boardSizeX)].reef = true;
        }
        else if (!strcmp("MOVE", command)) {


            cin >> numberOfShip >> shipClass >> direction;
            if (!md.moveCanBeMade(numberOfShip, shipClass)) {
                cout << "INVALID OPERATION \"MOVE " << numberOfShip << " " << shipClass << " " << direction << "\": SHIP MOVED ALREADY" << endl;
                break;
            }
            field* copy = new field[boardSizeX * boardSizeY];;


            for (int yy = 0; yy < 21; yy++) {
                for (int xx = 0; xx < 10; xx++) {
                    copy[getIndex(xx, yy, boardSizeX)] = board[getIndex(xx, yy, boardSizeX)];
                    if (board[getIndex(xx, yy, boardSizeX)].numberI == numberOfShip && !strcmp(board[getIndex(xx, yy, boardSizeX)].classOfShip, shipClass) && board[getIndex(xx, yy, boardSizeX)].player == currentPlayer) {
                        copy[getIndex(xx, yy, boardSizeX)].state = 'j';
                        board[getIndex(xx, yy, boardSizeX)].player = ' ';
                        board[getIndex(xx, yy, boardSizeX)].state = ' ';
                        strcpy_s(board[getIndex(xx, yy, boardSizeX)].classOfShip, " ");
                        board[getIndex(xx, yy, boardSizeX)].numberI = -1;
                        board[getIndex(xx, yy, boardSizeX)].direction = ' ';
                    }
                }
            }

            if (direction == 'F') {

                for (int yy = 0; yy < 21; yy++) {
                    for (int xx = 0; xx < 10; xx++) {

                        if (copy[getIndex(xx, yy, boardSizeX)].numberI == numberOfShip && !strcmp(copy[getIndex(xx, yy, boardSizeX)].classOfShip, shipClass) && copy[getIndex(xx, yy, boardSizeX)].player == currentPlayer) {
                            if (copy[getIndex(xx, yy, boardSizeX)].state == 'j') {
                                if (copy[getIndex(xx, yy, boardSizeX)].direction == 'N') {
                                    if (isSbAround(board, xx, yy - 1, currentPlayer, boardSizeY, boardSizeX)) tooCloseError = true;
                                    if (yy - 1 < 0 || xx < 0 || xx> SIZEX || yy - 1 > SIZEY) wentFromBoardError = true;
                                    board[getIndex(xx, yy - 1, boardSizeX)] = copy[getIndex(xx, yy, boardSizeX)];
                                    board[getIndex(xx, yy - 1, boardSizeX)].state = '+';
                                }
                                else if (copy[getIndex(xx, yy, boardSizeX)].direction == 'W') {
                                    if (isSbAround(board, xx - 1, yy, currentPlayer, boardSizeY, boardSizeX)) tooCloseError = true;
                                    if (yy <0 || xx - 1 < 0 || xx - 1 > SIZEX || yy>SIZEY) wentFromBoardError = true;
                                    board[getIndex(xx - 1, yy, boardSizeX)] = copy[getIndex(xx, yy, boardSizeX)];
                                    board[getIndex(xx - 1, yy, boardSizeX)].state = '+';
                                }
                                else if (copy[getIndex(xx, yy, boardSizeX)].direction == 'E') {
                                    if (isSbAround(board, xx + 1, yy, currentPlayer, boardSizeY, boardSizeX)) tooCloseError = true;
                                    if (yy <0 || xx + 1 < 0 || xx + 1 > SIZEX || yy>SIZEY) wentFromBoardError = true;
                                    board[getIndex(xx + 1, yy, boardSizeX)] = copy[getIndex(xx, yy, boardSizeX)];
                                    board[getIndex(xx + 1, yy, boardSizeX)].state = '+';
                                }
                                else if (copy[getIndex(xx, yy, boardSizeX)].direction == 'S') {
                                    if (isSbAround(board, xx, yy + 1, currentPlayer, boardSizeY, boardSizeX)) tooCloseError = true;
                                    if (yy + 1 < 0 || xx < 0 || xx > SIZEX || yy + 1 > SIZEY) wentFromBoardError = true;
                                    board[getIndex(xx, yy + 1, boardSizeX)] = copy[getIndex(xx, yy, boardSizeX)];
                                    board[getIndex(xx, yy + 1, boardSizeX)].state = '+';
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
                        if (copy[getIndex(xx, yy, boardSizeX)].numberI == numberOfShip && !strcmp(copy[getIndex(xx, yy, boardSizeX)].classOfShip, shipClass) && copy[getIndex(xx, yy, boardSizeX)].player == currentPlayer) {
                            for (int i = 0; i < getSizeOfShip(shipClass); i++) {
                                if (copy[getIndex(xx, yy, boardSizeX)].direction == 'N') {
                                    if (isSbAround(board, xx - i, yy, currentPlayer, boardSizeY, boardSizeX)) tooCloseError = true;
                                    if (yy < 0 || xx - i < 0 || xx - i > SIZEX || yy > SIZEY) wentFromBoardError = true;
                                    board[getIndex(xx - i, yy, boardSizeX)] = copy[getIndex(xx, yy, boardSizeX)];
                                    board[getIndex(xx - i, yy, boardSizeX)].direction = 'E';
                                    board[getIndex(xx - i, yy, boardSizeX)].state = '+';
                                }
                                else if (copy[getIndex(xx, yy, boardSizeX)].direction == 'E') {
                                    if (isSbAround(board, xx - 1, yy + i, currentPlayer, boardSizeY, boardSizeX)) tooCloseError = true;
                                    if (yy + i < 0 || xx - 1 < 0 || xx - 1 > SIZEX || yy + i > SIZEY) wentFromBoardError = true;
                                    board[getIndex(xx - 1, yy + i, boardSizeX)] = copy[getIndex(xx, yy, boardSizeX)];
                                    board[getIndex(xx - 1, yy + i, boardSizeX)].direction = 'S';
                                    board[getIndex(xx - 1, yy + i, boardSizeX)].state = '+';
                                }
                                else if (copy[getIndex(xx, yy, boardSizeX)].direction == 'S') {
                                    if (isSbAround(board, xx + 1 + i, yy, currentPlayer, boardSizeY, boardSizeX)) tooCloseError = true;
                                    if (yy< 0 || xx + 1 + i < 0 || xx + 1 + i > SIZEX || yy > SIZEY) wentFromBoardError = true;
                                    board[getIndex(xx + 1 + i, yy, boardSizeX)] = copy[getIndex(xx, yy, boardSizeX)];
                                    board[getIndex(xx + 1 + i, yy, boardSizeX)].direction = 'W';
                                    board[getIndex(xx + 1 + i, yy, boardSizeX)].state = '+';
                                }
                                else if (copy[getIndex(xx, yy, boardSizeX)].direction == 'W') {
                                    if (isSbAround(board, xx, yy - i + 1, currentPlayer, boardSizeY, boardSizeX)) tooCloseError = true;
                                    if (yy - i + 1 < 0 || xx < 0 || xx > SIZEX || yy - i + 1 > SIZEY) wentFromBoardError = true;
                                    board[getIndex(xx, yy - i + 1, boardSizeX)] = copy[getIndex(xx, yy, boardSizeX)];
                                    board[getIndex(xx, yy - i + 1, boardSizeX)].direction = 'N';
                                    board[getIndex(xx, yy - i + 1, boardSizeX)].state = '+';
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
                        if (copy[getIndex(xx, yy, boardSizeX)].numberI == numberOfShip && !strcmp(copy[getIndex(xx, yy, boardSizeX)].classOfShip, shipClass) && copy[getIndex(xx, yy, boardSizeX)].player == currentPlayer) {
                            for (int i = 0; i < getSizeOfShip(shipClass); i++) {
                                if (copy[getIndex(xx, yy, boardSizeX)].direction == 'N') {
                                    if (isSbAround(board, xx + 1, yy, currentPlayer, boardSizeY, boardSizeX)) tooCloseError = true;
                                    if (yy < 0 || xx + i< 0 || xx + i> SIZEX || yy > SIZEY) wentFromBoardError = true;
                                    board[getIndex(xx + i, yy, boardSizeX)] = copy[getIndex(xx, yy, boardSizeX)];
                                    board[getIndex(xx + i, yy, boardSizeX)].direction = 'W';
                                    board[getIndex(xx + i, yy, boardSizeX)].state = '+';
                                }
                                if (copy[getIndex(xx, yy, boardSizeX)].direction == 'W') {
                                    if (isSbAround(board, xx + 1, yy - i, currentPlayer, boardSizeY, boardSizeX)) tooCloseError = true;
                                    if (yy - i < 0 || xx + 1 < 0 || xx + 1 > SIZEX || yy - i > SIZEY) wentFromBoardError = true;
                                    board[getIndex(xx + 1, yy - i, boardSizeX)] = copy[getIndex(xx, yy, boardSizeX)];
                                    board[getIndex(xx + 1, yy - i, boardSizeX)].direction = 'N';
                                    board[getIndex(xx + 1, yy - i, boardSizeX)].state = '+';
                                }//_________________________________________ TO NIE DZIALA WGL
                                if (copy[getIndex(xx, yy, boardSizeX)].direction == 'S') {
                                    if (isSbAround(board, xx + 1, yy - i, currentPlayer, boardSizeY, boardSizeX)) tooCloseError = true;
                                    if (yy - i < 0 || xx + 1 < 0 || xx + 1 > SIZEX || yy - i > SIZEY) wentFromBoardError = true;
                                    board[getIndex(xx + 1, yy - i, boardSizeX)] = copy[getIndex(xx, yy, boardSizeX)];
                                    board[getIndex(xx + 1, yy - i, boardSizeX)].direction = 'N';
                                    board[getIndex(xx + 1, yy - i, boardSizeX)].state = '+';
                                }
                                if (copy[getIndex(xx, yy, boardSizeX)].direction == 'E') {
                                    if (isSbAround(board, xx + 1, yy - i, currentPlayer, boardSizeY, boardSizeX)) tooCloseError = true;
                                    if (yy - i < 0 || xx + 1 < 0 || xx + 1 > SIZEX || yy - i > SIZEY) wentFromBoardError = true;
                                    board[getIndex(xx + 1, yy - i, boardSizeX)] = copy[getIndex(xx, yy, boardSizeX)];
                                    board[getIndex(xx + 1, yy - i, boardSizeX)].direction = 'N';
                                    board[getIndex(xx + 1, yy - i, boardSizeX)].state = '+';
                                }//____________________________
                            }
                            flag = false;
                            break;
                        }
                    }
                }
            }
            
            if (tooCloseError) {
                cout << "INVALID OPERATION \"MOVE " << numberOfShip << " " << shipClass << " " << direction << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
                break;
            }
            if (wentFromBoardError) {
                cout << "INVALID OPERATION \"MOVE " << numberOfShip << " " << shipClass << " " << direction << "\": SHIP WENT FROM BOARD" << endl;
                break;
            }

        }
        else if (!strcmp("EXTENDED_SHIPS", command)) {
            extendedShips = true;
        }
        else if (!strcmp("SPY", command)) {
            cin >> numberOfShip >> y >> x;

            spy(board, x, y, boardSizeX, boardSizeY, currentPlayer);

        }
        else if (!strcmp("[state]", command)) {
            state ? state = false : state = true;
        }


        if (strcmp(command, DEFAULT_COMMAND)) {
            strncpy_s(lastLastCommand, lastCommand, 16);
            strncpy_s(lastCommand, command, 16);
        }

        //chceck if sb won
        if (howManyRemaining(board, 'A', boardSizeY, boardSizeX) == 0 && howManyDestroyed(board, 'A', boardSizeY, boardSizeX) > 0) {
            cout << "B won" << endl;
            break;
        }
        if (howManyRemaining(board, 'B', boardSizeY, boardSizeX) == 0 && howManyDestroyed(board, 'B', boardSizeY, boardSizeX) > 0) {
            cout << "A won" << endl;
            break;
        }
    }

    delete[] board;


}