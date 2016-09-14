#include <vector>
#include <memory>
#include <stdexcept>
// Using Adjacency List to represent graph
// copy node first, then edge

namespace gdwg {

    /******************** Node ***************************/
    template<typename N, typename E>
    class Node {
    private:
        N value_;
        E weight_;
        std::shared_ptr<Node<N, E>> next_;
    public:
        // edge constructor
        Node(const N &value, const E weight) : value_{value}, weight_{weight}, next_{nullptr} {};
        // node constructor
        Node(const N &value) : value_{value}, weight_{0}, next_{nullptr} {};
        // copy constructor
        Node(const Node<N, E> &cpy);

        // MEMBER FUNCTION
//        void setn(std::shared_ptr<Node<N, E>> new_edge);
//
//        void printnode();
//
        N getv();
        std::shared_ptr<Node<N, E>> getn();
//
//        bool containedge(const Edge <N, E> &edge);
//
//        void addnewedge(const Edge <N, E> &edge);
//
//        void merge(const N &, const N &);
//
//        void removeedge(const N &node, const E &weight);
//
//        bool removeedge(const N &node);
//
        unsigned int size();
    };


    /*********************** Graph ***************************/
    template<typename N, typename E>
    class Graph {
    private:
        // save node pointer node->egde1(node index|edge value)->edge2(node index|edge value)
        std::vector<std::shared_ptr<Node<N, E>>> node_;
    public:
        // default constructor
        Graph() {};
        // copy constructor
        Graph(const Graph<N, E> &cpy);
        // move constructor
        Graph(Graph<N, E> &&cpy);

        // MEMBER FUNCTION
        int num_node();
        bool addNode(const N &val);
        bool addEdge(const N &src, const N &dst, const E &w);
        bool replace(const N &oldData, const N &newData);
        void mergeReplace(const N &oldData, const N &newData);
        void deleteNode(const N &) noexcept;
        void deleteEdge(const N &src, const N &dst, const E &w) noexcept;
        void clear() noexcept;
        bool isNode(const N &val) const;
        bool isConnected(const N &src, const N &dst) const;
        void printNodes() const;
        void sort();
    };



/*********************************************************************/
/************************** Node ***************************************/
/*********************************************************************/

    // copy constructor
    template<typename N, typename E>
    Node<N, E>::Node(const Node &cpy) {
        if (cpy.next_ != nullptr) {
            weight_ = cpy.weight_;
            value_ = cpy.value_;
            next_ = nullptr;
            return;
        }
        Node<N, E> next(*(cpy.next_));
        weight_ = cpy.weight_;
        value_ = cpy.value_;
        next_ = std::make_shared(next);
    };

    // MEMBER FUNCTION
    // return node size
    template<typename N, typename E>
    unsigned int Node<N, E>::size() {
        auto itroator = next_;
        unsigned int i = 0;
        while (itroator != nullptr) {
            ++i;
            itroator = itroator->getn();
        }
        return i;
    }

    // return next_
    template<typename N, typename E>
    std::shared_ptr<Node<N, E>> Node<N, E>::getn() {
        return next_;
    };

    // return value_
    template<typename N, typename E>
    N Node<N, E>::getv() {
        return value_;
    };

//// set new next
//    template<typename N, typename E>
//    void Node<N, E>::setn(std::shared_ptr<Edge < N, E>>
//
//    new_edge) {
//    if (next_ == nullptr) {
//    next_ = new_edge;
//}
//else {
//std::shared_ptr<Edge < N, E>>
//itorator = next_;
//while (itorator->
//
//getn()
//
//!= nullptr) {
//itorator = itorator->getn();
//}
//itorator->
//setn(new_edge);
//}
//};
//

//// print value of node and its out edge;
//template<typename N, typename E>
//void Node<N, E>::printnode() {
//    std::shared_ptr<Edge < N, E>>
//    itorator;
//    if (next_ != nullptr) {
//        itorator = next_;
//    } else {
//        std::cout << "(null)\n";
//        return;
//    }
//    while (itorator != nullptr) {
//        std::cout << itorator->getnvalue() << "\n";
//        std::cout << itorator->getw() << "\n";
//        itorator = itorator->getn();
//    }
//};
//

///*************************************************************************/
///************************** Graph ***************************************/
///***********************************************************************/
    // add new node
    template<typename N, typename E>
    bool Graph<N, E>::addNode(const N &val) {
        if(isNode(val)) {
            return false;
        }
        auto insert = std::make_shared<Node<N, E>>(val);
        node_.push_back(insert);
        sort();
        return true;
    }

