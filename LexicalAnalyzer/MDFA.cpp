#include "MDFA.h"

pair<set<int>, set<int>> MDFA::split(std::set<std::set<int>>::iterator s_it)
{
	set<int> rv;
	set<int> rv2 = *s_it;
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
		if (!rv.empty() && rv.size() != s_it->size()) {
			addnewset = true;
			for (auto &d : rv) rv2.erase(d);
			break;
		}
		else rv.clear();
	}
	return make_pair(rv, rv2);
}

void MDFA::hopcroft()
{
	set<int> ac, notac;
	pair<set<int>, set<int>> temp;
	auto &alldfanodes = dfa.getallnodes();
	for (auto &node : alldfanodes) {
		if (node.accept) ac.insert(node.num);
		else notac.insert(node.num);
	}
	K.insert(ac);
	K.insert(notac);

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
	for (auto &vset : K) {
		nodes.push_back(MDFANode(isaccept(vset), i, vset));
		++i;
	}
	auto &alledges = dfa.getalledges();
	for (char c : alphabets) {
		auto pairit = alledges.equal_range(c);
		auto startit = pairit.first;
		auto endit = pairit.second;
		for (auto it = startit; it != endit; ++it) {
			addedge(it->second->from, it->second->to, c);
		}
	}

}

MDFA::MDFA(const string & reg):dfa(reg)
{
	addnewset = false;
	minimize();
}

vector<MDFANode>& MDFA::get_nodes()
{
	return nodes;
}
