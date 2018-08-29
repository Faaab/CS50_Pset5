# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

Functionally: this is longest wordt in the large dictionary provided in the CS50 distribution for pset5.
Semantically: this is an occupational lung disease caused by the inhalation of crystalline silica dust. It is also known as silicosis. (From: https://en.wikipedia.org/wiki/Silicosis)

## According to its man page, what does `getrusage` do?

This function returns data on resource usage of the current process. This data includes CPU time used, RAM used, and stack size, among others.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Since the program already uses a lot of memory, I think you chose to pass by reference instead of by value because of memory efficiency.
Passing by value would mean that the two rusage structs, which together contain 28 longs and 4 more structs, would need to be copied, only
for a simple calculation on a small subset of the data that was copied. Passing by reference spares the copying, thereby using a lot
less memory and it's a bit quicker too.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The main for-loop, the start of which is written on line 71, iterates over every character in the file, until the EOF is reached.
For every character, there are three possibilities:
A. (lines 74-89) The current character is alphabetic or an apostrophe, so it is possibly part of a string that the program could check. So the character
is placed in the array word[] at place 'index', after which index is incremented by 1, so we could (if we need to) place the next character
in the next place in the array.
BUT: if the index gets too large, meaning that the string is larger than the longest word we can check, a while-loop fast-forwards over the
string until the EOF or (presumably) an EOL is reached. Then index is set to 0, which prepares us for a new word.
B. (lines 92-99) Our program cannot check strings that include numbers, so if the current character is a number, a while-loop fast-forwards
over the until the EOF or (presumably) an EOL is reached. Then index is set to 0, which prepares us for a new word.
C. (lines 102-127) if the current character is neither alphanumeric nor an apostrophe, we presume we found the end of the word.
If we are at the end of a word AND the index is larger than 0 (which excludes strings deemed uncheckable by the prvious 2 branches),
the string in word[] is ended with a '\0'. The 'words'-counter is then updated (since we found another word), and the word is spell-checked.
If it is misspelled, the word is printed to the user and the misspellings-counter is updated. Lastly, to prepare for a new word, the index
is set to 0.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

This makes it easier to check for numbers in the string (which make the string incompatible with our program).

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Because it is important for these functions not to modify their parameters.
