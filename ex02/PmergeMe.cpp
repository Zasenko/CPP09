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
}

void PmergeMe::sort()
{
    bool isDebug = false;

    // --- Vector ---

    std::cout << "Before: ";
    for (size_t i = 0; i < _v.size(); i++) std::cout << _v[i] << " ";
    std::cout << std::endl;

    clock_t vStart = clock();
    Vector vSorted = sortVector(_v, 2, isDebug);
    clock_t vEnd = clock();

    std::cout << "After: ";
    for (size_t i = 0; i < vSorted.size(); i++)
        std::cout << vSorted[i] << " ";
    std::cout << std::endl;

    double vTime = double(vEnd - vStart) / CLOCKS_PER_SEC;
    std::cout << std::fixed << std::setprecision(6)
              << "Time to process a range of " << _v.size()
              << " elements with std::vector: " << vTime << " us" << std::endl;

    // --- Deque ---

    // clock_t dStart = clock();
    // Deque dSorted = sortDeque(_d, isDebug);
    // clock_t dEnd = clock();

    // double dTime = double(dEnd - dStart) / CLOCKS_PER_SEC;
    // std::cout << std::fixed << std::setprecision(6)
    //           << "Time to process a range of " << _d.size()
    //           << " elements with std::deque: " << dTime << " us" << std::endl;         
}

// --- Vector ---

void binaryInsert(const Vector& pend, Vector2D& main, size_t leftBound, size_t rightBound)
{
    if (main.empty()) return;

    size_t left = leftBound;
    size_t right = rightBound;
    while (left < right)
    {
        size_t mid = left + (right - left) / 2;
		if (pend.back() > main[mid].back()) {
    		left = mid + 1;
		}
        else
            right = mid;
    }
    main.insert(main.begin() + left, pend);
}

