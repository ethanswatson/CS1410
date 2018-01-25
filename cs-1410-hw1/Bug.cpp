#include <iostream>
#include <algorithm>

#include "Bug.hpp"

//
// Reference: https://en.wikipedia.org/wiki/Linear_congruential_generator
//
int myRand()
{
	const unsigned int a = 1103515245;
	const unsigned int c = 12345;
	const unsigned long div = 2147483648 - 1;
	static unsigned int seed = 123456789;

	seed = (a * seed + c) % div;
	return seed;
}

Bug::Bug()
{
	m_legs = myRand() % 10;
	m_mass = myRand() % 10;
}

Bug::Bug(unsigned int legs ,unsigned int mass) :
	m_legs(legs),
	m_mass(mass)
{
}

void Bug::print()
{
	std::cout << "legs: " << m_legs;
	std::cout << " mass: " << m_mass;
	std::cout << std::endl;
}

void Bug::eat(unsigned int bites)
{
	// a bug is what it eats
	m_mass += bites;
	// if a bug's mass exceeds 10, it
	// uses 5 units to grow a new leg
	if (m_mass > 10)
	{
		m_mass = 5;
		m_legs++;
	}

}

void Bug::poop()
{
	// try the new bug diet!
	m_mass -= (std::rand() % std::min(m_mass, 5u));

	// if a bug trys to poop itself into 
	// oblivion, it loses a leg instead
	if (m_mass < 3)
	{
		if (m_legs > 0)
		{
			m_legs--;
		}
		m_mass = 3;
	}
}
