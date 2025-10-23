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
        bool isDateValid(const std::string& date) const;
        bool isDigitsAndDot(const std::string& date) const;
        bool isDigitsAndDash(const std::string& date) const;
        bool isDigitsAndDotAndMinus(const std::string& date) const;
        double toDouble(const std::string& str) const;
};

#endif
