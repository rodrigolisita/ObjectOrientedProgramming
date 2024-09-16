#include <iostream>
#include <string>   // Include the string header
#include <map>      // Include the map header

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


int main()
{
    while(true){

        printMenu(); //Menu options

        std::string userOption = getUserOption(); // Get the user input

        processUserOption(userOption); // Process the user input
       
       
    }
    
    
    return 0;
}

