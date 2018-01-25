#ifndef _SORT_STATS_HPP
#define _SORT_STATS_HPP

#include <sstream>

struct SortStats
{
	int swapCount;
	int compareCount;
	double time;
};

std::string printSortStats(SortStats& rStats);

#endif // _SORT_STATS_HPP
