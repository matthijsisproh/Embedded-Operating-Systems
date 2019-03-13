#include <iostream>
#include <string>
#include <string.h>
#include "opdracht1.hh"
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
using namespace std;

void new_file(){
	string bestandsnaam;
	string tekst;
	cout << "Bestandsnaam: ";
	getline(cin, bestandsnaam);
	cout << "Voer hier tekst in: ";
	getline(cin, tekst);

	int newFile = creat(bestandsnaam.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);
	if(newFile < 0) cout << "Error: niet gelukt bestand aan te maken";
	close(newFile);

	int file = open(bestandsnaam.c_str(), O_WRONLY);
	if(file < 0) cout << "Error: niet gelukt bestand te openen";
	write(file, tekst.c_str(), strlen(tekst.c_str()));
close(file);
}

void list(){
	int pid = fork();
	if(pid==0){
	char *args[]={"/bin/ls", "-la", NULL};
	execvp(args[0], args);
	exit(2);
	}
else{wait(NULL);
	}
}

void find(){
	string temp;
	cout << "Search: ";
	getline(cin, temp);

	char searchString[temp.size()];
	for(int i = 0; i < temp.size(); i++)
	{
		searchString[i] = temp[i];
	}
	
	int processID_find;
	int processID_grep;
	int exitStatus;
	int pipeline[2];
	pipe(pipeline);

	processID_find = fork();
	if(processID_find == 0) 
	{
		close(pipeline[1]);
		char * args_find[] = {"/usr/bin/find", ".",  nullptr};
		syscall(SYS_dup2, pipeline[0], 0);
        execve(args_find[0], args_find, nullptr);
	}
	else
	{
		processID_grep = fork();		
	
		if(processID_grep == 0) 
		{
			close(pipeline[0]);
			char * args_grep[] = {"bin/grep", searchString, nullptr};
			syscall(SYS_dup2, pipeline[1], 1);
			execve(args_grep[0], args_grep, nullptr);
		}
		else
		{
			wait(&exitStatus);
		}
	}
}
}

void python(){
	int pid = fork();
	if(pid == 0){
		char *args[]={"/usr/bin/python", NULL};
		execvp(args[0], args);
	}
else{wait(NULL);
	
}
}

int main()
{ string input;
	ifstream inFile;
	inFile.open("config.txt");
	string prompt;
	inFile >> prompt;
	inFile.close();
  while(true) {
    cout << prompt;
    getline(cin, input);
    if (input == "new_file") new_file();
    if (input == "ls") list();
    if (input == "find") find();
    if (input == "python") python();
    if (input == "quit") return 0;
    if (input == "error") return 1; } }
