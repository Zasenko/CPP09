
#include "PmergeMe.hpp"

void trim(std::string &s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");

    if (start == std::string::npos)
        s.clear();
    else
        s = s.substr(start, end - start + 1);
}


bool isNumber(const std::string &str)
{
    if (str.empty()) return false;

    size_t start = 0;
    if (str[0] == '-') {
        if (str.size() == 1) return false;
        start = 1;
    }

    for (size_t i = start; i < str.size(); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(str[i])))
            return false;
    }
    return true;
}

int main(int ac, char *av[])
{
    if (ac < 3)
    {
        std::cerr << "Error: program need minimum 2 numbers to sort" << std::endl;
        return 1;
    }

    for (int i = 1; i < ac; i++)
    {
        //check number
        std::string arg = av[i];
        if (arg.length() == 0) {
            std::cerr << "Error: empty argument" << std::endl;
            return 1;
        }
        trim(arg);
        if (arg.length() == 0) {
            std::cerr << "Error: empty argument" << std::endl;
            return 1;
        }
        if (!isNumber(arg)) {
            std::cerr << "Error: " << arg << " wrong argument" << std::endl;
            return 1;
        }

        if (arg.length() > 11) {
            std::cerr << "Error: " << arg << " wrong argumen" << std::endl;
            return 1;
        }

        long num = std::atol(arg.c_str());
        if (num > INT_MAX) {
            std::cerr << "Error: " << arg << " too big number" << std::endl;
            return 1;
        }
        if (num < INT_MIN) {
            std::cerr << "Error: " << arg << " too small number" << std::endl;
            return 1;
        }

        std::cerr << "num " << i << ": " << num << std::endl;
    }

    return 0;
}
