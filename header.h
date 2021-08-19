#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

typedef struct tu tu;
struct tu {
	char data[256];
	char type[256];
	char meaning[256];
	struct tu *next;
};

int to_continue() {
	char yes;
	printf("\n\nPress y to continue!\nPress b to back to menu!\nPress any key to exit!\nInput: ");
	fflush(stdin);
	yes = getchar();
	if (yes == 'y')
		return 1;
	if (yes == 'b')
		return 2;
}

int Random(int lenght) {
	time_t t;
	srand((unsigned)time(&t));
	return rand() % (lenght - 1);
}

void to_lower(char word[]) {
	int i = 0;
	for (i = 0; i < strlen(word); i++)
		word[i] = (char)tolower(word[i]);
}
// random 1 ký tự trong word và thay bằng dấu *
int replace(char word[]) { 
	int lenght;
	int random;
	lenght = strlen(word);
	random = Random(lenght);
	word[random] = '*';
	return random;
}
//Trả về mảng not_null_in_hashtable chứa các vị trí i sao cho hashtable[i] != NULL
int Index(tu **hashtable, int not_null_in_hashtable[]) {
	int index;
	int j = 0;
	for (index = 0; index < 2000; index++) {
		if (hashtable[index] == NULL)
			continue;
		else {
			not_null_in_hashtable[j] = index;
			j++;
		}
	}
	return j;
}
// Djb2 hash function
int hash(char *str) { 
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
		hash = ((hash << 5) + hash) + c;
	return hash % 2000;
}

tu *fromfile(char temp_word[256], char temp_type[256], char temp_meaning[256], tu *ptr) {
	if (ptr == NULL) {
		ptr = (tu *)malloc(sizeof(tu));
		strcpy(ptr->data, temp_word);
		strcpy(ptr->type, temp_type);
		strcpy(ptr->meaning, temp_meaning);
		ptr->next = NULL;
		return ptr;
	}
	ptr->next = fromfile(temp_word, temp_type, temp_meaning, ptr->next);
	return ptr;
}

void adddata(tu **hashtable) {
	FILE *f = fopen("dic.txt", "a+");
	char t1[256], t2[256], t3[256];
	while (fgets(t1, 255, f)) {
		fgets(t2, 255, f);
		fgets(t3, 255, f);
		hashtable[hash(t1)] = fromfile(t1, t2, t3, hashtable[hash(t1)]);
	}
	fclose(f);
}

void viewdic(tu **hashtable) {
	int i, len1, len2, len3;
	int number_of_word = 0;
	char temp1[256];
	char temp2[256];
	char temp3[256];
	system("cls");
	printf("********    VIEW DICTIONARY    *********");
	printf("\n\nWORD\t\tTYPE\t\tMEAN\n");
	for (i = 0; i < 2000; i++) {
		if (hashtable[i] == NULL)
			continue;
		else {
			strcpy(temp1, hashtable[i]->data);
			strcpy(temp2, hashtable[i]->type);
			strcpy(temp3, hashtable[i]->meaning);
			len1 = strlen(temp1);
			len2 = strlen(temp2);
			len3 = strlen(temp3);
			temp1[len1 - 1] = '\0';
			temp2[len2 - 1] = '\0';
			temp3[len3 - 1] = '\0';
			printf("\n%s\t\t%s\t\t%s", temp1, temp2, temp3);
			number_of_word++;
		}
	}
	printf("\n\nNumber of word in dictionary: %d", number_of_word);
}

void search(tu *hashtable, char word[256]) {
	int len1, len2, len3;
	char temp1[256];
	char temp2[256];
	char temp3[256];
	if (hashtable != NULL) {
		if (strcmp(word, hashtable->data) != 0) {
			search(hashtable->next, word);
			return;
		}
		strcpy(temp1, hashtable->data);
		strcpy(temp2, hashtable->type);
		strcpy(temp3, hashtable->meaning);
		len1 = strlen(temp1);
		len2 = strlen(temp2);
		len3 = strlen(temp3);
		temp1[len1 - 1] = '\0';
		temp2[len2 - 1] = '\0';
		temp3[len3 - 1] = '\0';
		printf("\nWORD\t\tTYPE\t\tMEAN\n");
		printf("\n%s\t\t%s\t\t%s", temp1, temp2, temp3);
	}
	else
		printf("\nThis word is not in the dictionary!");
}

void append(tu *temp) { 
	FILE *f = fopen("dic.txt", "a");
	char tu[256];
	char str1[256], str2[256];
	fprintf(f, "%s", temp->data);
	fprintf(f, "%s", temp->type);
	fprintf(f, "%s", temp->meaning);
	fclose(f);
}

tu *addword(char temp_word[256], char temp_type[256], char temp_meaning[256], tu *ptr) {
	if (ptr == NULL) {
		ptr = (tu *)malloc(sizeof(tu));
		strcpy(ptr->data, temp_word);
		strcpy(ptr->type, temp_type);
		strcpy(ptr->meaning, temp_meaning);
		append(ptr);
		ptr->next = NULL;
		return ptr;
	}
	ptr->next = addword(temp_word, temp_type, temp_meaning, ptr->next);
	return ptr;
}

int fastfind(tu *hashtable, char word[]) {
	if (hashtable == NULL)
		return 0;
	if (strcmp(hashtable->data, word) != 0)
		return (0 || fastfind(hashtable->next, word));
	return 1;
}

