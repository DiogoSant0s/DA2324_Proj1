#include "Data.h"

Data::Data() : WaterNetwork(Graph()) {}

void Data::readData(const string& extension) {
    ifstream Reservoirs("../data/Reservoirs" + extension + ".csv");
    ifstream Stations("../data/Stations" + extension + ".csv");
    ifstream Cities("../data/Cities" + extension + ".csv");
    ifstream Pipes("../data/Pipes" + extension + ".csv");
    string textLine;

    getline(Reservoirs, textLine);
    getline(Stations, textLine);
    getline(Cities, textLine);
    getline(Pipes, textLine);

    while (getline(Reservoirs, textLine)) {
        stringstream input(textLine);
        string reservoir, Municipality, Id, Code, MaximumDelivery;

        getline(input, reservoir, ',');
        getline(input, Municipality, ',');
        getline(input, Id, ',');
        getline(input, Code, ',');
        getline(input, MaximumDelivery, '\r');

        WaterNetwork.addNode(Code, new Reservoir(stoi(Id), Code,
                                             wstringToString(removeAccents(stringToWstring(reservoir))),
                                             wstringToString(removeAccents(stringToWstring(Municipality))),
                                             stoi(MaximumDelivery)));
    }
    while (getline(Stations, textLine)) {
        stringstream input(textLine);
        string Id, Code;

        getline(input, Id, ',');
        getline(input, Code, '\r');

        WaterNetwork.addNode(Code, new PumpingStation(stoi(Id), Code));
    }
    while (getline(Cities, textLine)) {
        stringstream input(textLine);
        string city, Id, Code, Demand, Population;
        string empty;

        getline(input, city, ',');
        getline(input, Id, ',');
        getline(input, Code, ',');
        getline(input, Demand, ',');
        getline(input, Population, '\r');

        WaterNetwork.addNode(Code, new City(stoi(Id), Code,
                                            wstringToString(removeAccents(stringToWstring(city))),
                                            stof(Demand), stoi(Population)));
    }
    while (getline(Pipes, textLine)) {
        stringstream input(textLine);
        string Service_Point_A, Service_Point_B, Capacity, Direction;

        getline(input, Service_Point_A, ',');
        getline(input, Service_Point_B, ',');
        getline(input, Capacity, ',');
        getline(input, Direction, '\r');

        WaterNetwork.addEdge(Service_Point_A, Service_Point_B, stoi(Capacity), stoi(Direction));
    }
    Reservoirs.close();
    Stations.close();
    Cities.close();
    Pipes.close();
}

bool Data::checkIfItExists(const string &code) {
    return WaterNetwork.CheckIfNodeExists(code);
}

Graph Data::getWaterNetwork() {
    return WaterNetwork;
}

wstring Data::stringToWstring(const string& str) {
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}

string Data::wstringToString(const wstring& wstr) {
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

wstring Data::removeAccents(wstring wstr) {
    map<wchar_t, wchar_t> accentedChars = {
            {L'ã', L'a'}, {L'á', L'a'}, {L'à', L'a'}, {L'â', L'a'},
            {L'ç', L'c'}, {L'é', L'e'}, {L'è', L'e'}, {L'ê', L'e'},
            {L'í', L'i'}, {L'ì', L'i'}, {L'î', L'i'},
            {L'õ', L'o'}, {L'ó', L'o'}, {L'ò', L'o'}, {L'ô', L'o'},
            {L'ú', L'u'}, {L'ù', L'u'}, {L'û', L'u'},
            {L'Ã', L'A'}, {L'Á', L'A'}, {L'À', L'A'}, {L'Â', L'A'},
            {L'Ç', L'C'}, {L'É', L'E'}, {L'È', L'E'}, {L'Ê', L'E'},
            {L'Í', L'I'}, {L'Ì', L'I'}, {L'Î', L'I'},
            {L'Õ', L'O'}, {L'Ó', L'O'}, {L'Ò', L'O'}, {L'Ô', L'O'},
            {L'Ú', L'U'}, {L'Ù', L'U'}, {L'Û', L'U'},
    };
    for (wchar_t& i : wstr) {
        if (accentedChars.count(i)) {
            i = accentedChars[i];
        }
    }
    return wstr;
}

void Data::MaxFlow() {
    WaterNetwork.edmondsKarp();

    ofstream output("../data/FlowGraph.csv");
    ofstream output2("../data/MaxFlow.csv");

    output << "Source,Destination,Flow\n";
    output2 << "City,Code,Demand,MaxFlow\n";

    for (const auto& it : WaterNetwork.getNodes()) {
        for (const auto e : it.second->getEdges()) {
            output << e->getOrigin() << "," << e->getDest() << "," << e->getFlow() << "\n";
        }
        if (auto* city = dynamic_cast<City*>(it.second)) {
            int maxFlow = 0;
            for (const auto e : WaterNetwork.getIncomingEdges(city->getCode())) {
                if (e->getDest() == city->getCode()) {
                    maxFlow += e->getFlow();
                }
            }
            output2 << city->getCityName() << "," << city->getCode() << "," << city->getDemand() << "," << maxFlow << "\n";
        }
    }
    output.close();
    output2.close();
}
