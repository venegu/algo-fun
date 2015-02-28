/****************************************************
implementation file for linked list class.
*****************************************************/

#include "list.h"
#include <stdlib.h> //for rand()

namespace csc212
{
	/* listNode stuff: */
	listNode::listNode()
	{
		this->next = 0; //set the next pointer to be null
	}

	listNode::listNode(val_type x, listNode *pNext)
	{
		this->data = x;
		this->next = pNext;
	}


	/* linked list implementation: */
	list::list()
	{
		this->root = 0; //initialize the list to be empty
		//remember 0 == NULL, which is never memory you own.
	}

	list::list(const list &L)
	{
		//we need to make *this a copy of L
		listNode* pL, *p; //pL will traverse L, p will traverse *this
		pL = L.root;
		root = 0; //start out with the empty list
		if(L.root != 0)
		{
			this->root = new listNode(pL->data);
			pL = pL->next;
		}
		p = this->root;
		//loop invariant:

		/*pL is a pointer to the next node to be copied in L
		p is a pointer to the last node created in (*this)
		in english: pL goes through L and is is one step ahead of p,
		which is going through (*this)
		our loop should add a new node to *this, and then maintain the invariant*/

		while(pL != 0) //pL != NULL
		{
			p->next = new listNode(pL->data);
			p = p->next;
			pL = pL->next;
		}
	}

	list::~list()
	{
		this->clear(); //delete all nodes, deallocating memory
	}

	list& list::operator=(const list& L)
	{
		//idea: erase our contents, then copy L, similar to the copy constructor.
		//but first, check for self-assignment:
		if(this == &L) return *this;

		clear();
		listNode* pL, *p;
		pL = L.root;
		if(pL)
		{
			root = new listNode(pL->data);
			pL = pL->next;
		}
		p = root;
		while(pL)
		{
			p->next = new listNode(pL->data);
			p = p->next;
			pL = pL->next;
		}
		return *this;
	}

	bool operator==(const list& L1, const list& L2)
	{
		/* TODO: write this. */
		listNode *p1=L1.root; 
		listNode *p2=L2.root; 

		if(L1.length() !=L2.length()) return false; 

		while(p1 && p1->data==p2->data){
			p1=p1->next; 
			p2=p2->next; 
		} 

		if(p1) return false;  //just so it compiles.  you of course need to do something different.
		else return true;
	}
	bool operator !=(const list& L1, const list& L2)
	{
		return !(L1==L2);
	}

	void list::insert(val_type x)
	{
		/* TODO: write this. */
		listNode **p=&(this->root); /* to take care of root case :D */
		while(*p&&(x>(*p)->data)) p=&((*p)->next);
		*p=new listNode(x,*p); 
	}

	void list::remove(val_type x)
	{
		/* TODO: write this. */
		listNode **p=&(this->root); /* to take care of root case */
		while(*p){
			if((*p)->data==x){
				listNode *t=(*p)->next; 
				delete *p;
				*p=t; 
				return; 
			}
			p=&((*p)->next); /* Stops while loop *p is no longer true and increments p */
		}  
	} /* magical double pointer */

	bool list::isEmpty()
	{
		return (this->root == 0);
	}

	void list::clear()
	{
		//idea: repeatedly delete the root node...
		listNode* p;
		while((p = root)) //yes, I do mean "=", not "=="
		{
			root = p->next;
			delete p;
		}
	}

	ostream& operator<<(ostream& o, const list& L)
	{
		listNode* p;
		p = L.root;
		while(p)
		{
			o << p->data << " ";
			p = p->next;
		}
		return o;
	}

	bool list::search(val_type x) const
	{
		listNode* p;
		p = root;
		while(p && p->data != x) //again, short circuit evaluation is important...
			p = p->next;
		if(p) 
			return true;
		else 
			return false;
	}
	/* we are looking for the node we want to manipulate, thus it is linear */

	unsigned long list::length() const
	{
		/* TODO: write this. */
		listNode *p; 
		p=this->root; 
		unsigned long n=0; 

		while(p){
			p=p->next;
			++n; 
		}
		return n; //just so it compiles.  you of course need to do something different.
	}

