#include "PmergeMe.hpp"

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(int ac, char *av[])
{
    if (ac < 2) throw std::logic_error("Program need minimum 1 number");

    for (int i = 1; i < ac; i++)
    {
        std::string arg = av[i];
        if (arg.length() == 0)
            throw std::logic_error("Empty argument");
        trim(arg);
        if (arg.length() == 0)
            throw std::logic_error("Empty argument");
        if (!isNumber(arg))
            throw std::logic_error("Wrong argument: " + arg);
        if (arg.length() > 11)
            throw std::logic_error("Wrong argument: " + arg);
        long num = std::atol(arg.c_str());
        if (num > INT_MAX)
            throw std::logic_error("Very big number: " + arg);
        if (num < 0)
            throw std::logic_error("Negative number: " + arg);

        _v.push_back(num);
        _d.push_back(num);
    }

    std::cout << "Before: ";
    for (size_t i = 0; i < _v.size(); i++) std::cout << _v[i] << " ";
    std::cout << std::endl;
}

void PmergeMe::sort()
{
    // --- Vector ---
    clock_t vStart = clock();
    vec vSorted = sortVector(_v);
    clock_t vEnd = clock();

    std::cout << "After: ";
    for (size_t i = 0; i < vSorted.size(); i++)
        std::cout << vSorted[i] << " ";
    std::cout << std::endl;

    double vTime = double(vEnd - vStart) / CLOCKS_PER_SEC * 1e6;
    std::cout << std::fixed << std::setprecision(5)
              << "Time to process a range of " << _v.size()
              << " elements with std::vector: " << vTime << " us" << std::endl;

    // --- Deque ---
    clock_t dStart = clock();
    deq dSorted = sortDeque(_d);
    clock_t dEnd = clock();

    double dTime = double(dEnd - dStart) / CLOCKS_PER_SEC * 1e6;
    std::cout << std::fixed << std::setprecision(5)
              << "Time to process a range of " << _d.size()
              << " elements with std::deque: " << dTime << " us" << std::endl;
}

// --- Vector ---

vec PmergeMe::sortVector(const vec &vector)
{
    size_t vectorSize = vector.size();
    if (vectorSize < 2) return vector;

    pairVec pCont = makePairs(vector);
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
    insertPendVector(big, pend);
    if (hasRest)
    {
        size_t position = binarySearch(big, rest);
        big.insert(big.begin() + position, rest);
    }
    return big;
}

pairVec PmergeMe::makePairs(const vec &v)
{
    pairVec pCont;
    for (size_t i = 0; i < v.size();)
    {
        vec pair;
        if (i + 1 < v.size())
        {
            if (v[i] < v[i + 1])
            {
                pair.push_back(v[i]);
                pair.push_back(v[i + 1]);
            }
            else
            {
                pair.push_back(v[i + 1]);
                pair.push_back(v[i]);
            }
            i += 2;
        }
        else
        {
            pair.push_back(v[i]);
            i++;
        }
        pCont.push_back(pair);
    }
    return pCont;
}

void PmergeMe::insertPendVector(vec &sorted, const vec &pend)
{
    if (pend.empty())
        return;

    vec jacobOrder = buildJacobOrder<vec>(pend.size());
    std::vector<bool> inserted(pend.size(), false);
    for (size_t i = 0; i < jacobOrder.size(); i++)
    {
        size_t idx = jacobOrder[i];
        if (idx >= pend.size() || inserted[idx])
            continue;
        size_t value = pend[idx];
        size_t pos = 0;
        if (sorted.empty())
            pos = 0;
        else
        {
            if (value <= sorted.front())
                pos = 0;
            else if (value >= sorted.back())
                pos = sorted.size();
            else
                pos = binarySearch(sorted, value);
        } 
        if (pos > sorted.size())
            pos = sorted.size();
        sorted.insert(sorted.begin() + pos, value);
        inserted[idx] = true;
    }
}

// --- Deque ---

deq PmergeMe::sortDeque(const deq &deque)
{
    size_t deqSize = deque.size();
    if (deqSize < 2)
        return deque;

    pairDeq pCont = makePairs(deque);
    deq big;
    deq pend;
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
    big = sortDeque(big);
    insertPendDeque(big, pend);
    if (hasRest)
    {
        size_t position = binarySearch(big, rest);
        big.insert(big.begin() + position, rest);
    }
    return big;
}

pairDeq PmergeMe::makePairs(const deq &v)
{
    pairDeq pCont;
    for (size_t i = 0; i < v.size();)
    {
        deq pair;
        if (i + 1 < v.size())
        {
            if (v[i] < v[i + 1])
            {
                pair.push_back(v[i]);
                pair.push_back(v[i + 1]);
            }
            else
            {
                pair.push_back(v[i + 1]);
                pair.push_back(v[i]);
            }
            i += 2;
        }
        else
        {
            pair.push_back(v[i]);
            i++;
        }
        pCont.push_back(pair);
    }
    return pCont;
}

void PmergeMe::insertPendDeque(deq &sorted, const deq &pend)
{
    if (pend.empty())
        return;

    deq jacobOrder = buildJacobOrder<deq>(pend.size());
    std::vector<bool> inserted(pend.size(), false);
    for (size_t i = 0; i < jacobOrder.size(); i++)
    {
        size_t idx = jacobOrder[i];
        if (idx >= pend.size() || inserted[idx])
            continue;
        size_t value = pend[idx];
        size_t pos = 0;
        if (sorted.empty())
            pos = 0;
        else
        {
            if (value <= sorted.front())
                pos = 0;
            else if (value >= sorted.back())
                pos = sorted.size();
            else
                pos = binarySearch(sorted, value);
        }
        if (pos > sorted.size())
            pos = sorted.size();
        sorted.insert(sorted.begin() + pos, value);
        inserted[idx] = true;
    }
}

// --- Utils ---

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
