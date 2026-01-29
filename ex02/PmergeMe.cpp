#include "PmergeMe.hpp"
#include <cctype>
//#include <cstdint>
#include <iterator>
#include <limits>
#include <string>
#include <cstdlib>
//#include <limits.h>

PmergeMe::PmergeMe() { }

PmergeMe::~PmergeMe() { }

PmergeMe::PmergeMe(const PmergeMe &other) { *this = other; }

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		vec = other.vec;
		deq = other.deq;
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
		long	res;

		res = std::atol(arg[i]);
		if (res < 0 || res > std::numeric_limits<int>::max())
		{
			std::cerr << "Error : program only accepts positive int" << std::endl;
			return false;
		}
		vec.push_back(static_cast<int>(res));
		deq.push_back(static_cast<int>(res));
	}
	return true;
}

//******************DEQUE******************

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


static std::deque<size_t> build_jacob_deq(size_t max_pairs)
{
	std::deque<size_t>	jac;

	jac.push_back(1);
	jac.push_back(3);
	while (jac.back() < max_pairs)
		jac.push_back(jac[jac.size() - 1] + 2 * jac[jac.size() - 2]);
	return (jac);
}

static std::deque<size_t> build_full_order_deq(size_t max_pairs)
{
	std::deque<size_t>	jac;
	std::deque<size_t>	order;
	size_t			prev;
	size_t			curr;

	jac = build_jacob_deq(max_pairs);
	prev = 1;
	for (size_t i = 0; i < jac.size(); i++)
	{
		curr = jac[i];
		if (curr > max_pairs)
			curr = max_pairs;
		for (size_t j = curr; j > prev; j--)
			order.push_back(j - 1);
		prev = curr;
	}
	return (order);
}

static std::deque<size_t> get_jacob_order_deq(size_t max_pairs)
{
	static std::deque<size_t>	jacob_full_order;

	if (jacob_full_order.empty())
		jacob_full_order = build_full_order_deq(max_pairs);

	return (jacob_full_order);
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
	std::deque<std::pair<int, int> >	pairs;
	size_t			i;
	int			straggler = -1;
	bool			hasStraggler = false;

	for (i = 0; i + 1 < deq.size(); i += 2)
	{
		if (deq[i] > deq[i + 1])
			pairs.push_back(std::make_pair(deq[i + 1], deq[i]));
		else
			pairs.push_back(std::make_pair(deq[i], deq[i + 1]));
	}

	if (i < deq.size())
	{
		straggler = deq[i];
		hasStraggler = true;
	}

	std::deque<int> largerElements;
	for (size_t j = 0; j < pairs.size(); j++)
		largerElements.push_back(pairs[j].second);

	mergeInsertSortDeq(largerElements);

	std::deque<int>			&result = largerElements;
	const std::deque<size_t>	&order = get_jacob_order_deq(pairs.size());

	for (size_t k = 0; k < order.size(); k++)
	{
		size_t	j = order[k];
		int	smaller = pairs[j].first;

		std::deque<int>::iterator it = std::lower_bound(result.begin(), result.end(), smaller);
		result.insert(it, smaller);
	}

	if (hasStraggler)
	{
		std::deque<int>::iterator it = std::lower_bound(result.begin(), result.end(), straggler);
		result.insert(it, straggler);
	}

	deq = result;
}


//	******************VECTOR******************

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

static std::vector<size_t> build_jacob_vec(size_t max_pairs)
{
	std::vector<size_t>	jac;

	jac.push_back(1);
	jac.push_back(3);
	while (jac.back() < max_pairs)
		jac.push_back(jac[jac.size() - 1] + 2 * jac[jac.size() - 2]);
	return (jac);
}

static std::vector<size_t> build_full_order_vec(size_t max_pairs)
{
	std::vector<size_t>	jac;
	std::vector<size_t>	order;
	size_t			prev;
	size_t			curr;

	jac = build_jacob_vec(max_pairs);
	prev = 1;
	for (size_t i = 0; i < jac.size(); i++)
	{
		curr = jac[i];
		if (curr > max_pairs)
			curr = max_pairs;
		for (size_t j = curr; j > prev; j--)
			order.push_back(j - 1);
		prev = curr;
	}
	return (order);
}

static std::vector<size_t> get_jacob_order_vec(size_t max_pairs) 
{
	static std::vector<size_t>	jacob_full_order;

	if (jacob_full_order.empty())
		jacob_full_order = build_full_order_vec(max_pairs);

	return (jacob_full_order);
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
	std::vector<std::pair<int, int> >	pairs;
	size_t			i;
	int			straggler = -1;
	bool			hasStraggler = false;

	for (i = 0; i + 1 < vec.size(); i += 2)
	{
		if (vec[i] > vec[i + 1])
			pairs.push_back(std::make_pair(vec[i + 1], vec[i]));
		else
			pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
	}
	if (i < vec.size())
	{
		straggler = vec[i];
		hasStraggler = true;
	}

	std::vector<int>	largerElements;
	for (size_t j = 0; j < pairs.size(); j++)
		largerElements.push_back(pairs[j].second);

	mergeInsertSortVec(largerElements);

	std::vector<int>	&result = largerElements; //doing that just so it's named result ngl
	const std::vector<size_t>	&order = get_jacob_order_vec(pairs.size());

	for (size_t k = 0; k < order.size(); k++)
	{
		size_t	j = order[k];
		int	smaller = pairs[j].first;

		std::vector<int>::iterator it = std::lower_bound(result.begin(), result.end(), smaller);
		result.insert(it, smaller);
	}

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

	if (!is_sorted(vec) || !is_sorted(deq))
	{
		std::cerr << "Unsorted! what!?" << std::endl;
		return;
	}

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

