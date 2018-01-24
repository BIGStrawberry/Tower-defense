#include "PathNode.h"



PathNode::PathNode(bool passable, int index) :
	H(0),
	G(0),
	F(0),
	passable(passable),
	list(PathNodeList::None),
	index(index),
	parent(nullptr)
{
}

PathNode::PathNode():
	H(0),
	G(0),
	F(0),
	passable(true),
	list(PathNodeList::None),
	index(0),
	parent(nullptr)
{
}

void PathNode::setH(int h)
{
	H = h;
}

void PathNode::setG(int g)
{
	G = g;
	F = H + G;
}

void PathNode::setF(int f)
{
	F = f;
}

void PathNode::setList(PathNodeList l)
{
	list = l;
}

void PathNode::setPassable(bool p)
{
	passable = p;
}

void PathNode::setParent(PathNode* p)
{
	parent = p;
}

void PathNode::setNeighbour(PathNode* n)
{
	neighbours.push_back(n);
}

void PathNode::setIndex(int i)
{
	index = i;
}


int PathNode::getIndex()
{
	return index;
}

PathNodeList PathNode::getList()
{
	return list;
}

PathNode * PathNode::getParent()
{
	return parent;
}

bool PathNode::isPassable()
{
	return passable;
}

int PathNode::getG()
{
	return G;
}

int PathNode::getF()
{
	return F;
}

std::vector<PathNode*>& PathNode::getNeighbours()
{
	return neighbours;
}


void PathNode::reset(bool p)
{
	H = 0;
	G = 0;
	F = 0;
	passable = p;
	list = PathNodeList::None;
	parent = nullptr;
}