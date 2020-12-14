#ifndef CMD_H
#define CMD_H

using namespace std;

class list
{
	public:
		struct node {
			string cmd;
			string path;
			string paratr;
			struct node *next;
		} *head, *tail, *ptr;	
	
		list():head(NULL),tail(NULL){}	// constructor	
		~list();			// destructor
	
		struct list::node* initNode(string, string, string);
		struct list::node* searchCMD(struct list::node*, string);
		
		bool isemptyCMDLIST(struct list::node*);
		void addCMD( struct list::node*);
		void deleteCMD( struct list::node*);
		void deleteCMDLIST( struct list::node*);
		void displayCMD( struct list::node*) const;
	 	void displayCMDLIST( struct list::node*) const;	
	 	void printCMDLIST( struct list::node*, fstream&) const;	
};

#endif


