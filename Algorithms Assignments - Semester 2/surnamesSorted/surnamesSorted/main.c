//
//  main.c
//  surnamesSorted
//
//  Created by Oluchi Anyabuike on 27/01/2016.
//  Copyright © 2016 Oluchi Anyabuike. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char surnames[100][12];
    int i=0;
    int size = 0;
    char item[12];
    
    
    FILE *fptr;
    
    fptr = fopen("//Users/OluchiAnyabuike/Desktop/surnames.txt", "r");
    
    if(fptr == NULL)
    {
        printf("File could not be opened \n");
        return 0;
    }
    else
    {
            while (!feof(fptr))
            {
                fscanf(fptr, "%s\n", surnames[i]);
                printf("%s\n", surnames[i]);
                i++;
                size++;
            }
        
    }
    
    fclose(fptr);
    
    int nameA = 0;
    
    printf("Please enter a surname: \n");
    scanf("%s", item);
    printf("Your surname is: %s \n", item);
    
    for (i = 0; i < size; i++)
    {
        
            if(strcmp(surnames[i], item) == 0)
            {
                nameA++;
            }
           
        
    }
    
    if (nameA > 0)
    {
           printf("%s occurs %d time(s)\n", item, nameA);
    }
    else
    {
        printf("Name doesnt't occur \n");
    }
    
    getchar();

    
    return 1;
}

   