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
        bool removeedge(const N &node);
        unsigned int size();
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
        N getnvalue();

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
        void deleteNode(const N&) noexcept;
        void deleteEdge(const N& src, const N& dst, const E& w) noexcept;
        void clear() noexcept;
        bool isNode(const N& val) const;
        bool isConnected(const N& src, const N& dst) const;
        void printNodes() const;
        void sort();
    };

#include "Graph.tmp"

}
