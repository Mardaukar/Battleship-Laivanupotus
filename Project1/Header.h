#pragma once

#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#define SIZE 7 //pelialueen maarittava koko
#define SHIPS 4 //laivojen lukumaara
#define BIGGEST 5 //isoimman laivan pituus
#define WAIT_TIME 1000 //sekunti, kaytetaan taukoihin

using namespace std;

struct Stats { //tilastoja yllapitava struct
	int round = 0;
	int missCounter = 0;
	int missCounterMax = 0;
	int firstHit[4];
	int shipSunk[4];
};

//UI - alifunktiot, jotka liittyvat laheisesti kayttajaan
char menu(bool);
void printGamestate(char[SIZE][SIZE]);
void askPlacement(int*, int*, char*, int);
void askDirection(char*);
void askCoordinates(int*, int*, bool, bool*, bool*, bool*);
void printStats(Stats);
void getMostEfficient(int*, Stats);
void getOrder(string*, Stats);

//HandleGame - alifunktiot, jotka liittyvat pelaamiseen (ammuntaan)
void playGame(bool*, int[SHIPS], char[SIZE][SIZE], char[SIZE][SIZE], Stats&);
bool alreadyHit(int, int, char[SIZE][SIZE]);
void executeHit(int, int, int[SHIPS], char[SIZE][SIZE], char[SIZE][SIZE], Stats&);
bool checkGameFinished(int[SHIPS]);
void sinkShip(char, char[SIZE][SIZE], char[SIZE][SIZE]);
void randomHit(int*, int*);

//HandlePlacement - alifunktiot, jotka liittyvat laivojen asetteluun / pelin valmisteluun
void initGame(int[SHIPS], char[SIZE][SIZE], char[SIZE][SIZE], Stats&);
void placeShips(char[SIZE][SIZE]);
void randomShips(char[SIZE][SIZE]);
void placeShip(int, int, char, int, char[SIZE][SIZE]);
bool checkCoordinates(int, int, char, int, char[SIZE][SIZE]);
void randomCoordinates(int*, int*, char*, int);