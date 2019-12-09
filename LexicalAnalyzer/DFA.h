#pragma once
#include<set>
#include<map>
#include<vector>
#include"NFA.h"
struct DFAedge;
struct DFANode {
	std::set<int> vertex; //NFA���ļ���
	bool accept;  //�Ƿ��ǽ��ܽ��
	int num;
	DFANode(std::set<int> vertex, bool accept, int num) {
		this->vertex = vertex;
		this->accept = accept;
		this->num = num;
	}
	std::vector<DFAedge> edges; //�ڽӵı�
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
	std::vector<DFANode> allnodes; //DFA���еĵ㣨DFAͼ��
	std::multimap<char, DFAedge*> alledges;
	std::set<int> delta(const std::set<int> &st, char c); //�Ӽ���st��ͨ��c����ת�Ƶļ���
	std::set<int> closure(const std::set<int> &st); //����st��eps�ռ�
	bool addnewnode; //��InsertOrFind���Ƿ�������˽��
	int InsertOrFind(const std::set<int> &st); //��������ҵ����st
	void addedge(const std::set<int> &from, const std::set<int> &to, char c);
	void SubsetConstruct(); //�Ӽ������㷨
	void NFA_to_DFA();
public:
	DFA(const std::string &reg);
	DFA();
	std::set<char> alphabets;
	std::vector<DFANode> &getallnodes();
	std::multimap<char, DFAedge *> &getalledges();

};