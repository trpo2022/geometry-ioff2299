#include <libgeom/geometry.h>

#include <ctest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CTEST(figure, circle_s)
{
    double r = 3;

    double result = C_S(r);

    double expected = 28.274334;

    ASSERT_DBL_NEAR_TOL(expected, result, 1e-3);
}

CTEST(figure, circle_p)
{
    double r = 3;

    double result = C_P(r);

    double expected = 18.84955592153876;

    ASSERT_DBL_NEAR_TOL(expected, result, 1e-3);
}

CTEST(figure, point_analis)
{
    int string = 0;
    int lfound = 0;
    std::string storage[] = {"triangle((-3.0 -2, -1 0.0, -3.0 2.0, -3 -2))"};
    Point P;

    Point P_exp;
    P_exp.x = -3.0;
    P_exp.y = -2;

    P = Point_analysis(string, lfound, storage);

    ASSERT_DBL_NEAR_TOL(P_exp.x + P_exp.y, P.x + P.y, 1e-3);
}

CTEST(figure, test_circle_analysis)
{
    int string = 0;
    int order = 0;
    std::string storage[] = {"circle(0 0, 1.5)"};

    Circle C;
    C = Circle_analysis(order, string, storage);

    Circle C_exp;
    C_exp.r = 1.5;
    C_exp.Center.x = 0;
    C_exp.Center.y = 0;

    ASSERT_DBL_NEAR_TOL(C_exp.r, C.r, 1e-3);
    ASSERT_DBL_NEAR_TOL(C_exp.Center.x, C.Center.x, 1e-3);
    ASSERT_DBL_NEAR_TOL(C_exp.Center.y, C.Center.y, 1e-3);
}

CTEST(figure, test_triangle_analysis)
{
    int string = 0;
    int order = 0;
    std::string storage[] = {"triangle((3 -2.0, 3.0 2, 1.0 0, 3.0 -2))"};

    Triangle T;
    T = Triangle_analysis(order, string, storage);

    Triangle T_exp;
    T_exp.A.x = 3;
    T_exp.A.y = -2.0;

    T_exp.B.x = 3.0;
    T_exp.B.y = 2;

    T_exp.C.x = 1.0;
    T_exp.C.y = 0;

    ASSERT_DBL_NEAR_TOL(T_exp.A.x, T.A.x, 1e-3);
    ASSERT_DBL_NEAR_TOL(T_exp.A.y, T.A.y, 1e-3);

    ASSERT_DBL_NEAR_TOL(T_exp.B.x, T.B.x, 1e-3);
    ASSERT_DBL_NEAR_TOL(T_exp.B.y, T.B.y, 1e-3);

    ASSERT_DBL_NEAR_TOL(T_exp.C.x, T.C.x, 1e-3);
    ASSERT_DBL_NEAR_TOL(T_exp.C.y, T.C.y, 1e-3);
}
