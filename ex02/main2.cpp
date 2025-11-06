
#include "PmergeMe.hpp"

std::vector<size_t> PmergeMe::buildJacobOrder(size_t n)
{
    std::vector<size_t> order;
    if (n == 0)
        return order;

    // Построение чисел Якобсталя J_k
    std::vector<size_t> jNums;
    jNums.push_back(0);
    jNums.push_back(1);

    while (true)
    {
        size_t next = jNums.back() + 2 * jNums[jNums.size() - 2];
        if (next >= n)
            break;
        jNums.push_back(next);
    }

    // Генерация порядка вставки: группы в обратном порядке
    for (int k = jNums.size() - 1; k > 0; --k)
    {
        size_t start = jNums[k - 1];
        size_t end = std::min(jNums[k], n);

        // Добавляем элементы от end-1 до start (в обратном порядке)
        for (size_t i = end; i > start; --i)
        {
            size_t idx = i - 1;
            if (idx < n)
                order.push_back(idx);
        }
    }

    // Проверка, что все индексы от 0 до n-1 есть
    std::vector<bool> used(n, false);
    for (size_t i = 0; i < order.size(); i++)
        if (order[i] < n)
            used[order[i]] = true;

    for (size_t i = 0; i < n; i++)
        if (!used[i])
            order.push_back(i);

    return order;
}

void PmergeMe::insertPendVector(vec &sorted, const vec &pend)
{
    if (pend.empty())
        return;

    std::vector<size_t> jacobOrder = buildJacobOrder(pend.size());

    for (size_t i = 0; i < jacobOrder.size(); ++i)
    {
        size_t idx = jacobOrder[i];
        if (idx >= pend.size())
            continue;

        int value = pend[idx];
        size_t pos = 0;

        // Первые три элемента вставляем напрямую (без бинарного поиска)
        if (sorted.empty() || value <= sorted.front())
            pos = 0;
        else if (value >= sorted.back())
            pos = sorted.size();
        else if (i < 3)
        {
            // Для первых вставок — линейный поиск (ближе к поведению merge-insertion)
            for (pos = 0; pos < sorted.size(); ++pos)
            {
                if (value < sorted[pos])
                    break;
            }
        }
        else
        {
            // Остальные — бинарный поиск
            size_t left = 0;
            size_t right = sorted.size();
            while (left < right)
            {
                size_t mid = left + (right - left) / 2;
                if (sorted[mid] < value)
                    left = mid + 1;
                else
                    right = mid;
            }
            pos = left;
        }

        sorted.insert(sorted.begin() + pos, value);
    }
}


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
    std::cout << "Jacobsthal: " ;

    for (size_t i = 0; i < jac.size(); i++)
    {
        std::cout << jac[i] << " ";
    }
    std::cout << std::endl;

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

            std::cout << "Jacobsthal index: " << jac[i]
                      << " -> inserting element: " << pend[idx]
                      << " at position: " << (it - sorted.begin()) << "\n";


            sorted.insert(it, pend[idx]);
            used[idx] = true;

            std::cout << "Sorted after insertion: ";
            for (size_t k = 0; k < sorted.size(); k++)
                std::cout << sorted[k] << " ";
            std::cout << "\n\n";
        }
    }

    // Вставляем оставшиеся элементы
    std::cout << "Inserting remaining elements:\n";
    for (size_t i = 0; i < pend.size(); i++)
    {
        if (!used[i])
        {
            std::vector<int>::iterator it = std::lower_bound(sorted.begin(), sorted.end(), pend[i]);
            std::cout << "Remaining element: " << pend[i]
                      << " -> insert at position: " << (it - sorted.begin()) << "\n";

            sorted.insert(it, pend[i]);

            std::cout << "Sorted after insertion: ";
            for (size_t k = 0; k < sorted.size(); k++)
                std::cout << sorted[k] << " ";
            std::cout << "\n\n";
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
    pairVect pCont;

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
