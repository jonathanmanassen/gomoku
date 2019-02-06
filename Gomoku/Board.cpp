#include "stdafx.h"

#include <iostream>
#include <string>
#include "Board.h"

Board::Board(const int &side) : side(side)
{
	map = new piece*[side];
	for (int i = 0; i < side; i++)
	{
		map[i] = new piece[side];
		for (int j = 0; j < side; j++)
		{
			map[i][j] = piece::EMPTY;
		}
	}
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 4; j++)
			series[i][j] = 0;
}

Board::~Board()
{
}

void	Board::removeOccupied()
{
	for (auto i = lookT.begin(); i != lookT.end(); )
	{
		if (map[i->first][i->second] != piece::EMPTY)
		{
			i = lookT.erase(i);
		}
		else
			++i;
	}
}

void Board::feed(const int &x, const int &y, const int &whoPlaced, const bool &real, int **thisSerie)
{
	map[x][y] = static_cast<piece>(whoPlaced);
	if (real == true)
	{
		for (int i = x - 1; i <= x + 1; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				if (j >= 0 && j < side && i >= 0 && i < side && map[i][j] == piece::EMPTY)
				{
					lookT.push_front(std::make_pair(i, j));
				}
			}
		}
		removeOccupied();
	}
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 4; j++)
			series[i][j] = 0;
	oneSerie(x, y, whoPlaced);
	if (thisSerie != nullptr)
	{
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 4; j++)
				thisSerie[i][j] = series[i][j];
	}
}

void	Board::countHorVer()
{
	for (int x = 0; x < side; x++)
	{
		int count[2] = { 0, 0 };
		int	around[2] = { 0, 0 };
		bool	check[2] = { false, false };
		piece	whoPlaced[2] = { piece::EMPTY, piece::EMPTY };

		for (int y = 0; y < side; y++)
		{
			for (int i = 0; i < 2; i++)
			{
				piece	piece;
				if (i == 0)
					piece = map[x][y];
				else
					piece = map[y][x];
				if (whoPlaced[i] == piece::EMPTY && piece != piece::EMPTY)
					whoPlaced[i] = piece;
				if (piece == piece::EMPTY && count[i] == 0)
					around[i] = 1;
				else if (piece == piece::EMPTY && count[i] != 0)
				{
					around[i]++;
					check[i] = true;
				}
				else if (piece == whoPlaced[i])
					count[i]++;
				else
					check[i] = true;
				if (count[i] == 5)
					check[i] = true;
				if (check[i] == true)
				{
					if (count[i] == 2 && around[i] > 0)
						series[static_cast<int>(whoPlaced[i]) - 1][0] += 1 + (around[i] - 1) * 9;
					if (count[i] == 3 && around[i] > 0)
						series[static_cast<int>(whoPlaced[i]) - 1][1] += 1 + (around[i] - 1) * 18;
					if (count[i] == 4 && around[i] > 0)
						series[static_cast<int>(whoPlaced[i]) - 1][2] += 1 + (around[i] - 1) * 99;
					if (count[i] >= 5)
						series[static_cast<int>(whoPlaced[i]) - 1][3]++;
					count[i] = 0;
					check[i] = false;
					whoPlaced[i] = piece::EMPTY;
					if (piece != piece::EMPTY)
					{
						whoPlaced[i] = piece;
						count[i]++;
						around[i] = 0;
					}
					else
						around[i] = 1;
				}
			}
		}
	}
}

void	Board::countDiag()
{
	for (int a = side - 1; a >= 0; a--)
	{
		int count[2] = { 0, 0 };
		int	around[2] = { 0, 0 };
		bool	check[2] = { false, false };
		piece	whoPlaced[2] = { piece::EMPTY, piece::EMPTY };

		for (int y = a, x = 0; y < side; y++, x++)
		{
			for (int i = 0; i < 2; i++)
			{
				piece	piece;
				if (i == 0)
					piece = map[x][y];
				else
					piece = map[side - 1 - x][y];
				if (whoPlaced[i] == piece::EMPTY && piece != piece::EMPTY)
					whoPlaced[i] = piece;
				if (piece == piece::EMPTY && count[i] == 0)
					around[i] = 1;
				else if (piece == piece::EMPTY && count[i] != 0)
				{
					around[i]++;
					check[i] = true;
				}
				else if (piece == whoPlaced[i])
					count[i]++;
				else
					check[i] = true;
				if (count[i] == 5)
					check[i] = true;
				if (check[i] == true)
				{
					if (count[i] == 2 && around[i] > 0)
						series[static_cast<int>(whoPlaced[i]) - 1][0] += 1 + (around[i] - 1) * 9;
					if (count[i] == 3 && around[i] > 0)
						series[static_cast<int>(whoPlaced[i]) - 1][1] += 1 + (around[i] - 1) * 18;
					if (count[i] == 4 && around[i] > 0)
						series[static_cast<int>(whoPlaced[i]) - 1][2] += 1 + (around[i] - 1) * 99;
					if (count[i] >= 5)
						series[static_cast<int>(whoPlaced[i]) - 1][3]++;
					count[i] = 0;
					check[i] = false;
					whoPlaced[i] = piece::EMPTY;
					if (piece != piece::EMPTY)
					{
						whoPlaced[i] = piece;
						count[i]++;
						around[i] = 0;
					}
					else
						around[i] = 1;
				}
			}
		}
	}
	for (int a = side - 1; a > 0; a--)
	{
		int count[2] = { 0, 0 };
		int	around[2] = { 0, 0 };
		bool	check[2] = { false, false };
		piece	whoPlaced[2] = { piece::EMPTY, piece::EMPTY };

		for (int x = a, y = 0; x < side; y++, x++)
		{
			for (int i = 0; i < 2; i++)
			{
				piece	piece;
				if (i == 0)
					piece = map[x][y];
				else
					piece = map[side - 1 - x][y];
				if (whoPlaced[i] == piece::EMPTY && piece != piece::EMPTY)
					whoPlaced[i] = piece;
				if (piece == piece::EMPTY && count[i] == 0)
					around[i] = 1;
				else if (piece == piece::EMPTY && count[i] != 0)
				{
					around[i]++;
					check[i] = true;
				}
				else if (piece == whoPlaced[i])
					count[i]++;
				else
					check[i] = true;
				if (count[i] == 5)
					check[i] = true;
				if (check[i] == true)
				{
					if (count[i] == 2 && around[i] > 0)
						series[static_cast<int>(whoPlaced[i]) - 1][0] += 1 + (around[i] - 1) * 9;
					if (count[i] == 3 && around[i] > 0)
						series[static_cast<int>(whoPlaced[i]) - 1][1] += 1 + (around[i] - 1) * 18;
					if (count[i] == 4 && around[i] > 0)
						series[static_cast<int>(whoPlaced[i]) - 1][2] += 1 + (around[i] - 1) * 99;
					if (count[i] >= 5)
						series[static_cast<int>(whoPlaced[i]) - 1][3]++;
					count[i] = 0;
					check[i] = false;
					whoPlaced[i] = piece::EMPTY;
					if (piece != piece::EMPTY)
					{
						whoPlaced[i] = piece;
						count[i]++;
						around[i] = 0;
					}
					else
						around[i] = 1;
				}
			}
		}
	}
}

