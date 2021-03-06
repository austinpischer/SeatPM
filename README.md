<p align="center">
  <img src=/Documentation/SeatPM-Logo-3.png />
</p>

# SeatPM by Joint Effort
Here you can find all of the source code and associated documentation for
the "SeatPM".

The SeatPM was originally developed as a engineering senior design project
at Seattle Pacific University. The multidisciplinary team of students that
developed the SeatPM is named "Joint Effort" and consists of the following
members:

[Zahra Lawal](https://www.linkedin.com/in/zahra-lawal/) (Mechanical Engineering)  
[Shayne Carpenter](https://www.linkedin.com/in/shayne-carpenter/) (Mechanical Engineering)  
[Fahad Abulhasan](https://www.linkedin.com/in/fahadabulhasan/) (Electrical Engineering)  
[Ali Alansari](https://www.linkedin.com/in/ali-alansari/) (Electrical Engineering)  
[Austin Pischer](https://www.linkedin.com/in/austinpischer/) (Electrical Engineering)  

To jump straight into the code, navigate to:
```
SeatPM/PSoC Creator Workspace Folder/SeatPM_Project.cydsn/main.c 
```
and
```
SeatPM/PSoC Creator Workspace Folder/SeatPM_Project.cydsn/Source Code/...
```
## Project Context

The SeatPM is a knee rehabilitation device. It is designed to be more
lightweight and transportable than existing devices of its type. 

The SeatPM is a Continuous Passive Motion (CPM) device. CPM devices move the 
target joint back and forth, over-and-over again, without any effort from the
user. 

CPM devices are useful because they stimulate blood flow and prevent
buildup of stiff scar tissue, aiding in the healing process.

Traditional knee CPM devices are typically prescribed for 6+ hours
of use per day. This is unobtainable for people in late-stage rehabilitation, 
such as student athletes and office workers, because traditional devices are 
too bulky and heavy to use on-the-go:

<p align="center">
  <img src="/Documentation/tradcpm.jpg"/>
  </br>
  <em> A traditional knee CPM device, courtesy of Wikimedia Commons. </em>
</p>

To solve these problems, Joint Effort has set out to create an alternative
device that can be used on-the-go, such as in the office or school library.

Joint Effort's device, the SeatPM,  empowers its users to save time
spent rehabilitating their knee. The SeatPM is designed for use in a seated
position by clamping to a table. Therefore, users can comfortably multitask
while fulfilling their prescribed hours of CPM use.

<p align="center">
  <img src=/Documentation/seatpmill.PNG />
  <em> An illustration of the SeatPM. </em>
</p>


## Theory Of Operation

Disclaimer:  
Due to the COVID-19 Pandemic, Joint Effort had to dramatically alter the scope
of the SeatPM prototype. This means that many planned subsystems that
had already been implemented in code had to be replaced with simpler 
alternatives. Doing so while preserving the originally written code greatly
increased the complexity of the code.

For a summary of the changes, see the below diagram:

<p align="center">
  <img src=/Documentation/blockdiagram.png />
</p>

The SeatPM can be broken down into three main subsystems:
1) The goniometer (a knee angle measurement device made from two accelerometers)
2) The motor (used to move the knee)
3) The user interface (used to configure the device parameters)

The software of the SeatPM code is broken up into "classes":

<p align="center">
  <img src=/Documentation/classdiagram.png />
</p>

A class is a set of related data and/or functions.
Traditionally, classes can be used by other classes (dependency),
can contain instances of other classes (composition),
and/or can be extensions of other classes (inheritance).

As seen in the class diagram, the user interface class is central to the flow
of control of the SeatPM code. Physically, the user interface is a 16x2 
character screen and four buttons: confirm, back, increment, and decrement. 

Conceptually, the user interface is a finite state machine. This means that the 
user manipulates the device through a series of "states," one state at a time. 
Each state has a limited set of possible operations, and transitions between 
states depend upon specific conditions being met.

Below is a diagram that outlines each state and the transitions between them:

<p align="center">
  <img src=/Documentation/statediagram.png />
</p>


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
9. Build the project in PSoC Creator 4.2 to generate source code for components.
10. Commit your changes and push them to the GitHub servers
11. Create a pull request and wait for my approval.

## Rules for Code Appearance
Please adhere to the following practices for readability and maintainability
and simplicity of code:

1. All files written by a human author must include a "file header comment"
   at the top of the file. These file header comments should use this template:
```
/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name:
Author: 

File Explanation:
==============================================================================*/
```
2a. All major sections of a file should (feel free to change "=" for more or 
    less emphasis) have a "separator comment" as follows:
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
   end of the file (PSoC Creator creates this by default) as follows:
```
/* [] END OF FILE */
```
5a. All header files should have multiple inclusion protection (m.i.p.).
5b. The start of the multiple inclusion protection should be beneath the
    "file header comment".
5c. The start of the multiple inclusion protection should utilize the header 
    file's name in UPPER_CASE_SNAKE_CASE as follows:
```  
...file header comment...
==============================================================================*/

// Start of multiple inclusion protection
#ifndef FILE_NAME_H
#define FILE_NAME_H
```
5d. The end of the multiple inclusion protection should be before the 
    "end of file" comment as follows:
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

10. Variables and whatnot should be in "PascalCase" with underscores between
    acronyms and other words. 

11. This project tries to adhere to object-oriented C (OOC) principles.
    These are self-imposed rules that are not actually part of the C language.
    However, the size of the project is small enough that we do not need to
    implement most object-oriented interfaces, which saves us code space on
    the microcontroller. Please be smart about how much you adhere to OOC.
    See the following link for some information about OOC: 
    https://dmitryfrank.com/articles/oop_in_c

12. Functions should have a "contract" comment block above its declaration in
    a header file. The contract should detail what the function requires
    (parameters, global variables, prior conditions) and what
    the function returns. It should look something like this:
```
/* Function Name:
Requirements:
Results:
*/
```

<!-- End of file -->