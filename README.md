# CS50_Pset5
Problem Set 5 of CS50's Introduction to Computer Science is to implement a spell checker in C.
Since I found tries to be intriguing data structures, I decided to implement it that way.
The program takes (an optional dictionary file and) a text file, and checks the latter on spelling errors using the former.

NB: Many files were provided by the CS50 staff. 
My code can be found in the dictionary.c file, specifically the load, check, size and unload functions.

Usage:
./speller [dictionary] text

If no dictionary argument is provided, a default English dictionary is used. This can be found in dictionaries/large.
