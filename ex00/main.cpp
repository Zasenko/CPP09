
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <cstdlib>
#include <sstream>      // std::stringstream

#include <algorithm>

double toDouble(const std::string& str) {
    try {
        return std::stod(str);
    } catch (const std::invalid_argument&) {
        std::cerr << "Ошибка: строка не число: " << str << std::endl;
    } catch (const std::out_of_range&) {
        std::cerr << "Ошибка: слишком большое число: " << str << std::endl;
    }
    return 0.0;
}

void trim(std::string &s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");

    if (start == std::string::npos)
        s.clear();  // String contains only whitespace
    else
        s = s.substr(start, end - start + 1);
}

bool isDigitsAndDash(const std::string& date) {
    return date.find_first_not_of("0123456789-") == std::string::npos;
}

bool isValidDate(const std::string& date)
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



int main(int ac, char *av[])
{
    if (ac != 2)
    {
        std::cerr << "Error: program need 1 argument (exmpl: filename.txt)" << std::endl;
        return 1;
    }

    std::string fileName = av[1];
    if (fileName.empty())
    {
        std::cerr << "Error: file name is empty" << std::endl;
        return 1;
    }
    if (fileName.size() < 5)
    {
        std::cerr << "Error: incorrect file name" << std::endl;
        return 1;
    }
    if (fileName.substr(fileName.size() - 4) != ".txt")
    {
        std::cerr << "Error: incorrect file format (exmpl: filename.txt)" << std::endl;
        return 1;
    }
    
    // std::fstream file;
    // file.open(fileName.c_str(), std::fstream::in);
    // if (!file.is_open())
    // {
    //     std::cerr << "Error: Can't open the file " << fileName << std::endl;
    //     return 1;
    // }


    // typedef std::map<std::string, int> db_key_value;
    // db_key_value db;

    // std::string line;
    
    // while (std::getline(file, line))
    // {
    //     std::cout << "----------------" << std::endl;
    //     std::cout << "[" << line << "]" << std::endl;

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
    // }
    // file.close();

    // std::cout << "-------- ! --------" << std::endl;

    // for (db_key_value::const_iterator it = db.begin(); it != db.end(); it++)
    // {
    //     std::cout << "[" << it->first << "] [" << it->second << "]" << "\n";
    // }







    // e.txt

    // Each line in this file must use the following format: "date | value"
    // A valid date will always be in the following format: Year-Month-Day.
    // A valid value must be either a float or a positive integer, between 0 and 1000.

    // You must use at least one container in your code to validate this
    // exercise. You should handle possible errors with an appropriate
    // error message.

    // Your program will use the value in your input file.

    // Your program should display on the standard output the result of the value multiplied
    // by the exchange rate according to the date indicated in your database.

    // If the date used in the input does not exist in your DB then you
    // must use the closest date contained in your DB. Be careful to use the
    // lower date and not the upper one.

    // Warning: The container(s) you use to validate this exercise will no
    // longer be usable for the rest of this module.



    std::fstream file;
    file.open("data.csv", std::fstream::in);
    if (!file.is_open())
    {
        std::cerr << "Error: Can't open the file " << "data.csv" << std::endl;
        return 1;
    }

    typedef std::map<std::string, double> my_DB;
    my_DB db;
    std::string line;

    int f = 1;
    
    while (std::getline(file, line))
    {
        std::cout << "----------------" << std::endl;
        std::cout << "[" << line << "]" << std::endl;
        
        if (f)
        {
            if (line != "date,exchange_rate")
            {
                std::cerr << "Error: Incorrect db file data" << std::endl;
                file.close();
                return 1;
            }
            f = 0;
            continue;
        }

        std::string::iterator it = std::find(line.begin(), line.end(), ',');
        if (it == line.end())
        {
            std::cerr << "Error: Incorrect db file data (it == line.end())" << std::endl;
            file.close();
            return 1;
        }

        // key 2009-01-02

        std::string key(line.begin(), it - 1);
        
        trim(key);
        std::cout << "key: [" << key << "]" << std::endl;

        if (key.empty() || key.size() != 10) {
            std::cerr << "Error: Incorrect db file data (key.empty() || key.size() != 10)" << std::endl;
            file.close();
            return 1;
        }
        if (it + 1 == line.end())
        {
            std::cerr << "Error: Incorrect db file data (it + 1 == line.end())" << std::endl;
            file.close();
            return 1;
        }

        if (!isValidDate(key))
        {
            std::cout << "Error: Incorrect db file date format (expecting YYYY-MM-DD)" << std::endl;
            file.close();
            return 1;
        }
      
        // val

        std::string val(it + 1, line.end());
        trim(val);
        if (val.empty()) {
            std::cerr << "Error: Incorrect db file data (key.empty())" << std::endl;
            file.close();
            return 1;
        }
        
        std::cout << "val: [" << val << "]" << std::endl;

        double v = toDouble(val);
        // TODO: check date!
        // TODO: check atoi overflow!
        // int val = atoi(str_val.c_str());
        db[key] = v;
    }
    if (file.bad())
    {
        std::cerr << "Error: while reading file";
        file.close();
        return 1;
    }
    file.close();

    std::cout << "-------- ! --------" << std::endl;

    for (my_DB::const_iterator it = db.begin(); it != db.end(); it++)
    {
        std::cout << "[" << it->first << "] [" << it->second << "]" << "\n";
    }

    return 0;
}
