#include "PmergeMe.hpp"
#include <cctype>
#include <iterator>
#include <string>

PmergeMe::PmergeMe() { }

PmergeMe::~PmergeMe() { }

PmergeMe::PmergeMe(const PmergeMe &other) { *this = other; }

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	std::cout << "PmergeMe: Copy assignment operator called" << std::endl;
	if (this != &other)
	{
		// Copy members here
	}
	return *this;
}

bool	PmergeMe::parse_and_fill(size_t count, char **arg)
{
	for (size_t i = 0 ; i < count ; i++)
	{
		for (size_t j = 0 ; arg[i][j];)
		{
			if (!std::isdigit(arg[i][j]))
			{
				std::cerr << "Error : program only accepts numbers" << std::endl;
				return false;
			}
			j++;
		}
		int	res;

		try 
		{
			res = std::stoi(arg[i]);
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
			return false;
		}
		if (res < 0)
		{
			std::cerr << "Error : program only positive int" << std::endl;
			return false;
		}
		vec.push_back(res);
		deq.push_back(res);
	}
	return true;
}

void PmergeMe::insertionSortDeque(std::deque<int> &vec)
{
	for (size_t i = 1; i < vec.size(); i++)
	{
		int key = vec[i];
		int j = i - 1;

		while (j >= 0 && vec[j] > key)
		{
			vec[j + 1] = vec[j];
			j--;
		}
		vec[j + 1] = key;
	}
}

void PmergeMe::insertionSortVector(std::vector<int> &vec)
{
	for (size_t i = 1; i < vec.size(); i++)
	{
		int key = vec[i];
		int j = i - 1;

		while (j >= 0 && vec[j] > key)
		{
			vec[j + 1] = vec[j];
			j--;
		}
		vec[j + 1] = key;
	}
}

std::deque<size_t>	JacobsthalOrderDeq(size_t pairCount)
{
	std::deque<size_t>	order;
	std::deque<size_t>	jac;

	if (pairCount <= 1)
		return order;
	jac.push_back(1);
	jac.push_back(3);
	while (jac.back() < pairCount)
		jac.push_back(jac[jac.size() - 1] + 2 * jac[jac.size() - 2]);
	size_t	prev = 1;
	size_t	curr;

	for (size_t i = 0; i < jac.size(); i++)
	{
		curr = jac[i];
		if (curr > pairCount)
			curr = pairCount;
		for (size_t j = curr; j > prev; j--)
			order.push_back(j - 1);
		prev = curr;
	}
	return order;
}

std::vector<size_t>	JacobsthalOrderVec(size_t pairCount)
{
	std::vector<size_t>	order;
	std::vector<size_t>	jac;

	if (pairCount <= 1)
		return order;
	jac.push_back(1);
	jac.push_back(3);
	while (jac.back() < pairCount)
		jac.push_back(jac[jac.size() - 1] + 2 * jac[jac.size() - 2]);
	size_t	prev = 1;
	size_t	curr;

	for (size_t i = 0; i < jac.size(); i++)
	{
		curr = jac[i];
		if (curr > pairCount)
			curr = pairCount;
		for (size_t j = curr; j > prev; j--)
			order.push_back(j - 1);
		prev = curr;
	}
	return order;
}

void PmergeMe::mergeInsertSortDeq(std::deque<int> &deq)
{
	if (deq.size() <= 1)
		return;

	if (deq.size() <= 16)
	{
		insertionSortDeque(deq);
		return;
	}

	std::deque<std::pair<int, int> > pairs;
	size_t i;

	for (i = 0; i + 1 < deq.size(); i += 2)
	{
		if (deq[i] > deq[i + 1])
			pairs.push_back(std::make_pair(deq[i + 1], deq[i]));
		else
			pairs.push_back(std::make_pair(deq[i], deq[i + 1]));
	}

	int straggler = -1;
	bool hasStraggler = false;
	if (i < deq.size())
	{
		straggler = deq[i];
		hasStraggler = true;
	}

	std::deque<int> largerElements;
	for (size_t j = 0; j < pairs.size(); j++)
		largerElements.push_back(pairs[j].second);

	mergeInsertSortDeq(largerElements);

	std::deque<int>	result = largerElements;

	std::deque<size_t>	order = JacobsthalOrderDeq(pairs.size());

	for (size_t k = 0; k < order.size(); k++)
	{
	size_t j = order[k];
		std::cout << "order = " << order[k] << std::endl;
	int smaller = pairs[j].first;

		std::deque<int>::iterator it = std::lower_bound(result.begin(), result.end(), smaller);
	result.insert(it, smaller);
	}

//	for (size_t j = 0; j < pairs.size(); j++)
//	{
//		int smaller = pairs[j].first;
//
//		std::deque<int>::iterator it;
//		it = std::lower_bound(result.begin(), result.end(), smaller);
//		result.insert(it, smaller);
//	}

	if (hasStraggler)
	{
		std::deque<int>::iterator it = std::lower_bound(result.begin(), result.end(), straggler);
		result.insert(it, straggler);
	}

	deq = result;
}


void PmergeMe::mergeInsertSortVec(std::vector<int> &vec)
{
	if (vec.size() <= 1)
		return;

	if (vec.size() <= 16)
	{
		insertionSortVector(vec);
		return;
	}

	std::vector<std::pair<int, int> > pairs;
	size_t i;

	for (i = 0; i + 1 < vec.size(); i += 2)
	{
		if (vec[i] > vec[i + 1])
			pairs.push_back(std::make_pair(vec[i + 1], vec[i]));
		else
			pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
	}

	int straggler = -1;
	bool hasStraggler = false;
	if (i < vec.size())
	{
		straggler = vec[i];
		hasStraggler = true;
	}

	std::vector<int> largerElements;
	for (size_t j = 0; j < pairs.size(); j++)
		largerElements.push_back(pairs[j].second);

	mergeInsertSortVec(largerElements);

	std::vector<int>	result = largerElements;

	std::vector<size_t>	order = JacobsthalOrderVec(pairs.size());

	for (size_t k = 0; k < order.size(); k++)
	{
	size_t j = order[k];
	int smaller = pairs[j].first;

		std::vector<int>::iterator it = std::lower_bound(result.begin(), result.end(), smaller);
	result.insert(it, smaller);
	}

//	for (size_t j = 0; j < pairs.size(); j++)
//	{
//		int smaller = pairs[j].first;
//
//		std::vector<int>::iterator it;
//		it = std::lower_bound(result.begin(), result.end(), smaller);
//		result.insert(it, smaller);
//	}

	if (hasStraggler)
	{
		std::vector<int>::iterator it = std::lower_bound(result.begin(), result.end(), straggler);
		result.insert(it, straggler);
	}

	vec = result;
}

void	PmergeMe::print_vec(const char *str)
{
	std::cout << str;
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i];
		if (i < vec.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;

}

void	PmergeMe::execute()
{

	print_vec("Before ");

	clock_t startVec = clock();
	mergeInsertSortVec(vec);
	clock_t endVec = clock();
	double time_vec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000;

	clock_t startDeq = clock();
	mergeInsertSortDeq(deq);
	clock_t endDeq = clock();
	double time_deq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000;

	print_vec("After ");
	std::cout << "Time to process a range of " << vec.size()
			  << " elements with std::vector : " << time_vec << " us" << std::endl;
	std::cout << "Time to process a range of " << deq.size()
			 << " elements with std::deque : " << time_deq << " us" << std::endl;
}

PmergeMe::PmergeMe(int count, char **arg)
{
	if (parse_and_fill(count, arg))
		execute();
}

