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
        void addnewedge(const Edge<N, E> &edge);
        void merge(const N &, const N &);
        void removeedge(const N &node, const E &weight);
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
        Edge(N nvalue, E weight): weight_(weight), nvalue_(nvalue), next_{nullptr}  {};
        Edge(Edge &cpy);
        // MEMBER FUNCTION
        E getw();
        std::shared_ptr<Edge<N, E>> getn();
        void setn(std::shared_ptr<Edge<N, E>> n);
        void setnvalue(N nvalue);
        N getnvlue();

        // friend operator == for Edge

        friend bool operator == (const Edge<N, E> &, const Edge<N, E> &);

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


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // remove edge base value
    template <typename N, typename E>
    void Node<N, E>::removeedge(const N &node, const E &weight) {
        auto itorator = next_;
        auto pre = next_;
        if (itorator == nullptr) {
            return;
        }
        if (itorator->getn() == nullptr) {
            if(itorator->getnvlue() = node && itorator->getw() = weight) {
                delete itorator;
                itorator = nullptr;
                next_ = nullptr;
            }
            return;
        }
        itorator = itorator->getn();
        while (itorator->getn() != nullptr) {
            if(itorator->getnvlue() = node && itorator->getw() = weight) {
                pre->setn(itorator);
                delete itorator;
                itorator = nullptr;
                return;
            }
            pre = itorator;
            itorator = itorator->getn();
        }
        if(itorator->getnvlue() = node && itorator->getw() = weight) {
            pre->setn(itorator);
            delete itorator;
            itorator = nullptr;
        }
        return;


    }
    //  merge same
    template <typename N, typename E>
    void Node<N, E>::merge(const N &old_edge, const N & new_edge) {
        auto itorator = next_;
        std::vector<E> memory;
        while (itorator != nullptr) {
            if(itorator->getnvlue() == old_edge || itorator->getnvlue() == new_edge) {
                itorator->setnvalue(new_edge);
                int flag = 0;
                for (unsigned int i = 0; i < memory.size(); ++i) {
                    if (memory[i] == itorator->getw()) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 1) {
                    auto tmp = itorator;
                    itorator = itorator->getn();
                    removeedge(tmp->getnvlue(), tmp->getw());
                }
                else {
                    memory.push_back(itorator->getw());
                    itorator = itorator->getn();
                }
            }
        }
    }
    // set nvalue
    template <typename N, typename E>
    void Edge<N, E>::setnvalue(N nvalue) {
        nvalue_ = nvalue;

    }

    // node add new edge
    template <typename N, typename E>
    void Node<N, E>::addnewedge(const Edge<N, E> &edge) {
        auto itorator = next_;
        while (itorator != nullptr) {
            if (itorator->getn() != nullptr) {
                itorator = itorator->getn();
            } else {
                break;
            }
        }
        itorator->setn(std::make_shared<Edge<N,E>>(edge.getnvlue(), edge.getw()));
    }

    // frind operator
    template <typename N, typename E>
    bool operator == (const Edge<N, E> &lft, const Edge<N, E> &rht) {

        return lft.nvalue_==rht.nvalue_ && lft.weight_==rht.weight_;
    }


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



    // replace and merge node value
    template <typename N, typename E>
    void Graph<N, E>::mergeReplace(const N &oldData, const N &newData) {
        int oldi = -1;
        int newi = -1;
        for (unsigned int i = 0; i < num_node(); ++i) {
            if (node_[i]->getv() == oldData) {
                oldi = i;
            }
            if (node_[i]->getv() == newData) {
                newi = i;
            }
        }
        try {
            if(oldi == -1 || newi == -1) {
                throw std::runtime_error("can't find one of the node");
            }
            auto itorator = node_[oldi]->getn();
            // merge all the outgoing edge
            while (itorator != nullptr) {
                if(!node_[newi]->containedge(*itorator)) {
                    node_[newi]->addnewedge(*itorator);
                }
                itorator = itorator->getn();
            }
            // merge all the incoming edge
            for (unsigned int i = 0; i < num_node() ; ++i) {
                if(i == oldi || i = newi) {
                    continue;
                }
                node_[newi]->merge(oldData, newData);

            }
            // delete old node
            node_.erase(node_.begin() + oldi);

        }
        catch (std::runtime_error &e) {
            std::cout<<"can't find one of the node";
        }

    };



#include "Graph.tmp"

}
