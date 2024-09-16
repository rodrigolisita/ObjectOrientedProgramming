#include <iostream>
#include <string> // Include the string header

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
    printMenu();
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

    switch (userOption[0])
    {
    case '1':
        printHelp();
        break;
    case '2':
        printExhangeStats();
        break;
    case '3':
        enterOffer();
        break;
    case '4':
        enterBid();
        break;
    case '5':
        printWallet();
        break;
    case '6':
        goToNextTimeFrame();
        break;                                                            
    default:
        std::cout << userOption << " is not a valid input. Please provide an input between 1 to 6 " << std::endl;
        break;
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

