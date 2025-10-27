#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <cstdlib>
#include <climits>


class RPN {
    public:
        RPN();
        ~RPN();
        void process(const std::string &arg);
    private:
        RPN(const RPN &copy);
        RPN &operator=(const RPN &src);

        std::stack<int> _stack;

        bool isOperator(const std::string &str);
        bool isNumber(const std::string &token);
};

#endif
