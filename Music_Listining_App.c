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

void createUserPlaylist(SongNode* allSong, SongNode** userList, int totalSong){
	
	int* selected = (int*)calloc(totalSong,sizeof(int));
	if(selected == NULL){
		printf("Selected dizisi icin yer ayrilamadi!\n");
		exit(1);
	}
	
	int userSongCount = 3 + (rand() % 10);
	int i=0, j , k;
	SongNode* temp;
	while(i != userSongCount){
		k = rand() % totalSong;
		
		if(selected[k] == 0){
			selected[k] =1;
			
			temp = allSong;
			
			for(j=0;j<k;j++){
				temp = temp->next;
			}
			
			addSong(userList, temp->data.name, temp->data.duration);
			i++;
		}
	}
	
	free(selected);
}

int main(){

	int userCount, totalSong=100, i;
	
	srand(time(NULL));
		
	SongNode* allSong = NULL;
	createSongs(&allSong,totalSong);
	
	printf("Kulanici Sayisi: ");
	scanf("%d",&userCount);
	
	SongNode** userPlaylists = (SongNode**)malloc(userCount*sizeof(SongNode*));
	
	if (userPlaylists == NULL) {
    	printf("userPlaylists icin bellek ayrilamadi!\n");
    	exit(1);
	}
	
	for(i=0;i<userCount;i++){
		userPlaylists[i] = NULL;
		
		createUserPlaylist(allSong, &userPlaylists[i], totalSong);
		
		printCircularList(userPlaylists[i]);
		printf("\n\n\n");
	}
	
	
	return 0;
}
