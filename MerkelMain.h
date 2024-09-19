#include <iostream>
#include <string>   // Include the string header

class MerkelMain
{
    public:
        MerkelMain();
        /** Call this to start the simulation */
        void init();
        void printMenu();
        std::string getUserOption();
        void printChar(const std::string& inputString);
        void printHelp();
        void printExhangeStats();
        void enterOffer();
        void enterBid();
        void printWallet();
        void goToNextTimeFrame();
        void printSizes();
        void processUserOption(const std::string& userOption);
};