#pragma once
#include"DFA.h"
struct MDFAedge;
struct MDFANode{
	bool accept;
	int num;
	std::set<int> vertex; //DFA中的结点编号集合
	std::vector<MDFAedge> edges; //邻接的边
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
	std::vector<MDFANode> nodes;
	std::set<char> alphabets;
	std::set<std::set<int>> P, K; //hopcroft算法中，保存split前后的结果。
	bool addnewset; //记录在split过程中是否添加了新的集合
	std::pair<std::set<int>, std::set<int>> split(std::set<std::set<int>>::iterator s_it); //分离集合
	void hopcroft();
	void addedge(int from, int to, char c);  //根据DFA的连接关系，连接MDFA的结点。from和to为DFA的结点id
	int findnode(int id); //寻找DFA的结点id对应的MDFA中的结点id
	bool isaccept(const std::set<int> &S);
	void minimize(); //最小化算法
	int start; //MDFA中的开始结点
	
public:
	MDFA(const std::string &reg);
	MDFA();
	std::vector<MDFANode>& get_nodes();
	int getstart();
};