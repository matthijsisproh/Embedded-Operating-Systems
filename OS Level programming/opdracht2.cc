#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
using namespace std;

int main()
{
	string infile;
	string outfile;
	string number;
	cout << "Geef bestandsnaam die geshuffled moet worden: ";
	getline(cin, infile);
	cout << "Geef bestandsnaam waar in geprint moet worden: ";
	getline(cin, outfile);
	cout << "Rotatie: ";
	getline(cin, number);
	
	ifstream is;
	is.open (infile.c_str(), std::ios::binary );
	is.seekg (0, std::ios::end);
	int length = is.tellg();
	char buffer[128];
	int counter = 0;
	bool closeProgram = false;

	int file_read  = open(infile.c_str(), O_RDONLY);
	if(file_read == -1){
	cout << "Geen matchende bestandsnaam gevonden" << endl;
	}
	int file_write = open(outfile.c_str(), O_WRONLY);
	if(file_write == -1){
	cout  << "WRITE ERROR" << endl;
	}

	while(read(file_read, buffer, 1))
	{	
		lseek(file_read, counter, SEEK_SET);
		write(file_write, buffer, 1);
	
		if(closeProgram)
		{
			close(file_read);
			close(file_write);
			exit(0);
		}

		counter += (stoi(number));
		if(counter >= length)
		{
			counter -= length;
			if(counter == 0) closeProgram = true;
		}
	}
}