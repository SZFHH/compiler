#pragma once
#include"DFA.h"
struct MDFANode{
	bool accept;
	int num;
	std::set<int> vertex;
	std::vector<MDFAedge> edges;
	MDFANode(bool accept, int num, const std::set<int> &vertex) {
		this->accept = accept;
		this->num = num;
		this->vertex = vertex;
	}
};

struct MDFAedge {
	int from, to;
	char c;
	MDFAedge(int from, int to, char c) {
		this->from = from;
		this->to = to;
		this->c = c;
	}
};

class MDFA {
	DFA dfa;
	vector<MDFANode> nodes;
	set<char> alphabets;
	std::set<std::set<int>> P, K;
	bool addnewset;
	pair<set<int>, set<int>> split(std::set<std::set<int>>::iterator s_it);
	void hopcroft();
	void addedge(int from, int to, char c);
	int findnode(int id);
	bool isaccept(const std::set<int> &S);
	void minimize();
	
public:
	MDFA(const string &reg);
	vector<MDFANode>& get_nodes();
};