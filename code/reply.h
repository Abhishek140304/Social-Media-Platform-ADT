#ifndef REPLY_H
#define REPLY_H

typedef struct Reply{
    char* username;
    char* content;
    struct Reply* next;
}Reply;

// Function declarations
Reply* createReply(char* username, char* content);

void freeReply(Reply* reply);

#endif