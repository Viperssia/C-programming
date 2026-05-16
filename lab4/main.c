#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[128];
	int ID;
	char Level[16];
} worker;

void Search_worker(){
	FILE* file = fopen("database.dat", "rb");
	if (file == NULL) printf("Не найден файл database.dat");
	worker guy;
    int searchId;
    int found = 0;

    printf("Введите ID сотрудника для поиска: ");
    if (scanf("%d", &searchId) != 1) {
        printf("Ошибка ввода ID.\n");
        fclose(file);
        return;
    }

	 while (fread(&guy, sizeof(worker), 1, file)) {
        if (guy.ID == searchId) {
            printf("\nСотрудник найден:\n");
            printf("Имя:     %s\n", guy.name);
            printf("ID:      %d\n", guy.ID);
            printf("Уровень: %s\n", guy.Level);
            found = 1;
            break; 
        }
    }

	if (!found) {
        printf("Ошибка: Сотрудник с ID %d не найден в базе.\n", searchId);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("Ошибка: Укажите имя файла. Пример: %s\n", argv[0]);
        return 1;
    }

    
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }

    char line[256];
    worker list[100];
    
    printf("%-20s | %-10s | %-10s\n", "Имя Фамилия", "ID", "Уровень");
    printf("------------------------------------------------------\n");


	int counter = 0;
    
    while (fgets(line, sizeof(line), file)) {
        
        line[strcspn(line, "\n")] = 0;

        
        char *name  = strtok(line, ";");
        char *id    = strtok(NULL, ";");
        char *level = strtok(NULL, ";");

        if (name && id && level) {
			strncpy(list[counter].name, name, sizeof(name));
			list[counter].ID = atoi(id);
			strncpy(list[counter].Level, level, sizeof(level));
            printf("%-20s | %-10s | %-10s\n", name, id, level);
			counter++;
        }

    }

	FILE* save_file = fopen("database.dat", "wb");

	if (save_file == NULL) {
        printf("Ошибка создания бинарного файла");
        return 1;
    }

	fwrite(list, sizeof(worker), counter, save_file);
	fclose(save_file);

    fclose(file);

	Search_worker();

    return 0;
}
