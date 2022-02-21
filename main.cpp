#include <cstring>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

const double Pi = 3.14159265358979323;
int count_g = 0;

void Circle(int string, std::string storage[]){
    count_g++;
    float perimeter, area;
    int counter = 0;
    double r, S, P;
    std::size_t found, lfound, rfound, rezfound;
    std::string x = storage[string], str_r = "", numbers = "1234567890";

    std::cout << "\n\n " << count_g << ". " << x
              << std::endl; // 1 output string

    found = x.find(",");
    if (found != std::string::npos) {
        lfound = x.find_first_of(numbers, found);
        rfound = x.find_last_of(numbers);
        rezfound = rfound - lfound + 1;
        
        str_r.append(x, lfound, rezfound);
        r = atof(str_r.c_str());
        S = Pi * pow(r, 2);
        printf("    S = %f", S); // 2 output string
        P = 2 * Pi * r;
        printf("\n    P = %f", P); // 3 output string
    } else {
        printf("Error ");
    }
}

void Triangle(int string, std::string storage[]){
    count_g++;
    std::cout << "\n\n " << count_g << ". " << storage[string] << std::endl;
}

int main(){
    int counter = 0;
    int storage_size = 100;
    std::string storage[storage_size];
    std::string line;
    std::ifstream in("wkt.wkt");
    if (in.is_open()) {
        while (getline(in, line)) {
            storage[counter] = line;
            counter++;
        }
    } else {
        printf("Open File Error");
    }

    int verif_counter = 0;
    for (int counter_f = 0; counter_f < counter; counter_f++) {
        std::size_t found;
        found = storage[counter_f].find("circle");
        if (found != std::string::npos) {
            verif_counter++;
            Circle(counter_f, storage);
        }

        found = storage[counter_f].find("triangle");
        if (found != std::string::npos) {
            verif_counter++;
            Triangle(counter_f, storage);
        }

        if (verif_counter == 0) {
            printf("\n\n #Error in %d line, «circle» , «triangle»  or «polygon»  not found ", counter_f + 1);
            std::cout << "\n "<< counter_f + 1<< ". " <<storage[counter_f] << std::endl;
        }
        verif_counter = 0;
    }

    in.close();
    std::cout << "\n End of programm\n" << std::endl;
    return 0;
}
