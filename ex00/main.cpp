
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
    
    try
    {
        BitcoinExchange exchange;
        exchange.makeSecond(fileName);
    }
    catch (const std::logic_error &e)
    {
        std::cerr << "Error: BitcoinExchange: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;

    }
    catch (...)
    {
        std::cerr << "Undefined Error!" << std::endl;
        return 1;
    }
    return 0;
}
