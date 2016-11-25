#include "Pinball.h"
#include <iostream>
using namespace std;


/*
 * This is the default constructor for the Pinball class. The parameter n is the
 * size of the hash table. If no size is given, use 1019 which is a prime number.
 * You must allocate space for the H array and initialize it (and also for other
 * data members that you create).
 */
Pinball::Pinball(int n) {

}

/*
 * This is the destructor. Make sure you deallocate all memory for this object.
 * Strings in the H array must be deallocated using free() since they are C
 * strings (i.e., don't use delete).
 */
Pinball::~Pinball() {

}

/*
 * This function inserts a copy of the C string str into the hash table. It has
 * no return value. (Note: use strdup() to copy C strings.) If the hash table is
 * full or the maximum number of ejections was exceeded, then insert() should
 * throw a PinballHashFull exception. (This exception is already defined in
 * Pinball.h.)
 *
 * Calling insert() with a string that is already in the hash table should have
 * no effect. (I.e., do not insert a second copy of the same value.)
 */
void Pinball::insert(const char *str) {

}

/*
 * The find() function looks for str in the hash table. If found, the index of
 * str is returned. If str is not in the hash table, find() should return -1.
 *
 * The location returned by find() is only valid until the next call to insert()
 * or to remove().
 */
int Pinball::find(const char *str) {

}

/*
 * The at() function returns a pointer to the string stored at the index slot of
 * the hash table. If the index is invalid (i.e., less than 0 or greater than or
 * equal to m_capacity), then at() should throw an out_of_range error
 * (already defined in stdexcept).
 *
 * The pointer returned has type const char * to prevent the string stored in
 * the hash table from being changed. The calling function can make a copy if
 * desired.
 */
const char* Pinball::at(int index) {

}

/*
 * The remove() function removes str from the hash table and returns the pointer.
 * If str is not in the hash table, remove() returns NULL.
 *
 * It is the responsibility of the code that calls remove() to deallocate the
 * string that is returned. (Again, use free(), not delete to deallocate.)
 */
char* Pinball::remove(const char *str) {

}

/*
 * Print out some statistics about the hash table. (See sample output.) This
 * requires cooperation from insert() and remove() and additional data members
 * in the class. 
 * (See additional clarifications in project description)
 */
void Pinball::printStats() {

}
