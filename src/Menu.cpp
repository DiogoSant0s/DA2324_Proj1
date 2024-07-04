#include "Menu.h"

Menu::Menu() : data(Data()) {
    SelectGraphMenu();
}

void Menu::printTitle() {
    cout << R"(
_____________________________________________________________________________________________________________________
  __      __ ____ ___ ____ ____    ____ _  _ ____ ____ _   _  _    _  _ ____ _  _ ____ ____ ____ _  _ ____ _  _ ___
   \  /\  /  |__|  |  |___ |__/    |___ |  | |__| |__| |    \/     |\/| |__| |\ | |__| | _  |___ |\/| |___ |\ |  |
    \/  \/   |  |  |  |___ |  \    ___| |__| |    |    |___ ||     |  | |  | | \| |  | |__] |___ |  | |___ | \|  |
---------------------------------------------------------------------------------------------------------------------
    )" << "\n";
}

void Menu::Print(const string& s, int linelength) {
    int spaces;
    bool uneven = false;
    if ((linelength - int(s.size())) % 2 == 1) uneven = true;
    spaces = (linelength - int(s.size())) / 2;
    cout << "|";
    if (spaces > 0) cout << string(spaces, ' ');
    cout << s;
    if (spaces > 0) cout << string(spaces, ' ');
    if (uneven) cout << " ";
}

void Menu::clearScreen() {
    for (int i = 0; i < 20; i++) {
        cout << "\n";
    }
}

int Menu::getUserInput(vector<int> inputs) {
    int input;
    if(!cin){
        cin.ignore();
        cin.ignore(100,'\n');
        cin.clear();
    }
    cin >> input;
    while (cin.fail() || (find(inputs.begin(), inputs.end(), input) == inputs.end())) {
        if (cin.eof() || input == 0) {
            cout << "\nExiting\n\n";
            exit(0);
        }
        cin.clear();
        cin.ignore();
        cerr << "Not a valid input, please input one of the shown options: ";
        cin >> input;
    }
    cin.ignore(100, '\n');
    return input;
}

string Menu::getUserTextInput() {
    string input;
    getline(cin, input);
    if (cin.fail()) cout << "deez";
    while (cin.fail() || input.empty()) {
        if (cin.eof()) {
            cout << "\nExiting\n\n";
            exit(0);
        }
        cin.clear();
        cin.ignore(100, '\n');
        cerr << "Not a valid input, please try again: ";
        getline(cin, input);
    }
    return input;
}

void Menu::SelectGraphMenu() {
    printTitle();
    cout << "\n";
    cout << "\tSelect Graph Menu\n";
    cout << "(1) Large Dataset\n";
    cout << "(2) Small Dataset\n";
    cout << "(0) Exit\n";
    cout << " > ";

    if (!data.getWaterNetwork().getNodes().empty()) {
        data = Data();
    }

    int input = getUserInput({0, 1, 2});
    switch (input) {
        case 1:
            clearScreen();
            data.readData("");
            MainMenu();
        case 2:
            clearScreen();
            data.readData("_Madeira");
            MainMenu();
        case 0:
            exit(0);
        default:
            break;
    }
}

void Menu::MainMenu() {
    printTitle();
    cout << "\n";
    cout << "\tMain Menu\n";
    cout << "(1) Node Information\n";
    cout << "(2) Water Network Menu\n";
    cout << "(3) Resiliency Menu\n";
    cout << "(4) Back to Select Graph Menu\n";
    cout << "(0) Exit\n";
    cout << " > ";

    int input = getUserInput({0, 1, 2, 3, 4});
    switch (input) {
        case 1:
            clearScreen();
            NodeInfo();
        case 2:
            clearScreen();
            WaterNetworkMenu();
        case 3:
            clearScreen();
            ResiliencyMenu();
        case 4:
            clearScreen();
            SelectGraphMenu();
        case 0:
            exit(0);
        default:
            break;
    }
}

