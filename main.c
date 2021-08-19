#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
// file "header.h" chứa struct và các hàm con của chương trình
#include "header.h"

int main() {
	// mảng not_null_in_a chứa các giá trị i sao cho a[i] != NULL
	int not_null_in_hashtable[2000];
    char word[256], mean[256], type[256];
	int user_choice;
	int check;
	FILE *f= fopen("dic.txt","a+");
	// tạo mảng a[] = NULL, chứa địa chỉ của hashtable
	// "tu" là tên của struct chứa word, type, mean của một từ
	tu* hashtable[2000] = {NULL};
	// khởi tạo dữ liệu cho mảng a[] từ file dic.txt          
	adddata(hashtable);                  
	MENU: 
	system("cls");             
	user_choice = console();
	system("cls");
    switch(user_choice) {
	 	case 1: {  
		    VIEW:  
	 		viewdic(hashtable);
			check = to_continue();
	 		if(check == 1) goto VIEW;
			if(check == 2) goto MENU;
			break;
		}
	 	case 2: {         
		    int number_of_not_null = Index(hashtable, not_null_in_hashtable);         
		    PLAY:;
	 		game( hashtable, not_null_in_hashtable, number_of_not_null);
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
	 		search(hashtable[hash(word)],word);
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
		    if ( fastfind( hashtable[hash(word)], word )) printf("This word has been in the dictionary!");
		    else {
				fflush(stdin);
				printf("\nEnter its type: "); fgets(type, 255, stdin); fflush(stdin);
			 	printf("\nEnter its meaning: "); fgets(mean, 255, stdin);
			 	hashtable[hash(word)] = addword( word, type, mean, hashtable[hash(word)]);
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
	 		deleted(hashtable,word); 
	 		check = to_continue();
	 		if(check == 1) goto DELETE;
			if(check == 2) goto MENU;
			break;
		}
		case 6:  {
			EDIT:
	 		edit(hashtable);
	 		check = to_continue();
	 		if(check == 1) goto EDIT;
			if(check == 2) goto MENU;
			break;
		}
	 	default: break;
	}
	fclose(f); 
	update_data(hashtable);
	printf("\nGOOD BYE AND SEE YOU LATER!");
	getch();
	return 0;
}