void createVector2d(const Vector& pend, Vector& main, Vector2D &pendBlocks, Vector2D &mainBlocks, int level, bool isDebug)
{
    size_t blockSize = level / 2;
    size_t pendNumBlocks = (pend.size() + blockSize - 1) / blockSize;
	size_t mainNumBlocks = (main.size() + blockSize - 1) / blockSize;

    for (size_t i = 0; i < pendNumBlocks; ++i)
    {
        size_t start = i * blockSize;
        size_t end = std::min(start + blockSize, pend.size());
        pendBlocks[i].insert(pendBlocks[i].end(), pend.begin() + start, pend.begin() + end);
    }

    for (size_t i = 0; i < mainNumBlocks; i++)
    {
        size_t start = i * blockSize;
        size_t end = start + blockSize;
        mainBlocks[i].insert(mainBlocks[i].end(), main.begin() + start, main.begin() + end);
    }

	if (isDebug) {
		for (size_t i = 0; i < mainBlocks.size(); ++i)
		{
			std::cout << "Main " << i + 1 << ": ";
			for (size_t j = 0; j < mainBlocks[i].size(); ++j) std::cout << mainBlocks[i][j] << " ";
			std::cout << std::endl;
		}
		std::cout << std::endl;
		for (size_t i = 0; i < pendBlocks.size(); ++i)
		{
			std::cout << "Pend " << i + 1 << ": ";
			for (size_t j = 0; j < pendBlocks[i].size(); ++j) std::cout << pendBlocks[i][j] << " ";
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

}

void createVectorJacobsthal(const Vector2D &pendBlocks, Vector &order, bool isDebug)
{
    std::vector<size_t> jacob;
    jacob.push_back(1);
    jacob.push_back(3);

	while (jacob.back() < pendBlocks.size())
    {
        size_t next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
        jacob.push_back(next);
    }

	if (isDebug) {
		std::cout << "Jacobsthal sequence: ";
		for (size_t i = 0; i < jacob.size(); i++) std::cout << jacob[i] << " ";
		std::cout << std::endl;
	}

    for (size_t i = 0; i < jacob.size(); i++)
	{
	    size_t j = jacob[i];
	    if (j <= pendBlocks.size())
			order.push_back(j);
	    if (i > 0)
	    {
	        size_t prev = jacob[i - 1];
	        for (size_t k = j - 1; k > prev; k--)
	        {
	            if (k <= pendBlocks.size())
					order.push_back(k);
	            if (k - 1 == prev)
	                break;
	        }
	    }
	}
	
    if (isDebug) {
		std::cout << "Jacobsthal order: ";
		for (size_t i = 0; i < order.size(); i++) std::cout << order[i] << " ";
		std::cout << std::endl;
	}
}

void binaryInsertionSortJacob(const Vector& pend, Vector& main, int level, bool isDebug)
{
    size_t blockSize = level / 2;
    size_t pendNumBlocks = (pend.size() + blockSize - 1) / blockSize;
	size_t mainNumBlocks = (main.size() + blockSize - 1) / blockSize;
    Vector2D pendBlocks(pendNumBlocks);
    Vector2D mainBlocks(mainNumBlocks);
    createVector2d(pend, main, pendBlocks, mainBlocks, level, isDebug);

    Vector order;
	createVectorJacobsthal(pendBlocks, order, isDebug);

	size_t leftBound = 0;
	size_t	rightBound = mainBlocks.size();
    for (size_t i = 0; i < pendBlocks.size(); i++)
    {
        size_t idx = order[i] - 1;
		if (idx == 0) {
			mainBlocks.insert(mainBlocks.begin(), pendBlocks[idx]);
			continue;
		}
		rightBound = order[i] - 1 + i;
    	binaryInsert(pendBlocks[idx], mainBlocks, leftBound, rightBound);
		rightBound = mainBlocks.size();
    }

	Vector newMain;
	for (size_t i = 0; i < mainBlocks.size(); i++)
		newMain.insert(newMain.end(), mainBlocks[i].begin(), mainBlocks[i].end());
	main = newMain;
}

void createVectorPare(Vector &unsorted, Vector &pairVec, Vector &odd, int level, bool isDebug)
{
    Vector::iterator it = unsorted.begin();

	while ((it + level) <= unsorted.end())
	{
		pairVec.insert(pairVec.end(), it, it + level);
		it = it + level;
	}
	while (it < unsorted.end())
	{
		odd.push_back(*it);
		it++;
	}

    if (isDebug) {
		std::cout << "before sort: " << std::endl;
		for (size_t i = 0; i < pairVec.size();)
		{
			std::cout << "( ";
			int j = 0;
			for (; j < level / 2; j++)
			{
				std::cout << pairVec[i] << " ";
				i++;
			}
			std::cout << ", ";
			for (; j < level ; j++)
			{
				std::cout << pairVec[i] << " ";
				i++;
			}
			std::cout << ") ";
		}
		std::cout << "| odd: ";
		for (size_t i = 0; i < odd.size(); i++) std::cout << odd[i] << " ";
		std::cout << std::endl;
	}

}

void sortVectorPare(Vector &sortedPair, Vector &odd, Vector &pairVec, int level, bool isDebug)
{
    for (Vector::iterator pairIt = pairVec.begin(); pairIt < pairVec.end(); )
    {
		Vector first;
		Vector second;
		first.insert(first.end(), pairIt, pairIt + level / 2);
		pairIt += level / 2;
		second.insert(second.end(), pairIt, pairIt + level / 2);
		pairIt += level / 2;

		if (first.back() > second.back())
		{
			sortedPair.insert(sortedPair.end(), second.begin(), second.end());
			sortedPair.insert(sortedPair.end(), first.begin(), first.end());
		} else {
			sortedPair.insert(sortedPair.end(), first.begin(), first.end());
			sortedPair.insert(sortedPair.end(), second.begin(), second.end());
		}
	}
	
    if (isDebug) {
		std::cout << "after sort:" << std::endl;
		for (size_t i = 0; i < sortedPair.size();)
		{
			std::cout << "( ";
			int j = 0;
			for (; j < level / 2; j++)
			{
				std::cout << sortedPair[i] << " ";
				i++;
			}
			std::cout << ", ";
			for (; j < level ; j++)
			{
				std::cout << sortedPair[i] << " ";
				i++;
			}
			std::cout << ") ";
		}
		std::cout << "| odd: ";
		for (size_t i = 0; i < odd.size(); i++) std::cout << odd[i] << " ";
		std::cout << std::endl;
	}
}

Vector sortVectorBack(Vector &pairVec, int level, bool isDebug)
{
    if (isDebug) {
		std::cout << std::endl << "=== Exit recursion === " << level << std::endl << std::endl;
		size_t i = 0;
		for (; i + level < pairVec.size();)
			{
				std::cout << "( ";
				int j = 0;
				for (; j < level / 2; j++)
				{
					std::cout << pairVec[i] << " ";
					i++;
				}
				std::cout << ", ";
				for (; j < level ; j++)
				{
					std::cout << pairVec[i] << " ";
					i++;
				}
				std::cout << ") ";
		}
		std::cout << "| odd: ";
		for (; i < pairVec.size(); i++) std::cout << pairVec[i] << " ";
		std::cout << std::endl;
	}

    Vector main;
	Vector pend;
	Vector leftover;
	
    Vector::iterator pairIt = pairVec.begin();
	for (; pairIt + level < pairVec.end(); )
	{
		Vector small;
		Vector big;

		small.insert(small.end(), pairIt, pairIt + level / 2);
		pairIt += level / 2;
		big.insert(big.end(), pairIt, pairIt + level / 2);
		pairIt += level / 2;

		pend.insert(pend.end(), small.begin(), small.end());
		main.insert(main.end(), big.begin(), big.end());
	}
	if (pairIt < pairVec.end()) {

		if (pairIt + (level / 2) <= pairVec.end()) {
			std::vector<int> first;
			first.insert(first.end(), pairIt, pairIt + level / 2);
			pairIt += level / 2;
			pend.insert(pend.end(), first.begin(), first.end());
		}
		if (pairIt < pairVec.end())
		{
			leftover.insert(leftover.end(), pairIt, pairVec.end());
		}
	}

	if (isDebug) {
		std::cout << std::endl << "Leftover: ";
		for (size_t i = 0; i < leftover.size(); i++) std::cout << leftover[i] << " ";
		std::cout << std::endl << std::endl;
	}

	if (!pend.empty())
		binaryInsertionSortJacob(pend, main, level, isDebug);
	if (!leftover.empty())
	{
		for (size_t i = 0; i < leftover.size(); i++)
		main.push_back(leftover[i]);
	}
	if (isDebug) {
		std::cout << "result: \n";
		for (size_t i = 0; i < main.size(); i++) std::cout << main[i] << " ";		
		std::cout << std::endl;
	}
    return main;
}

Vector PmergeMe::sortVector(Vector &vector, int level, const bool isDebug)
{
    if (isDebug) std::cout << "\n=== Sort Pairs === " << level << "\n" << std::endl;
	
	Vector pairVec;
	Vector odd;
	createVectorPare(vector, pairVec, odd, level, isDebug);

	if (!pairVec.empty())
	{
		Vector sortedPair;
		sortVectorPare(sortedPair, odd, pairVec, level, isDebug);

		int nextLevel = level * 2;
		sortedPair.insert(sortedPair.end(), odd.begin(), odd.end());

		if (static_cast<size_t>(nextLevel) < vector.size())
			pairVec = sortVector(sortedPair, nextLevel, isDebug);
		else
			pairVec = sortedPair;
	}
	else
		return odd;

    return sortVectorBack(pairVec, level, isDebug);
}

// --- Deque ---

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
