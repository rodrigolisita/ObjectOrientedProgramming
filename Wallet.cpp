#include "Wallet.h"
#include "CSVReader.h"

Wallet::Wallet(/* args */)
{
}

Wallet::~Wallet()
{
}

void Wallet::insertCurrency(std::string type, double amount){

    double balance;
    if(amount < 0)
    {
        throw std::exception{};
    }
    if(currencies.count(type) == 0 ) // Not there yet
    {
        balance = 0;
    }
    else{
        balance = currencies[type];
    }
    balance += amount;
    currencies[type] = balance;

}

bool Wallet::removeCurrency(std::string type, double amount){

    double balance;
    if(amount < 0)
    {
        return false;
    }
    if(currencies.count(type) == 0 ) // Not there yet
    {
        return false;
    }
    else{
        if(containsCurrency(type, amount))
        {
            currencies[type] -= amount;
            return true;
        }
        else // they have it but not enough
        {
            return false;
        }
    }
   
}

bool Wallet::containsCurrency(std::string type, double amount){

    if(currencies.count(type) == 0)
    {
        return false;
    }
    else{
        return currencies[type] >= amount;
    }
}

std::string Wallet::toString(){

    std::string s;
    for(std::pair<std::string,double> pair : currencies)
    {
        std::string currency = pair.first;
        double amount = pair.second;
        s += currency + " : " + std::to_string(amount) + "\n";
    }
    return s;
}

bool Wallet::canFulfillOrder(const std::string& product, double price, double amount, 
                            const std::string& timestamp, OrderBookType orderType) {
//bool canFulfillOrder(OrderbookEntry order){

    std::vector<std::string> currs = CSVReader::tokenise(product, '/');
    // ask
    if(orderType == OrderBookType::ask)
    {
        //double amount = order.amount;
        std::string currency = currs[0];
        std::cout << "Ask. Wallet:canFulfillOrder " << currency << " : " << amount << std::endl;
        return containsCurrency(currency,amount);
    }
    // bid
    if(orderType == OrderBookType::bid)
    {
        double amountT = amount * price;
        std::string currency = currs[1];
        std::cout << "Bid. Wallet:canFulfillOrder " << currency << " : " << amount << std::endl;
        return containsCurrency(currency, amountT);
    }
   
    return false;
} 