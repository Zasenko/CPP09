#include "RPN.hpp"

RPN::RPN() {}


void RPN::process(const std::string &arg)
{
    if (arg.empty())
    {

    }

    std::istringstream iss(arg);
    std::string token;
    while (iss >> token)
    {
        if (isOperator(token))
        {
            if (_stack.size() < 2)
            {

            }

            int n1 = _stack.top();
            _stack.pop();
            int n2 = _stack.top();
            _stack.pop();

            if (token == "/")
            {
                if (n1 == 0)
                {
                    
                }
                _stack.push(n2 / n1);
            }
            else if (token == "-")
            {
                _stack.push(n2 - n1);
            }
            else if (token == "*")
            {
                _stack.push(n2 * n1);
            }
            else
            {
                _stack.push(n2 - n1);
            }



            //check if in stack

        }
        else
        {
            if (token.size() > 2)
            {

            }

        }

    }

    // std::string::const_iterator it = arg.begin();

    // for ( ; it != arg.end(); it++)
    // {
    //     if (*it == ' ' || *it == '\t' || *it == '\r')
    //     {
    //         it++;
    //     } else if (std::isdigit(*it)) {
            
    //     }

    // }

}

bool RPN::isOperator(const std::string &str)
{
    return str == "+" || str == "-" || str == "*" || str == "/";
}
