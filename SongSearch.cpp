#include <cstring> 
#include <iostream>
#include "SongSearch.h"
#include "SearchRunner.h"
#include "mynew.h"


SongSearch::SongSearch(const Song *songs, int songCount) 
{
//store Song array into data structure 
//How to make a deep copy of an array of objects?
	this->songCount = songCount;
	//this->songs= new Song*[songCount];
	linearprobingtitle = new QuadraticHashTable(songCount*2);  
	linearprobingartist = new QuadraticHashTable(songCount*2);
	linearprobingalbum = new QuadraticHashTable(songCount*2);
	linearprobingword = new QuadraticHashTable(songCount*2);   

	for (int i=0; i < songCount ; i++){
		Song * temp;
		temp = new Song();
		strcpy(temp->title,songs[i].title);
		strcpy(temp->artist,songs[i].artist);
		strcpy(temp->ID,songs[i].ID);
		strcpy(temp->album,songs[i].album);
		this -> songs[i] = temp;	
		linearprobingtitle->inserttitle(temp);
		linearprobingalbum->insertalbum(temp); 
		linearprobingartist-> insertartist(temp);
		//insertArray(temp);
		linearprobingword->insertword(temp);   
	}
	//quickSort is going to be used for 3 
	quickSort(0, songCount-1);

} // SongSearch()

//Copy function for ease of use 
void SongSearch::copy(Song &answer, Song mysong[]){

	strcpy(answer.title, mysong->title);
	strcpy(answer.artist,mysong->artist);
	strcpy(answer.ID,mysong->ID);
	strcpy(answer.album,mysong->album);

}


//Required for quicksort;Constantly splits data in half to sort different sections 
int SongSearch::partition(int low, int high){
	int pivotIndex = low + (high - low)/2; //choose middle index 
	char pivotValue[11]; 
	strcpy(pivotValue,songs[pivotIndex]->ID); //strcpy index into pivot Value 
	Song * temp; //create temp of middle index 
	temp = songs[pivotIndex];
	songs[pivotIndex] = songs[high]; 
	songs[high] = temp; //swap the middle value to the end 
	int storeIndex = low; //store lowest index 
	//pivotValue = songs[high];
	   for (int i= low ; i < high; i++){ //iterate through song ids 
		if(strcmp(songs[i]->ID, pivotValue) < 0){  
        		temp = songs[i]; //swap the values 
        		songs[i] = songs[storeIndex];
        		songs[storeIndex] = temp;
			storeIndex++; //increment the stored inedex 
		}
	   }
	   temp = songs[storeIndex];
           songs[storeIndex] = songs[high];
           songs[high] = temp;
           return storeIndex; 

}
//From Wikipedia Pseudocode --> Sorts the data in the array 
//Fasest way to sort data in an array 
void SongSearch::quickSort(int low, int high){
	if (low < high){
	  int p = partition(low, high);
	  quickSort(low, p-1);
	  quickSort(p+1, high);
	}
}


int SongSearch::partitionwords(int low, int high){
	int pivotIndex = low + (high - low)/2; //choose middle index 
	char pivotValue[11]; 
	strcpy(pivotValue,songs[pivotIndex]->title); //strcpy index into pivot Value 
	Song * temp; //create temp of middle index 
	temp = songs[pivotIndex];
	songs[pivotIndex] = songs[high]; 
	songs[high] = temp; //swap the middle value to the end 
	int storeIndex = low; //store lowest index 
	   for (int i= low ; i < high; i++){ //iterate through song ids 
		if(strcmp(songs[i]->title, pivotValue) < 0){  
        		temp = songs[i]; //swap the values 
        		songs[i] = songs[storeIndex];
        		songs[storeIndex] = temp;
			storeIndex++; //increment the stored inedex 
		}
	   }
	   temp = songs[storeIndex];
           songs[storeIndex] = songs[high];
           songs[high] = temp;
           return storeIndex; 

}



void SongSearch::quickSortwords(int low, int high){
	if (low < high){
	  int p = partitionwords(low, high);
	  quickSortwords(low, p-1);
	  quickSortwords(p+1, high);
	}
}



void SongSearch::query(const Request &request, Song answer[], int *answerCount)
{
	int counter = 0; 
	if(request.type == 0){
		 Song *temp; 
		 for(int i = 0; i < titles.size() ; i++){
		 	if( titles[i] != NULL && strstr(titles[i]->common, request.criteria) != NULL){
				for( ListItr <Song *> itr  = titles[i]->list->first(); !itr.isPastEnd(); itr.advance()){
				    temp = (Song *) itr.retrieve();
				    //cout << temp->title << endl; 
		  			copy(answer[counter], temp); 
		  			counter++; 
				}
		 	}
		}
		*answerCount = counter; 
	}   
	else if(request.type == 1){
  		const holdlink* link = linearprobingtitle->find(request.criteria); 
  		Song *temp;
  		for( ListItr <Song *>itr  = link->list->first(); !itr.isPastEnd(); itr.advance()){
  	    	temp = (Song *) itr.retrieve();
  	    	copy(answer[counter], temp); 
  	    	counter++; 
  		}
  	*answerCount = counter; 
    }
  	else if(request.type == 2){
  		const holdlink* link = linearprobingartist->find(request.criteria); 
  		Song *temp;
  		for( ListItr <Song *> itr  = link->list->first(); !itr.isPastEnd(); itr.advance()){
  	    	temp = (Song *) itr.retrieve();
  	    	copy(answer[counter], temp); 
  	    	counter++; 
  		}
  		*answerCount = counter; 
  	}   
  	else if(request.type == 3){ //WORKS 
		*answerCount = 0;   
			for(int i = 0; i < songCount; i++){
			   if(strcmp(songs[i]->ID, request.criteria) == 0 ){
			   		copy(answer[*answerCount], songs[i]); 
					(*answerCount)++;
			   		for(int j = i+1; j < songCount; j++){
			   			if(strcmp(songs[j]->ID, request.criteria2) == 0){
				   			while(strcmp(songs[j]->ID, request.criteria2) == 0){
						   		copy(answer[*answerCount], songs[j]); 
					   			(*answerCount)++;
				   				j++; 
				   			}
				   			return; 
			   			}
			   			else{
							copy(answer[*answerCount], songs[j]); 
				   			(*answerCount)++;
			   			}
			   		}	
				}
		    }
	}
    else if (request.type == 4){
  		const holdlink* link = linearprobingalbum->find(request.criteria); 
  		Song *temp;
  		for( ListItr <Song *> itr  = link->list->first(); !itr.isPastEnd(); itr.advance()){
  	    	temp = (Song *) itr.retrieve();
  	    	copy(answer[counter], temp); 
  	    	counter++; 
  		}
  		*answerCount = counter; 
    }
	
	return;  
}
