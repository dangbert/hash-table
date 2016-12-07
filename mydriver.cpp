// File: mydriver.cpp
// based on mediumtest.cpp

#include <iostream>
#include <time.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "words.h"
#include "Pinball.h"

using namespace std;


// A "bug-proof" way to call rand() that preserves the state of the
// random seed between calls to rand().
// Set the random seed by passing a non-zero parameter.
int myRand(int seed=0) {

    // static local variables persist between calls
    static int savedSeed;   

    if (seed) savedSeed = seed;

    int othersSeed = rand();  // save other people's seed
    srand(savedSeed);         // restore my seed
    int result = rand();
    savedSeed = result;       // save for next time
    srand(othersSeed);        // restore other people's
    return result;
}

int main() {
	// set the seed based on the current time
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    printf("Random seed set to: %ld\n\n", ms);
    myRand(ms);
    // myRand(8781035); // Uncomment to use same random seed each time


    Pinball PH = Pinball(100);
    int reps = 83; // number of words to insert into the hash table
    int index;
    int slot;

    int saveIndices[reps];  // array to remember which words were picked
    for (int i=0; i < reps; i++) {
        saveIndices [i] = -1; // initialize all values to -1
    }

    cout << "Inserting some words..." << endl;
    bool exceptionThrown = false; // true if a PinballHashFull error is thrown
    // Pick some words from global words[] array to insert in the hash table. 
    // Pick words in index 0 .. 9999
    for (int i=0; i < reps; i++) {
        try {
            index = myRand() % 10000;  // random int 0 to 9999
            saveIndices[i] = index;    // save indices of the picked words
            PH.insert(words[index]); // insert the word into the hash table

        } catch (PinballHashFull &e) {
            cout << e.what() << endl;
            exceptionThrown = true;
            cout << "   iteration = " << i << endl;
            cout << "   words[" << index << "] = " << words[index] << endl;
            break;
        } catch (...) {
            cout << "Unknown error\n";
        }
    }
    cout << "...complete!\n\n";
    PH.printStats();
    cout << "\n\n";


    // check that all the inserted words are really there
    cout << "verifying that all inserted words are really there..." << endl;
    bool error = false; // used to indicate if a test passed or not
    int notFound = 0; // number of words not found
    for (int i=0; i < reps; i++) {
        index = saveIndices[i];
        if (index < 0) continue;  // maybe exception thrown?

        slot = PH.find(words[index]);

        if (slot == -1) {
            notFound++;
            cout << "   Inserted word not found: " << words[index] << endl;
        }
        else if (strcmp(PH.at(slot),words[index]) != 0) {
            error = true;
            cout << "   ERROR: Found word not equal!\n";    
        }
    }

    if (error)
        cout << "...test failed.\n\n";
    else if (exceptionThrown && notFound <= 1)
        cout << "...test passed! (1 word not found due to ejection limit)\n\n";
    else
        cout << "...test passed!\n\n";


    // Pick some words to be removed from the hash table
    bool passed = true;
    char *str;
    cout << "Removing some words...\n";
    for (int j = 0; j < 20; j++) {
        index = saveIndices[myRand() % reps];
        if (index < 0) continue;  // maybe exception thrown?

        str = PH.remove(words[index]);  // recover words that were picked

        if (str != NULL && strcmp(str,words[index]) != 0) {
            passed = false;
            cout << "Wrong word removed!" << endl
                << "   str = " << str << endl 
                << "   words[" << index << "] = " 
                << words[index] << endl;
        }
        free(str);
    }
    if (passed)
        cout << "...words were successfully removed!\n" << endl;
    else 
        cout << "...test failed.\n" << endl;

    PH.printStats();
}
