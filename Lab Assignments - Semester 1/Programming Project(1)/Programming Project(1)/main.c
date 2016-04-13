//
//  main.c
//  Programming Project(1)
//
//  Created by Oluchi Anyabuike on 05/04/2016.
//  Copyright © 2016 Oluchi Anyabuike. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int countCharOccurence(char *string, char c);
int getMenu();
void randChar();
int findBestWord();
int findAllWords();

int nwords = 0;
char dictionary[80000][20];

int main(void)
{
    FILE *fptr;
    int menu = 0;
    
    fptr = fopen("//Users/OluchiAnyabuike/Desktop/webster.txt", "r");
    
    if ( fptr  == NULL )
    {
        printf( "File could not be opened !!\n" );
        return 0;
    }
    else
    {
        while (!feof( fptr))
        {
            
            fscanf(fptr,"%s\n",dictionary[nwords]); //reading in the number of words in the file
            nwords++; //incrementing each time
        }
        fclose(fptr);
    }
    
    menu = getMenu(); //calling the function 'getMenu()'
    
    while (menu != 0)
    {
        if (menu == 1) randChar(); //calling the function 'randChar()'
        if (menu == 2) findBestWord(); //calling the function 'getBestWord()'
        if (menu == 3) findAllWords(); //calling the function 'findAllWords()'
        if (menu == 0) return 0; //exiting the program
        menu = getMenu(); //calling the function 'getMenu()' again
    }
}

int getMenu() //function to print out the menu of the program
{
    int menu = 0;
    
    puts("\nMenu:");
    puts("1 = Generate Random Letters");
    puts("2 = Find Longest Word");
    puts("3 = Find All Possible Words");
    puts("0 = Quit");
    fflush(stdin); //removes data from the input buffer till the next newline
    scanf("%d", &menu);
    return menu;
}

void randChar() //function to generate random selection of letters
{
    char randC = ' ';
    int count;
    int randNum = 0;
    
    srand(time(NULL));
    
    printf("Random letters: ");
    
    for (count = 0; count < 10; count++) //for loop used to generate 10 letters
    {
        randNum = 26*(rand() / (RAND_MAX + 1.0)); //picks a number between 0 and 25
        
        randNum = randNum + 97; //the ASCII code for 'a' is 97 so add 97 to the random number to get a lower case letter.
        
        randC = (char) randNum; //type case to character to convert to a char type
        
        printf(" %c\t", randC);
    }
    
}

int findAllWords() //function to find all possible words when given letters
{
    char temp[20];
    int numMatches = 0;
    int i, j;
    int len = 0;
    int tempCount = 0, wordCount = 0;
    
    puts ("Enter letters you have");
    
    scanf("%s",temp);
    
    puts("\nMatching Words:\n--------------------------\n");
    
    for (i=0;i<nwords;i++)
    {
        numMatches = 0;
        len = strlen(dictionary[i]);
        
        for (j=0;j<len;j++)
        {
            tempCount = 0;
            wordCount = 0;
            tempCount = countCharOccurence(temp, dictionary[i][j]);
            wordCount = countCharOccurence(dictionary[i], dictionary[i][j]);
            
            /* every letter gets counted once => if 3 'a's in each word, then +1 for each a
            a full match on an n-letter word gets a score of 8 */
            if ((tempCount > 0) && (tempCount == wordCount))
            {
                numMatches = numMatches + 1;
            }
            else
            {
                numMatches = 0;
                break;
            }
        }
        
        // can make the word if all of it's letters are in the input string
        if (numMatches == len)
        {
            printf ("%s\n", dictionary[i]);
        }
    }
    
    
    
    return numMatches;
}

int findBestWord() //function to find longest/best word possible
{
    char bestFit[20];
    int numMatches = 0;
    int highestMatch = 0;
    int i=0, j=0, len=0;
    char temp[20];
    int tempCount=0, wordCount=0;
    
    puts ("Enter letters you have");
    
    scanf("%s",temp);
    
    for (i=0;i<nwords;i++)
    {
        numMatches = 0;
        len = strlen(dictionary[i]);
        
        for (j=0;j<len;j++)
        {
            tempCount = 0;
            wordCount = 0;
            tempCount = countCharOccurence(temp, dictionary[i][j]);
            wordCount = countCharOccurence(dictionary[i], dictionary[i][j]);
            
            /* every letter gets counted once, if there are 3 'a's in each word, then +1 for each a
            a full match on an 8-letter word gets a score of 8 */
            if ((tempCount > 0) && (tempCount == wordCount))
            {
                numMatches = numMatches + 1;
            }
            else
            {
                numMatches = 0;
                break;
            }
        }
        
        if (numMatches > highestMatch) 
        {
            strcpy(bestFit, dictionary[i]);
            highestMatch = numMatches;
        }
    }
    
    printf ("Best Fit for \"%s\" is \"%s\"  [%d]\n", temp, bestFit, highestMatch);
    
    return numMatches;
}


int countCharOccurence(char *string, char c)
{
    int i;
    int count = 0,len = 0;
    
    len = strlen(string);
    
    for(i = 0;i < len;i++)
    {
        if (string[i] == c)
        {
            count++;
        }
    }
    return count;
}
