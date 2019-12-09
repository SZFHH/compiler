#pragma once
#include"LexicalAnalyzer.h"
class Preprocess {
	std::string regs_filename; //�ʷ������ļ���
	std::string code_filename; //����������ļ���
	std::map<std::string, std::string> regs; //<����������ڱ��ʽ>
	std::map<std::string, std::string> opes; //<������Ӣ�ģ�������>
	std::map<std::string, std::string> reserved_words; //<�����ִ�д��ʾ��������>
	std::vector<std::string> lines; //�����ļ���������
	void trim(std::string & s); //ȥע��Ԥ����
	bool is_block_comment; //����Ƿ��ǿ�ע��
public:
	Preprocess();
	void read_codefile(std::string filename); //�������������ļ�
	void read_regsfile(std::string filename); //����ʷ������ļ�
	void buildLA(LexicalAnalyzer &LA); //����LA
	std::vector<std::string> &get_code_file(); //���ش����ļ���������
};