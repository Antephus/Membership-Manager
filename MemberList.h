#ifndef MEMBERLIST_H
#define MEMBERLIST_H
#include "Member.h"
#include <iostream>
using namespace std;

const int MAXMEMBERS = 10000;

class MemberList
{
private:
	Member *members;
	int numOfMembers;
	string typeOfMembers;

	// Private functions required for quicksort
	void swap(Member& member1, Member& member2);
	void split(const int first, const int last, int& position);
	void quickSort(const int first, const int last);
public:
	//Constructors and desctructors
	MemberList();
	MemberList(string membersType);
	~MemberList();

	// List/quicksort functions
	bool isEmpty();
	bool add(const Member& member);
	bool remove(int index);
	void quickSort();

	// Getters, settters and display
	int getNumOfMembers();
	void setNumOfMembers(int members);
	string getTypeOfMembers();
	void setTypeOfMembers(string membersType);
	Member getMember(int index);
	void setMember(int index, const Member& newMember);
	void displayList();
};
#endif