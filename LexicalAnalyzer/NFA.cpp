#include "NFA.h"
/*正则树转NFA*/
void NFA::RE_to_NFA()
{
	Thompson(regtree.getroot());
	//把所有的edge存入alledge，供DFA中的操作使用
	for (auto &node : allnodes) {
		for (auto &edge : node.edges) {
			alledges.insert({ edge.c, &edge });
		}
	}
}

int NFA::getStart()
{
	return start;
}

int NFA::getAccept()
{
	return accept;
}

std::set<char> NFA::getalphabets()
{
	return regtree.alphabets;
}

int NFA::NewNode()
{
	allnodes.push_back(NFANode(allnodes.size()));
	return allnodes.size() - 1;
}

void NFA::AddEdge(int from, int to, char c)
{
	allnodes[from].edges.push_back(NFAedge(from, to, c));
}

void NFA::resetvisit()
{
	for (auto &n : allnodes) {
		n.visit = false;
	}
}

void NFA::Thompson(ReTreeNode * retree)
{
	if (retree->kind == ELEMENT) {
		int from = NewNode();
		int to = NewNode();
		AddEdge(from, to, retree->c);
		start = from;
		accept = to;
	}
	else if (retree->kind == ALT) {
		int from = NewNode();
		int to = NewNode();
		Thompson(retree->childs[0]);
		AddEdge(from, start, EPS);
		AddEdge(accept, to, EPS);
		Thompson(retree->childs[1]);
		AddEdge(from, start, EPS);
		AddEdge(accept, to, EPS);
		start = from;
		accept = to;
	}
	else if (retree->kind == CONCAT) {
		int from = NewNode();
		int to = NewNode();
		Thompson(retree->childs[0]);
		AddEdge(from, start, EPS);
		int temp = accept;
		Thompson(retree->childs[1]);
		AddEdge(temp, start, EPS);
		AddEdge(accept, to, EPS);
		start = from;
		accept = to;
	}
	else if (retree->kind == CLOSURE) {
		int from = NewNode();
		int to = NewNode();
		Thompson(retree->childs[0]);
		AddEdge(accept, start, EPS);
		AddEdge(from, to, EPS);
		AddEdge(from, start, EPS);
		AddEdge(accept, to, EPS);
		start = from;
		accept = to;
	}
	else {
		int from = NewNode();
		int to = NewNode();
		Thompson(retree->childs[0]);
		AddEdge(from, to, EPS);
		AddEdge(from, start, EPS);
		AddEdge(accept, to, EPS);
		start = from;
		accept = to;
	}
}

NFA::NFA(const std::string & reg):regtree(reg)
{
	accept = start = 0;
	RE_to_NFA();
}

NFA::NFA()
{
}

std::vector<NFANode>& NFA::getallnodes()
{
	return allnodes;
}

std::multimap<char, NFAedge*>& NFA::getalledges()
{
	return alledges;
}
