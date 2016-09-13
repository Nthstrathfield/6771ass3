#include <iostream>
#include "Graph.h"
#include <memory>

int main() {
    // test Node
//    gdwg::Node<int, int> a(1);
//    gdwg::Node<int, int> b(a);
//    std::shared_ptr<gdwg::Edge<int>> first = std::make_shared<gdwg::Edge<int>>(2, 2);
//    a.sete(first);
//    a.printnode();
//    b.printnode();

    // test graph
    gdwg::Graph<int, int> a;
    int c =a.addNode(2);
    int i = a.addNode(2);

    std::cout<<c<<i;

    return 0;
}