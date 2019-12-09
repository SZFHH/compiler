#pragma once
#include<vector>
#include"ReTree.h"
#include<map>
#include<string>
struct NFAedge;
struct NFANode {
	bool visit; //是否访问标记
	int num;    //结点编号
	NFANode(int num) {
		this->visit = false;
		this->num = num;
	}
	std::vector<NFAedge> edges;  //邻接的边
};

struct NFAedge {
	int from, to;
	char c;
	NFAedge(int from, int to, char c) {
		this->from = from;
		this->to = to;
		this->c = c;
	}
};

class NFA {
	
	ReTree regtree; //正则树
	std::vector<NFANode> allnodes;
	std::multimap<char, NFAedge *> alledges;
	int accept, start; //开始和接受结点
	int NewNode();
	void AddEdge(int from, int to, char c);
	void Thompson(ReTreeNode * retree);
public:
	NFA(const std::string &reg);
	NFA();
	std::vector<NFANode> &getallnodes();
	std::multimap<char, NFAedge *> &getalledges();
	void resetvisit(); //重置所有结点的visit为false
	void RE_to_NFA();
	int getStart();
	int getAccept();
	std::set<char> getalphabets(); //从regtree中取出alphabets
};