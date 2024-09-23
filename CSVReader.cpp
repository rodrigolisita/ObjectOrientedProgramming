#include "CSVReader.h"
#include <iostream>



CSVReader::CSVReader(/* args */)
{
}

CSVReader::~CSVReader()
{
}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string fileToOpen)
{
    std::vector<OrderBookEntry> orders;

    std::ifstream csvFile{fileToOpen};
    std::string line;
    std::vector<std::string> tokens;
    double price;
    double amount;

    if(csvFile.is_open())
    {
        std::cout << "File open " << std::endl;
        while(std::getline(csvFile, line))
        {
            // std::cout << "Read line " << line << std::endl;
            tokens = CSVReader::tokenise(line, ',');
            if(tokens.size() != 5 ) // bad
            {
                // std::cout << "Bad line " << std::endl;
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
                                                OrderBookEntry::stringToOrderBookType(tokens[2])});

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

    return orders;

}

std::vector<std::string> CSVReader::tokenise(const std::string& line, char delimiter) {
    
    std::vector<std::string> tokens;

    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}