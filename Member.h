#include <iostream>
#include <string>
using namespace std;

class Member
{
private:
	string firstName;
	string lastName;
	int membershipNumber;
	int joinDate[3];
	bool currentMember;
public:
	// Constructors
	Member();
	Member(string newFName, string newLName, int newMemNum, int day, int month, int year, bool newMembership);

	// Overloaded operators
	bool operator>(Member& member);
	bool operator<=(Member& member);

	// Getters, setters and display
	string getFirstName();
	void setFirstName(string newFirstName);
	string getLastName();
	void setLastName(string newLastName);
	int getMembershipNumber();
	void setMembershipNumber(int newNumber);
	bool isMember();
	void setMembership(bool newMembership);
	int* getJoinDate();
	void setJoinDate(int day, int month, int year);
	void displayDetails();
};