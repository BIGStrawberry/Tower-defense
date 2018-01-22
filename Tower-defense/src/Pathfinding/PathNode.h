#pragma once
#include <vector>
#include "PathNodeList.h"

class PathNode
{
private:
	int H;
	int G;
	int F;

	bool passable;
	PathNodeList list;
	int index;
	PathNode* parent;

	std::vector<PathNode*> neighbours;

public:
	PathNode(bool passable, int index);
	PathNode();

	void setH(int h);
	void setG(int g);
	void setF(int f);
	void setList(PathNodeList l);
	void setPassable(bool p);
	void setParent(PathNode* p);
	void setNeighbour(PathNode* n);
	void setIndex(int i);
	int getIndex();
	PathNodeList getList();
	PathNode* getParent();
	bool isPassable();

	int getG();
	int getF();
	std::vector<PathNode*>& getNeighbours();

	void reset(bool p);
};