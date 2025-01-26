#include "contactbst.h"
#include<sstream>
#include<fstream>


ContactBST::ContactBST()  //contructor for contactbst
{
    root = NULL;
}

ContactBST::~ContactBST()    ///destructor for this class
{
    while (root != NULL)
    {
        if(root->contactVector.size()==1)   //if there are no dupliactes in node it just uses remove function to remove node
        {
            remove(root, root->getKey());
        }
        else            //if there are duplicates in node it erases all elements of a vector until vector size is one, we do this so the remove function does not take any input from the user 
        {
            for (int i = 0; i < root->contactVector.size()-1; i++)
            {
                root->contactVector.erase(i);
            }
        }
    }

}

Node* ContactBST::getRoot()  //simply returns root
{
    return root;
}



void ContactBST::add(Node* ptr,string key, Contact *data)
{   
    if(root == NULL)     //adds root
    {
        root = new Node(key, data);
    }
    else        //traverses over list using recursion
    {
        string ptrkey = ptr->getKey();
        if (key == ptrkey)   //if current node key is equal to input key then it just pushes to the vector
        {
            bool check_duplicate;  //this is to check if the contact is not entirely same 
            for (int i = 0; i < ptr->contactVector.size(); i++)
            {
                if (data->city == ptr->contactVector.at(i)->city && data->country == ptr->contactVector.at(i)->country && data->email == ptr->contactVector.at(i)->email && data->phone == ptr->contactVector.at(i)->phone)
                {
                    check_duplicate = true;
                    break;
                }
                else
                {
                    check_duplicate = false;
                }
            }
            
            if (!check_duplicate)
            {
                ptr->contactVector.push_back(data);
            }  
        }
        else if (key < ptrkey)  //if input key is alphabetically small adds to the left of the current key
        {
            if (ptr->left == NULL)
            {
                Node* addednode = new Node(key, data);
                ptr->left = addednode;
                addednode->parent = ptr;
            }
            else
            {
                add(ptr->left, key, data);
            }
        }
        else if (ptrkey < key)   //if input key is alphabetically bigger adds to the right of the current key
        {
            if (ptr->right == NULL)
            {
                Node* addednode = new Node(key, data);
                ptr->right = addednode;
                addednode->parent = ptr;
            }
            else
            {
                add(ptr->right, key, data);
            }
        }
    }  
}




