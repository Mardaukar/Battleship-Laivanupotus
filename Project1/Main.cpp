#include "Header.h"

/*--------------------------------------------------
 *
 * nimi: main
 * toiminta: pohjustaa pelin ja hoitaa siirtymiset paavalikosta muihin pelin osiin, antaa loppuviestin
 * parametri(t): -
 * paluuarvo(t): int
 *
 *--------------------------------------------------*/
int main() {
	bool shipsPlaced = false; //laivat asetettu
	bool gameFinished = false; //peli loppunut
	char shipTable[SIZE][SIZE]; //pitaa kirjaa laivojen sijainnista
	char shootingTable[SIZE][SIZE]; //pitaa kirjaa ammutuista ruuduista
	int shipStatus[SHIPS]; //pitaa kirjaa laivojen 'statuksesta'
	Stats stats; //pitaa kirjaa menossa olevan pelin statistiikasta
	srand(time(NULL)); //pohjustaa satunnaisuuden

	while (true) { //paavalikon looppi
		char selection = menu(shipsPlaced); //kysytaan kayttajan valinta

		if (selection == '1') { //pelaaja asettaa laivat, peli alustetaan
			initGame(shipStatus, shipTable, shootingTable, stats);
			placeShips(shipTable);
			shipsPlaced = true;
			gameFinished = false;
		}
		else if (selection == '2') { //siirrytaan pelaamaan (kunhan laivat on asetettu ensiksi)
			playGame(&gameFinished, shipStatus, shipTable, shootingTable, stats);
		}
		else if (selection == '3') { //tietokone arpoo laivat, peli alustetaan
			initGame(shipStatus, shipTable, shootingTable, stats);
			randomShips(shipTable);
			shipsPlaced = true;
			gameFinished = false;
		}
		else if (selection == 'L') { //lopetetaan peli
			break;
		}
	}

	//kun poistutaan ohjelmasta
	cout << endl << endl << "Kiitos pelista!" << endl;
	Sleep(WAIT_TIME);

	return EXIT_SUCCESS;
}