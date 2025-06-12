#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SHOES 100
#define MAX_NAME_LENGTH 50
#define MAX_COLOR_LENGTH 30

typedef struct {
    char name[MAX_NAME_LENGTH];
    int size;
    char color[MAX_COLOR_LENGTH];
    float price;
} Shoe;

void inputShoes(Shoe shoes[], int *count) {
    printf("Введіть кількість пар взуття: ");
    scanf("%d", count);
    
    for (int i = 0; i < *count; i++) {
        printf("\nПара взуття #%d:\n", i+1);
        printf("Назва: ");
        scanf("%s", shoes[i].name);
        printf("Розмір: ");
        scanf("%d", &shoes[i].size);
        printf("Колір: ");
        scanf("%s", shoes[i].color);
        printf("Ціна: ");
        scanf("%f", &shoes[i].price);
    }
}

void writeToFile(Shoe shoes[], int count, const char *targetName, float maxPrice) {
    FILE *file = fopen("filtered_shoes.txt", "w");
    if (file == NULL) {
        printf("Помилка відкриття файлу!\n");
        return;
    }
    
    fprintf(file, "Результати пошуку: назва '%s', максимальна ціна %.2f\n\n", targetName, maxPrice);
    fprintf(file, "%-20s %-10s %-15s %-10s\n", "Назва", "Розмір", "Колір", "Ціна");
    fprintf(file, "--------------------------------------------------\n");
    
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(shoes[i].name, targetName) == 0 && shoes[i].price <= maxPrice) {
            fprintf(file, "%-20s %-10d %-15s %-10.2f\n", 
                   shoes[i].name, shoes[i].size, shoes[i].color, shoes[i].price);
            found++;
        }
    }
    
    if (!found) {
        fprintf(file, "Взуття з вказаними параметрами не знайдено.\n");
    }
    
    fclose(file);
    printf("Результати збережено у файлі 'filtered_shoes.txt'\n");
}

int main() {
    system("chcp 65001");
    Shoe shoes[MAX_SHOES];
    int count;
    char targetName[MAX_NAME_LENGTH];
    float maxPrice;

    inputShoes(shoes, &count);

    printf("\nВведіть назву взуття для пошуку: ");
    scanf("%s", targetName);
    printf("Введіть максимальну ціну: ");
    scanf("%f", &maxPrice);

    writeToFile(shoes, count, targetName, maxPrice);
    
    return 0;
}