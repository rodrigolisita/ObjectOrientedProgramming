#pragma once

#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
public:
    /** construct, reading a csv file */
    OrderBook(std::string filename);
    ~OrderBook();

    /** return vector of all known products in the dataset */
    std::vector<std::string> getKnownProducts();

    /** return vector of Orders according to the sent filters */
    std::vector<OrderBookEntry> getOrders(OrderBookType type,
                                            std::string product,
                                            std::string timestamp);
private:
    /* data */
    std::vector<OrderBookEntry> orders;
};

