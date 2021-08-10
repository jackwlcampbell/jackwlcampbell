PURPOSE:

The purpose of this file was to read in two supplied files, badspeak.txt and newspeak.txt, as well as strings from stdin. The program would then compare the strings from the supplied files: determining whether it was goodspeak or thoughtcrime. Words that are goodspeak are only contained within the newspeak.txt file and vice versa for thoughtcrime. Once run, the program will print a message corresponding to the amount of goodspeak and thoughtcrime found within the stdin input.
 
BUILD COMMANDS:
 
 make banhammer - makes/compiles banhammer.c and its dependants.
 make           - makes/compiles all files.
 make all       - makes/compiles all files.
 make format    - formats all files in clang-format.
 make clean     - removes all *.o files.
 
USAGE STEPS:

	1. Type 'make' into command-line.
	2. Type './banhammer < [-stdin file]' into command-line for basic functionality.
	(arguments -t, hash table size; -f, bloom filter size; m, move-to-front; and h, help message are optional.)
	4. View resulting files.
