#include "MemberManager.h"


// Constructor
MemberManager::MemberManager() : currentMembers(MemberList("All Current Members")),
pastMembers(MemberList("All Past Members"))
{}


// Main user-options methods
void MemberManager::addMember()
{
	Member memberToAdd;
	string firstName, lastName;
	int day, month, year; 
	int membershipNum;
	bool currentMember;
	
	// Get all necessary member details	
	getMemberDetails(firstName, lastName, membershipNum, day, month, year, currentMember);
	memberToAdd = Member(firstName, lastName, membershipNum, day, month, year, currentMember);
	
	// Add the member to the appropriate list	
	if (currentMember == true && currentMembers.add(memberToAdd))
		cout << endl << "The member was successfully added to the list of current members." << endl;
	else if (currentMember == false && pastMembers.add(memberToAdd))
		cout << endl << "The member was successfully added to the list of past members." << endl;
	else
		cout << endl << "Sorry, the member could not be added to a list." << endl;	
}


void MemberManager::displayLongstandingMembers()
{
	Member currentMember;
	int* joinDatePointer;
	int currentDate[3];
	int cutOffDate[3];	
	int listPosition = 0;

	// Make sure the list isn't empty first
	if (currentMembers.isEmpty())
	{
		cout << "Sorry, there are no current members on the list at all!" << endl;
	}
	// If it's not, sort the list and make sure there's at least one long-standing member to display
	else
	{
		currentMembers.quickSort();
		currentMember = currentMembers.getMember(listPosition);

		// Get the current date, join date, and cut-off date (set cut-off to be 10 years ago to catch any long-standing member)
		cout << endl << "Please enter the current date as individual integers:" << endl;
		getDate(currentDate[0], currentDate[1], currentDate[2]);
		joinDatePointer = currentMember.getJoinDate();
		cutOffDate[0] = currentDate[0];
		cutOffDate[1] = currentDate[1];
		cutOffDate[2] = currentDate[2] - 10;


		// If there's a long-standing member, print the list header and reset the cut off date to 
		// check for 50+ years long-standing members (longest-standing members are at the top of the list)
		if (memberIsInCategory(joinDatePointer, cutOffDate))
		{
			cout << endl << "Long-standing members on " << currentDate[0] << "/" << currentDate[1] << "/" << currentDate[2] << ":" << endl;
			cutOffDate[2] = currentDate[2] - 50;
		}

		// For every category (starting at 5 = 50+ years)
		for (int category = 5; category >= 1; category--)
		{
			// If there's at least one member in this category, print the appropriate category heading
			if (memberIsInCategory(joinDatePointer, cutOffDate))
			{
				switch (category)
				{
				case 5:
					cout << endl << "50 years+" << endl;
					cout << endl << "Mem No.\t\tDate Joined\t\tName" << endl;
					break;
				case 4:
					cout << endl << endl << endl << "40 years+" << endl;
					cout << endl << "Mem No.\t\tDate Joined\t\tName" << endl;
					break;
				case 3:
					cout << endl << endl << endl << "30 years+" << endl;
					cout << endl << "Mem No.\t\tDate Joined\t\tName" << endl;
					break;
				case 2:
					cout << endl << endl << endl << "20 years+" << endl;
					cout << endl << "Mem No.\t\tDate Joined\t\tName" << endl;
					break;
				case 1:
					cout << endl << endl << endl << "10 years+" << endl;
					cout << endl << "Mem No.\t\tDate Joined\t\tName" << endl;
					break;
				}
			}

			// Until the end of the list or the end of the category, display the current member and get the next one
			while (listPosition < currentMembers.getNumOfMembers() && memberIsInCategory(joinDatePointer, cutOffDate))
			{
				currentMember.displayDetails();
				listPosition++;
				currentMember = currentMembers.getMember(listPosition);
				joinDatePointer = currentMember.getJoinDate();
			}

			// If we already reached the end of the list, don't bother with the rest of any categories still to go
			if (listPosition >= currentMembers.getNumOfMembers())
				category = 0;
			// Otherwise, adjust the cut off date for the next category
			else
				cutOffDate[2] = cutOffDate[2] + 10;
		} //End for
	} // End else
}


void MemberManager::revokeMembership()
{
	// Get the member to be removed details
	Member exMember;
	int membershipNum, location = 0;

	cout << endl << "Please enter the membership number of the member leaving the society: ";
	cin >> membershipNum;

	// Make sure the list is sorted, then if the member is in the list, take them out of the current members list, 
	// update their membership status, and add them to the past members list
	currentMembers.quickSort();
	if (linearSearch(currentMembers, membershipNum, location))
	{
		exMember = currentMembers.getMember(location);
		currentMembers.remove(location);
		exMember.setMembership(false);
		pastMembers.add(exMember);
		cout << "The membership has successfully been revoked." << endl;
	}
	else
		cout << "Sorry, that member doesn't appear to be on our list of current members." << endl;
}


