#ifndef DA_RAILWAYS_GRAPH_H
#define DA_RAILWAYS_GRAPH_H

#include <unordered_map>
#include <queue>
#include <vector>
#include <algorithm>
#include <limits>
#include <memory>
#include <cmath>
#include "Node.h"

/**
 * @class Graph
 * @details This class represents the water supply network in Portugal as a graph.
 */
class Graph {
private:
    /**
     * @details A hash table.
     * @details When searching the Time Complexity is O(1).
     */
    unordered_map<string, Node*> nodes;
public:
    /**
     * @details Creates a new Graph.
     * @details Constructor of the Graph class.
     */
    Graph();

    /**
     * @details Add a node to the Graph using the node code as a key and the node's information as value.
     * @details Time Complexity - O(1).
     * @param nodeCode The code of the node
     * @param node All of the node's information
     */
    void addNode(const string& nodeCode, Node* node);
    /**
     * @details Add an edge from a source station to a target station
     * @details Time Complexity - O(1).
     * @param sourceStation The source station.
     * @param targetStation The target station.
     * @param capacity Waterway's segment capacity
     * @param direction Direction of the waterway, true if it is unidirectional, false if it is bidirectional
     */
    void addEdge(const string &sourceStation, const string &targetStation, int capacity, bool direction);
    /**
     * @details Remove a node from the Graph.
     * @details Time Complexity - O(|E|).
     * @details E is the number of edges/links.
     * @param code The code of the node to remove
     */
    void removeNode(const string& code);
    /**
     * @details Normal method that returns the object nodes
     * @details Time Complexity: O(1)
     * @return The object nodes
     */
    unordered_map<string, Node*> getNodes();
    /**
     * @details Normal method that returns the edges of the provided Node
     * @details Time Complexity: O(1)
     * @param code Code of the Node to get the edges from
     * @return The edges of the provided Node
     */
    list<Edge*> getEdges(const string& code);
    /**
     * @details Normal method that returns the incoming edges of the provided Node
     * @details Time Complexity: O(|V| * |E|)
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param code Code of the Node to get the incoming edges from
     * @return The incoming edges of the provided Node
     */
    list<Edge*> getIncomingEdges(const string& code);
     /**
     * @details Checks if a node with the provided code exists in the graph
     * @details Time Complexity - O(1).
     * @param code Node's code.
     * @return True - If the station exists.
     * @return False - If the station doesn't exist.
     */
    bool CheckIfNodeExists(const string& code);
    /**
     * @details This function sets all the nodes to unvisited state.
     * @details Time Complexity - O(V).
     * @details V is the number of nodes.
     */
    void setUnvisited() ;
    /**
     * @details Find the maximum flow through the network using Edmonds-Karp algorithm
     * @details Time Complexity: O(|V| * |E|^²)
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     */
    void edmondsKarp();
    /**
     * @details Find an augmenting path in the graph using BFS
     * @details Time Complexity: O(|V| + |E| * log(|V|))
     * @param src Source Node
     * @param dest Destination Node
     * @return True - If it is possible.
     * @return False - If it isn't possible.
     */
    bool findAugmentingPath(Node* src, Node* dest);
    /**
     * @details Visit a node and add it to the queue
     * @details Time Complexity: O(1)
     * @param queue Queue of Nodes
     * @param edge Edge
     * @param node Node
     * @param residual Residual capacity
     */
    static void testAndVisit(queue<Node*> &queue, Edge* edge, Node* node, double residual);
    /**
     * @details Find the minimum residual capacity along the augmenting path
     * @details Time Complexity: O(|V|)
     * @details V is the number of vertices/nodes
     * @param src Source Node
     * @param dest Destination Node
     * @return The minimum residual capacity
     */
    int findMinResidualAlongPath(Node* src, Node* dest);
    /**
     * @details Augment flow along the augmenting path with the given flow value
     * @details Time Complexity: O(|V|)
     * @details V is the number of vertices/nodes
     * @param src Source Node
     * @param dest Destination Node
     * @param f Flow value
     */
    void augmentFlowAlongPath(Node* src, Node* dest, int f);
    /**
     * @details Find the cities that have a water deficit
     * @details Time Complexity: O(|V| * |E|)
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param totalSupply Total water supply
     * @param totalDemand Total water demand
     * @return The list of cities that have a water deficit
     */
    list<pair<City*, float>> WaterDeficit(int &totalSupply, float &totalDemand);
    /**
     * @details Compute the metrics of the network flow
     * @details Time Complexity: O(|V| * |E| + |E|)
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param maxDifference The maximum difference between the capacity and the flow of all edges
     * @param averageDifference The average difference between the capacity and the flow of all edges
     * @param variance The variance of the difference between the capacity and the flow of all edges
     * @return The list of edges and their respective difference between the capacity and the flow
     */
    list<pair<Edge *, double>> ComputeMetrics(double &maxDifference, double &averageDifference, double &variance);
    /**
     * @details Redistribute the flow in the network
     * @details Time Complexity: O(|C| * |E|)
     * @details C is the number of cities and E is the number of edges/links.
     */
    void balanceLoad(list<pair<Edge *, double>> list);
    /**
     * @details Find the cities that were affected by the removal of the reservoir with the given code
     * @details Time Complexity: O(|V| * |E|)
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param code The code of the reservoir to remove
     * @return The list of cities that were affected by the reservoir removal, with the respective impact
     */
    list<pair<City*, double>> evaluateReservoirImpact(const string &code);
    /**
     * @details Find the cities that were affected by the removal of the pumping station with the given code
     * @details Time Complexity: O(|V| * |E|)
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param code The code of the pumping station to remove
     * @return The list of cities that were affected by the pumping station removal, with the respective impact
     */
    list<pair<City *, double>> evaluatePumpingStationImpact(const string &code);
    /**
     * @details Find the cities that were affected by the removal of a pipeline
     * @details Time Complexity: O(|V|^2 * |E|^2)
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @return A hash table with the pipelines and the cities that were affected by the pipeline removal, with the respective impact
     */
    unordered_map<Edge *, list<pair<City *, double>>> evaluatePipelineImpact();
};

#endif //DA_RAILWAYS_GRAPH_H
