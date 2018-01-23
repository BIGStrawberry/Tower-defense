#pragma once
#include <vector>
#include "PathNodeList.h"


/**
* @class PathNode
* @brief Used by Pathfinder
* @details This class represents a tile in the grid. It has
* all the needed variables for A* pathfinding to work.
*/
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
	/**
	* @brief PathNode Constructor
	* @param bool		The corresponding tile is passable
	* @param int:		Index of the tile on the array.
	*/
	PathNode(bool passable, int index);
	/**
	* @brief PathNode Default Constructor
	*/
	PathNode();

	/**
	* @brief setter for H value
	*/
	void setH(int h);

	/**
	* @brief setter for G value
	*/
	void setG(int g);

	/**
	* @brief setter for F value
	*/
	void setF(int f);

	/**
	* @brief setter for the list on which the instance is to be found
	*/
	void setList(PathNodeList l);

	/**
	* @brief setter for passable state
	*/
	void setPassable(bool p);

	/**
	* @brief setter for parent
	*/
	void setParent(PathNode* p);

	/**
	* @brief setter for neighbours
	*/
	void setNeighbour(PathNode* n);

	/**
	* @brief setter for index
	*/
	void setIndex(int i);

	/**
	* @brief getter for index
	*/
	int getIndex();

	/**
	* @brief getter for list value
	*/
	PathNodeList getList();

	/**
	* @brief getter for parent
	*/
	PathNode* getParent();

	/**
	* @brief getter for passbale state
	*/
	bool isPassable();


	/**
	* @brief getter for G value
	*/
	int getG();

	/**
	* @brief getter for F value
	*/
	int getF();

	/**
	* @brief getter for neighbours
	*/
	std::vector<PathNode*>& getNeighbours();


	/**
	* @brief resets node's value
	* @details This function resets the values to default.
	* Passable state is set to the given bool. (true = passable)
	*/
	void reset(bool p);
};