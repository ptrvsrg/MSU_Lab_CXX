#include <iostream>
#include <Windows.h>
#include "resource.h"

using namespace std;

struct error_m
{
    double num;
    error_m(double num_n)
    {
        num = num_n;
    }
};

struct error_dt
{
    double num;
    error_dt(double num_n)
    {
        num = num_n;
    }
};

struct error_no_oscillation
{
    double a;
    double b;
    error_no_oscillation(double n_a, double n_b)
    {
        a = n_a;
        b = n_b;
    }
};

struct coordinate
{
    double X, Y;
};

double dt, t1, t2;
int width, height, control;
coordinate* pixel, * physics;

void harmonic_oscillation(double& L0, double& w, double& f0, double& dt, double& t1, double& t2)
{
    double k, m, L, U;

    cout << "Enter parameters:" << endl;
    cout << "\tEnter m: ";
    cin >> m;
    if (m < 1.0E-10)
        throw error_m(m);

    cout << "\tEnter k: ";
    cin >> k;
   
    w = sqrt(k / m);//Находим частоту колебаний

    cout << "\tEnter x0: ";
    cin >> L;
    cout << "\tEnter V0: ";
    cin >> U;
    f0 = atan(U / ( L * w)); // Находим разность фаз
    L0 = L / cos(f0); //Находим амплитуду смещения

    cout << "\tEnter [ t1 ; t2 ]: ";
    cin >> t1 >> t2;
    cout << "\tEnter dt: ";
    cin >> dt;
    if (dt < 1.0E-5)
        throw error_dt(dt);

    physics = new coordinate[round((t2 - t1) / dt)];

    for (int i = 0; i < round(t2 - t1) / dt; i++)
    {
        physics[i].X = i * dt;
        physics[i].Y = L0 * cos(w * (dt * i + t1) + f0);
    }

}

void damped_oscillation(double& L0, double& w, double& z, double& f0, double& dt, double& t1, double& t2)
{
    double a, k, m, L, U;

    cout << "Enter parameters:" << endl;
    cout << "\tEnter m: ";
    cin >> m;
    if (m < 1.0E-10)
        throw error_m(m);

    cout << "\tEnter k: ";
    cin >> k;
    cout << "\tEnter a: ";
    cin >> a;
    z = 0.5 * a / m;
    if (sqrt(k / m) < z)
        throw error_no_oscillation(sqrt(k / m), z);
    w = sqrt(k / m - pow(z, 2));

    cout << "\tEnter x0: ";
    cin >> L;
    cout << "\tEnter V0: ";
    cin >> U;
    f0 = atan((-z - U / L) / w);
    L0 = L / cos(f0);

    cout << "\tEnter [ t1 ; t2 ]: ";
    cin >> t1 >> t2;
    cout << "\tEnter dt: ";
    cin >> dt;
    if (dt < 1.0E-5)
        throw error_dt(dt);

    physics = new coordinate[round((t2 - t1) / dt)];

    for (int i = 0; i < round(t2 - t1) / dt; i++)
    {
        physics[i].X = i * dt;
        physics[i].Y = L0 * exp(-z * (dt * i + t1)) * cos(w * (dt * i + t1) + f0);
    }
}

void addition_of_co_directional_oscillation (double& L01, double& w1, double& f01, double& L02, double& w2, double& f02, double& dt, double& t1, double& t2)
{
    cout << "Enter parameters:" << endl;
    cout << "\tEnter L01: ";
    cin >> L01;
    cout << "\tEnter w1: ";
    cin >> w1;
    cout << "\tEnter f01: ";
    cin >> f01;
    cout << "\tEnter L02: ";
    cin >> L02;
    cout << "\tEnter w2: ";
    cin >> w2;
    cout << "\tEnter f02: ";
    cin >> f02;
    cout << "\tEnter [ t1 ; t2 ]: ";
    cin >> t1 >> t2;
    cout << "\tEnter dt: ";
    cin >> dt;
    if (dt < 1.0E-5)
        throw error_dt(dt);

    physics = new coordinate[round((t2 - t1) / dt)];

    for (int i = 0; i < round(t2 - t1) / dt; i++)
    {
        physics[i].X = i * dt;
        physics[i].Y = L01 * cos(w1 * (dt * i + t1) + f01) + L02 * cos(w2 * (dt * i + t1) + f02);
    }
}

int WINAPI DlgProc(HWND hDlg, WORD wMsg, WORD wParam, DWORD dwParam)
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

            if (control == 1)
            {
                double L0, w, z, f0;
                harmonic_oscillation(L0, w, f0, dt, t1, t2);

                pixel = new coordinate[round((t2 - t1) / dt)];

                for (int i = 0; i < round((t2 - t1) / dt); i++)
                {
                    pixel[i].X = physics[i].X * width / (t2 - t1);
                    pixel[i].Y = height / 2 - 0.5 * physics[i].Y * height / L0;
                }
            }

            if (control == 2)
            {
                double L0, w, z, f0;
                damped_oscillation(L0, w, z, f0, dt, t1, t2);

                pixel = new coordinate[round((t2 - t1) / dt)];

                for (int i = 0; i < round((t2 - t1) / dt); i++)
                {
                    pixel[i].X = physics[i].X * width / (t2 - t1);
                    pixel[i].Y = height / 2 - 0.5 * physics[i].Y * height / (L0 * exp(-z * t1));
                }
            }

            if (control == 3)
            {
                double L01, w1, f01, L02, w2, f02;
                addition_of_co_directional_oscillation(L01, w1, f01, L02, w2, f02, dt, t1, t2);

                pixel = new coordinate[round((t2 - t1) / dt)];

                for (int i = 0; i < round((t2 - t1) / dt); i++)
                {
                    pixel[i].X = physics[i].X * width / (t2 - t1);
                    pixel[i].Y = height / 2 - 0.5 * physics[i].Y * height / (L01 + L02);
                }
            }
        }
        else if (wMsg == WM_PAINT)
        {
            BeginPaint(hDlg, &ps);

            HPEN hPen = (HPEN)CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
            HPEN hOldPen = (HPEN)SelectObject(ps.hdc, hPen);
            POINT ptOld;
            MoveToEx(ps.hdc, 0, height / 2, &ptOld);
            LineTo(ps.hdc, width, height / 2);

            hPen = (HPEN)CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
            hOldPen = (HPEN)SelectObject(ps.hdc, hPen);

            for (int i = 0; i < round((t2 - t1) / dt) - 1; i++)
            {
                MoveToEx(ps.hdc, pixel[i].X, pixel[i].Y, &ptOld);
                LineTo(ps.hdc, pixel[i + 1].X, pixel[i + 1].Y);
            }

            SelectObject(ps.hdc, hOldPen);
            DeleteObject(hPen);
            EndPaint(hDlg, &ps);
        }

    return 0; 
}

int main()
{
    setlocale(LC_ALL, "");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    control = 3;

    try
    {
        DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);

        delete[] physics;
        delete[] pixel;
    }
    catch (error_m x)
    {
        cerr << "m = " << x.num << " too little!" << endl;
    }
    catch (error_dt x)
    {
        cerr << "dt = " << x.num << " too little!" << endl;
    }
    catch (error_no_oscillation x)
    {
        cerr << "For given value w = " << x.a << ", z = " << x.b << " will be aperiodic mode!" << endl;
    }
}