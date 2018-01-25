// A02225762
// Ethan Watson
// HW 1

#include <iostream>
#include <vector>

#include "Bug.hpp"
#include "TestCases.hpp"

void printBugs(std::vector<Bug> bugs)
{
	//TODO:write a function that prints all the contents of the
    //     bug array.  Use Bug::print() for each bug.

    for (int i = 0; i < bugs.size(); i++)
    {
        bugs[i].print(); // Get current bug from vector and print it
    }
}

void sortMass(std::vector<Bug>& bugs)
{
	//TODO:write a function to bubble sort the contents of a
	//     bug array based on the mass

    for (int i = 0; i < bugs.size(); i++)
    {
        for (int j = 0; j < bugs.size() - 1 - i; j++)
        {
            if (bugs[j].getMass() < bugs[j + 1].getMass())
            {
                std::swap(bugs[j], bugs[j + 1]);
            }
        }
    }
}

int main()
{
	const unsigned int NUMBUGS = 5;
    const int NUM_TO_ADD = 3;
    const int NUM_TO_REMOVE = 5;

	//TODO: make a vector of NUMBUGS bugs

    std::vector<Bug> bugs(NUMBUGS);

	//end of TODO

	std::cout << std::endl << "-- Initial Bugs --" << std::endl << std::endl;
	printBugs(bugs);
	executeTest(testCase1, bugs, "Initial Bugs");

	//TODO: add three more bugs to the vector

    for (int i = 0; i < NUM_TO_ADD; i++)
    {
        bugs.push_back(Bug());
    }

	//end of TODO

	std::cout << std::endl << "-- Three More Bugs --" << std::endl << std::endl;
	printBugs(bugs);
	executeTest(testCase2, bugs, "Three More Bugs");

	sortMass(bugs);

	std::cout << std::endl << "-- Sorted By Mass --" << std::endl << std::endl;
	printBugs(bugs);
	executeTest(testCase3, bugs, "Sorted By Mass");

	//TODO: get rid of the 5 bugs with the greatest mass

    for (int i = 0; i < NUM_TO_REMOVE; i++)
    {
        bugs.erase(bugs.begin());
    }

	//end of TODO

	std::cout << std::endl << "-- Removed Five Biggest --" << std::endl << std::endl;
	printBugs(bugs);
	executeTest(testCase4, bugs, "Removed Five Biggest");

	return 0;
}