	void list::merge(const list& L1, const list& L2)
	{
		/* TODO: write this. */
		#if 0	
		/* attempt 1 */	
		/* O(2n) ... almost working... :"3 */
		listNode *p1 = L1.root; 
		listNode *p2 = L2.root; 
		root = NULL; 
		listNode **p3 =&(this->root);

		if(p1->data>p2->data){
			root=new listNode(p2->data);
			p3=root;
			p2=p2->next;
		}
		
		else{
			root=new listNode(p1->data);
			p3=root;
			p1=p1->next;
		} 
	
		while(p1 && p2){ 
			if (p1->data==p2->data){ 
				/* To account for root case */ 
				if(!root){ /* if not null then set root to the stuff if thats the same in L1 & L2 */
					root=new listNode(p1->data); 
					p3=root; /* root into p3 */ 
				} 
				else{ /* if null then setting  */ 
					p3->next=new listNode(p1->data);
					p3=p3->next;
				} 
				p3->next=new listNode(p1->data);
				p3->next=new listNode(p2->data);
				p2=p2->next; 
				p1=p1->next; 
				p3=p3->next; 

			}
			else if(p1->data > p2->data){

				p3->next=new listNode(p2->data); 
				p2=p2->next; 
				p3=p3->next; 
			}
			else{ 
				p3->next=new listNode(p1->data);
				p1=p1->next;
				p3=p3->next; 
			} 
		}
		return; 
		#endif

		#if 0
		/* attempt 2 */
		/* pointer abilities regained */
		listNode *p1=L1.root; 
		listNode *p2=L2.root; 
		listNode **p3=&(this->root);

		while(p2){ /* arrrrrrgggggggggg !!!!! >.><.< SEGMENTATIONFAULTSCANGOTOHELL */ 
			if (p1->data==p2->data){ 
				*p3=new listNode(p1->data);
				p3=&((*p3)->next);
				*p3=new listNode(p2->data);
				p3=&((*p3)->next);
				p2=p2->next; 
				p1=p1->next;
			}
			else if(p1->data > p2->data){

				*p3=new listNode(p2->data); 
				p2=p2->next; 
				p3=&((*p3)->next); 
			}
			else{ 
				*p3=new listNode(p1->data);
				p1=p1->next;
				p3=&((*p3)->next); 
			} 
		}
		#endif

		/* O(6n) */  
		listNode *p1=L1.root;
		listNode *p2=L2.root;
		listNode **p3=&(this->root);

		while(p1 && p2){
			if(p1->data>p2->data){
				*p3=new listNode(p2->data);
				p3=&((*p3)->next);
				p2=p2->next;
			}
			else if (p1->data==p2->data){ 
				*p3=new listNode(p1->data);
				p3=&((*p3)->next);
				*p3=new listNode(p2->data);
				p3=&((*p3)->next);
				p2=p2->next; 
				p1=p1->next;
			}
			else{
				*p3=new listNode(p1->data);
				p3=&((*p3)->next);
				p1=p1->next;
			}
		}
		
		if(p1==0){
			while(p2){
				*p3=new listNode(p2->data);
				p3=&((*p3)->next);
				p2=p2->next;
			}
			return;
		}	
		else{
			while(p1){ 
				*p3=new listNode(p1->data);
				p3=&((*p3)->next);
				p1=p1->next;
			}
			return;	
		}

		//this algorithm should run in LINEAR TIME and set *this
		//to be the union of L1 and L2, and furthermore the list should remain sorted.

		/* While this function has several loops in it none are nested, thus it asymptotically grows O(3m+3n) [with m = size of list 1 and 
		 * n = size of list 2]. */ 
	}

	void list::randomFill(unsigned long n, unsigned long k)
	{
		//we want to fill the list with n random integers from 0..k-1
		this->clear(); //reset to the empty list
		unsigned long i;
		for(i=0; i<n; i++)
		{
			this->insert((val_type)(rand()%k));
		}
	}

	void list::intersection(const list &L1, const list& L2)
	{
		/* TODO: write this. */
		/* O(2n) */ 	
		listNode *p1=L1.root; 
		listNode *p2=L2.root;   
		listNode **p3=&(this->root); /* yay :3 for double pointers taking care of root case */

		while(p1 && p2){ 
			if (p1->data==p2->data){
				*p3=new listNode(p1->data);
				p3=&((*p3)->next);
				p2=p2->next; 
				p1=p1->next; 
			}
			else if(p1->data > p2->data) p2=p2->next;
			else p1=p1->next;  
		}
		return; 
		//this algorithm should run in LINEAR TIME, setting *this
		//to be the intersection (ordered) of L1 and L2.

		/* This algorithm asymptotically grows O(2n) [O(m+n) with m = size of list 1 and n = size of list 2] because there is a single while loop
		 * and no nested functions and/or loops. */
	}
}
