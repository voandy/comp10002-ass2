/* Programmer: Andy Vo, voa1@student.unimelb.edu.au

   Algorithms are fun!
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 30 /* max chars in a name */
#define MAX_DICT_LENGTH 100 /* max entries in dictionary */

typedef char data_t[MAX_NAME_LENGTH];
#include "listops.c"

#define DIV "=========================" /* stage header */
/* stage numbers */
#define STAGE_NUM_ONE 1 
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define STAGE_NUM_FIVE 5

/* struct to store properties of an entry in the dict */
typedef struct namedict_t{
	char name_ref[MAX_NAME_LENGTH];
	int p_first;
	int p_last;
	int p_non_name;
} namedict_t;

/* function prototypes */
void print_stage_header(int stage_no);
void print_word (namedict_t namedict[], int word_no);
void stage_one (namedict_t namedict[]);
void stage_two(namedict_t namedict[], int dict_length);
void stage_three(list_t *sentence);

/* main program */
int
main(int argc, char *argv[]) {
	namedict_t namedict[MAX_DICT_LENGTH]; /* stores dictionary entries */
	int dict_length = 0;
	
	/* reads our dictionary entries into namedict*/
	char tempname[MAX_NAME_LENGTH];
	char hash; /* stores a char, used to remove # and check for % in input */
	int i;
	for (i = 0;; i++) {

		/* individually reads in suffix before reading in name */
		scanf("%c%s", &hash, tempname);

		/* breaks the loop when the end of the dict is reached */
		if (hash == '%') {
			break;
		}

		/* copies tempname into our dictionary array, copying after the break
		condition rather than in the scanf function prevents the %%%%%%%%%% 
		line from being copied into our array */
		strcpy (namedict[i].name_ref, tempname);

		/* reads in probabilities */
		scanf("%d %d %d\n", &namedict[i].p_first, &namedict[i].p_last, 
			&namedict[i].p_non_name);
	}
	dict_length = i;

	/* creates a linked list and read in the inputted sentence */
	list_t *sentence = make_empty_list();
	while (scanf("%s", tempname) != EOF) {
		insert_at_foot(sentence, tempname);
	}

	/* stage 1 */
	stage_one(namedict);
	
	/* stage 2 */
	stage_two(namedict, dict_length);

	/* stage 3 */
	stage_three(sentence);

	return 0;
}

/* prints a stage header */
void
print_stage_header(int stage_no) {
	if (stage_no > STAGE_NUM_ONE) {
		printf("\n");
	}
	printf("%sStage %d%s\n", DIV, stage_no, DIV);
}

/* prints the first word from our dictionary */
void
stage_one (namedict_t namedict[]){
	print_stage_header(STAGE_NUM_ONE);
	print_word(namedict, 0);
}

/* prints a single word, seperated from stage 1 so it can be called for
debugging */
void
print_word (namedict_t namedict[], int word_no) {
	printf("Word %d: %s\n", word_no, namedict[word_no].name_ref);
	printf("Label probabilities: %d%% %d%% %d%%\n", namedict[word_no].p_first, 
		namedict[word_no].p_last, namedict[word_no].p_non_name);
}

void
stage_two(namedict_t namedict[], int dict_length) {
	print_stage_header(STAGE_NUM_TWO);

	int char_count = 0;
	double avg_count;
	int i, j;


	for (i = 0; i < dict_length; i++) {
		for (j = 0; namedict[i].name_ref[j] != '\0'; j++) {
			char_count++;
		}
	}
	avg_count = (float)char_count / (float)dict_length;

	printf("Number of words: %d\n", dict_length);
	printf("Average number of characters per word: %.2f\n", avg_count);
}

void 
stage_three(list_t *sentence) {
	print_stage_header(STAGE_NUM_THREE);

	/* prints each word in the linked list given */
	data_t curr_word; 
	while(sentence->head) {
		strcpy(curr_word, get_head(sentence));
		printf("%s\n", curr_word);
		sentence = get_tail(sentence);
	}

}