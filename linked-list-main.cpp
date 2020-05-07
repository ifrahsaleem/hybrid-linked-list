#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "linked-list.h"

using namespace std;

int main()
{
	CardList list;
	string creditCardNo;
	string ccnum;
	bool date = false;
	string a, s, f;
	int m, yr, b;
	bool dig = true;

	do 
	{
		cout << endl << " 1) Upload Card(s) from a File\n 2) Display List Chronological \n 3) Display List Reverse Chronological \n 4) Card Search \n 5) Bulk Delete \n 6) Exit \nPlease choose option from the menu: " ;
		if(cin >> b)
		{

				if (b == 1)
					list.insertCard();
			
				//--------------------------------------------------------------
		
				else if (b == 2)
					list.displayListChronological();
				//--------------------------------------------------------------
	
				else if (b == 3)
					list.displayListReverseChronological();
			
				//--------------------------------------------------------------
	
				else if (b == 4)
				{
			
						cout << "Please enter the credit card number: " ;
						cin >> ccnum;
						int i = 0;
						dig = true;
				
						if (ccnum.length() == 16)  // length of credit card num should be 16
						{
							while(i != 16) // they all must be integers between 0 and 9
							{
								if ( ccnum[i] != '0' &&
									 ccnum[i] != '1' &&
									 ccnum[i] != '2' &&
									 ccnum[i] != '3' &&
									 ccnum[i] != '4' &&
									 ccnum[i] != '5' &&
									 ccnum[i] != '6' &&
									 ccnum[i] != '7' &&
									 ccnum[i] != '8' &&
									 ccnum[i] != '9' )
								{
									dig = false;
								}
								i++;
							}
						}
					if(ccnum.length() != 16 || !dig)
					{
						cout << "Invalid format!" << endl << endl;
						dig = false;
					}
					if (dig)
						list.cardSearch(ccnum);
				}
	
				//--------------------------------------------------------------
	
				else if (b == 5)
				{
			
					cout << "Please enter month and year: " ;
			 
					// checking the validity of the month and year 
					if (cin >> m) 
					{
						if (cin >> yr)
						{
							if ( m >= 1 && m <= 12)
							{
								date = true;
							}
						}

						else 
						{
							cin.clear();
							cin >> s;
						}
					}
				
					else
					{
						cin.clear();
						cin >> s >> a;
					}
			
					if (!date)
						cout << "Invalid format!" << endl;

					else 
						list.bulkDelete (m, yr);

			}
		
			//--------------------------------------------------------------
		
			else if (b == 6)
			{
				cout << "Terminating!!!" << endl; 

				list.deleteAll();
			}
		
			//--------------------------------------------------------------

			else
			{
				cout << "Invalid operation!" << endl;
			}
		}

		else 
		{
			cout << "Invalid operation!" << endl;
			cin.clear();
			cin >> f;
		}
	} while(b != 6);
	return 0;
}

