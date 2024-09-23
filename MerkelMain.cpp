#include "MerkelMain.h"
#include <vector>
#include <limits>   // Include limits header
#include <map>      // Include the map header
#include <functional>

#include "OrderBookEntry.h"
#include "CSVReader.h"

MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{
    loadOrderBook();
    //int input;
    std::string input;
    while(true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
    
}

void MerkelMain::loadOrderBook()
{

    std::ifstream csvFile{"20200317.csv"};
    std::string line;
    std::vector<std::string> tokens;
    double price;
    double amount;

    if(csvFile.is_open())
    {
        std::cout << "File open " << std::endl;
        while(std::getline(csvFile, line))
        {
            std::cout << "Read line " << line << std::endl;
            tokens = CSVReader::tokenise(line, ',');
            if(tokens.size() != 5 ) // bad
            {
                std::cout << "Bad line " << std::endl;
                continue;
            }
            // We have 5 tokens
            try{
                price = std::stod(tokens[3]);
                amount = std::stod(tokens[4]);  
                // std::cout << price << ": " << amount << std::endl;

                orders.push_back(OrderBookEntry {price, 
                                                 amount,
                                                 tokens[0], 
                                                 tokens[1], 
                                                OrderBookEntry::stringToOrderBookType(tokens[2])});

            }catch(std::exception& e){
                std::cout << "Bad float! " << tokens[3] << std::endl;
                std::cout << "Bad float! " << tokens[4] << std::endl;
                continue;
            }

           

//            for(std::string& t : tokens){
//                std::cout << t << std::endl;
//            }
            
        }


        csvFile.close();
    }
    else{
        std::cout << "Could not open file " << std::endl;
    }
    
    for (OrderBookEntry& order : orders){
    //    std::cout << "The price is " << order.price << " for order type: " << OrderBookEntry::orderTypeToString(order.orderType)  <<  std::endl;
        std::cout << "The price is " << order.price <<  std::endl;
    }
}


double MerkelMain::computeAveragePrice(const std::vector<OrderBookEntry>& orders, OrderBookType orderType) {
    
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

double MerkelMain::computeLowPrice(const std::vector<OrderBookEntry>& orders, OrderBookType orderType){
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

double MerkelMain::computeHighPrice(const std::vector<OrderBookEntry>& orders, OrderBookType orderType){
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

double MerkelMain::computePriceSpread(const std::vector<OrderBookEntry>& orders){
    double ask=0.0;
    double bid=0.0;

    bid = MerkelMain::computeHighPrice(orders, OrderBookType::bid);
    ask = MerkelMain::computeLowPrice(orders, OrderBookType::ask);

    std::cout << "High bid: " << bid << " Lower ask: " << ask << std::endl;

    return (bid-ask);


}



void MerkelMain::printMenu(){
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

std::string MerkelMain::getUserOption(){
    std::string userOption;
    std::getline(std::cin, userOption);
    return userOption;
}

void MerkelMain::printChar(const std::string& inputString) {
    std::cout << inputString << std::endl;
}

void MerkelMain::printHelp(){
    //printMenu();
    std::cout << "Help - your aim is to make money." << std::endl;
    std::cout << "Analyse the market and make bids" << std::endl;
    std::cout << "and offers. " << std::endl;

}

void MerkelMain::printExhangeStats(){
    printChar("Market looks good.");

    std::cout << "OrderBook contains: " << orders.size() << " entries" << std::endl;

    std::cout << "The average price for bids is: " << computeAveragePrice(orders, OrderBookType::bid) << std::endl;
    std::cout << "The average price for asks is: " << computeAveragePrice(orders, OrderBookType::ask) << std::endl;
    std::cout << "The lower price for bids is: " << computeLowPrice(orders, OrderBookType::bid) << std::endl;
    std::cout << "The higher price for bids is: " << computeHighPrice(orders, OrderBookType::bid) << std::endl;
    std::cout << "The price spred is: " << computePriceSpread(orders) << std::endl;



}
void MerkelMain::enterOffer(){
    printChar("3: Make an offer.");
}

void MerkelMain::enterBid(){
    printChar("4: Make a bid.");
}

void MerkelMain::printWallet(){
    printChar("5: Print wallet.");
}

void MerkelMain::goToNextTimeFrame(){
    printChar("6: Going to next time frame.");
}

void MerkelMain::printSizes(){
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

void MerkelMain::processUserOption(const std::string& userOption){

    // Define a map to associate user input with functions
    // Use std::function to store member function pointers
    static std::map<char, std::function<void(MerkelMain*)>> optionMap={
        {'1', &MerkelMain::printHelp},
        {'2', &MerkelMain::printExhangeStats},
        {'3', &MerkelMain::enterOffer},
        {'4', &MerkelMain::enterBid},
        {'5', &MerkelMain::printWallet},
        {'6', &MerkelMain::goToNextTimeFrame}
    };

    // Check if the input is valid and call the associated function
    if (userOption.length() == 1 && optionMap.count(userOption[0])) {
        optionMap[userOption[0]](this); // Call the function
    } else {
        std::cout << userOption << " is not a valid input. Please provide an input between 1 to 6 " << std::endl;
    }

}