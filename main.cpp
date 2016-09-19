#include "Graph.h"


int main() {

    gdwg::Graph<std::string,int> gCopy;

    // create some data to store as nodes.
    std::string a = "a";
    std::string b = "b";
    std::string c = "c";
    std::string d = "d";
    std::string e = "e";

    // add this data into the graph
    gCopy.addNode(a);
    gCopy.addNode(b);
    gCopy.addNode(c);
    gCopy.addNode(d);

    gCopy.addEdge(a,a,2);

    gCopy.addEdge(a,b,1);
    gCopy.addEdge(b,a,2);

    gCopy.addEdge(a,c,1);
    gCopy.addEdge(c,a,2);

    gCopy.addEdge(a,d,1);
    gCopy.addEdge(d,a,2);

    gCopy.addEdge(b,c,1);
    gCopy.addEdge(c,d,2);


    std::cout << "Graph before node replacement" << std::endl;
    gCopy.printNodes();

    // replace node
    std::cout << "Node a edge" << std::endl;
    gCopy.printEdges("a");
    gCopy.replace("a","e");
    std::cout << "Graph after node replacement" << std::endl;
    gCopy.printNodes();
    std::cout << "Node e edge" << std::endl;
    gCopy.printEdges("e");

    std::cout << "Node b edge" << std::endl;
    gCopy.printEdges(b);

}