#pragma once

#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <ctime>

#pragma warning(disable:4996) // Имя POSIX устарело

using namespace std;

void run(int difficulty_location, int difficulty_speed);
void printMap();
void initMap(int difficulty_location);
void move(int dx, int dy);
void update();
void changeDirection(char key);
void clearScreen();
void generateFood();
char getMapValue(int value);
int getRecord(string file_name, int difficulty_location, int difficulty_speed);
void saveRecord(string file_name, int difficulty_location, int difficulty_speed, int value);