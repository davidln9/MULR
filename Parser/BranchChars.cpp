//
//  BranchChars.cpp
//  MULR
//	Open Source Software
//

#include "BranchChars.hpp"

static BranchChars * m_pInstance;

BranchChars * BranchChars::getInstance() {
	if (m_pInstance == NULL) {
		m_pInstance = new BranchChars();
	}
	return m_pInstance;
}

BranchChars::BranchChars() {
	
}


void BranchChars::insertChars(std::vector<char> c) {
	while (!c.empty()) {
		m_pInstance->chars.push_back(c.back());
		c.pop_back();
	}
}

std::vector<char> BranchChars::getChars() {
	std::vector<char> copy;
	while (!m_pInstance->chars.empty()) {
		copy.push_back(chars.back());
		m_pInstance->chars.pop_back();
	}
	
	return copy;
}
