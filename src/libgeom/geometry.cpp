#include "geometry.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

const double Pi = 3.1415;

// Geometric operations
double C_S(double r)
{
    double S = Pi * pow(r, 2);
    return S;
}

double C_P(double r)
{
    double P = 2 * Pi * r;
    return P;
}

// Analisis function
Point Point_analysis(int string, int& lfound, std::string storage[])
{
    Point P;
    std::size_t found, l_number, r_number;
    std::string str = storage[string], str_r = "", numbers = "1234567890.-";
    found = str.find(")");
    if (found != std::string::npos) {
        // X analysis
        l_number = str.find_first_of(numbers, lfound);
        for (r_number = l_number;
             numbers.find(str[r_number]) != std::string::npos;
             r_number++)
            ;
        std::string str_x;
        str_x.append(str, l_number, r_number);
        P.x = atof(str_x.c_str());

        // Y analysis
        r_number = str.find_last_of(numbers, str.find_first_of(",", lfound));
        for (l_number = r_number;
             numbers.find(str[l_number]) != std::string::npos;
             l_number--)
            ;
        std::string str_y;
        str_y.append(str, l_number, r_number);
        P.y = atof(str_y.c_str());

        // New left border
        lfound = str.find_first_of(",", lfound) + 1;
    } else {
        printf("Error ");
    }
    return P;
}

Circle Circle_analysis(int order, int string, std::string storage[])
{
    Circle C;
    std::size_t found, r_number, l_number, rezfound;
    std::string x = storage[string], str_r = "", numbers = "1234567890";

    C.Order = order;

    found = x.find(",");
    if (found != std::string::npos) {
        l_number = x.find_first_of(numbers, found);
        r_number = x.find_last_of(numbers);
        rezfound = r_number - l_number + 1;
        str_r.append(x, l_number, rezfound);

        C.r = atof(str_r.c_str());

        C.S = C_S(C.r);

        C.P = C_P(C.r);

    } else {
        printf("Error ");
    }

    int lfound = storage[string].find("(");
    C.Center = Point_analysis(string, lfound, storage);
    return C;
}

Triangle Triangle_analysis(int order, int string, std::string storage[])
{
    Triangle T;

    T.Order = order;

    int lfound = storage[string].find("(");
    T.A = Point_analysis(string, lfound, storage);
    T.B = Point_analysis(string, lfound, storage);
    T.C = Point_analysis(string, lfound, storage);
    T.End = Point_analysis(string, lfound, storage);

    T.S = 0.5
            * abs((T.A.x - T.C.x) * (T.B.y - T.C.y)
                  - (T.B.x - T.C.x) * (T.A.y - T.C.y));

    float AB = sqrt(pow(T.B.x - T.A.x, 2) + pow(T.B.y - T.A.y, 2));
    float BC = sqrt(pow(T.C.x - T.B.x, 2) + pow(T.C.y - T.B.y, 2));
    float CA = sqrt(pow(T.A.x - T.C.x, 2) + pow(T.A.y - T.C.y, 2));
    T.P = AB + BC + CA;
    return T;
}

// Intersectio function
int Intersec_T(Point A, Point B, Point C, Point D)
{
    float Ua = ((D.x - C.x) * (A.y - C.y) - (D.y - C.y) * (A.x - C.x))
            / ((D.y - C.y) * (B.x - A.x) - (D.x - C.x) * (B.y - A.y));
    float Ub = ((B.x - A.x) * (A.y - C.y) - (B.y - A.y) * (A.x - C.x))
            / ((D.y - C.y) * (B.x - A.x) - (D.x - C.x) * (B.y - A.y));

    if ((0 <= Ua && Ua <= 1) && (0 <= Ub && Ub <= 1)) {
        return 1;
    } else {
        return 0;
    }
}

