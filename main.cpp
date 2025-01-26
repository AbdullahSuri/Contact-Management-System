#include <sstream>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include "myvector.h"
#include "contact.h"
#include "contactbst.h"

// using namespace std; //added this

void listCommands()
{
	cout << "----------------------------------" << endl;
	cout << "import <path>      :Import contacts from a CSV file" << endl
		 << "export <path>      :Export contacts to a CSV file" << endl
		 << "add                :Add a new contact" << endl
		 << "update <key>       :Update a contact's details" << endl
		 << "remove <key>       :Delete a contact" << endl
		 << "searchFor <key>    :Search for a contact" << endl
		 << "markFav <key>      :Mark as favourite" << endl
		 << "unmarkFav <key>    :Unmark as favourite" << endl
		 << "printASC           :Print contacts in ascending order" << endl
		 << "printDES           :Print contacts in descending order" << endl
		 << "printFav           :Print all favourite contacts" << endl
		 << "help               :Display the available commands" << endl
		 << "exit               :Exit the program" << endl;
}

int main(void)
{
	ContactBST contactbst;
	listCommands();
	string user_input;
	string command;
	string parameter;
	do
	{
		cout << ">";
		getline(cin, user_input);

		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr, command, ' ');
		getline(sstr, parameter);

		// respective function is called according to user command
		if (command == "import")
		{
			ifstream file(parameter);
			if (!file) // if file path is valid invoke the import function
			{
				cout << "Your file path is not correct, try again!!" << endl;
			}
			else
			{
				cout << contactbst.importCSV(parameter) << " records have been imported" << endl;
			}
		}

		else if (command == "export")
		{
			ofstream file(parameter);
			cout << contactbst.exportCSV(contactbst.getRoot(), file) << " records have been exported" << endl;
		}
		else if (command == "add")
		{
			cout << "please enter the details of your contact" << endl;
			string firstname, lastname, email, phonenumber, city, country, yesno;

			do
			{
				cout << "First Name: "; // checking if first name is a non-digit word
				getline(cin, firstname);
				bool is_digit = all_of(firstname.begin(), firstname.end(), ::isdigit);
				if (is_digit)
				{
					cout << "Invalid first name, try again!!" << endl;
					continue;
				}
				else
				{
					break;
				}
			} while (true);

			do
			{
				cout << "Last Name: "; // checking if last name is a non-digit word
				getline(cin, lastname);
				bool is__digit = all_of(lastname.begin(), lastname.end(), ::isdigit);
				if (is__digit)
				{
					cout << "Invalid last name, try again!! " << endl;
					continue;
				}
				else
				{
					break;
				}
			} while (true);

			do
			{
				cout << "Email: "; // parsing the email
				getline(cin, email);
				bool iss_digit = all_of(email.begin(), email.end(), ::isdigit);
				if (iss_digit) // the email should not be a digit
				{
					cout << "Invalid email, try again!! ";
					continue;
				}
				else
				{
					stringstream sstr(email);
					if (sstr.peek() != '@' and !isdigit(sstr.peek())) // the email should not start with @ or digit
					{
						while (sstr.peek() != '@' and !sstr.eof()) // goes to @
						{
							sstr.get();
						}
						if (sstr.peek() == '@') // when the program  finds @
						{
							sstr.get();
							if (sstr.peek() != '.' and !isdigit(sstr.peek())) // the program should not find '.' right after the @
							{
								while (sstr.peek() != '.' and !sstr.eof())
								{
									sstr.get();
								}
								sstr.get();
								sstr.get();

								if (sstr.eof())
								{
									cout << "Invalid email, try again!! ";
									continue;
								}
								else
								{
									break;
								}
							}
							else // if it finds '.' right after @ the email is invalid
							{
								cout << "Invalid email, try again!! ";
								continue;
							}
						}
						else // this is the case where the program does not find @ after a string
						{
							cout << "Invalid email, try again!! ";
							continue;
						}
					}
					else // this is the case where the email starts with @ or a digit, thus the email is declared invalid
					{
						cout << "Invalid email, try again!! ";
						continue;
					}
				}
			} while (true);

			do
			{
				cout << "Phone#: ";
				getline(cin, phonenumber);
				bool is_digitt = all_of(phonenumber.begin(), phonenumber.end(), ::isdigit);
				if (phonenumber == "") // if the phone number is not entered it is invalid
				{
					cout << "Invalid phone number, try again!! ";
					continue;
				}
				else
				{
					if (is_digitt) // if the phone number is all digits it is valid
					{
						break;
					}
					else
					{
						stringstream sstr(phonenumber);
						if (sstr.peek() == '+') // this checks if the phone number is not all digits,it should start with +
						{
							sstr.get();
							string numberstr;
							int desired_len = phonenumber.length() - 1;
							while (!sstr.eof())
							{
								if (desired_len == numberstr.length())
								{
									break;
								}
								numberstr += sstr.peek();
								sstr.get();
							}
							bool is____digitt = all_of(numberstr.begin(), numberstr.end(), ::isdigit); // if the phone number starts + it should be all digits after that
							if (is____digitt)
							{
								break;
							}
							else
							{
								cout << "Invalid phone number, try again!! "; // if it is not all digits after + it is an invalid phone number
								continue;
							}
						}
						else
						{
							cout << "Invalid phone number, try again!! ";
							continue;
						}
					}
				}

			} while (true);

			do
			{
				cout << "City: "; // checks if the city is not a digit
				getline(cin, city);
				bool is__digitt = all_of(city.begin(), city.end(), ::isdigit);

				if (is__digitt)
				{
					cout << "Invalid city, try again!!" << endl;
					continue;
				}
				else
				{
					break;
				}
			} while (true);

			do
			{
				cout << "Country: "; // checks if the country is not a digit
				getline(cin, country);
				bool is__digittt = all_of(country.begin(), country.end(), ::isdigit);

				if (is__digittt)
				{
					cout << "Invalid city, try again!!" << endl;
					continue;
				}
				else
				{
					break;
				}
			} while (true);

			bool favbool;
			do
			{
				cout << "Do you want to add the contact in your favourites(y/n): ";
				getline(cin, yesno);

				if (yesno == "y") // this checks if the user enters y or n
				{
					favbool = true;
					break;
				}
				else if (yesno == "n")
				{
					favbool = false;
					break;
				}
				else
				{
					cout << "Either enter 'y' or 'n'" << endl;
					continue;
				}
			} while (true);

			string name = firstname + " " + lastname;
			Contact *thiscontact = new Contact(firstname, lastname, email, phonenumber, city, country, favbool);

			contactbst.add(contactbst.getRoot(), name, thiscontact); // creates a contact, and then adds a new node
			cout << "Contact " << name << " has been succesfully added" << endl;
		}
		else if (command == "update")
			contactbst.update(parameter);
		else if (command == "remove")
			contactbst.remove(contactbst.getRoot(), parameter);
		else if (command == "searchFor")
		{
			Node *searchfor_n = contactbst.searchFor(contactbst.getRoot(), parameter);
			if (searchfor_n != NULL)
			{
				searchfor_n->print();
			}
			else
			{
				cout << "0 records found" << endl;
			}
		}
		else if (command == "markFav")
			contactbst.markFav(parameter);
		else if (command == "unmarkFav")
			contactbst.unmarkFav(parameter);
		else if (command == "printASC")
			contactbst.printASC(contactbst.getRoot());
		else if (command == "printDES")
			contactbst.printDES(contactbst.getRoot());
		else if (command == "printFav")
			contactbst.printFav(contactbst.getRoot());
		else if (command == "help")
			listCommands();
		else if (command == "exit" or command == "quit")
			break;
		else if (command == "")
			continue;
		else
		{
			cout << "Invalid Command!!" << endl;
		}
	} while (true);

	return 0;
}