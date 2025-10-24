#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <cmath>
#include <sstream>      // std::stringstream

typedef std::map<std::string, double> DataBase;

class BitcoinExchange {
    public:
        BitcoinExchange();
        ~BitcoinExchange();
        // DataBase _db;
        void makeSecond(const std::string &fileName) const;

    private:
        BitcoinExchange(const BitcoinExchange &copy);
        BitcoinExchange &operator=(const BitcoinExchange &src);

        DataBase _db;
        void createDB();

        void trim(std::string &s) const;
        bool isDateValid(const std::string &str) const;
        bool isDigitsAndDot(const std::string &str) const;
        bool isDigitsAndDash(const std::string &str) const;
        bool isStringDoubleCorrect(const std::string &str) const;
        double toDouble(const std::string& str) const;
};

#endif
