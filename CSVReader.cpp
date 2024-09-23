#include "CSVReader.h"
#include <iostream>



CSVReader::CSVReader(/* args */)
{
}

CSVReader::~CSVReader()
{
}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFile)
{

}

std::vector<std::string> CSVReader::tokenise(const std::string& line, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}