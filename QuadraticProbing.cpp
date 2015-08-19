        #include "QuadraticProbing.h"


        /**
         * Internal method to test if a positive number is prime.
         * Not an efficient algorithm.
         */
        bool QuadraticHashTable::isPrime( int n ) const
        {
            if( n == 2 || n == 3 )
                return true;

            if( n == 1 || n % 2 == 0 )
                return false;

            for( int i = 3; i * i <= n; i += 2 )
                if( n % i == 0 )
                    return false;

            return true;
        }

        /**
         * Internal method to return a prime number at least as large as n.
         * Assumes n > 0.
         */
        int QuadraticHashTable::nextPrime( int n ) const
        {
            if( n % 2 == 0 )
                n++;

            for( ; !isPrime( n ); n += 2 )
                ;

            return n;
        }

        /**
         * Construct the hash table.
         */
        QuadraticHashTable::QuadraticHashTable( int size )
          : array( nextPrime( size ) )
        {
            makeEmpty( );
        }

        /**
         * Insert item x into the hash table. If the item is
         * already present, then do nothing.
         */
        void QuadraticHashTable::inserttitle(Song *x)
        {
                // Insert x as active
            int currentPos = findPos( x->title);
            if( array[currentPos] != NULL)
                array[currentPos]->insertlist(x); 
            else{
                array[currentPos] = new holdlink(); 
                strcpy(array[currentPos]->common, x->title);
                array[currentPos]->insertlist(x); 
            }

            //array[ currentPos ] = x;
                // Rehash; see Section 5.5
            if( ++currentSize > array.size( ) / 2 )
                rehash( );
        }

        void QuadraticHashTable::insertartist(Song *x)
        {
                // Insert x as active
            int currentPos = findPos( x->artist);
            if( array[currentPos] != NULL)
                array[currentPos]->insertlist(x); 
            else{
                array[currentPos] = new holdlink(); 
                strcpy(array[currentPos]->common, x->artist);
                array[currentPos]->insertlist(x); 
            }
            //array[ currentPos ] = x;
                // Rehash; see Section 5.5
            if( ++currentSize > array.size( ) / 2 )
                rehash( );
        }

        void QuadraticHashTable::insertalbum(Song *x)
        {
                // Insert x as active
            int currentPos = findPos( x->album);
            //cout << "album " << x->album << endl;
            if( array[currentPos] != NULL)
                array[currentPos]->insertlist(x); 
            else{
                array[currentPos] = new holdlink(); 
                strcpy(array[currentPos]->common, x->album);
                array[currentPos]->insertlist(x); 
            }

            //array[ currentPos ] = x;
                // Rehash; see Section 5.5
            if( ++currentSize > array.size( ) / 2 )
                rehash( );
        }

        void QuadraticHashTable::insertword(Song *x)
        {
                // Insert x as active
            //Strtok algorithm from cplusplus.com reference pseudocode
            char *word;
            char *temp = new char[68];
            strcpy(temp, x->title);
            int currentPos;
            word = strtok(temp," ");
            
            while( word != NULL){
                currentPos = findPos(word);
                if( array[currentPos] != NULL)
                    array[currentPos]->insertlist(x); 
                else{
                        array[currentPos] = new holdlink(); 
                        strcpy(array[currentPos]->common, word);
                        array[currentPos]->insertlist(x); 
                    }
                            // Rehash; see Section 5.5
                if( ++currentSize > array.size( ) / 2 )
                    rehash( ); 
                word = strtok(NULL , " "); 
            }
        }



        /**
         * Expand the hash table.
         */
        void QuadraticHashTable::rehash( )
        {
            vector<holdlink*> oldArray = array;

                // Create new double-sized, empty table
            array.resize( nextPrime( 2 * oldArray.size( ) ) );
            for( int j = 0; j < array.size( ); j++ )
                array[ j ] = NULL;

                // Copy table over
            currentSize = 0;
            for( int i = 0; i < oldArray.size( ); i++ )
                if( oldArray[ i ] != NULL ){
                    int key = hash(string(oldArray[i]->common), array.size()); 
                    array[key] = oldArray[ i ];
                }
        }

        /**
         * Method that performs quadratic probing resolution.
         * Return the position where the search for x terminates.
         */
        int QuadraticHashTable::findPos(const char *x) const
        {
/* 1*/      int collisionNum = 0;
/* 2*/      int currentPos = hash( string(x), array.size());

/* 3*/      while( array[ currentPos ] != NULL &&
                   strcmp(array[ currentPos ]->common, x) != 0)
            {
/* 4*/          currentPos += ++collisionNum ;  // Compute ith probe
/* 5*/          if( currentPos >= array.size( ) )
/* 6*/              currentPos -= array.size( );
            }

/* 7*/      return currentPos;
        }


        /**
         * Remove item x from the hash table.
         */
        void QuadraticHashTable::remove( Song *x )
        {
            int currentPos = findPos( x->title);
            if( isActive( currentPos ) )
                array[ currentPos ]= NULL;
        }

        /**
         * Find item x in the hash table.
         * Return the matching item, or ITEM_NOT_FOUND, if not found.
         */
        const holdlink* QuadraticHashTable::find( const char *x ) const
        {
            int currentPos = findPos( x );
            return array[ currentPos ];
        }


        /**
         * Make the hash table logically empty.
         */
        void QuadraticHashTable::makeEmpty( )
        {
            currentSize = 0;
            for( int i = 0; i < array.size( ); i++ )
                array[ i ] = NULL;
        }

        /**
         * Deep copy.
         */
        const QuadraticHashTable & QuadraticHashTable::
        operator=( const QuadraticHashTable & rhs )
        {
            if( this != &rhs )
            {
                array = rhs.array;
                currentSize = rhs.currentSize;
            }
            return *this;
        }


        /**
         * Return true if currentPos exists and is active.
         */
        bool QuadraticHashTable::isActive( int currentPos ) const
        {
            return array[currentPos] != NULL; 
        }

        /**
         * A hash routine for string objects.
         */
        int QuadraticHashTable::hash( const string & key, int tableSize ) const
        {
            int hashVal = 0;

            for( unsigned int i = 0; i< key.length() ; i++ )
                hashVal = 37 * hashVal + key[ i ];

            hashVal %= tableSize;
            if( hashVal < 0 )
                hashVal += tableSize;

            //if(key == "DRIFT"){
            //    cout << hashVal << endl; 
            //}

            return hashVal;
        }


        /**
         * A hash routine for ints.
         */
        int QuadraticHashTable::hash( int key, int tableSize ) const
        {
            if( key < 0 ) key = -key;
            return key % tableSize;
        }


        holdlink::holdlink(){
            list = new List<Song*>; 
        }


        void holdlink::insertlist(Song* x){
            list->insert(x,list->zeroth());
        }




        vector<holdlink*> & QuadraticHashTable::getvector(){
            return array; 
        } 





