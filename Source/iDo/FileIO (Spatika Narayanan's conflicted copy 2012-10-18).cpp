#include "FileIO.h"
#include "FloatingTask.h"
#include "DeadlinedTask.h"
#include "TimedTask.h"

const int MAX_INPUT_SIZE = 100;

vector<Task*> FileIO::getTaskList(){

	return FileIO::taskList;

}
void FileIO::setFileName(string fileName){
	this->fileName = fileName.c_str();
}
void FileIO::setTaskList(vector<Task*>& list){
	this->taskList = list;
}
 void FileIO::readList(){
	ifstream fin(FileIO::fileName);
	char fileInput[MAX_INPUT_SIZE];
	string day, month, year, hour, min;
	int check = 1;
	string description;
	tm *start = new tm, *end = new tm;
	while(fin.getline(fileInput, MAX_INPUT_SIZE)){
		if(check == 1){
			description = fileInput;
			check = 2;
		}
		else if(check == 2){
			day = fileInput;
			if(strcmpi(day.c_str(), "0") == 0){
				delete start;
				start = NULL;
				check = 7;
			}
			else{
				if(start == NULL)
					start = new tm;
				start->tm_mday = atoi(day.c_str());
				check = 3;
			}

			
		}
		else if(check == 3){
			month = fileInput;
			start->tm_mon = atoi(month.c_str());
			check = 4;
		}
		else if(check == 4){
			year = fileInput;
			start->tm_year = atoi(year.c_str());
			check = 5;
		}
		else if(check == 5){
			hour = fileInput;
			start->tm_hour = atoi(hour.c_str());
			check = 6;
		}
		else if(check == 6){
			min = fileInput;
			start->tm_min = atoi(min.c_str());
			check = 7;

		}
		else if(check == 7){
			day = fileInput;
			if(strcmpi(day.c_str(), "0") == 0){
				delete end;
				end = NULL;
				check = 12;
			}
			else{
				if(end == NULL)
					end = new tm;
				end->tm_mday = atoi(day.c_str());
				check = 8;
			}
			
		}
		else if(check == 8){
			month = fileInput;
			end->tm_mon = atoi(month.c_str());
			check = 9;
		}
		else if(check == 9){
			year = fileInput;
			end->tm_year = atoi(year.c_str());
			check = 10;
		}
		else if(check == 10){
			hour = fileInput;
			end->tm_hour = atoi(hour.c_str());
			check = 11;
		}
		else if(check == 11){
			min = fileInput;
			end->tm_min = atoi(min.c_str());
			check = 12;
		}
		if(check == 12){
		Task *newTask;
		if(end == NULL){
			newTask = new FloatingTask;
			newTask->setDesc(description);
		}
		else if(start == NULL){
			newTask = new DeadlinedTask;
			newTask->setDesc(description);
			newTask->setEnd(end);
		}
		else{
			newTask = new TimedTask;
			newTask->setDesc(description);
			newTask->setEnd(end);
			newTask->setStart(start);
		}

		taskList.push_back(newTask);
		start = end = NULL;
		check = 1;
	  }
	}
	fin.close();
}
void FileIO::writeList(){
	ofstream fout(FileIO::fileName);
	string day, month, year, hour, min;
	char buffer[MAX_INPUT_SIZE];
	for(int i = 0; i < FileIO::taskList.size(); i++){
		fout.write(FileIO::taskList[i]->getDesc().c_str(), strlen(FileIO::taskList[i]->getDesc().c_str())).put('\n');
		if(FileIO::taskList[i]->getStart() == NULL){
			fout.write("0", 1).put('\n');
		}
		else{
			itoa(FileIO::taskList[i]->getStart()->tm_mday, buffer, 10);
			day = buffer;
			fout.write(day.c_str(), strlen(day.c_str())).put('\n');
			itoa(FileIO::taskList[i]->getStart()->tm_mon, buffer, 10);
			month = buffer;
			fout.write(month.c_str(), strlen(month.c_str())).put('\n');
			itoa(FileIO::taskList[i]->getStart()->tm_year, buffer, 10);
			year = buffer;
			fout.write(year.c_str(), strlen(year.c_str())).put('\n');
			itoa(FileIO::taskList[i]->getStart()->tm_hour, buffer, 10);
			hour = buffer;
			fout.write(hour.c_str(), strlen(hour.c_str())).put('\n');
			itoa(FileIO::taskList[i]->getStart()->tm_min, buffer, 10);
			min = buffer;
			fout.write(min.c_str(), strlen(min.c_str())).put('\n');
		}
		if(FileIO::taskList[i]->getEnd()==NULL){
			fout.write("0", 1).put('\n');
		}
		else{
			itoa(FileIO::taskList[i]->getEnd()->tm_mday, buffer, 10);
			day = string(buffer);
			fout.write(day.c_str(), strlen(day.c_str())).put('\n');
			itoa(FileIO::taskList[i]->getEnd()->tm_mon, buffer, 10);
			month = string(buffer);
			fout.write(month.c_str(), strlen(month.c_str())).put('\n');
			itoa(FileIO::taskList[i]->getEnd()->tm_year, buffer, 10);
			year = string(buffer);
			fout.write(year.c_str(), strlen(year.c_str())).put('\n');
			itoa(FileIO::taskList[i]->getEnd()->tm_hour, buffer, 10);
			hour = string(buffer);
			fout.write(hour.c_str(), strlen(hour.c_str())).put('\n');
			itoa(FileIO::taskList[i]->getEnd()->tm_min, buffer, 10);
			min = string(buffer);
			fout.write(min.c_str(), strlen(min.c_str())).put('\n');
		}
	}


	fout.close();

}