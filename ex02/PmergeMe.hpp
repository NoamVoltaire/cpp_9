#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <iostream>
#include <vector>

class PmergeMe
{
private:
	std::vector<int>	vec;
	std::deque<int>		deq;

	void	print_vec(const char *str);
public:
	PmergeMe();
	~PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	PmergeMe(int ac, char **av);

	bool	parse_and_fill(size_t count, char **arg);
	void	execute();
	void	mergeInsertSortVec(std::vector<int> &vec);
	void	mergeInsertSortDeq(std::deque<int> &deq);
	void	insertionSortVector(std::vector<int> &vec);
	void	insertionSortDeque(std::deque<int> &vec);
};

#endif
