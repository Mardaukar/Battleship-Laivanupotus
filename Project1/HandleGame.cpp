#include "Header.h"

/*--------------------------------------------------
 *
 * nimi: playGame
 * toiminta: ammuntaosuuden paafunktio
 * parametri(t): *gameFinished, shipStatus, shipTable, shootingTable, &stats
 * paluuarvo(t): void
 *
 *--------------------------------------------------*/
void playGame(bool* gameFinished, int shipStatus[SHIPS], char shipTable[SIZE][SIZE], char shootingTable[SIZE][SIZE], Stats &stats) {
	int y, x; //ammunnan koordinaatit
	bool debugMode = false; //taman avulla 'vakoillaan'
	bool exitPlay = false; //taman avulla lopetetaan while-looppi ja peli loppuu
	bool simulationMode = false; //taman avulla simuloidaan ammunnat

	system("cls");

	while (*gameFinished == false) { //pelin aikainen looppi
		cout << "Pelitilanne on seuraava:" << endl << endl;
		printGamestate(shootingTable);

		while (simulationMode == false) { //talla loopilla pyydetaan koordinaatit pelaajalta
			cout << endl << "Anna ampumiskoordinaatit: ";
			askCoordinates(&y, &x, true, &debugMode, &exitPlay, &simulationMode);

			if (exitPlay == true) {
				return;
			}

			if (simulationMode == true) {
				break;
			}

			if (debugMode == true) { //vakoilu
				cout << endl << "Laivat sijaitsevat seuraavissa paikoissa:" << endl << endl;
				printGamestate(shipTable);

				debugMode = false;
				continue;
			}

			if (alreadyHit(y, x, shootingTable) == true) {
				cout << "Annettuun kohtaan on jo ammuttu." << endl;
				continue;
			}

			break;
		}

		if (simulationMode == true) { //simulaatio
			cout << endl << "Simuloidaan..." << endl;
			Sleep(WAIT_TIME/50);

			while (true) {
				randomHit(&y, &x);

				if (alreadyHit(y, x, shootingTable) == false) {
					break;
				}
			}
		}

		//kierroksen loppuosuus, tarkistetaan jatkuuko peli
		stats.round++;
		executeHit(y, x, shipStatus, shipTable, shootingTable, stats);

		*gameFinished = checkGameFinished(shipStatus);

		system("cls");
	}

	//kun peli paattyy, mennaan tanne
	cout << "Peli paattyi." << endl << endl;
	printGamestate(shootingTable);
	printStats(stats);
	cout << endl << "--- Paina mita tahansa nappainta jatkaaksesi ---" << endl;
	_getch();
}

/*--------------------------------------------------
 *
 * nimi: randomHit
 * toiminta: antaa koordinaatit satunnaiselle ruudulle taulukosta
 * parametri(t): *y, *x
 * paluuarvo(t): void
 *
 *--------------------------------------------------*/
void randomHit(int* y, int* x) {
	*y = rand() % SIZE;
	*x = rand() % SIZE;
}

/*--------------------------------------------------
 *
 * nimi: checkGameFinished
 * toiminta: tarkistaa laivojen statuksesta, ovatko kaikki uponneet
 * parametri(t): shipStatus
 * paluuarvo(t): bool
 *
 *--------------------------------------------------*/
bool checkGameFinished(int shipStatus[SHIPS]) {
	for (int i = 0; i < SHIPS; i++) {
		if (shipStatus[i] != 0) {
			return false;
		}
	}

	return true;
}

/*--------------------------------------------------
 *
 * nimi: executeHit
 * toiminta: suorittaa ammunnan, muuttaa pelin statuksen siihen, että ammunta ruutuun on tapahtunut
 * parametri(t): y, x, shipStatus, shipTable, shootingTable, &stats
 * paluuarvo(t): void
 *
 *--------------------------------------------------*/
void executeHit(int y, int x, int shipStatus[SHIPS], char shipTable[SIZE][SIZE], char shootingTable[SIZE][SIZE], Stats &stats) {
	char hit = shipTable[y][x];

	if (hit == ' ') { //ei osumaa
		shootingTable[y][x] = 'x';
		stats.missCounter++;

		if (stats.missCounter > stats.missCounterMax) {
			stats.missCounterMax = stats.missCounter;
		}
	}
	else { //osuma
		stats.missCounter = 0;

		if (hit == '5') {
			if (shipStatus[0] == 1) {
				sinkShip(hit, shipTable, shootingTable);
				stats.shipSunk[0] = stats.round;
			}
			else {
				if (shipStatus[0] == 5) {
					stats.firstHit[0] = stats.round;
				}

				shootingTable[y][x] = '*';
			}

			shipStatus[0]--;
		}
		else if (hit == '4') {
			if (shipStatus[1] == 1) {
				sinkShip(hit, shipTable, shootingTable);
				stats.shipSunk[1] = stats.round;
			}
			else {
				if (shipStatus[1] == 4) {
					stats.firstHit[1] = stats.round;
				}

				shootingTable[y][x] = '*';
			}

			shipStatus[1]--;
		}
		else if (hit == '3') {
			if (shipStatus[2] == 1) {
				sinkShip(hit, shipTable, shootingTable);
				stats.shipSunk[2] = stats.round;
			}
			else {
				if (shipStatus[2] == 3) {
					stats.firstHit[2] = stats.round;
				}

				shootingTable[y][x] = '*';
			}

			shipStatus[2]--;
		}
		else if (hit == '2') {
			if (shipStatus[3] == 1) {
				sinkShip(hit, shipTable, shootingTable);
				stats.shipSunk[3] = stats.round;
			}
			else {
				if (shipStatus[3] == 2) {
					stats.firstHit[3] = stats.round;
				}

				shootingTable[y][x] = '*';
			}

			shipStatus[3]--;
		}
	}
}

/*--------------------------------------------------
 *
 * nimi: sinkShip
 * toiminta: muuttaa uponneen laivan merkit ammuntatauluun
 * parametri(t): hit, shipTable, shootingTable
 * paluuarvo(t): void
 *
 *--------------------------------------------------*/
void sinkShip(char hit, char shipTable[SIZE][SIZE], char shootingTable[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (shipTable[i][j] == hit) {
				shootingTable[i][j] = '#';
			}
		}
	}
}

/*--------------------------------------------------
 *
 * nimi: alradyHit
 * toiminta: tarkistaa onko kyseiseen ruutuun ammuttu jo
 * parametri(t): y, x, shootingTable
 * paluuarvo(t): bool
 *
 *--------------------------------------------------*/
bool alreadyHit(int y, int x, char shootingTable[SIZE][SIZE]) {
	if (shootingTable[y][x] == ' ') {
		return false;
	}
	else {
		return true;
	}
}