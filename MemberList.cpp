#include "MemberList.h"

// Constructors and destructors
MemberList::MemberList() : members(new Member[MAXMEMBERS]),
numOfMembers(0),
typeOfMembers("Unknown")
{}

MemberList::MemberList(string membersType) : members(new Member[MAXMEMBERS]),
numOfMembers(0),
typeOfMembers(membersType)
{}

MemberList::~MemberList()
{
	delete[] members;
}


// List functions
bool MemberList::isEmpty()
{
	return (numOfMembers == 0) ? true : false;
}


bool MemberList::add(const Member& newMember)
{
	if (numOfMembers < MAXMEMBERS)
	{
		members[numOfMembers] = newMember;
		numOfMembers++;
		return true;
	}
	else
	{
		cout << endl << "Sorry, it seems this list is full!" << endl;
		return false;
	}
}


bool MemberList::remove(int index)
{
	// As long as the index is valid, move the last member on the list to the member-to-be-removed's space, set their old 
	// space to empty/default member, and update the number of members
	if (index >= 0 && index < numOfMembers)
	{
		members[index] = members[numOfMembers - 1];
		members[numOfMembers - 1] = Member();
		numOfMembers--;
		return true;
	}
	else
		return false;
}


// Quicksort functions
// The method called to set off the quicksort process
void MemberList::quickSort()
{
	quickSort(0, numOfMembers - 1);
}


// Sorts a list between the two given indexes
void MemberList::quickSort(const int first, const int last)
{
	int position; // Of the pivot

				  // As long as there's at least two elements left, split the list and sort each sublist
	if (first < last)
	{
		split(first, last, position);
		quickSort(first, position - 1);
		quickSort(position + 1, last);
	}
}


void MemberList::swap(Member& member1, Member& member2)
{
	Member placeholder = member1;
	member1 = member2;
	member2 = placeholder;
}


void MemberList::split(const int first, const int last, int& position)
{
	int left, right;
	Member pivot;

	pivot = members[first];
	left = first;
	right = last;
	
	// Until the markers meet
	while (left < right)
	{
		// Find a member that should come before (or is the same as) the pivot (moving right)
		while (members[right] > pivot)
			right = right - 1;

		// Find a member that should come after the pivot (moving left)
		while ((left < right) && (members[left] <= pivot))
			left = left + 1;

		// If it's not the same member, swap the two members
		if (left < right)
			swap(members[left], members[right]);
	};

	// Move the pivot to where it should be
	position = right;
	members[first] = members[position];
	members[position] = pivot;
}


// Getters, setters and display
int MemberList::getNumOfMembers()
{
	return numOfMembers;
}

void MemberList::setNumOfMembers(int members)
{
	numOfMembers = members;
}

string MemberList::getTypeOfMembers()
{
	return typeOfMembers;
}

void MemberList::setTypeOfMembers(string membersType)
{
	typeOfMembers = membersType;
}

Member MemberList::getMember(int index)
{
	return members[index];
}

void MemberList::setMember(int index, const Member& newMember)
{
	members[index] = newMember;
}

void MemberList::displayList()
{
	cout << endl << typeOfMembers << endl;
	cout << endl << "Mem No.\t\tDate Joined\t\tName";
	for (int counter = 0; counter < numOfMembers; counter++)
		members[counter].displayDetails();
	cout << endl << endl;
}