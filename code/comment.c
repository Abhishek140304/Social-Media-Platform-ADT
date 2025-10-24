#include"comment.h"
#include<stdlib.h>
#include<string.h>

// Function to Create new Comment
Comment* createComment(char* username, char* content){
    Comment* newComment=(Comment*)malloc(sizeof(Comment));
    if(!newComment) return NULL;

    newComment->content=strdup(content);
    newComment->username=strdup(username);
    if(!newComment->content || !newComment->username){
        free(newComment->username);
        free(newComment->content);
        free(newComment);
        return NULL;
    }

    newComment->next=NULL;
    newComment->replies=NULL;

    return newComment;
}

// Fuction to free Comment after deletion
void freeComment(Comment* comment){
    if(!comment) return;

    free(comment->username);
    free(comment->content);
    
    Reply* curr=comment->replies;
    while(curr){
        Reply* temp=curr;
        curr=curr->next;
        freeReply(temp);
    }

    free(comment);
}