#include "Pinball.h"
#include <iostream>
#include <assert.h>
#include <string.h>
using namespace std;


/*
 * This is the default constructor for the Pinball class. The parameter n is the
 * size of the hash table. If no size is given, use 1019 which is a prime number.
 * You must allocate space for the H array and initialize it (and also for other
 * data members that you create).
 */
Pinball::Pinball(int n) {
    H = new char*[n](); // the hash table, the () sets all indices to NULL
    m_size = 0; // number of items stored in H
    m_capacity = n; // number of slots in H

    m_degree = 5; // my assigned value
    m_ejectLimit = 20; // my assigned value
    numEjections = 0;
    assert(m_degree <= m_capacity); // must be possible to have all unique offsets

    // create m_offsets (unique values)
    m_offset = new unsigned int[m_degree]; // one offset per slot
    m_offset[0] = 0; // represents the primary slot

    for (int i=1; i<m_degree; i++) { // iterate through rest of m_offset
        bool unique = false;

        while (!unique) {
            m_offset[i] = rand() % m_capacity; // create an offset value
            // compare against all prior offsets to make sure its unique
            for (int k=0; k<i; k++) {
                if (m_offset[i] == m_offset[k]) // if not unique
                    break;
                if (k == i-1) // its unique
                    unique = true;
            }
        }
    }

    for (int i=0; i<4; i++)
        cout << "offset " << i << " -> " << m_offset[i] << endl;
}

/*
 * This is the destructor. Make sure you deallocate all memory for this object.
 * Strings in the H array must be deallocated using free() since they are C
 * strings (i.e., don't use delete).
 */
Pinball::~Pinball() {
    cout << "\n---destructing---" << endl;
    delete [] m_offset;
    for (int i=0; i<m_capacity; i++) {
        if (H[i] != NULL) {
            cout << i << ":\t" << H[i] << endl;
        }
        free(H[i]); // deallocate memory that was initialized with malloc() by strdup()
    }
    delete [] H;
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
    char* value = strdup(str); // copy of str (uses malloc() internally)
    unsigned int primarySlot = hashCode(str) % m_capacity;

    // look for an open slot (starting with the primarySlot)
    for (int i=0; i<m_degree; i++) { // loop through all the offsets
        int slot = (primarySlot + m_offset[i]) % m_capacity;
        if (H[slot] == NULL) { // if this slot is free
            H[slot] = value; // insert into this slot
            numEjections = 0; // reset the number of ejections
            m_size++;

            if (i == 0)
                cout << " inserted " << str << "\tinto primarySlot\t" << primarySlot << endl;
            else
                cout << " inserted " << str << "\tinto open aux\t" << slot << endl;
            return;
        }
    }

    // all slots are full so randomly chose one auxillary slot
    int index = 1 + rand() % (m_degree-1); // random num between 1 and (m_degree-1)
    int auxSlot = (primarySlot + m_offset[index]) % m_capacity; // index of the auxillary slot

    char* ejected = H[auxSlot];
    H[auxSlot] = value;
    numEjections++; // increment the number of ejections
    if (numEjections > m_ejectLimit) {
        // TODO: throw exception and free up memory (call destructor?)
        cout << "****need to throw exception****" << endl;

        return;
    }
    cout << " inserted " << str << "\tinto taken aux\t" << auxSlot << endl;
    cout << "....ejected: " << ejected << " from " << auxSlot << endl;
    insert(ejected);
    free(ejected); // free ejected because the call to insert() stored a copy
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
