/**
* Definition for undirected graph.*/
 
#include <map>
#include <stack>
#include <vector>
struct UndirectedGraphNode {
     int label;
     std::vector<UndirectedGraphNode *> neighbors;
     UndirectedGraphNode(int x) : label(x) {};
 };

typedef UndirectedGraphNode UGN;

class Solution {
public:
	std::map<UGN *, UGN *> o2n; // map the old node to new node.

	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
		// solution 1. try the depth-first search 
		if (node == nullptr)
			return nullptr;

		std::stack<UGN *> s;
		s.push(node);
		while (s.size())
		{
			UGN *temp = s.top();
			s.pop();

			if (o2n.count(temp) == 1)
			{
				// visited already.
			}
			else
			{
				o2n[temp] = nullptr; // to visite;
				for (unsigned int i = 0; i < temp->neighbors.size(); ++i)
				{
					s.push(temp->neighbors[i]);
				}
			}
		}
		//s.clear();

		// copy all the nodes.
		for (std::map<UGN *, UGN *>::iterator it = o2n.begin(); it != o2n.end(); ++it)
		{
			UGN *o = it->first;
			UGN *n = new UGN(o->label);
			it.second = n;
		}
		for (std::map<UGN *, UGN *>::iterator it = o2n.begin(); it != o2n.end(); ++it)
		{
			UGN *o = it.first;
			UGN *n = it.second;

			for (unsigned int i = 0; i < o->neighbors.size(); ++i)
			{
				n->neighbors.push_back(o2n[o->neighbors[i]]);
			}
		}
		return o2n[node];

		// solution 2. try the breadth-first search
	}
};