void deleted(tu **hashtable, char word[]) {
	int i, j;
	i = hash(word);
	if (hashtable[i] == NULL)
		printf("\nThis word is not in the dictionary!");
	else {
		hashtable[i] = NULL;
		printf("\nSuccessfully deleted!");
	}
}
void edit(tu **hashtable) {
	FILE *f = fopen("dic.txt", "a+");
	char word[256];
	int edit_what;
	int len1, len2, len3;
	char temp1[256];
	char temp2[256];
	char temp3[256];
	char edited_word[256];
	char edited_type[256];
	char edited_meaning[256];

	system("cls");
	printf("********    EDIT    *********");
	printf("\nEnter the word you want to edit: ");
	fflush(stdin);
	fgets(word, 255, stdin);
	to_lower(word);
	printf("\nInput word: %s", word);

	if (hashtable[hash(word)] != NULL) {
		if (strcmp(word, hashtable[hash(word)]->data) != 0) {
			search(hashtable[hash(word)]->next, word);
			return;
		}

		strcpy(temp1, hashtable[hash(word)]->data);
		strcpy(temp2, hashtable[hash(word)]->type);
		strcpy(temp3, hashtable[hash(word)]->meaning);
		len1 = strlen(temp1);
		len2 = strlen(temp2);
		len3 = strlen(temp3);
		temp1[len1 - 1] = '\0';
		temp2[len2 - 1] = '\0';
		temp3[len3 - 1] = '\0';

		printf("\nWORD\t\tTYPE\t\tMEAN\n");
		printf("\n%s\t\t%s\t\t%s", temp1, temp2, temp3);

		printf("\nPress\n1. To edit word\n2. To edit type\n3. To edit meaning\nPress any keys else to exit!\nInput: ");
		fflush(stdin);
		scanf("%d", &edit_what);
		switch (edit_what) {
			case 1: {
				printf("\n\nEnter edited word: ");
				fflush(stdin);
				fgets(edited_word, 255, stdin);
				hashtable[hash(edited_word)] = addword(edited_word, hashtable[hash(word)]->type, hashtable[hash(word)]->meaning, hashtable[hash(edited_word)]);
				hashtable[hash(word)] = NULL;
				printf("\nDone!");
				break;
			}
			case 2: {
				printf("\n\nEnter edited type: ");
				fflush(stdin);
				fgets(edited_type, 255, stdin);
				strcpy(hashtable[hash(word)]->type, edited_type);
				printf("\nDone!");
				break;
			}
			case 3: {
				printf("\n\nEnter edited meaning: ");
				fflush(stdin);
				fgets(edited_meaning, 255, stdin);
				strcpy(hashtable[hash(word)]->meaning, edited_meaning);
				printf("\nDone!");
				break;
			}
			default:
				break;
			}
	}
	else
		printf("\nThis word is not in the dictionary!");
	fclose(f);
}

void update_data(tu **hashtable) {
	FILE *f = fopen("dic.txt", "r");
	FILE *temp_file = fopen("temp.txt", "w");
	int i;
	for (i = 0; i < 2000; i++) {
		if (hashtable[i] == NULL)
			continue;
		fprintf(temp_file, "%s", hashtable[i]->data);
		fprintf(temp_file, "%s", hashtable[i]->type);
		fprintf(temp_file, "%s", hashtable[i]->meaning);
	}
	fclose(f);
	fclose(temp_file);
	remove("dic.txt");
	rename("temp.txt", "dic.txt");
}

void game(tu **hashtable, int not_null_in_hashtable[], int number_of_not_null) {
	char missing_char;
	char temp[256], word[256];
	int position;
	int address = 0;
	int point = 0;
	do {
		system("cls");
		printf("********    LET'S PLAY!    *********");
		printf("\n\nYour point: %d", point);

		address = not_null_in_hashtable[Random(number_of_not_null + 1)];
		strcpy(word, hashtable[address]->data);
		strcpy(temp, hashtable[address]->data);
		
		position = replace(temp);
		printf("\n\nFind the word: %s", temp);
		printf("\nEnter the missing character: ");
		fflush(stdin);
		missing_char = getchar();
		temp[position] = missing_char;
		printf("\nYour answer: %s", temp);

		if (strcmp(temp, word) == 0) {
			printf("\nGreat! That is the correct answer!\n");
			search(hashtable[hash(word)], word);
			printf("\n\n");
			point++;
			system("pause");
			continue;
		}
		if (fastfind(hashtable[hash(temp)], temp) == 1) {
			printf("\nNice! That is correct!\n");
			search(hashtable[hash(temp)], temp);
			printf("\n\n");
			point++;
			system("pause");
			continue;
		}
		break;
	} while (1);

	system("cls");
	printf("\nYour answer: %s", temp);
	printf("\nOpps, that's wrong answer!!");
	printf("\n\nThe answer must be:\n ");
	search(hashtable[hash(word)], word);
	printf("\n\nYou have got %d points!", point);
}

int console() {
	float choose;
	do {
		printf("\n============== WORD  -  GAME ==============\n");
		printf("|   1. View dictionary                    |\n");
		printf("|   2. Play                               |\n");
		printf("|   3. Search word                        |\n");
		printf("|   4. Add new word to dictionary         |\n");
		printf("|   5. Delete word in dictionary          |\n");
		printf("|   6. Edit word                          |\n");
		printf("|   7. Exit game!                         |\n");
		printf("===========================================\n");
		printf("Choose your option: ");
		fflush(stdin);
		scanf("%f", &choose);

		if (!((choose == (int)choose) && (choose <= 7 && choose >= 1))) {
			system("cls");
			printf("\nFailed! Please choose again!\n");
		}
		else
			break;
	} while (!((choose == (int)choose) && (choose <= 7 && choose >= 1)));
	return choose;
}
