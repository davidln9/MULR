//
//  SetGenerator.cpp
//  MULR
//	Open Source Software
//

#include "SetGenerator.h"

using namespace std;
SetGenerator::SetGenerator(vector<TerminalRule*> t) {
	this->functions = t;
}

void SetGenerator::generateFollow(TerminalRule *t) {
	
	cout<<"entered generateFollow: "<<t->name<<endl;
	node * temp = t->expression->starting;
	
	vector<followBranch*> branches;
	TerminalRule * f = NULL;
	
	node * stop = NULL;
	bool flag = false;
	
	while (1) {
		
		if (temp == stop) {
			temp = stop->neighbor1;
			stop = NULL;
		}
		if (temp->label1 != NULL && temp->label1->type == EPSILON) {
			if (temp->label2 != NULL && temp->label2->type == EPSILON) {
				followBranch * br = new followBranch;
				br->altRoute = temp->neighbor2;
				br->f = f;
				if (temp->loop) {
					br->stopAt = temp;
				} else {
					br->stopAt = NULL;
				}
				branches.push_back(br);
			}
			temp = temp->neighbor1;
		} else if (temp->label1 != NULL) {
			if (temp->label1->type == NON_TERMINAL) {
				if (f != NULL) {
					for (size_t i = 0; i < functions.size(); i++) {
						if (functions.at(i)->name == temp->label1->literal_text) {
							if (functions.at(i)->name != t->name) {
								flag = false;
								generateFollow(functions.at(i));
								set<string>:: iterator it;
								for (it = functions.at(i)->first.begin(); it != functions.at(i)->first.end(); ++it) {
									f->follow.insert(*it);
									set<TerminalRule*>:: iterator st;
									for (st = f->affected.begin(); st != f->affected.end(); ++st) {
										TerminalRule * th = *st;
										generateFollow(th);
										th->follow.insert(*it);
										cout<<"DEBUGS: "<<th->name<<endl;
									}
								}
							} else {
								cout<<"DEBUG: SET FLAG"<<endl;
								flag = true;
							}
							f = functions.at(i);
							temp = temp->neighbor1;
							break;
						}
					}
				} else {
					for (size_t i = 0; i < functions.size(); i++) {
						if (functions.at(i)->name == temp->label1->literal_text) {
							f = functions.at(i);
							if (f->name != t->name) {
								generateFollow(f);
							} else {
								cout<<"DEBUG_B: SET FLAG"<<endl;
								flag = true;
							}
							temp = temp->neighbor1;
							break;
						}
					}
				}
			} else if (temp->label1->type == TERMINAL) {
				if (f != NULL) {
					f->follow.insert(temp->label1->literal_text);
					set<TerminalRule*>:: iterator ag;
					for (ag = f->affected.begin(); ag != f->affected.end(); ++ag) {
						TerminalRule * m = *ag;
						m->follow.insert(temp->label1->literal_text);
					}
					if (!branches.empty()) {
						followBranch * b = branches.back();
						f = b->f;
						temp = b->altRoute;
						stop = b->stopAt;
						branches.pop_back();
						cout<<"DEBUG_C"<<endl;
					} else {
						f = NULL;
						temp = temp->neighbor1;
					}
				} else if (f != NULL && flag) {
					f->between.insert(temp->label1->literal_text);
					set<TerminalRule*>:: iterator ag;
					for (ag = f->affected.begin(); ag != f->affected.end(); ++ag) {
						TerminalRule * m = *ag;
						m->follow.insert(temp->label1->literal_text);
					}
					if (!branches.empty()) {
						followBranch * b = branches.back();
						f = b->f;
						temp = b->altRoute;
						stop = b->stopAt;
						branches.pop_back();
						cout<<"DEBUG_C"<<endl;
					} else {
						f = NULL;
						temp = temp->neighbor1;
					}
				} else {
					temp = temp->neighbor1;
				}
			}
		} else {
			flag = false;
			bool tocontinue = false;
			if (f != NULL && f->name != t->name) {
				cout<<"DEBUG: "<<f->name<<endl;
				t->affected.insert(f);
			}
			while (!branches.empty()) {
				followBranch * b = branches.back();
				branches.pop_back();
				f = b->f;
				temp = b->altRoute;
				tocontinue = true;
				stop = b->stopAt;
				cout<<"DEBUG_B"<<endl;
				break;
			}
			if (!tocontinue) {
				cout<<"exited generateFollow: "<<t->name<<endl;
				set<TerminalRule*>:: iterator st;
				for (st = t->affected.begin(); st != t->affected.end(); ++st) {
					TerminalRule * a = *st;
					set<string>:: iterator g;
					for (g = t->follow.begin(); g != t->follow.end(); ++g) {
						a->follow.insert(*g);
					}
				}
				return;
			}
		}
	}
}

void SetGenerator::generateFirsts(TerminalRule * t) {
	//implementation needed
	
	node * temp = t->expression->starting;
	bool addFirst = true;
	vector<firstBranch*> branches;
	while (1) {
		
		if (temp->label1 != NULL && temp->label1->type == EPSILON) {
			if (temp->label2 != NULL && temp->label2->type == EPSILON && !temp->loop) {
				firstBranch * fr = new firstBranch;
				fr->altRoute = temp->neighbor2;
				fr->addFirst = addFirst;
				branches.push_back(fr);
			}
			temp = temp->neighbor1;
		} else if (temp->label1 != NULL && temp->label1->type == TERMINAL) { //we found a member of the FIRST set
			if (addFirst) {
				t->first.insert(temp->label1->literal_text);
			}
			if (branches.empty()) {
				return;
			} else {
				firstBranch * fr = branches.back();
				temp = fr->altRoute;
				addFirst = fr->addFirst;
				branches.pop_back();
			}
		} else if (temp->label1 != NULL && temp->label1->type == NON_TERMINAL) {
			//we need FIRST set of the function
			bool block = false;
			for (size_t i = 0; i < functions.size(); i++) {
				if (functions.at(i)->name == temp->label1->literal_text && functions.at(i)->name != t->name) {
					generateFirsts(functions.at(i));
					if (addFirst) {
						set<string>:: iterator it;
						for (it = functions.at(i)->first.begin(); it != functions.at(i)->first.end(); ++it) {
							t->first.insert(*it);
						}
					}
				} else if (functions.at(i)->name == temp->label1->literal_text && functions.at(i)->name == t->name) {
					block = true;
				}
			}
			if (block) {
				if (branches.empty()) {
					return;
				} else {
					firstBranch * fr = branches.back();
					temp = fr->altRoute;
					addFirst = fr->addFirst;
					branches.pop_back();
				}
			} else {
				temp = temp->neighbor1;
				addFirst = false;
			}
		} else if (temp->label1 == NULL) { //we made it to the end of the function, add EPSILOM to first
			t->first.insert("EPSILON");
			if (branches.empty()) {
				return;
			} else {
				firstBranch * fr = branches.back();
				temp = fr->altRoute;
				addFirst = fr->addFirst;
				branches.pop_back();
			}
			
		}
	}
}
