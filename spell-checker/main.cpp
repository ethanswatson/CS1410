#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "BinarySearchTree.hpp"

void testTree()
{
    BinarySearchTree<std::string> tree;
    //
    // Add a bunch of values to the tree
    tree.insert("Olga");
    tree.insert("Tomeka");
    tree.insert("Benjamin");
    tree.insert("Ulysses");
    tree.insert("Tanesha");
    tree.insert("Judie");
    tree.insert("Tisa");
    tree.insert("Santiago");
    tree.insert("Chia");
    tree.insert("Arden");

    //
    // Make sure it displays in sorted order
    tree.display();

    //
    // Try to add a duplicate
    std::cout << std::endl << "---- adding a duplicate ----" << std::endl;
    if (tree.insert("Tomeka"))
    {
        std::cout << "oops, shouldn't have returned true from the insert" << std::endl;
    }
    tree.display();

    //
    // Remove an existing value from the tree
    std::cout << std::endl << "---- removing an existing value ----" << std::endl;
    tree.remove("Olga");
    tree.display();

    //
    // Remove a value that was never in the tree, hope it doesn't crash!
    tree.remove("Karl");

    //
    // Check the tree stats
    std::cout << std::endl << "---- checking the tree stats ----" << std::endl;
    std::cout << "Expecting 9 nodes, found " << tree.numberNodes() << std::endl;
    std::cout << "Expecting 4 leaf nodes, found " << tree.numberLeafNodes() << std::endl;
    std::cout << "Expecting height of 6, found " << tree.height() << std::endl;
}

BinarySearchTree<std::string> loadDictionary()
{
    std::ifstream input("Dictionary.txt");

    if (!input)
    {
        throw std::string("File Not Found");
    }

    BinarySearchTree<std::string> dictionary;

    std::string line;
    std::vector<std::string> vec;

    while (std::getline(input, line))
    {
        vec.push_back(line);
    }

    std::random_shuffle(vec.begin(), vec.end());

    for (unsigned int i = 0; i < vec.size(); i++)
    {
        dictionary.insert(vec[i]);
    }

    std::cout << "-- Tree Stats --" << std::endl << std::endl;
    std::cout << "Total Nodes: " << dictionary.numberNodes() << std::endl;
    std::cout << "Leaf Nodes: " << dictionary.numberLeafNodes() << std::endl;
    std::cout << "Tree Height: " << dictionary.height() << std::endl;

    return dictionary;
}

void removePunctuation(std::string& word)
{
    std::string::iterator it;

    for (unsigned int i = 0; i < word.length(); i++)
    {
        char c = word[i];

        switch (c)
        {
            case ',':
            case ':':
            case '.':
            case '!':
            case '?':
            case '(':
            case ')':
                it = word.begin() + i;
                word.erase(it);
                break;
        }
    }
}

std::vector<std::string> loadLetter()
{
    std::ifstream input("Letter.txt");

    if (!input)
    {
        throw std::string("File Not Found");
    }

    std::string word;
    std::vector<std::string> words;

    while (input >> word)
    {
        removePunctuation(word);
        words.push_back(word);
    }

    return words;
}

std::vector<std::string> checkSpelling(BinarySearchTree<std::string>& dictionary, std::vector<std::string> letter)
{
    std::vector<std::string> incorrectWords;

    for (unsigned int i = 0; i < letter.size(); i++)
    {
        if (!dictionary.search(letter[i]))
        {
            incorrectWords.push_back(letter[i]);
        }
    }

    return incorrectWords;
}

int main()
{
    //testTree();

    BinarySearchTree<std::string> dictionary = loadDictionary();
    std::vector<std::string> letter = loadLetter();
    std::vector<std::string> incorrectWords = checkSpelling(dictionary, letter);

    std::cout << "Misspelled words : " << std::endl;

    for (unsigned int i = 0; i < incorrectWords.size(); i++)
    {
        std::cout << incorrectWords[i] << std::endl;
    }

    return 0;
}