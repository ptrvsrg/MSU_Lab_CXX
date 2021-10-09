#include "geom.h"

//Îòêðûòèè ôàéëà äëÿ ÷òåíèÿ
FILE* open_file()
{
	setlocale(LC_ALL, "");
	char file_name[] = "1.txt";

	/*printf("Ââåäèòå íàçâàíèå ôàéëà: ");
	scanf("%s", file_name);*/

	FILE* file = fopen(file_name, "r");

	if (!file)
	{
		printf("Îøèáêà ïðè îòêðûòèè ôàéëà %s", file_name);
		exit(2);
	}

	return file;
}

//Êîýôôèöèåíòû â óðàâíåíèè ïðÿìîé
koefficient koef(otrezok AB)
{
	koefficient koef;
	koef.A = (double)(AB.b.y - AB.a.y);
	koef.B = (double)(AB.a.x - AB.b.x);
	koef.C = (double)(AB.a.x * AB.b.y - AB.a.y * AB.b.x);
	return koef;
}

//Ñîçäàíèå ïîëÿ
void input()
{
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j < X; j++)
		{
			POLE[i][j] = ' ';
		}
	}
}

//Ïîñòðîåíèå òî÷êè
void tchk_pst(tochka O)
{
	if (0 <= O.x < X && 0 <= O.y < Y)
		POLE[O.y][O.x] = SYM;
}

//Ïîñòðîåíèå îòðåçêà
void otr_pst(otrezok A1A2)
{
	int x = 0, y = 0;
	koefficient coef = koef(A1A2);

	for (int i = fmin(A1A2.a.x, A1A2.b.x); i <= fmax(A1A2.a.x, A1A2.b.x); i++)
	{
		y = round(coef.C / coef.B - (coef.A * i) / coef.B);
		if (0 <= i <= X && 0 <= y <= Y)
		{
			y = round(coef.C / coef.B - (coef.A * i) / coef.B);
			if (y >= 0 && i >= 0)
				POLE[y][i] = SYM;
		}
	}

	for (int i = fmin(A1A2.a.y, A1A2.b.y); i <= fmax(A1A2.a.y, A1A2.b.y); i++)
	{
		x = round(coef.C / coef.A - (coef.B * i) / coef.A);
		if (0 <= i <= Y && 0 <= x <= X)
		{
			x = round(coef.C / coef.A - (coef.B * i) / coef.A);
			if (x >= 0 && i >= 0)
				POLE[i][x] = SYM;
		}
	}
}

//Ïîñòðîåíèå êðóãà
void kr_pst(krug okr)
{
	int xn = round(okr.O.x - sqrt(pow(okr.radius, 2) - pow(round(okr.O.y - okr.radius / sqrt(2)) - okr.O.y, 2)));
	int yn = round(okr.O.y - sqrt(pow(okr.radius, 2) - pow(round(okr.O.x - okr.radius / sqrt(2)) - okr.O.x, 2)));
	int xv = round(okr.O.x + sqrt(pow(okr.radius, 2) - pow(round(okr.O.y - okr.radius / sqrt(2)) - okr.O.y, 2)));
	int yv = round(okr.O.y + sqrt(pow(okr.radius, 2) - pow(round(okr.O.x - okr.radius / sqrt(2)) - okr.O.x, 2)));

	if (okr.chetvert % 10000 / 1000 == 1 || okr.chetvert % 1000 / 100 == 1 || okr.chetvert % 100 / 10 == 1 || okr.chetvert % 10 == 1)
	{
		for (int i = okr.O.x; i <= okr.O.x + okr.radius; i++)
		{
			if (i < X && yv < Y)
			{
				yv = round(okr.O.y + sqrt(pow(okr.radius, 2) - pow(i - okr.O.x, 2)));
				if (yv >= 0 && i >= 0)
					POLE[yv][i] = SYM;
			}
		}

		for (int i = okr.O.y; i <= okr.O.y + okr.radius; i++)
		{
			if (xv < X && i < Y)
			{
				xv = round(okr.O.x + sqrt(pow(okr.radius, 2) - pow(i - okr.O.y, 2)));
				if (xv >= 0 && i >= 0)
					POLE[i][xv] = SYM;
			}
		}
	}

	if (okr.chetvert % 10000 / 1000 == 2|| okr.chetvert % 1000 / 100 == 2 || okr.chetvert % 100 / 10 == 2 || okr.chetvert % 10 == 2)
	{
		for (int i = okr.O.x - okr.radius; i <= okr.O.x; i++)
		{
			if (i < X && yn < Y)
			{
				yn = round(okr.O.y + sqrt(pow(okr.radius, 2) - pow(i - okr.O.x, 2)));
				if (yn >= 0 && i >= 0)
					POLE[yn][i] = SYM;
			}
		}

		for (int i = okr.O.y; i <= okr.O.y + okr.radius; i++)
		{
			if (xn < X && i < Y)
			{
				xn = round(okr.O.x - sqrt(pow(okr.radius, 2) - pow(i - okr.O.y, 2)));
				if (xn >= 0 && i >= 0)
					POLE[i][xn] = SYM;
			}
		}
	}

	if (okr.chetvert % 10000 / 1000 == 3 || okr.chetvert % 1000 / 100 == 3 || okr.chetvert % 100 / 10 == 3 || okr.chetvert % 10 == 3)
	{
		for (int i = okr.O.x - okr.radius; i <= okr.O.x; i++)
		{
			if (i < X && yn < Y)
			{
				yn = round(okr.O.y - sqrt(pow(okr.radius, 2) - pow(i - okr.O.x, 2)));
				if (yn >= 0 && i >= 0)
					POLE[yn][i] = SYM;
			}
		}

		for (int i = okr.O.y - okr.radius; i <= okr.O.y; i++)
		{
			if (xn < X && i < Y)
			{
				xn = round(okr.O.x - sqrt(pow(okr.radius, 2) - pow(i - okr.O.y, 2)));
				if (xn >= 0 && i >= 0)
					POLE[i][xn] = SYM;
			}
		}
	}

	if (okr.chetvert % 10000 / 1000 == 4 || okr.chetvert % 1000 / 100 == 4 || okr.chetvert % 100 / 10 == 4 || okr.chetvert % 10 == 4)
	{
		for (int i = okr.O.x; i <= okr.O.x + okr.radius; i++)
		{
			if (i < X && yn < Y)
			{
				yn = round(okr.O.y - sqrt(pow(okr.radius, 2) - pow(i - okr.O.x, 2)));
				if (yn >= 0 && i >= 0)
					POLE[yn][i] = SYM;
			}
		}

		for (int i = okr.O.y - okr.radius; i <= okr.O.y; i++)
		{
			if (xv < X && i < Y)
			{
				xv = round(okr.O.x + sqrt(pow(okr.radius, 2) - pow(i - okr.O.y, 2)));
				if (xv >= 0 && i >= 0)
					POLE[i][xv] = SYM;
			}
		}
	}
}

