#ifndef DA2324_PROJ1_EDGE_H
#define DA2324_PROJ1_EDGE_H

#include <string>
#include <utility>

using namespace std;

/**
 * @class Edge
 * @details Represents the edges of the graph/network segments.
 */
class Edge {
private:
    /**
     * @brief Origin node's code
     */
    string origin;
    /**
     * @brief Destination node's code
     */
    string dest;
    /**
     * @brief Capacity of the edge
     */
    int capacity;
    /**
     * @brief Auxiliary property for flow-related problems
     */
    int flow{};
public:
    /**
     * @details Constructor of the Edge class
     * @param origin Origin node's code
     * @param dest Destination node's code
     * @param capacity Capacity of the edge
     */
    Edge(string origin, string dest, int capacity);
    /**
     * @details Normal method that returns the edge's origin
     * @details Time Complexity - O(1).
     * @return Origin node's code
     */
    string getOrigin() const;
    /**
     * @details Normal method that returns the edge's destination
     * @details Time Complexity - O(1).
     * @return Destination node's code
     */
    string getDest() const;
    /**
     * @details Normal method that returns the edge's capacity
     * @details Time Complexity - O(1).
     * @return Capacity of the edge
     */
    int getCapacity() const;
    /**
     * @details Normal method that returns the edge's flow
     * @details Time Complexity - O(1).
     * @return Flow of the edge
     */
    int getFlow() const;
    /**
     * @details Normal method that sets the edge's flow
     * @details Time Complexity - O(1).
     * @param Flow Flow of the edge
     */
    void setFlow(int Flow);
};

#endif //DA2324_PROJ1_EDGE_H