    // sort node
    template<typename N, typename E>
    void Graph<N, E>::sort() {
        unsigned int i, j;
        for (i = 0; i <= num_node() - 1; ++i) {
            for (j = 0; j < num_node() - 1 - i; ++j) {
                if (node_[j]->size() > node_[j + 1]->size()) {
                    auto tmp = node_[j];
                    node_[j] = node_[j + 1];
                    node_[j + 1] = tmp;
                }
                if (node_[j]->size() == node_[j + 1]->size()) {
                    if (node_[j]->getv() > node_[j + 1]->getv()) {
                        auto tmp = node_[j];
                        node_[j] = node_[j + 1];
                        node_[j + 1] = tmp;
                    }
                }
            }
        }
    }

    // return numer of node
    template<typename N, typename E>
    int Graph<N, E>::num_node() {
        return node_.size();
    }

    // print nodes
    template<typename N, typename E>
    void Graph<N, E>::printNodes() const {
        for (unsigned int i = 0; i < node_.size(); ++i) {
            std::cout << node_[i]->getv() << "\n";
        }
    }

    // if exists node
    template<typename N, typename E>
    bool Graph<N, E>::isNode(const N &val) const {
        for (unsigned int i = 0; i < node_.size(); ++i) {
            if (node_[i]->getv() == val) {
                return true;
            }
        }
        return false;
    }

    // check exists edge
    template<typename N, typename E>
    bool Graph<N, E>::isConnected(const N &src, const N &dst) const {
        try {
            if(!isNode(src) || !isNode(dst)) {
                throw std::runtime_error("can't find node");
            }
            else
            {
                for (unsigned int i = 0; i < node_.size(); ++i) {
                    if (node_[i]->getv == src) {
                        auto itorator = node_[i]->getn();
                        while (itorator != nullptr) {
                            if (itorator->getv() == dst) {
                                return true;
                            }
                            itorator = itorator->getn();
                        }
                    }
                }
                return false;
            }
        }
        catch (std::runtime_error &e) {
            std::cout<<"can't find node";
        }
    }

