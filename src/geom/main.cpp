#include "libgeom/geometry.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

int main()
{
    int counter = 0;
    const int storage_size = 100;
    const int figure_limit = 10;
    std::string line, file_name;
    std::string storage[storage_size];
    Circle Circle_mass[figure_limit];
    Triangle Triangle_mass[figure_limit];

    // Open file
    std::cout << "\n The program accepts format files as input .wkt!";
    // std::cout << "\n Enter the full file name: ";
    // std::cin >> file_name;
    file_name = "wkt.wkt";

    std::ifstream in(file_name);
    if (in.is_open()) {
        while (getline(in, line)) {
            storage[counter] = line;
            counter++;
        }
    } else {
        printf(" !Open File Error\n !File not found");
    }

    // Search for shapes in a string
    int check = 0;
    int order_counter = 0;
    int Circle_counter = 0;
    int Triangle_counter = 0;

    for (int counter_f = 0; counter_f < counter; counter_f++) {
        std::size_t found;

        // Circle
        found = storage[counter_f].find("circle");
        if (found != std::string::npos) {
            check++;
            order_counter++;
            Circle_mass[Circle_counter]
                    = Circle_analysis(order_counter, counter_f, storage);
            Circle_counter++;
        }

        // Triangle
        found = storage[counter_f].find("triangle");
        if (found != std::string::npos) {
            check++;
            order_counter++;
            Triangle_mass[Triangle_counter]
                    = Triangle_analysis(order_counter, counter_f, storage);
            Triangle_counter++;
        }

        // Error
        if (check == 0) {
            printf("\n\n #Error in %d line, «circle» , «triangle» not found ",
                   counter_f + 1);
            std::cout << "\n " << counter_f + 1 << ". " << storage[counter_f]
                      << std::endl;
        }
        check = 0;
    }

    // Checking intersections

    // Output of results
    int fig_counter = Triangle_counter + Circle_counter + 1;
    int Triangle_pr = 0;
    int Circle_pr = 0;
    for (int counter_f = 1; counter_f < fig_counter; counter_f++) {
        if (Triangle_mass[Triangle_pr].Order == counter_f) {
            Triangle_print(Triangle_mass[Triangle_pr], storage);
            printf("      intersects:\n");
            Triangle_intersec(
                    Triangle_mass[Triangle_pr],
                    Circle_mass,
                    Circle_counter,
                    Triangle_mass,
                    Triangle_counter);
            Triangle_pr++;
        } else if (Circle_mass[Circle_pr].Order == counter_f) {
            Circle_print(Circle_mass[Circle_pr], storage);
            Circle_intersec(
                    Circle_mass[Circle_pr],
                    Circle_mass,
                    Circle_counter,
                    Triangle_mass,
                    Triangle_counter);
            Circle_pr++;
        }
    }

    in.close();
    std::cout << "\n\n End of programm\n" << std::endl;
    return 0;
}
