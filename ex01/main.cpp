
#include "RPN.hpp"

int main(int ac, char *av[])
{
    if (ac != 2)
    {
        std::cerr << "Error: program need 1 argument" << std::endl;
        return 1;
    }

    const std::string arg = av[1];

    RPN r_p_n;

    r_p_n.process(arg);

    return 0;
}
