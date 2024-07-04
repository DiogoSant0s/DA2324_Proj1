#include "Graph.h"

Graph::Graph() = default;

void Graph::addNode(const string& nodeCode, Node* node) {
    if (nodes.find(nodeCode) == nodes.end()) {
        nodes[nodeCode] = node;
    }
}

void Graph::addEdge(const string &sourceStation, const string &targetStation, int capacity, bool direction) {
    auto itSrc = nodes.find(sourceStation);
    auto itTar = nodes.find(targetStation);
    if (itSrc == nodes.end() || itTar == nodes.end() || itSrc == itTar) {
        return;
    }
    if (direction) {
        itSrc->second->addEdge(new Edge{sourceStation, targetStation, capacity});
    } else {
        itSrc->second->addEdge(new Edge{sourceStation, targetStation, capacity});
        itTar->second->addEdge(new Edge{targetStation, sourceStation, capacity});
    }
}

void Graph::removeNode(const string& code) {
    for (auto e : nodes[code]->getEdges()) {
        nodes[code]->removeEdge(e);
    }
    for (auto e : getIncomingEdges(code)) {
        nodes[e->getOrigin()]->removeEdge(e);
    }
    delete nodes[code];
    nodes.erase(code);
}

void Graph::setUnvisited() {
    for (const auto& it : nodes) {
        it.second->setVisited(false);
    }
}

unordered_map<string, Node*> Graph::getNodes() {
    return nodes;
}

list<Edge*> Graph::getEdges(const string& code) {
    return nodes.find(code)->second->getEdges();
}

list<Edge*> Graph::getIncomingEdges(const string& code) {
    list<Edge*> incomingEdges;
    for (const auto& it : nodes) {
        for (auto e : it.second->getEdges()) {
            if (e->getDest() == code) {
                incomingEdges.push_back(e);
            }
        }
    }
    return incomingEdges;
}

bool Graph::CheckIfNodeExists(const string &code)  {
    return nodes.find(code) != nodes.end();
}

void Graph::testAndVisit(queue<Node*> &queue, Edge* edge, Node* node, double residual) {
    if (!node->getVisited() && residual > 0) {
        node->setVisited(true);
        node->setPath(edge);
        queue.push(node);
    }
}

bool Graph::findAugmentingPath(Node* src, Node* dest) {
    setUnvisited();
    src->setVisited(true);
    queue<Node*> q;
    q.push(src);
    while (!q.empty() && !dest->getVisited()) {
        auto v = q.front();
        q.pop();
        for (auto e: v->getEdges()) {
            testAndVisit(q, e, nodes[e->getDest()], e->getCapacity() - e->getFlow());
        }
        for (auto e: getIncomingEdges(v->getCode())) {
            testAndVisit(q, e, nodes[e->getOrigin()], e->getFlow());
        }
    }
    return dest->getVisited();
}

int Graph::findMinResidualAlongPath(Node* src, Node* dest) {
    int f = numeric_limits<int>::max();
    for (auto v = dest; v != src; ) {
        auto e = v->getPath();
        if (e->getDest() == v->getCode()) {
            f = min(f, e->getCapacity() - e->getFlow());
            v = nodes[e->getOrigin()];
        }
        else {
            f = min(f, e->getFlow());
            v = nodes[e->getDest()];
        }
    }
    return f;
}

void Graph::augmentFlowAlongPath(Node* src, Node* dest, int f) {
    for (auto v = dest; v != src;) {
        auto e = v->getPath();
        if (e->getDest() == v->getCode()) {
            e->setFlow(e->getFlow() + f);
            v = nodes[e->getOrigin()];
        }
        else {
            e->setFlow(e->getFlow() - f);
            v = nodes[e->getDest()];
        }
    }
}

void Graph::edmondsKarp() {
    addNode("R_0", new Reservoir(0, "R_0", "superSource", "superSource", numeric_limits<int>::max()));
    addNode("C_0", new City(0, "C_0", "superSink", numeric_limits<float>::max(), 0));
    for (auto& it : nodes) {
        if (auto* reservoir = dynamic_cast<Reservoir*>(it.second)) {
            addEdge("R_0", it.first, reservoir->getMaximumDelivery(), true);
        }
        if (auto* city = dynamic_cast<City*>(it.second)) {
            addEdge(it.first, "C_0", (int) city->getDemand(), true);
        }
    }
    setUnvisited();
    for (const auto& v : nodes) {
        for (auto e: v.second->getEdges()) {
            e->setFlow(0);
        }
    }
    while (findAugmentingPath(nodes["R_0"], nodes["C_0"])) {
        augmentFlowAlongPath(nodes["R_0"], nodes["C_0"], findMinResidualAlongPath(nodes["R_0"], nodes["C_0"]));
    }
    removeNode("R_0");
    removeNode("C_0");
}

list<pair<City*, float>> Graph::WaterDeficit(int &totalSupply, float &totalDemand) {
    list<pair<City*, float>> deficit;
    for (const auto& it : nodes) {
        if (auto* reservoir = dynamic_cast<Reservoir*>(it.second)) {
            totalSupply += reservoir->getMaximumDelivery();
        }
        if (auto* city = dynamic_cast<City*>(it.second)) {
            float demand = city->getDemand();
            totalDemand += demand;
            float maxFlow = 0;
            for (auto e : getIncomingEdges(city->getCode())) {
                maxFlow += (float) e->getFlow();
            }
            if (maxFlow < demand) {
                deficit.emplace_back(city, demand - maxFlow);
            }
        }
    }
    deficit.sort([](const pair<City*, float>& a, const pair<City*, float>& b) {
        return a.second > b.second;
    });
    return deficit;
}

