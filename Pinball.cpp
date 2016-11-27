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
    H = new char*[n]; // the hash table
    m_size = 0; // number of items stored in H
    m_capacity = n; // number of slots in H

    // my assigned values for this project:
    m_degree = 5;
    m_ejectLimit = 20;
    numEjections = 0;
    assert(m_degree <= m_capacity); // must be possible to have unique offsets

    // create m_offsets (unique values)
    m_offset = new unsigned int[m_degree-1];
    m_offset[0] = rand() % m_capacity; // populate the first value

    // TODO: also make sure that none of them are 0
    for (int i=1; i<4; i++) {
        bool unique = false;

        while (!unique) {
            m_offset[i] = rand() % m_capacity;
            // compare against all previously generated offsets
            for (int k=0; k<i; k++) {
                if (m_offset[i] == m_offset[k])
                    break;
                if (k == i-1)
                    unique = true;
            }
        }
    }

}

/*
 * This is the destructor. Make sure you deallocate all memory for this object.
 * Strings in the H array must be deallocated using free() since they are C
 * strings (i.e., don't use delete).
 */
Pinball::~Pinball() {
    delete [] m_offset;
    for (int i=0; i<m_capacity; i++) {
        free(H[i]); // deallocate memory that was initialized with malloc()
    }

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

    if (H[primarySlot] == NULL) {
        H[primarySlot] = value; // insert into primary slot
        numEjections = 0; // reset the number of ejections
    }
    else {
        bool inserted = false;
        for (int i=0; i<m_degree-1; i++) {
            int slot = (primarySlot + m_offset[i]) % m_capacity;
            if (H[slot] != NULL) {
                H[slot] = value;
                inserted = true;
                numEjections = 0;
                break;
            }
        }

        if (!inserted) { // all slots are full
            // randomly chose one auxillary slot
            int index = rand() % (m_degree-1); // random number between 0 and 3
            int auxSlot = (primarySlot + m_offset[index]) % m_capacity;

            const char* ejected = H[auxSlot];
            H[auxSlot] = value;
            numEjections++; // increment the number of ejections
            if (numEjections > m_ejectLimit) {
                //TODO: throw exception

                return;
            }
            insert(ejected);
        }
    }

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
