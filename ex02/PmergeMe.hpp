#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
#include <deque>
#include <ctime>
#include <iomanip>

typedef std::vector<int> Vector;
typedef std::vector<Vector> Vector2D;

typedef std::deque<int> Deque;
typedef std::deque<Deque> Deque2D;

class PmergeMe {
    public:
        PmergeMe(int ac, char *av[]);
        ~PmergeMe();
        void sort();
    private:
        PmergeMe();
        PmergeMe(const PmergeMe &copy);
        PmergeMe &operator=(const PmergeMe &src);

        Vector _v;
        Deque _d;

        Vector sortVector(Vector &v, int level, bool isDebug);
        void createVectorPare(Vector &unsorted, Vector &pairVec, Vector &odd, int level, bool isDebug);
        void sortVectorPare(Vector &sortedPair, Vector &odd, Vector &pairVec, int level, bool isDebug);
        Vector sortVectorBack(Vector &pairVec, int level, bool isDebug);
        void createVector2d(const Vector& pend, Vector& main, Vector2D &pendBlocks, Vector2D &mainBlocks, int level, bool isDebug);
        void createVectorJacobsthal(const Vector2D &pendBlocks, Vector &order, bool isDebug);
        void binaryInsertionVector(const Vector& pend, Vector& main, int level, bool isDebug);
        void binaryInsertVector(const Vector& pend, Vector2D& main, size_t leftBound, size_t rightBound);

        Deque sortDeque(Deque &v, int level, bool isDebug);
        void createDequePare(Deque &unsorted, Deque &pairVec, Deque &odd, int level, bool isDebug);
        void sortDequePare(Deque &sortedPair, Deque &odd, Deque &pairVec, int level, bool isDebug);
        Deque sortDequeBack(Deque &pairVec, int level, bool isDebug);
        void createDeque2d(const Deque& pend, Deque& main, Deque2D &pendBlocks, Deque2D &mainBlocks, int level, bool isDebug);
        void createDequeJacobsthal(const Deque2D &pendBlocks, Deque &order, bool isDebug);
        void binaryInsertionDeque(const Deque& pend, Deque& main, int level, bool isDebug);
        void binaryInsertDeque(const Deque& pend, Deque2D& main, size_t leftBound, size_t rightBound);

        void trim(std::string &s);
        bool isNumber(const std::string &str);
};

#endif
