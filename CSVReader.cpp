#include "CSVReader.h"
#include <iostream>

CSVReader::CSVReader(){

}

CSVReader::std::vector<OrderBookEntry> readCSV(std::string csvFile){

    std::ifstream csvFile{"20200317.csv"};
    std::string line;
    std::vector<std::string> tokens;
    double price;
    double amount;

    if(csvFile.is_open())
    {
        std::cout << "File open " << std::endl;
        while(std::getline(csvFile, line))
        {
            std::cout << "Read line " << line << std::endl;
            tokens = tokenise(line, ',');
            if(tokens.size() != 5 ) // bad
            {
                std::cout << "Bad line " << std::endl;
                continue;
            }
            // We have 5 tokens
            try{
                price = std::stod(tokens[3]);
                amount = std::stod(tokens[4]);  
                // std::cout << price << ": " << amount << std::endl;

                orders.push_back(OrderBookEntry {price, 
                                                 amount,
                                                 tokens[0], 
                                                 tokens[1], 
                                                stringToOrderBookType(tokens[2])});

            }catch(std::exception& e){
                std::cout << "Bad float! " << tokens[3] << std::endl;
                std::cout << "Bad float! " << tokens[4] << std::endl;
                continue;
            }

           

//            for(std::string& t : tokens){
//                std::cout << t << std::endl;
//            }
            
        }


        csvFile.close();
    }
    else{
        std::cout << "Could not open file " << std::endl;
    }
    std::vector<OrderBookEntry> entries;
    return entries;

}

CSVReader::std::vector<std::string> tokenise(const std::string& line, char delimiter){
    
    std::vector<std::string> tokens;
    return tokens;

}
CSVReader::OrderBookEntry stringsToOBE(std::vector<std::string> tokens){
    
    double price;
    double amount;

    if(tokens.size() != 5 ) // bad
    {
        std::cout << "Bad line " << std::endl;
        throw std::expection{};
    }
    // We have 5 tokens
    try{
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);  
        // std::cout << price << ": " << amount << std::endl;

    }catch(const std::exception& e){
        std::cout << "Bad float! " << tokens[3] << std::endl;
        std::cout << "Bad float! " << tokens[4] << std::endl;
        throw;
    }

    OrderBookEntry {price, 
                    amount,
                    tokens[0], 
                    tokens[1], 
                    stringToOrderBookType(tokens[2])
                    };

   
}
