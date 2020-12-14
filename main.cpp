#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <limits>
#include <cstring>
#include <windows.h>
#include <algorithm>
#include "cmd.h"

using namespace std;

void spacestr(string*&, int);
bool isnumstr(string);
void lrtrim(string*&);

list::~list() {
	node *current,*temp;
	current = head;
	temp = head;
	while(current != NULL) {
		current = current->next;
		delete temp;
		temp = current;
	}
}

struct list::node* list::initNode(string cmdstr, string pathstr, string paratrstr) {
	struct node *ptr = new node;
 
	// error? then just return
	if( ptr == NULL )                         
		return static_cast<struct node *>(NULL);  
	// assign it 
	// then return pointer to ne node
	else {  
		ptr->cmd = cmdstr;  
		ptr->path = pathstr;
		ptr->paratr = paratrstr;                        
		return ptr;                         
	}
}

// adding to the end of list  
void list::addCMD( struct node *newNode )  {
	// if there is no node, put it to head
	if( head == NULL ) {
		head = newNode;  
		tail = newNode;
	}
   
	// link in the new_node to the tail of the list
	// then mark the next field as the end of the list
	// adjust tail to point to the last node

	tail->next = newNode;       
	newNode->next = NULL;       
	tail = newNode;               
}

struct list::node* list::searchCMD(struct node* ptr, string cmdstr) {
    while( cmdstr != ptr->cmd ) {    
       ptr = ptr->next;                          
       if( ptr == NULL )                          
          break;                                  
    }
    return ptr; 	
}

void list::deleteCMD( struct list::node *ptr )
{
  struct node *temp, *prev;
   temp = ptr;    // node to be deleted 
   prev = head;   // start of the list, will cycle to node before temp    

   if( temp == prev ) {                    // deleting first node?  
       head = head->next;                  // moves head to next node     
       if( tail == temp )                  // is it end, only one node?   
          tail = tail->next;               // adjust end as well          
       delete temp ;                       // free up space 
   }
   else {                                  // if not the first node, then 
       while( prev->next != temp ) {       // move prev to the node before
           prev = prev->next;              // the one to be deleted       
       }
       prev->next = temp->next;            // link previous node to next  
       if( tail == temp )                  // if this was the end node,   
           tail = prev;                    // then reset the end pointer  
      delete temp;                         // free up space
   }
}

void list::deleteCMDLIST( struct node *ptr )
{
   struct node *temp;

   if( head == NULL ) return;   	// don't try to delete an empty list      

   if( ptr == head ) {			// if we are deleting the entire list    
       head = NULL;			// then reset head and    
       tail = NULL;			// end to empty                                     
   }
   else {
       temp = head;			// if it's not the entire list, readjust end   
       while( temp->next != ptr )       // locate previous node to ptr   
           temp = temp->next;
       tail = temp;                     // set end to node before ptr   
   }

   while( ptr != NULL ) {		// whilst there are still nodes to delete      
      temp = ptr->next;			// record address of next node                 
      delete ptr;			// free this node                             
      ptr = temp;			// point to next node to be deleted           
   }
}

void list::displayCMD( struct list::node *ptr ) const
{
    string *pathptr = &ptr->path;
	string *paratrptr = &ptr->paratr;
	
	spacestr(pathptr, 2);
	spacestr(paratrptr, 2);
	cout << "Command Name" << setw(8) << ": " << ptr->cmd << endl;
	cout << "Target Path" << setw(9) << ": " << ptr->path << endl;
	if (ptr->paratr.compare("*") == 0)
	{
		cout << "Executing argument: NO ARGUMENTS" << endl;
	}
	else
	{
		cout << "Executing argument: "<< ptr->paratr << endl;
	}
	cout << endl;
}

void list::displayCMDLIST( struct list::node *ptr) const
{
	if(!ptr)
	{
		cout << "Nothing to display" << endl;
	}
	else
	{
		cout << "-----------------\nCommand List\n-----------------\n" << endl;
		while(ptr) 
		{
			displayCMD(ptr);
			ptr = ptr->next;
		}
	}
}

bool isemptyCMDLIST( struct list::node *ptr)
{
	if(!ptr)
	{
		return 1;
	} 
	return 0;
}

