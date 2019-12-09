#include "MDFA.h"

std::pair<std::set<int>, std::set<int>> MDFA::split(std::set<std::set<int>>::iterator s_it)
{
	std::set<int> rv;
	std::set<int> rv2 = *s_it;
	std::set<std::set<int>>::iterator last = P.end();
	auto &alledges = dfa.getalledges();
	for (char c : alphabets) {
		auto pairit = alledges.equal_range(c);
		auto startit = pairit.first;
		auto endit = pairit.second;
		for (auto it = startit; it != endit; ++it) {
			if (s_it->find(it->second->from) == s_it->end()) continue;
			if (s_it->find(it->second->to) != s_it->end()) continue;
			for (auto k_it = P.begin(); k_it != P.end(); ++k_it) {
				if (k_it == s_it) continue;
				if (k_it->find(it->second->to) != k_it->end()) {
					if (last == P.end()) last = k_it;
					if (k_it == last) {
						rv.insert(it->second->from);
					}
				}
			}
		}
		//通过以c为字符的边，一个集合中的所有点指向自身，或者指向同一个另外的集合，就不用分割。
		if (!rv.empty() && rv.size() != s_it->size()) {
			addnewset = true;
			for (auto &d : rv) rv2.erase(d);
			break;
		}
		else rv.clear();
	}
	return std::make_pair(rv, rv2);
}

void MDFA::hopcroft()
{
	std::set<int> ac, notac;
	std::pair<std::set<int>, std::set<int>> temp;
	auto &alldfanodes = dfa.getallnodes();
	for (auto &node : alldfanodes) {
		if (node.accept) ac.insert(node.num);
		else notac.insert(node.num);
	}
	K.insert(ac);
	K.insert(notac);
	//最初把所有点按接受和不接受分成两个集合，K为输出集合，P为临时集合
	do{
		P = K;
		K.clear();
		addnewset = false;
		for (auto it = P.begin(); it != P.end();++it) {
			temp = split(it);
			if (!temp.first.empty()) K.insert(temp.first);
			if (!temp.second.empty())K.insert(temp.second);
		}
	} while (addnewset); 

}

void MDFA::addedge(int from, int to, char c)
{
	from = findnode(from);
	to = findnode(to);
	for (auto &edge : nodes[from].edges) {
		if (edge.c == c) return;
	}
	nodes[from].edges.push_back(MDFAedge(from, to, c));
}

int MDFA::findnode(int id)
{
	for (int i = 0; i < nodes.size(); ++i) {
		if (nodes[i].vertex.find(id) != nodes[i].vertex.end()) return i;
	}
	return 0;
}

bool MDFA::isaccept(const std::set<int>& S)
{
	auto &alldfanodes = dfa.getallnodes();
	for (auto &id : S) {
		if (alldfanodes[id].accept) return true;
	}
	return false;
}

void MDFA::minimize()
{
	hopcroft();
	int i = 0;
	//按分好的集合建点
	for (auto &vset : K) {
		nodes.push_back(MDFANode(isaccept(vset), i, vset));
		++i;
	}
	//按DFA的连接关系连接MDFA的点
	auto &alledges = dfa.getalledges();
	for (auto &edge:alledges) {
		addedge(edge.second->from, edge.second->to, edge.first);
	}
	//找到MDFA中的起始结点
	for (int i = 0; i < nodes.size(); ++i) {
		if (nodes[i].vertex.find(0) != nodes[i].vertex.end()) {
			start = i;
			break;
		}
	}

}

MDFA::MDFA(const std::string & reg):dfa(reg)
{
	addnewset = false;
	alphabets = dfa.alphabets;
	minimize();
}

MDFA::MDFA()
{
}

std::vector<MDFANode>& MDFA::get_nodes()
{
	return nodes;
}

int MDFA::getstart()
{
	return start;
}
