
#include "BitcoinExchange.hpp"

#include <string>
#include <cstdlib>

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
    
    try {

        BitcoinExchange exchange;
        exchange.makeSecond(fileName);

    }
    catch (const std::logic_error &e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;

    }
    catch (...) {
        std::cout << "Undefind. Error" << std::endl;
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



    // std::fstream file;
    // file.open("data.csv", std::fstream::in);
    // if (!file.is_open())
    // {
    //     std::cerr << "Error: Can't open the file " << "data.csv" << std::endl;
    //     return 1;
    // }

    // typedef std::map<std::string, double> my_DB;
    // my_DB db;
    // std::string line;

    // int f = 1;
    
    // while (std::getline(file, line))
    // {
    //     std::cout << "----------------" << std::endl;
    //     std::cout << "[" << line << "]" << std::endl;
        
    //     if (f)
    //     {
    //         if (line != "date,exchange_rate")
    //         {
    //             std::cerr << "Error: Incorrect db file data" << std::endl;
    //             file.close();
    //             return 1;
    //         }
    //         f = 0;
    //         continue;
    //     }

    //     std::string::iterator it = std::find(line.begin(), line.end(), ',');
    //     if (it == line.end())
    //     {
    //         std::cerr << "Error: Incorrect db file data (it == line.end())" << std::endl;
    //         file.close();
    //         return 1;
    //     }

    //     // key 2009-01-02

    //     std::string key(line.begin(), it);
        
    //     trim(key);
    //     std::cout << "key: [" << key << "]" << std::endl;

    //     if (key.empty() || key.size() != 10) {
    //         std::cerr << "Error: Incorrect db file data (key.empty() || key.size() != 10)" << std::endl;
    //         file.close();
    //         return 1;
    //     }

    //     if (!isValidDate(key))
    //     {
    //         std::cout << "Error: Incorrect db file date format (expecting YYYY-MM-DD)" << std::endl;
    //         file.close();
    //         return 1;
    //     }
      
    //     it++;
    //     if (it == line.end())
    //     {
    //         std::cerr << "Error: Incorrect db file data (it + 1 == line.end())" << std::endl;
    //         file.close();
    //         return 1;
    //     }

    //     // val

    //     std::string val(it, line.end());
    //     trim(val);
    //     if (val.empty()) {
    //         std::cerr << "Error: Incorrect db file data (key.empty())" << std::endl;
    //         file.close();
    //         return 1;
    //     }
        
    //     std::cout << "val: [" << val << "]" << std::endl;
    //     if (!isDigitsAndDot(val))
    //     {
    //         std::cout << "Error: Incorrect db file value format" << std::endl;
    //         file.close();
    //         return 1;
    //     }
    //     double v = toDouble(val);
    //     // TODO: check date!
    //     // TODO: check atoi overflow!
    //     // int val = atoi(str_val.c_str());
    //     db[key] = v;
    // }
    // if (file.bad())
    // {
    //     std::cerr << "Error: while reading file";
    //     file.close();
    //     return 1;
    // }
    // file.close();

    return 0;
}