int Intersec_C(Point A, Point B, Point C, float r)
{
    float D;
    float At = pow(A.x - B.x, 2) + pow(A.y + B.y, 2);
    float Bt = pow(A.x - C.x, 2) + pow(A.y + C.y, 2);
    float Ct = pow(C.x - B.x, 2) + pow(C.y + B.y, 2);
    float S = abs((A.x - C.x) * (B.x - C.x) - (B.x - C.x) * (A.y - C.y)) / 2;
    float h = 2 * S / sqrt(Ct);
    if ((At + Ct < Bt) || (Bt + Ct < At)) {
        if (At < Bt) {
            D = sqrt(At);
        } else {
            D = sqrt(Bt);
        }
    } else {
        D = h;
    }

    if (r >= D) {
        return 1;
    } else {
        return 0;
    }
}

void Circle_intersec(Circle C, Circle CM[], int s_CM, Triangle TM[], int s_TM)
{
    for (int counter = 0; counter < s_CM; counter++) {
        if (C.Order != CM[counter].Order) {
            Circle X = CM[counter];
            float h
                    = sqrt(pow(abs(C.Center.y - X.Center.y), 2)
                           + pow(abs(C.Center.x - X.Center.y), 2));
            float d = (C.r + X.r);
            if (h <= d) {
                std::cout << "          " << X.Order << ". circle" << std::endl;
                break;
            }
        }
    }
    for (int counter = 0; counter < s_TM; counter++) {
        int cheak[3];
        Triangle X = TM[counter];
        cheak[0] = Intersec_C(X.A, X.B, C.Center, C.r);
        cheak[1] = Intersec_C(X.B, X.C, C.Center, C.r);
        cheak[2] = Intersec_C(X.C, X.A, C.Center, C.r);
        for (int i = 0; i < 3; i++) {
            if (cheak[i] == 1) {
                std::cout << "          " << X.Order << ". triangle"
                          << std::endl;
                break;
            }
        }
    }
}

void Triangle_intersec(
        Triangle T, Circle CM[], int s_CM, Triangle TM[], int s_TM)
{
    for (int counter = 0; counter < s_CM; counter++) {
        int cheak[3];
        Circle X = CM[counter];
        cheak[0] = Intersec_C(T.A, T.B, X.Center, X.r);
        cheak[1] = Intersec_C(T.B, T.C, X.Center, X.r);
        cheak[2] = Intersec_C(T.C, T.A, X.Center, X.r);
        for (int i = 0; i < 3; i++) {
            if (cheak[i] == 1) {
                std::cout << "          " << X.Order << ". circle" << std::endl;
                break;
            }
        }
    }

    for (int counter = 0; counter < s_TM; counter++) {
        if (T.Order != TM[counter].Order) {
            int cheak[9];
            Triangle X = TM[counter];
            cheak[0] = Intersec_T(T.A, T.B, X.A, X.B);
            cheak[1] = Intersec_T(T.A, T.B, X.B, X.C);
            cheak[2] = Intersec_T(T.A, T.B, X.C, X.A);

            cheak[3] = Intersec_T(T.B, T.C, X.A, X.B);
            cheak[4] = Intersec_T(T.B, T.C, X.B, X.C);
            cheak[5] = Intersec_T(T.B, T.C, X.C, X.A);

            cheak[6] = Intersec_T(T.C, T.A, X.A, X.B);
            cheak[7] = Intersec_T(T.C, T.A, X.B, X.C);
            cheak[8] = Intersec_T(T.C, T.A, X.C, X.A);

            for (int i = 0; i < 9; i++) {
                if (cheak[i] == 1) {
                    std::cout << "          " << X.Order << ". triangle"
                              << std::endl;
                    break;
                }
            }
        }
    }
}

// Printing function
void Circle_print(Circle C, std::string storage[])
{
    std::cout << "\n " << C.Order << ". " << storage[C.Order - 1]
              << "\n      perimeter = " << C.P << "\n      area = " << C.S
              << std::endl;
}

void Triangle_print(Triangle T, std::string storage[])
{
    std::cout << "\n " << T.Order << ". " << storage[T.Order - 1]
              << "\n      perimeter = " << T.P << "\n      area = " << T.S
              << std::endl;
}
