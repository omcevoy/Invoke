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

#include "Reporting.h"
using namespace std;

void appendDailyLog(std::string class_name, struct Student * student, time_t time, char flag){
	char t = '\t';
	char buff [sizeof "2011-10-08"];
	if (strftime(buff, sizeof buff, "%Y-%m-%d", gmtime(&time))) {
		std::string path = getPath(0);
		std::string filename = path + class_name + '-' + buff + ".tsv";
		//std::cout << filename << std::endl;
		std::ofstream dailyLog;
		dailyLog.open(filename, std::fstream::in | std::fstream::app);
		if (dailyLog.is_open()){
			dailyLog << student->first_name << t << student->last_name << t << student->email << t;
			dailyLog << buff << t << flag << '\n';
		}
		else {
			std::cerr << "Unable to locate the daily log file. Please try again." << std::endl;
			createDir();
			return;
		}
		dailyLog.close();
		return;
	}
}

void exportTermData(std::vector<std::shared_ptr<struct Student>> roster, std::string filename){
	char t = '\t';
	std::string path = getPath(0);
	filename = path + filename + ".tsv";
	ofstream exportFile (filename);
	if (exportFile.is_open()){
		exportFile << "# of Participations" << t << "First Name" << t << "Last Name" << t << "Student ID";
		exportFile << t << "Email" << t << "Phonetic Spelling" << t << "Reveal Code\n";
		int rosterSize = roster.size();
		//Write out each students data to the export file
		for (int i = 0; i < rosterSize; i++){
			//The amount of times a student participated
			int participations = roster[i]->participation.size();
			exportFile << participations << t << roster[i]->first_name << t << roster[i]->last_name << t;
			exportFile << roster[i]->student_id << t << roster[i]->email << t << roster[i]->phonetic_spelling << t;
			exportFile << roster[i]->reveal_code << '\n';
		}
		exportFile.close();
	}
	else {
		std::cerr << "ERROR: Unable to export the term data. Please try again" << std::endl;
		createDir();
	}
}
