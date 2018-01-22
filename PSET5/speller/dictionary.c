// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// declare hash_string function
unsigned long hash_string (const char *str);

// define node struct
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// create hashtable
node *hashtable[50];

// create variable to keep track of number of words in file
unsigned int counter = 0;

// create bool to check if dictionary is loaded
bool file_loaded = false;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //make copy of const word to make word lowercase
    int word_length = strlen(word);
    char temp[word_length];
    strcpy(temp,word);
    for (int i = 0; i < word_length; i++)
    {
        temp[i]= tolower(temp[i]);
    }

    // hash word and declare head pointer to corresponding linked list
    node *head = hashtable[hash_string(temp)];

    //create cursor pointer that points to same node as head
    node *cursor = head;

    // compare strings with each node of the linked list until end of list
    while (cursor != NULL){

        // if we found the word in a node, return true
        if ((strcmp(cursor->word,temp) == 0))
        {
            return true;
        }
        // else, set cursor to next node
        cursor = cursor->next;
    }
    // return false if word is not in dictionary
    return false;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    char word[LENGTH + 1];

    //open dictionary file
    FILE *dic = fopen(dictionary, "r");

    // check if dictionary file exists
    if (dic == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }

    // read dictionary until EOF
    while (fscanf(dic, "%s", word) != EOF)
    {
        // count each words
        counter++;

        // malloc new node for each word and set it's pointer to NULL
        node *new_node = malloc(sizeof(node));
        new_node->next = NULL;

        // check that memory available for new_node
        if (new_node == NULL)
        {
            unload();
            return false;
        }

        // copy word into node
        strcpy(new_node->word, word);

        // use function hashstring() to get hashtable index
        int index = hash_string(word);

        // if this word is the first element for this index, make hashtable[index] point to new_node
        if (hashtable[index] == NULL)
        {
            hashtable[index] = new_node;
        }
        // else insert new_node to the linked list
        else
        {
            new_node->next = hashtable[index];
            hashtable[index] = new_node;
        }
    }
    fclose(dic);
    file_loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (file_loaded == true)
    {
        return counter;
    }
    else return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // iterate over hashtable array
    for (int i = 0; i < 50; i++)
    {

        // free every node for each hashtable element
        node *cursor = hashtable[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
            counter--;
        }
    }
    if (counter == 0)
    {
        return true;
    }
    return false;
}

//hash function (djb2) to return an index number
unsigned long hash_string(const char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % 50;
}
