#include "OrderBook.h"
#include <algorithm>

OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
    orderMap = OrderBook::getOrderMap();
}

OrderBook::~OrderBook()
{
}

std::map<std::string,bool> OrderBook::getOrderMap()
{
    if (!isOrderMapInitialized) { // Check if the map has already been initialized
        std::map<std::string,bool> prodMap; // Create a local map

        for (const OrderBookEntry& e : orders)  // Use const reference for read-only access
        {
            prodMap[e.product] = true;        // Populate the local map
        }
        
        isOrderMapInitialized = true; // Set the flag to true after initialization
    
        return prodMap;                        // Return the local map  
    } else {
        return orderMap; // If already initialized, return the existing map
    }
    
}

std::vector<std::string> OrderBook::getKnownProducts()
{
    
    std::vector<std::string> products;

//    OrderBook::getOrderMap();

    //std::map<std::string,bool> prodMap = OrderBook::getOrderMap();

    //for (OrderBookEntry& e : orders)
    //{
    //    prodMap[e.product] = true;
    //}

    // Flatten the map to a vector of strings
    for (auto const& e : orderMap)
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

void OrderBook::enterOrder(const std::string& product, double price, double amount, 
                           const std::string& timestamp, OrderBookType orderType) {
    // 1. Create a new OrderBookEntry
    OrderBookEntry newOrder{price, amount, timestamp, product, orderType}; 

    // 2. Add the new order to the orders vector
    orders.push_back(newOrder);

    // 3. Update the orderMap if necessary
    if (orderMap.find(product) == orderMap.end()) {
        // Product not found in the map, add it
        orderMap[product] = true;
    } // Otherwise, the product is already in the map, no need to update

    // 4. Sort the orders by timestamp
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}