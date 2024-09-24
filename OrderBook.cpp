#include "OrderBook.h"
#include <map>

OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}

OrderBook::~OrderBook()
{
}

std::vector<std::string> OrderBook::getKnownProducts()
{
    
    std::vector<std::string> products;

    std::map<std::string,bool> prodMap;

    for (OrderBookEntry& e : orders)
    {
        prodMap[e.product] = true;
    }

    // Flatten the map to a vector of strings
    for (auto const& e : prodMap)
    {
        products.push_back(e.first);
    }

    return products;


}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                        std::string product,
                                        std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;

    for (const OrderBookEntry& order : orders )
    {
        if (order.orderType == type && order.product == product && order.timestamp == timestamp){
            orders_sub.push_back(order);
        }
    }



    return orders_sub;

}

std::string OrderBook::getEarliestTime(){
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string& timestamp){
    
    std::string next_timestamp = "";

    for (OrderBookEntry& e : orders)
    {
        if(e.timestamp > timestamp)
        {
            next_timestamp = e.timestamp;
            break;
        }
    }
    if(next_timestamp == ""){
        next_timestamp = orders[0].timestamp;
    }
    return next_timestamp;
}

double OrderBook::getHighPrice(const std::vector<OrderBookEntry>& orders){
    double val=orders[0].price;

    for(const OrderBookEntry& order : orders){
        if(val<order.price){
            val=order.price;
        }
    }
        return val;
}

double OrderBook::getLowPrice(const std::vector<OrderBookEntry>& orders){
    double val=orders[0].price;

    for(const OrderBookEntry& order : orders){
        if(val>order.price){
            val=order.price;
        }
    }
        return val;
}

double OrderBook::getAveragePrice(const std::vector<OrderBookEntry>& orders){

    double average = 0;
    int count = 0;
    for (const OrderBookEntry& order : orders){
        average +=order.price;
        count++;
    }

    return average/count;

}