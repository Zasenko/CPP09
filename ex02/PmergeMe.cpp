#include "PmergeMe.hpp"


PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(int ac, char *av[])
{
    if (ac < 2) throw std::logic_error("Program need minimum 1 number");

    for (int i = 1; i < ac; i++)
    {
        std::string arg = av[i];
        if (arg.length() == 0) throw std::logic_error("Empty argument");
        trim(arg);
        if (arg.length() == 0) throw std::logic_error("Empty argument");
        if (!isNumber(arg)) throw std::logic_error("Wrong argument: " + arg);
        if (arg.length() > 11) throw std::logic_error("Wrong argument: " + arg);
        long num = std::atol(arg.c_str());
        if (num > INT_MAX) throw std::logic_error("Very big number: " + arg);
        if (num < 0) throw std::logic_error("Negative number: " + arg);

        _v.push_back(num);
        _d.push_back(num);
    }

    std::cout << "Before: ";
    for (size_t i = 0; i < _v.size(); i++)
    {
        std::cout << _v[i] << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::sort()
{
    clock_t start = clock();
    vec result = sortVector(_v);
    clock_t end = clock();


    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time elapsed: " << elapsed << " seconds" << std::endl;
    
}

vec PmergeMe::sortVector(const vec &vector)
{
    size_t vectorSize = vector.size();
    if (vectorSize < 2) return vector;
    
    pairVec pCont;

    for (size_t i = 0; i < vectorSize; )
    {

        vec pc;
        if (i + 1 < vectorSize)
        {
            if (vector[i] < vector[i + 1])
            {
                pc.push_back(vector[i]);
                pc.push_back(vector[i + 1]);
            }
            else
            {
                pc.push_back(vector[i + 1]);
                pc.push_back(vector[i]);
            }
            i++;
            i++;
        }
        else
        {
            pc.push_back(vector[i]);
            i++;
        }
        pCont.push_back(pc);
    }

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

    big = sortVector(big);
    
//     insertPendByJacobsthal2(big, pend, count);

//     if (hasRest)
//     {
//         size_t pos = 0;
//         if (rest <= big.front())
//         {
//             pos = 0;
//         }
//         else if (rest >= big.back())
//         {
//             pos = big.size();
//         }
//         else
//         {
//             // бинарный поиск только в "среднем диапазоне"
//             size_t leftBound = 1;
//             size_t rightBound = big.size() - 1;
//             size_t left = leftBound;
//             size_t right = rightBound;

//             while (left < right)
//             {
//                 size_t mid = left + (right - left) / 2;
//                 count++; // считаем сравнение
//                 if (big[mid] < rest)
//                     left = mid + 1;
//                 else
//                     right = mid;
//             }
//             pos = left;
//         }

//         std::cout << "hasRest insert at position: " << pos << ", value: " << rest << std::endl;
//         big.insert(big.begin() + pos, rest);
//     }

//     // вывод
//     for (size_t i = 0; i < big.size(); i++)
//         std::cout << big[i] << " ";
//     std::cout << std::endl;
//     return big;
}

void sortDeque()
{
    
}

// --- INSERT ---

void PmergeMe::insertPendVector(vec &sorted, const vec &pend)
{
    if (pend.empty())
        return;
        
    std::vector<size_t> jacobOrder = buildJacobOrder(pend.size());

    // std::cout << "Jacobsthal order: ";
    // for (size_t i = 0; i < jacobOrder.size(); i++)
    //     std::cout << jacobOrder[i] << " ";
    // std::cout << std::endl;

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
                // std::cout << "-> count ++ :" << count << std::endl;
                if (sorted[mid] < value)
                    left = mid + 1;
                else
                    right = mid;
            }
            pos = left;
        }

        // std::cout << "Insert pend[" << idx << "] = " << value << " at position " << pos << std::endl;
        sorted.insert(sorted.begin() + pos, value);
    }
}

std::vector<size_t> PmergeMe::buildJacobOrder(size_t n)
{
    std::vector<size_t> order;
    std::vector<size_t> jNums;
    std::vector<bool> used(n, false);

    if (n == 0)
        return order;

    jNums.push_back(0);
    jNums.push_back(1);

    while (true)
    {
        size_t next = jNums[jNums.size() - 1] + 2 * jNums[jNums.size() - 2];
        if (next >= n)
            break;
        jNums.push_back(next);
    }
    for (size_t k = 0; k < jNums.size(); k++)
    {
        size_t idx = jNums[k];
        if (idx < n && !used[idx])
        {
            order.push_back(idx);
            used[idx] = true;
        }
    }
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


// --- UTILS ---

void PmergeMe::trim(std::string &s)
{
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");

    if (start == std::string::npos)
        s.clear();
    else
        s = s.substr(start, end - start + 1);
}

bool PmergeMe::isNumber(const std::string &str)
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
