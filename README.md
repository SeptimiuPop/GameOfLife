# GameOfLife
A standalone application built with C++/SFML John Conway's Game of Life built with C++/SFML

## Features

### Support needed

The software requirements to run must be the following :

- Linux OS 
- C++ 11 or above
- SFML library installed

## Controls

Key Binds | Actions 
------------ | ------------- 
Escape | Close application
Left Click | Fill cell
Right Click | Clear cell
Mouse Scroll | Zoom in/out
Space Bar | Pause animation
C | Clear entire grid
Q | Speed up animation 
E | Slow down animation 
S | Update grid by one step 

## Project setup 

From the terminal use the following commands to give users permission to run the scripts. Replace File-name with the name of the shell script you want to give permission to :

```properties
sudo chmod u+x <file-name>
```  
Example :

```properties
sudo chmod u+x run.sh
```  
In order to successfully build and run the application you must create a folder named bin where the build files will go. To do this use the following command from the terminal :

```properties
mkdir bin
```  

### Launch the Application

From the terminal use the following command to build and launch the application

```properties
./run.sh
```  

### Clear the previous build for the application

From the terminal use the following command to clear the build

```properties
./clear.sh
```
### Pushs changes to your repository

After forking the repository to your local machine and making some local changes, use the following command to add all changes, commit with a message and push to the remote repository 

```properties
./push.sh
```

Uppon using this command you will be prompted to write a commit message. To confirm and move to the next step press enter
