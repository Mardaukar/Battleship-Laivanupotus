#include "Header.h"

/*--------------------------------------------------
 *
 * nimi: menu
 * toiminta: tulostetaan paavalikko ja kysytaan pelaajan valinta
 * parametri(t): shipsPlaced
 * paluuarvo(t): char
 *
 *--------------------------------------------------*/
char menu(bool shipsPlaced) {
	string selection;
	int selectionFail = 0;

	while (true) {
		system("cls");
		cout << endl;
		cout << "Laivanupotuspeli" << endl;
		cout << "================" << endl;
		cout << endl;
		cout << "Valinnat:" << endl;
		cout << "1) Syota laivat" << endl;
		cout << "2) Pelaa" << endl;
		cout << "3) Arvo laivojen sijainnit" << endl;
		cout << "L) Lopeta" << endl;
		cout << endl;
		if (selectionFail == 1) {
			cout << "Valitse annetuista vaihtoehdoista." << endl;
		}
		else if (selectionFail == 2) {
			cout << "Laivat pitaa asettaa ensiksi." << endl;
		}
		else {
			cout << endl;
		}
		cout << endl;
		cout << "Valintasi: ";

		cin >> selection;

		if (selection == "l" || selection == "L") {
			return 'L';
		}
		else if (selection == "1" || selection == "3") {
			return selection[0];
		}
		else if (selection == "2") {
			if (shipsPlaced == true) {
				return selection[0];
			}
			else {
				selectionFail = 2;
			}
		}
		else {
			selectionFail = 1;
		}
	}
}

/*--------------------------------------------------
 *
 * nimi: getMostEfficient
 * toiminta: asetetaan tehokkaimman ammuntajakson laiva
 * parametri(t): *mostEff, stats
 * paluuarvo(t): void
 *
 *--------------------------------------------------*/
void getMostEfficient(int* mostEff, Stats stats) {
	double factors[SHIPS];

	for (int i = 0; i < SHIPS; i++) {
		factors[i] = (stats.shipSunk[i] - stats.firstHit[i] + 1.0) / (BIGGEST - i);
	}

	int position = 0;

	for (int i = 1; i < SHIPS; i++) {
		if (factors[i] < factors[position])
			position = i;
	}

	*mostEff = position;
}

/*--------------------------------------------------
 *
 * nimi: getOrder
 * toiminta: lisataan tekstiin laivat uppoamisjarjestyksessa
 * parametri(t): *text, stats
 * paluuarvo(t): void
 *
 *--------------------------------------------------*/
void getOrder(string* text, Stats stats) {
	string shipNames[SHIPS] = { "VIISI", "NELJA", "KOLME", "KAKSI" };
	
	for (int i = 0; i < SHIPS; i++) {
		int index = 0;

		for (int j = 1; j < SHIPS; j++) {
			if (stats.shipSunk[j] < stats.shipSunk[index]) {
				index = j;
			}
		}

		*text += shipNames[index];
		*text += " ";

		stats.shipSunk[index] = 99;
	}
}

/*--------------------------------------------------
 *
 * nimi: printStats
 * toiminta: tulostetaan loppuneen pelin statistiikka
 * parametri(t): stats
 * paluuarvo(t): void
 *
 *--------------------------------------------------*/
void printStats(Stats stats) {
	int mostEff;
	string order = "Laivojen uppoamisjarjestys: ";

	getMostEfficient(&mostEff, stats);
	getOrder(&order, stats);

	cout << endl << "STATISTIIKKAA:" << endl;
	cout << endl;
	cout << "Ammuntoja yhteensa: " << stats.round << endl;
	cout << "Ohilaukauksia yhteensa: " << stats.round - 5 - 4 - 3 - 2 << endl;
	cout << "Pisin ohilaukauksien jakso: " << stats.missCounterMax << endl;
	cout << endl;
	cout << "\t\t1. Osuma\tUppoaminen\t1. -> Upp" << endl;
	cout << "VIISI\t\t" << stats.firstHit[0] << "\t\t" << stats.shipSunk[0] << "\t\t" << stats.shipSunk[0] - stats.firstHit[0] + 1 << endl;
	cout << "NELJA\t\t" << stats.firstHit[1] << "\t\t" << stats.shipSunk[1] << "\t\t" << stats.shipSunk[1] - stats.firstHit[1] + 1 << endl;
	cout << "KOLME\t\t" << stats.firstHit[2] << "\t\t" << stats.shipSunk[2] << "\t\t" << stats.shipSunk[2] - stats.firstHit[2] + 1 << endl;
	cout << "KAKSI\t\t" << stats.firstHit[3] << "\t\t" << stats.shipSunk[3] << "\t\t" << stats.shipSunk[3] - stats.firstHit[3] + 1 << endl;
	cout << endl;
	cout << order << endl;
	cout << endl;
	cout << "Tehokkain osumisjakso oli laukaukset " << stats.firstHit[mostEff] << ". - " << stats.shipSunk[mostEff] << ".," << endl;
	cout << "missa upotettiin " << BIGGEST - mostEff << " pituinen laiva." << endl;
}

