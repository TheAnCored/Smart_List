#include <iostream>
#include "header.hpp"

using namespace std;

int main(){

    size_t length=0;

    std::cout<< " Input length of list: "; std::cin >> length; std::cout <<endl;

    std::unique_ptr<double[]> array = input_by_console(length);

    List list(length, std::move(array));

    output_list(list);

    return 0;
}