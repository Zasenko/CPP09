
#include <iostream>

int main(int ac, char *av[])
{
    if (ac != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }
    std::string fileName = av[1];

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
    return 0;
}