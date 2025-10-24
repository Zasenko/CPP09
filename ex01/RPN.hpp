#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>

class RPN {
    public:
        RPN();
        void process(const std::string &arg);
    private:
        RPN(const RPN &copy);
        ~RPN();
        RPN &operator=(const RPN &src);

        std::stack<int> _stack;

        bool isOperator(const std::string &str);

};

#endif
