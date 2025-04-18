#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song{
	
	char name[100];
	int duration;

}Song;

typedef struct SongNode{

	Song data;
	struct SongNode* next;
	struct SongNode* prev;

}SongNode;

SongNode* createSongNode(char* name, int duration){
	
	SongNode* node = (SongNode*)malloc(sizeof(SongNode));
	
	strcpy(node->data.name,name);
	node->data.duration = duration;
	node->next = NULL;
	node->prev = NULL;

	return node;
}

void addSong(SongNode** head,char* name,int duration){
	
	SongNode* newNode = createSongNode(name,duration);
	
	if((*head) == NULL){
		
		newNode->next = newNode;
		newNode->prev = newNode;
		
		(*head) = newNode;
		
		return;
	}
	
	newNode->prev = (*head)->prev;
	(*head)->prev->next = newNode;
	(*head)->prev = newNode;
	newNode->next = (*head);
	
	
}

void printCircularList(SongNode* head){
	
	if(head ==NULL)
		return;
		
	SongNode* tmp = head;
	
	do{
		
		printf("%s (%d)\n",tmp->data.name,tmp->data.duration);
		tmp = tmp->next;
			
	}while(tmp != head);
	
	
}

void createSongs(SongNode** head,int songNumber){
	int i,duration;
	char songName[10];
	
	for(i=0; i<songNumber; i++){
		sprintf(songName, "S%d",i+1);
		duration = 2 + (rand() % 5);
		addSong(&(*head),songName,duration);
	}
}

int main(){

	SongNode* allSong = NULL;
	createSongs(&allSong,100);
	
	printCircularList(allSong);
	return 0;
}
