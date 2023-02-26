# CPP-Programs

Project 3:

For the third project in my Programming Languages class, we were required to create a program which could read from a text file, consisting of single words separated by lines, and output:
    1. The number of times that a word provided by the user appears in the source file
    2. A list of all words in the source file and the number of times they each appear
    3. A histogram which indicates visually the number of times each words appears in the source file.
The program was also required to write a list of each word and its frequency to a .txt file as backup.
    
In this project, I wrote code which was efficient and well-documented with descriptive in-line comments. My getUserInput() function also validates user input in accordance with best practice. I reduced redundant code through use of functions and strove to maximize adaptability and maintainability.

If I were to try to build upon this project, I would start by improving my histogram() function. Currently, it draws a single asterisk for each appearance of a word and displays up to ten asterisks - this approach was fine for the input file provided, as no word appeared more than ten times, but the code would be more flexible if I made the function adjust to the maximum frequency word rather than hard-coding it.

The most challanging aspect of this project was finding an effective way to store each word and its frequency, and then display that information without repeating words. My solution to this was to use a map that relates strings (words) to integers (the number of times they appear). This had the added bonus of solving the problem of the same word appearing multiple times in the output, as C++ automatically increments the value for a given key within the map if that key is already present.

This project also gave me the opportunity to practice reading and writing to files, a useful skill both in my studies and real-world applications.
