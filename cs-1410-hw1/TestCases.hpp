#include <functional>
#include <string>
#include <vector>

#include "Bug.hpp"


bool compareVectors(std::vector<Bug> one, std::vector<Bug> two);
bool testCase1(std::vector<Bug> bugs);
bool testCase2(std::vector<Bug> bugs);
bool testCase3(std::vector<Bug> bugs);
bool testCase4(std::vector<Bug> bugs);
void executeTest(std::function<bool(std::vector<Bug>)> testCase, std::vector<Bug> bugs, std::string label);
