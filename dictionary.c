// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h" //TODO: make trie struct in dictionary.h

//Create pointers needed by multiple functions.
trie_node *head;
unsigned int *word_count;
FILE *dict_file;

//Prototype for free_node function, for use in unload()
bool free_node(trie_node *current_node);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //initialize variables for finding path through the trie
    trie_node *trav = head;
    int index = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        //make sure check is case-insensitive
        char c = tolower(word[i]);

        //Set index value to navigate the trie. 'a' goes to trie_node.path[0], 'z' to path[25], '\'' goes to trie_node.path[26]
        if (c >= 'a' && c <= 'z')
        {
            index = c - 97;
        }
        else if (c == '\'')
        {
            index = 26;
        }

        //check for available path; if it is not, return false. If it is, go deeper in the trie.
        if (trav->path[index] == NULL)
        {
            return false;
        }
        else
        {
            trav = trav->path[index];
        }
    }

    //This function only breaks out of the loop when it hits the end of a word.
    if (trav->exists == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Allocate space for a trie_node to the head of the trie. For definition of struct trie_node, see dictionary.h
    head = calloc(1, sizeof(trie_node));

    //Open dictionary
    dict_file = fopen(dictionary, "r");
    if (!dict_file)
    {
        free(head);
        return false;
    }

    //Create variables for use in navigating trie
    int index = 0;
    trie_node *trav = head;

    //Set global variable 'word_count' to 0. This variable is used for size() function.
    word_count = malloc(sizeof(unsigned int));
    *word_count = 0;

    //Iterate through characters in dictionary
    for (int c = fgetc(dict_file); c != EOF; c = fgetc(dict_file))
    {
        //Set index value to navigate the trie. 'a' goes to trie_node.path[0], 'z' to path[25] ' goes to trie_node.path[26]
        if (c >= 'a' && c <= 'z')
        {
            index = c - 97;
        }
        else if (c == '\'')
        {
            index = 26;
        }
        else //c == 10, aka \0
        {
            index = 27;
        }

        // when fgetc hits '\0', c == 10. So this needs to be rewritten to handle that.
        if (index >= 0 && index <= 26)
        {
            if (trav->path[index])
            {
                //If path[index] points to something, follow that path
                trav = trav->path[index];
            }
            else
            {
                //If path[index] does not point to something, create a new node, put into the trie, and follow that path.
                trie_node *new_node = calloc(1, sizeof(trie_node));
                if (!new_node)
                {
                    unload();
                    *word_count = 0;
                    return false;
                }

                trav->path[index] = new_node;
                trav = trav->path[index];
            }
        }
        //This 'else' branch is for the case that c == '\0': word is finished
        else
        {
            trav->exists = true;
            *word_count = *word_count + 1;
            trav = head;
        }
    }

    //if we get here, everything went fine
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return *word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    free(word_count);

    bool done = free_node(head);
    fclose(dict_file);
    if (done)
    {
        return true;
    }
    else
    {
        return false;
    }

}

//Unloads a node in a trie
bool free_node(trie_node *current_node)
{
    //iterate over paths in given trie, deleting if all paths are NULL and calling free_node on every path that points to another node.
    for (int i = 0; i < 27; i++)
    {
        if (current_node->path[i] != NULL)
        {
            free_node(current_node->path[i]);
        }
    }

    free(current_node);
    return true;
}