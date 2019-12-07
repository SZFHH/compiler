#pragma once
#include<set>
#include<map>
#include<vector>
#include"NFA.h"
struct DFANode {
	std::set<int> vertex;
	bool accept;
	int num;
	DFANode(std::set<int> vertex, bool accept, int num) {
		this->vertex = vertex;
		this->accept = accept;
		this->num = num;
	}
	std::vector<DFAedge> edges;
};

struct DFAedge {
	int from, to;
	char c;
	DFAedge(int from, int to, char c) {
		this->from = from;
		this->to = to;
		this->c = c;
	}
};

class DFA {
	NFA nfa;
	std::vector<DFANode> allnodes;
	std::multimap<char, DFAedge*> alledges;
	std::set<int> delta(const std::set<int> &st, char c);
	std::set<int> closure(const std::set<int> &st);
	set<char> alphabets;
	bool addnewnode;
	int InsertOrFind(const std::set<int> &st);
	void addedge(const std::set<int> &from, const std::set<int> &to, char c);
	void SubsetConstruct();
	void NFA_to_DFA();
public:
	DFA(const string &reg);
	std::vector<DFANode> &getallnodes();
	multimap<char, DFAedge *> &getalledges();

};