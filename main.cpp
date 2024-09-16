#include <iostream>

int main()
{
    while(true){
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

        int userOption;
        std::cin >> userOption;

        switch (userOption)
        {
        case 1:
            /* code */
            std::cout << "You chose: 1" << std::endl;
            break;
        case 2:
            /* code */
            std::cout << "You chose: 2" << std::endl;
            break;
        case 3:
            /* code */
            std::cout << "You chose: 3" << std::endl;
            break;
        case 4:
            /* code */
            std::cout << "You chose: 4" << std::endl;
            break;
        case 5:
            /* code */
            std::cout << "You chose: 5" << std::endl;
            break;
        case 6:
            /* code */
            std::cout << "You chose: 6" << std::endl;
            break;                                                            
        default:
            std::cout << "Not a valid input. Please provide an input between 1 to 6 " << std::endl;
            break;
        }
        // std::cout << "You chose: " << userOption << std::endl;
    }
    
    return 0;
}