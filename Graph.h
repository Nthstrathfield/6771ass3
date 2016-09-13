#include <vector>
#include <memory>
#include <stdexcept>
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
        N getv() {
            return value_;
        }
        std::shared_ptr<Edge<E>> getn() {
            return next_;
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

        template <typename E>
        friend bool operator == (const Edge<E> &, const Edge<E> &);

    };

    // Graph template
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

        /****************** member function *******************/
        //return number of nodes
        int num_node();
        // add node
        bool addNode(const N& val);
        // add edge
        bool addEdge(const N& src, const N& dst, const E& w);

    };

    template <typename E>
    bool operator == (const Edge<E> &, const Edge<E> &);

}
// friend operator == for Edge
template <typename E>
bool gdwg::operator == (const Edge<E> &lft, const Edge<E> &rht) {

    return lft.index_==rht.index_ && lft.weight_==rht.weight_;
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
gdwg::Graph<N, E>::Graph(const gdwg::Graph<N, E> &cpy) {
    for(unsigned int i = 0; i < cpy.node_.size(); i++) {
        Node<N, E> new_node(*cpy.node_[i]);
        node_.pop_back(std::make_shared<Node<N, E>>(new_node));
    }
}

// move constructor
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(Graph<N, E> &&cpy) {
    for(unsigned int i = 0; i < cpy.node_.size(); i++) {
        node_.pop_back(cpy.node_[i]);
        cpy.node_[i] = nullptr;
    }
}

// return numer of node
template <typename N, typename E>
int gdwg::Graph<N, E>::num_node() {
    return node_.size();
}


// add new node
template <typename N, typename E>
bool gdwg::Graph<N, E>::addNode(const N &val) {
    for (unsigned int i = 0; i < num_node(); ++i) {
        if(node_[i]->getv() == val)
        {
            return false;
        }
    }
    std::shared_ptr<gdwg::Node<N, E>> insert = std::make_shared<gdwg::Node<N, E>>(val);
    node_.push_back(insert);
    return true;
}

// add new edge
template <typename N, typename E>
bool gdwg::Graph<N, E>::addEdge(const N &src, const N &dst, const E &w) {
    // record index
    int srci = -1;
    int dsti = -1;
    try {
        for (unsigned i = 0; i <= num_node(); ++i) {
            if (node_[i]->getv() == sec) {
                srci = i;
            }
            if (node_[i]->getv() == dst) {
                dsti = i;
            }
        }
        if (srci == -1 || dsti == -1) {
            throw std::runtime_error("can't find node");
        }
    }
    catch (std::runtime_error &e) {
        std::cout<<"oh no";
    }
    auto itorator = node_[srci]->getn();
    while (itorator != nullptr) {
        if(*itorator == )

        if (itorator->getn()!= nullptr) {
            itorator = itorator->getn();
        } else {
            break;
        }
    }


}