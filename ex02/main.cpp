#include "PmergeMe.hpp"
#include <ctime>

vec algor(const vec &cont, int &count);
std::vector<size_t> buildJacobOrder(size_t n);

void trim(std::string &s)
{
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");

    if (start == std::string::npos)
        s.clear();
    else
        s = s.substr(start, end - start + 1);
}

bool isNumber(const std::string &str)
{
    if (str.empty())
        return false;
    for (size_t i = 0; i < str.size(); i++)
    {
        if (!std::isdigit(static_cast<unsigned char>(str[i])))
            return false;
    }
    return true;
}

size_t binarySearch(vec &arr, int x, int &count)
{

    if (arr.empty())
        return 0;

    size_t left = 0;
    size_t right = arr.size();

    while (left < right)
    {
        size_t mid = left + (right - left) / 2;

        count++;

        if (arr[mid] < x)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
    return left;
}

std::vector<size_t> buildJacobOrder(size_t n)
{
    std::vector<size_t> order;
    if (n == 0)
        return order;

    // Генерация чисел Якобсталя
    std::vector<size_t> J;
    J.push_back(0); // J0
    J.push_back(1); // J1

    while (true)
    {
        size_t next = J[J.size() - 1] + 2 * J[J.size() - 2];
        if (next >= n)
            break;
        J.push_back(next);
    }

    std::vector<bool> used(n, false);

    // Вставляем элементы по Jacobsthal
    for (size_t k = 0; k < J.size(); k++)
    {
        size_t idx = J[k];
        if (idx < n && !used[idx])
        {
            order.push_back(idx);
            used[idx] = true;
        }
    }

    // Добавляем оставшиеся элементы по возрастанию
    for (size_t i = 0; i < n; i++)
    {
        if (!used[i])
        {
            order.push_back(i);
            used[i] = true;
        }
    }

    return order;
}

void insertPendByJacobsthal2(vec &sorted, const vec &pend, int &count)
{
    std::cout << "= insertPendByJacobsthal2 =" << std::endl;

    if (pend.empty())
        return;

    std::vector<size_t> jacobOrder = buildJacobOrder(pend.size());

    std::cout << "Jacobsthal order: ";
    for (size_t i = 0; i < jacobOrder.size(); i++)
        std::cout << jacobOrder[i] << " ";
    std::cout << std::endl;

    for (size_t i = 0; i < jacobOrder.size(); ++i)
    {
        size_t idx = jacobOrder[i];
        if (idx >= pend.size())
        {
            std::cerr << "Warning: index " << idx << " out of bounds for pend size " << pend.size() << std::endl;
            continue;
        }

        int value = pend[idx];
        size_t pos = 0;

        // Оптимизация: вставка в начало или конец без бинарного поиска
        if (sorted.empty() || value <= sorted.front())
        {
            pos = 0;
        }
        else if (value >= sorted.back())
        {
            pos = sorted.size();
        }
        else
        {
            // бинарный поиск только в "среднем диапазоне"
            size_t leftBound = 1;
            size_t rightBound = sorted.size() - 1;

            size_t left = leftBound;
            size_t right = rightBound;

            while (left < right)
            {
                size_t mid = left + (right - left) / 2;
                count++; // считаем сравнение
                std::cout << "-> count ++ :" << count << std::endl;
                ;
                if (sorted[mid] < value)
                    left = mid + 1;
                else
                    right = mid;
            }
            pos = left;
        }

        std::cout << "Insert pend[" << idx << "] = " << value << " at position " << pos << std::endl;
        sorted.insert(sorted.begin() + pos, value);
    }
}

int main(int ac, char *av[])
{
    if (ac < 2)
    {
        std::cerr << "Error: program need minimum 1 number to sort" << std::endl;
        return 1;
    }

    int count = 0;

    vec cont;

    for (int i = 1; i < ac; i++)
    {
        // check number
        std::string arg = av[i];
        if (arg.length() == 0)
        {
            std::cerr << "Error: empty argument" << std::endl;
            return 1;
        }
        trim(arg);
        if (arg.length() == 0)
        {
            std::cerr << "Error: empty argument" << std::endl;
            return 1;
        }
        if (!isNumber(arg))
        {
            std::cerr << "Error: " << arg << " wrong argument" << std::endl;
            return 1;
        }

        if (arg.length() > 11)
        {
            std::cerr << "Error: " << arg << " wrong argumen" << std::endl;
            return 1;
        }

        long num = std::atol(arg.c_str());
        if (num > INT_MAX)
        {
            std::cerr << "Error: " << arg << " too big number" << std::endl;
            return 1;
        }
        if (num < INT_MIN)
        {
            std::cerr << "Error: " << arg << " too small number" << std::endl;
            return 1;
        }
        cont.push_back(num);
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "size " << cont.size() << std::endl;

    clock_t start = clock();

    vec result = algor(cont, count);
    clock_t end = clock();

    std::cout << "FINAL: ";
    for (size_t i = 0; i < result.size(); i++)
    {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Final count:" << count << std::endl;

    double elapsed = double(end - start) / CLOCKS_PER_SEC;
std::cout << "Time elapsed: " << elapsed << " seconds" << std::endl;
    return 0;
}

vec algor(const vec &cont, int &count)
{
    std::cout << std::endl
              << "-- RECURSION --" << std::endl;

    if (cont.size() < 2)
    {
        std::cout << "END RECURSION" << std::endl;
        for (size_t i = 0; i < cont.size(); i++)
        {
            std::cout << cont[i] << " ";
        }
        std::cout << std::endl;
        return cont;
    }
    pairCont pCont;

    for (size_t i = 0; i < cont.size();)
    {

        vec pc;

        if (i + 1 < cont.size())
        {
            count++;
            if (cont[i] < cont[i + 1])
            {
                pc.push_back(cont[i]);
                pc.push_back(cont[i + 1]);
            }
            else
            {
                pc.push_back(cont[i + 1]);
                pc.push_back(cont[i]);
            }
            i++;
            i++;
        }
        else
        {
            pc.push_back(cont[i]);
            i++;
        }
        pCont.push_back(pc);
    }

    for (size_t i = 0; i < pCont.size(); i++)
    {
        std::cout << "[ ";

        for (size_t z = 0; z < pCont[i].size(); z++)
        {
            std::cout << pCont[i][z] << " ";
        }
        std::cout << "] ";
    }
    std::cout << std::endl;

    vec big;
    vec pend;
    int rest = 0;
    bool hasRest = false;

    for (size_t i = 0; i < pCont.size(); i++)
    {
        if (pCont[i].size() == 1)
        {
            hasRest = true;
            rest = pCont[i][0];
        }
        else
        {
            pend.push_back(pCont[i][0]);
            big.push_back(pCont[i][1]);
        }
    }

    std::string hrs = hasRest ? "rest: " : "no rest:";
    std::cout << hrs << rest << std::endl;

    for (size_t i = 0; i < big.size(); i++)
    {
        std::cout << big[i] << " ";
    }
    std::cout << std::endl;

    big = algor(big, count);
    
    insertPendByJacobsthal2(big, pend, count);

    if (hasRest)
    {
        size_t pos = 0;
        if (rest <= big.front())
        {
            pos = 0;
        }
        else if (rest >= big.back())
        {
            pos = big.size();
        }
        else
        {
            // бинарный поиск только в "среднем диапазоне"
            size_t leftBound = 1;
            size_t rightBound = big.size() - 1;
            size_t left = leftBound;
            size_t right = rightBound;

            while (left < right)
            {
                size_t mid = left + (right - left) / 2;
                count++; // считаем сравнение
                if (big[mid] < rest)
                    left = mid + 1;
                else
                    right = mid;
            }
            pos = left;
        }

        std::cout << "hasRest insert at position: " << pos << ", value: " << rest << std::endl;
        big.insert(big.begin() + pos, rest);
    }

    // вывод
    for (size_t i = 0; i < big.size(); i++)
        std::cout << big[i] << " ";
    std::cout << std::endl;
    return big;
}