void	Board::countSeries()
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 4; j++)
			series[i][j] = 0;
	countHorVer();
	countDiag();
}

void	Board::oneSerie(const int &x, const int &y, const int &whoPlaced)
{
	int	around[2][4] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };
	int	count[4] = { 1, 1, 1, 1 };
	bool	stop[4] = { false, false, false, false };

	for (int i = x - 1, j = y - 1, k = x + 1; i >= x - 4; i--, j--, k++)
	{
		for (int l = 0; l < 4; l++)
		{
			if (stop[l] == true)
				continue;
			piece	p;
			if (l > 0 && (j < 0 || j >= side))
				continue;
			else if (l % 2 == 0 && (i < 0 || i >= side))
				continue;
			else if (l == 3 && (k < 0 || k >= side))
				continue;
			if (l == 0)
				p = map[i][y];
			else if (l == 1)
				p = map[x][j];
			else if (l == 2)
				p = map[i][j];
			else
				p = map[k][j];
			if (p == static_cast<piece>(whoPlaced) && around[0][l] == 0)
				count[l]++;
			else if (p == piece::EMPTY)
				around[0][l]++;
			else if (p != static_cast<piece>(whoPlaced))
				stop[l] = true;
		}
	}
	for (int i = 0; i < 4; i++)
		stop[i] = false;
	for (int i = x + 1, j = y + 1, k = x - 1; i <= x + 4; i++, j++, k--)
	{
		for (int l = 0; l < 4; l++)
		{
			if (stop[l] == true)
				continue;
			piece	p;
			if (l > 0 && (j < 0 || j >= side))
				continue;
			else if (l % 2 == 0 && (i < 0 || i >= side))
				continue;
			else if (l == 3 && (k < 0 || k >= side))
				continue;
			if (l == 0)
				p = map[i][y];
			else if (l == 1)
				p = map[x][j];
			else if (l == 2)
				p = map[i][j];
			else
				p = map[k][j];
			if (p == static_cast<piece>(whoPlaced) && around[1][l] == 0)
				count[l]++;
			else if (p == piece::EMPTY)
				around[1][l]++;
			else if (p != static_cast<piece>(whoPlaced))
				stop[l] = true;
		}
	}
	for (int l = 0; l < 4; l++)
	{
		if (count[l] == 2 && (around[0][l] + around[1][l]) >= 3)
			series[whoPlaced - 1][0] += 1 + ((around[0][l] > 0 && around[1][l] > 0) ? 1 : 0) * 9;
		if (count[l] == 3 && (around[0][l] + around[1][l]) >= 2)
			series[whoPlaced - 1][1] += 1 + ((around[0][l] > 0 && around[1][l] > 0) ? 1 : 0) * 18;
		if (count[l] == 4 && (around[0][l] + around[1][l]) >= 1)
			series[whoPlaced - 1][2] += 1 + ((around[0][l] > 0 && around[1][l] > 0) ? 1 : 0) * 99;
		if (count[l] >= 5)
			series[whoPlaced - 1][3]++;
	}
}

void	Board::clear()
{
	for (int i = 0; i < side; i++)
	{
		for (int j = 0; j < side; j++)
			map[i][j] = piece::EMPTY;
	}
}

void	Board::fill()
{
	std::string	str;

	std::getline(std::cin, str);
	while (str.size() >= 4 && str.compare("DONE") != 0)
	{
		size_t i = 0;
		int values[3];

		for (int j = 0; j < 2; j++)
		{
			values[j] = std::atoi(str.substr(i, str.find(i, ',') - i).c_str());
			i = str.find(',', i) + 1;
		}
		values[2] = std::atoi(str.substr(i).c_str());
		feed(values[0], values[1], values[2], true);
		std::getline(std::cin, str);
	}
}

void	Board::show()
{
	for (int i = 0; i < side; i++)
	{
		for (int j = 0; j < side; j++)
		{
			std::cout << static_cast<int>(map[j][i]);
		}
		std::cout << std::endl;
	}
}
