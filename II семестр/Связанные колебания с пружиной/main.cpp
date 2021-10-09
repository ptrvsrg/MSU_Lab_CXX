#include <iostream>
#include <windows.h>
#include <cmath>
#include <vector>
#include "resource.h"

#define g 9.815
#define PI 3.142

using namespace std;

struct coordinate
{
	double X, Y;
};

vector <coordinate> physics1, pixel1, physics2, pixel2;
double t1, t2, dt, A1, A2, w1, w2, f01, f02;
int height, width;

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
				
				coordinate O;
				for (int i = 0; i < round((t2 - t1) / dt); i++)
				{
					O.X = physics1[i].X * width / (t2 - t1);
					O.Y = height / 4 - 0.5 * physics1[i].Y * height / (A1 + A2);
					pixel1.push_back(O);
					O.X = physics2[i].X * width / (t2 - t1);
					O.Y = 3 * height / 4 - 0.5 * physics2[i].Y * height / (A1 + A2);
					pixel2.push_back(O);
				}
			}
			else
				if (wMsg == WM_PAINT) 
				{
					BeginPaint(hDlg, &ps);

					HPEN hPen = (HPEN)CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
					HPEN hOldPen = (HPEN)SelectObject(ps.hdc, hPen);
					POINT ptOld;
					MoveToEx(ps.hdc, 0, height / 4, &ptOld);
					LineTo(ps.hdc, width, height / 4);

					hPen = (HPEN)CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
					hOldPen = (HPEN)SelectObject(ps.hdc, hPen);

					MoveToEx(ps.hdc, 0, 3 * height / 4, &ptOld);
					LineTo(ps.hdc, width, 3 * height / 4);

					hPen = (HPEN)CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
					hOldPen = (HPEN)SelectObject(ps.hdc, hPen);

					for (int i = 0; i < round((t2 - t1) / dt) - 1; i++)
					{
						MoveToEx(ps.hdc, pixel1[i].X, pixel1[i].Y, &ptOld);
						LineTo(ps.hdc, pixel1[i + 1].X, pixel1[i + 1].Y);
					}

					hPen = (HPEN)CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
					hOldPen = (HPEN)SelectObject(ps.hdc, hPen);

					for (int i = 0; i < round((t2 - t1) / dt) - 1; i++)
					{
						MoveToEx(ps.hdc, pixel2[i].X, pixel2[i].Y, &ptOld);
						LineTo(ps.hdc, pixel2[i + 1].X, pixel2[i + 1].Y);
					}

					SelectObject(ps.hdc, hOldPen);
					DeleteObject(hPen);
					EndPaint(hDlg, &ps);
				}
	return 0;
}
void main()
{
	try
	{
		setlocale(LC_ALL, "");
		double x01, x02, u01, u02, k, m1, m2, a, l1, l2;
		cout << "Enter parameters: " << endl;
		cout << "\tEnter x01: ";
		cin >> x01;
		cout << "\tEnter x02: ";
		cin >> x02;
		cout << "\tEnter u01: ";
		cin >> u01;
		cout << "\tEnter u02: ";
		cin >> u02;
		cout << "\tEnter k: ";
		cin >> k;
		cout << "\tEnter m1: ";
		cin >> m1;
		cout << "\tEnter m2: ";
		cin >> m2;
		cout << "\tEnter l1: ";
		cin >> l1;
		cout << "\tEnter l2: ";
		cin >> l2;
		cout << "\tEnter a: ";
		cin >> a;

		w1 = sqrt(g / l1);
		w2 = sqrt(g / l2 - k * pow(a, 2) * (1 / (m1 * pow(l1, 2)) + 1 / (m2 * pow(l2, 2))));
		if (g / l2 < k * pow(a, 2) * (1 / (m1 * pow(l1, 2)) + 1 / (m2 * pow(l2, 2))))
			throw 1;

		if (x01 + x02 == 0)
			f01 = (-u01 - u02) * 0.5 * PI / fabs(-u01 - u02);
		else
			f01 = atan((-u01 - u02) / (w1 * (x01 + x02)));

		if (x01 - x02 == 0)
			f02 = (-u01 + u02) * 0.5 * PI / fabs(-u01 + u02);
		else
			f02 = atan((-u01 + u02) / (w1 * (x01 - x02)));

		if (x01 + x02 == 0)
			A1 = (-u01 - u02) / (sin(f01) * w1);
		else
			A1 = (x01 + x02) / cos(f01);

		if (x01 - x02 == 0)
			A1 = (-u01 + u02) / (sin(f02) * w2);
		else
			A2 = (x01 - x02) / cos(f02);

		cout << "\tEnter [ t1 ; t2 ]: ";
		cin >> t1 >> t2;
		cout << "\tEnter dt: ";
		cin >> dt;

		coordinate O;
		for (int i = 0; i < round(t2 - t1) / dt; i++)
		{
			O.X = i * dt;
			O.Y = 0.5 * A1 * cos(w1 * (dt * i + t1) + f01) + 0.5 * A2 * cos(w2 * (dt * i + t1) + f02);
			physics1.push_back(O);
			O.X = i * dt;
			O.Y = 0.5 * A1 * cos(w1 * (dt * i + t1) + f01) - 0.5 * A2 * cos(w2 * (dt * i + t1) + f02);
			physics2.push_back(O);
		}

		DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
	}
	catch (int x)
	{
		exit(1);
	}
}
