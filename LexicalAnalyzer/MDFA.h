#pragma once
#include"DFA.h"
struct MDFAedge;
struct MDFANode{
	bool accept;
	int num;
	std::set<int> vertex; //DFA�еĽ���ż���
	std::vector<MDFAedge> edges; //�ڽӵı�
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
	std::set<std::set<int>> P, K; //hopcroft�㷨�У�����splitǰ��Ľ����
	bool addnewset; //��¼��split�������Ƿ�������µļ���
	std::pair<std::set<int>, std::set<int>> split(std::set<std::set<int>>::iterator s_it); //���뼯��
	void hopcroft();
	void addedge(int from, int to, char c);  //����DFA�����ӹ�ϵ������MDFA�Ľ�㡣from��toΪDFA�Ľ��id
	int findnode(int id); //Ѱ��DFA�Ľ��id��Ӧ��MDFA�еĽ��id
	bool isaccept(const std::set<int> &S);
	void minimize(); //��С���㷨
	int start; //MDFA�еĿ�ʼ���
	
public:
	MDFA(const std::string &reg);
	MDFA();
	std::vector<MDFANode>& get_nodes();
	int getstart();
};