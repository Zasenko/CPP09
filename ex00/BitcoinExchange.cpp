#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    createDB();
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::createDB()
{
    std::fstream file;
    file.open("data.csv", std::fstream::in);
    if (!file.is_open()) throw std::logic_error("Can't open the file data.csv");

    std::string line;
    int isFirstLine = 1;

    while (std::getline(file, line))
    {
        trim(line);
        if (isFirstLine)
        {
            if (line != "date,exchange_rate")
                throw std::logic_error("Incorrect header in data.csv");
            isFirstLine = 0;
            continue;
        }
        std::string::iterator it = std::find(line.begin(), line.end(), ',');
        if (it == line.end())
            throw std::logic_error("Incorrect data in data.csv: " + line);
        std::string key(line.begin(), it);
        if (key.empty() || key.size() != 10)
            throw std::logic_error("Incorrect date in data.csv: " + line);
        if (!isDateValid(key))
            throw std::logic_error("Incorrect date in data.csv: " + line);
        it++;
        if (it == line.end())
            throw std::logic_error("Incorrect value in data.csv: " + line);
        std::string valueStr(it, line.end());
        if (valueStr.empty())
            throw std::logic_error("Incorrect value in data.csv: " + line);
        if (!isDigitsAndDot(valueStr))
            throw std::logic_error("Incorrect value in data.csv: " + line);

        if (!isStringDoubleCorrect(valueStr))
        {
            std::cerr << "Error: bad input => " << valueStr << std::endl;
            continue;
        }
        double value;
        try
        {
            value = toDouble(valueStr);
        }
        catch (const std::logic_error &e)
        {
            throw std::logic_error(std::string("Incorrect value in data.csv: ") + e.what());
        }
        if (value < 0)
        {
            throw std::logic_error("not a positive number in data.csv: " + line);
        }
        _db[key] = value;
    }
    if (file.bad())
        throw std::logic_error("reading file data.csv failed");
    file.close();
    if (_db.empty())
        throw std::logic_error("data Base from data.csv is empty");
}

void BitcoinExchange::exchange(const std::string &fileName) const
{

    std::fstream file;
    file.open(fileName.c_str(), std::fstream::in);
    if (!file.is_open()) throw std::logic_error("Can't open the file " + fileName);


    std::string line;
    bool isFirstLine = true;
        
    while (std::getline(file, line))
    {
        trim(line);
        if (line.empty())
            continue;

        if (isFirstLine)
        {
            size_t headerDelimPosition = line.find('|');
            if (headerDelimPosition == std::string::npos)
                throw std::logic_error("bad header in file " + fileName + ": " + line);

            std::string headerKey = line.substr(0, headerDelimPosition);
            std::string headerVal = line.substr(headerDelimPosition + 1);

            trim(headerKey);
            trim(headerVal);

            if (headerKey.empty() || headerKey != "date" || headerVal.empty() || headerVal != "value")
                throw std::logic_error("bad header in file " + fileName + ": " + line);

            isFirstLine = false;
            continue;
        }

        size_t delimPosition = line.find('|');
        if (delimPosition == std::string::npos)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string key = line.substr(0, delimPosition);
        std::string valueStr = line.substr(delimPosition + 1);

        trim(key);
        trim(valueStr);

        if (key.empty())
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (valueStr.empty())
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        if (!isDateValid(key))
        {
            std::cerr << "Error: bad input => " << key << std::endl;
            continue;
        }

        if (!isStringDoubleCorrect(valueStr))
        {
            std::cerr << "Error: bad input => " << valueStr << std::endl;
            continue;
        }

        if (isMoreThanThousand(valueStr))
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        double value;
        try
        {
            value = toDouble(valueStr);
        }
        catch (const std::logic_error &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            continue;
        }

        if (value < 0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000)
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        DataBase::const_iterator it = _db.lower_bound(key);
        if (it == _db.end())
        {
            --it;
        }
        else if (it->first != key)
        {
            if (it != _db.begin())
                --it;
        }

        double rate = it->second;
        double result = rate * value;

        std::cout << key << " => " << value << " = " << result << std::endl;
    }
    if (file.bad())
        throw std::logic_error("reading file " + fileName + " failed" );
    file.close();
    if (isFirstLine)
        throw std::logic_error("File " + fileName + " is empty");
}

void BitcoinExchange::trim(std::string &s) const {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");

    if (start == std::string::npos)
        s.clear();
    else
        s = s.substr(start, end - start + 1);
}

bool BitcoinExchange::isDigitsAndDash(const std::string& str) const
{
    if (str.size() != 10) return false;
    return str.find_first_not_of("0123456789-") == std::string::npos;
}

bool BitcoinExchange::isDigitsAndDot(const std::string &str) const
{
    return str.find_first_not_of("0123456789.") == std::string::npos;
}

bool BitcoinExchange::isStringDoubleCorrect(const std::string &str) const
{
    bool dotFound = false;

    size_t i = 0;
    
     if (str[i] == '-')
        i++;
    
    if (!std::isdigit(str[i]))
        return false;
    for (; i < str.size(); i++)
    {
        if (str[i] == '.')
        {
            if (dotFound)
                return false;
            dotFound = true;
            if (i + 1 >= str.size()) return false;
        }
        else if (!std::isdigit(str[i]))
            return false;
    }
    return true;
}

bool BitcoinExchange::isMoreThanThousand(const std::string &str) const
{
    std::string::size_type pos = str.find('.');
    std::string intPart;

    if (pos == std::string::npos)
    {
        intPart = str;
        while (intPart.size() > 1 && intPart[0] == '0')
            intPart.erase(0, 1);
        if (intPart.size() > 4)
            return true;
        if (intPart.size() < 4)
            return false;
        return intPart > "1000";
    }
    else
    {
        intPart = str.substr(0, pos);
        while (intPart.size() > 1 && intPart[0] == '0')
            intPart.erase(0, 1);
        if (intPart.size() > 4)
            return true;
        if (intPart.size() < 4)
            return false;

        if (intPart > "1000")
            return true;
        if (intPart == "1000")
        {
            std::string restPart = str.substr(pos + 1, str.size() - 1); //?? overflow
            for (size_t i = 0; i < restPart.size(); i++)
            {
                if (restPart[i] > '0')
                    return true;
            }
        }
        return false;
    }
}

bool BitcoinExchange::isDateValid(const std::string& date) const
{

    if (!isDigitsAndDash(date))return false;
    
    int year, month, day;

    if (std::sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day) != 3)
        return false;

    if (month < 1 || month > 12) return false;
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

    std::time_t t = std::time(NULL);
    std::tm *now = std::localtime(&t);
    int curYear = now->tm_year + 1900;
    int curMonth = now->tm_mon + 1;
    int curDay = now->tm_mday;

    if (year < 2009)
        return false;
    if (year == 2009)
    {
        if (month < 1)
            return false;
        if (month == 1 && day < 2)
            return false;
    }

    if (year > curYear)
        return false;
    if (year == curYear)
    {
        if (month > curMonth)
            return false;
        if (month == curMonth && day > curDay)
            return false;
    }

    return true;
}

double BitcoinExchange::toDouble(const std::string& str) const
{
    char *endptr = NULL;
    double d = std::strtod(str.c_str(), &endptr);

    if (std::isnan(d) || std::isinf(d)) {
        throw std::logic_error("number NaN or infinity");
    }  
    return d;
}
