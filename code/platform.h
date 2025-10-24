#ifndef PLATFORM_H
#define PLATFORM_H

#include"post.h"
#include"comment.h"
#include"reply.h"
#include<stdbool.h>

typedef struct Platform{
    Post* posts;
    Post* lastViewedPost;
}Platform;

extern Platform platform;

// Function declarations
void createPlatform();
void freePlatform();

bool addPost(char* username, char* caption);
bool deletePost(int n);
Post* viewPost(int n);

Post* currPost();
Post* nextPost();
Post* previousPost();

bool addComment(char* username, char* content);
bool deleteComment(int n);
Comment* viewComments();

bool addReply(char* username, char* content, int n);
bool deleteReply(int n, int m);

#endif