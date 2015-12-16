#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <glib.h>


void print_words(gpointer key, gpointer value, gpointer userdata) {
	char* realKey = (char*)key;
   	int* realValue = (int*)value;
    printf("%s => %d\n", realKey, *realValue);
}

int main() {
	FILE *file;
	char line[80];

	file = fopen("huckfinn.txt", "r");

	GHashTable *word_counts = g_hash_table_new (g_str_hash,  /* Hash function  */
							                    g_str_equal); /* Comparator     */

	if (file != NULL) {
	    while (fgets(line, 80, file) != NULL) {
			/* get a line, up to 80 chars from file. done if NULL */
		   const char s[2] = " ";
		   char *token;
		   
		   /* get the first token */
		   token = strtok(line, s);
		   
		   /* walk through other tokens */
		   while( token != NULL ) 
		   {
				gint *val = (gint *) g_hash_table_lookup(word_counts, token);
				/* This is the pointer to our key data. */
			    char* key = NULL;
			    /* This is the pointer to our value data. */
			    int* newval = NULL;

				if (val == NULL) {
					key = strdup(token);
					gint *newval = g_new (gint, 1);
					*newval = 1;
					g_hash_table_insert (word_counts, key, newval);
				} else {
					*val += 1;
				}	
				token = strtok(NULL, s);
		   }
		}
	    fclose(file);

	    g_hash_table_foreach(word_counts, print_words, NULL);
	    return(0);
	} else {
		perror("Error Opening File");
		return(-1);
	}
}