void Menu::NodeInfo() {
    printTitle();
    cout << "\n";
    cout << "\tNode Menu\n";
    cout << "(1) All nodes\n";
    cout << "(2) Information about a specific node\n";
    cout << "(3) Max flow to the cities\n";
    cout << "(4) Back to Main Menu\n";
    cout << "(0) Exit\n";
    cout << " > ";

    int input = getUserInput({0, 1, 2, 3, 4});
    switch (input) {
        case 1:
            if (!data.getWaterNetwork().getNodes().empty()) {
                int count = 0;
                // Print the cities
                cout << "\n\n";
                for (int i = 0; i < 65; ++i) cout << "-";
                cout << "\n";
                Print("Id", 6);
                Print("Code", 8);
                Print("City", 20);
                Print("Demand", 10);
                Print("Population", 15);
                cout << "|\n";
                for (int i = 0; i < 65; ++i) cout << "-";
                cout << "\n";
                for (auto& it : data.getWaterNetwork().getNodes()) {
                    if (City* city = dynamic_cast<City*>(it.second)) {
                        Print(to_string(city->getId()), 6);
                        Print(city->getCode(), 8);
                        Print(city->getCityName(), 20);
                        stringstream x;
                        x << fixed << setprecision(2) << city->getDemand();
                        Print(x.str(), 10);
                        Print(to_string(city->getPopulation()), 15);
                        cout << "|\n";
                        count++;
                    }
                }
                for (int i = 0; i < 65; ++i) cout << "-";
                cout << "\n\nThere exists a total of " << count << " cities/delivery sites.\n\n";
                count = 0;
                // Print the reservoirs
                for (int i = 0; i < 87; ++i) cout << "-";
                cout << "\n";
                Print("Id", 6);
                Print("Code", 8);
                Print("Reservoir", 20);
                Print("Municipality", 20);
                Print("Maximum Delivery (m3/sec)", 27);
                cout << "|\n";
                for (int i = 0; i < 87; ++i) cout << "-";
                cout << "\n";
                for (auto& it : data.getWaterNetwork().getNodes()) {
                    if (auto* reservoir = dynamic_cast<Reservoir*>(it.second)) {
                        Print(to_string(reservoir->getId()), 6);
                        Print(reservoir->getCode(), 8);
                        Print(reservoir->getReservoirName(), 20);
                        Print(reservoir->getMunicipality(), 20);
                        Print(to_string(reservoir->getMaximumDelivery()), 27);
                        cout << "|\n";
                        count++;
                    }
                }
                for (int i = 0; i < 87; ++i) cout << "-";
                cout << "\n\nThere exists a total of " << count << " reservoirs.\n\n";
                count = 0;
                // Print the pumping stations
                for (int i = 0; i < 17; ++i) cout << "-";
                cout << "\n";
                Print("Id", 6);
                Print("Code", 8);
                cout << "|\n";
                for (int i = 0; i < 17; ++i) cout << "-";
                cout << "\n";
                for (auto& it : data.getWaterNetwork().getNodes()) {
                    if (auto* pumpingStation = dynamic_cast<PumpingStation*>(it.second)) {
                        Print(to_string(pumpingStation->getId()), 6);
                        Print(pumpingStation->getCode(), 8);
                        cout << "|\n";
                        count++;
                    }
                }
                for (int i = 0; i < 17; ++i) cout << "-";
                cout << "\n\nThere exists a total of " << count << " pumping stations.\n\n";

                cout << "\n";
                cout << "(1) Go back to the Node Menu\n";
                cout << "(0) Exit\n";
                cout << " > ";

                input = getUserInput({0, 1});
                switch (input) {
                    case 1:
                        clearScreen();
                        NodeInfo();
                    case 0:
                        exit(0);
                    default:
                        break;
                }
            }
        case 2:
            if (!data.getWaterNetwork().getNodes().empty()) {
                cout << "\n\nWrite the code of the node you want to search for: ";
                string textInput = getUserTextInput();
                if (!data.checkIfItExists(textInput)) {
                    cout << "That Node doesn't exist. Try Again.\n\n";
                    NodeInfo();
                }
                if (auto* city = dynamic_cast<City*>(data.getWaterNetwork().getNodes().find(textInput)->second)) {
                    cout << "\n\n";
                    for (int i = 0; i < 65; ++i) cout << "-";
                    cout << "\n";
                    Print("Id", 6);
                    Print("Code", 8);
                    Print("City", 20);
                    Print("Demand", 10);
                    Print("Population", 15);
                    cout << "|\n";
                    for (int i = 0; i < 65; ++i) cout << "-";
                    cout << "\n";
                    Print(to_string(city->getId()), 6);
                    Print(city->getCode(), 8);
                    Print(city->getCityName(), 20);
                    stringstream x;
                    x << fixed << setprecision(2) << city->getDemand();
                    Print(x.str(), 10);
                    Print(to_string(city->getPopulation()), 15);
                    cout << "|\n";
                    for (int i = 0; i < 65; ++i) cout << "-";
                    cout << "\n";
                } else if (auto* reservoir = dynamic_cast<Reservoir*>(data.getWaterNetwork().getNodes().find(textInput)->second)) {
                    cout << "\n\n";
                    for (int i = 0; i < 87; ++i) cout << "-";
                    cout << "\n";
                    Print("Id", 6);
                    Print("Code", 8);
                    Print("Reservoir", 20);
                    Print("Municipality", 20);
                    Print("Maximum Delivery (m3/sec)", 27);
                    cout << "|\n";
                    for (int i = 0; i < 87; ++i) cout << "-";
                    cout << "\n";
                    Print(to_string(reservoir->getId()), 6);
                    Print(reservoir->getCode(), 8);
                    Print(reservoir->getReservoirName(), 20);
                    Print(reservoir->getMunicipality(), 20);
                    Print(to_string(reservoir->getMaximumDelivery()), 27);
                    cout << "|\n";
                    for (int i = 0; i < 87; ++i) cout << "-";
                    cout << "\n";
                } else if (auto* pumpingStation = dynamic_cast<PumpingStation*>(data.getWaterNetwork().getNodes().find(textInput)->second)) {
                    cout << "\n\n";
                    for (int i = 0; i < 17; ++i) cout << "-";
                    cout << "\n";
                    Print("Id", 6);
                    Print("Code", 8);
                    cout << "|\n";
                    for (int i = 0; i < 17; ++i) cout << "-";
                    cout << "\n";
                    Print(to_string(pumpingStation->getId()), 6);
                    Print(pumpingStation->getCode(), 8);
                    cout << "|\n";
                    for (int i = 0; i < 17; ++i) cout << "-";
                    cout << "\n";
                } else {
                    cout << "Something really wrong happened here, it is supposed to be impossible to reach here\n\n";
                    exit(0);
                }
                cout << "\n";
                for (int i = 0; i < 38; ++i) cout << "-";
                cout << "\n";
                Print("Origin", 10);
                Print("Destination", 13);
                Print("Capacity", 10);
                cout << "|\n";
                for (int i = 0; i < 38; ++i) cout << "-";
                cout << "\n";

                auto edges = data.getWaterNetwork().getEdges(textInput);
                edges.merge(data.getWaterNetwork().getIncomingEdges(textInput));

                for (const auto& edge : edges) {
                    Print(edge->getOrigin(), 10);
                    Print(edge->getDest(), 13);
                    Print(to_string(edge->getCapacity()), 10);
                    cout << "|\n";
                }
                for (int i = 0; i < 38; ++i) cout << "-";
                cout << "\n\n";
                cout << "(1) Go back to the Node Menu\n";
                cout << "(0) Exit\n";
                cout << " > ";
                input = getUserInput({0, 1});
                switch (input) {
                    case 1:
                        clearScreen();
                        NodeInfo();
                        break;
                    case 0:
                        exit(0);
                    default:
                        break;
                }
            }
        case 3:
            clearScreen();
            MaxFlowMenu();
        case 4:
            clearScreen();
            MainMenu();
        case 0:
            exit(0);
        default:
            break;
    }
}

