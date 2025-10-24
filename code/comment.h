#ifndef COMMENT_H
#define COMMENT_H

#include"reply.h"

typedef struct Comment{
    char* username;
    char* content;
    Reply* replies;
    struct Comment* next;
}Comment;

//Function declarations
Comment* createComment(char* username, char* content);

void freeComment(Comment* comment);

#endif