#pragma once

#include <vector>
#include <list>
#include <iostream>

class Board
{
public:
	enum class piece : int
	{
		EMPTY = 0,
		OWN = 1,
		OTHER = 2
	};

	Board(const int&);
	~Board();

	void	feed(const int&, const int&, const int&, const bool&, int** = nullptr);
	void	clear();
	void	fill();
	void	show();
	bool	isEmpty(const int &x, const int &y) { if (map[x][y] == piece::EMPTY) return true; return false; }
	void	countSeries();
	void	countHorVer();
	void	countDiag();
	void	removeOccupied();
	void	oneSerie(const int &x, const int &y, const int &whoPlaced);

	int		getSide() { return side; }
	int		getWinner() { if (series[0][3] > 0) return 1; else if (series[1][3] > 0) return -1; else if (series[1][2] >= 100) return -100000; return 0; }
	void	setWinner(const int &winner) { this->winner = winner; }
	void	setMap(const int &x, const int &y, const piece &p) { map[x][y] = p; }

private:
	int	side;
	int winner;
public:
	piece	**map;
	std::list<std::pair<int, int>>	lookT;
	int	series[2][4];
};