/*--------------------------------------------------
 *
 * nimi: printGamestate
 * toiminta: tulostetaan joko ammunnan tai laivojen tila
 * parametri(t): table
 * paluuarvo(t): void
 *
 *--------------------------------------------------*/
void printGamestate(char table[SIZE][SIZE]) {
	string letters = "ABCDEFG";
	
	cout << "    1 2 3 4 5 6 7" << endl;
	cout << "  -----------------" << endl;

	for (int i = 0; i < SIZE; i++) {
		cout << letters[i] << " | ";

		for (int j = 0; j < SIZE; j++) {
			cout << table[i][j] << " ";
		}

		cout << "| " << letters[i] << endl;
	}

	cout << "  -----------------" << endl;
	cout << "    1 2 3 4 5 6 7" << endl;
}

/*--------------------------------------------------
 *
 * nimi: askPlacement
 * toiminta: tulosteet laivan sijainnin ja suunnan kysymiselle
 * parametri(t): *y, *x, *direction, shipSize
 * paluuarvo(t): void
 *
 *--------------------------------------------------*/
void askPlacement(int* y, int* x, char* direction, int shipSize) {
	bool fake; //Tämä on luotu vain täytteeksi funktiokutsuun
	
	string coordinatesQuestion = "Anna ";

	if (shipSize == 5) {
		coordinatesQuestion += "viiden ";
	}
	else if (shipSize == 4) {
		coordinatesQuestion += "neljan ";
	}
	else if (shipSize == 3) {
		coordinatesQuestion += "kolmen ";
	}
	else if (shipSize == 2) {
		coordinatesQuestion += "kahden ";
	}

	coordinatesQuestion += "pituisen laivan alkupiste: ";

	cout << coordinatesQuestion;
	askCoordinates(y, x, false, &fake, &fake, &fake);

	cout << "Anna suunta (p(ohjoinen)/i(ta)/e(tela)/l(ansi)): ";
	askDirection(direction);
}

/*--------------------------------------------------
 *
 * nimi: askCoordinates
 * toiminta: pyydetaan (oikean muotoiset) koordinaatit
 * parametri(t): *y, *x, shooting, *debugMode, *exitPlay, *simulationMode
 * paluuarvo(t): void
 *
 *--------------------------------------------------*/
void askCoordinates(int* y, int* x, bool shooting, bool* debugMode, bool* exitPlay, bool* simulationMode) {
	bool coordinatesError = false;
	string letters = "ABCDEFGabcdefg";
	string numbers = "1234567";
	string coordinatesAnswer;

	while (true) {
		if (coordinatesError == true) {
			cout << "Anna koordinaatit oikeassa muodossa (A2, E5, B1): ";
		}

		cin >> coordinatesAnswer;

		if (shooting == true) {
			if (coordinatesAnswer == "\\@") {
				*debugMode = true;
				break;
			}

			if (coordinatesAnswer == "p") {
				*exitPlay = true;
				break;
			}

			if (coordinatesAnswer == "simuloi") {
				*simulationMode = true;
				break;
			}
		}

		if (coordinatesAnswer.length() == 2) {
			if (letters.find(coordinatesAnswer[0]) != string::npos) {
				if (numbers.find(coordinatesAnswer[1]) != string::npos) {
					int position = letters.find(coordinatesAnswer[0]);
					if (position >= letters.length() / 2) {
						position -= letters.length() / 2;
					}
					*y = position;
					*x = numbers.find(coordinatesAnswer[1]);
					break;
				}
			}
		}

		coordinatesError = true;
	}
}

/*--------------------------------------------------
 *
 * nimi: askDirection
 * toiminta: pyydetaan (oikean muotoinen) suunta
 * parametri(t): *direction
 * paluuarvo(t): void
 *
 *--------------------------------------------------*/
void askDirection(char* direction) {
	bool directionError = false;
	string directionAnswer;
	string directions = "pielPIEL";

	while (true) {
		if (directionError == true) {
			cout << "Anna suunta oikeassa muodossa (p, i, e tai l): ";
		}

		cin >> directionAnswer;

		if (directionAnswer.length() == 1) {
			if (directions.find(directionAnswer[0]) != string::npos) {
				int position = directions.find(directionAnswer[0]);
				if (position >= directions.length() / 2) {
					position -= directions.length() / 2;
				}
				*direction = directions[position];
				break;
			}
		}

		directionError = true;
	}
}