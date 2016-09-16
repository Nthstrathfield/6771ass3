#include <vector>
#include <memory>
#include <stdexcept>
// Using Adjacency List to represent graph
// copy node first, then edge

namespace gdwg {


    /******************** Node/Edge***************************/
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
        void setn(std::shared_ptr<Node<N, E>> new_edge);
        void setv(const N &value);
        void printnode();
        N getv();
        std::shared_ptr<Node<N, E>> getn();
//        bool containedge(const Edge <N, E> &edge);
        void addeg(const N &, const E &);
        E getw();
        void merge(const N &, const N &);
        void removeedge(const N &node, const E &weight);
        bool removeedge(const N &node);
        unsigned int size();
        std::shared_ptr<Node<N, E>> findedge(const N &) const;
        std::shared_ptr<Node<N, E>> findedge(const N &, const E &) const;
    };


    /*********************** Graph ***************************/
    template<typename N, typename E>
    class Graph {
    private:
        //
        // save node pointer node->egde1(node index|edge value)->edge2(node index|edge value)
        //
        std::vector<std::shared_ptr<Node<N, E>>> node_;
        mutable typename std::vector<std::shared_ptr<Node<N, E>>>::const_iterator iterator_;
        mutable int position;
        int num_node() const;
        bool isSameEdge(const N &src, const N &dst, const E &wei) const;
        void sort();
        std::shared_ptr<Node<N, E>> findnode(const N &val) const;
        unsigned int findindex(const N &val) const;

    public:
        // default constructor
        Graph() {};
        // copy constructor
        Graph(const Graph<N, E> &cpy);
        // move constructor
        Graph(Graph<N, E> &&cpy);
        // MEMBER FUNCTION
//        int num_node() const;
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
        void printEdges(const N &val) const;
        void begin() const;
        bool end() const;
        void next() const;
        const N &value() const;
    };

    /****************************************************************************/
    /************************** Node/Edge ***************************************/
    /***************************************************************************/

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

    template<typename N, typename E>
    void Node<N, E>::setn(std::shared_ptr<Node<N, E>> new_edge) {
        next_ = new_edge;
    }

    template<typename N, typename E>
    void Node<N, E>::setv(const N &value) {
        value_ = value;
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

    template<typename N, typename E>
    E Node<N, E>::getw() {
        return weight_;
    }

    // find edge 1. connected 2.same edge with same weight
    template<typename N, typename E>
    std::shared_ptr<Node<N, E>> Node<N, E>::findedge(const N &val) const {
        auto itroator = next_;
        while (itroator != nullptr) {
            if (itroator->value_ == val) {
                return itroator;
            }
            itroator = itroator->next_;
        }
        return nullptr;
    }

    template<typename N, typename E>
    std::shared_ptr<Node<N, E>> Node<N, E>::findedge(const N &val, const E &wei) const {
        auto itroator = next_;
        while (itroator != nullptr) {
            if (itroator->value_ == val && itroator->weight_ == wei) {
                return itroator;
            }
            itroator = itroator->next_;
        }
        return nullptr;
    };


    // add edge: insert in sequence, like priority queue
    template<typename N, typename E>
    void Node<N, E>::addeg(const N &val, const E &wei) {
        auto itorator = next_;
        auto pre_itorator = next_;
        // if list is empty
        if (itorator == nullptr) {
            next_ = std::make_shared<Node<N, E>>(val, wei);
            return;
        } else if (itorator->next_ == nullptr) {
            if (wei > itorator->weight_) {
                itorator->next_ = std::make_shared<Node<N, E>>(val, wei);
            } else if (wei == itorator->weight_) {
                if (val > itorator->value_) {
                    itorator->next_ = std::make_shared<Node<N, E>>(val, wei);
                } else {
                    next_ = std::make_shared<Node<N, E>>(val, wei);
                    next_->next_ = itorator;
                }
            } else {
                next_ = std::make_shared<Node<N, E>>(val, wei);
                next_->next_ = itorator;
            }
        } else {
            // for first node
            if (wei > itorator->weight_) {
                itorator = itorator->next_;
            } else if (wei == itorator->weight_) {
                if (val > itorator->value_) {
                    itorator = itorator->next_;
                } else {
                    next_ = std::make_shared<Node<N, E>>(val, wei);
                    next_->next_ = pre_itorator;
                    return;
                }
            } else {
                next_ = std::make_shared<Node<N, E>>(val, wei);
                next_->next_ = pre_itorator;
                return;
            }
            // for n node
            while (itorator->next_ != nullptr) {

                if (wei > itorator->weight_) {
                    pre_itorator = itorator;
                    itorator = itorator->next_;
                } else if (wei == itorator->weight_) {
                    if (val > itorator->value_) {
                        pre_itorator = itorator;
                        itorator = itorator->next_;
                    } else {
                        pre_itorator->next_ = std::make_shared<Node<N, E>>(val, wei);
                        pre_itorator->next_->next_ = itorator;
                        return;
                    }
                } else {
                    pre_itorator->next_ = std::make_shared<Node<N, E>>(val, wei);
                    pre_itorator->next_->next_ = itorator;
                    return;
                }
            }
            // for last node
            if (wei > itorator->weight_) {
                itorator->next_ = std::make_shared<Node<N, E>>(val, wei);
                return;
            } else if (wei == itorator->weight_) {
                if (val > itorator->value_) {
                    itorator->next_ = std::make_shared<Node<N, E>>(val, wei);
                    return;
                } else {
                    pre_itorator->next_ = std::make_shared<Node<N, E>>(val, wei);
                    pre_itorator->next_->next_ = itorator;
                    return;
                }
            } else {
                pre_itorator->next_ = std::make_shared<Node<N, E>>(val, wei);
                pre_itorator->next_->next_ = itorator;
                return;
            }
        }
    }

    // remove edge base value
    template<typename N, typename E>
    void Node<N, E>::removeedge(const N &node, const E &weight) {
        auto itorator = next_;
        auto pre = next_;
        if (itorator == nullptr) {
            return;
        }
        if (itorator->getn() == nullptr) {
            if (itorator->getv() == node && itorator->getw() == weight) {
                itorator = nullptr;
                next_ = nullptr;
            }
            return;
        }
        itorator = itorator->getn();
        while (itorator->getn() != nullptr) {
            if (itorator->getv() == node && itorator->getw() == weight) {
                pre->setn(itorator);

                itorator = nullptr;
                return;
            }
            pre = itorator;
            itorator = itorator->getn();
        }
        if (itorator->getv() == node && itorator->getw() == weight) {
            pre->setn(itorator);

            itorator = nullptr;
        }
        return;
    }

//
    // remove edge
    template<typename N, typename E>
    bool Node<N, E>::removeedge(const N &node) {
        auto itorator = next_;
        auto pre = next_;
        if (itorator == nullptr) {
            return false;
        }
        if (itorator->getn() == nullptr) {
            if (itorator->getnvlue() = node) {
                delete itorator;
                itorator = nullptr;
                next_ = nullptr;
                return true;
            }
            return false;
        }
        itorator = itorator->getn();
        while (itorator->getn() != nullptr) {
            if (itorator->getnvlue() = node) {
                pre->setn(itorator);
                delete itorator;
                itorator = nullptr;
                return true;
            }
            pre = itorator;
            itorator = itorator->getn();
        }
        if (itorator->getnvlue() = node) {
            pre->setn(itorator);
            delete itorator;
            itorator = nullptr;
            return true;
        }
        return false;
    }

    // print value of node and its out edge;
    template<typename N, typename E>
    void Node<N, E>::printnode() {
        std::shared_ptr<Node<N, E>> itorator;
        if (next_ != nullptr) {
            itorator = next_;
        } else {
            std::cout << "(null)\n";
            return;
        }
        while (itorator != nullptr) {
            std::cout << itorator->getv() << " ";
            std::cout << itorator->getw() << "\n";
            itorator = itorator->getn();
        }
    };
//

    /*************************************************************************/
    /************************** Graph ***************************************/
    /***********************************************************************/
    template<typename N, typename E>
    void Graph<N, E>::begin() const {
        iterator_ = node_.cbegin();
        position = 0;

    }

    template<typename N, typename E>
    bool Graph<N, E>::end() const {
        return iterator_ == node_.cend();

    }

    template<typename N, typename E>
    void Graph<N, E>::next() const {
        iterator_++;
        position++;
    }

    template<typename N, typename E>
    const N &Graph<N, E>::value() const {
        return node_[position]->getv();
    }


    // add new node
    template<typename N, typename E>
    bool Graph<N, E>::addNode(const N &val) {
        if (isNode(val)) {
            return false;
        }
        auto insert = std::make_shared<Node<N, E>>(val);
        node_.push_back(insert);
        sort();
        return true;
    }

    template<typename N, typename E>
    unsigned int Graph<N, E>::findindex(const N &val) const {
        unsigned int i = 0;
        for (unsigned int j = 0; j < node_.size(); ++j) {
            if (node_[j]->getv() == val) {
                return j;
            }
        }
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
    int Graph<N, E>::num_node() const {
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
        if (findnode(val) == nullptr) {
            return false;
        }
        return true;
    }

    // check exists edge
    template<typename N, typename E>
    bool Graph<N, E>::isConnected(const N &src, const N &dst) const {
        if (!isNode(src) || !isNode(dst)) {
            throw std::runtime_error("can't find node");
        } else {
            auto src_node = findnode(src);
            if (src_node->findedge(dst) == nullptr) {
                return false;
            } else {
                return true;
            }

        }
    }

    // check if there is a same edge with same weight in the graph
    template<typename N, typename E>
    bool Graph<N, E>::isSameEdge(const N &src, const N &dst, const E &wei) const {
        if (!isNode(src) || !isNode(dst)) {
            throw std::runtime_error("can't find node");
        } else {
            auto src_node = findnode(src);
            if (src_node->findedge(dst, wei) == nullptr) {
                return false;
            } else {
                return true;
            }
        }
    }

    // add new edge
    template<typename N, typename E>
    bool Graph<N, E>::addEdge(const N &src, const N &dst, const E &w) {
        if (!isNode(src) || !isNode(dst)) {
            throw std::runtime_error("can't find node");
        }
        if (isSameEdge(src, dst, w)) {
            return false;
        }
        for (unsigned int i = 0; i < node_.size(); ++i) {
            if (node_[i]->getv() == src) {
                node_[i]->addeg(dst, w);
                break;
            }
        }
        sort();
    }

    // replace egde
    template<typename N, typename E>
    bool Graph<N, E>::replace(const N &oldData, const N &newData) {
//        try {
        if (!isNode(oldData)) {
            throw std::runtime_error("can't find node");
        }
        if (isNode(newData)) {
            return false;
        } else {
            auto node = findnode(oldData);
            node->setv(newData);
            sort();
        }

    }

    // find node vie value
    template<typename N, typename E>
    std::shared_ptr<Node<N, E>> Graph<N, E>::findnode(const N &val) const {
        for (unsigned int i = 0; i < num_node(); ++i) {
            if (node_[i]->getv() == val) {
                return node_[i];
            }
        }
        return nullptr;
    }



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

    // clear vector
    template<typename N, typename E>
    void Graph<N, E>::clear() noexcept {
        node_.clear();
    }

    // Graph delete Edge
    template<typename N, typename E>
    void Graph<N, E>::deleteEdge(const N &src, const N &dst, const E &w) noexcept {
        for (unsigned int i = 0; i < num_node(); ++i) {
            if (node_[i]->getv() == src) {
                node_[i]->removeedge(dst, w);
                sort();
                return;
            }
        }
    }

    // Graph delete node
    template<typename N, typename E>
    void Graph<N, E>::deleteNode(const N &dnode) noexcept {
        // remove outgoing edge
        for (unsigned int i = 0; i < num_node(); ++i) {
            if (node_[i]->getv == dnode) {
                node_.erase(node_.begin() + i);
                break;
            }
        }
        // remove incoming edge
        for (unsigned int i = 0; i < num_node(); ++i) {
            int flag = 1;
            while (flag == 1) {
                if (node_[i]->removeedge(dnode) == 0) {
                    flag = 0;
                }
            }
        }
    }

    //  merge same
    template<typename N, typename E>
    void Node<N, E>::merge(const N &old_edge, const N &new_edge) {
        auto itorator = next_;
        // save weight
        std::vector<E> memory;
        while (itorator != nullptr) {
            int flag = 0;
            if (itorator->getv() == old_edge || itorator->getv() == new_edge) {
                itorator->setv(new_edge);
                for (unsigned int i = 0; i < memory.size(); ++i) {
                    if (memory[i] == itorator->getw()) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 1) {
                    auto tmp = itorator;
                    itorator = itorator->getn();
                    removeedge(tmp->getv(), tmp->getw());
                    continue;
                } else {
                    memory.push_back(itorator->getw());
                    itorator = itorator->getn();
                    continue;
                }
            }
            itorator = itorator->getn();
        }
    }

    template<typename N, typename E>
    void Graph<N, E>::mergeReplace(const N &oldData, const N &newData) {
        if (!isNode(oldData) || !isNode(newData)) {
            throw std::runtime_error("can't find one of the node");
        }
        // merge all the outgoing edge
        auto itorator = findnode(oldData);
        auto itorator_new = findnode(newData);
        itorator = itorator->getn();
        while (itorator != nullptr) {
            if (itorator_new->findedge(itorator->getv(), itorator->getw()) == nullptr) {
                itorator_new->addeg(itorator->getv(), itorator->getw());
            }
            itorator = itorator->getn();
        }
        // merge all the incoming edge
        for (unsigned int i = 0; i < num_node(); ++i) {
            node_[i]->merge(oldData, newData);
        }
        // delete old node
        node_.erase(node_.begin() + findindex(oldData));
        sort();

    }
    template<typename N, typename E>
    void Graph<N, E>::printEdges(const N &val) const {
        auto node = findnode(val);
        if (node != nullptr) {
            std::cout << "Edges attached to Node " << node->getv() << "\n";
            node->printnode();

        }

    }
}


// move constructor delete pointer or leave it


