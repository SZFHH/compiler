#pragma once
#include<set>
#include<map>
#include<vector>
#include"NFA.h"
struct DFAedge;
struct DFANode {
	std::set<int> vertex; //NFA结点的集合
	bool accept;  //是否是接受结点
	int num;
	DFANode(std::set<int> vertex, bool accept, int num) {
		this->vertex = vertex;
		this->accept = accept;
		this->num = num;
	}
	std::vector<DFAedge> edges; //邻接的边
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
	std::vector<DFANode> allnodes; //DFA所有的点（DFA图）
	std::multimap<char, DFAedge*> alledges;
	std::set<int> delta(const std::set<int> &st, char c); //从集合st中通过c可以转移的集合
	std::set<int> closure(const std::set<int> &st); //集合st的eps闭集
	bool addnewnode; //在InsertOrFind中是否新添加了结点
	int InsertOrFind(const std::set<int> &st); //加入或者找到结点st
	void addedge(const std::set<int> &from, const std::set<int> &to, char c);
	void SubsetConstruct(); //子集构造算法
	void NFA_to_DFA();
public:
	DFA(const std::string &reg);
	DFA();
	std::set<char> alphabets;
	std::vector<DFANode> &getallnodes();
	std::multimap<char, DFAedge *> &getalledges();

};