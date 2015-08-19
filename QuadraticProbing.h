        #ifndef _QUADRATIC_PROBING_H_
        #define _QUADRATIC_PROBING_H_

        #include <cstring>
        #include "vector.h"
        #include "SearchRunner.h"
        #include "LinkedList.h" 

        // QuadraticProbing Hash table class
        //
        // CONSTRUCTION: an initialization for ITEM_NOT_FOUND
        //               and an approximate initial size or default of 101
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // void remove( x )       --> Remove x
        // Hashable find( x )     --> Return item that matches x
        // void makeEmpty( )      --> Remove all items
        // int hash( String str, int tableSize )
        //                        --> Static method to hash strings

        class holdlink{

            public:
                holdlink(); 
                char common[68]; 
                List<Song*> *list;
                void insertlist(Song* list); 

        }; 

        //template <class HashedObj>
        class QuadraticHashTable
        {
          public:
            explicit QuadraticHashTable(int size = 101 );
            QuadraticHashTable( const QuadraticHashTable & rhs ):
                array( rhs.array ), currentSize( rhs.currentSize ) { }

            const holdlink* find( const char * input ) const;

            void makeEmpty( );
            void inserttitle(  Song * x );
            void insertartist(Song * x);
            void insertalbum(Song * x);
            void insertword(Song* x);  
            void remove(Song * x );
            vector<holdlink*> & getvector(); 

            const QuadraticHashTable & operator=( const QuadraticHashTable & rhs );

          private:      

            vector<holdlink*> array;
            int currentSize;
            bool isPrime( int n ) const;
            int nextPrime( int n ) const;
            bool isActive( int currentPos ) const;
            int findPos( const char * x ) const;
            int hash( const string & key, int tableSize ) const;
            int hash( int key, int tableSize ) const;
            void rehash( );
        };

        //#include "QuadraticProbing.cpp"
        #endif
