/* Lisa Maldonado - Sorry for the lateness! */ 
/* huffman encoding. */
#pragma once
#include <stddef.h> /* size_t */
#include <iostream>
using std::ostream;
#include <fstream>
using std::ofstream;
#include <algorithm>
using std::swap;
#include <functional>
using std::less;
#include <map>
using std::map;
#include <vector>
using std::vector;
#include <string>
using std::string;

/* forward declarations: */
template <typename T> struct hNode;
template <typename T>
void nodeToDot(hNode<T>* n, void* pFILE);

/* node for huffman encoding tree */
template <typename T>
struct hNode {
	T symbol;
	size_t weight;
	hNode<T>* left;
	hNode<T>* right;
	hNode() {left = right = 0;}
	typedef void (*nodeProcFn)(hNode<T>*,void*);
	void postOrderST(nodeProcFn f, void* pParams) {
		if(this == 0) return;
		left->postOrderST(f,pParams);
		right->postOrderST(f,pParams);
		f(this,pParams);
	}
	void drawDot(const char* fname) {
		ofstream fdot(fname);
		fdot << "digraph htree {\n" <<
				"  graph [ordering=\"out\"];\n" <<
				"  bgcolor=black\n" <<
				"  edge [color=white fontcolor=white]\n" <<
				"  node [style=filled color=white " <<
				"fillcolor=plum shape=circle]\n";
		this->postOrderST(&nodeToDot,(void*)&fdot);
		fdot << "}\n";
		fdot.close();
	}
};

/* a few utility functions for trees: */
template <typename T>
void nodeToDot(hNode<T>* n, void* pfdot)
{
	/* NOTE: the void* param is assumed to be a file stream which
	 * is opened for writing.  Also, you need to do this post order. */
	if (n==0) return;
	ofstream& fdot = *(ofstream*)(pfdot);
	/* print out leaf nodes with symbol and weight; print internal
	 * nodes with different color, and only weight. */
	if (!n->left && !n->right) {
		fdot << "  \"" << n << "\" [label=\"" << n->symbol <<
			" | " << n->weight <<"\" shape=box fillcolor=palegreen3]\n";
	} else {
		fdot << "  \"" << n << "\" [label=\"" << n->weight <<"\"]\n";
	}
	if (!(n->left||n->right)) return;
	/* for a Huffman tree, should be "full" (each node either
	 * has both children, or is a leaf) */
	if (n->left) {
		fdot << "  \""<<n<<"\" -> \""<<n->left<<"\" [label=0]\n";
	}
	if (n->right) {
		fdot << "  \""<<n<<"\" -> \""<<n->right<<"\" [label=1]\n";
	}
}

template <typename T>
void printLabels(hNode<T>* n, string& label)
{
	if (n==0) return;
	/* leaf node: print the symbol and label;
	 * non-leaf: append 0 for left, 1 for right. */
	if (!n->left && !n->right) {
		cout << "  " << n->symbol << "\t" << label << "\n";
		return;
	}
	label.push_back('0');
	printLabels(n->left,label);
	label.erase(label.size()-1);
	label.push_back('1');
	printLabels(n->right,label);
	label.erase(label.size()-1);
}

/*************** Heap functions ***************/
/* NOTE: most heap operations can be done in-place on an array.
 * Hence, we don't bother making a heap class, but instead just
 * provide a set of functions for arrays. */

/* utility macros for finding left / right and parent, assuming
 * 0-based indexing. */
#define LEFT(x)  ((x<<1)+1)
#define RIGHT(x) ((x+1)<<1)
#define PARENT(x) ((x-1)/2)

/* LOOKHERE */
/* we want to compare pointers to hNodes by their weight: */
template <typename T>
struct hnComp {
	bool operator()(hNode<T>* n1, hNode<T>* n2) {return (n1->weight < n2->weight);}
};

/* L provides a means for comparing elements of type T */ 

/* heapify (downward). assumes that both left and right children of i
 * are max heaps (so that the only possible violation is at i). */
template <typename T, typename L>
void heapify(vector<T>& A, size_t i, L lt = less<T>())
{
	/* TODO: write this */
	/* Right and Left children - make vars for them */
	size_t right=RIGHT(i), size_t left=LEFT(i);

	/* For the least one */
	size_t l; 

	if(right<A.size() && lt(A[right],A[i])) l = right; 
	else if(left<A.size() && lt(A[left],A[i])) l = left; 
	else
		l = i; 

	if(l!=i) swap(A[i], A[l]), heapify(A, l, lt);
	/* sorry, I'm going to be lazy here and pretty much everywhere */
}

/* we also need to heapify "upward" when inserting new elements: */
template <typename T, typename L>
void heapify_up(vector<T>& A, size_t i, L lt = less<T>())
{
	/* TODO: write this */
	size_t parent = PARENT(i); 

	/* This should be recursive for elements up zzzz */
	if(lt(A[i],A[parent])) swap(A[parent],A[i]), heapify_up(A,parent,lt);
}

/* buildHeap.  Takes an un-ordered array and turns it into a heap. */
template <typename T, typename L>
void buildHeap(vector<T>& A, L lt = less<T>())
{
	/* Note that all leaves are heaps on their own.  So, you can work
	 * backwards through the tree calling heapify, starting from the
	 * last node's parent. */
	/* TODO: write this */
	/* given the above note: */
	size_t thing = (A.size())-1; 
	/* decrementing other things yabagabaga */ 
	for(size_t other_thing = thing; other_thing!=0; other_thing--){
		heapify(A,PARENT(other_thing), lt);
		/* now what ... ? */
		if(other_thing%2==0) other_thing--; //:)
	}	 
}

/************* priority queue functions. **************/
/* NOTE: we assume that every array passed to these functions is already a
 * heap!  NOTE: although the operations take only log(n) time, this is not
 * the most efficient priority queue implementation known -- see your book
 * for more advanced techniques which can reduce the *insert* time over a
 * sequence of calls.  Finally, note that the smallest element will always
 * be stored at index 0. */

/* remove and return front item from priority queue. */
template <typename T, typename L>
T pqPop(vector<T>& Q, L lt = less<T>())
{
	/* copy last value to top and reduce size (call pop_back). */
	/* TODO: write this */
	return T(); /* just so it compiles! */
}

/* insert new item into priority queue. */
template <typename T, typename L>
void pqPush(vector<T>& Q, T x, L lt = less<T>())
{
	/* push new item to back; then heapify up. */
	/* TODO: write this */
}

/************* huffman encoding / decoding *************/

/* Take raw data and encode.  Return the root of the tree used
 * for the encoding.  (This would be needed if we ever wanted
 * to decode.)
 * NOTE: this function should allocate memory for nodes (as an array)
 * which the caller is then responsible for cleaning up.  See the
 * readme for more details. */
template <typename T>
hNode<T>* huffmanEncode(T* data, size_t len, hNode<T>*& nodes)
{
	/* TODO: write this */
	/* step 1: make a frequency table. */
	/* step 2: create array of nodes.  Note that 2n will suffice (this
	 * follows from the fact that a Huffman tree will always be full).
	 * step 3: initialize array from frequency table. */

	/* since we don't want the nodes to ever be re-located (which would
	 * invalidate the pointers in the Huffman tree), we build our queue
	 * out of node pointers rather than the nodes themselves. */
	/* step 4: call buildHeap to create a priority queue; then build the
	 * tree by repeatedly "merging" the two nodes at the front of the
	 * queue, and then reinserting the merged node. */
	return 0; /* just so it compiles. */
}