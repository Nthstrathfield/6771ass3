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
        Node(N &value): value_{value}, next_{nullptr} {};
        Node();
        // copy constructor
        Node (const Node<N, E> &cpy);
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
        Edge<E>(E weight, int index): weight_(weight), index_(index), next_{nullptr}  {};
        // copy constructor
        Edge<E>(Edge &cpy);
        // memebr function
        E getw() {
            return weight_;
        }
        E geti() {
            return index_;
        }
    };

    // Graph template
    template <typename N, typename E> class Graph {

     private:
        // save node pointer node->egde1(node index|edge value)->edge2(node index|edge value)
        std::vector<Node<N, E>*> node_;
     public:
        // default constructor
        Graph(){};
        // copy constructor
        Graph(Graph<N, E> &cpy) {
            for(unsigned int i; i < node_.size(); node_++) {

            }
        };
        // move constructor
        Graph(Graph<N, E> &&cpy) {};
        //return number of nodes
        int num_node();
    };

}


// node copy constructor
template <typename N, typename E>
gdwg::Node<N, E>::Node(const Node &cpy)  {
//    value_ = cpy.value_;
//    std::shared_ptr<Edge<E>> itorator;
//    itorator = cpy.next_;
//    if(itorator != nullptr) {
//        std::make_shared(Edge<E>{itorator->getw(),itorator->geti()});
//    }
//    while(itorator!= nullptr) {
//        itorator = itorator->next_;
//    }


};

template <typename N, typename E>
int gdwg::Graph<N, E>::num_node() {
    return node_.size();
}


