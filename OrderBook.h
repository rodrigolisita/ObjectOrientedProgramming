#pragma once

#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>
#include <map>


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

    void enterOrder(const std::string& product, double price, double amount, 
                           const std::string& timestamp, OrderBookType orderType);
    

    std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);




    /** Get earlisest time */
    std::string getEarliestTime();

    /** Get next time 
     * If there is no next timestamp, wraps around to the start;
    */
    std::string getNextTime(std::string& timestamp);

    /** Get the higher price */
    static double getHighPrice(const std::vector<OrderBookEntry>& entries);

    /** Get the lower price */
    static double getLowPrice(const std::vector<OrderBookEntry>& entries);

    /** Get the average price */
    static double getAveragePrice(const std::vector<OrderBookEntry>& entries);


private:
    /* data */
    std::vector<OrderBookEntry> orders;
    std::map<std::string,bool> orderMap;
    bool isOrderMapInitialized = false; // Add a flag to track initialization
    std::map<std::string,bool> getOrderMap();


};

