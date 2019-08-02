#include "qtree.h"

void print_greetings();

int main (int argc, char **argv) {
	
	QNode *root = NULL;	
	char answer[MAX_LINE];	
	char name[MAX_LINE];
	

	Node * interests = NULL;

	if (argc < 2) {
        printf ("To run the program ./categorizer <name of input file>\n");
        return 1;
    }
	
    interests = get_list_from_file ( argv[1]);
	
    if (interests == NULL)
        return 1;

	root = add_next_level (root,  interests);
	free_list (interests);

	//main application loop
	while(1){

		// print greetings
		print_greetings();

		// get name
		printf("Please enter your name. Type 'q' to quit\n");
		fgets(name, MAX_LINE, stdin);

		// check wether reach MAX_LINE
		if(name[strlen(name) - 1] != '\n'){
			printf("Invalid user name: user name is either shorter than 8 characters or longer than 128 characters.\n\n");
			while (name[strlen(name) - 1] != '\n') {
				fgets(name, MAX_LINE, stdin);
			}
			continue;
		}

		name[strcspn (name, "\r\n")] = '\0';

		// check whether quit
		if((strlen(name) == 1) && ((name[0] == 'q') || (name[0] == 'Q'))) {
			break;
		}

		// check alphanumeric
		int error = 0;
		int j = 0;
		while (j < strlen(name)) {
			// check whether lower case letter
			if ((name[j] >= 'a') && (name[j] <= 'z')){
				j++;
				continue;
				
				// check whther upper case letter
			} else if ((name[j] >= 'A') && (name[j] <= 'Z')){
				j++;
				continue;
			
				// check whether number
			} else if ((name[j] >= '0') && (name[j] <= '9')) {
				j++;
				continue;
			} else {
				error++;
				j++;
			}
		}
		// contain special character
		if (error > 0){
			printf("Invalid user name: user name contains non-alphanumeric characters.\n\n");
			continue;
		}

		// check too short or long
		if(strlen(name) < 8 || strlen(name) > 128) {
			printf("Invalid user name: user name is either shorter than 8 characters or longer than 128 characters.\n\n");
			continue;
		}

		// check whether user exists
		Node *friend_list_head = search_user(name, root);
		if (friend_list_head != NULL) {
			print_friend_list(friend_list_head, name);

		} else {
			QNode *curr = root;
			while (!is_leaf(curr)) {
				//get answer
				printf("Do you like %s? (y/n)\n", curr->question);
				fgets(answer, MAX_LINE, stdin);
				answer[strcspn (answer, "\r\n")] = '\0';

				// check validity
				if (strlen(answer) > 3) {
					printf("Invalid answer: the answer is longer than 3 characters.\n\n");
					continue;
				} 

				if((answer[0] == 'q') || (answer[0] == 'Q')) {
					break;
				} else if((answer[0] == 'n') || (answer[0] == 'N')) {
					curr = add_users(name, curr, 0);
				} else if((answer[0] == 'y') || (answer[0] == 'Y')) {
					curr = add_users(name, curr, 1);
				} else {
					printf("Invalid answer: the answer does not start with 'q', or 'n', or 'y', or 'Q', or 'N', or 'Y'.\n\n");
					continue;
				}
			}

			if((answer[0] == 'q') || (answer[0] == 'Q')) {
				break;
			}

			while(1) {
				//get answer
				printf("Do you like %s? (y/n)\n", curr->question);
				fgets(answer, MAX_LINE, stdin);
				answer[strcspn (answer, "\r\n")] = '\0';

				// check validity
				if (strlen(answer) > 3) {
					printf("Invalid answer: the answer is longer than 3 characters.\n\n");
					continue;
				} else if((answer[0] == 'q') || (answer[0] == 'Q')) {
					break;
				} else if((answer[0] == 'n') || (answer[0] == 'N')) {
					curr = add_users(name, curr, 0);
					print_friend_list(curr->children[0].fchild, name);
					break;
				} else if((answer[0] == 'y') || (answer[0] == 'Y')) {
					curr = add_users(name, curr, 1);
					print_friend_list(curr->children[1].fchild, name);
					break;
				} else {
					printf("Invalid answer: the answer does not start with 'q', or 'n', or 'y', or 'Q', or 'N', or 'Y'.\n\n");
					continue;
				}
			}

		}

		if(answer[0] == 'q' || (answer[0] == 'Q')) {
			break;
		}

	}
	
    //end of main loop - the user tyoped "q"
    print_qtree (root, 0);

    //free the qtree
    free_qtree(root);

	return 0;
}

void print_greetings () {
	printf ("----------------------------------------------\n");
	printf ("Friend recommender system. Find people who are just like you!\n");
	printf ("CSC209 fall 2016 team. All rights reserved\n");
	printf ("----------------------------------------------\n");
}