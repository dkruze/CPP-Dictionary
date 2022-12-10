INSTRUCTIONS FOR TERM PROJECT:

	This program should allow querying of a dictionary created with multiplicative hashing and chaining. It allows the user to search for words within the dictionary and will provide them
	with suggestions should they enter something invalid. Additionally, it will return a list of all existing words that are similar to the word they entered. To run this, you have two options:
		TESLA: use winSCP to upload the program and the makefile to tesla. Then, simply run the following commands:
				>>make
				>>make run
			 Note that this will require you to rename your makefile.mak to simply "makefile" in order to function. Also note that this program wields a pretty hefty compilation
			 time, so if it takes some time to compile, that is not a local issue. The tesla version provides some pretty inaccurate answers, but does successfully spellcheck and provide
			 suggestions--the problem is that Tesla's compiler likely does not like the streaming libraries I used to create the driver function.
		LOCAL: place program into preferred directory on g++/makefile compatible computer. Either modify your makefile so that "./a.out" reads "./a.exe", or run the following commands:
				>>g++ dictionary.cpp
				>>./a.exe
			This will provide the proper output, and is the recommended method. Either way, it is highly recommended that all included files in this package be compiled according to 
			C++23 standards.
				
	Note that the given source file includes the actual hashing as a header file, which in turn includes the specified TimeInterval.h that we were given for the assignment. Please DO NOT
	rename Dictionary.txt prior to running this program, and be sure to avoid including dictionaryHash.h in any other source files with drivers in the same directory (not that you would.)