#pragma once
#include"LexicalAnalyzer.h"
class Preprocess {
	std::string regs_filename; //词法规则文件名
	std::string code_filename; //待编译代码文件名
	std::map<std::string, std::string> regs; //<类别名，正在表达式>
	std::map<std::string, std::string> opes; //<操作符英文，操作符>
	std::map<std::string, std::string> reserved_words; //<保留字大写表示，保留字>
	std::vector<std::string> lines; //代码文件的所有行
	void trim(std::string & s); //去注释预处理
	bool is_block_comment; //标记是否是块注释
public:
	Preprocess();
	void read_codefile(std::string filename); //读入待编译代码文件
	void read_regsfile(std::string filename); //读入词法规则文件
	void buildLA(LexicalAnalyzer &LA); //建立LA
	std::vector<std::string> &get_code_file(); //返回代码文件的所有行
};