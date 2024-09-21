#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry( double _price, 
                double _amount, 
                std::string _timestamp, 
                std::string _product, 
                OrderBookType _orderType)
: price(_price), 
  amount(_amount), 
  timestamp(_timestamp),
  product(_product), 
  orderType(_orderType)                
{
    
};

double OrderBookEntry::getPrice()
{
    return price;
}

std::string OrderBookEntry::orderTypeToString(OrderBookType type) {
    switch (type) {
        case OrderBookType::bid: return "bid";
        case OrderBookType::ask: return "ask";
        // Add more cases if you extend your OrderBookType enum
        default: return "unknown"; // Handle unexpected values
    }
}

