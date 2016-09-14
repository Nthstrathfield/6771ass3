#include <vector>
#include <memory>
#include <stdexcept>
// Using Adjacency List to represent graph
// copy node first, then edge

namespace gdwg {


    template <typename N, typename E> class Edge;


    /******************** Node ***************************/
    template <typename N, typename E>
    class Node {
     private:
        N value_;
        std::shared_ptr<Edge<N, E>> next_;
     public:
        // Constructor
        Node(const N &value): value_{value}, next_{nullptr} {};
        Node (const Node<N, E> &cpy);
        // MEMBER FUNCTION
        void setn(std::shared_ptr<Edge<N, E>> new_edge);
        void printnode();
        N getv();
        std::shared_ptr<Edge<N, E>> getn();
        bool containedge(const Edge<N, E> &edge);
    };


    /********************* Edge ***************************/
    template <typename N, typename E>
    class Edge {
     private:
        E weight_;
        // save the index of the node, which this edge point to
        N nvalue_;
        std::shared_ptr<Edge<N, E>> next_;
     public:
        // Constructor
        Edge(E weight, N nvalue): weight_(weight), nvalue_(nvalue), next_{nullptr}  {};
        Edge(Edge &cpy);
        // MEMBER FUNCTION
        E getw();
        std::shared_ptr<Edge<N, E>> getn();
        void setn(std::shared_ptr<Edge<N, E>> n);
        N getnvlue();


    };


    /*********************** Graph ***************************/
    template <typename N, typename E> class Graph {

     private:
        // save node pointer node->egde1(node index|edge value)->edge2(node index|edge value)
        std::vector<std::shared_ptr<Node<N, E>>> node_;
     public:
        // default constructor
        Graph(){};
        // copy constructor
        Graph(const Graph<N, E> &cpy);
        // move constructor
        Graph(Graph<N, E> &&cpy);

        // MEMBER FUNCTION
        int num_node();
        bool addNode(const N& val);
        bool addEdge(const N& src, const N& dst, const E& w);
        bool replace(const N& oldData, const N& newData);
        void mergeReplace(const N& oldData, const N& newData);
    };


    // replace node value
    template <typename N, typename E>
    bool Graph<N, E>::replace(const N& oldData, const N& newData) {
        int oldi = -1;
        int newi = -1;
        for (unsigned int i = 0; i < num_node(); ++i) {
            if (node_[i]->getv() == oldData ) {
                oldi = i;
            }
            if (node_[i]->getv() == newData ) {
                newi = i;
            }
        }
        try {
            if(oldi == -1) {
                throw std::runtime_error("can't find src node");
            }
            if(newi != -1) {
                return false;
            }
            node_[oldi]->setn(std::make_shared<Edge<N, E>>(newData));
            return true;
        }
        catch (std::runtime_error &e) {
            std::cout<<"can't find src node";
        }
    };

    // Check if node contains same edge
    template <typename N, typename E>
    bool Node<N, E>::containedge(const Edge<N, E> &edge) {
        auto itorator = next_;
        while (itorator != nullptr) {
            if (*itorator == edge) {
                return true;
            }
            itorator = itorator->getn();
        }
        return false;
    }



    // replace node value
    template <typename N, typename E>
    void Graph<N, E>::mergeReplace(const N &oldData, const N &newData) {
        int oldi = -1;
        int newi = -1;
        for (unsigned int i = 0; i < num_node(); ++i) {
            if (node_[i]->getv() == oldData ) {
                oldi = i;
            }
            if (node_[i]->getv() == newData ) {
                newi = i;
            }
        }
        try {
            if(oldi == -1 || newi == -1 ) {
                throw std::runtime_error("can't find one of the node");
            }

        }
        catch (std::runtime_error &e) {
            std::cout<<"can't find one of the node";
        }
    };



#include "Graph.tmp"

}
