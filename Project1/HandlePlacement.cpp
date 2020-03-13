#include "Header.h"

/*--------------------------------------------------
 *
 * nimi: initGame
 * toiminta: alustetaan peli, tyhjennetaan taulukot, resetoidaan statistiikka, asetetaan laivojen alkutilat 'ehjiksi'
 * parametri(t): shipStatus, shipTable, shootingTable, &stats
 * paluuarvo(t): void
 *
 *--------------------------------------------------*/
void initGame(int shipStatus[SHIPS], char shipTable[SIZE][SIZE], char shootingTable[SIZE][SIZE], Stats &stats) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			shipTable[i][j] = ' ';
			shootingTable[i][j] = ' ';
		}
	}

	for (int i = 0; i < SHIPS; i++) {
		shipStatus[i] = BIGGEST - i;
	}

	stats.round = 0;
	stats.missCounterMax = 0;
}

/*--------------------------------------------------
 *
 * nimi: placeShip
 * toiminta: asetetaan laiva haluttuun/arvottuun kohtaan
 * parametri(t): y, x, direction, shipSize, shipTable
 * paluuarvo(t): void
 *
 *--------------------------------------------------*/
void placeShip(int y, int x, char direction, int shipSize, char shipTable[SIZE][SIZE]) {
	if (direction == 'p') {
		y = y - shipSize + 1;
		direction = 'e';
	}

	if (direction == 'l') {
		x = x - shipSize + 1;
		direction = 'i';
	}

	char shipSymbol = '0' + shipSize;

	if (direction == 'e') {
		for (int i = 0; i < shipSize; i++) {
			shipTable[y + i][x] = shipSymbol;
		}
	}

	if (direction == 'i') {
		for (int i = 0; i < shipSize; i++) {
			shipTable[y][x + i] = shipSymbol;
		}
	}
}

/*--------------------------------------------------
 *
 * nimi: checkCoordinates
 * toiminta: tarkistetaan voiko laivan asettaa haluttuun/arvottuun kohtaan
 * parametri(t): y, x, direction, shipSize, shipTable
 * paluuarvo(t): bool
 *
 *--------------------------------------------------*/
bool checkCoordinates(int y, int x, char direction, int shipSize, char shipTable[SIZE][SIZE]) {
	if (direction == 'p') {
		y = y - shipSize + 1;
		direction = 'e';
	}

	if (direction == 'l') {
		x = x - shipSize + 1;
		direction = 'i';
	}

	if (y > (SIZE - 1) || y < 0) {
		return false;
	}

	if (x > (SIZE - 1) || x < 0) {
		return false;
	}

	if (direction == 'e') {
		if (y + shipSize > SIZE) {
			return false;
		}

		for (int i = 0; i < shipSize; i++) {
			if (shipTable[y + i][x] != ' ') {
				return false;
			}
		}
	}

	if (direction == 'i') {
		if (x + shipSize > SIZE) {
			return false;
		}

		for (int i = 0; i < shipSize; i++) {
			if (shipTable[y][x + i] != ' ') {
				return false;
			}
		}
	}

	return true;
}

/*--------------------------------------------------
 *
 * nimi: placeShips
 * toiminta: paafunktio laivojen asettelulle
 * parametri(t): shipTable
 * paluuarvo(t): void
 *
 *--------------------------------------------------*/
void placeShips(char shipTable[SIZE][SIZE]) {
	int y, x; //koordinaatit
	char direction; //suunta

	for (int i = 0; i < SHIPS; i++) { //asetuslooppi
		while (true) {
			system("cls");
			printGamestate(shipTable);
			askPlacement(&y, &x, &direction, BIGGEST - i);

			if (checkCoordinates(y, x, direction, BIGGEST - i, shipTable) == true) {
				break;
			}

			cout << endl << "Laivaa ei voi sijoittaa valitsemaasi kohtaan." << endl;
			Sleep(WAIT_TIME);
		}

		placeShip(y, x, direction, BIGGEST - i, shipTable);
	}

	//kun kaikki laivat asetettu
	system("cls");
	printGamestate(shipTable);
	cout << "Kaikki laivat asetettu." << endl;
	Sleep(WAIT_TIME);
}

/*--------------------------------------------------
 *
 * nimi: randomShips
 * toiminta: arpoo laivojen sijainnit taulukkoon
 * parametri(t): shipTable
 * paluuarvo(t): void
 *
 *--------------------------------------------------*/
void randomShips(char shipTable[SIZE][SIZE]) {
	int y, x;
	char direction;

	cout << endl << endl << "Arvotaan laivojen sijainnit";

	for (int i = 0; i < SHIPS; i++) {
		while (true) {
			randomCoordinates(&y, &x, &direction, BIGGEST - i);

			cout << ".";
			Sleep(WAIT_TIME / 5);

			if (checkCoordinates(y, x, direction, BIGGEST - i, shipTable) == true) {
				break;
			}
		}

		placeShip(y, x, direction, BIGGEST - i, shipTable);
	}

	cout << " Laivojen sijainnit arvottu." << endl;
	Sleep(WAIT_TIME);
}

/*--------------------------------------------------
 *
 * nimi: randomCoordinates
 * toiminta: tuottaa satunnaiset koordinaatit ja suunnan
 * parametri(t): *y, *x, *direction, shipSize
 * paluuarvo(t): void
 *
 *--------------------------------------------------*/
void randomCoordinates(int* y, int* x, char* direction, int shipSize) {
	int r_direction = rand() % 2;

	if (r_direction == 0) {
		*direction = 'e';
		*x = rand() % SIZE;
		*y = rand() % (SIZE - shipSize + 1);
	}
	else {
		*direction = 'i';
		*y = rand() % SIZE;
		*x = rand() % (SIZE - shipSize + 1);
	}
}