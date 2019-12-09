#pragma once
#include<vector>
#include"ReTree.h"
#include<map>
#include<string>
struct NFAedge;
struct NFANode {
	bool visit; //�Ƿ���ʱ��
	int num;    //�����
	NFANode(int num) {
		this->visit = false;
		this->num = num;
	}
	std::vector<NFAedge> edges;  //�ڽӵı�
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
	
	ReTree regtree; //������
	std::vector<NFANode> allnodes;
	std::multimap<char, NFAedge *> alledges;
	int accept, start; //��ʼ�ͽ��ܽ��
	int NewNode();
	void AddEdge(int from, int to, char c);
	void Thompson(ReTreeNode * retree);
public:
	NFA(const std::string &reg);
	NFA();
	std::vector<NFANode> &getallnodes();
	std::multimap<char, NFAedge *> &getalledges();
	void resetvisit(); //�������н���visitΪfalse
	void RE_to_NFA();
	int getStart();
	int getAccept();
	std::set<char> getalphabets(); //��regtree��ȡ��alphabets
};