#include "MerkelMain.h"
#include <vector>
#include <limits>   // Include limits header
#include <map>      // Include the map header
#include <functional>
#include <iomanip> // Include the iomanip header


#include "OrderBookEntry.h"
#include "CSVReader.h"


MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{
    // loadOrderBook();
    //int input;

    currentTime = orderBook.getEarliestTime();
    previousTime = currentTime;
    nextTime = orderBook.getNextTime(currentTime);




    std::string input;
    while(true)
    {

        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
    
}


// void MerkelMain::computeNumberOfBidsAsks(const std::vector<OrderBookEntry>& orders) 
// {
    // unsigned int ask=0;
    // unsigned int bid = 0;
// 
    // for (const OrderBookEntry& order : orders){
        // if(order.orderType == OrderBookType::bid){
            // bid++;
        // }
        // if(order.orderType == OrderBookType::ask){
        //    ask++;
        // }
        //  
    // }
// 
    // std::cout << "Numbers of bids: " << bid << std::endl;
    // std::cout << "Numbers of asks: " << ask << std::endl;
// 
// }

// double MerkelMain::computeAveragePrice(const std::vector<OrderBookEntry>& orders, OrderBookType orderType) {
    // 
    // double average = 0;
    // int count = 0;
// 
    // for (const OrderBookEntry& order : orders){
        // if(order.orderType == orderType){
            // average +=order.price;
            // count++;
        // }
        // 
    // }
    // if(count > 0){
        // return average/count;
    // } else {
        // return 0;
    // }
    // 
// }

// double MerkelMain::computeLowPrice(const std::vector<OrderBookEntry>& orders, OrderBookType orderType){
    // double val=std::numeric_limits<double>::max();
    // int count=0;
// 
    // for(const OrderBookEntry& order : orders){
        // if(order.orderType==orderType && val>order.price){
            // val=order.price;
            // count++;
        // }
    // }
    // if(count>0){
        // return val;
    // }else{
        // return 0;
    // }
    // 
// }

// double MerkelMain::computeHighPrice(const std::vector<OrderBookEntry>& orders, OrderBookType orderType){
    // double val=0;
    // int count = 0;
// 
    // for(const OrderBookEntry& order : orders){
        // if(order.orderType==orderType && val<order.price){
            // val=order.price;
            // count++;
        // }
    // }
    // if(count > 0){
        // return val;
    // }else{
        // return 0;
    // }
    // 
// }

// double MerkelMain::computePriceSpread(const std::vector<OrderBookEntry>& orders){
    // double ask=0.0;
    // double bid=0.0;
// 
    // bid = MerkelMain::computeHighPrice(orders, OrderBookType::bid);
    // ask = MerkelMain::computeLowPrice(orders, OrderBookType::ask);
// 
    // std::cout << "High bid: " << bid << " Lower ask: " << ask << std::endl;
// 
    // return (bid-ask);
// 
// 
// }



void MerkelMain::printMenu(){
    std::cout << "\n=================== " << std::endl;
    std::cout << "====== Menu ======= " << std::endl;
    // 1 print help
    std::cout << "1: Print help " << std::endl;

    // 2 print exhange stats
    std::cout << "2: Print exhange stats " << std::endl;
        
    // 3 make an offer
    std::cout << "3: Make a trade (ask or bid) " << std::endl;

    // 4 print wallet
    std::cout << "4: Print wallet " << std::endl;

    // 5 continue
    std::cout << "5: Continue " << std::endl;

    std::cout << "=================== " << std::endl;
    std::cout << "Current time: " << currentTime << std::endl;
    //std::cout << "Next time: " << nextTime << std::endl;
}

std::string MerkelMain::getUserOption(){
    std::string userOption;

    std::getline(std::cin, userOption);
    //std::cin >> userOption;
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

// Function to display market information and return max/min values
void MerkelMain::displayMarketInfo(const std::vector<OrderBookEntry>& entriesAsk, const std::vector<OrderBookEntry>& entriesBid,
                                   double& maxAsk, double& minAsk, double& maxBid, double& minBid) {
                                  
    maxAsk = OrderBook::getHighPrice(entriesAsk);
    minAsk = OrderBook::getLowPrice(entriesAsk);
    maxBid = OrderBook::getHighPrice(entriesBid);
    minBid = OrderBook::getLowPrice(entriesBid);

    // Set the width for each field
    int fieldWidth = 10;

     std::cout << std::left << std::setw(fieldWidth) << " " 
              << std::left << std::setw(fieldWidth) << "Asks: " + std::to_string(entriesAsk.size()) 
              << std::left << std::setw(fieldWidth) << "Bids: " + std::to_string(entriesBid.size()) << std::endl;
    
    std::cout << std::left << std::setw(fieldWidth) << "Max: " 
              << std::left << std::setw(fieldWidth) << maxAsk 
              << std::left << std::setw(fieldWidth) << maxBid << std::endl;
    
    std::cout << std::left << std::setw(fieldWidth) << "Min: " 
              << std::left << std::setw(fieldWidth) << minAsk
              << std::left << std::setw(fieldWidth) << minBid << std::endl;
    
    std::cout << std::left << std::setw(fieldWidth) << "Average: " 
              << std::left << std::setw(fieldWidth) << OrderBook::getAveragePrice(entriesAsk)
              << std::left << std::setw(fieldWidth) << OrderBook::getAveragePrice(entriesBid) << std::endl;

};

void MerkelMain::printExhangeStats(){
    printChar("Market stats....");
    std::cout << "==================================" << std::endl;

    double maxAsk, minAsk, maxBid, minBid; // Declare variables to store the values
    
    for (std::string const p : orderBook.getKnownProducts())
    {
        std::cout << "-------------------------------" << std::endl;
        std::cout << "Product " << p << std::endl;
        std::cout << "-------------------------------" << std::endl;
        std::vector<OrderBookEntry> entriesAsk = orderBook.getOrders(OrderBookType::ask, 
                                                                 p,
                                                                 currentTime);
        
        std::vector<OrderBookEntry> entriesBid = orderBook.getOrders(OrderBookType::bid, 
                                                         p,
                                                         currentTime);                                                                 

        displayMarketInfo(entriesAsk, entriesBid, maxAsk, minAsk, maxBid, minBid); 

    }

    // std::cout << "The price spred is: " << computePriceSpread(orders) << std::endl;
}

int getChoice()
{
    std::string schoice;
    int choice;
    std::cout << "Enter the number of the desired pair: ";
//    std::cin >> choice;
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer
    std::getline(std::cin, schoice);

    // Attempt to convert the string to an integer
    try {
        choice = std::stoi(schoice);
        // std::cout << "You entered the number: " << choice << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid input. Please enter a number for the pair." << std::endl;
    }
    return choice;
}

void MerkelMain::enterTrade(){
    printChar("Make a trade. Available pairs: ");

    bool validChoice = false;

    const std::vector<std::string>& products = orderBook.getKnownProducts();

    // Print the available pairs
    while(!validChoice){
    
        for (size_t i = 0; i < products.size(); ++i) {
            std::cout << i + 1 << ". " << products[i] << std::endl;
        }

        int choice = getChoice();
        if (choice >= 1 && choice <= products.size()) 
        {
            const std::string& selectedProduct = products[choice - 1]; 
            std::cout << "You choose the pair: " << selectedProduct << std::endl;

            //Ask for trade type (ask or bid)
            OrderBookType tradeType;
            std::string tradeTypeString;
            while(true){
                std::cout << "Enter trade type (ask/bid): ";
                std::getline(std::cin, tradeTypeString);
                if(tradeTypeString == "ask"){
                    tradeType = OrderBookType::ask;
                    break;
                }else if (tradeTypeString == "bid"){
                    tradeType = OrderBookType::bid;
                    break;
                } else {
                    std::cout << "Invalid trade type. Please enter 'ask' or 'bid'.\n";

                }
            }

            // Get orders for ask and bid regardless of the chosen trade type
            std::vector<OrderBookEntry> entriesAsk= orderBook.getOrders(OrderBookType::ask, 
                                                                     selectedProduct,
                                                                     currentTime);

            std::vector<OrderBookEntry> entriesBid = orderBook.getOrders(OrderBookType::bid, 
                                                                     selectedProduct,
                                                                     currentTime);

            double maxAsk, minAsk, maxBid, minBid; // Declare variables to store the values
            displayMarketInfo(entriesAsk, entriesBid, maxAsk, minAsk, maxBid, minBid); 

            double price, amount;
            std::string sprice, samount;

            std::cout << "Enter price: ";
            std::getline(std::cin, sprice);
            
            std::cout << "Enter amount: ";
            std::getline(std::cin, samount);

            // Attempt to convert the string to double
            try {
                price = std::stod(sprice);
                amount = std::stoi(samount);
                std::cout << "You entered the price: " << price << " and the amount of: " << amount << std::endl;
                
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid input. Please enter a number for price and amount." << std::endl;
                continue;
            }

            // Validate price and amount here
            if ( (price > 0.0) && amount > 0 ) {
                if(tradeType == OrderBookType::ask){
                    if ((price < maxAsk + 0.3*maxAsk) && (price > minAsk - 0.3*minAsk)){
                        validChoice = true;
                        //orderBook.enterAsk(selectedProduct, price, amount, currentTime);
                        orderBook.enterOrder(selectedProduct, price, amount, currentTime, OrderBookType::ask);

                        std::cout << "\nAsk order entered successfully!\n\n";
                    } else {
                        std::cout << "\nInvalid ask price. Please verify your value.\n";
                    }
                } else { //bid
                    if ((price < maxBid + 0.3*maxBid) && (price > minBid - 0.3*minBid)){
                        validChoice = true;
                        //orderBook.enterBid(selectedProduct, price, amount, currentTime);
                        orderBook.enterOrder(selectedProduct, price, amount, currentTime, OrderBookType::bid);
                        std::cout << "\nBid order entered successfully!\n\n";
                    } else {
                        std::cout << "\nInvalid bid price. Please verify your value.\n";
                    }
                }
                
                if(validChoice){
                    // Display updated market information
                    entriesAsk = orderBook.getOrders(OrderBookType::ask, selectedProduct, currentTime);
                    entriesBid = orderBook.getOrders(OrderBookType::bid, selectedProduct, currentTime);
                    
                    std::cout << "Updated trade market information " << std::endl;
                    displayMarketInfo(entriesAsk, entriesBid, maxAsk, minAsk, maxBid, minBid);

                }
            } else {
                std::cout << "Invalid price or amount. Please verify your values.\n";
            }
        } else {
            std::cout << "Invalid choice. Please select a valid pair number.\n";
        }
    }
}

void MerkelMain::printWallet(){
    printChar("4: Print wallet.");
}

void MerkelMain::goToNextTimeFrame(){
    printChar("5: Going to next time frame.");
    //std::cout << "Current time: " << currentTime << std::endl;
    //std::cout << "Next time: " << nextTime << std::endl;
    
    previousTime = currentTime;
    currentTime = orderBook.getNextTime(currentTime);
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
        {'3', &MerkelMain::enterTrade},
        {'4', &MerkelMain::printWallet},
        {'5', &MerkelMain::goToNextTimeFrame}
    };

    // Check if the input is valid and call the associated function
    if (userOption.length() == 1 && optionMap.count(userOption[0])) {
        optionMap[userOption[0]](this); // Call the function
    } else {
        std::cout << userOption << " is not a valid input. Please provide an input between 1 to 6 " << std::endl;
    }

}