#pragma once

#include <iostream>
#include <string>
#include "Board.h"

class IA
{
	struct added
	{
		int	x;
		int	y;
		int	whoPlaced;
	};
public:
	IA(Board*);
	~IA();
	int	*Play();
	int	eval();
	int	alphabeta(const int &depth, const bool&, int alpha, int beta);
	void	changeList(std::list<std::pair<int, int>>&, const int&, const int&);

private:
	Board	*board;
	int depth = 4;
	int	alpha = INT_MIN;
	int score;
public:
	int		*coord = new int[2];
	int		***pieces;
	time_t	begin;
	time_t	end;
};