void Menu::MaxFlowMenu() {
    printTitle();
    cout << "Max Flow Menu\n";
    cout << "(1) Maximum amount of water that can reach a specific city\n";
    cout << "(2) Maximum amount of water that can reach each city\n";
    cout << "(3) Go back to the Node Menu\n";
    cout << "(0) Exit\n";
    cout << " > ";

    data.MaxFlow();

    int input = getUserInput({0, 1, 2, 3});
    switch (input) {
        case 1:
            if (!data.getWaterNetwork().getNodes().empty()) {
                cout << "\n\nPlease enter the target City's code: ";
                string targetCity = getUserTextInput();
                if (data.checkIfItExists(targetCity)) {
                    if (auto* city = dynamic_cast<City*>(data.getWaterNetwork().getNodes().find(targetCity)->second)) {
                        cout << "\n";
                        for (int i = 0; i < 76; ++i) cout << "-";
                        cout << "\n";
                        Print("Id", 6);
                        Print("Code", 8);
                        Print("City", 20);
                        Print("Demand", 10);
                        Print("Population", 15);
                        Print("Max Flow", 10);
                        cout << "|\n";
                        for (int i = 0; i < 76; ++i) cout << "-";
                        cout << "\n";
                        Print(to_string(city->getId()), 6);
                        Print(city->getCode(), 8);
                        Print(city->getCityName(), 20);
                        stringstream x;
                        x << fixed << setprecision(2) << city->getDemand();
                        Print(x.str(), 10);
                        Print(to_string(city->getPopulation()), 15);
                        double maxFlow = 0;
                        for (const auto& edge : data.getWaterNetwork().getIncomingEdges(targetCity)) {
                            maxFlow += edge->getFlow();
                        }
                        stringstream y;
                        y << fixed << setprecision(2) << maxFlow;
                        Print(y.str(), 10);
                        cout << "|\n";
                        for (int i = 0; i < 76; ++i) cout << "-";
                        cout << "\n\n";
                    } else {
                        cout << "\n\nThat code does not correspond to a City. Try Again.\n\n";
                        MaxFlowMenu();
                    }
                } else {
                    cout << "\n\nThat code doesn't correspond with an existing Node. Try Again.\n\n";
                    MaxFlowMenu();
                }
                cout << "(1) Go back to the Node Menu\n";
                cout << "(0) Exit\n";
                cout << " > ";
                input = getUserInput({0, 1});
                switch (input) {
                    case 1:
                        clearScreen();
                        NodeInfo();
                    case 0:
                        exit(0);
                    default:
                        break;
                }
            }
        case 2:
            if (!data.getWaterNetwork().getNodes().empty()) {
                cout << "\n";
                for (int i = 0; i < 76; ++i) cout << "-";
                cout << "\n";
                Print("Id", 6);
                Print("Code", 8);
                Print("City", 20);
                Print("Demand", 10);
                Print("Population", 15);
                Print("Max Flow", 10);
                cout << "|\n";
                for (int i = 0; i < 76; ++i) cout << "-";
                cout << "\n";
                for (auto& it : data.getWaterNetwork().getNodes()) {
                    if (auto* city = dynamic_cast<City*>(it.second)) {
                        Print(to_string(city->getId()), 6);
                        Print(city->getCode(), 8);
                        Print(city->getCityName(), 20);
                        stringstream x;
                        x << fixed << setprecision(2) << city->getDemand();
                        Print(x.str(), 10);
                        Print(to_string(city->getPopulation()), 15);
                        double maxFlow = 0;
                        for (const auto& edge : data.getWaterNetwork().getIncomingEdges(city->getCode())) {
                            maxFlow += edge->getFlow();
                        }
                        stringstream y;
                        y << fixed << setprecision(2) << maxFlow;
                        Print(y.str(), 10);
                        cout << "|\n";
                    }
                }
                for (int i = 0; i < 76; ++i) cout << "-";
                cout << "\n\n(1) Go back to the Node Menu\n";
                cout << "(0) Exit\n";
                cout << " > ";
                input = getUserInput({0, 1});
                switch (input) {
                    case 1:
                        clearScreen();
                        NodeInfo();
                    case 0:
                        exit(0);
                    default:
                        break;
                }
            }
        case 3:
            clearScreen();
            NodeInfo();
        case 0:
            exit(0);
        default:
            break;
    }
}

