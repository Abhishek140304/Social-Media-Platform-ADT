#include"reply.h"
#include<stdlib.h>
#include<string.h>

// Function to create a new Reply
Reply* createReply(char* username, char* content){
    Reply* newReply=(Reply*)malloc(sizeof(Reply));
    if(!newReply) return NULL;

    newReply->username=strdup(username);
    newReply->content=strdup(content);
    if(!newReply->content || !newReply->username){
        free(newReply->username);
        free(newReply->content);
        free(newReply);
        return NULL;
    }

    newReply->next=NULL;
    return newReply;
}

// Function to free a Reply after deleting
void freeReply(Reply* reply){
    if(!reply) return;

    free(reply->username);
    free(reply->content);
    free(reply);
}