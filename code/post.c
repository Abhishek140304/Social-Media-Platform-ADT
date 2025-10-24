#include"post.h"
#include<stdlib.h>
#include<string.h>

// Function to create a new post
Post* createPost(char* username, char* caption){
    Post* newPost=(Post*)malloc(sizeof(Post));
    if(!newPost) return NULL;

    newPost->username=strdup(username);
    newPost->caption=strdup(caption);

    if(!newPost->username || !newPost->caption){
        free(newPost->username);
        free(newPost->caption);
        free(newPost);
        return NULL;
    }

    newPost->comments=NULL;
    newPost->next=NULL;

    return newPost;
}

// Function to free a post after deleting
void freePost(Post* post){
    if(!post) return;

    free(post->caption);
    free(post->username);

    Comment* curr=post->comments;
    while(curr){
        Comment* temp=curr;
        curr=curr->next;
        freeComment(temp);
    }

    free(post);
}