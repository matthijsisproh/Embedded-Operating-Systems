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
	getline(std::cin, bestandsnaam);
	cout << "Voer hier tekst in: ";
	getline(cin, tekst);

	int newFile = creat(bestandsnaam.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);
	if(newFile < 0) std::cout << "Error: niet gelukt bestand aan te maken";
	close(newFile);

	int file = open(bestandsnaam.c_str(), O_WRONLY);
	if(file < 0) std::cout << "Error: niet gelukt bestand te openen";
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
	string invoer;
	string command;
	cout << "Geef een string: ";
	cin >> invoer;
	command = "find | grep " + invoer;
	system(command.c_str());
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
{ std::string input;
	ifstream inFile;
	inFile.open("config.txt");
	string prompt;
	inFile >> prompt;
	inFile.close();
  while(true) {
    cout << prompt;
    std::getline(std::cin, input);
    if (input == "new_file") new_file();
    if (input == "ls") list();
    if (input == "find") find();
    if (input == "python") python();
    if (input == "quit") return 0;
    if (input == "error") return 1; } }
