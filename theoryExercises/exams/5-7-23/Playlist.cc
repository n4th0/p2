#include "Playlist.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;


Playlist::Playlist(string name){
	if(name.empty()){
		throw 1; // se lanza cualquier cosa 
	}

	this->name = name; 
}

string Playlist::getName() const{
	return this->name;
}
unsigned int const Playlist::totalDuration(){
	unsigned int total = 0; 
	
	for(unsigned int i = 0; i< this->songs.size(); i++){
		total = total + this->songs[i]->getDuration();
	}
	return total;

}
void Playlist::addSong(Song *S){
	if(song == NULL){
		return;
	}

	this-> songs.push_back(S);
}

ostream& operator<<(ostream& os, const Playlist &Playlist){
	os << playlist.name << endl;
	for(unsigned int i = 0; i<songs.size(); i++){
		os << i+1 << " "<< *(playlist.songs[i])<<endl;
	}
	os << "- Total duration: " << playlist.totalDuration()<<"s"<< endl;

	return os;
}
