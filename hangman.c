////////////////////////////////
//Title: Hangman              //
//Author: Matthew Anderson    //
//Date: 14/02/2024            //
//Description: Hangman Game   //
////////////////////////////////

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define DELIMITER ", "
#define MAX_WORD_LENGTH 1000

void playHangman(char secret_word[], char guessedLetters[], int right, int wrong);

int main(){
  
    FILE *file = fopen("wordbank.txt", "r");
        if (file == NULL){
            printf("Error: File not found.\n");
            return 1;
    }
    
    char line[MAX_WORD_LENGTH];
    if (fgets(line, sizeof(line), file) == NULL){
            printf("Error reading file.\n");
            fclose(file);
            return 1;
        
      }
    fclose(file);

  char *token;
  int num_words = 0;
  char *words[MAX_WORD_LENGTH];
  token = strtok(line, DELIMITER);

  while(token != NULL){
    words[num_words++] = token;
    token = strtok(NULL, DELIMITER);
  }

  if (num_words == 0){
    printf("Word bank empty.\n");
    return 1;
  }
      
  srand(time(NULL));

  int rwi = rand() % num_words;//rwi = random word index

  char secret_word[MAX_WORD_LENGTH];
  char guessedLetters[strlen(secret_word) + 1];
  memset(guessedLetters, '_', strlen(secret_word));
  guessedLetters[strlen(secret_word)] = '\0';
  strcpy(secret_word, words[rwi]);

    printf("Welcome to Hangman\n");
    playHangman(secret_word, guessedLetters, 0, 0);

  return 0;
}

void displayWord(char word[], int length){
 for (int i = 0; i < length; i++) {
    printf("%c ", toupper(word[i]));
  }
  printf("\n");
}


void playHangman(char secret_word[], char guessedLetters[], int right, int wrong){
    printf("Guess a letter: ");
    char guess;
    scanf(" %c", &guess);

  int word_length = strlen(secret_word);
  int found = 0;

 for (int i = 0; i < word_length; i++) {
   if (secret_word[i] == guess){
     printf("Yes!\n");
     guessedLetters[i] = guess;
     found = 1;
     right++;
   }
 }

if (!found) {
    printf("No!\n");
    wrong++;
  }

displayWord(guessedLetters, word_length);

if (right == word_length) {
    printf("A WINRAR IS YOU!\n");
    printf("The word was: %s\n", secret_word);
  } else if (wrong < 10) {
    playHangman(secret_word, guessedLetters, right, wrong);
  } else {
    printf("The word was: %s\n", secret_word);
  }
}
