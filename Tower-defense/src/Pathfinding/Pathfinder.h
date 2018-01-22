#pragma once
#include <exception>
#include <array>
#include <algorithm>
#include "PathNode.h"
#include "../tower/Tower.h"
#include <vector>
#include <memory>


class UnreachableBase : public std::exception
{
};


template<int N>
class Pathfinder
{
private:
	std::array<std::shared_ptr<Tower>, N>& tiles;
	std::array<PathNode, N> grid;
	std::vector<PathNode*> open_list;

	int row_length;

	PathNode* begin;
	PathNode* target;
	PathNode* active;

	void reset()
	{
		open_list.clear();
		for (int i = 0; i < N; ++i)
		{
			if (tiles[i])
			{
				grid[i].reset(false);
			}
			else
			{
				grid[i].reset(true);
			}
		}
		active = begin;
	}
	void setNeighbours(PathNode* node)
	{
		int idx = node->getIndex() - 1;
		if (idx >= 0)
		{
			node->setNeighbour(&grid[idx]);
		}
		idx += 2;
		if (idx < row_length)
		{
			node->setNeighbour(&grid[idx]);
		}
		idx = idx - 1 - row_length;
		if (idx >= 0)
		{
			node->setNeighbour(&grid[idx]);
		}
		idx += (row_length * 2);
		if (idx < N)
		{
			node->setNeighbour(&grid[idx]);
		}
	}


	void calculate_h()
	{
		int trow = target->getIndex() / row_length;
		int tcolumn = target->getIndex() / row_length;
		for (auto& node : grid)
		{
			int row = node.getIndex() / row_length;
			int column = node.getIndex() % row_length;
			node.setH(abs(trow - row) + abs(tcolumn - column));
		}
	}


public:
	Pathfinder(std::array<std::shared_ptr<Tower>, N>& tiles, int row_length, int s, int t) :
		tiles(tiles),
		row_length(row_length),
		begin(nullptr),
		target(nullptr),
		active(nullptr)
	{
		for (int i = 0; i < N; ++i)
		{
			if (tiles[i])
			{
				grid[i].setPassable(true);
			}
			else
			{
				grid[i].setPassable(false);
			}
			grid[i].setIndex(i);
		}
		for (auto& node : grid)
		{
			setNeighbours(&node);
		}
		target = &grid[s];
		begin = &grid[t];
		active = begin;
	}

	std::vector<int> find()
	{
		std::vector<int> path;
		reset();
		calculate_h();

		while (true)
		{
			active->setList(PathNodeList::Closed);
			for (auto n : active->getNeighbours())
			{
				if (n == target)
				{
					n->setParent(active);
					active = target;
					while (active != nullptr)
					{
						path.push_back(active->getIndex());
						active = active->getParent();
					}
					std::reverse(path.begin(), path.end());
					return path;
				}
				if (n->isPassable())
				{
					switch (n->getList())
					{
					case PathNodeList::None:
					{
						n->setList(PathNodeList::Open);
						open_list.push_back(n);
						n->setParent(active);
						n->setG(active->getG() + 10);
						break;
					}
					case PathNodeList::Open:
					{
						if (active->getG() + 10 < n->getG())
						{
							n->setParent(active);
							n->setG(active->getG() + 10);
						}
						break;
					}
					case PathNodeList::Closed:
					{
						break;
					}
					}
				}
			}
			if (open_list.size() == 0)
			{
				throw UnreachableBase();
			}
			active = open_list[0];
			for (auto n : open_list)
			{
				if (n->getF() < active->getF())
				{
					active = n;
				}
			}
			open_list.erase(std::remove(open_list.begin(), open_list.end(), active));
		}
	}
};