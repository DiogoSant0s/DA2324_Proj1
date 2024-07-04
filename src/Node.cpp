#include "Node.h"

/*------ Base Node class ------*/
Node::Node(int id, string code) : Id(id), Code(std::move(code)) {}

int Node::getId() const {return Id;}
string Node::getCode() const {return Code;}

bool Node::getVisited() const {return visited;}
list<Edge*> Node::getEdges() const {return edges;}
Edge* Node::getPath() const {return path;}
int Node::getNumEdges() const {return (int) edges.size();}

void Node::setVisited(bool Visited) {visited = Visited;}
void Node::setPath(Edge *Path) {path = Path;}

void Node::addEdge(Edge *edge) {edges.push_back(edge);}
void Node::removeEdge(Edge *edge) {
    edges.remove(edge);
    delete edge;
}

/*------ City class ------*/
City::City(int id, string code, string city, float demand, int population) : Node(id, std::move(code)), CityName(std::move(city)), Demand(demand), Population(population) {}

int City::getId() const {return Node::getId();}
string City::getCode() const {return Node::getCode();}
string City::getCityName() const {return CityName;}
float City::getDemand() const {return Demand;}
int City::getPopulation() const {return Population;}

/*------ Reservoir class ------*/
Reservoir::Reservoir(int id, string code, string reservoir, string municipality, int maximumDelivery) : Node(id, std::move(code)), ReservoirName(std::move(reservoir)), Municipality(std::move(municipality)), MaximumDelivery(maximumDelivery) {}

int Reservoir::getId() const {return Node::getId();}
string Reservoir::getCode() const {return Node::getCode();}
string Reservoir::getReservoirName() const {return ReservoirName;}
string Reservoir::getMunicipality() const {return Municipality;}
int Reservoir::getMaximumDelivery() const {return MaximumDelivery;}

/*------ PumpingStation class ------*/
PumpingStation::PumpingStation(int id, string code) : Node(id, std::move(code)) {}

int PumpingStation::getId() const {return Node::getId();}
string PumpingStation::getCode() const {return Node::getCode();}
