/****************************************************************
   PROGRAM:   fleschKincaid.cpp
   AUTHOR:    Andrew Stefanik
   LOGON ID:  z1753912
   DUE DATE:  10/20/2015

   PURPOSE:   to read a file and calculate the Flesh-Kincaid
		readability index for the file

   INPUT:     input file(s) whose name(s) is given as a command
		line argument(s); input file(s) should contain
		a piece of English writing

   OUTPUT:    standard output, the readability index and some
		summary information for each file

   NOTES:     none
****************************************************************/
#include <iostream>	//cout, endl
#include <iomanip>	//fixed, setprecision
#include <cstdlib>	//exit
#include <string>	//string
#include <fstream>	//ifstream

using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;
using std::exit;
using std::string;
using std::ifstream;

//Function Prototypes
void fleschKincaid(char*);

//MAIN FUNCTION
int main(int argc, char* argv[])
{
	//check that there is at least one file name specified, exit the program if not
	if(argc < 2)
	{
		cout << "ERROR: no file name specified" << endl;
		exit(-1);
	}

	//calls fleschKincaid for each command line argument
	for(int i = 1; i < argc; i++)
	{
		fleschKincaid(argv[i]);
	}

	return 0;
}

/****************************************************************
   FUNCTION:   fleschKincaid(char*)

   ARGUMENTS:  char* filename

   RETURNS:    void

   NOTES:      reads a file with name filename; calculates and
		prints the Flesch-Kincaid readability index for
		the file
****************************************************************/
void fleschKincaid(char* filename)
{
	//declare variables
    ifstream inFile;
	string temp;
	string name(filename);
	int wordcount = 0, syllcount = 0, sentcount = 0;
	bool is_first_vowel;
	float L, N, glvl, rage;

	string::iterator it, jt;

		//open the file
        inFile.open(filename);

		//ensure the file opened properly, exit the program if not
        if(inFile.fail())
        {
                cout << "ERROR: File failed to open";
                exit(-1);
        }

		//while there are still unread characters, store each space-delimited character sequence in the input file into a temporary string
        while(inFile >> temp)
        {
			//for each word, increment the word and syllable count by one
			//it is necessary to increment the syllable count here because some words do not have vowels
            wordcount++;
			syllcount++;

			//if there is a sentence-ending punction mark at the end of a word, increment the sentence count by one
			it = temp.end() - 1;
			if(*it == '.' || *it == ':' || *it == ';' || *it == '?' || *it == '!')
			{
				sentcount++;
			}

			//reset the is_first_vowel flag to true
			//this is necessary so the first vowel isn't counted twice
			is_first_vowel = true;

			//for each character in the string
			for(it = temp.begin(); it != temp.end(); it++)
			{
				//if the character is a vowel
				//note that y is considered to be a vowel in all cases in this implementation
				if(*it == 'a' || *it == 'e' || *it == 'i' || *it == 'o' || *it == 'u' || *it == 'y')
				{
					jt = it+1;

					//if the next character is a vowel, it is not an additional syllable and the rest of the iteration is skipped
					if(*jt == 'a' || *jt == 'e' || *jt == 'i' || *jt == 'o' || *jt == 'u' || *jt == 'y')
					{
						continue;
					}

					//if the last character in the word is an e, it is not an additional syllable and the rest of the iteration is skipped
					if(jt == temp.end() && *it == 'e')
					{
						continue;
					}

					//if the character is the first vowel in the word, do not increment the syllable count
					if(is_first_vowel == true)
					{
						is_first_vowel = false;
					}
					//otherwise increment the syllable count by one
					else
					{
						syllcount++;
					}
				}
			}
		}

	//close the file
	inFile.close();

	//calculate readability and print information
	cout << endl << "File Name: " << name << endl << endl;

	cout << "Word Count: " << wordcount << endl;
	cout << "Syllable Count: " << syllcount << endl;
	cout << "Sentence Count: " << sentcount << endl << endl;

	L = (float) wordcount/sentcount;
	N = (float) syllcount/wordcount;

	cout << "Average Words per Sentence: " << fixed << setprecision(2) << L << endl;
	cout << "Average Syllables per Word: " << N << endl << endl;

	glvl = (L * 0.39) + (N * 11.8) - 15.59;
	rage = (L * 0.39) + (N * 11.8) - 10.59;

	cout << "Grade Level: " << glvl << endl;
	cout << "Reading Age: " << rage << endl << endl;
}
