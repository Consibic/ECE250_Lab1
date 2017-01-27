/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  b9cheng @ uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Winter 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    z464zhan
 *****************************************/

#ifndef DYNAMIC_STACK_AS_ARRAY_H
#define DYNAMIC_STACK_AS_ARRAY_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "Exception.h"
using namespace std;

class Dynamic_range_stack
{
private:
    int entry_count;
    int max_count;
    int min_count;
    int initial_capacity;
    int current_capacity;

    int *stack_array;
    int *maximum_array;
    int *minimum_array;

    // You may wish to include a number of helper functions
    // in order to abstract out some operations


public:
    Dynamic_range_stack( int = 10 );
    Dynamic_range_stack( Dynamic_range_stack const & );
    ~Dynamic_range_stack();

    int top() const;
    int size() const;
    bool empty() const;
    int capacity() const;

    int maximum() const;
    int minimum() const;

    void push( int const & );
    int pop();
    void clear();
    // Friends

    friend std::ostream &operator<<( std::ostream &, Dynamic_range_stack const & );
};

Dynamic_range_stack::Dynamic_range_stack( int n ):
    entry_count( 0 ),
    min_count( 0 ),
    max_count( 0 ),
    initial_capacity( std::max( 1, n ) ),
    current_capacity( initial_capacity ),
    stack_array( new int[current_capacity] ),
    maximum_array( new int[current_capacity] ),
    minimum_array( new int[current_capacity] )
{
    // empty constructor
}

Dynamic_range_stack::~Dynamic_range_stack()
{
    clear();
    delete [] stack_array;
    delete [] maximum_array;
    delete [] minimum_array;
}

int Dynamic_range_stack::top() const
{
    if (entry_count < 1)
    {
        underflow ex;
        throw ex;
    }
    return stack_array[entry_count - 1];
}

int Dynamic_range_stack::maximum() const
{
    if (max_count < 1)
    {
        underflow ex;
        throw ex;
    }
    return maximum_array[max_count - 1];
}

int Dynamic_range_stack::minimum() const
{
    if (min_count < 1)
    {
        underflow ex;
        throw ex;
    }
    return minimum_array[min_count - 1];
}

int Dynamic_range_stack::size() const
{
    return entry_count;
}

bool Dynamic_range_stack::empty() const
{
    if(entry_count == 0)
        return true;
    else return false;
}

int Dynamic_range_stack::capacity() const
{
    return current_capacity;
}

void Dynamic_range_stack::push( int const &obj )
{
    if(entry_count >= current_capacity)
    {
        current_capacity *= 2;
        int *temp_array_stack = new int[current_capacity];
        int *temp_array_max = new int[current_capacity];
        int *temp_array_min = new int[current_capacity];
        copy(stack_array, stack_array + entry_count, temp_array_stack);
        copy(maximum_array, maximum_array + max_count, temp_array_max);
        copy(minimum_array, minimum_array + min_count, temp_array_min);
        delete [] stack_array;
        delete [] maximum_array;
        delete [] minimum_array;
        stack_array = new int[current_capacity];
        maximum_array = new int[current_capacity];
        minimum_array = new int[current_capacity];
        copy(temp_array_stack, temp_array_stack + entry_count, stack_array);
        copy(temp_array_max, temp_array_max + max_count, maximum_array);
        copy(temp_array_min, temp_array_min + min_count, minimum_array);
        delete [] temp_array_stack;
        delete [] temp_array_max;
        delete [] temp_array_min;
    }
    stack_array[entry_count] = obj;
    entry_count += 1;
    if(entry_count == 1){
        maximum_array[max_count] = obj;
        max_count += 1;
        minimum_array[min_count] = obj;
        min_count += 1;
    }else{
        if(obj >= maximum()){
            maximum_array[max_count] = obj;
            max_count += 1;
        }
        if(obj <= minimum()){
            minimum_array[min_count] = obj;
            min_count += 1;
        }
    }
    return;
}

int Dynamic_range_stack::pop()
{
    if(entry_count <= 0){
        underflow ex;
        throw ex;
    }
    int entry = stack_array[entry_count-1];
    entry_count -= 1;
    if(entry == maximum_array[max_count-1]){
        max_count -= 1;
    }
	if(entry == minimum_array[min_count-1]){
		min_count -= 1;
	}
    return entry;
}

void Dynamic_range_stack::clear()
{
    max_count = 0;
    min_count = 0;
    entry_count = 0;
    delete [] stack_array;
    delete [] maximum_array;
    delete [] minimum_array;
    stack_array = new int[initial_capacity];
    maximum_array = new int[initial_capacity];
    minimum_array = new int[initial_capacity];
    current_capacity = initial_capacity;
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Dynamic_range_stack const &stack )
{
    // Print out your stacks

    return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
