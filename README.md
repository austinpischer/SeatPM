# SeatPM

![SeatPM Logo](Documentation Files/SeatPM-Logo-3.png)

## How to Collaborate
This is a public repository that allows potential collaborators to
contribute to our project using "git" version control.

This project structure is reflected in the file structure of this repository.

To contribute to the project, one must do at least the following steps:
1. Download some version of "git" on your computer
2. Create a GitHub account and contact me (Austin) to request access.
3. Create a directory on your computer in which you will clone this repo.
4. Copy the repo clone URL from the "<> Code" page of this repo.
5. Clone the repo into said directory with the command "git clone *URL*" 
6. Use the command "git pull" to fetch the latest branches and files from G.H.
7. Checkout a branch on your computer
8. In PSoC creator, be sure to "Update Components" under the "Project" tab.
9. Build all projects in PSoC Creator to generate source code for components.
10. Commit your changes and push them to the GitHub servers
11. Create a pull request and wait for my approval.

## Rules for Code Appearance
Please adhere to the following practices for readability and maintainability
and simplicity of code:

1. All files written by a human author must include a "file header comment"
   at the top of the file. These file header comments should use this template:
```
/*==============================================================================
 * Project: SeatPM
 * Team: Joint Effort
 * School: Seattle Pacific University
 * Class: CatalyzeU Senior Design
 * 
 * File Name:
 * Author: 
 * 
 * File Explanation:
 *============================================================================*/
```
2a. All major sections of a file should have a "separator comment" as follows:
```
//==============================================================================
// Section Name
//==============================================================================
```
2b. A preceding section should have one newline between the last line of code
    and the following "separator comment".

3. Strive to limit all lines of code to 80 characters or less,
   unless doing so hinders readability/coherence of the code.

4. Each file should have a "end of file comment" at the (you guessed it)
   end of the file as follows:

/* [] END OF FILE */

5a. All header files should have multiple inclusion protection (m.i.p.).
5b. The start of the m.i.p. should be beneath the "file header comment".
5c. The start of the m.i.p. should utilize the header file's name in
    UPPER_CASE_SNAKE_CASE as follows:
```   
// Start of multiple inclusion protection
#ifndef FILE_NAME_H
#define FILE_NAME_H
```
5d.The end of the m.i.p. should be before the "end of file" comment as follows:
```
#endif // End of multiple inclusion protection.
/* [] END OF FILE */
```
6. All #define statements should use UPPER_CASE_SNAKE_CASE as shown in 5c.

7a. The bodies of all statments (if, if else, else, for, 
   while, do while, struct, enum, and etcetera) must be surrounded
   by curly braces.
7b. The leading curly brace of a statement body must be on its own line,
    as follows:
```
    if(Author->DoesntLikeIt == TRUE)
    {
        Author_GoCryAboutIt(&Author);
    }
    else
    {
        Author_PatSelfOnBack(&Author);
    }
```
8. Try to avoid acronyms or contractions for words.
   Try to make the code as close to plain english as possible.
   Try to optimize for read-time over write-time.

9. Filenames should be in "snake_case"

10. Variables and whatnot should be in "PascalCase"

11. This project tries to adhere to object-oriented C (OOC) principles.
    These are self-imposed rules that are not actually part of the C language.
    However, the size of the project is small enough that we do not need to
    implement most object-oriented interfaces, which saves us code space on
    the microcontroller. Please be smart about how much you adhere to OOC.
    See the following link for some information about OOC: 
    https://dmitryfrank.com/articles/oop_in_c

    
   