list<pair<Edge*, double>> Graph::ComputeMetrics(double &maxDifference, double &averageDifference, double &variance) {
    list<pair<Edge*, double>> metrics;
    double totalDifference = 0;
    int edgeCount = 0;
    double difference;
    for (const auto& it : nodes) {
        edgeCount += it.second->getNumEdges();
        for (Edge* edge : it.second->getEdges()) {
            difference = edge->getCapacity() - edge->getFlow();
            totalDifference += difference;
            maxDifference = max(maxDifference, difference);
            metrics.emplace_back(edge, difference);
        }
    }
    metrics.sort([](const pair<Edge*, double>& a, const pair<Edge*, double>& b) {
        if (a.second == b.second) {
            return a.first->getCapacity() < b.first->getCapacity();
        }
        return a.second < b.second;
    });
    averageDifference = totalDifference / edgeCount;
    for (auto pair : metrics) {
        variance += pow(pair.second - averageDifference, 2);
    }
    variance /= edgeCount;
    return metrics;
}

void Graph::balanceLoad(list<pair<Edge*, double>> metrics) {
    // Calculate total excess capacity
    double totalExcessCapacity = 0;
    for (auto& pair : metrics) {
        if (pair.second > 0) {
            totalExcessCapacity += pair.second;
        }
    }
    // Calculate total unmet demand
    double totalUnmetDemand = 0;
    int unusedArg1 = 0;
    float unusedArg2 = 0;
    for (auto& pair : WaterDeficit(unusedArg1, unusedArg2)) {
        totalUnmetDemand += pair.second;
    }
    // Redistribute flow based on excess capacity and unmet demand
    for (auto& pair : metrics) {
        if (pair.second > 0) {
            double flowIncrease = (pair.second / totalExcessCapacity) * totalUnmetDemand;
            pair.first->setFlow(pair.first->getFlow() + (int) min(flowIncrease, pair.second));
        }
    }
}

list<pair<City*, double>> Graph::evaluateReservoirImpact(const string &code) {
    auto* reservoir = dynamic_cast<Reservoir*>(nodes[code]);
    list<pair<City*, double>> cities;
    nodes.erase(code);
    edmondsKarp();
    for (const auto& it : nodes) {
        if (auto* city = dynamic_cast<City*>(it.second)) {
            double totalIncomingFlow = 0;
            for (Edge* edge : getIncomingEdges(city->getCode())) {
                totalIncomingFlow += edge->getFlow();
            }
            if (totalIncomingFlow < city->getDemand()) {
                cities.emplace_back(city, (double) city->getDemand() - totalIncomingFlow);
            }
        }
    }
    nodes[code] = reservoir;
    return cities;
}

list<pair<City*, double>> Graph::evaluatePumpingStationImpact(const string &code) {
    auto* station = dynamic_cast<PumpingStation*>(nodes[code]);
    list<pair<City*, double>> cities;
    list<Edge> edges;
    for (Edge* edge : getIncomingEdges(code)) {
        edges.push_back(*edge);
    }
    for (Edge* edge : getIncomingEdges(code)) {
        nodes[edge->getOrigin()]->removeEdge(edge);
    }
    nodes.erase(code);
    edmondsKarp();
    for (const auto& it : nodes) {
        if (auto* city = dynamic_cast<City*>(it.second)) {
            double totalIncomingFlow = 0;
            for (Edge* edge : getIncomingEdges(city->getCode())) {
                totalIncomingFlow += edge->getFlow();
            }
            if (totalIncomingFlow < city->getDemand()) {
                cities.emplace_back(city, (double) city->getDemand() - totalIncomingFlow);
            }
        }
    }
    cities.sort([](const pair<City*, double>& a, const pair<City*, double>& b) {
        return a.second > b.second;
    });
    nodes[code] = station;
    for (const Edge& edge : edges) {
        nodes[edge.getOrigin()]->addEdge(new Edge(edge));
    }
    return cities;
}

unordered_map<Edge*, list<pair<City*, double>>> Graph::evaluatePipelineImpact() {
    unordered_map<Edge*, list<pair<City*, double>>> impact;
    for (const auto& it : nodes) {
        for (Edge* edge : it.second->getEdges()) {
            Edge edgeCopy = *edge;
            nodes[it.first]->removeEdge(edge);
            // Run the Edmonds-Karp algorithm
            edmondsKarp();
            // Check which cities have their demands not met
            list<pair<City*, double>> affectedCities;
            for (const auto& nodePair2 : nodes) {
                if (auto* city = dynamic_cast<City*>(nodePair2.second)) {
                    double totalIncomingFlow = 0;
                    for (Edge* edge2 : getIncomingEdges(city->getCode())) {
                        totalIncomingFlow += edge2->getFlow();
                    }
                    if (totalIncomingFlow < city->getDemand()) {
                        affectedCities.emplace_back(city, city->getDemand() - totalIncomingFlow);
                    }
                }
            }
            Edge* edgeCopyPtr = new Edge(edgeCopy);
            nodes[it.first]->addEdge(edgeCopyPtr);
            impact[edgeCopyPtr] = affectedCities;
        }
    }
    return impact;
}
