#include "MemberList.h"
#include "sortlist.h"
#include "sortlisttemplate.h"


class MemberManager
{
private:
	MemberList currentMembers;
	MemberList pastMembers;
public:
	// Constructor
	MemberManager();

	// Main user-option methods
	void addMember();
	void displayLongstandingMembers();
	void revokeMembership();
	void displayCurrentMembers();
	void displayPastMembers();

	// Helper methods - checks
	bool dateIsInvalid(int day, int month, int year);	
	bool memberIsInCategory(int* joinDatePointer, int cutOffDate[3]);
	bool membershipIsUnique(int membershipNum);
	bool linearSearch(MemberList& members, int membershipNum, int& index);

	// Helper methods - info grabbers
	void getMemberDetails(string& firstName, string& lastName, int& membershipNum, int& day, int& month, int& year, bool& currentMember);
	void getDate(int& day, int& month, int& year);
	
	// Display methods
	void displayWelcome();
	void displayMenu();

	// For testing
	void addTestData();
};