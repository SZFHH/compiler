#pragma once
#include<string>
using namespace std;
enum Nodekind{
	ELEMENT, //�ַ�
	CONCAT,  //����
	ALT,     // ��
	CLOSURE, //�հ�
	ZORONE   //��
}; 
const int EPS = -2;
struct ReTreeNode {
	Nodekind kind;
	char c;
	ReTreeNode* childs[2];
	ReTreeNode(Nodekind kind, char c, ReTreeNode* lch, ReTreeNode* rch) {
		this->kind = kind;
		this->c = c;
		childs[0] = lch, childs[1] = rch;
	}
};

class ReTree {

	string reg;
	ReTreeNode* root;
	int pos;
	char curc;
	char getnext();
	ReTreeNode* parse(); //����|
	ReTreeNode* parse_A(); //������
	ReTreeNode* parse_B(); //����*���ߣ�
	ReTreeNode* parse_C(); //����Ԫ��
	bool iselement();

public:
	ReTree(const string &s);
	ReTreeNode* getroot();
};