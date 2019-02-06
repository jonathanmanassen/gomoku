#include "stdafx.h"
#include <thread>
#include "IA.h"

int count = 0;

IA::IA(Board *board) : board(board)
{
	time(&begin);
	pieces = new int**[depth];
	for (int i = 0; i < depth; i++)
	{
		pieces[i] = new int*[2];
		for (int j = 0; j < 2; j++)
			pieces[i][j] = new int[4];
	}
}

IA::~IA()
{
}

int IA::eval()
{
	int scoreP1 = 0, scoreP2 = 0;

	for (int i = 0; i + 1 < depth; i += 2)
	{
		scoreP1 += pieces[i][0][0] + pieces[i][0][1] * 20 + pieces[i][0][2] * 400;
		scoreP2 += pieces[i + 1][1][0] + pieces[i + 1][1][1] * 20 + pieces[i + 1][1][2] * 400;
	}
	return scoreP1 - scoreP2;
}

void	IA::changeList(std::list<std::pair<int, int>> &tmp, const int &x, const int &y)
{
	for (int i = x - 1; i <= x + 1; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (j >= 0 && j < board->getSide() && i >= 0 && i < board->getSide() && board->isEmpty(i, j) == true)
			{
				tmp.push_front(std::make_pair(i, j));
			}
		}
	}
}

int	IA::alphabeta(const int &depth, const bool &player, int alpha, int beta)
{
	time(&end);
	if (difftime(end, begin) > 4)
	{
		return (0);
	}
	if (depth == 0 || (this->depth != depth && board->getWinner() != 0))
	{
		int win = board->getWinner();
		if (win != 0)
		{
			if (win > 0)
				return INT_MAX - (this->depth - depth) - win;
			else
				return INT_MIN + (this->depth - depth) - win;
		}
		return score;
	}
	int nb;
	if (player == true)
	{
		int value = INT_MIN;
		for (auto i = board->lookT.begin(); i != board->lookT.end(); ++i)
		{
			int x = i->first;
			int y = i->second;
			if (board->isEmpty(x, y) == true)
			{
				board->feed(x, y, 1, false, pieces[this->depth - depth]);
				score += pieces[this->depth - depth][0][0] + pieces[this->depth - depth][0][1] * 20 + pieces[this->depth - depth][0][2] * 400;
				if (depth == this->depth)
					beta = INT_MAX;
				if (value < (nb = alphabeta(depth - 1, false, alpha, beta)))
					value = nb;
				board->setMap(x, y, Board::piece::EMPTY);
				score -= pieces[this->depth - depth][0][0] + pieces[this->depth - depth][0][1] * 20 + pieces[this->depth - depth][0][2] * 400;
				if (alpha < value)
				{
					alpha = value;
					if (depth == this->depth)
					{
						if (difftime(end, begin) > 4)
						{
							return (0);
						}
						this->alpha = alpha;
						coord[0] = x;
						coord[1] = y;
					}
				}
			}
			if (beta <= alpha && depth != this->depth)
				return (value);
		}
		return (value);
	}
	else
	{
		int value = INT_MAX;
		for (auto i = board->lookT.begin(); i != board->lookT.end(); ++i)
		{
			int x = i->first;
			int y = i->second;
			if (board->isEmpty(x, y) == true)
			{
				board->feed(x, y, 2, false, pieces[this->depth - depth]);
				score -= pieces[this->depth - depth][1][0] + pieces[this->depth - depth][1][1] * 20 + pieces[this->depth - depth][1][2] * 400;
				if (value > (nb = alphabeta(depth - 1, true, alpha, beta)))
					value = nb;
				score += pieces[this->depth - depth][1][0] + pieces[this->depth - depth][1][1] * 20 + pieces[this->depth - depth][1][2] * 400;
				board->setMap(x, y, Board::piece::EMPTY);
				if (beta > value)
				{
					beta = value;
				}
			}
			if (beta <= alpha)
				return (value);
		}
		return (value);
	}
}

int *IA::Play()
{
	coord[0] = 0;
	coord[1] = 0;
	alphabeta(depth, true, alpha, INT_MAX);
	return (coord);
}