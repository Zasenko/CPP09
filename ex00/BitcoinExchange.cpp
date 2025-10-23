#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
    createDB();
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::createDB()
{
    std::fstream file;
    file.open("data.csv", std::fstream::in);
    if (!file.is_open()) throw std::logic_error("BitcoinExchange: Can't open the file data.csv");

    std::string line;
    int isFirstLine = 1;
    
    while (std::getline(file, line))
    {
        // std::cout << "----------------" << std::endl;
        // std::cout << "[" << line << "]" << std::endl;
        
        if (isFirstLine)
        {
            if (line != "date,exchange_rate")
            {
                file.close();
                throw std::logic_error("BitcoinExchange: Incorrect data in data.csv");
            }
            isFirstLine = 0;
            continue;
        }

        std::string::iterator it = std::find(line.begin(), line.end(), ',');
        if (it == line.end())
        {
            file.close();
            throw std::logic_error("BitcoinExchange: Incorrect data in data.csv");
        }

        std::string key(line.begin(), it);
        
        trim(key);
        std::cout << "key: [" << key << "]" << std::endl;

        if (key.empty() || key.size() != 10) {
            file.close();
            throw std::logic_error("BitcoinExchange: Incorrect data in data.csv");
        }

        if (!isDateValid(key))
        {
            file.close();
            throw std::logic_error("BitcoinExchange: Incorrect date format in data.csv");
        }
      
        it++;
        if (it == line.end())
        {
            file.close();
            throw std::logic_error("BitcoinExchange: Incorrect data in data.csv");
        }

        // val

        std::string valueStr(it, line.end());
        trim(valueStr);
        if (valueStr.empty()) {
            file.close();
            throw std::logic_error("BitcoinExchange: Incorrect data in data.csv");
        }
        
        std::cout << "val: [" << valueStr << "]" << std::endl;
        if (!isDigitsAndDot(valueStr))
        {
            file.close();
            throw std::logic_error("BitcoinExchange: Incorrect data in data.csv");
        }
        double value = toDouble(valueStr);
        _db[key] = value;
    }
    if (file.bad())
    {
        file.close();
        throw std::logic_error("BitcoinExchange: Error while reading file data.csv");
    }
    file.close();
}

void BitcoinExchange::makeSecond(const std::string &fileName) const {

    std::fstream file;
    file.open(fileName.c_str(), std::fstream::in);
    if (!file.is_open()) throw std::logic_error("BitcoinExchange: Can't open the file " + fileName);

    DataBase db2;

    std::string line;
    int isFirstLine = 1;
    
    std::string line;
    
    while (std::getline(file, line))
    {
        std::cout << "----------------" << std::endl;
        std::cout << "[" << line << "]" << std::endl;



    //     std::string key, delim, str_val, rest;

    //     std::stringstream ss(line);

    //     ss >> key >> delim >> str_val >> rest; // rest if more then 4!

    //     if (delim != "|" || !rest.empty())
    //     {
    //         std::cerr << "Error: !!!!!!!!!!!" << std::endl;
    //         return 1;
    //     }
    //     std::cout << "[" << key << "] [" << delim << "] [" << str_val << "]" << "\n";

    //     // TODO: check date!
    //     // TODO: check atoi overflow!
    //     int val = atoi(str_val.c_str());
    //     db[key] = val;
    // }
    // if (file.bad())
    // {
    //     std::cerr << "Error: while reading file";
    //     file.close();
    //     return 1;
    }
    if (file.bad())
    {
        file.close();
        throw std::logic_error("BitcoinExchange: Error while reading file " + fileName);
    }
    file.close();
}

void BitcoinExchange::trim(std::string &s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");

    if (start == std::string::npos)
        s.clear();
    else
        s = s.substr(start, end - start + 1);
}

bool BitcoinExchange::isDigitsAndDash(const std::string& date) {
    return date.find_first_not_of("0123456789-") == std::string::npos;
}

bool BitcoinExchange::isDigitsAndDot(const std::string& date) {
    return date.find_first_not_of("0123456789.") == std::string::npos;
}

bool BitcoinExchange::isDateValid(const std::string& date)
{

    if (!isDigitsAndDash(date))return false;
    int year, month, day;

    if (std::sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day) != 3)
        return false;

    //todo bitcoin date!
    if (month < 1 || month > 12 || day < 1) return false;
    if (day < 1 || day > 31) return false;

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    bool isLeap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    if (isLeap)
    {
        daysInMonth[1] = 29;
    }

    if (day > daysInMonth[month - 1])
    {
        return false;
    }

    return true;
}

double BitcoinExchange::toDouble(const std::string& str) {
    char *endptr = NULL;
    double d = std::strtod(str.c_str(), &endptr);

    std::cout << "double: ";
    if (std::isnan(d)) {
        std::cout << "nan" << std::endl;
    } else if (std::isinf(d)) {
        std::cout << (d > 0 ? "+inf" : "-inf") << std::endl;
    } else {  
        std::cout << d << std::endl;
    }
    return d;
}
