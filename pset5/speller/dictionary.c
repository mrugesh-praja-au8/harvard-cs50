// Implements a dictionary's functionality


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// const unsigned int N = 65536;

// Hash table
node *table[N];

// word count
unsigned int word_count = 0;

// check if loaded or not
bool loaded = false;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int word_length = strlen(word);
    char word_duplicate[word_length + 1];
    for(int i = 0; i < word_length; i++)
    {
        word_duplicate[i] = tolower(word[i]);
    }

    word_duplicate[word_length] = '\0';

    int hash_value = hash(word_duplicate);

    node *pointer = table[hash_value];

    while(pointer != NULL)
    {
        if(strcmp(pointer->word, word_duplicate) == 0)
        {
            return true;
        }
        else
        {
            pointer = pointer->next;
        }
    }
    return false;
}

// Hashes word to a number
// unsigned int hash(const char *word)
// {
//     // TODO

//     return 0;
// }
unsigned int hash(const char *word)
{
    // unsigned long hash = 5381;
    // int c;

    // while (c = *word++)
    //   {
    //       hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    //   }
    unsigned int x = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
        x = (x << 2) ^ word[i];
    return x % N;
    // return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    for(int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    FILE *file = fopen(dictionary, "r");
    if(file == NULL)
    {
        printf("Couldn't open dictionary\n");
        return false;
    }

    while(true)             // read a word from the dictionary and store it in store until EOF
    {
        // creating node named as new and memory allocation
        node *new = malloc(sizeof(struct node));
        if(new == NULL)
        {
            printf("Could not malloc a new node.\n");
            return false;
        }

        // copy string from store new->word
        fscanf(file, "%s", new->word);
        new->next = NULL;

        if(feof(file))
        {
            // at end of file free allocated memory
            free(new);
            break;
        }

        word_count++;

        int code = hash(new->word);
        node *head = table[code];

        if(head == NULL)
        {
            table[code] = new;
        }
        else
        {
            // here i have created unsorted linked list to minimize load time, but letter i will make sorted linked list
            new->next = table[code];
            table[code] = new;
        }
    }
    fclose(file);
    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if(loaded == true)
    {
       return word_count;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++)
    {
        node *pointer = table[i];
        node *temp;
        while(pointer != NULL)
        {
            temp = pointer;
            pointer = pointer->next;
            free(temp);
        }
    }
    loaded = false;
    return true;
}
