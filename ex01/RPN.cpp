#include "RPN.hpp"

RPN::RPN() {

}

RPN::~RPN() {
    
}

void RPN::process(const std::string &arg)
{
    if (arg.empty())
    {
        std::cerr << "arg.empty()" << std::endl;
        return;
    }

    std::istringstream iss(arg);
    std::string token;
    while (iss >> token)
    {
        if (isOperator(token))
        {
            if (_stack.size() < 2)
            {
                std::cerr << "_stack.size() < 2" << std::endl;
                return;
            }

            int n1 = _stack.top();
            _stack.pop();
            int n2 = _stack.top();
            _stack.pop();

            // TODO: overflow
            long result;

            if (token == "/")
            {
                if (n1 == 0)
                {
                    std::cerr << "n1 == 0" << std::endl;
                    return;
                }
                result = n2 / n1;
                _stack.push(result);
            }
            else if (token == "-")
            {
                result = n2 - n1;
                _stack.push(result);
            }
            else if (token == "*")
            {
                result = n2 * n1;
                _stack.push(result);
            }
            else
            {
                result = n2 + n1;
                _stack.push(result);
            }
        }
        else
        {
            if (token.size() > 2)
            {
                std::cerr << "token.size() > 2" << std::endl;
                return;
            }

            //check - , digits

            // std::string::const_iterator it = arg.begin();
            int n = atoi(token.c_str());
            if (n < -9 || n > 9)
            {
                std::cerr << "n < -9 || n > 9" << std::endl;
                return;
            }
            _stack.push(n);

        }

    }

    if (_stack.empty() || _stack.size() != 1)
    {
        std::cerr << "_stack.empty() || _stack.size() != 1" << std::endl;
        return;
    }

    std::cout << _stack.top() << std::endl;

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
