#include <vector>
#include <memory>
// Using Adjacency List to represent graph
// copy node first, then edge

namespace gdwg {

    template <typename E> class Edge;

    // Node template
    template <typename N, typename E>
    class Node {
     private:
        N value_;
        std::shared_ptr<Edge<E>> next_;
     public:
        // default constructor
        Node(const N &value): value_{value}, next_{nullptr} {};
        // copy constructor
        Node (const Node<N, E> &cpy);
        // set edge;
        void sete(std::shared_ptr<Edge<E>> new_edge) {
            if (next_ == nullptr) {
                next_ = new_edge;
            } else {
                std::shared_ptr<Edge<E>> itorator = next_;
                while (itorator->getn() != nullptr) {
                    itorator = itorator->getn();
                }
                itorator->setn(new_edge);
            }
        }
        // print;
        void printnode() {
            std::cout<<value_;
            std::shared_ptr<Edge<E>> itorator;
            if(next_ != nullptr) {
                itorator = next_;
            }
            else {
                return;
            }
            while (itorator != nullptr) {
                std::cout<<itorator->geti();
                std::cout<<" ";
                itorator = itorator->getn();
            }
        }

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
        Edge(E weight, int index): weight_(weight), index_(index), next_{nullptr}  {};
        // copy constructor
        Edge(Edge &cpy);
        // memebr function
        E getw() {
            return weight_;
        }
        int geti() {
            return index_;
        }
        std::shared_ptr<Edge<E>> getn() {
            return next_;
        }
        void setn(std::shared_ptr<Edge<E>> n) {
            next_ = n;
        }
    };

    // Graph template
    template <typename N, typename E> class Graph {

     private:
        // save node pointer node->egde1(node index|edge value)->edge2(node index|edge value)
        std::vector<std::shared_ptr<Node>> node_;
     public:
        // default constructor
        Graph(){};
        // copy constructor
        Graph(const Graph<N, E> &cpy);
        // move constructor
        Graph(Graph<N, E> &&cpy) {};
        //return number of nodes
        int num_node();
    };

}


// node deep copy constructor, as well as copy the related edges
template <typename N, typename E>
gdwg::Node<N, E>::Node(const Node &cpy)  {
    value_ = cpy.value_;
    std::shared_ptr<Edge<E>> itorator;
    std::shared_ptr<Edge<E>> itorator_new;
    itorator = cpy.next_;
    if(itorator != nullptr) {
        next_ = std::make_shared<Edge<E>>(itorator->getw(), itorator->geti());
        itorator_new = next_;
        itorator = itorator->getn();
    } else {
        return ;
    }
    while(itorator!= nullptr) {
        // generate new edge node
        itorator_new->setn(std::make_shared<Edge<E>>(itorator->getw(), itorator->geti()));
        // go through old
        itorator = itorator->getn();
        // go through new
        itorator_new = itorator_new->getn();
    }
};

// graph deep copy constructor;



template <typename N, typename E>
int gdwg::Graph<N, E>::num_node() {
    return node_.size();
}