void MemberManager::displayCurrentMembers()
{
	if (!currentMembers.isEmpty())
		currentMembers.displayList();
	else
		cout << "Sorry, it looks like there's no current members on the list to display." << endl;
}


void MemberManager::displayPastMembers()
{
	if (!pastMembers.isEmpty())
		pastMembers.displayList();
	else
		cout << "Sorry, it looks like there's no current members on the list to display." << endl;
}


// Helper functions- checks
bool MemberManager::dateIsInvalid(int day, int month, int year)
{
	// If the month is february
	if (month == 2)
	{
		// If it's a leap year, check if the day is 29 or less
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		{
			if (day < 30)
				return false;
			else
			{
				cout << "Sorry, it seems that's not a valid date according to the Gregorian calendar. Please try again." << endl;
				return true;
			}
		}
		// Otherwise check it's 28 or less
		else if (day < 29)
			return false;
		else
		{
			cout << "Sorry, it seems that's not a valid date according to the Gregorian calendar. Please try again." << endl;
			return true;
		}
	}

	// If it's a month with 30 days, check the day is 30 or less
	else if (month == 4 || month == 6 || month == 9 || month == 11)
		if (day < 31)
			return false;
		else
		{
			cout << "Sorry, it seems that's not a valid date according to the Gregorian calendar. Please try again." << endl;
			return true;
		}
	// Add future date check back in w/o localtime if time! <-----------------------------------------------------------------------------------------!!!
	// Otherwise, prior basic checks will mean the day is at 31 or less for the rest of the months
	else
		return false;
}


bool MemberManager::memberIsInCategory(int* joinDatePointer, int cutOffDate[3])
{
	// Check if the join date comes before the cut off for the category, or is the same as it
	if (joinDatePointer[2] < cutOffDate[2])
		return true;
	else if ((joinDatePointer[2] == cutOffDate[2]) && joinDatePointer[1] < cutOffDate[1])
		return true;
	else if ((joinDatePointer[2] == cutOffDate[2]) && (joinDatePointer[1] == cutOffDate[1]) && joinDatePointer[0] < cutOffDate[0])
		return true;
	else if ((joinDatePointer[2] == cutOffDate[2]) && (joinDatePointer[1] == cutOffDate[1]) && joinDatePointer[0] == cutOffDate[0])
		return true;
	else
		return false;
}


bool MemberManager::membershipIsUnique(int membershipNum)
{
	int location = 0;
	return (linearSearch(currentMembers, membershipNum, location) || linearSearch(pastMembers, membershipNum, location)) ? false : true;
}


bool MemberManager::linearSearch(MemberList& members, int membershipNum, int& location)
{
	bool found = false;

	// Until the membership number is found or we've searched the whole list
	while (!found && location < members.getNumOfMembers())
	{
		if (membershipNum == (members.getMember(location)).getMembershipNumber())
			found = true;
		else
			location++;
	}
	return found;
}


// Helper methods - info grabbers
void MemberManager::getDate(int& day, int& month, int& year)
{
	do
	{
		// Get the day and do basic validation
		cout << "Day (1 - 31): ";
		cin >> day;
		while (cin.fail() || day < 1 || day > 31 || cin.peek() == '.' || cin.peek() == '/' || cin.peek() == '-')
		{
			cout << endl << "That's not a valid day, please enter a number within the range 1 - 31: " << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> day;
		}

		// Get the month and do basic validation
		cout << "Month (1 - 12): ";
		cin >> month;
		while (cin.fail() || month < 1 || month > 12 || cin.peek() == '.' || cin.peek() == '-' || cin.peek() == '-')
		{
			cout << endl << "That's not a valid month, please enter a number within the range 1 - 12: " << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> month;
		}

		// Get the year and do basic validation that it's a "full" format year
		cout << "Year in full (e.g. 1990): ";
		cin >> year;
		while (cin.fail() || year < 1000 || cin.peek() == '.' || cin.peek() == '/' || cin.peek() == '-')
		{
			cout << endl << "Sorry, that is not a valid year, please enter a full year from 1000 AD onwards: " << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> year;
		}
	} while (dateIsInvalid(day, month, year));
}


