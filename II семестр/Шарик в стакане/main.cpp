#include <iostream>
#include <windows.h>
#include "resource.h"

using namespace std;

struct error_dt
{
	double num;
	error_dt(double num_n)
	{
		num = num_n;
	}
};

struct error_wrong_initial_parameters
{
	double mx0, my0;
	error_wrong_initial_parameters(double nmx0, double nmy0)
	{
		mx0 = nmx0;
		my0 = nmy0;
	}
};

struct error_wrong_glass_parameters
{
	double mx1, mx2;
	error_wrong_glass_parameters(double nmx1, double nmx2)
	{
		mx1 = nmx1;
		mx2 = nmx2;
	}
};

struct coordinate
{
	double x, y;
};

double X1, X2, Y1, X0, Y0, Ux, Uy, dt, T;
int height, width;
coordinate* physics, * pixel;

int WINAPI DlgProc(HWND hDlg, WORD wMsg, WORD wParam, DWORD)
{
	PAINTSTRUCT ps;
		if (wMsg == WM_CLOSE || wMsg == WM_COMMAND && wParam == IDOK) 
		{
			EndDialog(hDlg, 0);
		}
		else
			if (wMsg == WM_INITDIALOG)
			{
				RECT rc;
				GetClientRect(hDlg, &rc);
				width = rc.right - rc.left;
				height = rc.bottom - rc.top;
				
				pixel = new coordinate[round(T / dt)];

				for (int i = 0; i < round(T / dt) || Y1 - physics[i].y < Uy*dt ; i++)
				{
					pixel[i].x = (physics[i].x - X1) * width / (X2 - X1);
					pixel[i].y = height - physics[i].y * height / Y1;
				}
			}
			else
				if (wMsg == WM_PAINT) 
				{
					BeginPaint(hDlg, &ps);
					HPEN hPen = (HPEN)CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
					HPEN hOldPen = (HPEN)SelectObject(ps.hdc, hPen);
					POINT ptOld;

					for (int i = 0; i < round(T / dt) - 1 || Y1 - physics[i].y < fabs(Uy * dt) || Y1 - physics[i+1].y < fabs(Uy * dt); i++)
					{
						MoveToEx(ps.hdc, pixel[i].x, pixel[i].y, &ptOld);
						LineTo(ps.hdc, pixel[i + 1].x, pixel[i + 1].y);
					}

					SelectObject(ps.hdc, hOldPen);
					DeleteObject(hPen);
					EndPaint(hDlg, &ps);
				}
	return 0;
}
void main()
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	try
	{
		cout << "Enter parameters:" << endl;
		cout << "\tEnter x1: ";
		cin >> X1;

		cout << "\tEnter x2: ";
		cin >> X2;
		if (X1 > X2)
			throw error_wrong_glass_parameters(X1, X2);

		cout << "\tEnter y: ";
		cin >> Y1;

		cout << "\tEnter x0: ";
		cin >> X0;

		cout << "\tEnter y0: ";
		cin >> Y0;
		if (X0 > X2 || X0 < X1 || Y1 < Y0)
			throw error_wrong_initial_parameters(X0, Y0);

		cout << "\tEnter ux: ";
		cin >> Ux;

		cout << "\tEnter uy: ";
		cin >> Uy;

		cout << "\tEnter T: ";
		cin >> T;

		cout << "\tEnter dt: ";
		cin >> dt;
		if (dt < 1.0E-5)
			throw error_dt(dt);
		
		physics = new coordinate[round(T / dt)];

		double X = X0, Y = Y0;

		for (int i = 0; i < round(T / dt) && Y1 - Y - Uy * dt > 0; i++)
		{
			physics[i].x = X += Ux * dt;
			physics[i].y = Y += Uy * dt;

			if (X + Ux * dt - X1 < 0 || X2 - X - Ux * dt < 0)
				Ux *= -1;
			if (Y + Uy * dt < 0)
				Uy *= -1;
		}

		DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
	}
	catch (error_dt x)
	{
		cerr << "dt = " << x.num << " too little!" << endl;
	}
	catch (error_wrong_glass_parameters x)
	{
		cerr << "Wrong statement" << x.mx1 << " < " << x.mx2 << endl;
	}
	catch (error_wrong_initial_parameters x)
	{
		cerr << "Wrong initial parameters (  " << x.mx0 << "; " << x.my0 << " )" << endl;
	}
}
