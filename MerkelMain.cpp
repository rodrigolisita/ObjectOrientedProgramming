#include "MerkelMain.h"


#include <map>      // Include the map header
#include <functional> 

MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{
    //int input;
    std::string input;
    while(true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
    
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