#include <iostream>
#include <string>   // Include the string header
//#include <map>      // Include the map header
#include <vector>
#include <limits>   // Include limits header
#include "OrderBookEntry.h"
#include "MerkelMain.h"

int main()
{

    MerkelMain app{};
    app.init();

    // Wallet wallet;
    // wallet.insertCurrency("BTC", 10);
    // wallet.insertCurrency("USDT", 1000);
    // 
    // std::cout << wallet.toString() << std::endl;
// 
    // wallet.removeCurrency("USDT", 100);
    // std::cout << wallet.toString() << std::endl;

    return 0;
}