    //// add new edge
    template<typename N, typename E>
    bool Graph<N, E>::addEdge(const N &src, const N &dst, const E &w) {
        try {
            if (!isNode(src) || !isNode(dst)) {
                throw std::runtime_error("can't find node");
            }
        }
        catch (std::runtime_error & e)
        {
            std::cout << "can't find node";
        }

    }
//        int srci = -1;
//        int dsti = -1;
//        try {
//            for (unsigned i = 0; i < num_node(); ++i) {
//                if (node_[i]->getv() == src) {
//                    srci = i;
//                }
//                if (node_[i]->getv() == dst) {
//                    dsti = i;
//                }
//            }
//            if (srci == -1 || dsti == -1) {
//                throw std::runtime_error("can't find node");
//            }
//        }
//        catch (std::runtime_error &e) {
//            std::cout << "oh no";
//        }
//        auto itorator = node_[srci]->getn();
//        while (itorator != nullptr) {
//            if ((*itorator).getw() == w && (*itorator).getnvalue() == dsti) {
//                return false;
//            }
//            if (itorator->getn() != nullptr) {
//                itorator = itorator->getn();
//            } else {
//                break;
//            }
//        }
//        auto new_edge = std::make_shared<Edge < N, E>>
//        (dst, w);
//        if (itorator == nullptr) {
//            node_[srci]->setn(new_edge);
//        } else {
//            itorator->setn(new_edge);
//        }
//        sort();


//// graph deep copy constructor;
//template<typename N, typename E>
//Graph<N, E>::Graph(const Graph <N, E> &cpy) {
//    for (unsigned int i = 0; i < cpy.node_.size(); i++) {
//        Node <N, E> new_node(*cpy.node_[i]);
//        node_.pop_back(std::make_shared<Node < N, E>>
//        (new_node));
//    }
//}
//
//// move constructor
//template<typename N, typename E>
//Graph<N, E>::Graph(Graph <N, E> &&cpy) {
//    for (unsigned int i = 0; i < cpy.node_.size(); i++) {
//        node_.pop_back(cpy.node_[i]);
//        cpy.node_[i] = nullptr;
//    }
//}

//// clear vector
//template<typename N, typename E>
//void Graph<N, E>::clear() noexcept {
//    node_.clear();
//}
//
//// Graph delete Edge
//template<typename N, typename E>
//void Graph<N, E>::deleteEdge(const N &src, const N &dst, const E &w) noexcept {
//    for (unsigned int i = 0; i < num_node(); ++i) {
//        if (node_[i]->getv == src) {
//            node_[i]->removeedge(dst, w);
//            sort();
//            return;
//        }
//    }
//}
//
//
//// Graph delete node
//template<typename N, typename E>
//void Graph<N, E>::deleteNode(const N &dnode) noexcept {
//    // remove outgoing edge
//    for (unsigned int i = 0; i < num_node(); ++i) {
//        if (node_[i]->getv == dnode) {
//            node_.erase(node_.begin() + i);
//            break;
//        }
//    }
//    // remove incoming edge
//    for (unsigned int i = 0; i < num_node(); ++i) {
//        int flag = 1;
//        while (flag == 1) {
//            if (node_[i]->removeedge(dnode) == 0) {
//                flag = 0;
//            }
//        }
//    }
//}
//
//// remove edge base value
//template<typename N, typename E>
//void Node<N, E>::removeedge(const N &node, const E &weight) {
//    auto itorator = next_;
//    auto pre = next_;
//    if (itorator == nullptr) {
//        return;
//    }
//    if (itorator->getn() == nullptr) {
//        if (itorator->getnvlue() = node && itorator->getw() = weight) {
//            delete itorator;
//            itorator = nullptr;
//            next_ = nullptr;
//        }
//        return;
//    }
//    itorator = itorator->getn();
//    while (itorator->getn() != nullptr) {
//        if (itorator->getnvlue() = node && itorator->getw() = weight) {
//            pre->setn(itorator);
//            delete itorator;
//            itorator = nullptr;
//            return;
//        }
//        pre = itorator;
//        itorator = itorator->getn();
//    }
//    if (itorator->getnvlue() = node && itorator->getw() = weight) {
//        pre->setn(itorator);
//        delete itorator;
//        itorator = nullptr;
//    }
//    return;
//}
//
//// remove edge
//template<typename N, typename E>
//bool Node<N, E>::removeedge(const N &node) {
//    auto itorator = next_;
//    auto pre = next_;
//    if (itorator == nullptr) {
//        return false;
//    }
//    if (itorator->getn() == nullptr) {
//        if (itorator->getnvlue() = node) {
//            delete itorator;
//            itorator = nullptr;
//            next_ = nullptr;
//            return true;
//        }
//        return false;
//    }
//    itorator = itorator->getn();
//    while (itorator->getn() != nullptr) {
//        if (itorator->getnvlue() = node) {
//            pre->setn(itorator);
//            delete itorator;
//            itorator = nullptr;
//            return true;
//        }
//        pre = itorator;
//        itorator = itorator->getn();
//    }
//    if (itorator->getnvlue() = node) {
//        pre->setn(itorator);
//        delete itorator;
//        itorator = nullptr;
//        return true;
//    }
//    return false;
//}
//
////  merge same
//template<typename N, typename E>
//void Node<N, E>::merge(const N &old_edge, const N &new_edge) {
//    auto itorator = next_;
//    std::vector<E> memory;
//    while (itorator != nullptr) {
//        if (itorator->getnvlue() == old_edge || itorator->getnvlue() == new_edge) {
//            itorator->setnvalue(new_edge);
//            int flag = 0;
//            for (unsigned int i = 0; i < memory.size(); ++i) {
//                if (memory[i] == itorator->getw()) {
//                    flag = 1;
//                    break;
//                }
//            }
//            if (flag == 1) {
//                auto tmp = itorator;
//                itorator = itorator->getn();
//                removeedge(tmp->getnvlue(), tmp->getw());
//            } else {
//                memory.push_back(itorator->getw());
//                itorator = itorator->getn();
//            }
//        }
//    }
//}
//
//// set nvalue
//template<typename N, typename E>
//void Edge<N, E>::setnvalue(N nvalue) {
//    nvalue_ = nvalue;
//
//}
//
//// node add new edge
//template<typename N, typename E>
//void Node<N, E>::addnewedge(const Edge <N, E> &edge) {
//    auto itorator = next_;
//    while (itorator != nullptr) {
//        if (itorator->getn() != nullptr) {
//            itorator = itorator->getn();
//        } else {
//            break;
//        }
//    }
//    itorator->setn(std::make_shared<Edge < N, E>>
//    (edge.getnvlue(), edge.getw()));
//
//}
//
//// friend operator
//template<typename N, typename E>
//bool operator==(const Edge <N, E> &lft, const Edge <N, E> &rht) {
//
//    return lft.nvalue_ == rht.nvalue_ && lft.weight_ == rht.weight_;
//}
//
//
//// replace node value
//template<typename N, typename E>
//bool Graph<N, E>::replace(const N &oldData, const N &newData) {
//    int oldi = -1;
//    int newi = -1;
//    for (unsigned int i = 0; i < num_node(); ++i) {
//        if (node_[i]->getv() == oldData) {
//            oldi = i;
//        }
//        if (node_[i]->getv() == newData) {
//            newi = i;
//        }
//    }
//    try {
//        if (oldi == -1) {
//            throw std::runtime_error("can't find src node");
//        }
//        if (newi != -1) {
//            return false;
//        }
//        node_[oldi]->setn(std::make_shared<Edge < N, E>>
//        (newData));
//        sort();
//        return true;
//    }
//    catch (std::runtime_error &e) {
//        std::cout << "can't find src node";
//    }
//};
//
//// Check if node contains same edge
//template<typename N, typename E>
//bool Node<N, E>::containedge(const Edge <N, E> &edge) {
//    auto itorator = next_;
//    while (itorator != nullptr) {
//        if (*itorator == edge) {
//            return true;
//        }
//        itorator = itorator->getn();
//    }
//    return false;
//}
//
//
//// replace and merge node value
//template<typename N, typename E>
//void Graph<N, E>::mergeReplace(const N &oldData, const N &newData) {
//    int oldi = -1;
//    int newi = -1;
//    for (unsigned int i = 0; i < num_node(); ++i) {
//        if (node_[i]->getv() == oldData) {
//            oldi = i;
//        }
//        if (node_[i]->getv() == newData) {
//            newi = i;
//        }
//    }
//    try {
//        if (oldi == -1 || newi == -1) {
//            throw std::runtime_error("can't find one of the node");
//        }
//        auto itorator = node_[oldi]->getn();
//        // merge all the outgoing edge
//        while (itorator != nullptr) {
//            if (!node_[newi]->containedge(*itorator)) {
//                node_[newi]->addnewedge(*itorator);
//            }
//            itorator = itorator->getn();
//        }
//        // merge all the incoming edge
//        for (unsigned int i = 0; i < num_node(); ++i) {
//            if (i == oldi || i = newi) {
//                continue;
//            }
//            node_[newi]->merge(oldData, newData);
//        }
//        // delete old node
//        node_.erase(node_.begin() + oldi);
//        sort();
//    }
//    catch (std::runtime_error &e) {
//        std::cout << "can't find one of the node
//    }
//}
}