void Menu::WaterNetworkMenu() {
    printTitle();
    cout << "\n";
    cout << "\tWater Network Menu\n";
    cout << "(1) Water flow in deficit\n";
    cout << "(2) Flow Redistribution\n";
    cout << "(3) Back to Main Menu\n";
    cout << "(0) Exit\n";
    cout << " > ";

    data.getWaterNetwork().edmondsKarp();

    int input = getUserInput({0, 1, 2, 3});
    switch (input) {
        case 1:
            if (!data.getWaterNetwork().getNodes().empty()) {
                int totalSupply = 0;
                float totalDemand = 0;
                float totalDeficit = 0;
                cout << "\n";
                for (int i = 0; i < 76; ++i) cout << "-";
                cout << "\n";
                Print("Id", 6);
                Print("Code", 8);
                Print("City", 20);
                Print("Demand", 10);
                Print("Population", 15);
                Print("Deficit", 10);
                cout << "|\n";
                for (int i = 0; i < 76; ++i) cout << "-";
                cout << "\n";
                for (auto pair : data.getWaterNetwork().WaterDeficit(totalSupply, totalDemand)) {
                    Print(to_string(pair.first->getId()), 6);
                    Print(pair.first->getCode(), 8);
                    Print(pair.first->getCityName(), 20);
                    stringstream x;
                    x << fixed << setprecision(2) << pair.first->getDemand();
                    Print(x.str(), 10);
                    Print(to_string(pair.first->getPopulation()), 15);
                    stringstream y;
                    y << fixed << setprecision(2) << pair.second;
                    Print(y.str(), 10);
                    cout << "|\n";
                    totalDeficit += pair.second;
                }
                for (int i = 0; i < 76; ++i) cout << "-";
                cout << "\n\n";

                for (int i = 0; i < 53; ++i) cout << "-";
                cout << "\n";
                Print("Water Network", 51);
                cout << "|\n";
                for (int i = 0; i < 53; ++i) cout << "-";
                cout << "\n";
                Print("Total Supply", 16);
                Print("Total Demand", 16);
                Print("Total Deficit", 17);
                cout << "|\n";
                for (int i = 0; i < 53; ++i) cout << "-";
                cout << "\n";
                Print(to_string(totalSupply), 16);
                stringstream x;
                x << fixed << setprecision(2) << totalDemand;
                Print(x.str(), 16);
                stringstream y;
                y << fixed << setprecision(2) << totalDeficit;
                Print(y.str(), 17);
                cout << "|\n";
                for (int i = 0; i < 53; ++i) cout << "-";
                cout << "\n";

                cout << "\n\n(1) Go back to the Main Menu\n";
                cout << "(0) Exit\n";
                cout << " > ";
                input = getUserInput({0, 1});
                switch (input) {
                    case 1:
                        clearScreen();
                        MainMenu();
                    case 0:
                        exit(0);
                    default:
                        break;
                }
            }
            break;
        case 2:
            if (!data.getWaterNetwork().getNodes().empty()) {
                double maxDifference = 0;
                double averageDifference = 0;
                double variance = 0;
                double maxDifference2 = 0;
                double averageDifference2 = 0;
                double variance2 = 0;
                cout << "\n";
                for (int i = 0; i < 102; ++i) cout << "-";
                cout << "\n";
                Print("Edge Information", 39);
                Print("Before Flow Redistribution", 30);
                Print("After Flow Redistribution", 29);
                cout << "|\n";
                for (int i = 0; i < 102; ++i) cout << "-";
                cout << "\n";
                Print("Origin", 10);
                Print("Destination", 15);
                Print("Capacity", 12);
                Print("Flow", 13);
                Print("Difference", 16);
                Print("Flow", 13);
                Print("Difference", 15);
                cout << "|\n";
                for (int i = 0; i < 102; ++i) cout << "-";
                cout << "\n";

                auto initialMetrics = data.getWaterNetwork().ComputeMetrics(maxDifference, averageDifference, variance);
                data.getWaterNetwork().balanceLoad(initialMetrics);
                auto finalMetrics = data.getWaterNetwork().ComputeMetrics(maxDifference2, averageDifference2, variance2);

                for (auto pair : initialMetrics) {
                    Print(pair.first->getOrigin(), 10);
                    Print(pair.first->getDest(), 15);
                    Print(to_string(pair.first->getCapacity()), 12);
                    Print(to_string(pair.first->getCapacity() - (int) pair.second), 13);
                    Print(to_string((int) pair.second), 16);
                    for (auto pair2 : finalMetrics) {
                        if (pair.first == pair2.first) {
                            Print(to_string(pair2.first->getFlow()), 13);
                            Print(to_string((int) pair2.second), 15);
                        }
                    }
                    cout << "|\n";
                }
                for (int i = 0; i < 102; ++i) cout << "-";
                cout << "\n\n\n";
                for (int i = 0; i < 115; ++i) cout << "-";
                cout << "\n";
                Print("Water Network", 113);
                cout << "|\n";
                for (int i = 0; i < 115; ++i) cout << "-";
                cout << "\n";
                Print("Before Flow Redistribution", 56);
                Print("After Flow Redistribution", 56);
                cout << "|\n";
                for (int i = 0; i < 115; ++i) cout << "-";
                cout << "\n";
                Print("Max Difference", 18);
                Print("Average Difference", 22);
                Print("Variance", 14);
                Print("Max Difference", 18);
                Print("Average Difference", 22);
                Print("Variance", 14);
                cout << "|\n";
                for (int i = 0; i < 115; ++i) cout << "-";
                cout << "\n";
                stringstream x;
                x << fixed << setprecision(3) << variance;
                stringstream y;
                y << fixed << setprecision(3) << variance2;
                Print(to_string((int) maxDifference), 18);
                Print(to_string(averageDifference), 22);
                Print(x.str(), 14);
                Print(to_string((int)maxDifference2), 18);
                Print(to_string(averageDifference2), 22);
                Print(y.str(), 14);
                cout << "|\n";
                for (int i = 0; i < 115; ++i) cout << "-";
                cout << "\n\n\n";

                cout << "(1) Go back to the Main Menu\n";
                cout << "(0) Exit\n";
                cout << " > ";
                input = getUserInput({0, 1});
                switch (input) {
                    case 1:
                        clearScreen();
                        MainMenu();
                    case 0:
                        exit(0);
                    default:
                        break;
                }
            }
        case 3:
            clearScreen();
            MainMenu();
        case 0:
            exit(0);
        default:
            break;
    }
}

