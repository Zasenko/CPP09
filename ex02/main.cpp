
#include "PmergeMe.hpp"

vec algor(const vec &cont);

void trim(std::string &s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");

    if (start == std::string::npos)
        s.clear();
    else
        s = s.substr(start, end - start + 1);
}


bool isNumber(const std::string &str)
{
    if (str.empty()) return false;

    size_t start = 0;
    if (str[0] == '-') {
        if (str.size() == 1) return false;
        start = 1;
    }

    for (size_t i = start; i < str.size(); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(str[i])))
            return false;
    }
    return true;
}

std::vector<int> generateJacobsthal(size_t n)
{
    std::vector<int> jac;
    int J0 = 0;
    int J1 = 1;
    jac.push_back(J1); // начинаем с 1

    while ((size_t)J1 < n)
    {
        int J2 = J1 + 2 * J0;
        if ((size_t)J2 >= n)
            break;
        jac.push_back(J2);
        J0 = J1;
        J1 = J2;
    }
    return jac;
}

// Вставка элементов pend в отсортированный массив sorted по Jacobsthal
void insertPendByJacobsthal(vec &sorted, const vec &pend)
{
    std::vector<int> jac = generateJacobsthal(pend.size());
    std::vector<bool> used(pend.size(), false);

    // Сначала вставляем элементы по Jacobsthal
    for (size_t i = 0; i < jac.size(); i++)
    {
        int idx = jac[i] - 1; // индексы Jacobsthal начинаются с 1
        if (idx >= 0 && (size_t)idx < pend.size() && !used[idx])
        {
            std::vector<int>::iterator it = std::lower_bound(sorted.begin(), sorted.end(), pend[idx]);
            sorted.insert(it, pend[idx]);
            used[idx] = true;
        }
    }

    // Вставляем оставшиеся элементы
    for (size_t i = 0; i < pend.size(); i++)
    {
        if (!used[i])
        {
            std::vector<int>::iterator it = std::lower_bound(sorted.begin(), sorted.end(), pend[i]);
            sorted.insert(it, pend[i]);
        }
    }
}

int main(int ac, char *av[])
{
    if (ac < 3)
    {
        std::cerr << "Error: program need minimum 2 numbers to sort" << std::endl;
        return 1;
    }

    // vec cont(ac - 1);
    vec cont;


    for (int i = 1; i < ac; i++)
    {
        //check number
        std::string arg = av[i];
        if (arg.length() == 0) {
            std::cerr << "Error: empty argument" << std::endl;
            return 1;
        }
        trim(arg);
        if (arg.length() == 0) {
            std::cerr << "Error: empty argument" << std::endl;
            return 1;
        }
        if (!isNumber(arg)) {
            std::cerr << "Error: " << arg << " wrong argument" << std::endl;
            return 1;
        }

        if (arg.length() > 11) {
            std::cerr << "Error: " << arg << " wrong argumen" << std::endl;
            return 1;
        }

        long num = std::atol(arg.c_str());
        if (num > INT_MAX) {
            std::cerr << "Error: " << arg << " too big number" << std::endl;
            return 1;
        }
        if (num < INT_MIN) {
            std::cerr << "Error: " << arg << " too small number" << std::endl;
            return 1;
        }
        cont.push_back(num);
        std::cout << num << " " ;
    }
    std::cout << std::endl;

    std::cout << "size " << cont.size() << std::endl;

    vec result = algor(cont);

    std::cout << "FINAL: ";
    for (size_t i = 0; i < result.size(); i++)
    {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}


vec algor(const vec &cont)
{
    std::cout << "-- RECURSION --" << std::endl;

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

    for (size_t i = 0; i < cont.size(); ) {

        vec pc;

        if (i + 1 < cont.size())
        {
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
        } else {
            pend.push_back(pCont[i][0]);
            big.push_back(pCont[i][1]);
        }
    }

    std::string hrs = hasRest ? "rest: " : "no rest:";
    std::cout << hrs  << rest << std::endl;

    for (size_t i = 0; i < big.size(); i++)
    {
        std::cout << big[i] << " ";
    }
    std::cout << std::endl;

    big = algor(big);
    insertPendByJacobsthal(big, pend);

    if (hasRest)
    {
        std::vector<int>::iterator it = std::lower_bound(big.begin(), big.end(), rest);
        big.insert(it, rest);
    }

    // вывод
    for (size_t i = 0; i < big.size(); i++)
        std::cout << big[i] << " ";
    std::cout << std::endl;
    return big;
}
