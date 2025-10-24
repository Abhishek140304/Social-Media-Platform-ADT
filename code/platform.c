#include"platform.h"
#include<stdlib.h>

Platform platform;

// Function to create a new Platform
void createPlatform(){
    platform.posts=NULL;
    platform.lastViewedPost=NULL;
}

// Function to free the Platform
void freePlatform(){
    Post* curr=platform.posts;
    while(curr){
        Post* temp=curr;
        curr=curr->next;
        freePost(temp);
    }
    platform.posts=NULL;
    platform.lastViewedPost=NULL;
}

// Function to add post to the Platform
bool addPost(char* username, char* caption){
    Post* newPost=createPost(username,caption);
    if(!newPost) return false;

    newPost->next=platform.posts;
    platform.posts=newPost;

    if(platform.lastViewedPost==NULL) platform.lastViewedPost=newPost;

    return true;
}

// Function to Deletes the nth recent post
bool deletePost(int n){
    if(n<=0 || !platform.posts) return false;

    Post* curr=platform.posts;
    Post* prev=NULL;

    for(int i=1; i<n && curr; i++){
        prev=curr;
        curr=curr->next;
    }

    if(!curr) return false;

    if(prev==NULL) platform.posts=curr->next;
    else prev->next=curr->next;

    if(platform.lastViewedPost==curr){
        platform.lastViewedPost=platform.posts;
    }

    freePost(curr);
    return true;
}

// Function to Returns the nth recent post
Post* viewPost(int n){
    if(n<=0 || !platform.posts) return NULL;

    Post* curr=platform.posts;

    for(int i=1; i<n && curr; i++){
        curr=curr->next;
    }

    if(!curr) return NULL;

    if(platform.lastViewedPost==curr){
        platform.lastViewedPost=platform.posts;
    }

    platform.lastViewedPost=curr;
    return curr;
}

// Function to Returns the lastViewedPost
Post* currPost(){
    if(platform.lastViewedPost) return platform.lastViewedPost;

    return platform.posts;
}

// Function to view post which is posted just before posting the lastViewedPost
Post* nextPost(){
    Post* curr=currPost();
    if(!curr) return NULL;

    Post* next=curr->next;

    if(next==NULL){
        platform.lastViewedPost=curr;
        return curr;
    }
    else{
        platform.lastViewedPost=next;
        return next;
    }
}

// Function to view post which is posted just after posting the lastViewedPost
Post* previousPost(){
    Post* curr=currPost();
    if(!curr) return NULL;

    if(curr==platform.posts){
        platform.lastViewedPost=curr;
        return curr;
    }

    Post* post=platform.posts;
    while(post && post->next!=curr){
        post=post->next;
    }

    if(!post) return NULL;

    platform.lastViewedPost=post;
    return post;
}

// Function to Adds a comment to the lastViewedPost
bool addComment(char* username, char* content){
    Post* post=currPost();
    if(!post) return false;

    Comment* newComment=createComment(username,content);

    if(!newComment) return false;

    newComment->next=post->comments;
    post->comments=newComment;
    return true;
}

// Function to Deletes the nth recent comment to the lastViewedPost
bool deleteComment(int n){
    Post* post=currPost();
    if(n<=0 || !post || !post->comments) return false;

    Comment* curr=post->comments;
    Comment* prev=NULL;

    for(int i=1; i<n && curr; i++){
        prev=curr;
        curr=curr->next;
    }

    if(!curr) return false;

    if(prev==NULL) post->comments=curr->next;
    else prev->next=curr->next;

    freeComment(curr);
    return true;
}

// Function to Returns a list of all comments to the lastViewedPost
Comment* viewComments(){
    Post* post=currPost();
    if(!post) return NULL;
    return post->comments;
}

// Function to Adds a reply to the nth recent comment of the lastViewedPos
bool addReply(char* username, char* content, int n){
    Post* post=currPost();
    if(n<=0 || !post || !post->comments) return false;

    Comment* comment=post->comments;
    for(int i=1; i<n && comment; i++){
        comment=comment->next;
    }

    if(!comment) return false;

    Reply* newReply=createReply(username,content);
    if(!newReply) return false;

    newReply->next=comment->replies;
    comment->replies=newReply;

    return true;
}

// Function to Deletes the mth recent reply to the nth recent comment of the lastViewedPost
bool deleteReply(int n, int m){
    Post* post=currPost();
    if(n<=0 || m<=0 || !post || !post->comments) return false;

    Comment* comment=post->comments;
    for(int i=1; i<n && comment; i++){
        comment=comment->next;
    }

    if(!comment || !comment->replies) return false;

    Reply* reply=comment->replies;
    Reply* prevReply=NULL;
    for(int i=1; i<m && reply; i++){
        prevReply=reply;
        reply=reply->next;
    }

    if(!reply) return false;

    if(prevReply==NULL){
        comment->replies=reply->next;
    }
    else{
        prevReply->next=reply->next;
    }

    freeReply(reply);

    return true;
}