Term Project Implementation for simple spell checker using Hashing with chaining

Execution Steps:

1. Run "make" to link the project together, then "./HSS" to run the program.

2. Initially, the program prompts the user to enter a word to see if it is in the provided dictionary. If it is present,
the program will print "True" and a list of all the words that start with the same two first letters as the provided word.
And provide the execution time in micro-seconds. Then, it will ask the user if they woudl like to continue or exit the program.

3. If the word is not initially found and it is because of a misspelling of the word, the program will recommend a word to the user.
If the recommended word is what the user wanted, they have to type "yes", "y", or "Y" and the program will proceed by printing "True" 
and a list of words that start with the same two first letters as the recommended word and provide the execution time in micro-seconds.
Then, it will ask the user if they would like to continue or exit the program. 

4. Lastly, if the word the user provided does not exist and does not closely resemble an existing dictionary word, the program proceeds
by printing "False" and asking the user if they would like to continue or exit the program.


File Unzipping Briefing:

"make": The make file was created using the MPC tool, so the .zip contains a "Makefile" and a "Makefile.HSS". 
both are required to run "make", so please make sure both are present before running "make".

"make realclean": This will clear up the executable and the object files created during the linking process. 

Happy Hunting.  
