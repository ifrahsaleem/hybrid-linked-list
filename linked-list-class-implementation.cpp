#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "linked-list.h"

using namespace std;

CardList::CardList ()
{
	head = NULL;
	tail = NULL;
}

bool CardList::CheckCC(creditCardNode * traversalPointer_2, string cc) // private member function that checks whether the credit card number in file is bigger than the one in node
{
	bool check = false;

	if (traversalPointer_2 -> creditCardNo == cc) // if credit cards are the same
		return check;

	else
	{

		for (unsigned int i= 0; i< 16; i++)
		{

			if(cc[i] > traversalPointer_2 -> creditCardNo[i]) // if credit card in the file is bigger
			{
				check = true;
				return check;
			}

			else if(cc[i] < traversalPointer_2 -> creditCardNo[i]) // if credit card in the file is smaller
			{
				check = false;
				return check;
			}
		}
	}

	return check;
}

void CardList::insertCard()
{
	int k = 0;
	creditCardNode * traversalPointer_2;
	expirationNode * traversalPointer_1;
	bool check = false, check2 = false, cc_check = false;
	string fname, line1,cc;
	ifstream input1;
	int m, yr;
	
	cout << "Please enter file name: " ;
	cin >> fname; // entering file name 
	cout << endl;

	input1.open(fname.c_str()); // opening file 

	if (input1.fail()) // if file fails to open
		cout << endl << "Cannot find a file named " << fname << endl << endl;
	
	else 
	{
		while(getline(input1,line1))
		 {
			 istringstream ss(line1);

			 ss >> cc >> m >> yr; // credit card num >> month >> year
		
			if (head == NULL)
			{
				creditCardNode * newsinglyNode = new creditCardNode(cc, NULL); // first node of singly linked list pointing towards NULL
				expirationNode * newdoublyNode = new expirationNode(m, yr, newsinglyNode ,NULL,NULL); // first node of doubly linked list where next pointing towards tail and prev towards NULL
				head = newdoublyNode;
				tail = newdoublyNode;
				cout << cc << " " << m << " " << yr << " : added to a new expiration date node" << endl;
			}

			else
			{
				traversalPointer_1 = head;
			 
				while (traversalPointer_1 != NULL && !check)
				{
					if ( traversalPointer_1 -> month == m && traversalPointer_1 -> year == yr) // if expiration date already exists, simply add to singly linked list 
					{	 
					
						if (traversalPointer_1 ->cHead == NULL) // if there is no node, make a new node pointing to NULL
						{
						 
							traversalPointer_1 -> cHead = new creditCardNode(cc, NULL);
							check = true;
						}

						else // if there is a node, traverse through it to add the new credit card 
						{
							traversalPointer_2 = traversalPointer_1 -> cHead;
							
							while (traversalPointer_2 != NULL && !check2)
							{
								cc_check = CheckCC(traversalPointer_2, cc);

								if (traversalPointer_2 -> creditCardNo == cc)// if card already exists
								{
									cout << cc << " " << m << " " << yr << " : this card was already inserted" << endl; 
									check2 = true;
									check = true;
								}

								else if(traversalPointer_2 -> next == NULL && (cc_check)) //adding to the last node 
								{
									traversalPointer_2 -> next = new creditCardNode(cc, NULL);
									cout << cc << " " << m << " " << yr << " : inserted to an existing expiration date node" << endl;
									check = true;
									check2 = true;

								}

								else if(traversalPointer_2 == traversalPointer_1 -> cHead && !(cc_check)) // adding to beginning
								{

									creditCardNode * c = new creditCardNode(cc, traversalPointer_2);
									traversalPointer_1 -> cHead = c;
									cout << cc << " " << m << " " << yr << " : inserted to an existing expiration date node" << endl;
									check = true;
									check2 = true;
								}

								else if(traversalPointer_2 -> next -> creditCardNo  != cc && (!CheckCC(traversalPointer_2 -> next, cc)) && (cc_check)) // adding between two nodes
								{
									creditCardNode * c = new creditCardNode(cc, traversalPointer_2-> next);
									traversalPointer_2 ->next  = c;
									cout << cc << " " << m << " " << yr << " : inserted to an existing expiration date node" << endl;
									check = true;
									check2 = true;
								}
								traversalPointer_2 = traversalPointer_2 -> next;
							}
						}
					}

					else // if expiration date does not already exist, make a new node
					{
						// adding nodes in a sorted manner 

						// 3 cases 
						//------------------------------------------ if adding before start node ---------------------------------------------------------------//

						if (((traversalPointer_1 -> month > m && traversalPointer_1 -> year == yr) || (traversalPointer_1 -> year > yr)) && traversalPointer_1 == head)
						//if year in file is less than the head, make it the new head 
						{
							tail = traversalPointer_1;
							creditCardNode * c = new creditCardNode(cc, NULL);
							expirationNode * e = new expirationNode(m, yr, c, head, NULL); 
							head -> prev = e;
							head = e;
							
							cout << cc << " " << m << " " << yr << " : added to a new expiration date node" << endl;
							check = true;
						}

						//-----------------------------------------if adding in middle of two nodes --------------------------------------------------------//

						else if ( traversalPointer_1 != head && ((traversalPointer_1 -> year > yr && traversalPointer_1 -> prev -> year < yr) || 
							(traversalPointer_1 -> year == yr && traversalPointer_1 -> month > m && traversalPointer_1 -> prev -> year < yr) ||
							(traversalPointer_1 -> prev -> year == yr && traversalPointer_1 -> prev -> month < m && traversalPointer_1 -> year == yr && traversalPointer_1 -> month > m) || 
							traversalPointer_1 -> year > yr && traversalPointer_1 -> prev -> year == yr  && traversalPointer_1 -> prev -> month < m)) 
							// between current(traversal node) & previous node 
						{
							if (traversalPointer_1 -> next == NULL)
							{
								tail = traversalPointer_1;
							}
					
							creditCardNode * c = new creditCardNode(cc, NULL);
							expirationNode * r = new expirationNode(m , yr, c, traversalPointer_1, traversalPointer_1 -> prev);
							traversalPointer_1 -> prev -> next = r;
							traversalPointer_1 -> prev = r;
							cout << cc << " " << m << " " << yr << " : added to a new expiration date node" << endl;
							check = true;
						}

						//-------------------------------------------if adding after last node --------------------------------------------------------------//

						else if ((traversalPointer_1 -> year < yr || (traversalPointer_1 ->year == yr && traversalPointer_1 -> month < m )) && traversalPointer_1 -> next == NULL)
						//traversal pointer points towards null and is smaller than the year 
						{
							creditCardNode * c = new creditCardNode(cc, NULL);
							expirationNode * r = new expirationNode(m , yr, c, NULL, traversalPointer_1);
							traversalPointer_1 -> next = r;
							tail = r;
							cout << cc << " " << m << " " << yr << " : added to a new expiration date node" << endl;
							check = true;
						}
					}
					traversalPointer_1 = traversalPointer_1 -> next;
				}
			check = false;
			check2 = false;
			}
		}
	}
}

