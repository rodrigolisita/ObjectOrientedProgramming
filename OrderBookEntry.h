#include <string>

enum class OrderBookType{bid, ask};

class OrderBookEntry
{
    public:
    /** Create a new OrderBookEntry with the price
    * set to the sent value
    */
    OrderBookEntry(double _price, 
                   double _amount, 
                   std::string _timestamp, 
                   std::string _product, 
                   OrderBookType _orderType);
    double price;
    double amount;
    std::string timestamp;
    std::string product;  // Corrected member variable name
    OrderBookType orderType;   

     double getPrice();


};
