Student's Name: Patricia Zapansa
Lab Exercise #5, Part 1 
Lab Section: X02L, Fall 2018
CMPUT 201, Fall 2018
Lab Instructor's Name: Calin Anton

- - - - - - - -

[ FIX 1 ]
a. Error on line 11 in safeStr.c 
	
	11:	while((c!='\0') && (count<size))

b. Debugger commands used are 'break', 'next', and 'run'.
	
	break: 	To set a breakpoint at the beginning of the safeReadString function.
	
	run: 	To run the program.

	next:	To go through each line of the function safeReadString.
	
c. The while loop didn't stop until count<size. It just kept going and asking for input
   because there was no condition for it to exit the while loop before the count<size.
   An inputted string isn't going to have a '\0' to signify the end of it. To stop the 
   problem, I could make a condition to exit the while loop.

d. Change the null terminator to a newline.

	OLD:	c = getchar(); 
		while((c!='\0') && (count<size))

	FIX:	c = getchar(); 
		while((c!='\n') && (count<size))

- - - - - -

[FIX 2]
a. Error on line 14 in main.c

	14:	    safeReadString(insStr,remChars);

b. Debugger commands used are 'break', 'next', and 'run' and 'where'.

	break: 	To set a breakpoint at main.
	
	run: 	To run the program.

	next:	To go through each line of the function main.

	where: 	Find the problem area after running and receiving a Segmentation fault.

c. After looking at line 14 I found that it was a function call using just an address 
   in memory that doesn't point to anything so I couldn't use it in the safeReadString 
   function.  I can change that to a regular char array of a size - whatever is remaining 
   from the last string, and use it that way. 

d. Change the char pointer to a char array. 

	OLD: 	char * insStr;

	FIX:	char insStr[remChar];

- - - - - -

[FIX 3]
a. Error on line 16 in main.c
b. Debugger commands used are 'break', 'next', and 'run' and 'print'.

	break: 	To set a breakpoint at main.
	
	run: 	To run the program.

	next:	To go through each line of the function main.

	print: 	To find out what is the value of newStr after every for loop in both loops. 
	        "Today is\000 Wednesday"

	list: 	To look at all the lines where I am in the function.

c. After going through the loop everything seemed to be working but. The first for loop on
   line 16 kept looping up until the null terminator in the first string. when it was 
   Concatenating, it also added the null terminator that's why previously it was displaying
   "Today is" instead of "Today is Wednesday". I could just change that to not go to the 
   very last char in the string. 

d. Change <= with < to not go into the very last char of newStr (the null terminator) before
   actually finishing the concatenation with insStr. 

	OLD:	for(i=0;i<=strlen(mainStr);i++)
		  newStr[i]=mainStr[i];
	    	for(int j=0;j<=strlen(insStr);j++)
		  newStr[i+j]=insStr[j];

	FIX:	for(i=0;i<strlen(mainStr);i++)
		  newStr[i]=mainStr[i];
	    	for(int j=0;j<=strlen(insStr);j++)
		  newStr[i+j]=insStr[j];
