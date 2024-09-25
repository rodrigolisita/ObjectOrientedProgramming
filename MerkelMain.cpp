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
    std::cout << "3: Make an Ask " << std::endl;

    // 4 make a bid
    std::cout << "4: Make a bid " << std::endl;

    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;

    // 6 continue
    std::cout << "6: Continue " << std::endl;

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

void MerkelMain::printExhangeStats(){
    printChar("Market stats....");
    std::cout << "==================================" << std::endl;

    for (std::string const p : orderBook.getKnownProducts())
    {
        std::cout << "Product " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, 
                                                                 p,
                                                                 currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
        std::cout << "Average ask: " << OrderBook::getAveragePrice(entries) << std::endl;
        std::cout << "==================================" << std::endl;

    }

    //std::cout << "OrderBook contains: " << orderBook.size() << " entries" << std::endl;
    //OrderBook::returnOrderSize();


    // computeNumberOfBidsAsks(orders);
    // std::cout << "The average price for bids is: " << computeAveragePrice(orders, OrderBookType::bid) << std::endl;
    // std::cout << "The average price for asks is: " << computeAveragePrice(orders, OrderBookType::ask) << std::endl;
    // std::cout << "The lower price for bids is: " << computeLowPrice(orders, OrderBookType::bid) << std::endl;
    // std::cout << "The higher price for bids is: " << computeHighPrice(orders, OrderBookType::bid) << std::endl;
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
        std::cout << "You entered the number: " << choice << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid input. Please enter a number for the pair." << std::endl;
    }
    return choice;
}

void MerkelMain::enterAsk(){
    printChar("Make an ask. Available pairs: ");

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
            // validChoice = true;
            
            const std::string& selectedProduct = products[choice - 1]; 

            std::cout << "You choose the pair: " << selectedProduct << std::endl;

            // prompt for price and amount, validate, and call orderBook.enterAsk)
            std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, 
                                                                     selectedProduct,
                                                                     currentTime);

            double maxAsk = OrderBook::getHighPrice(entries);
            double minAsk = OrderBook::getLowPrice(entries);
            std::cout << "Max ask: " << maxAsk << std::endl;
            std::cout << "Min ask: " << minAsk << std::endl;
            std::cout << "Average ask: " << OrderBook::getAveragePrice(entries) << std::endl;

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
            if ( (price > 0.0) && (price < maxAsk + 0.3*maxAsk) && (price > minAsk - 0.3*minAsk) && amount > 0 ) {
                
                validChoice = true;
                
                orderBook.enterAsk(selectedProduct, price, amount, currentTime);
 
                std::cout << "Ask order entered successfully!\n";

                // Display updated market information
                std::vector<OrderBookEntry> updatedEntries = orderBook.getOrders(OrderBookType::ask, selectedProduct, currentTime);
                std::cout << "Updated Max ask: " << OrderBook::getHighPrice(updatedEntries) << std::endl;
                std::cout << "Updated Min ask: " << OrderBook::getLowPrice(updatedEntries) << std::endl;
                std::cout << "Updated Average ask: " << OrderBook::getAveragePrice(updatedEntries) << std::endl;

            } else {
                std::cout << "Invalid price or amount. Please verify your values.\n";
            }

        } else {
            std::cout << "Invalid choice. Please select a valid pair number.\n";
        }
    }

  

    // std::string input;
// 
    // std::vector<std::string> availablePairs;
    // unsigned int counter = 0;
    // unsigned int pairNumber;
    // bool validChoice = false;
// 
    // double value;
    // double amount;
// 
    // for (std::string const p : orderBook.getKnownProducts())
    // {
        // availablePairs.push_back(p);
        // std::cout << counter++ << ": " << p << std::endl;
    // }
// 
    // while(!validChoice){
        // std::cout << "Choose desired pair number: ";
        // std::cin >> pairNumber;
////        Check if the pair is valid:
        // if(pairNumber < counter)
        // {
            // validChoice = true;
        // }
    // }
    // std::cout << "You choose the pair: " << availablePairs[pairNumber] << std::endl;
// 
    // std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, 
                                                        //  availablePairs[pairNumber],
                                                        //  currentTime);
// 
    // std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
    // std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
    // std::cout << "Average ask: " << OrderBook::getAveragePrice(entries) << std::endl;
    // 
    // 
    // std::cout << "Enter value: ";
    // std::cin >> value;
// 
    // std::cout << "Enter amount: ";
    // std::cin >> amount;
    // 
    // std::cout << "Your ask: amount = " << amount << " value = " << value << std::endl;
// 
    // OrderBook::enterOrder(value, amount, currentTime, availablePairs[pairNumber], "ask");

}

void MerkelMain::enterBid(){
    printChar("4: Make a bid.");
}

void MerkelMain::printWallet(){
    printChar("5: Print wallet.");
}

void MerkelMain::goToNextTimeFrame(){
    printChar("6: Going to next time frame.");
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
        {'3', &MerkelMain::enterAsk},
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