#ifndef POST_H
#define POST_H

#include"comment.h"

typedef struct Post{
    char* username;
    char* caption;
    Comment* comments;
    struct Post* next;
}Post;

// Function declarations
Post* createPost(char* username, char* caption);

void freePost(Post* post);

#endif