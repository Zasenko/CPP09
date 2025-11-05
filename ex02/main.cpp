#include "PmergeMe.hpp"
#include <ctime>   // clock(), CLOCKS_PER_SEC

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
    if (n == 0)
        return std::vector<size_t>();

    // Генерируем числа Якобсталя
    std::vector<size_t> jacob;
    jacob.push_back(1);
    if (n > 1)
        jacob.push_back(3);

    for (size_t i = 2; jacob.back() < n; ++i)
    {
        size_t next = jacob[i - 1] + 2 * jacob[i - 2];
        if (next > n)
            break;
        jacob.push_back(next);
    }

    // Строим порядок вставки
    std::vector<size_t> order;
    std::vector<bool> inserted(n + 1, false);

    // Добавляем первое число Якобсталя
    if (jacob[0] <= n)
    {
        order.push_back(jacob[0]);
        inserted[jacob[0]] = true;
    }

    // Добавляем остальные в специальном порядке
    for (size_t i = 1; i < jacob.size(); ++i)
    {
        size_t current = jacob[i];
        size_t prev = jacob[i - 1];

        // Добавляем числа от current-1 до prev+1 в убывающем порядке
        for (size_t j = current; j > prev; --j)
        {
            if (j <= n && !inserted[j])
            {
                order.push_back(j);
                inserted[j] = true;
            }
        }
    }

    // Добавляем пропущенные числа
    for (size_t i = 1; i <= n; ++i)
    {
        if (!inserted[i])
        {
            order.push_back(i);
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

    // Вставляем элементы в порядке Якобсталя
    for (size_t i = 0; i < jacobOrder.size(); ++i)
    {
        size_t idx = jacobOrder[i] - 1; // преобразуем в 0-based индекс
        if (idx >= pend.size())
        {
            std::cerr << "Warning: index " << idx << " out of bounds for pend size " << pend.size() << std::endl;
            continue;
        }

        int value = pend[idx];
        size_t pos = binarySearch(sorted, value, count);

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
        size_t result = binarySearch(big, rest, count);
        std::cout << "hasRest binarySearch result index: " << result << ", insert number: " << rest << std::endl;
        big.insert(big.begin() + result, rest);
    }

    // вывод
    for (size_t i = 0; i < big.size(); i++)
        std::cout << big[i] << " ";
    std::cout << std::endl;
    return big;
}

// void insertPendByJacobsthal2(vec &sorted, const vec &pend, int &count)
// {
//     std::cout << "= insertPendByJacobsthal2 =" << std::endl;

//     std::cout << "big: ";
//     for (size_t i = 0; i < sorted.size(); i++)
//         std::cout << sorted[i] << " ";
//     std::cout << " | small: ";
//     for (size_t i = 0; i < pend.size(); i++)
//         std::cout << pend[i] << " ";
//     std::cout << std::endl;

//     // Построение последовательности Якобсталя
//     std::vector<size_t> jacobsthal = buildJacobOrder(pend.size());

//     std::cout << "Jacobsthal: ";
//     for (size_t i = 0; i < jacobsthal.size(); i++)
//         std::cout << jacobsthal[i] << " ";
//     std::cout << " | ";

//     for (size_t k = 0; k < jacobsthal.size(); k++)
//     {
//         size_t idx = jacobsthal[k];
//         if (idx == 0 || idx > pend.size())
//             continue;

//         std::cout << "insertOrder[" << k << "] = " << idx;
//     }

//     std::cout << std::endl;

//     // Вставка элементов в порядке insertOrder (прямой порядок)
//     for (size_t k = 0; k < jacobsthal.size(); ++k)
//     {
//         size_t idx = jacobsthal[k];
//         if (idx == 0 || idx > pend.size())
//             continue;

//         int value = pend[idx - 1];
//         size_t pos = binarySearch(sorted, value, count);

//         std::cout << "insertOrder[" << k << "] = " << idx
//                   << " -> insert " << value
//                   << " at pos " << pos << std::endl;

//         sorted.insert(sorted.begin() + pos, value);
//     }

//     // Вставка оставшихся (если Jacobsthal не покрыл всех)
//     for (size_t i = 1; i <= pend.size(); i++)
//     {
//         bool found = false;
//         for (size_t j = 0; j < jacobsthal.size(); j++)
//         {
//             if (jacobsthal[j] == i)
//             {
//                 found = true;
//                 break;
//             }
//         }
//         if (!found)
//         {
//             int value = pend[i - 1];
//             size_t pos = binarySearch(sorted, value, count);

//             std::cout << "remaining insert " << value
//                       << " at pos " << pos << std::endl;
//             // count++;
//             sorted.insert(sorted.begin() + pos, value);
//         }
//     }
// }

//----

// std::vector<size_t> buildJacobOrder(size_t n)
// {
//     std::vector<size_t> J;
//     J.push_back(0);
//     J.push_back(1);

//     while (J.back() < n)
//         J.push_back(J[J.size() - 1] + 2 * J[J.size() - 2]);

//     std::vector<size_t> order;
//     size_t last = 1;

//     for (size_t i = 2; i < J.size(); i++)
//     {
//         size_t cur = std::min(J[i], n);
//         for (size_t k = cur; k > last; k--)
//             order.push_back(k);
//         last = cur;
//         if (cur == n)
//             break;
//     }
//     return order;
// }

// std::vector<size_t> generateJacobsthal(size_t n)
// {
//     // Построить числа Якобстала: 0,1,1,3,5,11,21,...
//     std::vector<size_t> J;
//     J.push_back(0);
//     J.push_back(1);
//     while (J.back() < n)
//     {
//         size_t sz = J.size();
//         size_t next = J[sz - 1] + 2 * J[sz - 2];
//         J.push_back(next);
//     }

//     // Построить реальный порядок вставок (1-based индексы)
//     std::vector<size_t> order;
//     size_t prev = 0;
//     for (size_t i = 1; i < J.size() && J[i] <= n; ++i)
//     {
//         size_t from = prev + 1;
//         size_t to   = J[i];
//         // Добавляем диапазон [from..to] в обратном порядке
//         for (size_t k = to; k >= from; --k)
//         {
//             order.push_back(k);
//             if (k == from) break; // чтобы не зациклиться на size_t
//         }
//         prev = J[i];
//     }
//     return order;
// }

// Вставка элементов pend в отсортированный массив sorted по Jacobsthal
// void insertPendByJacobsthal(vec &sorted, const vec &pend, int &count)
// {
//     std::vector<size_t> jac = generateJacobsthal(pend.size());
//     std::vector<bool> used(pend.size(), false);

//     std::cout << "Jacobsthal: " ;
//     for (size_t i = 0; i < jac.size(); i++)
//     {
//         std::cout << jac[i] << " ";
//     }
//     std::cout << " | ";
//     std::cout << "sorted: " ;
//     for (size_t i = 0; i < sorted.size(); i++)
//     {
//         std::cout << sorted[i] << " ";
//     }
//     std::cout << " | ";
//     std::cout << "pend: " ;
//     for (size_t i = 0; i < pend.size(); i++)
//     {
//         std::cout << pend[i] << " ";
//     }
//     std::cout << std::endl;

//     // Сначала вставляем элементы по Jacobsthal
//     for (size_t i = 0; i < jac.size(); i++)
//     {
//         size_t idx = jac[i] - 1; // индексы Jacobsthal начинаются с 1
//         std::cout << "idx: " << idx << std::endl;

//         // if (idx >= 0 && idx < pend.size() && !used[idx])
//         if (idx < pend.size() && !used[idx])
//         {
//             size_t result = binarySearch(sorted, pend[idx], count);
//             std::cout << "binarySearch result index: " << result << ", insert number: " << pend[idx] << std::endl;
//             sorted.insert(sorted.begin() + result, pend[idx]);
//             used[idx] = true;

//             std::cout << "new sorted: " ;
//             for (size_t i = 0; i < sorted.size(); i++)
//             {
//                 std::cout << sorted[i] << " ";
//             }
//             std::cout << std::endl;
//         }
//     }

//     for (size_t i = 0; i < pend.size(); i++)
//     {
//         if (!used[i])
//         {
//             size_t result = binarySearch(sorted, pend[i], count);
//             std::cout << "binarySearch result index: " << result << ", insert number: " << pend[i] << std::endl;
//             sorted.insert(sorted.begin() + result, pend[i]);
//         }
//     }
// }

// std::vector<int> generateJacobsthal(size_t n)
// {
//     std::vector<int> jac;
//     int J0 = 0;
//     int J1 = 1;
//     jac.push_back(J0);
//     jac.push_back(J1);

//     size_t size =

//     while ((size_t)J1 < n)
//     {
//         int J2 = J1 + 2 * J0;
//         if ((size_t)J2 >= n)
//             break;
//         jac.push_back(J2);
//         J0 = J1;
//         J1 = J2;
//     }

//     std::cout << "Jacobsthal: " ;
//     for (size_t i = 0; i < jac.size(); i++)
//     {
//         std::cout << jac[i] << " ";
//     }
//     std::cout << std::endl;

//     return jac;
// }
