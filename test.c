#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "test.h"
// hàm edit và update ko hoạt động
int main(){
	int not_null_in_a[1000];
    char word[256], mean[256], type[256];
	int user_choice;
	int check;
	FILE *f= fopen("dic.txt","a+");
	tu* a[1000] = {NULL};                // Khởi tạo mảng a Null để đảm bảo không tạo ra lỗi
	adddata(a);                          // Khỏi tạo dữ liệu cho mảng a
	MENU: system("cls");                 
	user_choice = console();
	system("cls");
    switch(user_choice) {
	 	case 1: {  
		    VIEW: ;            
	 		viewdic(a);
			check = to_continue();
	 		if(check == 1) goto VIEW;
			if(check == 2) goto MENU;
			break;
		}
	 	case 2: {         
		    int number_of_not_null = Index(a, not_null_in_a);         
		    PLAY:;
	 		game(a,not_null_in_a, number_of_not_null);
	 		check = to_continue();
	 		if(check == 1) goto PLAY;
			if(check == 2) goto MENU;
			break;
		}
	 	case 3: {    
		    SEARCH:                       
		    system("cls");
		    printf("********  SEARCHING  *********");
	 		printf("\nEnter the word you want to find: "); fflush(stdin); fgets(word,255,stdin);
	 		to_lower(word);
	 		printf("\nInput word: %s",word);
	 		search(a[hash(word)],word);
	 		check = to_continue();
	 		if(check == 1) goto SEARCH;
			if(check == 2) goto MENU;
			break;
		}
	 	case 4: {   
		    ADD:; 
			// Mở lại file để mọi thay đổi đều được update vào file để tiếp tục xử lý các tác vụ khác!
		    FILE *f = fopen("dic.txt", "a+"); 
		    system("cls");
		    printf("********  ADD A NEW WORD  *********");
		    printf("\nEnter a word: "); 
			getchar(); fgets(word, 255, stdin);
			to_lower(word);
		    if ( fastfind( a[hash(word)], word )) printf("This word has been in the dictionary!");
		    else {
				fflush(stdin);
				printf("\nEnter its type: "); fgets(type, 255, stdin); fflush(stdin);
			 	printf("\nEnter its meaning: "); fgets(mean, 255, stdin);
			 	a[ hash(word) ] = addword( word, type, mean, a[hash(word) ]);
			 	printf("\nSuccess!");
		    }
		    check = to_continue();
	 		if(check == 1) goto ADD;
			if(check == 2) goto MENU;
		    fclose(f);
		    break;
		}
	 	case 5: {         
		    DELETE:                 
	 		system("cls");
		    printf("********  DELETE  *********");
	 		printf("\nEnter the word you want to delete: "); fflush(stdin); fgets(word,255,stdin);
	 		to_lower(word);
	 		printf("word: %s",word);
	 		deleted(a,word); 
	 		check = to_continue();
	 		if(check == 1) goto DELETE;
			if(check == 2) goto MENU;
			break;
		}
		case 6:  {
			EDIT:
			system("cls");
		    printf("********    EDIT    *********");
			printf("\nEnter the word you want to edit: "); fflush(stdin); fgets(word,255,stdin);
	 		to_lower(word);
	 		printf("\nInput word: %s",word);
	 		edit(a[hash(word)],word);
	 		check = to_continue();
	 		if(check == 1) goto EDIT;
			if(check == 2) goto MENU;
			break;
		}
	 	default: break;
	}
	update_data(a);
	printf("\nGOOD BYE AND SEE YOU LATER!");
	fclose(f); 
	getch();
	return 0;
}
