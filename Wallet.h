#pragma once
#include <string>
#include<map>
#include "OrderBook.h"

class Wallet
{

public:
    Wallet(/* args */);
    ~Wallet();
    /** insert currency to the wallet */
    void insertCurrency(std::string type, double amount);
    /** remove currency to the wallet */
    bool removeCurrency(std::string type, double amount);

    /** Check if the wallet contains this much currency or more */
    bool containsCurrency(std::string type, double amount);
    /** generate a string representation of the wallet */
    /** checks if the wallet can cope with this ask or bid */
    //bool canFulfillOrder(OrderbookEntry order);
    bool canFulfillOrder(const std::string& product, double price, double amount,
                            const std::string& timestamp, OrderBookType orderType);
    /** update the contents of the wallet
     * assumer the order was made by the owner of the waller=t
     */
    void processSale(OrderBookEntry& sale);

    /** Generate a string representing the wallet */
    std::string toString();

private:
    /* data */
    std::map<std::string, double> currencies;
};







