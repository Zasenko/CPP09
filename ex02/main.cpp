#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
#include <ctime>
#include <iomanip>

static size_t count = 0;
typedef std::vector<std::pair<int, int> > intPairVec;


typedef std::vector<std::vector<int> > Vec2D;


void binaryInsert(const std::vector<int>& pend, std::vector<std::vector<int> >& main,
                  size_t leftBound, size_t rightBound)
{
    if (main.empty()) return;

    size_t left = leftBound;
    size_t right = rightBound;

    while (left < right)
    {
        count++;
		std::cout << "🔍 Binary search step: left=" << left << ", right=" << right << "😈 count: " << count << std::endl;
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


void binaryInsertionSortJacob(const std::vector<int>& pend, std::vector<int>& main, int level)
{


    size_t blockSize = level / 2;
    size_t pendNumBlocks = (pend.size() + blockSize - 1) / blockSize;
	size_t mainNumBlocks = (main.size() + blockSize - 1) / blockSize;

	std::cout << "mainNumBlocks: " << mainNumBlocks << ", pendNumBlocks: " << pendNumBlocks << std::endl;		

    // разбиваем pend на блоки
    std::vector<std::vector<int> > pendBlocks(pendNumBlocks);
    for (size_t i = 0; i < pendNumBlocks; ++i)
    {
        size_t start = i * blockSize;
        size_t end = std::min(start + blockSize, pend.size());
        pendBlocks[i].insert(pendBlocks[i].end(), pend.begin() + start, pend.begin() + end);
    }

	// разбиваем main на блоки
    std::vector<std::vector<int> > mainBlocks(mainNumBlocks);
    for (size_t i = 0; i < mainNumBlocks; i++)
    {
        size_t start = i * blockSize;
        size_t end = start + blockSize;
        mainBlocks[i].insert(mainBlocks[i].end(), main.begin() + start, main.begin() + end);
    }

	for (size_t i = 0; i < mainBlocks.size(); ++i)
	{
		std::cout << "\n✅ Main block " << i << ": ";
		for (size_t j = 0; j < mainBlocks[i].size(); ++j)
			std::cout << mainBlocks[i][j] << " ";
	}
	std::cout << std::endl;

	for (size_t i = 0; i < pendBlocks.size(); ++i)
	{
		std::cout << "\n✅ Pend block " << i << ": ";
		for (size_t j = 0; j < pendBlocks[i].size(); ++j)
			std::cout << pendBlocks[i][j] << " ";
	}
	std::cout << std::endl;

    // строим последовательность Джейкобсталя для блоков
  	// size_t current = 3; // Starting at the third Jacobsthal index
	// size_t high = 3;    // Limit of binary search in main
	// size_t next = jacobsthalIndexGen(current, NEXT);
	// size_t prev = jacobsthalIndexGen(current, PREV);

	std::vector<size_t> jacob;
    jacob.push_back(1);
    jacob.push_back(3);

	while (jacob.back() < pendBlocks.size())
    {
        size_t next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
        jacob.push_back(next);
    }
	std::cout << "\n✅ Jacobsthal sequence: ";
	for (size_t i = 0; i < jacob.size(); i++)
		std::cout << jacob[i] << " ";
	std::cout << std::endl;


    std::vector<size_t> order;
    for (size_t i = 0; i < jacob.size(); i++)
	{
	    size_t j = jacob[i];
	    if (j <= pendBlocks.size())  // <= можно оставить, чтобы включить последний элемент
	    {
	        order.push_back(j);
	        std::cout << "Adding Jacobsthal index: " << j << std::endl;
	    }

	    if (i > 0)
	    {
	        size_t prev = jacob[i - 1];
	        std::cout << "prev: " << prev << std::endl;

	        for (size_t k = j - 1; k > prev; k--)
	        {
	            if (k <= pendBlocks.size())
	            {
	                order.push_back(k);
	                std::cout << "Adding Jacobsthal index between: " << k << std::endl;
	            }
	            if (k - 1 == prev)
	                break;
	        }
	    }
	}

	std::cout << "\n✅ Jacobsthal order: ";
	for (size_t i = 0; i < order.size(); i++)
		std::cout << order[i] << " ";
	std::cout << std::endl;

    // вставка блоков по Джейкобсталю

	size_t leftBound = 0;
	size_t	rightBound = mainBlocks.size();
    for (size_t i = 0; i < pendBlocks.size(); i++)
    {
		
        size_t idx = order[i] - 1;

		if ( idx == 0) {
			std::cout << "Inserting pend block index: " << order[i] << std::endl;

			std::cout << "block: ";
			for (size_t i = 0; i < pendBlocks[idx].size(); i++)
			{
				std::cout << pendBlocks[idx][i] << " ";
			}
			std::cout << std::endl;

			mainBlocks.insert(mainBlocks.begin(), pendBlocks[idx]);
			continue;
		}

    	std::cout << "Inserting pend block index: " << order[i] << " | left: " << leftBound << ", right: " << rightBound << std::endl;

		std::cout << "block: ";
		for (size_t i = 0; i < pendBlocks[idx].size(); i++)
		{
			std::cout << pendBlocks[idx][i] << " ";
		}
		std::cout << std::endl;

		rightBound = order[i] - 1 + i;

    	binaryInsert(pendBlocks[idx], mainBlocks, leftBound, rightBound);



       	leftBound = 0;
		rightBound = mainBlocks.size();

    }

	std::vector<int> newMain;

	for (size_t i = 0; i < mainBlocks.size(); i++)
	{
		newMain.insert(newMain.end(), mainBlocks[i].begin(), mainBlocks[i].end());
	}

	main = newMain;

	std::cout << "\n✅ Result main: ";
	for (size_t i = 0; i < main.size(); ++i)
		std::cout << main[i] << " ";
	std::cout << std::endl;

}

std::vector<int> sortVec(std::vector<int> &vecIntSeq, int level)
{

	std::cout << "\n===================== SORT START =====================\n";

	std::cout << "\n🟦 [createPairs] level: " << level << std::endl;
	for (size_t i = 0; i < vecIntSeq.size(); ++i)
		std::cout << vecIntSeq[i] << " ";
	std::cout << std::endl;

	std::vector<int> pairVec;
	std::vector<int>::iterator it = vecIntSeq.begin();
	while ((it + level) <= vecIntSeq.end())
	{
		pairVec.insert(pairVec.end(), it, it + level);
		it = it + level;
	}

	std::cout << "\n🟦 Created pairs before sort: ";
	for (size_t i = 0; i < pairVec.size();)
	{
		std::cout << "(";
		int j = 0;
		for (; j < level / 2; j++)
		{
			std::cout << pairVec[i] << " ";
			i++;
		}
		std::cout << " , ";
		for (; j < level ; j++)
		{
			std::cout << pairVec[i] << " ";
			i++;
		}
		std::cout << ") ";
	}
	std::cout << std::endl;

	std::vector<int> odd;
	while (it < vecIntSeq.end())
	{
		odd.push_back(*it);
		it++;
	}

	std::cout << "\n🟦 Created odd before sort: ";
	for (size_t i = 0; i < odd.size(); i++)
	{
		std::cout << odd[i] << ", ";
	}
	std::cout << std::endl;

	if (!pairVec.empty())
	{

		std::cout << "\n🟦 Sorting pairs:\n";
		std::vector<int> sortedPair;

		for (std::vector<int>::iterator pairIt = pairVec.begin(); pairIt < pairVec.end(); ) {

			std::vector<int> first;
			std::vector<int> second;

			first.insert(first.end(), pairIt, pairIt + level / 2);
			pairIt += level / 2;

			second.insert(second.end(), pairIt, pairIt + level / 2);
			count++;
			pairIt += level / 2;

			std::cout << "first: ";
			for (size_t i = 0; i < first.size(); i++) std::cout << first[i] << " ";
			std::cout << " | second: ";
			for (size_t i = 0; i < second.size(); i++) std::cout << second[i] << " ";		
			std::cout << " 😈😈😈 + COUNT : " << count << std::endl;
			if (first.back() > second.back())
			{
				sortedPair.insert(sortedPair.end(), second.begin(), second.end());
				sortedPair.insert(sortedPair.end(), first.begin(), first.end());

			} else {
				sortedPair.insert(sortedPair.end(), first.begin(), first.end());
				sortedPair.insert(sortedPair.end(), second.begin(), second.end());
			}
		}

		std::cout << "\n🟦 after sort: ";
		for (size_t i = 0; i < sortedPair.size();)
		{
			std::cout << "(";
			int j = 0;
			for (; j < level / 2; j++)
			{
				std::cout << sortedPair[i] << " ";
				i++;
			}
			std::cout << " , ";
			for (; j < level ; j++)
			{
				std::cout << sortedPair[i] << " ";
				i++;
			}
			std::cout << ") ";
		}
		std::cout << std::endl;

		int nextLevel = level * 2;
		sortedPair.insert(sortedPair.end(), odd.begin(), odd.end());

		std::cout << "->>> sorted: ";
		for (size_t i = 0; i < sortedPair.size(); i++)
			std::cout << sortedPair[i] << " ";
		std::cout << std::endl;

		if (static_cast<size_t>(nextLevel) < vecIntSeq.size())
		{
			pairVec = sortVec(sortedPair, nextLevel);
		} else {
			pairVec = sortedPair;
		}

	} else {
		std::cout << "⚠️ No pairs created from input sequence. EMPTY\n";
	}

	std::cout << "\n===================== Exit recursion ===================== level: " << level << std::endl;

	std::cout << "\n🟦 pairVec: ";
	size_t i = 0;
	for (; i + level < pairVec.size();)
		{
			std::cout << "(";
			int j = 0;
			for (; j < level / 2; j++)
			{
				std::cout << pairVec[i] << " ";
				i++;
			}
			std::cout << " , ";
			for (; j < level ; j++)
			{
				std::cout << pairVec[i] << " ";
				i++;
			}
			std::cout << ") ";
	}
	for (; i < pairVec.size(); i++)
	{
		std::cout << pairVec[i] << " ";
	}
	std::cout << std::endl;

	
	std::vector<int> main;
	std::vector<int> pend;
	std::vector<int> leftover;

	std::vector<int>::iterator pairIt = pairVec.begin();
	for (; pairIt + level < pairVec.end(); )
	{
		std::vector<int> first;
		std::vector<int> second;

		first.insert(first.end(), pairIt, pairIt + level / 2);
		pairIt += level / 2;
		second.insert(second.end(), pairIt, pairIt + level / 2);
		pairIt += level / 2;

		std::cout << "+ pend: ";
		for (size_t i = 0; i < first.size(); i++) std::cout << first[i] << " ";
		std::cout << " | main: ";
		for (size_t i = 0; i < second.size(); i++) std::cout << second[i] << " ";		
		std::cout << std::endl;
		
		pend.insert(pend.end(), first.begin(), first.end());
		main.insert(main.end(), second.begin(), second.end());

	}
	if (pairIt < pairVec.end()) {

		if (pairIt + (level / 2) <= pairVec.end()) {
			std::cout << "⚙️ adding to pend from odd\n";

			std::vector<int> first;
			first.insert(first.end(), pairIt, pairIt + level / 2);
			pairIt += level / 2;
			pend.insert(pend.end(), first.begin(), first.end());

			std::cout << "⚙️ to pendl from odd: " << std::endl;
			for (size_t i = 0; i < first.size(); i++)
			{
				std::cout << first[i] << " ";
			}
			std::cout << std::endl;

		}
		if (pairIt < pairVec.end())
		{
			leftover.insert(leftover.end(), pairIt, pairVec.end());
			std::cout << "⚙️ leftover: " << std::endl;
			for (size_t i = 0; i < leftover.size(); i++)
			{
				std::cout << leftover[i] << " ";
			}
			std::cout << std::endl;
		}
	}

	// if (!pend.empty())
	// {
	// 	std::vector<int> first;

	// 	std::vector<int>::iterator pendIt = pend.begin();
	// 	first.insert(first.end(), pendIt, pendIt + level / 2);

	// 	std::cout << "addin first from pend to main: ";
	// 	for (size_t i = 0; i < first.size(); i++)
	// 	{
	// 		std::cout << first[i] << " ";
	// 	}
	// 	std::cout << std::endl;

	// 	main.insert(main.begin(), first.begin(), first.end());
	// 	pend.erase(pend.begin(), pend.begin() + level / 2);
	// }

	std::cout << "main: ";
	for (size_t i = 0; i < main.size(); i++)
	{
		std::cout << main[i] << " ";		

	}
	std::cout << std::endl << "pend: ";
	for (size_t i = 0; i < pend.size(); i++)
	{
		std::cout << pend[i] << " ";		

	}
	std::cout << std::endl;

	if (!pend.empty())
	{
		binaryInsertionSortJacob(pend, main, level);
	}

	std::cout << "main after binary: ";
	for (size_t i = 0; i < main.size(); i++)
	{
		std::cout << main[i] << " ";		

	}
	std::cout << std::endl << "pend: ";
	for (size_t i = 0; i < pend.size(); i++)
	{
		std::cout << pend[i] << " ";		

	}
	std::cout << std::endl;

	if (!leftover.empty())
	{
		std::cout << "Adding leftover to main: ";
		for (size_t i = 0; i < leftover.size(); i++)
		{
			std::cout << leftover[i] << " ";
			main.push_back(leftover[i]);
		}
		std::cout << std::endl;
	}
	std::cout << " new main: ";
	for (size_t i = 0; i < main.size(); i++)
	{
		std::cout << main[i] << " ";		

	}

	return main;

	std::cout << "===================== SORT END =====================\n";
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

	std::cout << "Count: " << count << std::endl;
}

