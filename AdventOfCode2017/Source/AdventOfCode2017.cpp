#include "Puzzles\Day1.h"
#include "Puzzles\Day2.h"
#include "Puzzles\Day3.h"
#include "Puzzles\Day4.h"
#include "Puzzles\Day5.h"
#include "Puzzles\Day6.h"
#include "Puzzles\Day7.h"

#include <iostream>

using namespace std;


template <class TPuzzle>
void Solve(int number)
{
    TPuzzle puzzle;
	std::cout << "Day " << number << endl;
    std::cout << puzzle.Solve() << endl;
	std::cout << endl;
}

#define SOLVE(n) Solve<Day ## n>(n);

int main()
{
	//SOLVE(1)
	//SOLVE(2)
	//SOLVE(3)
	//SOLVE(4)
	//SOLVE(5)
	//SOLVE(6)
	SOLVE(7)
	system("pause");
    return 0;
}

