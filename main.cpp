#include <iostream>
#include <string>   // Include the string header
//#include <map>      // Include the map header
#include <vector>
#include <limits>   // Include limits header

#include "OrderBookEntry.h"
#include "MerkelMain.h"

/**Compute the average price */
//double computeAveragePrice(const std::vector<OrderBookEntry>& entries, OrderBookType orderType);
double computeAveragePrice(const std::vector<OrderBookEntry>& orders, OrderBookType orderType);


/**Compute the lower price */
double computeLowPrice(const std::vector<OrderBookEntry>& entries, OrderBookType orderType);

/**Compute the higher price */
double computeHighPrice(const std::vector<OrderBookEntry>& entries, OrderBookType orderType);

/**Compute the price spread */
double computePriceSpread(const std::vector<OrderBookEntry>& orders);

double computeAveragePrice(const std::vector<OrderBookEntry>& orders, OrderBookType orderType) {
    
    double average = 0;
    int count = 0;

    for (const OrderBookEntry& order : orders){
        if(order.orderType == orderType){
            average +=order.price;
            count++;
        }
        
    }
    if(count > 0){
        return average/count;
    } else {
        return 0;
    }
    
}

double computeLowPrice(const std::vector<OrderBookEntry>& orders, OrderBookType orderType){
    double val=std::numeric_limits<double>::max();
    int count=0;

    for(const OrderBookEntry& order : orders){
        if(order.orderType==orderType && val>order.price){
            val=order.price;
            count++;
        }
    }
    if(count>0){
        return val;
    }else{
        return 0;
    }
    
}

double computeHighPrice(const std::vector<OrderBookEntry>& orders, OrderBookType orderType){
    double val=0;
    int count = 0;

    for(const OrderBookEntry& order : orders){
        if(order.orderType==orderType && val<order.price){
            val=order.price;
            count++;
        }
    }
    if(count > 0){
        return val;
    }else{
        return 0;
    }
    
}

double computePriceSpread(const std::vector<OrderBookEntry>& orders){
    double ask=0.0;
    double bid=0.0;

    bid = computeHighPrice(orders, OrderBookType::bid);
    ask = computeLowPrice(orders, OrderBookType::ask);

    std::cout << "High bid: " << bid << " Lower ask: " << ask << std::endl;

    return (bid-ask);


}

std::string orderTypeToString(OrderBookType type) {
    switch (type) {
        case OrderBookType::bid: return "bid";
        case OrderBookType::ask: return "ask";
        // Add more cases if you extend your OrderBookType enum
        default: return "unknown"; // Handle unexpected values
    }
}

int main()
{

    std::vector<OrderBookEntry> orders;

    orders.push_back(OrderBookEntry {1000, 
                                     0.02,
                                    "2020/03/17 17:01:24.884492", 
                                    "BTC/USDT", 
                                    OrderBookType::bid});

    orders.push_back(OrderBookEntry {1200, 
                                     0.02,
                                "2020/03/17 17:01:24.884492", 
                                "BTC/USDT", 
                                OrderBookType::bid});
    
    for (OrderBookEntry& order : orders){
        std::cout << "The price is " << order.price << " for order type: " << orderTypeToString(order.orderType)  <<  std::endl;
    }
    
    std::cout << "The average price for bids is: " << computeAveragePrice(orders, OrderBookType::bid) << std::endl;
    std::cout << "The average price for asks is: " << computeAveragePrice(orders, OrderBookType::ask) << std::endl;
    std::cout << "The lower price for bids is: " << computeLowPrice(orders, OrderBookType::bid) << std::endl;
    std::cout << "The higher price for bids is: " << computeHighPrice(orders, OrderBookType::bid) << std::endl;
    std::cout << "The price spred is: " << computePriceSpread(orders) << std::endl;
    

    MerkelMain app{};
    app.init();

    return 0;
}

