*----------------------------------*
Student's Name: Patricia Zapansa
Lab Exercise #9
Lab Section: 201-X02L
Lab Instructor’s Name: Calin Anton
Course: CMPUT 201
Instructor's Name: Calin Anton
*----------------------------------*

*----------------------------------*
 POSSIBLE EXPLOITATIONS
*----------------------------------*

1. Improper Data Sanitization
---
If a person already knows at least 1 set of username+password, when they 
are prompted for a filename a system() is called for mkdir. You can do 
more than one thing with a system() call via a ';'. 

Example:   
folderName was inputted as such "foldername; cat Lab9.c > badstuff"
strcpy(command,"mkdir ");
strcat(command,folderName);
system(command);

It would make a directory called foldername and then concatenate the source
file into another file to see it. This could be exploited by someone if they 
can find a way to access stuff they aren't supposed to access via a 
system call.

2. strcpy in authenticate 
---
If the password is big enough, there wouldn't be enough room in passwd and 
there would be undefined behaviour. 
