#pragma

#include <iostream>
#include <ctime>
#include <vector>
#include <conio.h>

#pragma warning(disable:4996) // Имя POSIX устарело

using namespace std;

void filling();
void random();
void complication();
void carry();
void printMap();
void initMap();
void clearMap();
void updateCursorPosition(char key);
void move(int dx, int dy);
void cursor();
void answer(char key);
void run();