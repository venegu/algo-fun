/****************************************************
implementation file for our binary search tree.
*****************************************************/
/* Lisa Maldonado */
#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdio>

using std::cin;
using std::cout;
using std::endl;
using std::setw;

#include "searchTree.h"

namespace csc212
{

	struct treeNode {
		treeNode(val_type d=0, treeNode* l=0, treeNode* r=0);

		val_type data; /* the data of the node */
		treeNode* left; /* pointer to the left subtree */
		treeNode* right; /* pointer to the right subtree */

		/* please ignore this -- used for printing the tree */
		void getLevel(val_type* A, size_t l, size_t h=0, size_t id=0);
	};

	/* function pointers... */
	typedef void (*nodeProcessingFn)(treeNode*&,void*);
	/* this says that things of type "nodeProcessingFn" are actually functions
	 * which take a treeNode pointer by reference along with another pointer
	 * (for parameters) and doesn't return a value.
	 * */

	/* example: for basic, space-separated printing you could use this: */
	void coutData(treeNode*& n, void*)
	{
		cout << n->data << " ";
	}
	/* a more general function to output data from a node to a stream: */
	void outputData(treeNode*& n, void* pOStream)
	{
		/* NOTE: pOStream is a pointer to the desired output stream */
		std::ostream* o;
		if(pOStream) //if an explicit output stream is supplied, use it:
			o = reinterpret_cast<std::ostream*>(pOStream);
		else //default to using cout
			o = &cout;
		(*o) << n->data << " ";
	}
	/* for smily-face delimited printing: */
	void coutData2(treeNode*& n, void*) { cout << n->data << ": )"; }

	/* for writing a dot file: */
	void printDot(treeNode*& n, void* pFILE)
	{
		/* NOTE: the void* param is assumed to be a file stream which
		 * is opened for writing.  Also, you need to do this post order. */
		if (n==0) return;
		FILE* f = (FILE*)(pFILE);
		fprintf(f, "  \"%p\" [label=%li]\n", n,n->data);
		if (!(n->left||n->right)) return;
		/* nodes with a single child may be rendered directly below, so
		 * print invisible nodes to space it out: */
		if (!n->left) {
			fprintf(f, "  \"%s%p\" [label=\"\",width=.1,style=invis]","l",n);
			fprintf(f, "  \"%p\" -> \"%s%p\" [style=invis]\n",n,"l",n);
		} else {
			fprintf(f, "  \"%p\" -> \"%p\" [style=dashed]\n",n,n->left);
		}
		if (!n->right) {
			fprintf(f, "  \"%s%p\" [label=\"\",width=.1,style=invis]","r",n);
			fprintf(f, "  \"%p\" -> \"%s%p\" [style=invis]\n",n,"r",n);
		} else {
			fprintf(f, "  \"%p\" -> \"%p\"\n",n,n->right);
		}
	}

	/* forward declarations for subtree functions: */

	/* this makes a copy of the subtree and returns a pointer to the root
	 * (the root of the copy, of course) */
	treeNode* copyST(treeNode* original);

	/* returns whether or not x is in the subtree with root == stroot */
	bool searchST(treeNode* stroot, val_type x);

	
	/* insert and remove for a subtree */
	/* NOTE: the pointers for these two are by reference */

	/* attempts to insert x into the subtree, returning whether or not
	 * insertion took place */
	bool insertST(treeNode*& stroot, val_type x);
	/* attempts to remove x from the subtree */
	void removeST(treeNode*& stroot, val_type x);

	/* clears a subtree. */
	void clearST(treeNode*& stroot);

	/* min and max for a subtree */
	val_type maxST(treeNode* stroot);
	val_type minST(treeNode* stroot);

	/* subtree traversal functions */
	/* NOTE: pParams will point to the parameters for f (if there are any) */
	void preOrderST(treeNode*& stroot, nodeProcessingFn f, void* pParams);
	void inOrderST(treeNode*& stroot, nodeProcessingFn f, void* pParams);
	void postOrderST(treeNode*& stroot, nodeProcessingFn f, void* pParams);

	/* tells if this node is a leaf. */
	bool isLeaf(treeNode* tn);

	/* tree statistics */
	/* counts and returns the number of leaves in the subtree */
	unsigned long numLeavesST(treeNode* stroot);
	/* returns the total size of the subtree (i.e., the number of elements) */
	unsigned long sizeST(treeNode* stroot);
	/* gives the height of this subtree */
	unsigned long heightST(treeNode* stroot);

	bool isLeaf(treeNode* tn) { return (tn->left == 0 && tn->right == 0); }
	
	/* this makes a copy of the subtree and returns a pointer to the root
	 * (the root of the copy, of course) */
	treeNode* copyST(treeNode* original)
	{
		/* TODO: write this */

		if(original){
			treeNode* seed = new treeNode(original->data, copyST(original->left), copyST(original->right));
			return seed; 
		}
		else(!original) return 0;
	}

	/* construction / destruction */
	Tree::Tree() { root = 0; }
	Tree::Tree(const Tree& T) { this->root = copyST(T.root); }
	Tree::Tree(val_type* A, unsigned long size)
	{
		this->root = 0;
		//just sequentially insert items...
		for(unsigned long i=0; i<size; i++)
			this->insert(A[i]);
	}
	treeNode::treeNode(val_type d, treeNode* l, treeNode* r)
		: data(d), left(l), right(r) {}
	Tree::~Tree() { clear(); }

	void Tree::operator=(const Tree& T)
	{
		/* TODO: write this */
	}

	bool Tree::isEmpty() { return (root==0); }

