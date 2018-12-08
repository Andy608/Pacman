#include "PathfindingList.h"
#include <string>

PathfindingList::~PathfindingList()
{
	mNodeRecords.clear();
}

bool PathfindingList::contains(Node* node)
{
	auto iter = mNodeRecords.begin();
	for (; iter != mNodeRecords.end(); ++iter)
	{
		if ((*iter).node == node)
		{
			return true;
		}
	}

	return false;
}

bool PathfindingList::find(Node* node, NodeRecord& nodeRecord)
{
	auto iter = mNodeRecords.begin();
	for (; iter != mNodeRecords.end(); ++iter)
	{
		NodeRecord& currentRecord = (*iter);
		if (currentRecord.node == node)
		{
			nodeRecord = currentRecord;
			return true;
		}
	}

	std::cout << "There is no NodeRecord with that node in the list!" << std::endl;
	return false;
}

bool PathfindingList::getSmallestElement(NodeRecord& nodeRecord)
{
	if (mNodeRecords.size() > 0)
	{
		nodeRecord = *mNodeRecords.begin();
		return true;
	}
	else
	{
		std::cout << "The pathfinding list is empty!" << std::endl;
		return false;
	}
}

void PathfindingList::addBasedOnCost(NodeRecord& recordToAdd)
{
	auto iter = mNodeRecords.begin();
	for (; iter != mNodeRecords.end(); ++iter)
	{
		NodeRecord& currentRecord = *iter;

		if (recordToAdd.costSoFar <= currentRecord.costSoFar)
		{
			mNodeRecords.insert(iter, recordToAdd);
			return;
		}
	}

	mNodeRecords.push_back(recordToAdd);
}

void PathfindingList::addBasedOnEstimate(NodeRecord& recordToAdd)
{
	auto iter = mNodeRecords.begin();
	for (; iter != mNodeRecords.end(); ++iter)
	{
		NodeRecord& currentRecord = *iter;

		if (recordToAdd.estimatedTotalCost <= currentRecord.estimatedTotalCost)
		{
			mNodeRecords.insert(iter, recordToAdd);
			return;
		}
	}

	mNodeRecords.push_back(recordToAdd);
}

void PathfindingList::operator-=(NodeRecord& recordToRemove)
{
	auto iter = mNodeRecords.begin();
	for (; iter != mNodeRecords.end(); ++iter)
	{
		NodeRecord& currentRecord = *iter;

		if (currentRecord == recordToRemove)
		{
			mNodeRecords.erase(iter);
			break;
		}
	}
}

void PathfindingList::print()
{
	print(mNodeRecords);
}

void PathfindingList::print(std::list<NodeRecord> records)
{
	auto iter = records.begin();

	for (; iter != records.end(); ++iter)
	{
		std::cout << std::to_string((*iter).costSoFar) << " ";
	}

	std::cout << '\n';
}
