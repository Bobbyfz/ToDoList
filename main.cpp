#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
using namespace std;

void printTasks(fstream& file);
void addTask(fstream& file);
void finishTask(fstream& file,string fName);

int main (int argc, char** argv)
{
    fstream file;
    string fileName;
    int choice;
    
    cout <<"-------------------- Welcome to ToDo list maker --------------------" << endl << endl;
    
    do
    {
        
        cout << "Please name of text file (don't include .txt): ";
        cin >> fileName;
        fileName = fileName + ".txt";
        file.open(fileName,fstream::in | fstream::out | fstream:: app);
        
        
    }while (!file.is_open());
    
    do
    {
        cout << "----------- Main Menu -----------" << endl << endl;
        cout << "What would you like to do?" << endl << "1. View All Tasks" << endl << "2. Add Tasks" << endl << "3. Finish Task" << endl << "0. Exit" << endl;
        cin >> choice;
        
        switch (choice)
        {
            case (1):
                printTasks(file);
                break;
            case (2):
                addTask(file);
                break;
            case (3):
                printTasks(file);
                finishTask(file,fileName);
                file.open(fileName,fstream::in | fstream::out | fstream:: app);
                break;
            case (0):
                break;
            default:
                cout << "Not an option, please select a valid option" << endl;
                continue;
        }
    } while (choice != 0);
    
    file.close();
    file.close();
    cout << "Thank you for making your todo list!" << endl;
    return 0;
}

void printTasks(fstream& file)
{
    file.seekg(0);
    string task;
    int i = 1;
    cout << "---------- Current Tasks ----------" << endl << endl;
    while (getline(file,task))
    {
        cout << i << ". " << task << endl;
        i++;
    }
    //resets the end of file flag and resets file to beginning of file
    file.ios_base::clear();
    file.seekg(0);
}

void addTask(fstream& file)
{
    string task;
    cout << "What task would you like to add? (0 to exit): ";
    //reads until 0 is entered from the user
    getline(cin,task);
    while (getline(cin,task))
    {
        if (task == "0")
        {
            break;
        }
        cout << "Anything else? (0 to exit): ";
        file << task << endl;
    }
    
}


void finishTask(fstream& file,string fName)
{
    int lineNum;
    string task;
    int lineCount = 1;
    char c;
    
    fstream temp;
    temp.open("temp.txt", ofstream::out);
    
    cout << "What task would you like to delete? (0 to exit): ";
    cin >> lineNum;
    
    while (file.get(c) && lineNum != 0)
    {
        if (c == '\n')
        {
            lineCount++;
        }
        if (lineCount != lineNum)
        {
            temp << c;
        }
    }
    
    file.close();
    temp.close();
    
    
    
    remove(fName.c_str());
    
    rename("temp.txt",fName.c_str());
}
