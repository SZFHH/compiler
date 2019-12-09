#pragma once
#include<string>
#include<set>
//�������
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

	std::string reg; //������ʽ
	ReTreeNode* root;
	int pos;
	char currentChar;
	char getnextChar();
	void update(); //Ԥ����������ʽ���﷨��
	/*���õݹ鴦��������ʽ������������*/
	ReTreeNode* parse(); //����|
	ReTreeNode* parse_A(); //������
	ReTreeNode* parse_B(); //����*���ߣ�
	ReTreeNode* parse_C(); //����Ԫ��
	void RE2tree();
public:
	std::set<char> alphabets; //������ʽ�г��ֵ��ַ�
	ReTree(const std::string &s);
	ReTree();
	ReTreeNode* getroot();
};