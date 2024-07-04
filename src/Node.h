#ifndef DA_RAILWAYS_STATION_H
#define DA_RAILWAYS_STATION_H

#include <list>
#include <Edge.h>

/**
 * @class Node
 * @details This class keeps the data of each of the 3 different types of nodes
 */
class Node {
private:
    /**
     * @details Unique identifier of node, be it a City, Reservoir or Pumping Station
     */
    int Id;
    /**
     * @details Code of node, be it a CityName, ReservoirName or pumping station
     */
    string Code;
    /**
     * @details List of outgoing edges, to adjacent nodes.
     */
    list<Edge*> edges = {};
    /**
     * @details This variable set to True means that the node has been visited and False otherwise.
     */
    bool visited = false;
    /**
     * @details Path from src to this node
     */
    Edge* path = nullptr;
public:
    virtual ~Node() = default;
    /**
     * @details Constructor of the Node class
     * @param id Id of the node
     * @param code Code of the node
     */
    Node(int id, string code);
    /**
     * @details Virtual method that returns the Id of a node
     * @details Time Complexity: O(1)
     * @return The id of a node
     */
    virtual int getId() const;
    /**
     * @details Virtual method that returns the Code of a node
     * @details Time Complexity: O(1)
     * @return The code of a node
     */
    virtual string getCode() const;
    /**
     * @details Normal method that returns the list of edges of a node
     * @details Time Complexity: O(1)
     * @return The list of edges of a node
     */
    list<Edge*> getEdges() const;
    /**
     * @details Normal method that returns the visited attribute of a node
     * @details Time Complexity: O(1)
     * @return The visited attribute of a node
     */
    bool getVisited() const;
    /**
     * @details Normal method that returns the path of a node
     * @details Time Complexity: O(1)
     * @return The path of a node
     */
    Edge* getPath() const;
    /**
     * @details Normal method that sets the visited  of a node
     * @details Time Complexity: O(1)
     * @param Visited The visited attribute of a node
     */
    void setVisited(bool Visited);
    /**
     * @details Normal method that sets the path of a node
     * @details Time Complexity: O(1)
     * @param Path The path of a node
     */
    void setPath(Edge* Path);
    /**
     * @details Normal method that adds an edge to the list of edges of a node
     * @details Time Complexity: O(1)
     * @param edge The edge to be added
     */
    void addEdge(Edge* edge);
    /**
     * @details Normal method that removes an edge from the list of edges of a node and deletes it
     * @details Time Complexity: O(1)
     * @param edge The edge to be removed
     */
    void removeEdge(Edge* edge);
    /**
     * @details Normal method that returns the number of edges of a node
     * @details Time Complexity: O(1)
     * @return The number of edges of a node
     */
    int getNumEdges() const;
};

/**
 * @class City
 * @details This class represents the delivery sites in the water supply network
 */
class City : public Node {
private:
    /**
     * @details Name of the city/delivery site
     */
    string CityName;
    /**
     * @details Rate demand or need of delivery site in m3/sec
     */
    float Demand;
    /**
     * @details Total population of the delivery site
     */
    int Population;
public:
    /**
     * @details Constructor of the City class
     * @param id Id of the city
     * @param code Code of the city
     * @param city Name of the city
     * @param demand Water demand of the delivery site in m3/sec
     * @param population Total population of the delivery site
     */
    City(int id, string code, string city, float demand, int population);
    /**
     * @details Normal method that returns the Id of a city
     * @details Time Complexity: O(1)
     * @return The id of a city
     */
    int getId() const override;
    /**
     * @details Normal method that returns the Code of a city
     * @details Time Complexity: O(1)
     * @return The code of a city
     */
    string getCode() const override;
    /**
     * @details Normal method that returns the name of the city
     * @details Time Complexity: O(1)
     * @return The name of the city
     */
    string getCityName() const;
    /**
     * @details Normal method that returns the demand of the city
     * @details Time Complexity: O(1)
     * @return The water demand of the city
     */
    float getDemand() const;
    /**
     * @details Normal method that returns the population of the city
     * @details Time Complexity: O(1)
     * @return The population of the city
     */
    int getPopulation() const;
};

/**
 * @class Reservoir
 * @details This class represents the water sources in the water supply network
 */
class Reservoir : public Node {
private:
    /**
     * @details Name of the reservoir
     */
    string ReservoirName;
    /**
     * @details Name of the municipality where the reservoir is located
     */
    string Municipality;
    /**
     * @details Maximum delivery of the reservoir in m3/sec
     */
    int MaximumDelivery;
public:
    /**
     * @details Constructor of the Reservoir class
     * @param id Id of the reservoir
     * @param code Code of the reservoir
     * @param reservoir Name of the reservoir
     * @param municipality Name of the municipality where the reservoir is located
     * @param maximumDelivery Maximum delivery of the reservoir in m3/sec
     */
    Reservoir(int id, string code, string reservoir, string municipality, int maximumDelivery);
    /**
     * @details Normal method that returns the Id of a reservoir
     * @details Time Complexity: O(1)
     * @return The id of a reservoir
     */
    int getId() const override;
    /**
     * @details Normal method that returns the Code of a reservoir
     * @details Time Complexity: O(1)
     * @return The code of a reservoir
     */
    string getCode() const override;
    /**
     * @details Normal method that returns the name of the reservoir
     * @details Time Complexity: O(1)
     * @return The name of the reservoir
     */
    string getReservoirName() const;
    /**
     * @details Normal method that returns the municipality of the reservoir
     * @details Time Complexity: O(1)
     * @return The municipality of the reservoir
     */
    string getMunicipality() const;
    /**
     * @details Normal method that returns the maximum delivery of the reservoir
     * @details Time Complexity: O(1)
     * @return The maximum delivery of the reservoir
     */
    int getMaximumDelivery() const;
};

/**
 * @class PumpingStation
 * @details This class represents the pumping stations in the water supply network
 */
class PumpingStation : public Node {
public:
    /**
     * @details Constructor of the PumpingStation class
     * @param id Id of the pumping station
     * @param code Code of the pumping station
     */
    PumpingStation(int id, string code);
    /**
     * @details Normal method that returns the Id of a pumping station
     * @details Time Complexity: O(1)
     * @return The id of a pumping station
     */
    int getId() const override;
    /**
     * @details Normal method that returns the Code of a pumping station
     * @details Time Complexity: O(1)
     * @return The code of a pumping station
     */
    string getCode() const override;
};

#endif //DA_RAILWAYS_STATION_H