void Menu::ResiliencyMenu() {
    printTitle();
    cout << "\n";
    cout << "\tResiliency Menu\n";
    cout << "(1) Resiliency check: Removing a Reservoir\n";
    cout << "(2) Resiliency check: Removing a Pumping Station\n";
    cout << "(3) Resiliency check: Removing all Edges, one at a time\n";
    cout << "(4) Go back to Main Menu\n";
    cout << "(0) Exit\n";
    cout << " > ";

    int input = getUserInput({0, 1, 2, 3, 4});
    switch (input) {
        case 1:
            if (!data.getWaterNetwork().getNodes().empty()) {
                cout << "\n\nPlease enter the code of the Reservoir you want to remove: ";
                string reservoirCode = getUserTextInput();
                if (data.checkIfItExists(reservoirCode)) {
                    if (auto reservoir = dynamic_cast<Reservoir*>(data.getWaterNetwork().getNodes().find(reservoirCode)->second)) {
                        cout << "\n\nThe Reservoir named" << reservoir->getReservoirName() << " has been temporarily removed.\n\n";
                        for (int i = 0; i < 76; ++i) cout << "-";
                        cout << "\n";
                        Print("Id", 6);
                        Print("Code", 8);
                        Print("City", 20);
                        Print("Demand", 10);
                        Print("Population", 15);
                        Print("Deficit", 10);
                        cout << "|\n";
                        for (int i = 0; i < 76; ++i) cout << "-";
                        cout << "\n";
                        for (auto pair : data.getWaterNetwork().evaluateReservoirImpact(reservoirCode)) {
                            Print(to_string(pair.first->getId()), 6);
                            Print(pair.first->getCode(), 8);
                            Print(pair.first->getCityName(), 20);
                            stringstream x;
                            x << fixed << setprecision(2) << pair.first->getDemand();
                            Print(x.str(), 10);
                            Print(to_string(pair.first->getPopulation()), 15);
                            stringstream y;
                            y << fixed << setprecision(2) << pair.second;
                            Print(y.str(), 10);
                            cout << "|\n";
                        }
                        for (int i = 0; i < 76; ++i) cout << "-";
                    } else {
                        cout << "\n\nThat code does not correspond to a Reservoir. Try Again.\n\n";
                        WaterNetworkMenu();
                    }
                } else {
                    cout << "\n\nThat code doesn't correspond with an existing Node. Try Again.\n\n";
                    WaterNetworkMenu();
                }
                cout << "\n\n(1) Go back to the Main Menu\n";
                cout << "(0) Exit\n";
                cout << " > ";
                input = getUserInput({0, 1});
                switch (input) {
                    case 1:
                        clearScreen();
                        MainMenu();
                    case 0:
                        exit(0);
                    default:
                        break;
                }
            }
        case 2:
            if (!data.getWaterNetwork().getNodes().empty()) {
                cout << "\n\nPlease enter the code of the Pumping Station you want to remove: ";
                string psCode = getUserTextInput();
                if (data.checkIfItExists(psCode)) {
                    if (auto pumpingStation = dynamic_cast<PumpingStation*>(data.getWaterNetwork().getNodes().find(psCode)->second)) {
                        cout << "\n\nThe Pumping Station number " << pumpingStation->getId() << " has been temporarily removed.\n\n";
                        auto list = data.getWaterNetwork().evaluatePumpingStationImpact(psCode);
                        int unused = 0;
                        float unused2 = 0;
                        auto normalList = data.getWaterNetwork().WaterDeficit(unused, unused2);
                        bool equal = true;
                        if (list.size() != normalList.size()) {
                            equal = false;
                        } else {
                            for (auto pair : list) {
                                if ((int) normalList.front().second != (int) pair.second) {
                                    equal = false;
                                    break;
                                } else {
                                    normalList.pop_front();
                                }
                            }
                        }
                        if (list.empty() || equal) {
                            cout << "The removal of this Pumping Station has no impact on the Water Network.\n\n";
                            cout << "(1) Go back to the Main Menu\n";
                            cout << "(0) Exit\n";
                            cout << " > ";
                            input = getUserInput({0, 1});
                            switch (input) {
                                case 1:
                                    clearScreen();
                                    MainMenu();
                                case 0:
                                    exit(0);
                                default:
                                    break;
                            }
                        }
                        for (int i = 0; i < 76; ++i) cout << "-";
                        cout << "\n";
                        Print("Id", 6);
                        Print("Code", 8);
                        Print("City", 20);
                        Print("Demand", 10);
                        Print("Population", 15);
                        Print("Deficit", 10);
                        cout << "|\n";
                        for (int i = 0; i < 76; ++i) cout << "-";
                        cout << "\n";
                        for (auto pair : list) {
                            Print(to_string(pair.first->getId()), 6);
                            Print(pair.first->getCode(), 8);
                            Print(pair.first->getCityName(), 20);
                            stringstream x;
                            x << fixed << setprecision(2) << pair.first->getDemand();
                            Print(x.str(), 10);
                            Print(to_string(pair.first->getPopulation()), 15);
                            stringstream y;
                            y << fixed << setprecision(2) << pair.second;
                            Print(y.str(), 10);
                            cout << "|\n";
                        }
                        for (int i = 0; i < 76; ++i) cout << "-";
                    } else {
                        cout << "\n\nThat code does not correspond to a Pumping Station. Try Again.\n\n";
                        ResiliencyMenu();
                    }
                } else {
                    cout << "\n\nThat code doesn't correspond with an existing Node. Try Again.\n\n";
                    ResiliencyMenu();
                }
                cout << "\n\n(1) Go back to the Main Menu\n";
                cout << "(0) Exit\n";
                cout << " > ";
                input = getUserInput({0, 1});
                switch (input) {
                    case 1:
                        clearScreen();
                        MainMenu();
                    case 0:
                        exit(0);
                    default:
                        break;
                }
            }
        case 3:
            if (!data.getWaterNetwork().getNodes().empty()) {
                cout << "\n\n";
                for (int i = 0; i < 106; ++i) cout << "-";
                cout << "\n";
                Print("Edge Information", 33);
                Print("City Information", 70);
                cout << "|\n";
                for (int i = 0; i < 106; ++i) cout << "-";
                cout << "\n";
                Print("Origin", 8);
                Print("Destination", 13);
                Print("Capacity", 10);
                Print("Id", 4);
                Print("Code", 8);
                Print("City", 20);
                Print("Demand", 10);
                Print("Population", 12);
                Print("Deficit", 11);
                cout << "|\n";
                for (int i = 0; i < 106; ++i) cout << "-";
                cout << "\n";
                for (const auto& pair : data.getWaterNetwork().evaluatePipelineImpact()) {
                    Print(pair.first->getOrigin(), 8);
                    Print(pair.first->getDest(), 13);
                    Print(to_string(pair.first->getCapacity()), 10);
                    bool first = true;
                    for (auto pair2 : pair.second) {
                        if (!first) {
                            Print("", 8);
                            Print("", 13);
                            Print("", 10);
                        }
                        Print(to_string(pair2.first->getId()), 4);
                        Print(pair2.first->getCode(), 8);
                        Print(pair2.first->getCityName(), 20);
                        stringstream x;
                        x << fixed << setprecision(2) << pair2.first->getDemand();
                        Print(x.str(), 10);
                        Print(to_string(pair2.first->getPopulation()), 12);
                        stringstream y;
                        y << fixed << setprecision(2) << pair2.second;
                        Print(y.str(), 11);
                        cout << "|\n";
                        first = false;
                    }
                    for (int i = 0; i < 106; ++i) cout << "-";
                        cout << "\n";
                }
                cout << "\n\n(1) Go back to the Main Menu\n";
                cout << "(0) Exit\n";
                cout << " > ";
                input = getUserInput({0, 1});
                switch (input) {
                    case 1:
                        clearScreen();
                        MainMenu();
                    case 0:
                        exit(0);
                    default:
                        break;
                }
            }
        case 4:
            clearScreen();
            MainMenu();
        case 0:
            exit(0);
        default:
            break;
    }
}
