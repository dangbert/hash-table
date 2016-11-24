#ifndef _PINBALL_H_
#define _PINBALL_H_

#include <string>
#include <stdexcept>
using namespace std ;

class PinballHashFull : public std::out_of_range {

public:
   PinballHashFull(const string& what) : std::out_of_range(what) { }
} ;


class Pinball {

public:
   Pinball(int n=1019) ;    // default capacity is prime
   ~Pinball() ;

   void insert(const char *str) ;
   int find(const char *str) ;
   const char * at(int index) ;
   char * remove(const char *str) ;
   void printStats() ;

   int size() { return m_size ; }

   // add public data members and 
   // public member functions as needed


private:
 
   char ** H ;        // the actual hash table
   int m_size ;       // number of items stored in H
   int m_capacity ;   // number slots allocated in H

   int m_degree ;     // use degree assigned to you
   int m_ejectLimit ; // use ejection limit assigned to you


   // Made inline definition of hashCode() so everyone uses
   // the same function.
   //
   unsigned int hashCode(const char *str) {

      unsigned int val = 0 ; 
      const unsigned int thirtyThree = 33 ;  // magic number from textbook

      int i = 0 ;
      while (str[i] != '\0') {
         val = val * thirtyThree + str[i] ;
         i++ ;
      }
      return val ; 
   }


   // add private data members and 
   // private member functions as needed

} ;


#endif
