
#include "SortStats.hpp"

std::string printSortStats(SortStats& rStats)
{
	std::stringstream ss;
	ss << rStats.compareCount << " compares, " << rStats.swapCount << " swap count, " << rStats.time << " seconds";
	return ss.str();
}
