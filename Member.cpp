#include "Member.h"

//Constructors
Member::Member() : firstName("Unknown"),
lastName("Unknown"),
membershipNumber(-1),
currentMember(false)
{
	joinDate[0] = 0;
	joinDate[1] = 0;
	joinDate[2] = 0;
}

Member::Member(string newFName, string newLName, int newMemNum, int day, int month, int year, bool newMembership) : firstName(newFName),
lastName(newLName),
membershipNumber(newMemNum),
currentMember(newMembership)
{
	joinDate[0] = day;
	joinDate[1] = month;
	joinDate[2] = year;
}


// Overloaded operators for member comparison when sorting
bool Member::operator>(Member& member)
{
	// Compare each date component in order of sort precedence, and return true if one is found > the other;
	// true should only be returned for each subsequent check if all other prior components were equal though
	if (joinDate[2] > member.joinDate[2])
		return true;
	else if ((joinDate[2] == member.joinDate[2]) && (joinDate[1] > member.joinDate[1]))
		return true;
	else if ((joinDate[2] == member.joinDate[2]) && (joinDate[1] == member.joinDate[1]) && (joinDate[0] > member.joinDate[0]))
		return true;

	// If the dates were the same, compare the last name; if that's the same too, compare the first name
	else if ((joinDate[0] == member.joinDate[0]) && (joinDate[1] == member.joinDate[1]) && (joinDate[2] == member.joinDate[2]))
	{
		if (lastName > member.lastName)
			return true;
		else if (lastName == member.lastName && firstName > member.firstName)
			return true;
	} 
	
	// If nothing was found to be >, just return false
	return false;
}


/* Compare each date component in order of sort precedence, and return true if one is found < the other;
true should only be returned for each subsequent check if all other prior components were equal.
Checking for equality must be left for later (so checks are < and not <=), otherwise comparisons returning equal
for components early in the checks e.g. 1990 == 1990 will return true wrongly in cases where the overall comparison result
should be > based on later components e.g. (1990/6/30 <= 1990/6/15) would falsely return true prematurely */
bool Member::operator<=(Member& member)
{
	if (joinDate[2] < member.joinDate[2])
		return true;
	else if ((joinDate[2] == member.joinDate[2]) && joinDate[1] < member.joinDate[1])
		return true;
	else if ((joinDate[2] == member.joinDate[2]) && (joinDate[1] == member.joinDate[1]) && joinDate[0] < member.joinDate[0])
		return true;

	// If the dates were the same, compare the last name; if that's the same too, compare the first name
	else if ((joinDate[0] == member.joinDate[0]) && (joinDate[1] == member.joinDate[1]) && (joinDate[2] == member.joinDate[2]))
	{
		if (lastName < member.lastName)
			return true;
		else if (lastName == member.lastName && firstName < member.firstName)
			return true;
		// If everything was equal, also return true
		else if ((lastName == member.lastName) && (firstName == member.firstName))
			return true;
	}

	// If nothing was found to be <=, just return false
	return false;
}


// Getters, setters and display
string Member::getFirstName()
{
	return firstName;
}

void Member::setFirstName(string newFirstName)
{
	firstName = newFirstName;
}

string Member::getLastName()
{
	return lastName;
}

void Member::setLastName(string newLastName)
{
	lastName = newLastName;
}

int Member::getMembershipNumber()
{
	return membershipNumber;
}

void Member::setMembershipNumber(int newNumber)
{
	membershipNumber = newNumber;
}

bool Member::isMember()
{
	return currentMember;
}

void Member::setMembership(bool newMembership)
{
	currentMember = newMembership;
}

int* Member::getJoinDate()
{
	return joinDate;
}

void Member::setJoinDate(int day, int month, int year)
{
	joinDate[0] = day;
	joinDate[1] = month;
	joinDate[2] = year;
}

void Member::displayDetails()
{
	cout << endl << membershipNumber << "\t\t" << joinDate[0] << "/" << joinDate[1] << "/" << joinDate[2] << "\t\t" << lastName << ", " << firstName;
}