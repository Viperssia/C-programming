#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct struct_room {
	char name[50];
	int level;
	int number;
	int resolution;
	struct struct_room* next;
	struct struct_room* next2;
} room;

const char *names[] = {"Forgotten Laboratory", "** depths of Darkness**", "Frozen Fortress", "Tower of Illusions", "Chamber of Trials"};



room *new_room() {
	
	room *new_r = (room *)malloc(sizeof(room));
	strcpy(new_r->name, names[rand() % 5]);
	new_r->level = rand() % 11;
	new_r->number = 0;
	new_r->resolution = rand() % 4;
	new_r->next = NULL;
	new_r->next2 = NULL;
	return new_r;
}

room *new_room_from(room *new_r) {
	
	// room *new_r = (room *)malloc(sizeof(room));
	strcpy(new_r->name, names[rand() % 5]);
	new_r->level = rand() % 11;
	new_r->number = 0;
	new_r->resolution = rand() % 4;
	new_r->next = NULL;
	new_r->next2 = NULL;
	return new_r;
}

void AddToLast(room *head) {
	int counter = 1;
	if (head->next == NULL) {
		head->next = new_room();
		head->next->number = counter;

		return;
	}
	
	room *cur = head->next;
	while (cur->next != NULL) {
		counter++;
		cur = cur->next;
	}
	
	cur->next = new_room();
	head->next->number = counter;
}

void printList(room *head) {

    room* cur = head;
	
    while (cur) {
        printf("%s -> ", cur->name);
        cur = cur->next;
    }
    printf("NULL\n");
}

void interface(room* head){
	
	printf("Cur: %d\n", head->number);
	if (head->next != NULL) {
		printf("1. Next: room %d\n", head->next->number);
	}
	if (head->next2 != NULL) {
		printf("2. Next2: room %d\n", head->next2->number);
	}
	int a;
	printf("Enter any number to exit: ");
	scanf("%d", &a);
	// printf("%d", a);
	if (a == 1 && head->next != NULL) {
		interface(head->next);
	}
	else if (a == 2 && head->next2 != NULL) {
		interface(head->next2);
	}
}

int main(int argc, char *argv[]) {
	srand(time(NULL));
	int N = atoi(argv[1]);
	room *list[N];
	int counter = 1;
	for (int i = 0; i < N; i++) {
		list[i] = (room*)malloc(sizeof(room));
		new_room_from(list[i]);
		list[i]->number = counter;
		counter++;
	}
	room *head = list[0];
	
	
	for (int i = 1; i < N; i++) {
		if (i == 1) {
			list[0]->next2 = list[1];
			list[1]->next2 = list[0];
			continue;
		}
		if (i % 2 == 0) {
			list[i - 2]->next = list[i];
		} else {
			list[i]->next = list[i - 2];
			list[i - 1]->next2 = list[i];
		}
	}

	interface(head);
	// printList(head);
	return 0;
}