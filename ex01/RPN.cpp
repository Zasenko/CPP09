#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

void RPN::process(const std::string &arg)
{
    if (arg.empty()) throw std::logic_error("Empty argument");

    std::istringstream iss(arg);
    std::string token;
    while (iss >> token)
    {
        if (isOperator(token))
        {
            if (_stack.size() < 2) throw std::logic_error("Wrong numbers count");

            int n1 = _stack.top();
            _stack.pop();
            int n2 = _stack.top();
            _stack.pop();

            long result = 0;
            
            if (token == "/")
            {
                if (n1 == 0) throw std::logic_error("Can't devide by 0");
                result = static_cast<long>(n2) / static_cast<long>(n1);
            }
            else if (token == "-")
            {
                result = static_cast<long>(n2) - static_cast<long>(n1);
            }
            else if (token == "*")
            {
                result = static_cast<long>(n2) * static_cast<long>(n1);
            }
            else
            {
                result = static_cast<long>(n2) + static_cast<long>(n1);
            }
            if (result > INT_MAX) throw std::logic_error("Resut is very big number");
            if (result < INT_MIN) throw std::logic_error("Resut is very small number");
            _stack.push(result);
        }
        else
        {
            if (token.size() > 2) throw std::logic_error("Wrong argument");
            if (!isNumber(token)) throw std::logic_error("Wrong argument");

            int n = atoi(token.c_str());
            if (n < -9) throw std::logic_error("Number is smaller then 9");
            if (n > 9) throw std::logic_error("Number is bigger then 9");
            _stack.push(n);
        }
    }

    if (_stack.empty() || _stack.size() != 1) throw std::logic_error("Wrong numbers count");
    std::cout << _stack.top() << std::endl;
}

bool RPN::isOperator(const std::string &str)
{
    return str == "+" || str == "-" || str == "*" || str == "/";
}

bool RPN::isNumber(const std::string &token)
{
    if (token.empty()) return false;

    size_t start = 0;
    if (token[0] == '-') {
        if (token.size() == 1) return false;
        start = 1;
    }

    for (size_t i = start; i < token.size(); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(token[i])))
            return false;
    }
    return true;
}
