#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "platform.h"

// Helper functions to get the replies in order of the time of commenting, the latest being at last
void printReplies(Reply* r){
    if(r==NULL) return;
    printReplies(r->next);
    if(r->username && r->content){
        printf("%s %s\n", r->username, r->content);
    }
}

// Helper functions to get the comments in order of the time of commenting, the latest being at last
void printComments(Comment* c) {
    if(c==NULL) return;
    printComments(c->next);
    if(c->username && c->content){    
        printf("%s %s\n", c->username, c->content);
    }
    printReplies(c->replies);
}

// Function to display a menu bar
void displayMenu(){
    printf("\nWelcome to social media Platform...................\n");
    printf("Below are the possible functionalities and their expected commands\n");
    printf("Enter what you want to do:\n");
    printf("Function \t\t\t\t\t\t\t\t Command\n");
    printf("1. Create a new Platform \t\t\t\t\t\t create_platform\n");
    printf("2. Add a new post \t\t\t\t\t\t\t add_post <user> <caption>\n");
    printf("3. Delete nth recent post \t\t\t\t\t\t delete_post <n>\n");
    printf("4. Get the nth recent post \t\t\t\t\t\t view_post <n>\n");
    printf("5. Get the lastviewed post \t\t\t\t\t\t current_post\n");
    printf("6. Get post which was posted just before posting the lastViewedPost \t next_post\n");
    printf("7. Get post which was posted just after posting the lastViewedPost \t previous_post\n");
    printf("8. Adds a comment to the lastViewedPost \t\t\t\t add_comment <user> <content>\n");
    printf("9. get a list of all comments to the lastViewedPost \t\t\t view_all_comments\n");
    printf("10. Delete the nth recent comment to the lastViewedPost \t\t delete_comment <n>\n");
    printf("11. Adds a reply to the nth recent comment of the lastViewedPos \t add_reply <user> <reply> <n>\n");
    printf("12. Deletes the mth recent reply to the nth recent comment\n of the lastViewedPost \t\t\t\t\t\t\t delete_reply <n> <m>\n");
    printf("13. Display the Menu bar \t\t\t\t\t\t display\n");
    printf("14. Enter q to exit the platform\n");
    printf("------------------------------------------------------------------\n");
    return;
}

int main() {
    char line[512];     // Buffer to read the whole line
    char command[50];
    char arg1[256], arg2[256];
    int n, m;

    displayMenu();
    createPlatform();

    while(fgets(line, sizeof(line), stdin)){

        // Remove the trailing newline character that fgets reads
        line[strcspn(line, "\n")] = 0;

        int command_read = sscanf(line, "%s", command);

        // If the line was empty or just whitespace, skip it
        if(command_read <= 0){
            continue;
        }

        // Find the start of the arguments (skip command and leading spaces)
        char* args = line + strlen(command);
        while(*args && isspace((unsigned char)*args)) args++;

        if(strcmp(command, "q")==0 || strcmp(command, "Q")==0){
            break;
        }
        if(strcmp(command, "create_platform")==0){
            printf("Platform created.\n");
        }
        else if(strcmp(command, "add_post")==0){
            int args_read = sscanf(args, "%s %[^\n]", arg1, arg2);

            if (args_read != 2) { 
                printf("Error: Missing arguments. Usage: add_post <user> <caption_with_or_without_spaces>\n");
            } else if(!addPost(arg1, arg2)){
                printf("Error: Could not add post.\n");
            }
        } 
        else if(strcmp(command, "delete_post")==0){
            int args_read = sscanf(args, "%d", &n);
            if(args_read != 1){ 
                printf("Error: Missing argument. Usage: delete_post <n>\n");
            }else if(!deletePost(n)){
                printf("Error: Post %d does not exist.\n", n);
            }
        } 
        else if(strcmp(command, "view_post")==0){
            int args_read = sscanf(args, "%d", &n);
            
            if (args_read != 1) { 
                printf("Error: Missing argument. Usage: view_post <n>\n");
            } else {
                Post* post=viewPost(n);
                if(post){
                    printf("%s %s\n", post->username, post->caption);
                }else{
                    printf("Error: Post %d does not exist.\n", n);
                }
            }
        } 
        else if(strcmp(command, "current_post")==0){
            Post* post=currPost();
            if(post){
                printf("%s %s\n", post->username, post->caption);
            }else{
                printf("Error: No current post.\n");
            }
        } 
        else if (strcmp(command, "next_post")==0){
            Post* post=nextPost();
            if(post){
                printf("%s %s\n", post->username, post->caption);
            }else{
                printf("Next post does not exist.\n");
            }
        } 
        else if(strcmp(command, "previous_post")==0){
            Post* post=previousPost();
            if(post){
                printf("%s %s\n", post->username, post->caption);
            }else{
                printf("Previous post does not exist.\n");
            }
        } 
        else if(strcmp(command, "add_comment")==0){
            int args_read = sscanf(args, "%s %[^\n]", arg1, arg2); 

            if (args_read != 2) { 
                printf("Error: Missing arguments. Usage: add_comment <user> <content>\n");
            } else if(!addComment(arg1, arg2)){
                printf("Error: No post to comment on.\n");
            }
        } 
        else if(strcmp(command, "delete_comment")==0){
            int args_read = sscanf(args, "%d", &n); 

            if (args_read != 1) { 
                printf("Error: Missing argument. Usage: delete_comment <n>\n");
            } else if(!deleteComment(n)){
                printf("Error: Comment %d does not exist.\n", n);
            }
        } 
        else if(strcmp(command, "view_comments")==0 || strcmp(command, "view_all_comments")==0){
            Comment* comment=viewComments();
            printComments(comment);
        } 
        else if(strcmp(command, "add_reply")==0){
            char* last_space = strrchr(args, ' '); // Find the last space
            int n_read = 0;
            int user_reply_read = 0;

            if (last_space != NULL) {
                n_read = sscanf(last_space + 1, "%d", &n); 
                if (n_read == 1) {
                    // Temporarily cut the string *before* the number
                    *last_space = '\0'; 
                    // Parse the "user reply_with_spaces" part from the modified 'args'
                    user_reply_read = sscanf(args, "%s %[^\n]", arg1, arg2); 
                }
            }

            // Check if we successfully read all 3 parts.
            if (n_read != 1 || user_reply_read != 2) { 
                printf("Error: Missing arguments. Usage: add_reply <user> <reply_with_spaces> <n>\n");
            } else if(!addReply(arg1, arg2, n)){
                printf("Error: Could not add reply to comment %d.\n", n);
            }
        } 
        else if(strcmp(command, "delete_reply")==0){
            int args_read = sscanf(args, "%d %d", &n, &m); 

            if (args_read != 2) { 
                printf("Error: Missing arguments. Usage: delete_reply <n> <m>\n");
            } else if(!deleteReply(n, m)){
                printf("Error: Could not delete reply %d from comment %d.\n", m, n);
            }
        } 
        else if(strcmp(command, "display")==0){
            displayMenu();
        }
        else{
            printf("Error: Unknown command '%s'.\n", command);
        }
    }

    freePlatform();
    return 0;
}