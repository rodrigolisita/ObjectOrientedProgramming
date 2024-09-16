#include <iostream>
#include <string> // Include the string header

void printChar(const std::string& inputString) {
    std::cout << "You entered " << inputString << std::endl;
}

int main()
{
    while(true){

        std::cout << "=================== " << std::endl;
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

        //int userOption;
        std::string userOption;
        // std::cin >> userOption;
        std::getline(std::cin, userOption);

        switch (userOption[0])
        {
        case '1':
            /* code */
            printChar("Help - choose options from the menu\nand follow the on screen instructions.");
            break;
        case '2':
            /* code */
            printChar("2: Print exhange stats");
            break;
        case '3':
            /* code */
            printChar("3: Make an offer ");
            break;
        case '4':
            /* code */
            printChar("4: Make a bid ");
            break;
        case '5':
            /* code */
            printChar("5: Print wallet");
            break;
        case '6':
            /* code */
            printChar("6: Continue");
            break;                                                            
        default:
            std::cout << userOption << " is not a valid input. Please provide an input between 1 to 6 " << std::endl;
            break;
        }
        // std::cout << "You chose: " << userOption << std::endl;
    }
    std::cout << "=====================" << std::endl;
    
    return 0;
}