	bool searchST(treeNode* stroot, val_type x)
	{
		/* TODO: write this */
		return true;
	}

	bool Tree::search(val_type x)
	{
		return searchST(this->root,x);
	}

	/* insert x into subtree. returns !search(x) (i.e., whether or not an
	 * insert took place) */
	bool insertST(treeNode*& stroot, val_type x)
	{
		if(stroot == 0)
		{
			stroot = new treeNode(x);
			return true;
		}
		if(x < stroot->data)
			return insertST(stroot->left,x);
		else if(stroot->data < x)
			return insertST(stroot->right,x);
		return false; //x was already in the tree
	}
	bool Tree::insert(val_type x) { return insertST(this->root,x); }

	val_type maxST(treeNode* stroot) //returns max value in subtree
	{
		/* TODO: write this */
		return 0;
	}
	val_type Tree::max() { return maxST(this->root); }

	val_type minST(treeNode* stroot) //returns min value in subtree
	{
		/* TODO: write this */
		return 0;
	}
	val_type Tree::min() { return minST(this->root); }

	void removeST(treeNode*& stroot, val_type x)
	{
		/* TODO: write this */
	}
	void Tree::remove(csc212::val_type x)
	{
		removeST(this->root,x);
	}

	void clearST(treeNode*& stroot) //erases subtree
	{
		/* TODO: write this */
	}
	void Tree::clear()
	{
		clearST(this->root);
	}

	/* traversals */
	void preOrderST(treeNode*& stroot, nodeProcessingFn f, void* pParams)
	{
		//I'll do one for you to help you get the idea.
		if(stroot==0) return;
		f(stroot,pParams); //apply some process (f) to the root.
		preOrderST(stroot->left,f,pParams); //then process the left subtree
		preOrderST(stroot->right,f,pParams);//and then the right subtree
	}
	void inOrderST(treeNode*& stroot, nodeProcessingFn f, void* pParams)
	{
		/* TODO: write this */
	}
	void postOrderST(treeNode*& stroot, nodeProcessingFn f, void* pParams)
	{
		/* TODO: write this */
	}

	void Tree::preOrder(ostream* o)
	{
		preOrderST(this->root,&outputData,(void*)(o));
	}
	void Tree::inOrder(ostream* o)
	{
		inOrderST(this->root,&outputData,(void*)(o));
	}
	void Tree::postOrder(ostream* o)
	{
		postOrderST(this->root,&outputData,(void*)(o));
	}

	unsigned long numLeavesST(treeNode* stroot) //returns number of leaves in the subtree.
	{
		/* TODO: write this */
		return 0;
	}
	unsigned long Tree::numLeaves()
	{
		return numLeavesST(this->root);
	}

	/* return size of subtree */
	unsigned long sizeST(treeNode* stroot)
	{
		/* TODO: write this */
		return 0;
	}
	unsigned long Tree::size()
	{
		return sizeST(this->root);
	}

	unsigned long heightST(treeNode* stroot) //gives the height of this subtree
	{
		if(stroot == 0) return 0;
		if(isLeaf(stroot)) //a single node has height 0
			return 0;

		unsigned long hl = 0, hr = 0; //left and right subtree heights
		hl = heightST(stroot->left);
		hr = heightST(stroot->right);
		if(hl < hr)
			return 1+hr;
		return 1+hl;
	}
	unsigned long Tree::height() { return heightST(this->root); }

	void Tree::drawDot(const char* fname)
	{
		FILE* fdot = fopen(fname,"wb");
		fprintf(fdot, "digraph bstree {\n");
		fprintf(fdot, "  graph [ordering=\"out\"];\n");
		fprintf(fdot, "  bgcolor=black\n  edge [color=white]\n");
		fprintf(fdot, "  node [style=filled color=white fillcolor=dodgerblue4 shape=circle]\n");
		postOrderST(this->root,&printDot,fdot);
		fprintf(fdot, "}\n");
		fclose(fdot);
	}
	void treeNode::getLevel(val_type* A, size_t l, size_t h, size_t id)
	{
		if(l==h)
		{
			A[id] = data;
			return;
		}
		h++;
		if(left)
			left->getLevel(A,l,h,2*id);
		if(right)
			right->getLevel(A,l,h,2*id+1);
	}
	void printSpace(int n)
	{
		for(int i=0; i<n; i++)
			cout << ' ';
	}
	void Tree::drawTree()
	{
		if(this->isEmpty()) return;
		unsigned long h = height() + 1;
		val_type m = max();
		unsigned long len = 1;
		unsigned long n = (unsigned long)pow((double)2,(int)h-1);
		/* (this is number of nodes in bottom row.) */
		while((m = m/10)) //set len = to log of the max
			len++;
		val_type* A = new val_type[n];
		unsigned long i;
		cout << endl << endl;
		for(i=0; i<h; i++)
		{
			for(unsigned long k=0; k<pow((double)2,(int)i); k++)
				A[k] = -1;
			root->getLevel(A,i);
			for(unsigned long j=0; j<pow((double)2,(int)i); j++)
			{
				printSpace((int)(n/(pow((double)2,(int)i)))*len);
				if(i>0 && j%2) 
					printSpace(2*(h+len-i-3)+1);
				if(A[j]>=0)
					cout << setw(len) << A[j];
				else
					printSpace(len);
			}
			cout << endl << endl;
		}
		cout << endl << endl;

		delete [] A;
	}
	ostream& operator<<(ostream& o, Tree& T)
	{
		preOrderST(T.root,&outputData,(void*)(&o));
		return o;
	}
}
