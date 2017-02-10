#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  r66xu
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"
#include <iostream>
enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
	// enter your implemetation here 
	delete [] array;
	delete [] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
    // enter your implemetation here 
	return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
    // enter your implemetation here 
	return array_size;
}



template<typename T >
bool DoubleHashTable<T >::empty() const {
    // enter your implemetation here
	if (count==0){
		return true;
	}
	else{
		return false;

	}
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
	// enter your implemetation here 
	int hone = static_cast<int>(obj);
	hone = hone%array_size;
	if (hone < 0) {
		hone = hone + array_size;
	}
	return hone;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
	// enter your implemetation here 
	int htwo = static_cast<int>(obj);
	htwo = (htwo / array_size)%array_size;
	if (htwo < 0) {
		htwo = htwo + array_size;
	}
	if (htwo % 2 == 0) {
		htwo++;
	}
	return htwo;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
	// enter your implemetation here 

	for (int i = 0; i <= array_size; i++) {
		if (array_state[i] == OCCUPIED && array[i] == obj) {
			return true;
		}
	}
	

	return false;
}

template<typename T >
T DoubleHashTable<T >::bin(int n) const {
	// enter your implemetation here 	      
	if (array_state[n] == OCCUPIED) {
		return array[n];
	}
	else {
		return 0;
	}
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
	 // enter your implemetation here 	
	int position = h1(obj);
	int htwoposition;
	if (count >= array_size) {
		overflow exception;
		throw exception;
		return;
	}
	htwoposition = position;
	while (array_state[htwoposition] == OCCUPIED) {
		position = position+h2(obj);
		htwoposition = position % array_size;
		if (htwoposition < 0) {
			htwoposition = htwoposition + array_size;
		}
		
	}

	array[htwoposition] = obj;
	array_state[htwoposition] = OCCUPIED;
	count++;

	return ; 

}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	 // enter your implemetation here 	
	
	
	for (int i = 0; i <= array_size; i++) {
		if (array_state[i] == OCCUPIED && array[i] == obj) {
			array_state[i] = DELETED;
			count--;
			return true;
		}
	}

	return false;
}

template<typename T >
void DoubleHashTable<T >::clear() {
	 //enter your implemetation here 	
	delete[] array;
	array = new T[array_size];
	delete[] array_state;
	array_state = new state[array_size];
	count = 0;//
	/*for (int i = 0; i <= array_size; i++) {
		if (array_state[i] == OCCUPIED) {
			array_state[i] = DELETED;
		}
	}
	count = 0;
	return ; */
}

template<typename T >
void DoubleHashTable<T >::print() const {
      // enter your implemetation here 	
	for (int i = 0; i < array_size; i++) {
	std::cout << i << ":" << array[i]<< std::endl;
	}
	return;
}

#endif
