#include <iostream>
#include <string>   // Include the string header
#include <vector>
#include "OrderBookEntry.h"

class MerkelMain
{
    public:
        MerkelMain();
        /** Call this to start the simulation */
        void init();
    private:
        void loadOrderBook();
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

        std::vector<OrderBookEntry> orders;

        /**Compute the average price */
        double computeAveragePrice(const std::vector<OrderBookEntry>& orders, OrderBookType orderType);

        /**Compute the lower price */
        double computeLowPrice(const std::vector<OrderBookEntry>& entries, OrderBookType orderType);

        /**Compute the higher price */
        double computeHighPrice(const std::vector<OrderBookEntry>& entries, OrderBookType orderType);

        /**Compute the price spread */
        double computePriceSpread(const std::vector<OrderBookEntry>& orders);

        /**Tokenise the input */
        //std::vector<std::string> tokenise(const std::string& line, char delimiter);

};