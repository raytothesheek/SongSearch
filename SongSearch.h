#ifndef SONGSEARCH_H
#define	SONGSEARCH_H

#include "SearchRunner.h"
#include "QuadraticProbing.h"

class SongSearch {
public:
  SongSearch(const Song *songs, int songCount);
  void copy(Song &answer, Song mysong[]); 
  void quickSort(int low, int high);
  void quickSortwords(int low, int high); 
  int partition(int low, int high);
  int partitionwords(int low, int high); 
  void query(const Request &request, Song answer[], int *answerCount);
  void insertArray(char* word); 
private:
  int songCount; 
  Song *songs[42553];
  vector<holdlink*> titles;  
  QuadraticHashTable *linearprobingtitle; 
  QuadraticHashTable *linearprobingartist; 
  QuadraticHashTable *linearprobingalbum;
  QuadraticHashTable *linearprobingword; 

}; // class SongSearch 

#endif	// SONGSEARCH_H

