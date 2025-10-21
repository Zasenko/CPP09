
#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <sstream>      // std::stringstream

#include <algorithm>


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

    typedef std::map<std::string, int> my_DB;
    my_DB db;
    std::string line;

    int f = 0;
    
    while (std::getline(file, line))
    {
        std::cout << "----------------" << std::endl;
        std::cout << "[" << line << "]" << std::endl;
        
        if (!f)
        {
            if (line != "date,exchange_rate")
            {
                std::cerr << "Error: Incorrect db file data" << std::endl;
                file.close();
                return 1;
            }
            f = 1;
            continue;
        }

        std::string::iterator it = std::find(line.begin(), line.end(), ',');
        if (it == line.end())
        {
            std::cerr << "Error: Incorrect db file data" << std::endl;
            file.close();
            return 1;
        }

        std::string key(line.begin(), it - 1);
        
        std::cout << "key: [" << key << "]" << std::endl;

        if (it + 1 == line.end())
        {
            std::cerr << "Error: Incorrect db file data" << std::endl;
            file.close();
            return 1;
        }
        std::string val(it + 1, line.end());
        std::cout << "val: [" << val << "]" << std::endl;

        // TODO: check date!
        // TODO: check atoi overflow!
        // int val = atoi(str_val.c_str());
        // db[key] = val;
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
