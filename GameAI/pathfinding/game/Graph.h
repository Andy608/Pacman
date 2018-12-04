#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <map>
#include <Trackable.h>
#include "Node.h"

class Connection;

class Graph : public Trackable
{
public:
	Graph();
	virtual ~Graph();

	virtual void init();

	std::vector<Connection*> getConnections(const Node& from);
	std::vector<Connection*> getConnections(const NODE_ID& fromId);

	Node* getNode(int index);

protected:
	std::vector<Node*> mNodes;
	std::vector<Connection*> mConnections;
	std::map<NODE_ID, std::vector<Connection*>> mConnectionMap;
};

#endif