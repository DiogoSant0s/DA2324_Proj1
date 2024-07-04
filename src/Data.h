#ifndef DA_RAILWAYS_DATA_H
#define DA_RAILWAYS_DATA_H

#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <codecvt>
#include <locale>
#include "Graph.h"

/**
 * @class Data
 * @details Class that stores all the data from the files and the WaterNetwork.
 */
class Data {
private:
    Graph WaterNetwork;
public:
    /**
     * @details Creates the WaterNetwork.
     * @details Constructor of the Data class.
     */
    Data();
    /**
     * @details Reads all the data saved in the files and stores them in the correct structures.
     * @details Time Complexity - O(N).
     * @details N is the number of lines in the files to be read.
     */
    void readData(const string& extension);
    /**
     * @details Auxiliary method to convert a string to a wstring
     * @details Time Complexity- O(1).
     * @param str String that is to be converted
     * @return wstring resulting from the conversion
     */
    static wstring stringToWstring(const string& str);
    /**
     * @details Auxiliary method to convert a wstring to a string
     * @details Time Complexity - O(1).
     * @param wstr Wstring that is to be converted
     * @return string resulting from the conversion
     */
    static string wstringToString(const wstring& wstr);
    /**
     * @details Auxiliary method to remove accents from a wstring
     * @details Time Complexity - O(1).
     * @param wstr Wstring from which the accents are to be removed
     * @return wstring without accents
     */
    static wstring removeAccents(wstring wstr);
    /**
     * @details Checks if Node exists in nodes hash table.
     * @details Time Complexity - O(1).
     * @param code Node's code.
     * @return True - If the station exists.
     * @return False - If the station doesn't exist.
     */
    bool checkIfItExists(const string &code) ;
    /**
     * @details Normal method that returns the WaterNetwork
     * @details Complexity: O(1)
     * @return WaterNetwork
     */
    Graph getWaterNetwork();
    /**
     * @details Calls the EdmondsKarp method from the Graph class and writes the results to two different files
     * @details Time Complexity: O(|V| * |E|^2)
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     */
    void MaxFlow();
};

#endif //DA_RAILWAYS_DATA_H
