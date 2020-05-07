#ifndef _LINKED-LIST_H
#define _LINKED-LIST_H
using namespace std;

struct creditCardNode
{
	string creditCardNo;
	creditCardNode * next;
	// constructors come here

	creditCardNode::creditCardNode ()
		{}

	creditCardNode::creditCardNode (string ccnum, creditCardNode * n)
		: creditCardNo(ccnum), next(n)
	{}
};

struct expirationNode
{
	int month, year;
	creditCardNode * cHead;
	expirationNode * next;
	expirationNode * prev;

	expirationNode::expirationNode ()
		{}

	expirationNode::expirationNode (int m, int y, creditCardNode * cH,expirationNode * n, expirationNode * p)
		: month(m), year(y), cHead(cH), next(n), prev(p)
	{}
};

class CardList
{
	public:
		CardList(); //default constructor that creates an empty list
		void insertCard ();
		//inserts a new card to the structure in sorted fashion
		void displayListChronological ();
		//displays entire structure in chronological order
		void displayListReverseChronological ();
		//displays entire structure in reverse chronological order
		void cardSearch (string creditCardNo);
		//displays all of the occurrences of the given card number
		void bulkDelete (int month, int year);
		//deletes all nodes up to and including given expiration date
		void deleteAll (); //deletes the entire structure
	
	private:
		expirationNode * head;
		expirationNode * tail;
		bool CheckCC(creditCardNode * traversalPointer_2, string cc);
	// any helper functions you see necessary
};

#endif