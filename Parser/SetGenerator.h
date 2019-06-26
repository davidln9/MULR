//
//  SetGenerator.h
//  MULR
//	Open Source Software
//

#ifndef SetGenerator_h
#define SetGenerator_h

#include <stdio.h>
#include "DFA.h"
#include <vector>
#include <iostream>

class SetGenerator {
public:
	SetGenerator(std::vector<TerminalRule*> t);
	void generateFirsts(TerminalRule * t);
	void generateFollow(TerminalRule * t);
private:
	std::vector<TerminalRule*> functions;
};

#endif /* SetGenerator_h */
