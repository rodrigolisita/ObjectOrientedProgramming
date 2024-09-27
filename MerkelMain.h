#include <iostream>
#include <string>   // Include the string header
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"

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
        void enterTrade(); // To sell something
        void enterBid(); // To buy something
        void printWallet();
        void goToNextTimeFrame();
        void printSizes();
        void processUserOption(const std::string& userOption);
        void displayMarketInfo(const std::vector<OrderBookEntry>& entriesAsk, const std::vector<OrderBookEntry>& entriesBid,
                           double& maxAsk, double& minAsk, double& maxBid, double& minBid);
        

        // std::vector<OrderBookEntry> orders;
        //OrderBook orderBook{"20200317.csv"};
        OrderBook orderBook{"test.csv"};
        //OrderBook orderBook{"testNoBid.csv"};
        //OrderBook orderBook{"testNoAsk.csv"};

        std::string currentTime;
        std::string nextTime;
        std::string previousTime;

        /**Output the number of bids and asks */
        void computeNumberOfBidsAsks(const std::vector<OrderBookEntry>& orders);

        /**Compute the average price */
        double computeAveragePrice(const std::vector<OrderBookEntry>& orders, OrderBookType orderType);

        /**Compute the lower price */
        double computeLowPrice(const std::vector<OrderBookEntry>& entries, OrderBookType orderType);

        /**Compute the price spread */
        double computePriceSpread(const std::vector<OrderBookEntry>& orders);

        /**Tokenise the input */
        //std::vector<std::string> tokenise(const std::string& line, char delimiter);

};

