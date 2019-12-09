#pragma once
#include<map>
#include"MDFA.h"
/*�ʷ�����������*/
enum codekind{IDENT, NUM, OPRT, STRING, CHAR, RESERVE};
const std::string kindexp[6] = { "IDENT", "NUM", "OPRT", "STRING","CHAR", "RESERVE" };

const int ERROR = -1; //����״̬

/*ÿ���ʵ��ַ���������*/
struct code2kind { 
	std::string code;
	codekind kind;
};

class LexicalAnalyzer {
	std::map<enum codekind, MDFA> MDFAs; //�ʷ����Ͷ�Ӧ��MDFA
	std::map<std::string, int> reserved_words; //�����ֶ�Ӧ��ţ���257��ʼ��
	std::map<std::string, int> opes; //��������Ӧ���
	std::map<int, std::string> id2reserved_sig; //��Ŷ�Ӧ�����ֵĴ�д���
	std::map<int, std::string> id2opes_sig; //��Ŷ�Ӧ��������Ӣ�ı��
	std::vector<std::vector<code2kind>> outputs; //���������ļ���ʾΪcode2kind���ͣ����д洢��ÿ�зִʴ洢
	std::string test_str; //һ�д���
	int pos; //��ǰ�д����е��±�
	int line; //��ǰ�д��������
	char currentChar;
	char getnextChar();
	int nextstate(MDFANode &mdfanode, int c); //�ӵ�ǰstatus�������ַ�c�ıߵ������һ��status
	std::vector<code2kind> match(const std::string &text); //��һ�д�����дʷ�����
	bool match_single_mdfa(MDFA &mdfa, code2kind &cdkd); //��mdfa��Ѱ����һ��token��Ѱ�ұ�ʶ�������֣�
	bool match_string(code2kind &cdkd); //Ѱ���ַ���
	bool match_char(code2kind &cdkd); //Ѱ���ַ�
	bool match_ope(code2kind &cdkd); //Ѱ�Ҳ�����
	void print(std::string out_filename); //�ѽ�����ʷ��������
	void rollback(); //����һ���ַ�
	void RaiseExption(std::string errinfo); //�쳣����
	void reset(); //pos��0
	void NextUnspace(); //��pos�ƶ����¸���Ϊ���ַ��ĵط���' ','\t'��
	void print_(std::ostream &o);
public:
	LexicalAnalyzer();
	void parse(std::vector<std::string> &lines, std::string out_filename = ""); //�ʷ�����
	//��ʼ��LA
	void build(const std::map<std::string, std::string> &regs, 
		const std::map<std::string, std::string> opes,
		const std::map<std::string, std::string> reserved_words);
	
};