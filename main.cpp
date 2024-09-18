#include <iostream>
#include <string>   // Include the string header
#include <map>      // Include the map header
#include <vector>
#include <limits>   // Include limits header


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

/**Compute the average price */
//double computeAveragePrice(const std::vector<OrderBookEntry>& entries, OrderBookType orderType);
double computeAveragePrice(const std::vector<OrderBookEntry>& orders, OrderBookType orderType);


/**Compute the lower price */
double computeLowPrice(const std::vector<OrderBookEntry>& entries, OrderBookType orderType);

/**Compute the higher price */
double computeHighPrice(const std::vector<OrderBookEntry>& entries, OrderBookType orderType);

/**Compute the price spread */
double computePriceSpread(const std::vector<OrderBookEntry>& orders);



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

void printMenu(){
    std::cout << "\n=================== " << std::endl;
    std::cout << "====== Menu ======= " << std::endl;
    // 1 print help
    std::cout << "1: Print help " << std::endl;

    // 2 print exhange stats
    std::cout << "2: Print exhange stats " << std::endl;
        
    // 3 make an offer
    std::cout << "3: Make an offer " << std::endl;

    // 4 make a bid
    std::cout << "4: Make a bid " << std::endl;

    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;

    // 6 continue
    std::cout << "6: Continue " << std::endl;

    std::cout << "=================== " << std::endl;
    std::cout << "Type in 1-6: ";
}

std::string getUserOption(){
    std::string userOption;
    std::getline(std::cin, userOption);
    return userOption;
}

void printChar(const std::string& inputString) {
    std::cout << inputString << std::endl;
}

void printHelp(){
    //printMenu();
    std::cout << "Help - your aim is to make money." << std::endl;
    std::cout << "Analyse the market and make bids" << std::endl;
    std::cout << "and offers. " << std::endl;

}

void printExhangeStats(){
    printChar("Market looks good.");
}
void enterOffer(){
    printChar("3: Make an offer.");
}

void enterBid(){
    printChar("4: Make a bid.");
}

void printWallet(){
    printChar("5: Print wallet.");
}

void goToNextTimeFrame(){
    printChar("6: Going to next time frame.");
}

void printSizes(){
    char c=0;
    std::cout << "char: " << sizeof(c) << std::endl;

    signed int i = 0;
    std::cout << "signed int: " << sizeof(i) << std::endl;

    float f=0.0f;
    std::cout << "float: " << sizeof(f) << std::endl;

    long double d=0.0;
    std::cout << "long double: " << sizeof(d) << std::endl;

    bool b = 0;
    std::cout << "boolean: " << sizeof(b) << std::endl;
}

void processUserOption(const std::string& userOption){

    // Define a map to associate user input with functions
    static std::map<char, void(*)()> optionMap={
        {'1', printHelp},
        {'2', printExhangeStats},
        {'3', enterOffer},
        {'4', enterBid},
        {'5', printWallet},
        {'6', goToNextTimeFrame}
    };

    // Check if the input is valid and call the associated function
    if (userOption.length() == 1 && optionMap.count(userOption[0])) {
        optionMap[userOption[0]](); // Call the function
    } else {
        std::cout << userOption << " is not a valid input. Please provide an input between 1 to 6 " << std::endl;
    }

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
    


    while(true){

        printMenu(); //Menu options

        std::string userOption = getUserOption(); // Get the user input

        processUserOption(userOption); // Process the user input
       
       
    }
    
    
    return 0;
}