void ContactBST::update(string key)
{
    Node* updatenode = searchFor(root, key);
    if (updatenode == NULL)  //case for if contact is not found 
    {
        cout<<"Contact not found"<<endl;
        return;
    }
    else    
    {
        updatenode->print();
        string recordselect;
        int vectorint;
        int yesnocheck;
        
        do  //first takes user input on what element of the vector to update
        {
            cout<<"Please select the record you want to update: ";
            getline(cin, recordselect);
            bool is_digit = all_of(recordselect.begin(), recordselect.end(),::isdigit);
            if(is_digit)
            {
                int recordint = stoi(recordselect);
                if(recordint > updatenode->contactVector.size() or recordint == 0)
                {
                    cout<<"Invalid entry, enter a valid number"<<endl; 
                    continue;
                }
                else
                {
                    vectorint = recordint-1;
                    break;
                }
            }
            else
            {
                cout<<"Invalid entry, enter a number like '1'"<<endl;
                continue;
            }
        } 
        while (true);
        do      //now takes input of what element of the contact vector to update
        {
            string updatestring;
            cout<<"Please select the record you want to update: "<<endl<<"1) First Name, 2) Last Name, 3) Email, 4) Phone#, 5) City, 6) Country : ";
            getline(cin, updatestring);
            bool is_digit = all_of(updatestring.begin(), updatestring.end(),::isdigit);
            if(!is_digit)
            {
                cout<<"Invalid input, enter a number like '1'!"<<endl;
                continue;
            }
            else
            {
                int updateint = stoi(updatestring);
                if (updateint > 6 or updateint == 0)
                {
                    cout<<"Make sure that the number that you enter is between 1 to 6"<<endl;
                    continue;
                }
                else
                {
                    string firstname, lastname, email, phonenumber, city, country;
                    if(updateint == 1) 
                    {
                        do
                        {
                            cout<<"Please enter the new First Name: ";
                            getline(cin, firstname);
                            bool is_digit = all_of(firstname.begin(), firstname.end(),::isdigit);
                            if(is_digit)
                            {
                                cout<<"Invalid first name, try again!!"<<endl;
                                continue;
                            }
                            else
                            {
                                string u_nodekey = firstname+" "+updatenode->contactVector.at(vectorint)->lname;            //if first name is changed, key is changed, so a new node is added (with the updated key) and the previous with the outdated key is deleted
                                updatenode->contactVector.at(vectorint)->fname = firstname;
                                Contact* updatedcontact = new Contact(updatenode->contactVector.at(vectorint)->fname, updatenode->contactVector.at(vectorint)->lname, updatenode->contactVector.at(vectorint)->email, updatenode->contactVector.at(vectorint)->phone, updatenode->contactVector.at(vectorint)->city, updatenode->contactVector.at(vectorint)->country, updatenode->contactVector.at(vectorint)->isFav);
                                add(root, u_nodekey, updatedcontact);
                                Node* new_updatednode = searchFor(root, u_nodekey);
                                if (updatenode->contactVector.size()== 1)
                                {
                                    remove(root, updatenode->getKey());
                                }
                                else //if key of duplicate key is updated the outdated key is simply erased from the vector, a new updated node is added to the bst
                                {
                                    updatenode->contactVector.erase(vectorint);
                                }
                                updatenode = new_updatednode;
                                vectorint = 0;
                                
                                break;
                            }
                        } 
                        while (true);
                    }
                    else if(updateint == 2) 
                    {
                        do
                        {
                            cout<<"Please enter the new Last Name: ";
                            getline(cin, lastname);
                            bool is__digit = all_of(lastname.begin(), lastname.end(), ::isdigit);
                            if(is__digit)
                            {
                                cout<<"Invalid last name, try again!! "<<endl;
                                continue;
                            }
                            else
                            {
                                string u_nodekey = updatenode->contactVector.at(vectorint)->fname+" "+lastname;    //if last name is changed, key is changed, so a new node is added (with the updated key) and the previous with the outdated key is deleted
                                updatenode->contactVector.at(vectorint)->lname = lastname;
                                Contact* updatedcontact = new Contact(updatenode->contactVector.at(vectorint)->fname, updatenode->contactVector.at(vectorint)->lname, updatenode->contactVector.at(vectorint)->email, updatenode->contactVector.at(vectorint)->phone, updatenode->contactVector.at(vectorint)->city, updatenode->contactVector.at(vectorint)->country, updatenode->contactVector.at(vectorint)->isFav);
                                add(root, u_nodekey, updatedcontact);
                                Node* new_updatednode = searchFor(root, u_nodekey);
                                if (updatenode->contactVector.size()== 1)
                                {
                                    remove(root, updatenode->getKey());
                                }
                                else  //if key of duplicate key is updated the outdated key is simply erased from the vector, a new updated node is added to the bst
                                {
                                    updatenode->contactVector.erase(vectorint);
                                }
                                updatenode = new_updatednode;
                                vectorint = 0;

                                break;
                            }
                        } 
                        while (true);
                    }
                    else if(updateint ==3)  //case for input of the email, also contains input validation for email similar to that in main
                    {
                        do
                        {
                            cout<<"Please enter the new email: ";
                            getline(cin, email);
                            bool iss_digit = all_of(email.begin(), email.end(), ::isdigit);
                            if(iss_digit)
                            {
                                cout<<"Invalid email, try again!! ";
                                continue;
                            }
                            else
                            {
                                stringstream sstr(email);
                                if (sstr.peek() != '@' and !isdigit(sstr.peek()))
                                {
                                    while(sstr.peek() != '@' and !sstr.eof()) 
                                    {
                                        sstr.get();
                                    }
                                    if (sstr.peek() == '@')
                                    {
                                        sstr.get();
                                        if (sstr.peek() != '.' and !isdigit(sstr.peek()))
                                        {
                                            while(sstr.peek() != '.' and !sstr.eof())
                                            {
                                                sstr.get();
                                            }
                                            sstr.get();
                                            sstr.get();
                                            
                                            if (sstr.eof())
                                            {
                                                cout<<"Invalid email, try again!! ";
                                                continue;
                                            }
                                            else
                                            {
                                                updatenode->contactVector.at(vectorint)->email = email;
                                                break;
                                            }		
                                        }
                                        else
                                        {
                                            cout<<"Invalid email, try again!! ";
                                            continue;
                                        }
                                    }
                                    else 
                                    {
                                        cout<<"Invalid email, try again!! ";
                                        continue;
                                    }						
                                }
                                else
                                {
                                    cout<<"Invalid email, try again!! ";
                                    continue;
                                }
                            }
                        } 
                        while (true);   
                    }
                    else if(updateint == 4)  //case for input of the phonenumber, also contains input validation for phonenumber similar to that in main
                    {
                        do
                        {
                            cout<<"Please enter the new phone number: ";
                            getline(cin, phonenumber);
                            bool is_digitt = all_of(phonenumber.begin(), phonenumber.end(), ::isdigit);
                            if (phonenumber == "")
                            {
                                cout<<"Invalid phone number, try again!! ";
                                continue;
                            }
                            else
                            {
                                if(is_digitt)
                                {
                                    updatenode->contactVector.at(vectorint)->phone = phonenumber;
                                    break;
                                }
                                else
                                {
                                    stringstream sstr(phonenumber);
                                    if (sstr.peek() == '+')
                                    {
                                        sstr.get();
                                        string numberstr;
                                        int desired_len = phonenumber.length()-1;
                                        while (!sstr.eof())
                                        {
                                            if (desired_len == numberstr.length())
                                            {
                                                break;
                                            }
                                            numberstr += sstr.peek();
                                            sstr.get();
                                        }
                                        bool is____digitt = all_of(numberstr.begin(), numberstr.end(), ::isdigit);
                                        if(is____digitt)
                                        {
                                            updatenode->contactVector.at(vectorint)->phone = phonenumber;
                                            break;
                                        }
                                        else
                                        {
                                            cout<<"Invalid phone number, try again!! ";
                                            continue;
                                        }
                                    }
                                    else
                                    {
                                        cout<<"Invalid phone number, try again!! ";
                                        continue;
                                    }
                                }
                            }
                            
                            
                        } 
                        while (true);
                    }
                    else if (updateint == 5) //case for input of the city, also contains input validation for city similar to that in main
                    {
                        do
                        {
                            cout<<"Please enter the new City: ";
                            getline(cin, city);
                            bool is__digitt = all_of(city.begin(), city.end(), ::isdigit);
                            
                            if(is__digitt)
                            {
                                cout<<"Invalid city, try again!!"<<endl;
                                continue;
                            }
                            else
                            {
                                updatenode->contactVector.at(vectorint)->city = city;
                                break;
                            }
                        } 
                        while (true);
                    }
                    else if (updateint == 6)  //case for input of the city, also contains input validation for city similar to that in main
                    {
                        do
                        {
                            cout<<"Please enter the new Country: ";
                            getline(cin, country);
                            bool is__digittt = all_of(country.begin(), country.end(), ::isdigit);
                            
                            if(is__digittt)
                            {
                                cout<<"Invalid city, try again!!"<<endl;
                                continue;
                            }
                            else
                            {
                                updatenode->contactVector.at(vectorint)->country = country;
                                break;
                            }
                        } 
                        while (true);
                    }
                    cout<<"The contact has been successfully updated"<<endl;
                    string yesno;
                    do    //this loop helps the bigger dowhile loop to continue so that the user can make additional changes to the contact
                    {
                        cout<<"Do you want to edit another field(y/n): ";
                        getline(cin, yesno);
                        if (yesno == "y")
                        {
                            yesnocheck=0;
                            break;
                        }
                        else if (yesno == "n")
                        {
                            yesnocheck=1;
                            break;
                        }
                        else
                        {
                            cout<<"Either enter 'y' or 'no'"<<endl;
                            continue;
                        }
                    } 
                    while (true);

                    if(yesnocheck==0)
                    {
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        } 
        while (true);
    }
    
}


void ContactBST::remove(Node* ptr,string key)   
{
    Node* removenode = searchFor(ptr, key);
    if (removenode == NULL)   //case for if node is not found
    {
        return;
    }
    if (removenode->contactVector.size() == 1)   //case for dealing with non-duplicate keys
    {
        if (removenode->left != NULL && removenode->right != NULL)  //if node has two children
        { 
            Node* replacenode = findMin(removenode->right);
            Contact* tempcontact = new Contact(replacenode->contactVector.at(0)->fname, replacenode->contactVector.at(0)->lname, replacenode->contactVector.at(0)->email, replacenode->contactVector.at(0)->phone, replacenode->contactVector.at(0)->city, replacenode->contactVector.at(0)->country, replacenode->contactVector.at(0)->isFav);
            Node* newnode = new Node(replacenode->getKey(), tempcontact);   //created a deep copy of the node that is supposed to replace the node to be removed
            if(removenode->right == replacenode)     //if node to be replaced is the right child of the node to be removed this is executed
            {
                newnode->left = removenode->left; 
            }
            else
            {
                newnode->left = removenode->left;
                newnode->right = removenode->right;
            }

            if(removenode->parent == NULL)  //setting the parent of the newnoe(copy of the node to be replaced according to the position of the node to be removed 
            {
                root = newnode;
                newnode->parent = NULL;
            }
            else if (removenode == removenode->parent->left)
            {
                removenode->parent->left = newnode;
            }
            else
            {
                removenode->parent->right = newnode;
            }
            delete removenode;
            remove (replacenode, replacenode->getKey());
            
        }
        else if (removenode->left == NULL && removenode->right == NULL)  //if node has no children
        {
            if (removenode == root)
            {
                root = NULL;
                delete removenode;
            }
            else
            {
                if(removenode == removenode->parent->right)
                {
                    removenode->parent->right = NULL;
                }
                else
                {
                    removenode->parent->left = NULL;
                }
                delete removenode;
            }

        }
        else if (removenode->left == NULL && removenode->right != NULL)   //if node has only a left child
        {
            if(removenode == root)
            {
                root = removenode->right;
                removenode->right->parent = NULL;
                delete removenode;
            }
            else
            {
                if(removenode == removenode->parent->right)
                {
                    removenode->parent->right = removenode->right;
                    removenode->right->parent = removenode->parent;
                }
                else
                {
                    removenode->parent->left = removenode->right;
                    removenode->right->parent = removenode->parent;
                }
                delete removenode;
            }
        }
        else if (removenode->left != NULL && removenode->right == NULL)  //if node only has a right child
        {
            if(removenode == root)
            {
                root = removenode->left;
                removenode->left->parent = NULL;
                delete removenode;
            }
            else
            {
                if(removenode == removenode->parent->right)
                {
                    removenode->parent->right = removenode->left;
                    removenode->left->parent = removenode->parent;
                }
                else
                {
                    removenode->parent->left = removenode->left;
                    removenode->left->parent = removenode->parent;
                }
                delete removenode;
            }
        }
    }
    else     //the case for dealing with duplicates
    {
        removenode->print();
        string deleteintstr;
        do
			{
				cout<<"Please select the record you want to delete: ";
                getline(cin, deleteintstr);
				bool is_digit = all_of(deleteintstr.begin(), deleteintstr.end(),::isdigit);
				if(is_digit)
				{
					int deleteint = stoi(deleteintstr);
                    if(deleteint > removenode->contactVector.size() or deleteint == 0)
                    {
                        cout<<"Invalid entry, enter a valid number"<<endl; 
                        continue;
                    }
                    else
                    {
                        removenode->contactVector.erase(deleteint-1);   //it simply erases the contact from the vector based pon the user input 
                        break;
                    }
				}
				else
				{
					cout<<"Invalid entry, enter a number like '1'"<<endl;
                    continue;
				}
			} 
		while (true);
    } 
}

Node* ContactBST::searchFor(Node* ptr,string key)  
{
    if (ptr == NULL) 
    {
        return NULL;   //if no node is found(base case)
    }
    else if (key == ptr->getKey())
    {
        return ptr;   //if node is found
    }
    else
    {
        string ptrkey = ptr->getKey();   //iterates through the binary search tree using recursion
        if (key < ptrkey) 
        {
            return searchFor(ptr->left, key);
        }
        else 
        {
            return searchFor(ptr->right, key);
        }
    } 
}


bool ContactBST::markFav(string key)
{
    Node* favnode = searchFor(root, key);
    if (favnode == NULL)
    {
        cout<<"The contact was not found"<<endl;
        return false;
    }
    if(favnode->contactVector.size()==1)   //case for dealing with non-duplicate contacts: their bool value of isFAv is accessed through the contact vector
    {
        favnode->contactVector.at(0)->isFav = 1;
        cout<<favnode->getKey()<<" has been sucessfully marked as favorite!"<<endl;
        return true;
    }
    else  //case for dealing with duplicate contacts: their bool value of isFAv is accessed through the contact vector
    {
        favnode->print();
        string markfav;
        do
			{
				cout<<"Please select the record you want to mark as favorite: ";
                getline(cin, markfav);
				bool is_digit = all_of(markfav.begin(), markfav.end(),::isdigit);
				if(is_digit)
				{
					int markfavint = stoi(markfav);
                    if(markfavint > favnode->contactVector.size() or markfavint == 0)
                    {
                        cout<<"Invalid entry, enter a valid number"<<endl; 
                        continue;
                    }
                    else
                    {
                        favnode->contactVector.at(markfavint-1)->isFav = 1;
                        cout<<favnode->getKey()<<" ("<<favnode->contactVector.at(markfavint-1)->email<<") has been sucessfully marked as favorite!"<<endl;
                        return true;
                        break;
                    }
				}
				else
				{
					cout<<"Invalid entry, enter a number like '1'"<<endl;
                    continue;
				}
			} 
		while (true);
    }
    
}

bool ContactBST::unmarkFav(string key)
{
    Node* unfavnode = searchFor(root, key);
    if (unfavnode == NULL)
    {
        cout<<"The contact was not found"<<endl;
        return false;
    }
    if(unfavnode->contactVector.size()==1) //case for dealing with non-duplicate contacts: their bool value of isFAv is accessed through the contact vector
    {
        unfavnode->contactVector.at(0)->isFav = 0;
        cout<<unfavnode->getKey()<<" has been sucessfully unmarked as favorite!"<<endl;
        return true;
    }
    else  //case for dealing with duplicate contacts: their bool value of isFAv is accessed through the contact vector
    {
        unfavnode->print();
        string unmarkfav;
        do
			{
				cout<<"Please select the record you want to unmark as favorite: ";
                getline(cin, unmarkfav);
				bool is_digit = all_of(unmarkfav.begin(), unmarkfav.end(),::isdigit);
				if(is_digit)
				{
					int unmarkfavint = stoi(unmarkfav);
                    if(unmarkfavint > unfavnode->contactVector.size() or unmarkfavint == 0)
                    {
                        cout<<"Invalid entry, enter a valid number"<<endl; 
                        continue;
                    }
                    else
                    {
                        unfavnode->contactVector.at(unmarkfavint-1)->isFav = 0;
                        cout<<unfavnode->getKey()<<" ("<<unfavnode->contactVector.at(unmarkfavint-1)->email<<") has been sucessfully unmarked as favorite!"<<endl;
                        return true;
                        break;
                    }
				}
				else
				{
					cout<<"Invalid entry, enter a number like '1'"<<endl;
                    continue;
				}
			} 
		while (true);
    }
}

void ContactBST::printASC(Node* ptr)  //inorder traversal done using recursion
{
    if (ptr == NULL)
    {
        return;
    }
    else
    {
        printASC(ptr->left);
        ptr->print2(cout);
        printASC(ptr->right);
    }
}

void ContactBST::printDES(Node* ptr)  //opposite of inorder tarversal done using recursion as ptr->right is printed first, so biggest value will be returned first
{
    if (ptr == NULL)
    {
        return;
    }
    else
    {
        printDES(ptr->right);
        ptr->print2(cout);
        printDES(ptr->left);
    }
}

void ContactBST::printFav(Node* ptr)  //prints the Fav based on the boolean isFav value of teh contact, it uses inorder traversal as well since we have to print the contacts in ascending order
{
    if (ptr == NULL)
    {
        return;
    }
    else
    {
        printFav(ptr->left);
        if(ptr->contactVector.size() == 1 && ptr->contactVector.at(0)->isFav == 1)
        {
            ptr->print2(cout);
        }
        else if (ptr->contactVector.size() > 1)
        {
            for (int i = 0; i < ptr->contactVector.size(); i++)
            {
                Contact *ct = ptr->contactVector.at(i);
                if (ct->isFav == true)
                {
                    cout<<ct->fname<<","<<ct->lname<<","<<ct->email<<","<<ct->phone<<","<<ct->city<<","<<ct->country<<","<<ct->isFav<<endl;
                }
            }
            
        }
        printFav(ptr->right);
    }
}


int ContactBST::importCSV(string path)
{
    string firstname, lastname, email, phonenumber, city, country, yesno;
    ifstream fin(path);
    if (fin.is_open())
    {
        int no_ofline = 0;
        string line;
        while (getline(fin, line))
        {
            stringstream sstr(line);   //uses sstream to store values of the contacts in different variables
            getline(sstr, firstname, ',');
            getline(sstr, lastname, ',');
            getline(sstr, email, ',');
            getline(sstr, phonenumber, ',');
            getline(sstr, city, ',');
            getline(sstr, country, ',');
            getline(sstr, yesno, '\r');
            
            bool favbool;
            if(yesno == "1")
            {
                favbool = true;
            }
            else if(yesno == "0")
            {
                favbool = false;
            }

            Contact* importedcontact = new Contact(firstname, lastname, email, phonenumber, city, country, favbool);   //makes a new contact and that using that contact and its key, adds it to the bst using the add function
            add(root, firstname + " " + lastname, importedcontact);
            no_ofline++;
            
        }
        fin.close();
        return no_ofline; 
    }
    else
    {
        cout<<"error finding the file, check your path!!"<<endl;
        return -1;
    }
}

int ContactBST::exportCSV(Node* ptr,ostream& file)
{
    int export_count=0; 
    if(ptr == NULL)   //base case
    {
        return 0;
    }
    else  //uses in order traversal as well, to print in ascending order
    {
        export_count += exportCSV(ptr->left, file);  //uses recursion to print the contacts onto the export file, it also simultaneously increments the count of the number of contacts uploaded
        ptr->print2(file);
        export_count++;    
        export_count += exportCSV(ptr->right, file);
        return export_count;
    }
}

Node* ContactBST::findMin(Node* ptr)
{
    if (ptr == NULL)  //case for if bst is empty
    {
        return NULL;
    }
    else
    {
        if(ptr->left == NULL)
        {
            return ptr;
        }
        else
        {
            return findMin(ptr->left);
        }    
    }
}