void list::printCMDLIST( struct list::node *ptr, fstream &file) const
{
	string *pathptr;
	string *paratrptr;
	
	if(!ptr) cout << "\nQrun Library is empty!" << endl;
	while(ptr) {
		pathptr = &ptr->path;
		paratrptr = &ptr->paratr;
		spacestr(pathptr, 1);
		spacestr(paratrptr, 1);
		file << ptr->cmd << " " << ptr->path << " " << ptr->paratr << "\n";
		ptr = ptr->next;
	}
}

int main(int argc, char** argv)
{
	if (argc < 2) 
	{
		MessageBox( NULL, "No arguments.\nFor first time users, please firstly locate Qrun in \"C:\\WINDOWS\\\", after that, run Qrun with \"show\" argument with Windows run dialog (Win Key + \"R\") as follows:\n\nqrun.exe show" , NULL, MB_OK | MB_ICONERROR);
		return 1;
	}
	else if (argc == 2)
	{
		string arg = argv[1];

		fstream myfile;
		string line;
		string cmd;
		string newcmd;
		string path;
		string paratr;
		string *cmdptr = &cmd;
		string *pathptr = &path;
		string *paratrptr = &paratr;
		string filename = "QrunLib.dat";
		string option;
		
		list myList;
		list::node* ptr;
		
		int op;
		bool pass = false;
		myfile.open ( filename.c_str() , ios::in | ios::out);
		if (!myfile.is_open())				
		{
			// create
			myfile.open(filename.c_str(), ios::out); 
		
			// close
			if (myfile.is_open())
				myfile.close();
		
			// re-open
			myfile.open(filename.c_str(), ios::in | ios::out); 
		} 
		bool issuccess = true;
		bool fileex = false;
		while ( getline (myfile, line) )
	    {
	    	fileex = true;
			istringstream iss(line);
			HINSTANCE i;
	    	while (iss >> cmd >> path >> paratr) 
	    	{ 
	    		if (cmd.compare(arg) == 0)
	    		{
	    			spacestr(pathptr, 2);
	    			if (paratr.compare("*") == 0)
	    			{
	    				i = ShellExecute( NULL, "open", path.c_str(), NULL, NULL, SW_SHOWNORMAL);  //"*" equals to NULL;
					}
					else
					{
						spacestr(paratrptr, 2); // no "+"
						i = ShellExecute( NULL, "open", path.c_str(), paratr.c_str(), NULL, SW_SHOWNORMAL);
					}
					if ((long) i >= 0 && (long)i <= 32)
					{ 
						issuccess = false; 
					} 
					else
					{
						myfile.close();
						return 0;
					}

				}
				else if (arg.compare("show") == 0)
				{
					ptr = myList.initNode( cmd, path, paratr);
					myList.addCMD(ptr);
					issuccess = true;
				}
				else
				{
					issuccess = false;
				}
			}
	    }
	    if (!issuccess)
		{
			MessageBox( NULL, "Fail to run command. Please make sure you have created this command with valid path and parameters." , NULL, MB_OK | MB_ICONERROR);
			return 1;
		}
		while (pass != true)
		{
			bool check = false;
			string toadd;
			system("cls"); 

			if (!fileex)
			{
				cout << "Empty Qrun Library! Please add some commands!\n" << endl;
			}
			cout << "Welcome to Qrun. Written By Alex Chan.\n" << endl;
			//command list
			cout << "Please select your operation:\n" << endl;
			cout << "1. View command table" << endl;
			cout << "2. Add a new command" << endl;
			cout << "3. Edit a command" << endl;
			cout << "4. Delete a command" << endl;
			cout << "5. Exit\n" << endl;
			cout << "Please select your operation: ";
			getline (cin, option);
			pass = isnumstr(option);
			if (pass == true)
			{
				op = atoi(option.c_str());
				if (op >= 1 || op <= 5)
				{
					switch (op)
					{
						case 1:
							system("cls"); 
							myList.displayCMDLIST(myList.head);
							cout << "\nPress <Enter> to go back" << endl;
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							pass = false;
							break;
						case 2:
							system("cls");
							cout << "-----------------\nAdd a new command\n-----------------\n" << endl;
							while (check != true)
							{
								cout << "Command name, type \"exit\" to quit:\n";
								getline (cin, cmd);
								lrtrim(cmdptr);
								if (cmd.compare("") != 0)
								{
									if (cmd.find (' ') == string::npos)
								    {
								    	if (cmd.compare("exit") == 0)
										{
											myList.deleteCMDLIST(myList.head);
											myfile.close();
											return 0;
										}
										else if (cmd.compare("show") == 0)
										{
											cout  << "//This command is reserved for Qrun! Press <Enter> to retype." << endl;
											cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
											system("cls");
											cout << "-----------------\nAdd a new command\n-----------------\n" << endl;
										}
										else if ( 0 == isemptyCMDLIST( myList.head)) //unempty list
										{
											ptr = myList.searchCMD( myList.head, cmd);
											if( ptr == NULL ) 
											{
												check = true;
											}
											else
											{
												cout  << "//This command already exists! Press <Enter> to retype." << endl;
												cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
												system("cls");
												cout << "-----------------\nAdd a new command\n-----------------\n" << endl;
											}
										}
										else
										{
											check = true;
										}
								    }
								    else
								    {
								    	cout  << "//Should not contain any spaces! Press <Enter> to retype." << endl;
								    	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								    	system("cls");
								    	cout << "-----------------\nAdd a new command\n-----------------\n" << endl;
									}
								}
								else
								{
									cout  << "//Should not be empty! Press <Enter> to retype." << endl;
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									system("cls");
									cout << "-----------------\nAdd a new command\n-----------------\n" << endl;
								}
							}
							
							system("cls");
							check = false;
	    					while (check != true)
							{
								cout << "-----------------\nAdd a new command\n-----------------\n" << endl;
								cout << "Command name, type \"exit\" to quit:" << endl;
								cout << cmd << endl;
								cout << "\nPath for the file, type \"exit\" to quit:\n";
								getline (cin, path);
								if (path.compare("") != 0)
								{
									if (path.compare("exit") == 0)
									{
										myList.deleteCMDLIST(myList.head);
										myfile.close();
										return 0;
									}
									check = true;
								}
								else
								{
									cout  << "//Should not be empty! Press <Enter> to retype." << endl;
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									system("cls");
								}
							}
							
							cout << "\nParameter for the file (leave it blank for NO arguments), type \"exit\" to quit:\n";
							getline (cin, paratr);
							
							if (paratr.compare("") == 0)
							{
								paratr = "*";
							}
							else if (paratr.compare("exit") == 0)
							{
								myList.deleteCMDLIST(myList.head);
								myfile.close();
								return 0;
							}
							
	    					lrtrim(pathptr);
	    					lrtrim(paratrptr);
	    					
							check = false;
	    					while (check != true)
							{
								system("cls");
								cout << "-----------------\nAdd a new command\n-----------------\n" << endl;
								cout << "Command Name" << setw(8) << ": " << cmd << endl;
								cout << "Target Path" << setw(9) << ": " << path << endl;
								if (paratr.compare("*") == 0)
								{
									cout << "Executing argument: NO ARGUMENTS" << endl;
								}
								else
								{
									cout << "Executing argument: "<< paratr << endl;
								}
								cout << "\nConfirm to add? <y/n>" << endl;
								getline (cin, toadd);
								
								if ((toadd.compare("y") == 0)||(toadd.compare("Y") == 0))
								{
							        ptr = myList.initNode( cmd, path, paratr);
									myList.addCMD(ptr);

									myfile.close();
									myfile.open(filename.c_str(), ios::in | ios::out | ios::trunc); 
									myfile.seekg(0, ios::beg); 
									
									myList.printCMDLIST(myList.head, myfile);
									
									myfile.close();
									myfile.open(filename.c_str(), ios::in | ios::out); 
									cout << "\nCommand added!" << endl;
									cout << "Press <Enter> to go back" << endl;
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									check = true;
									
							    }
							    else if ((toadd.compare("n") == 0)||(toadd.compare("N") == 0))
							    {
							    	cout  << "\nOperation discarded." << endl;
							    	cout << "Press <Enter> to go back" << endl;
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									check = true;
								}
								else
								{
									cout  << "//Invalid input! Press <Enter> to retype." << endl;
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									check = false;
								}
							}
							pass = false;
	    					break;
						case 3: //edit
							/*check if the list is empty*/
							if ( 1 == isemptyCMDLIST( myList.head))
							{
								cout << "\nNo commands found. Please add command first." << endl;
								cout << "Press <Enter> to go back" << endl;
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								pass = false;
								break;
							}
							
							/*check if the command exists*/
							check = false;
	    					while (check != true)
							{
								system("cls");
								cout << "-----------------\nEdit a new command\n-----------------\n" << endl;
		
								cout << "Command name, type \"exit\" to quit:\n";
								getline (cin, cmd);
								lrtrim(cmdptr);
								
								if (cmd.compare("") != 0)
								{
									if (cmd.find (' ') == string::npos)
									{
										if (cmd.compare("exit") == 0)
										{
											myList.deleteCMDLIST(myList.head);
											myfile.close();
											return 0;
										}
										ptr = myList.searchCMD( myList.head, cmd);
										if( ptr == NULL ) 
										{
											cout << "//Command: " << cmd << " not found" << endl;
											cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
										}
										else 
										{
											check = true;
										}
									}
									else
								    {
								    	cout  << "//Should not contain any spaces! Press <Enter> to retype." << endl;
								    	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								    	system("cls");
								    	cout << "-----------------\nAdd a new command\n-----------------\n" << endl;
									}
								}
								else
								{
									cout  << "//Should not be empty! Press <Enter> to retype." << endl;
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									system("cls");
								}
								
							}
							
							/*new name for the command*/
							check = false;
							newcmd = cmd;
	    					while (check != true)
							{
								system("cls");
								cout << "-----------------\nEdit a new command\n-----------------\n" << endl;
								cout << "Command name, type \"exit\" to quit:" << endl;
								cout << newcmd << endl;
								cout << "\nNew name(no spaces), type \"exit\" to quit:\n";
								getline (cin, cmd);
								lrtrim(cmdptr);
								if (cmd.compare("") != 0)
								{
									if (cmd.find (' ') == string::npos)
								    {
								    	if (cmd.compare("exit") == 0)
										{
											myList.deleteCMDLIST(myList.head);
											myfile.close();
											return 0;
										}
										else if (cmd.compare("show") == 0)
										{
											cout  << "//This command is reserved for Qrun! Press <Enter> to retype." << endl;
											cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
										}
										ptr = myList.searchCMD( myList.head, cmd);
										if( ptr == NULL ) 
										{
											check = true;
										}
										else if (ptr->cmd == newcmd)
										{
											check = true;
										}
										else
										{
											cout  << "//This command already exists! Press <Enter> to retype." << endl;
											cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
										}
								    }
								    else
								    {
								    	cout  << "//Should not contain any spaces! Press <Enter> to retype." << endl;
								    	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									}
								}
								else
								{
									cout  << "//Should not be empty! Press <Enter> to retype." << endl;
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								}	
							}
							
							/*new command path*/
							ptr = myList.searchCMD( myList.head, newcmd);
							check = false;
							while (check != true)
							{	
								system("cls");
								cout << "-----------------\nEdit a new command\n-----------------\n" << endl;
								cout << "Command name, type \"exit\" to quit:" << endl;
								cout << newcmd << endl;
								cout << "\nNew name(no spaces), type \"exit\" to quit:\n";
								cout << cmd << endl;
								cout << "\nNew path for the file (type \"keep\" to keep original path), type \"exit\" to quit:\n";
								getline (cin, path);
								if (path.compare("") != 0)
								{
									if (path.compare("exit") == 0)
									{
										myList.deleteCMDLIST(myList.head);
										myfile.close();
										return 0;
									}
									else if (path.compare("keep") == 0)
									{
										path = ptr->path;
										cout << "\nThe original path is:\n\"" << path  << "\"\nand remain unchanged" << endl;
										
									}
									check = true;
								}
								else
								{
									cout  << "//Should not be empty! Press <Enter> to retype." << endl;
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								}
							}
							
							/*new command parameter*/
							check = false;
							while (check != true)
							{
							
								cout << "\nNew parameter for the file\n(leave it blank for NO arguments, \"keep\" to keep original parameter),\ntype \"exit\" to quit:\n";
								getline (cin, paratr);
								
								if (paratr.compare("") == 0)
								{
									paratr = "*";
								}
								else if (paratr.compare("keep") == 0)
								{
									paratr = ptr->paratr;
								}
								else if (paratr.compare("exit") == 0)
								{
									myList.deleteCMDLIST(myList.head);
									myfile.close();
									return 0;
								}
								check = true;
							}
							
	    					lrtrim(pathptr);
	    					lrtrim(paratrptr);
	    					
		    				/*confirm to add*/
	    					check = false;
	    					while (check != true)
							{
								system("cls");
								cout << "-----------------\nEdit a new command\n-----------------\n" << endl;
								cout << "Command Name" << setw(8) << ": " << cmd << endl;
								cout << "Target Path" << setw(9) << ": " << path << endl;
								if (paratr.compare("*") == 0)
								{
									cout << "Executing argument: NO ARGUMENTS" << endl;
								}
								else
								{
									cout << "Executing argument: "<< paratr << endl;
								}
								cout << "\nConfirm to edit? <y/n>" << endl;
								getline (cin, toadd);
								
								if ((toadd.compare("y") == 0)||(toadd.compare("Y") == 0))
								{
							        ptr->cmd = cmd;
			    					ptr->path = path;
			    					ptr->paratr = paratr;
			    					myfile.close();
									myfile.open(filename.c_str(), ios::in | ios::out | ios::trunc); 
									
									myfile.seekg(0, ios::beg); 
									
									myList.printCMDLIST(myList.head, myfile);
									
									myfile.close();
									myfile.open(filename.c_str(), ios::in | ios::out); 
									cout << "\nCommand edited!" << endl;
									cout << "Press <Enter> to go back" << endl;
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									check = true;
							    }
							    else if ((toadd.compare("n") == 0)||(toadd.compare("N") == 0))
							    {
							    	cout  << "\nOperation discarded." << endl;
							    	cout << "Press <Enter> to go back" << endl;
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									check = true;
								}
								else
								{
									cout  << "//Invalid input! Press <Enter> to retype." << endl;
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									check = false;
								}
							}
							pass = false;
							break;
						case 4:
							/*check if the list is empty*/
							if ( 1 == isemptyCMDLIST( myList.head))
							{
								cout << "\nNo commands found. Please add command first." << endl;
								cout << "Press <Enter> to go back" << endl;
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								pass = false;
								break;
							}
							
							/*check if the command exists*/
							check = false;
	    					while (check != true)
							{
								system("cls");
								cout << "-----------------\nDelete a new command\n-----------------\n" << endl;
		
								cout << "Command name, type \"exit\" to quit:\n";
								getline (cin, cmd);
								lrtrim(cmdptr);
								
								if (cmd.compare("") != 0)
								{
									if (cmd.compare("exit") == 0)
									{
										myList.deleteCMDLIST(myList.head);
										myfile.close();
										return 0;
									}
									ptr = myList.searchCMD( myList.head, cmd);
									if( ptr == NULL ) 
									{
										cout << "//Command: " << cmd << " not found" << endl;
										cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									}
									else 
									{
										check = true;
									}
								}
								else
								{
									cout  << "//Should not be empty! Press <Enter> to retype." << endl;
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									system("cls");
								}
							}
							myList.deleteCMD(ptr);
						    myfile.close();
							myfile.open(filename.c_str(), ios::in | ios::out | ios::trunc); 
							myfile.seekg(0, ios::beg); 
							
							myList.printCMDLIST(myList.head, myfile);
							
							myfile.close();
							myfile.open(filename.c_str(), ios::in | ios::out);
							cout << "\nDeleted!...  \n";
							cout << "Press <Enter> to go back" << endl;
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
							pass = false;
							break;
						case 5:
							myList.deleteCMDLIST(myList.head);
							myfile.close();
							return 0;
							break;
						default:
							pass = false;
					}
				} 
			}
		}
		myfile.close();
	}
	else if (argc > 2)
	{
		MessageBox( NULL, "Only accept single parameter." , NULL, MB_OK | MB_ICONERROR);
		return 1;
	}
	return 0;
}

void spacestr(string *&s, int x) 
{
    if (x == 1)
    {
        replace( s->begin(), s->end(), ' ', '+');
    }
    else
    {
        replace( s->begin(), s->end(), '+', ' '); 
    }
}


bool isnumstr(string s)
{
	char *cstr = new char [s.length()+1];
	strcpy (cstr, s.c_str());
	while(*cstr)
	{
		if(!isdigit(*cstr))
		{
			return false;
		}
		cstr++;
	}
	return true;
}

void lrtrim(string *&s) 
{
    s->erase(find_if(s->rbegin(), s->rend(), not1(ptr_fun<int, int>(isspace))).base(), s->end());
    s->erase(s->begin(), find_if(s->begin(), s->end(), not1(ptr_fun<int, int>(isspace))));
}
