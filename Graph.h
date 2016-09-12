#include <vector>
#include <memory>
// Using Adjacency List to represent graph
// copy node first, then edge

namespace gdwg{

    template <typename E> class Edge;
    // Node template
    template <typename N, typename E>
    class Node {
     private:
        N value_;
        std::shared_ptr<Edge<E>> next_;
     public:
        // default constructor
        Node<N, E>(N &value): value_{value}, next_{nullptr} {};
        // copy constructor
        Node<N, E>(Node<N, E> &cpy):{};
    };

    // Edge template
    template <typename E>
    class Edge {
     private:
        E weight_;
        // save the index of the node, which this edge point to
        int index_;
        std::shared_ptr<Edge<E>> next_;
     public:
        // default constructor
        Edge<E>(E weight, int index, Edge<E> *arg): weight_(weight), index_(index), next_{std::make_shared<E>(arg)} {};
        // copy constructor
    };

    // Graph template
    template <typename N, typename E> class Graph {

     private:
        // save node pointer node->egde1(node index|edge value)->edge2(node index|edge value)
        std::vector<Node<N, E>*> node_;
     public:
        // default constructor
        Graph<N, E>(){};
        // copy constructor
        Graph<N, E>(Graph<N, E> &cpy) {
            for(unsigned int i; i < node_.size(); node_++) {

            }
        };
        // move constructor
        Graph<N, E>(Graph<N, E> &&cpy) {};
        //return number of nodes
        int num_node();
    };

}

// node copy constructor
template <typename N, typename E>
gdwg::Node::Node<N, E>(Node<N, E> &cpy) {

};

template <typename N, typename E>
int gdwg::Graph<N, E>::num_node() {
    return node_.size();
}


