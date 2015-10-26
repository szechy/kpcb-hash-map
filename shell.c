#include <stdio.h>
#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

const static char * help = "Welcome to the C hash map demonstrator shell. "\
	"This shell is designed to demonstrate the hash map structure written "\
	"in hash.h. With a hash map size passed as an integer following the "\
	"\'-s\' flag, the shell creates a hash map of that size for users to "\
	"interact and use.\n";
const static char * help_flags = "FLAGS:\n\t-s, -size:\tPass an integer to "\
"specify the size of the hash map.\n\t-h, -help:\tDisplays help messages.\n";
const static char * help_functions = "USAGE:\n\tQUIT:\t$ quit\n\t\t$ q\n\t\t"\
	"End shell program.\n\n\tSET:\t$ map[string_key] = "\
	"user_defined_integer\n\t\tSet a key-value pair in the map.\n\n\tGET:\t"\
	"$ map[string_key]\n\t\tRetrieve key-value pair in map.\n\n\tDELETE:\t"\
	"$ map.remove(string_key)\n\t\tRemove key-value pair from map.\n\n\tLOAD:"\
	"\t$ map.load()\n\t\tCalculate load factor of map's current state.\n";

void print_help()
{
	printf("%s\n%s\n%s\n", help, help_flags, help_functions);
}

int main(int argc, char ** argv)
{
	// Parse command line argument for help, or hash map size.
	opterr = 0;
	int size = 0;
	int c;
	int received_size = 0;

	while((c = getopt(argc, argv, "s:h")) != -1)
	{
		switch(c)
		{
			// specify size
			case 's':
				size = atoi(optarg);
				printf("Welcome to the C hash map demonstrator. A shell is"\
					" about to open to allow you to\ninteract with a hash map"\
					" of size %d, as specified in the command line arguments."\
					"\n", size);
				received_size = 1;
				break;
			// specify help, then exit
			case 'h':
			default:
				print_help();
				return 0;
			break;
		}
	}

	// If we weren't passed a size, print help and then exit
	if(received_size == 0)
	{
		print_help();
		return 0;
	}

	// Going to begin implementation by allowing one hash map to be created
	hash * map = construct_hash(size);

	// Main while loop for parsing commands
	size_t input_length = 255;
	int length = 0;
	char * input = (char *)malloc(sizeof(char)*255);
	while(1)
	{
		// prepare "shell"-feel and acquire input from user
		printf("$ ");
		length = getline(&input, &input_length, stdin);
		
		// parse command
		// print help again
		if((strcmp(input, "h\n") == 0) || (strcmp(input, "help\n") == 0))
		{
			print_help();
		}
		// Exit program
		else if((strcmp(input, "q\n") == 0) || (strcmp(input, "quit\n") == 0))
		{
			break;			
		}
		// Set or set value based on key - format begins: map[string_key]
		// minimum number of characters: 'm', 'a', 'p', '[', ... ']', '\n' = 7
		else if(strstr(input, "map[") != 0)
		{
			// retrieve desired key
			int end_of_key = strchr(input, ']') - input;
			char * key = (char *)malloc(sizeof(char)*255);
			memcpy(key, &input[4], end_of_key - 4);
			key[end_of_key - 4] = '\0'; // add terminating char

			// looking for a set() or a get()? Depends on presence of '='
			char * value_loc = strchr(&input[end_of_key], '=');
			// This is a get
			if(value_loc == 0)
			{
				int * number = (int *)get(map, key);
				if(number == 0)
				{
					printf("No value with key \'%s\' was found.\n", key);
				}
				else
				{
					printf("map[%s] = %d\n", key, *number);
				}
			}
			// This is a set
			else
			{
				int * number = malloc(sizeof(int));
				*number = atoi(&input[value_loc - input + 1]);
				set(map, key, number);
			}
			free(key);
		}
		// Delete value from key
		else if(strstr(input, "map.remove(") != 0)
		{
			// retrieve desired key
			int end_of_key = strchr(input, ')') - input;
			char * key = (char *)malloc(sizeof(char) * 255);
			memcpy(key, &input[11], end_of_key - 11);
			key[end_of_key - 11] = '\0'; // add terminating char

			int * number = delete(map, key);
			if(number == 0)
			{
				printf("The key was not found.\n");
			}
			else
			{
				printf("map[%s] = %d has been removed.\n", key, *number);
				free(number);
			}
		}
		// Return load factor
		else if(strcmp(input, "map.load()\n") == 0)
		{
			printf("Load factor: %f\n", load(map));
		}
		// Didn't recognize command
		else
		{
			printf("Command not recognized. Try again. Type 'h' or 'help'"\
				" to see the help page.\n");
		}

	}

	// Clean up remaining memory from map
	free_hash(map);

	return 0;
}
