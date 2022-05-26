#pragma once

#include <string>

using namespace std;

struct Point {
    double x;
    double y;
};

struct Circle {
    int Order;
    Point Center;
    double r;
    double P;
    double S;
};

struct Triangle {
    int Order;
    Point A;
    Point B;
    Point C;
    Point End;
    double P;
    double S;
};

double C_S(double r);
double C_P(double r);

Point Point_analysis(int string, int& lfound, std::string storage[]);
Circle Circle_analysis(int order, int string, std::string storage[]);
Triangle Triangle_analysis(int order, int string, std::string storage[]);

int Intersec_T(Point A, Point B, Point C, Point D);
int Intersec_C(Point A, Point B, Point C, float r);

void Circle_intersec(
        Circle C, Circle CM[], int size_CM, Triangle TM[], int size_TM);
void Triangle_intersec(
        Triangle T, Circle CM[], int size_CM, Triangle TM[], int size_TM);

void Circle_print(Circle C, std::string storage[]);
void Triangle_print(Triangle T, std::string storage[]);
