#include "Puzzles\Day1Puzzle1.h"

#include <iostream>

template <class TPuzzle>
void Solve()
{
    TPuzzle puzzle;
    std::cout << puzzle.Solve();
}

int main()
{
    Solve<Day1Puzzle1>();
    return 0;
}

