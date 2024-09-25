#pragma once

#include <iostream>
#include <fstream>
#include <sstream> // For std::stringstream
#include <vector>
#include "OrderBookEntry.h"



class CSVReader
{
private:
    /* data */
    
public:
    CSVReader(/* args */);
    ~CSVReader();

    /** Read the CSV file and return the tokenized orders */
    static std::vector<OrderBookEntry> readCSV(std::string csvFile);

    //static OrderBookEntry enterOrder(double price, double amount, std::string timestamp, std::string product, std::string OrderBookType);
    

    static std::vector<std::string> tokenise(const std::string& line, char delimiter);

};








