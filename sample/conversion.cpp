#include <iostream>
#include <string>

int main() {
    std::string str = "";

    // convert string to float
    float num_float = std::stof(str);

    // convert string to double
    double num_double = std::stod(str);

   std:: cout<< "num_float = " << num_float << std::endl;
   std:: cout<< "num_double = " << num_double << std::endl;

    return 0;
}