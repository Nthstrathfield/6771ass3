#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>
// Using Adjacency List to represent graph
// copy node first, then edge

namespace gdwg {


    // Node, Edge
    template<typename N, typename E>
    class Node {
    private:
        N value_;
        E weight_;
        std::shared_ptr<Node<N, E>> next_;
    public:
         // constructor
         Node(const N &value, const E weight) : value_{value}, weight_{weight}, next_{nullptr} {};
         Node(const N &value) : value_{value}, weight_{0}, next_{nullptr} {};
        // member function
        void setn(std::shared_ptr<Node<N, E>> new_edge);
        void setv(const N &value);
        void printnode();
        N &getv();
        std::shared_ptr<Node<N, E>> getn();
        void addeg(const N &, const E &);
        E getw();
        void merge(const N &, const N &);
        void removeedge(const N &node, const E &weight);
        bool removeedge(const N &node);
        unsigned int size();
        std::shared_ptr<Node<N, E>> findedge(const N &) const;
        std::shared_ptr<Node<N, E>> findedge(const N &, const E &) const;
    };


    // Graph
    template<typename N, typename E>
    class Graph {
    private:
        std::vector<std::shared_ptr<Node<N, E>>> node_;
        mutable typename std::vector<std::shared_ptr<Node<N, E>>>::const_iterator iterator_;
        
        // private member function
        int num_node() const;
        bool isSameEdge(const N &, const N &, const E &) const;
        void sort();
        std::shared_ptr<Node<N, E>> findnode(const N &) const;
        unsigned int findindex(const N &) const;
    public:
        /******************************************************/
        /************* Constructor ****************************/
        /******************************************************/
        Graph() {};

        // copy constructor
        Graph(const Graph<N, E> &);

        // move constructor
        Graph(Graph<N, E> &&) noexcept;

        // copy assignement
        Graph & operator = (const Graph<N,E> &);

        // move assignement
        Graph & operator = (Graph<N, E> &&) noexcept;

        /*****************************************************/
        /*************** Member function *********************/
        /*****************************************************/
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

    #include "Graph.tem"
}


