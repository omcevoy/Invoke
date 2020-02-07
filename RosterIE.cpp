/*
* Description: Project 1 (cold calling system)
*
* Author: Owen, Mason, James, Zach, Sam
*
* Date of last update: 2/3/2020
*
* Notes:
*
*/
#include "RosterIE.h"
using namespace std;

char
getDelim(string line){
	char t = '\t';
	char delim;
	for (unsigned int i = 0; i < line.size(); i++){
		//check if delimiter is a comma
		if (line[i] == ','){
			//cout << "Recognized comma as the delimiter" << endl;
			delim = ',';
			return delim;
		}
		else if (line[i] == t){
			//check if delimiter is a tab
			delim = '\t';
			return delim;
		}
		else if (line[i] == '\n') {
			//if the delimiter is unrecognizable, return 0
			return '0';
		}
	}
	return '0';
}

std::vector<std::shared_ptr<struct Student>>
importRoster (string file) {
	 //the vector where all the students will be stored
	std::vector<std::shared_ptr<struct Student>> newClass;
	char delimiter = 'o';
	int i = 0;
	ifstream input;
	std::string filename = file + ".txt";
	input.open(filename);
	if (!input.is_open()) {
		cerr << "There was an issue opening the file" << filename << endl;
		return newClass;
	}
	while(input) {
		string line;
		while(getline(input, line, '\n')) {	//parses file line by line
			if (i == 0) {
				//skip the first line, as it does not contain data we care about
				i++;
				break;
			}
			if (delimiter == 'o'){
				//determine the delimiter of the file
				delimiter = getDelim(line);
				//if unrecognized delimiter, do not import the file
				if (delimiter == '0'){
					return newClass;
				}
			}
			//vector which contains data for each individual student entry
			std::vector<string> entry;
			stringstream meta(line);
			string key;
			//int variable to ensure the data is full/correct
			int j = 0;
			while(getline(meta, key, delimiter)) {
				entry.push_back(key);
				j++;
				if(j > 6) {
					//If there is too many columns, do not add it. Report the row number this error occurred at
					cerr << "An error has occurred at row " << i << " it appears there are too many entries" << endl;
					break;
				}
			}
			//Only add the student to the roster if the data is complete
			if(j == 6){
				std::shared_ptr<struct Student> S (new struct Student());
				(*S).first_name = entry[0];
				(*S).last_name = entry[1];
				(*S).student_id = entry[2];
				(*S).email = entry[3];
				(*S).phonetic_spelling = entry[4];
				(*S).reveal_code = entry[5][0];
				newClass.push_back(S);
			}
			else if (j < 6) {
				//If the data for the entry is not complete, do not add it to the roster and report the row number.
				cerr << "An error has occurred at row " << i << " ensure the data is complete" << endl;
			}
		}
		i++;
	}
	return newClass;
}

void exportRoster(std::vector<std::shared_ptr<struct Student>> roster, std::string filename){
	char t = '\t';
	//get file path to user directory
	std::string path = getPath(0);
	filename = path + filename + ".txt";
	ofstream exportFile (filename);
	exportFile << "# of Participations" << t << "First Name" << t << "Last Name" << t << "Student ID";
	exportFile << t << "Email" << t << "Phonetic Spelling" << t << "Reveal Code\n";
	if (exportFile.is_open()){
		exportFile << "# of Participations" << t << "First Name" << t << "Last Name" << t << "Student ID" << t;
		exportFile << "Email" << t << "Phonetic Spelling" << t << "Reveal Code\n";
		int rosterSize = roster.size();
		for (int i = 0; i < rosterSize; i++){
			//For each student, write their data to the export file
			exportFile << roster[i]->first_name << t << roster[i]->last_name << t << roster[i]->student_id << t;
			exportFile << roster[i]->email << t << roster[i]->phonetic_spelling << roster[i]->reveal_code << '\n';
		}
		exportFile.close();
	}
	else {
		std::cerr << "ERROR: Unable to export the roster. Please try again." << std::endl;
		createDir();
	}
}
