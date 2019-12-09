#pragma once
#include<map>
#include"MDFA.h"
/*词法分析的类型*/
enum codekind{IDENT, NUM, OPRT, STRING, CHAR, RESERVE};
const std::string kindexp[6] = { "IDENT", "NUM", "OPRT", "STRING","CHAR", "RESERVE" };

const int ERROR = -1; //错误状态

/*每个词的字符串和类型*/
struct code2kind { 
	std::string code;
	codekind kind;
};

class LexicalAnalyzer {
	std::map<enum codekind, MDFA> MDFAs; //词法类型对应的MDFA
	std::map<std::string, int> reserved_words; //保留字对应编号（从257开始）
	std::map<std::string, int> opes; //操作符对应编号
	std::map<int, std::string> id2reserved_sig; //编号对应保留字的大写表达
	std::map<int, std::string> id2opes_sig; //编号对应操作符的英文表达
	std::vector<std::vector<code2kind>> outputs; //整个代码文件表示为code2kind类型，分行存储，每行分词存储
	std::string test_str; //一行代码
	int pos; //当前行代码中的下标
	int line; //当前行代码的行数
	char currentChar;
	char getnextChar();
	int nextstate(MDFANode &mdfanode, int c); //从当前status，经过字符c的边到达的下一个status
	std::vector<code2kind> match(const std::string &text); //对一行代码进行词法分析
	bool match_single_mdfa(MDFA &mdfa, code2kind &cdkd); //从mdfa中寻找下一个token（寻找标识符和数字）
	bool match_string(code2kind &cdkd); //寻找字符串
	bool match_char(code2kind &cdkd); //寻找字符
	bool match_ope(code2kind &cdkd); //寻找操作符
	void print(std::string out_filename); //把结果按词法类型输出
	void rollback(); //回退一个字符
	void RaiseExption(std::string errinfo); //异常处理
	void reset(); //pos置0
	void NextUnspace(); //把pos移动到下个不为空字符的地方（' ','\t'）
	void print_(std::ostream &o);
public:
	LexicalAnalyzer();
	void parse(std::vector<std::string> &lines, std::string out_filename = ""); //词法分析
	//初始化LA
	void build(const std::map<std::string, std::string> &regs, 
		const std::map<std::string, std::string> opes,
		const std::map<std::string, std::string> reserved_words);
	
};