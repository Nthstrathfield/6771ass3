#include <vector>
namespace gdwg{
    // Node template
    template <typename N, typename E> class Edge;

    template <typename N, typename E>
    class Node {
     private:
        std::vector<std::shared_ptr<Node<N, E>>> in_;
        std::vector<std::shared_ptr<Node<N, E>>> out_;
        std::vector<int> a;
        N value_;
     public:
        Node<N, E>bb

    };

    // Edge template
    template <typename N, typename E>
    class Edge {
     private:
        std::vector<std::shared_ptr<Node<N, E>>> src_;
        std::vector<std::shared_ptr<Node<N, E>>> dst_;
        E weight_;
     public:

    };

    // Graph template
    template <typename N, typename E> class Graph {

    private:
        std::vector<Node<N, E>> node_;
        std::vector<Edge<N, E>> edge_;
     public:
        // default constructor
        Graph<N, E>(): node_(),edge_() {
        };
        // copy constructor
        Graph<N, E>(Graph<N, E>) {};
        // move constructor



    };

}