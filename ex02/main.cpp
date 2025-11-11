#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
#include <ctime>
#include <iomanip>

static size_t count = 0;
typedef std::vector<int> Vector;
typedef std::vector<std::vector<int> > Vector2D;

void binaryInsert(const Vector& pend, Vector2D& main, size_t leftBound, size_t rightBound)
{
    if (main.empty()) return;

    size_t left = leftBound;
    size_t right = rightBound;

    while (left < right)
    {
        count++;
        size_t mid = left + (right - left) / 2;
		if (pend.back() == main[mid].back()) {
    		left = mid;
			main.insert(main.begin() + left, pend);
			return;
		}
        else if (main[mid].back() < pend.back())
            left = mid + 1;
        else
            right = mid;
    }
    main.insert(main.begin() + left, pend);
}


void binaryInsertionSortJacob(const Vector& pend, Vector& main, int level)
{
    size_t blockSize = level / 2;
    size_t pendNumBlocks = (pend.size() + blockSize - 1) / blockSize;
	size_t mainNumBlocks = (main.size() + blockSize - 1) / blockSize;

    // разбиваем pend на блоки
    Vector2D pendBlocks(pendNumBlocks);
    for (size_t i = 0; i < pendNumBlocks; ++i)
    {
        size_t start = i * blockSize;
        size_t end = std::min(start + blockSize, pend.size());
        pendBlocks[i].insert(pendBlocks[i].end(), pend.begin() + start, pend.begin() + end);
    }

	// разбиваем main на блоки
    Vector2D mainBlocks(mainNumBlocks);
    for (size_t i = 0; i < mainNumBlocks; i++)
    {
        size_t start = i * blockSize;
        size_t end = start + blockSize;
        mainBlocks[i].insert(mainBlocks[i].end(), main.begin() + start, main.begin() + end);
    }

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

	std::vector<size_t> jacob;
    jacob.push_back(1);
    jacob.push_back(3);

	while (jacob.back() < pendBlocks.size())
    {
        size_t next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
        jacob.push_back(next);
    }
	std::cout << "Jacobsthal sequence: ";
	for (size_t i = 0; i < jacob.size(); i++) std::cout << jacob[i] << " ";
	std::cout << std::endl;

    Vector order;
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

	std::cout << "Jacobsthal order: ";
	for (size_t i = 0; i < order.size(); i++) std::cout << order[i] << " ";
	std::cout << std::endl;

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
	std::cout << "😈 count after binary: " << count << std::endl;

	Vector newMain;
	for (size_t i = 0; i < mainBlocks.size(); i++)
		newMain.insert(newMain.end(), mainBlocks[i].begin(), mainBlocks[i].end());
	main = newMain;
}

Vector sortVec(Vector &vecIntSeq, int level)
{

	std::cout << std::endl << "=== SORT START === " << level << std::endl;
	
	Vector pairVec;
	Vector::iterator it = vecIntSeq.begin();
	while ((it + level) <= vecIntSeq.end())
	{
		pairVec.insert(pairVec.end(), it, it + level);
		it = it + level;
	}

	Vector odd;
	while (it < vecIntSeq.end())
	{
		odd.push_back(*it);
		it++;
	}

	std::cout << "\nbefore sort: " << std::endl;
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

	if (!pairVec.empty())
	{
		Vector sortedPair;
		for (Vector::iterator pairIt = pairVec.begin(); pairIt < pairVec.end(); ) {

			Vector first;
			Vector second;

			first.insert(first.end(), pairIt, pairIt + level / 2);
			pairIt += level / 2;

			second.insert(second.end(), pairIt, pairIt + level / 2);
			pairIt += level / 2;
	
			count++;
			if (first.back() > second.back())
			{
				sortedPair.insert(sortedPair.end(), second.begin(), second.end());
				sortedPair.insert(sortedPair.end(), first.begin(), first.end());

			} else {
				sortedPair.insert(sortedPair.end(), first.begin(), first.end());
				sortedPair.insert(sortedPair.end(), second.begin(), second.end());
			}
		}

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
		std::cout << std::endl << "😈 count: " << count << std::endl;

		int nextLevel = level * 2;
		sortedPair.insert(sortedPair.end(), odd.begin(), odd.end());

		if (static_cast<size_t>(nextLevel) < vecIntSeq.size())
			pairVec = sortVec(sortedPair, nextLevel);
		else
			pairVec = sortedPair;
	}
	else
	{
		return odd;
	}

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

	std::cout << std::endl << "Leftover: ";
	for (size_t i = 0; i < leftover.size(); i++) std::cout << leftover[i] << " ";
	std::cout << std::endl;

	if (!pend.empty())
		binaryInsertionSortJacob(pend, main, level);

	if (!leftover.empty())
	{
		for (size_t i = 0; i < leftover.size(); i++) main.push_back(leftover[i]);
	}
	std::cout << "result: ";
	for (size_t i = 0; i < main.size(); i++) std::cout << main[i] << " ";		
	std::cout << std::endl;
	return main;
}

int main(int ac, char *av[])
{
	std::vector<int> _v;

    if (ac < 2) throw std::logic_error("Program need minimum 1 number");

    for (int i = 1; i < ac; i++)
    {
        std::string arg = av[i];
        long num = std::atol(arg.c_str());
        if (num > INT_MAX)
            throw std::logic_error("Very big number: " + arg);
        if (num < 0)
            throw std::logic_error("Negative number: " + arg);

        _v.push_back(num);
    }

    std::cout << "Before: ";
    for (size_t i = 0; i < _v.size(); i++) std::cout << _v[i] << " ";
    std::cout << std::endl;


	std::vector<int> sorted = sortVec(_v, 2);
 	
	std::cout << "\n\nBefore: ";
    for (size_t i = 0; i < _v.size(); i++) std::cout << _v[i] << " ";
    std::cout << std::endl;

	std::cout << "After : ";
    for (size_t i = 0; i < sorted.size(); i++) std::cout << sorted[i] << " ";
    std::cout << std::endl;

	std::sort(_v.begin(), _v.end());

	if (sorted.size() != _v.size())
	{
		std::cout << "❌ Error: sizes differ\n";
		return 1;
	}

	for (size_t i = 0; i < _v.size(); i++)
	{
		if (sorted[i] != _v[i])
		{
			std::cout << "❌ Error: elements differ at index " << i << ": " << sorted[i] << " != " << _v[i] << std::endl;
			return 1;
		}
	}
	std::cout << "✅ Sorted correctly!\n";

	std::cout << "Count: " << count << std::endl;
}

