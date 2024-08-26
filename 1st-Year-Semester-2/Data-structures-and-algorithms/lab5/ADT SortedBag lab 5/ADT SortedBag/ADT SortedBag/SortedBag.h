#pragma once
#include <vector>
//DO NOT INCLUDE SORTEDBAGITERATOR

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;

class SortedBag {
	friend class SortedBagIterator;

private:
	struct BSTNode{
		TComp info;
		BSTNode* left;
		BSTNode* right;
	};

	Relation relation;
	BSTNode* root;
	int nrElems;

	BSTNode* initNode(TComp e);
	BSTNode* insertNode(BSTNode* node, TComp e);
	BSTNode* removeNode(BSTNode* node, TComp e);
	BSTNode* maximumNode(BSTNode* node);
	bool searchNode(BSTNode* node, TComp e) const;
	int nrOccurrencesNode(BSTNode* node, TComp e) const;
	void destroy(BSTNode* node);

public:
	//constructor
	SortedBag(Relation r);

	//adds an element to the sorted bag
	void add(TComp e);

	//removes one occurence of an element from a sorted bag
	//returns true if an eleent was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appearch is the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;

	//adds nr occurences of elem into the SortedBag (if elem was
	//not in the bag, it will be added)
	//throws an exception if nr is negative
	void addOccurences(int nr, TComp elem);

	//destructor
	~SortedBag();
};