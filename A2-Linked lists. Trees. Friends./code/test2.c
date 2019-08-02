#include "qtree.h"

int main (int argc, char ** argv) {
    QNode *root = NULL;
	Node *q_list;
    
    if (argc < 2) {
        printf ("To run the program ./test2 <name of input file>\n");
        return 1;
    }
    
    q_list = get_list_from_file (argv[1]);
    
    if (q_list == NULL) {
        printf ("The list is empty\n");
        return 1;
    }
    
    //that is only the first test to test creation of the question tree
    root = add_next_level (root, q_list);
	print_qtree (root, 0);
    
    
    //your tests here
    // need to give enough arguments in command line
    // count the number of questions
    Node * curr = q_list;
    int count = 0;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    
    if ((argc-3) > count) {
        printf("Too much aruguments: give %d answers for %d questions.\n", argc-3, count);
        return 1;
    }
    if ((argc-3) < count) {
        printf("Few arguments: only give %d answers for %d questions.\n", argc-3, count);
        return 1;
    }

    int i = 3;
    QNode *next = root;

    while(!(is_leaf(next))){
        next = add_users(argv[2], next, strtol(argv[i], NULL, 2));
        i++;
    }
    next = add_users(argv[2], next, strtol(argv[i], NULL, 2));

    printf("Tree after adding user %s:\n", argv[2]);
    print_qtree(root,0);

    
    return 0;
}