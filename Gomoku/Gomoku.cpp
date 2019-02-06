#include "stdafx.h"

#include <fstream>
#include <iostream>
#include <string>
#include "Board.h"
#include "IA.h"

int main()
{
	Board	*board = new Board(20);
	while (true)
	{
		std::string string;
		std::getline(std::cin, string);

		try
		{
			if (string.size() >= 5 && string.compare("ABOUT") == 0)
				std::cout << "name=\"jonathan\", version=\"1.0\", author=\"Nymand\", country=\"USA\"" << std::endl;
			else if (string.size() >= 7 && string.compare("RESTART") == 0)
			{
				int nb = board->getSide();
				delete board;
				board = new Board(nb);
				std::cout << "OK" << std::endl;
			}
			else if (string.size() >= 3 && string.compare("END") == 0)
				return (0);
			else if (string.size() >= 7 && string.substr(0, 5).compare("START") == 0)
			{
				int i = std::atoi(string.substr(6).c_str());
				if (i > 0)
				{
					std::cout << "OK" << std::endl;
					delete board;
					board = new Board(i);
				}
				else
				{
					std::cout << "ERROR unsupported size" << std::endl;
				}
			}
			else if (string.size() >= 5 && string.substr(0, 5).compare("BEGIN") == 0)
			{
				board->feed(board->getSide() / 2, board->getSide() / 2, 1, true);
				std::cout << board->getSide() / 2 << "," << board->getSide() / 2 << std::endl;
			}
			else if (string.size() >= 8 && string.substr(0, 4).compare("TURN") == 0)
			{
				int nb = string.find(',');
				board->feed(std::atoi(string.substr(5, nb - 5).c_str()), std::atoi(string.substr(nb + 1, string.find(',', nb + 1) - nb + 1).c_str()), 2, true);
			}
			else if (string.size() >= 5 && string.compare("BOARD") == 0)
			{
				board->clear();
				board->fill();
			}
			if ((string.size() >= 5 && string.compare("BOARD") == 0) || (string.size() >= 8 && string.substr(0, 4).compare("TURN") == 0))
			{
				IA	ia(board);
				int	*coord = new int[2];

				coord = ia.Play();
				std::cout << coord[0] << "," << coord[1] << std::endl;
				board->feed(coord[0], coord[1], 1, true);
			}
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	return 0;
}