void CardList::displayListChronological ()
{
	expirationNode * ptr;
	creditCardNode * ptr2 = NULL;
	int count = 1;
	ptr = head; // for traversing through the doubly linked list 

	if (ptr == NULL) // if there are no nodes 
		cout<< endl << "List is empty!" << endl ;

	while (ptr != NULL) // if the list is not empty 
	{
		cout << "Expiration Date: " << ptr -> month << " " << ptr -> year << endl;

		ptr2 = ptr ->cHead; // for traversing through the singly linked list 

		while (ptr2 != NULL)
		{

			cout << count << ") " << ptr2 ->creditCardNo << endl;
			ptr2 = ptr2 -> next;
			count++;
		}

		count = 1;
		cout << "-------------------" << endl;

		ptr = ptr->next;
	}
	delete ptr;
	delete ptr2;
}

void CardList::displayListReverseChronological ()
{
	expirationNode * ptr;
	creditCardNode * ptr2 = NULL;
	int count = 1;
	ptr = tail; // for traversing through the doubly linked list 

	if (ptr == NULL) // if there are no nodes 
	{
		cout << endl << "List is empty!" << endl;
	}

	while (ptr != NULL) // if the list is not empty 
	{
		cout << "Expiration Date: " << ptr -> month << " " << ptr -> year << endl;

		ptr2 = ptr ->cHead; // for traversing through the singly linked list 

		while (ptr2 != NULL)
		{

			cout << count << ") " << ptr2 ->creditCardNo << endl;
			ptr2 = ptr2 -> next;
			count++;
		}

		count = 1;
		cout << "-------------------" << endl;
		ptr = ptr->prev;
	}
	delete ptr;
	delete ptr2;
}

void CardList::cardSearch (string ccnum)
{
	creditCardNode * traversalPointer_2 = NULL; // for traversing through the singly linked list 
	expirationNode * traversalPointer_1 = head; // for traversing through the doubly linked list 
	bool check1 = false;

	while (traversalPointer_1 != NULL)
	{
		traversalPointer_2 = traversalPointer_1 -> cHead;
		while (traversalPointer_2 != NULL)
		{
			if (traversalPointer_2 -> creditCardNo == ccnum) // if credit card is found 
			{
				check1 = true;
				cout << "There exists a credit card given number " << ccnum << " with expiration date: " << traversalPointer_1 -> month << " " << traversalPointer_1 -> year << endl;
			}
			traversalPointer_2 = traversalPointer_2 -> next;
		}
		traversalPointer_1 = traversalPointer_1 -> next;
	}

	if (!check1) // credit card is not found 
		cout << endl << "There is no credit card with given credit card number: " << ccnum << endl << endl;

	check1 = true;
}

void CardList::bulkDelete (int m, int yr)
{
	expirationNode * ptr = head;
	expirationNode * temp;
	creditCardNode * ptr2;
	bool check = false;
	int count = 1;

	while(!check && ptr != NULL)
	{
		if (ptr -> year > yr || (ptr ->year == yr && ptr -> month > m )) // if the current date is bigger than the one input by user, stop the loop 
			check = true;

		else // keep deleting as long as date of node is smaller than the one input by user 
		{
			cout << "Node with expiration date " << ptr -> month << " " << ptr -> year << " and the following credit cards have been deleted!" << endl;
			while (ptr -> cHead != NULL)
			{
				ptr2 = ptr -> cHead;
				ptr -> cHead = ptr -> cHead -> next;
				cout << count << ") " << ptr2 ->creditCardNo << endl;
				count++;
				delete ptr2;
			}
			temp = ptr;
			ptr=ptr->next;
			head = ptr;
			count = 1;
			delete temp;
		}
	}
	if (ptr == NULL) // if list is empty after deletion
	{
	
		head = NULL;
		tail = NULL;
		
	}
	else // if list is not empty after deletion
	{
		head -> prev = NULL;
	}
}

void CardList::deleteAll ()
{
	expirationNode * ptr;
	creditCardNode * ptr2;
	while(head!=NULL)
	{
		ptr=head;
		 
		while (ptr -> cHead != NULL)
		{
			ptr2 = ptr -> cHead;
			ptr -> cHead = ptr -> cHead -> next;
			delete ptr2;
		}
		head=head->next;
		delete ptr;
	}
}
 
