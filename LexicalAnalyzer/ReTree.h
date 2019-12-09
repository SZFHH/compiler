#pragma once
#include<string>
#include<set>
//结点种类
enum Nodekind{
	ELEMENT, //字符
	CONCAT,  //连接
	ALT,     // 或
	CLOSURE, //闭包
	ZORONE   //？
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

	std::string reg; //正则表达式
	ReTreeNode* root;
	int pos;
	char currentChar;
	char getnextChar();
	void update(); //预处理正则表达式的语法糖
	/*利用递归处理正则表达式，建立正则树*/
	ReTreeNode* parse(); //处理|
	ReTreeNode* parse_A(); //处理与
	ReTreeNode* parse_B(); //处理*或者？
	ReTreeNode* parse_C(); //处理元素
	void RE2tree();
public:
	std::set<char> alphabets; //正则表达式中出现的字符
	ReTree(const std::string &s);
	ReTree();
	ReTreeNode* getroot();
};