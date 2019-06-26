//
//  BranchChars.hpp
//  MULR
//	Open Source Software
//

#ifndef BranchChars_hpp
#define BranchChars_hpp

#include <stdio.h>
#include <vector>

class BranchChars{
public:
	static BranchChars * getInstance();
	void insertChars(std::vector<char>);
	std::vector<char> getChars();
	
private:
	BranchChars();
	BranchChars(BranchChars const&){};
	std::vector<char> chars;
};

#endif /* BranchChars_hpp */
