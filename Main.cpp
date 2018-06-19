#include "MemberManager.h"


int main()
{
	MemberManager currentSession;
	int menuChoice = 1;

	currentSession.addTestData();
	currentSession.displayWelcome();

	while (menuChoice != 0)
	{
		currentSession.displayMenu();
		cin >> menuChoice;

		while (cin.fail() || menuChoice < 0 || menuChoice > 5 || cin.peek() == '.')
		{
			cout << endl << "That's not a valid choice, please enter 1-5, or 0 to exit: " << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> menuChoice;
		}

		switch (menuChoice)
		{
		case 1:
			// Add a member to the current or past members list
			currentSession.addMember();
			break;

		case 2:
			// Display a broken down list of long-standing members in order of the length of their membership
			currentSession.displayLongstandingMembers();
			break;

		case 3:
			// Remove a member from the current members list to the past members list and update their membership
			currentSession.revokeMembership();
			break;

		case 4:
			// Display the list of current members
			currentSession.displayCurrentMembers();
			break;

		case 5:
			// Display the list of past members
			currentSession.displayPastMembers();
			break;

		case 0:
			// If the user wants to exit, don't display an error message and exit.
			break;

		default:
			// If not an expected entry, get a new choice number
			cout << "That's not a valid choice, please enter 1-5, or 0 to exit: " << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> menuChoice;
			break;
		}
	}

	return 0;
}