//Ïîñòðîåíèå ïðÿìîóãîëüíèêà
void pr_pst(pryamougolnik pr)
{
	setlocale(LC_ALL, "");
	if (pr.A.x > pr.B.x || pr.A.y > pr.B.y)
	{
		printf("Ââåäèòå ïðàâèëëüíî ïàðàìåòðû ïðÿìîãóëüíèêà: x(A) < x(B) è y(A) < y(B)\n");
		exit(1);
	}

	otr_pst({ pr.A, {pr.A.x, pr.B.y} });
	otr_pst({ pr.A, {pr.B.x, pr.A.y} });
	otr_pst({ pr.B, {pr.A.x, pr.B.y} });
	otr_pst({ pr.B, {pr.B.x, pr.A.y} });
}

//Ïîñòðîåíèå òðåóãîëüíèêà
void tr_pst(treugolnik KLM)
{
	otr_pst({ KLM.K, KLM.L });
	otr_pst({ KLM.L, KLM.M });
	otr_pst({ KLM.M, KLM.K });
}

//×òåíèå èç ôàéëà
void read(FILE* file)
{
	setlocale(LC_ALL, "");
	char line[100], * sym;
	while (!feof(file))
	{
		fgets(line, 100, file);
		sym = strtok(line, " ,.:-\n");

		if (sym)
		{
			if (strcmp(sym, "Òî÷êà") == 0)
			{
				tchk_pst({ atoi(strtok(NULL, " ,:.-\n")), atoi(strtok(NULL, " ,:.-\n")) });
			}
			else if (strcmp(sym, "Îòðåçîê") == 0)
			{
				otr_pst({ {atoi(strtok(NULL, " ,:.-\n")), atoi(strtok(NULL, " ,:.-\n"))}, {atoi(strtok(NULL, " ,:.-\n")), atoi(strtok(NULL, " ,:.-\n"))} });
			}
			else if (strcmp(sym, "Êðóã") == 0)
			{
				kr_pst({ atoi(strtok(NULL, " ,:.-\n")), {atoi(strtok(NULL, " ,:.-\n")), atoi(strtok(NULL, " ,:.-\n"))}, atoi(strtok(NULL, " ,:.-\n")) });
			}
			else if (strcmp(sym, "Òðåóãîëüíèê") == 0)
			{
				tr_pst({ {atoi(strtok(NULL, " ,:.-\n")), atoi(strtok(NULL, " ,:.-\n")) }, {atoi(strtok(NULL, " ,:.-\n")), atoi(strtok(NULL, " ,:.-\n")) }, {atoi(strtok(NULL, " ,:.-\n")), atoi(strtok(NULL, " ,:.-\n"))} });
			}
			else if (strcmp(sym, "Ïðÿìîóãîëüíèê") == 0)
			{
				pr_pst({ {atoi(strtok(NULL, " ,:.-\n")), atoi(strtok(NULL, " ,:.-\n")) }, {atoi(strtok(NULL, " ,:.-\n")), atoi(strtok(NULL, " ,:.-\n")) } });
			}
			else
			{
				printf("Íåïðàâèëüíî çàïîëíåí ôàéë");
				exit(3);
			}
		}
		memset(line, 0, 100);
	}
}

//Ïå÷àòü ïîëÿ
void output()
{
	for (int i = 1; i <= Y; i++)
	{
		for (int j = 0; j < X; j++)
		{
			printf("%c ", POLE[Y -  i][j]);
		}
		printf("\n");
	}
}
