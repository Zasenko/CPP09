#include "PmergeMe.hpp"

size_t binarySearch(const vec &sorted, int value, int &count)
{
    if (sorted.empty())
        return 0;

    size_t left = 0;
    size_t right = sorted.size();
    
    while (left < right)
    {
        count++;
        size_t mid = left + (right - left) / 2;
        if (sorted[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

std::vector<size_t> buildJacobOrder2(size_t n)
{
    std::vector<size_t> order;
    if (n == 0) return order;
    
    // Generate Jacobsthal numbers up to n
    std::vector<size_t> jacob;
    jacob.push_back(1);
    jacob.push_back(3);
    
    while (jacob.back() < n)
    {
        size_t next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
        jacob.push_back(next);
    }
    
    // Build insertion order
    order.push_back(0); // First element is always at index 0
    
    for (size_t i = 0; i < jacob.size(); i++)
    {
        size_t j = jacob[i];
        if (j < n) order.push_back(j);
        
        // Add numbers between previous Jacobsthal numbers
        if (i > 0)
        {
            size_t prev = jacob[i - 1];
            for (size_t k = j - 1; k > prev; k--)
            {
                if (k < n) order.push_back(k);
            }
        }
    }
    
    return order;
}

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
    int count = 0;

    clock_t vectorStart = clock();
    vec vectorResult = sortVector(_v, count);
    clock_t vectorEnd = clock();

    std::cout << "After: ";
    for (size_t i = 0; i < vectorResult.size(); i++)
        std::cout << vectorResult[i] << " ";
    std::cout << std::endl;
    
    double vectorElapsed = double(vectorEnd - vectorStart) / CLOCKS_PER_SEC;
    std::cout << "Time elapsed: " << vectorElapsed << " seconds" << std::endl;

        std::cout << "Count: " << count << std::endl;


    // clock_t dequeStart = clock();
    // vec vectorResult = sortVector(_v);
    // clock_t dequeEnd = clock();

    // double dequeElapsed = double(dequeEnd - dequeStart) / CLOCKS_PER_SEC;
    // std::cout << "Time elapsed: " << dequeElapsed << " seconds" << std::endl;

}

vec PmergeMe::sortVector(const vec &vector, int &count)
{
    size_t vectorSize = vector.size();
    if (vectorSize < 2) return vector;
    
    pairVec pCont;

    for (size_t i = 0; i < vectorSize; )
    {
        vec pair;
        if (i + 1 < vectorSize)
        {
            count++;
            if (vector[i] < vector[i + 1])
            {
                pair.push_back(vector[i]);
                pair.push_back(vector[i + 1]);
            }
            else
            {
                pair.push_back(vector[i + 1]);
                pair.push_back(vector[i]);
            }
            i++;
            i++;
        }
        else
        {
            pair.push_back(vector[i]);
            i++;
        }
        pCont.push_back(pair);
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

    big = sortVector(big, count);
    insertPendVector(big, pend, count);
    if (hasRest)
    {
        size_t position = binarySearch(big, rest, count);
        std::cout << "hasRest insert at position: " << position << ", value: " << rest << std::endl;
        big.insert(big.begin() + position, rest);
    }
    return big;
}

void PmergeMe::insertPendVector(vec &sorted, const vec &pend, int &count)
{
    if (pend.empty())
        return;
        
    std::vector<size_t> jacobOrder2 = buildJacobOrder2(pend.size());

    std::cout << "Jacobsthal order: ";
    for (size_t i = 0; i < jacobOrder2.size(); i++)
        std::cout << jacobOrder2[i] << " ";
    std::cout << std::endl;

    for (size_t i = 0; i < jacobOrder2.size(); i++)
    {
        size_t idx = jacobOrder2[i];
        if (idx >= pend.size())
            continue;

        int value = pend[idx];
        size_t pos = 0;

        // Оптимизация: вставка в начало или конец без бинарного поиска
        if (sorted.empty() || value <= sorted.front())
            pos = 0;
        else if (value >= sorted.back())
            pos = sorted.size();
        else if (i < 3)
        {
            for (pos = 0; pos < sorted.size(); pos++)
            {
                if (value < sorted[pos])
                    break;
            }
        }
        else
            pos = binarySearch(sorted, value, count);

        std::cout << "Insert pend[" << idx << "] = " << value << " at position " << pos << std::endl;
        sorted.insert(sorted.begin() + pos, value);
    }
}

// deq PmergeMe::sortDeque(const deq &d)
// {
//     (void)d;
// }

// --- INSERT ---


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
