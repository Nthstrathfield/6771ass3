#include <iostream>
#include "Graph.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    gdwg::Graph<std::string, int> a;
    std::cout<<a.num_node();

//    int k = a.getg();
//    std::cout<<k<<std::endl;

    return 0;
}