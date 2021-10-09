#ifndef GEOM
#define GEOM
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#define X 95
#define Y 50
#define SYM 'Ô'
static char POLE[Y][X];

struct tochka
{
	int x, y;
};

struct otrezok
{
	tochka a, b;
};

struct krug
{
	int radius;
	tochka O;
	int chetvert;
};

struct treugolnik
{
	tochka K, L, M;
};

struct pryamougolnik
{
	tochka A, B;
};

struct koefficient
{
	double A, B, C;
};

FILE* open_file();
koefficient koef(otrezok AB);
void tchk_pst(tochka O);
void input();
void otr_pst(otrezok A1A2);
void kr_pst(krug okr);
void pr_pst(pryamougolnik pr);
void tr_pst(treugolnik KLM);
void read(FILE* file);
void output();

#endif GEOM