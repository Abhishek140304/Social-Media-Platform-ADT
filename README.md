# Social Media Platform ADT


---

## 1. Overview

This project is an implementation of a basic Social Media Platform Abstract Data Type (ADT) in C. It uses singly-linked lists to manage a platform that supports posts, comments, and replies. The platform is operated through a command-line interface (CLI) that accepts a defined set of commands to add, delete, view, and navigate content.

## 2. Features Implemented

* **Platform:** Create and manage a global platform instance.
* **Posts:**
    * Add a new post (`add_post`).
    * Delete the $n^{th}$ recent post (`delete_post`).
    * View the $n^{th}$ recent post (`view_post`).
    * Navigate posts via a `lastViewedPost` pointer:
        * `current_post`: View the last viewed post.
        * `next_post`: Move to and view the post added *before* the current one.
        * `previous_post`: Move to and view the post added *after* the current one.
* **Comments:**
    * Add a comment to the currently viewed post (`add_comment`).
    * Delete the $n^{th}$ recent comment (`delete_comment`).
    * View all comments for the current post (`view_comments`).
* **Replies (Bonus):**
    * Add a reply to the $n^{th}$ recent comment (`add_reply`).
    * Delete the $m^{th}$ reply from the $n^{th}$ comment (`delete_reply`).

## 3. File Structure

The project is organized into the following modular files:

* `main.c`: The main driver program, responsible for parsing user input and calling platform functions.
* `platform.h` / `platform.c`: Defines and implements the main `Platform` ADT and its functions.
* `post.h` / `post.c`: Defines and implements the `Post` structure and its helper functions.
* `comment.h` / `comment.c`: Defines and implements the `Comment` structure and its helper functions.
* `reply.h` / `reply.c`: Defines and implements the `Reply` structure (Bonus).
* `Makefile`: For easy compilation of the project.
* `README.md`: User Manual.

## 4. Compilation and Running

A `Makefile` is included in the project directory. To compile the project, navigate to the directory and run:

**Compile:**
```bash
make
```

**Run:**
```bash
.\social_app.exe
```

**Clean object files:**
```bash
make clean
```


## 6. Assumptions & Design Decisions

This section contains the assumptions made during implementation.

* **Data Structure:** All lists (posts, comments, and replies) are implemented as **singly-linked lists**.
* **Order of Addition (LIFO):** New items (posts, comments, replies) are added to the **front (head)** of their respective lists. This is an efficient $O(1)$ operation.
* **"Nth Recent" Interpretation:** Based on the LIFO addition, the "$n^{th}$ recent" item (e.g., in `delete_post` or `add_reply`) is interpreted as the $n^{th}$ node from the head of the list.
    * The **1st recent** item is the head of the list (the one most recently added).
    * The **2nd recent** item is `head->next` (the second most recently added).
* **Display Order (FIFO):** Although items are stored in LIFO order, the `view_comments` command must display comments in the order they were added (oldest first, newest last) to match the sample output. The provided `main.c` helper functions (`printComments`, `printReplies`) use recursion to achieve this FIFO display.
* **`lastViewedPost` Pointer:**
    * This pointer tracks the post for all comment/reply operations.
    * It defaults to the most recently added post if no post has been explicitly "viewed".
    * It is updated by `viewPost(n)`, `nextPost()`, and `previousPost()` as per their definitions.
* **Error Handling:** The program provides basic error messages to `stdout` for invalid operations (e.g., viewing a non-existent post, deleting a non-existent comment).
* **Input Format:** Usernames and captions/content are assumed to be single strings without whitespace, as per the `scanf` implementation in `main.c` and the sample I/O.