void MemberManager::getMemberDetails(string& firstName, string& lastName, int& membershipNum, int& day, int& month, int& year, bool& currentMember)
{
	int choice;
	
	// Get the member's name
	cout << endl << "Please enter the member's details below." << endl;
	cout << "First Name: ";
	cin >> firstName;
	cout << "Last Name: ";
	cin >> lastName;

	// Get their join date
	cout << endl << "Please enter the date the member joined as individual integers:" << endl;
	getDate(day, month, year);

	// Get their membership number
	cout << "Membership Number: ";
	cin >> membershipNum;
	while (cin.fail() || !membershipIsUnique(membershipNum) || cin.peek() == '.')
	{
		cout << endl << "That's not valid membership number, please enter a whole number that is different than other current members: " << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> membershipNum;
	}

	// Get their membership status
	cout << "Are they a current member?" << endl;
	cout << "1. Yes." << endl;
	cout << "2. No." << endl;
	cout << "Enter number of choice: ";
	cin >> choice;
	while (cin.fail() || choice < 1 || choice > 2 || cin.peek() == '.')
	{
		cout << endl << "That's not a valid choice, please enter 1 for yes or 2 for no: " << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> choice;
	}
	if (choice == 1)
		currentMember = true;
	else if (choice == 2)
		currentMember = false;
}


void MemberManager::displayWelcome()
{
	cout << "************************************************************************************" << endl;
	cout << "***                                    Welcome!                                  ***" << endl;
	cout << "***          This program will allow you to add society members to the           ***" << endl;
	cout << "***           membership list, view members in order of their length             ***" << endl;
	cout << "***              of membership, and remove members from the list.                ***" << endl;
	cout << "***                                                                              ***" << endl;
	cout << "************************************************************************************";
}


void MemberManager::displayMenu()
{
	cout << endl << endl << "1. Add a member";
	cout << endl << "2. View long-standing members";
	cout << endl << "3. Revoke membership from a member";
	cout << endl << "4. View list of current members";
	cout << endl << "5. View list of past members";
	cout << endl << "Please enter the number of your choice or 0 to exit: ";
}


void MemberManager::addTestData()
{
	// Order of params: firstName, lastName, memNum, day, month, year, currentMember?
	Member mem1 = Member("Carrie", "Morris", 1000, 30, 06, 1990, true);
	Member mem2 = Member("Kayleigh", "Stewart", 2000, 28, 02, 1992, true);
	Member mem3 = Member("Garreth", "Tigwell", 3000, 03, 12, 1976, true);
	Member mem4 = Member("Harry", "Potter", 4000, 03, 12, 1976, true);
	Member mem5 = Member("John", "Doe", 5000, 03, 12, 1976, true);
	Member mem6 = Member("Jane", "Deer", 6000, 15, 06, 1990, true);
	Member mem7 = Member("Helena", "Bell", 7000, 01, 06, 1990, true);
	Member mem8 = Member("Dawn", "Morris", 8000, 30, 06, 1990, true);
	Member mem9 = Member("Gordon", "Winks", 9000, 28, 07, 1990, true);
	Member mem10 = Member("Ryeowook", "Kim", 10000, 20, 01, 1990, true);
	Member mem11 = Member("Heechul", "Kim", 1001, 13, 8, 2017, true);
	Member mem12 = Member("Caitlin", "Morris", 2001, 30, 06, 2000, true);
	Member mem13 = Member("John", "Watson", 3001, 22, 10, 2009, true);
	Member mem14 = Member("Antonio", "Black", 4001, 01, 05, 1745, true);
	Member mem15 = Member("Joseph", "White", 5001, 19, 03, 2001, true);
	Member mem16 = Member("Adam", "White", 6001, 19, 03, 1980, true);
	Member mem17 = Member("Laura", "Smith", 7001, 13, 03, 1981, true);
	Member mem18 = Member("Josh", "Collie", 8001, 13, 03, 1981, true);
	Member mem19 = Member("Ann", "Brown", 9001, 29, 11, 1979, true);
	Member mem20 = Member("Jenifer", "Fowler", 1002, 19, 03, 1950, true);
	Member mem21 = Member("Blake", "McDonald", 1003, 19, 03, 1964, true);

		
	currentMembers.add(mem1);
	currentMembers.add(mem2);
	currentMembers.add(mem3);
	currentMembers.add(mem4);
	currentMembers.add(mem5);
	currentMembers.add(mem6);
	currentMembers.add(mem7);
	currentMembers.add(mem8);
	currentMembers.add(mem9);
	currentMembers.add(mem10);
	currentMembers.add(mem11);
	currentMembers.add(mem12);
	currentMembers.add(mem13);
	currentMembers.add(mem14);
	currentMembers.add(mem15);
	currentMembers.add(mem16);
	currentMembers.add(mem17);
	currentMembers.add(mem18);
	currentMembers.add(mem19);
	currentMembers.add(mem20);
	currentMembers.add(mem21);
}