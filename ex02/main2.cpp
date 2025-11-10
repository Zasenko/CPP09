#include "PmergeMe.hpp"

int main(int ac, char *av[])
{
    try
    {
        PmergeMe pmergeMe(ac, av);
        pmergeMe.sort();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
