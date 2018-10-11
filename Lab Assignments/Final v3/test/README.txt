The test folder includes sub folders of the different programs that include
various testing files and makefiles specific to the program:

1. selectline
   - selectline (executable)
   - selectline.c
   - makefile
   - ansSelectLine1-5
   - testInputSelectLine1-5
   - testOutputSelectLine1-5
2. famdaytest
   - famdaytest (executable)
   - famdaytest.c
   - makefile
   - ansFamDayTest1-4
   - testInputFamDayTest1-4
   - testOutputFamDayTest1-4
3. anagram
   - anagram (executable)
   - anagram.c
   - makefile
   - ansAnagram1-3
   - testInputAnagram1-3
4. squeeze
   - squeeze (executable)
   - squeeze.c
   - makefile
   - ansSqueeze1-3
   - testInputSqueeze1-3
   - testOutputSqueeze1-3   
   - testOutputAnagram1-3
5. primesdiff
   - primesdiff (executable)
   - primesdiff.c
   - makefile
   - ansPrimesDiff1-3
   - testInputPrimesDiff1-3
   - testOutputPrimesDiff1-3

All of them also include program specific explanation to the testing.

--------------------------------------------------------------------------

General Explanation for testing:

All of the testing I did for each program are essentially similar, I had files with he correct and expected output, I had input files and output files. 

In each input file I tested different cases of input specific to the program. Some input files were one line and one input only, and some were multiple lines of input. I had those files to check if the programs can handle single or multiple lines of input from a file (separated with a newline), and read until the very end of the file. 

Once I got the program working as I needed, I made a files with the correct output (naming convention: ans[program][num]) from an input (naming convention: testInput[program][num]). Then on, after making any more changes to the program's code, I check to see if the new output(naming convention: testOutput[program][num]) matches the previously correct output.

I think this was sufficient because the comparisons between the correct output and new output from the same input assured that any more changes I made to the program after, I can quickly check if it's doing everything I wanted it to do.  


