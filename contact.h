#ifndef CONTACT_H
#define CONTACT_H

#include<iostream>
using namespace std;

class Contact
{
	private:
		string fname;
		string lname;
		string email;
		string phone;
		string city;
		string country;
		bool isFav;

	public:
		Contact(string fname1, string lname1, string email1, string phone1, string city1, string country1, bool isFav1);
		friend class Node;
		friend class ContactBST;
};

#endif