#include "Edge.h"

Edge::Edge(string origin, string dest, int capacity) {
    this->origin = std::move(origin);
    this->dest = std::move(dest);
    this->capacity = capacity;
}

string Edge::getOrigin() const {return origin;}
string Edge::getDest() const {return dest;}
int Edge::getCapacity() const {return capacity;}
int Edge::getFlow() const {return flow;}

void Edge::setFlow(int Flow) {flow = Flow;}
