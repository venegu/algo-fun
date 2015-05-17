/****************************************************
implementation file for the hash table class.
*****************************************************/

/* Lisa Maldonado */

#include "hashtbl.h"
#include <iostream>
using std::endl;
using std::ostream;
#include <string.h> /* for strcpy */
#include <algorithm> /* for find */
using std::find;
#include <iomanip>
using std::setfill;
using std::setw;
#include <cassert>

#define R32 (rand()*100003 + rand())
#define R64 (((uint64_t)R32 << 32) + R32)
#define TLEN ((size_t)(1 << this->nBits))

namespace csc212
{
	/* First we implement our hash family */
	hashTbl::hash::hash(unsigned rangebits, const uint32_t* a,
					const uint64_t* alpha, const uint64_t* beta) {
		this->rangebits = rangebits;
		if (a) {
			for (size_t i = 0; i < aLen; i++) {
				this->a[i] = a[i] | 1; /* make sure it is odd. */
			}
		} else {
			for (size_t i = 0; i < aLen; i++) {
				this->a[i] = R32 | 1;
			}
		}
		this->alpha = ((alpha) ? *alpha : R64) | 1;
		this->beta = ((beta) ? *beta : R64);
		/* only keep the low order bits of beta: */
		this->beta &= ((uint64_t)-1)>>(64 - rangebits);
	}
	uint64_t hashTbl::hash::operator()(const string& x) const {
		assert(x.length() <= 4*aLen);
		/* TODO: write the hash function. */
		string t = x; 
		if(x.length()%8 !=0){
			for(size_t i = 0; i<(8-(x.length()%8)); i++) t.push_back('\0'); /* correcting */
		}

		const uint32_t* H = reinterpret_cast<const uint32_t*>(t.c_str()); 
		uint64_t q = 0;
		uint64_t w = 0; 
		/* conversions happening here - this is slightly ugly and painful */
		for(size_t i= 0; i<t.length()/8; i++) q+=(uint64_t)(H[2*i]+this->a[2*i])*(H[2*i+1]+this->a[2*i+1]); 
		return w=((q*(this->alpha)+this->beta)>>((uint64_t)(64-(this->rangebits)))); 
	}

	//constructors:
	hashTbl::hashTbl(unsigned nBits, const uint32_t* ha,
					const uint64_t* halpha, const uint64_t* hbeta) :
		nBits(nBits),h(nBits,ha,halpha,hbeta)
	{
		this->table = new list<val_type>[TLEN];
	}
	hashTbl::hashTbl(const hashTbl& H)
	{
		/* TODO: write this */
		
		/* NOTE: the underlying linked list class has a working
		 * assignment operator! */
		this->nBits = H.nBits;
		this->h=H.h;
		/* wai dis ^ -.- */
        this->table = new list<val_type>[TLEN];
        for(size_t i = 0 ; i < TLEN ; i++)
             this->table[i] = H.table[i];
	}

	//destructor:
	hashTbl::~hashTbl()
	{
		delete[] this->table;
		//NOTE: this will call the destructor of each of the linked lists,
		//so there isn't anything else that we need to worry about.
	}

	//operators:
	hashTbl& hashTbl::operator=(const hashTbl& H)
	{
		/* TODO: write this */
		if(this==&H) return *this;
		clear();
		this->nBits=H.nBits; 
		this->h=H.h; 
		this->table= new list<val_type>[TLEN]; 
		for(size_t i = 0; i<TLEN; i++) this->table[i] = H.table[i];
 		/* what value does this return??? the original? */
		return *this;
	}

	ostream& operator<<(ostream& o, const hashTbl& H)
	{
		for (size_t i = 0; i < H.tableLength(); i++) {
			o << "[" << setfill('0') << setw(2) << i << "] |";
			for (list<val_type>::iterator j = H.table[i].begin();
					j != H.table[i].end(); j++) {
				o << *j << "|";
			}
			o << endl;
		}
		return o;
	}

	void hashTbl::insert(val_type x)
	{
		/* TODO: write this */
		if(!search(x)) this->table[h(x)].push_front(x);
		else return; 
		//Remember to check for uniqueness before inserting.
	}

	void hashTbl::remove(val_type x)
	{
		/* TODO: write this */
		/* what if I used an if else... */
		table[h(x)].remove(x); 	
	}

	void hashTbl::clear()
	{
		for(size_t i=0; i<TLEN; i++)
			this->table[i].clear();
	}

	bool hashTbl::isEmpty() const
	{
		/* look for any non-empty list. */
		for(size_t i=0; i<TLEN; i++)
			if(!this->table[i].empty()) return false;
		return true;
	}

	bool hashTbl::search(val_type x) const
	{
		/* TODO: write this */
		/* how to one line this ... if only it were skippable - could this be recursive? */
		list<val_type>::iterator why; // why will break further down without this initilization
		why = find(table[h(x)].begin(), table[h(x)].end(),x); /* range to look for what and the "what" -> x */
		if(why != table[h(x).end()]) return true;
		else return false; 

		/* Another solution that could possibly work */
		#if 0
		return this->table[h(x,[h(x)].tableLength())].search(x);
		/*what would be acceptable as a reference to the table length
		 * TLEN, this->nBits nor the actual value of TLEN do not work @-@*/
		 //what if search(x); --> would be inefficient unless params change - WHY DID WE USE BOOL???
		 #endif

		/* yet another solution (yas) -- this one actually works */
		#if 0
		/* putting param into hash function */
		int val = h(x); 
		list<val_type>::iterator y = this->table[val].begin(); //this silliness again
		for(table[val].begin(); y!= table[key].end(); ++y){ //one must be added first before proceeding
			if(*y==x) return true; 
		}
		/* if not then it's false */
		else return false; 
		#endif
	}

	size_t hashTbl::countElements() const
	{
		/* TODO: write this */
		size_t count = 0; 
		for(size_t i = 0; i < TLEN; i++){
			for(list<val_type>::iterator why = this->table[i].begin(); why !=this->table[i].end(); why++) count++;
		}		
		return count; //just so it compiles for now...
	}

	size_t hashTbl::tableLength() const
	{
		return TLEN;
	}

	size_t hashTbl::countCollisions() const
	{
		//just count the number of lists of length > 1
		size_t i,nCollisions=0;
		for(i=0; i<TLEN; i++)
			if(table[i].size() > 1)
				++nCollisions;
		return nCollisions;
	}

	size_t hashTbl::longestListLength() const
	{
		/* TODO: write this */
		size_t longest=0; size_t size=0;
		for(size_t i=0; i<TLEN; i++){
			size = table[i].size(); 
			if(size>longest) longest = size; 
		}
		return longest;
		//return 0; //just so it compiles for now...
	}
}
