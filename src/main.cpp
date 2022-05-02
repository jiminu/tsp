#include <iostream>
#include "file_stream.h"

int main(int, char**) {
    string tspFile = "../data/tsp_data.txt";
    
    FileStream file;
    
    file.read_from_file(tspFile);
    vector<Point> point = file.get_points();
    
    std::cout << "Hello, world!\n";
}
