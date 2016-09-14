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

    // make a graph
    gdwg::Graph<unsigned int,int> g;

    g.addNode(2);
    g.addNode(3);
    g.addNode(1);
    g.addNode(2);

//
    g.printNodes();

    return 0;
}