#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <limits>
using namespace std;
void loginadmin();
void addteacher();
void adminMenu();
void viewTeachers();
void deleteTeacher();
void loginTeacher();
void teacherMenu(int login);
void addStudent(ofstream& file);
void viewStudent(const string& file,string course);
void viewGrades(const string& file,string course);
void loginStudent();
void Viewcourse(string id, string course, const string& file);
float CGPA(string id, const string& file, float CH);
void assignmarks(const string& file, int login, const string& marks);
bool isValidName(const std::string& name) {
    for (char ch : name) {
        if (!std::isalpha(ch)) {
            return false; // Invalid if non-alphabetic character or non-space is found
        }
    }
    return true; // Valid if all characters are alphabetic or spaces
}
int main(){
    int choice; 
        cout << "^-^-^-^-^-^-^-^-^-^-^-^-^-^-^Welcome to Student Management System^-^-^-^-^-^-^-^-^-^-^-^-^-^-^\n\n";
    
    do {
        //Menu to choose how wants to use the system
        cout << "Choose who is using the system:\n\n";;
        cout << "Press 1  for Admin\n" ;
        cout << "Press 2  for Teacher\n";
        cout << "Press 3  for Student\n";
        cout << "Press 0  to exit program\n\n";;
        cout << "Your choice: ";
        cin >> choice;
        cout << endl;
        cout << setw(85) << setfill('-') << "\n";
        cout << endl << endl;
        switch (choice) {
        case 0: // Exit program
            cout << "\nProgram exited successfully.\n\n";
            break;
        case 1: // Admin
            loginadmin();
            break;
        case 2://teachers
            loginTeacher();
            break;
        case 3://students
            loginStudent();
            break;
        default:
            cout << "\nWrong choice entered!..\n\n";
            continue;//on putting wrong choice error message will pop up and menu will be displayed again
        }
    } while (choice != 0);//system will keep asking for user until the system is exited by entering 0

    return 0;//to exit whole system
}
// Adds a teacher to the file
void addteacher() {
    string ID, name, password, course, courseCode;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard leftover input
    cout << "-------Enter information of teacher you want to add in system-------\n\n";
    bool a=false ;
    do {
        cout << "Enter Teacher name: ";
        getline(cin, name);
        if (!isValidName(name)) {
            cout << "Invalid input\n";
            cin.clear();

        }
        else a = true;
    } while (!a);
    cout << "Enter ID: ";
    getline(cin, ID);
    cout << "Enter password: ";
    getline(cin, password);
    cout << "Enter course name: ";
    getline(cin, course);
    cout << "Enter course code: ";
    getline(cin, courseCode);
    //Declaration of file to write in that
    ofstream FileName("teacher.txt", ios::app);
    if (FileName.is_open()) {//check if file exist/opened or not
        //writing into a file
        FileName << ID << "," << name << "," << password << "," << course << "," << courseCode << "\n";
        FileName.close();//closing file
        cout << "\nTeacher added successfully!\n\n";
    }
    else {//if file doesn't open then error message shows up
        cout << "\nError! File can't open.\n\n";
    }
}

// Displays the admin menu
void adminMenu() {
    int choose;
    do {
        cout << "********************************Admin Menu************************************ \n\n";
        cout << "What you would like to do?\n\n";
        cout << "Press 1 to Add teacher\n";
        cout << "Press 2 to View teachers\n";
        cout << "Press 3 to delete teacher\n";
        cout << "Press 0 to logged out\n\n";
        cout << "Your choice: ";
        cin >> choose;
        cout <<  "\n";
        cout << setw(85) << setfill('-') << "\n";
        cout << endl << endl;
        switch (choose) {
        case 0: // Return to main menu
            cout << "Admin logout successfully!.....\n\n";
            system("cls");
            break;
        case 1://Add teacher function
            addteacher();
            break;
        case 2://view teacher function
            viewTeachers();
            break;
        case 3://delete teacher
            deleteTeacher();
            break;
        default://In case of other inputs
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choose != 0);//will return to main menu when 0 is entered
}

// Admin login function
void loginadmin() {
    const string username1 = "Hassan Ahmed", password1 = "CFD", ID1 = "1234";
    string username, password, ID;
    int failed = 0;
    bool loggedIn = false;

    do {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "****************************Admin Login Page**********************************\n\n";
            cout << "Enter  username: ";
            getline(cin, username);   
        cout << "Enter ID: ";
        cin >> ID;
        cout << "Enter Password: ";
        cin >> password;
        cout << "\n";
        //Check if all the entered value is correct
        if (username == username1 && password == password1 && ID == ID1) {
            cout << "Login successfully!\n\n";
            cout << setw(85) << setfill('-') << "\n";
            cout << endl << endl;
            loggedIn = true;//if correct then bool will become true
        }
        else {//if not correct error message displayed
            cout << "Wrong username, password, or ID! Try again.\n\n";
            cout << setw(85) << setfill('-') << "\n";
            cout << endl << endl;
        }
    } while (!loggedIn);//until bool don't becomes true system will keep on displaying the login page

    adminMenu();//after login display menu of admin
}

// Deletes a teacher by ID
void deleteTeacher() {
    ifstream in("teacher.txt");//open file
    if (!in) {
        cerr << "Error opening file!" << endl;
        return;
    }

    ofstream out("teacher_temp.txt");//declaration of temperory file
    if (!out) {
        cerr << "Error creating temporary file!" << endl;
        return;
    }

    string id;
    cout << "Enter the ID of the teacher to delete: ";
    cin >> id;
    cout << endl;
    string line;
    bool found = false;

    while (getline(in, line)) {
        int a = line.find(',');
        if (a != -1) {
            string currentID = line.substr(0, a);
            if (currentID == id) {
                found = true;
            }
            else {
                out << line << "\n";
            }
        }
    }
    //Closing files
    in.close();
    out.close();

    if (found) {
        remove("teacher.txt");
        rename("teacher_temp.txt", "teacher.txt");
        cout << "Teacher deleted successfully!\n\n";
    }
    else {
        remove("teacher_temp.txt");
        cout << "Teacher with ID " << id << " not found.\n\n";
    }
}
// Views the list of teachers
void viewTeachers() {
    ifstream in("teacher.txt");
    if (!in) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string element;
    bool data = false;

    cout << "\nList of Teachers:\n\n";
    cout << setw(10) << left << "ID"<< setw(20) << left << "Name"<< setw(20) << left << "Password"<< setw(20) << left << "Course"<< setw(20) << left << "Course Code" << endl << endl;
      while (getline(in, element)) {
        int a = element.find(','); //fetches position of first element in a line
        int b = element.find(',', a + 1);//fetches position of second element in a line
        int c = element.find(',', b + 1);//fetches position of third element in a line
        int d = element.find(',', c + 1);//fetches position of fourth element in a line
        if (a != -1 && b != -1 && c != -1 && d != -1) {
            string id = element.substr(0, a);  //makes a substring from 0 index to a
            string name = element.substr(a + 1, b - a - 1);//makes a substring from a index to b
            string password = element.substr(b + 1, c - b - 1);//makes a substring from b index to c
            string course = element.substr(c + 1, d - c - 1);//makes a substring from c index to d
            string courseCode = element.substr(d + 1);//makes a substring from d index till end
         //displays all the info from file on compiler
            cout << setw(10) << left << id << setw(20) << left << name<< setw(20) << left << password << setw(20) << left << course << setw(20) << left << courseCode << endl<<endl;
            data = true;
        }

    }
      cout << setw(85) << setfill('-') << "\n";
      cout << endl << endl;
    //closing file
    in.close();
    if (!data) {// if no data in the file then it will display a message 
        cout << "No teachers found!" << endl<<endl;
        cout << setw(85) << setfill('-') << "\n";
        cout << endl << endl;
    }
}
// Function to add a student to the teacher's file
void addStudent(ofstream& file) {
    string ID, name, password;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard leftover input
    cout << "\n------ Enter information of the student you want to add to the system -------\n\n";
    bool a = false;
    do {
        cout << "Enter Student name: ";
        getline(cin, name);
        if (!isValidName(name)) {
            cout << "Invalid input\n";
            cin.clear();
        }
        else  a = true;
    } while (!a);
    cout << "Enter ID: ";
    getline(cin, ID);
    cout << "Enter password: ";
    getline(cin, password);

    if (file.is_open()) {  // Check if file exists and is open
        file << ID << "," << name << "," << password  << "\n\n";
        cout << "Student added successfully!\n\n";
    }
    else {  // Error handling if file doesn't open
        cout << "Error! File can't be opened.\n\n";
    }
    cout << setw(85) << setfill('-') << "\n";
    cout << endl << endl;
}
//function to delete student
void deleteStudent(const string& teacherFile, const string& tempfile) {
    ifstream file(teacherFile);
    if (!file.is_open()) {
        cerr << "Error opening input file!" << endl;
        return;
    }

    ofstream out(tempfile); // Declaration of temporary file
    if (!out) {
        cerr << "Error creating temporary file!" << endl;
        file.close();
        return;
    }

    string id;
    cout << "Enter the ID of the Student to delete: ";
    cin >> id;

    string line;
    bool found = false;
    // Process each line of the file
    while (getline(file, line)) {
        size_t delimiterPos = line.find(',');
        if (delimiterPos != string::npos) {
            string currentID = line.substr(0, delimiterPos);
            if (currentID == id) {
                found = true; // Mark as found
            }
            else {
                out << line << "\n"; // Write line to temporary file
            }
        }
    }

    // Close the files
    file.close();
    out.close();

    if (found) {
        // Remove the original file and rename the temporary file
        if (remove(teacherFile.c_str()) != 0) {
            cerr << "Error deleting the original file!" << endl;
            return;
        }
        if (rename(tempfile.c_str(), teacherFile.c_str()) != 0) {
            cerr << "Error renaming the temporary file!" << endl;
            return;
        }
        cout << "Student deleted successfully!\n"<<endl;
    }
    else {
        // Delete the temporary file if no match was found
        remove(tempfile.c_str());
        cout << "Student with ID " << id << " not found.\n"<<endl;
    }
    cout << setw(85) << setfill('-') << "\n";
    cout << endl << endl;
}


void viewStudent(const string & file,string course) {
    ifstream in(file);
    if (!in) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string element;
    bool data = false;

    cout << "List of Students regestered in "<<course<<" :\n\n";
    cout << setw(10) << left << "ID"
        << setw(20) << left << "Name"
        << setw(20) << left << "Password" << endl;
    cout << endl;

    while (getline(in, element)) {
        int a = element.find(','); //fetches position of first element in a line
        int b = element.find(',', a + 1);//fetches position of second element in a line
        if (a != -1 && b != -1  ) {
            string id = element.substr(0, a);  //makes a substring from 0 index to a
            string name = element.substr(a + 1, b - a - 1);//makes a substring from a index to b
            string password = element.substr(b + 1);//makes a substring from b index to 
            //displays all the info from file on compiler
            cout << setw(10) << left << id
                << setw(20) << left << name
                << setw(20) << left << password << endl<<endl;
            data = true;
        }

    }
    cout << setw(85) << setfill('-') << "\n";
    cout << endl << endl;
    //closing file
    in.close();

    if (!data) {// if no data in the file then it will display a message 
        cout << "No student found!" << endl;
    }
}


void viewGrades(const string&file,string course) {
    ifstream in(file);
    if (!in) {
        cerr << "Error opening file to view grades!\n";
        return;
    }
    string element;
    bool data = false;

    cout << "Performance of Students in "<<course<<" :\n\n";
    cout<< setw(10) << left << "ID"
        << setw(10) << left << "A1"
        << setw(10) << left << "A2"
        << setw(10) << left << "A3" 
        << setw(10) << left << "Q1" 
        << setw(10) << left << "Q2"
        << setw(10) << left << "Q3"
        << setw(10) << left << "M" << setw(10) << left << "F" 
        << setw(20) << left << "Grade" <<endl;
    cout << endl;

    while (getline(in, element)) {
        int a = element.find(','); 
        int b = element.find(',', a + 1);
        int c = element.find(',', b + 1);
        int d = element.find(',', c + 1);
        int e = element.find(',', d + 1);
        int f = element.find(',', e + 1);
        int g = element.find(',', f + 1);
        int h = element.find(',', g + 1);
        int i = element.find(',', h + 1);
        if (a != -1 && b != -1 && c != -1 && d != -1 && e != -1 && f != -1 && g != -1 && h != -1 && i != -1) {
            string id = element.substr(0, a);  
            string A1= element.substr(a + 1, b - a - 1);
            string A2 = element.substr(b+ 1, c - b - 1);
            string A3 = element.substr(c + 1, d - c - 1);
            string Q1 = element.substr(d + 1, e - d - 1);
            string Q2 = element.substr(e + 1, f - e - 1);
            string Q3 = element.substr(f + 1, g - f- 1);
            string M = element.substr(g + 1, h - g - 1);
            string F = element.substr(h + 1, i - h - 1);
            string Grade = element.substr(i + 1); 
            cout << setw(10) << left << id << setw(10) << left << A1 << setw(10) << left << A2 << setw(10) << left << A3
                << setw(10) << left << Q1 << setw(10) << left << Q2 << setw(10) << left << Q3
                << setw(10) << left << M << setw(10) << left << F << setw(20) << left << Grade << "\n" << endl;;
            data = true;
        }

    }
    cout << setw(85) << setfill('-') << "\n";
    cout << endl << endl;
    //closing file
    in.close();

    if (!data) {// if no data in the file then it will display a message 
        cout << "No student found!" << endl<<endl;
    }
}
//teacher menu function
void teacherMenu(int login) 
{
    ifstream in("teacher.txt");
    if (!in) {
        cerr << "Error opening file!\n";
        return;
    }
    string element, course1, course2, course3;
    for (int i = 1;i <= 3;i++) {
        (getline(in, element));
        int a = element.find(',');
        int b = element.find(',', a + 1);
        int c = element.find(',', b + 1);
        int d = element.find(',', c + 1);
        if (a != -1 && b != -1 && c != -1 && d != -1) {
            if (i == 1) {
                course1 = element.substr(c + 1, d - c - 1);
            }
            if (i == 2) {
                course2 = element.substr(c + 1, d - c - 1);
            }
            if (i == 3) {
                course3 = element.substr(c + 1, d - c - 1);
            }
        }
    }
    in.close();
    int choice;
    string mark, course;
    string teacherFile;
    string  tempfile;
    // Determine the file based on the logged-in teacher
    if (login == 1) teacherFile = "Teacher1.txt";
    else if (login == 2) teacherFile = "Teacher2.txt";
    else if (login == 3) teacherFile = "Teacher3.txt";
    if (login == 1)course = course1;
    else if (login == 2)course = course2;
    else if (login == 3) course = course3;
    if (login == 1) mark = "marks1.txt";
    else if (login == 2) mark = "marks2.txt";
    else if (login == 3) mark = "marks3.txt";
   
    do {
        cout << "**********************************Teacher Menu**********************************";
        cout << "\n\n";
        cout << "What you would like to do?\n\n";
        cout << "1. Add student\n";
        cout << "2. View students\n";
        cout << "3. Delete students\n";
        cout << "4. Assign Marks & Grades \n";
        cout << "5.To view performance and grade\n";
        cout << "0. Logout\n\n";
        cout << "Your choice: ";
        cin >> choice;
    
        cout << setw(85) << setfill('-') << "\n";
        cout << endl << endl;

        switch (choice) {
        case 0:  // Return to main menu
            cout << "Teacher logged out successfully!\n\n";
            break;
        case 1: {  // Add student function
            ofstream file(teacherFile, ios::app);  // Append to the teacher's file
            if (!file) {
                cerr << "Error opening file for writing.\n\n";
                break;
            }
            addStudent(file);
            file.close();
        }
              break;
        case 2://view student function
            viewStudent(teacherFile,course);
            break;
        case 3: { // Delete student function
            if (login == 1) tempfile = "Teacher_temp1.txt";
            if (login == 2) tempfile = "Teacher_temp2.txt";
            if (login == 3) tempfile = "Teacher_temp3.txt";
            deleteStudent(teacherFile, tempfile);
            break;
        }

        case 4:
             assignmarks(teacherFile,login,mark);
             break;
        case 5:
            viewGrades(mark,course);
            break;
        default:
            cout << "Invalid choice! Please try again.\n\n";
        }
    } while (choice != 0);  // Loop until the teacher chooses to log out
}
// Teacher login function
void loginTeacher() {
    string element, id, name, password;
    string id1, name1, password1, id2, name2, password2, id3, name3, password3;

    // Open the teacher file
    ifstream in("teacher.txt");
    if (!in) {
        cerr << "Error opening teacher file!\n\n";
        return;
    }
    // Read teacher data from file
    for (int i = 1; i <= 3; i++) {
        getline(in, element);
        int a = element.find(',');
        int b = element.find(',', a + 1);
        int c = element.find(',', b + 1);
        if (a!=-1 && b!=-1 && c!=-1) {
            if (i == 1) {
                id1 = element.substr(0, a);
                name1 = element.substr(a + 1, b - a - 1);
                password1 = element.substr(b + 1, c - b - 1);
            }
            else if (i == 2) {
                id2 = element.substr(0, a);
                name2 = element.substr(a + 1, b - a - 1);
                password2 = element.substr(b + 1, c - b - 1);
            }
            else if (i == 3) {
                id3 = element.substr(0, a);
                name3 = element.substr(a + 1, b - a - 1);
                password3 = element.substr(b + 1, c - b - 1);
            }
        }
    }
    in.close();
    // Teacher login process
    string inputID, inputUsername, inputPassword, course;
    bool loggedIn = false;
    int login = -1;
    do {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n********************************Teacher Login Page********************************\n\n";
        cout << "Enter username: ";
        getline(cin, inputUsername);
        cout << "Enter ID: ";
        getline(cin, inputID);
        cout << "Enter Password: ";
        getline(cin, inputPassword);
        cout << "\n\n";
        if (inputUsername == name1 && inputPassword == password1 && inputID == id1) {
            loggedIn = true;
            login = 1;
            cout << "Logged in successfully as "<<inputUsername<<"...\n\n";

        }
        else if (inputUsername == name2 && inputPassword == password2 && inputID == id2) {
            loggedIn = true;
            login = 2;
            cout << "Logged in successfully as" <<inputUsername<<"...\n\n";
        }
        else if (inputUsername == name3 && inputPassword == password3 && inputID == id3) {
            loggedIn = true;
            login = 3;
            cout << "Logged in successfully as  " << inputUsername << "...\n\n";
        }
        else {
            cout << "Invalid credentials! Please try again.\n\n";
        }
    } while (!loggedIn);
    // Redirect to the teacher menu
    cout << setw(85) << setfill('-') << "\n";
    cout << endl << endl;
    teacherMenu(login);
}
void studentMenu(string id) {
    ifstream in("teacher.txt");
    if (!in) {
        cerr << "Error opening file!\n";
        return;
    }
    string element, course1, course2, course3;
    for (int i = 1;i <= 3;i++) {
        (getline(in, element));
        int a = element.find(',');
        int b = element.find(',', a + 1);
        int c = element.find(',', b + 1);
        int d = element.find(',', c + 1);
        if (a != -1 && b != -1 && c != -1 && d != -1) {
            if (i == 1) {
                course1 = element.substr(c + 1, d - c - 1);
            }
            if (i == 2) {
                course2 = element.substr(c + 1, d - c - 1);
            }
            if (i == 3) {
                course3 = element.substr(c + 1, d - c - 1);
            }
        }
    }
    in.close();
    int choice;
    float M1, M2, M3;
    float GPA;
    string status;
    cout << setw(85) << setfill('-') << "\n";
    cout << endl << endl;

    do {
        cout  << "****************************************Student Menu**************************************** \n\n";
        cout << "What you would like to do?\n\n";
        cout << "1. View Performance of individual course\n";
        cout << "2. View overall performance & CGPA\n";
        cout << "0. Logout\n\n";
        cout << "Your choice: ";
        cin >> choice;
        system("cls");

        int courseChoice;
        switch (choice) {
        case 0:
            cout << "Student logout successsfully.....\n\n";
            cout << setw(85) << setfill('-') << "\n";
            cout << endl;
            break;
        case 1:
            do {
                cout << "Choose the course whose performance you want to see:\n\n";
                cout << "1. " << course1 << "\n";
                cout << "2. " << course2 << "\n";
                cout << "3. " << course3 << "\n";
                cout << "0. Go back to student menu\n\n";
                cout << "Your choice: ";
                cin >> courseChoice;
                cout << setw(85) << setfill('-') << "\n";
                cout << endl << endl;
                switch (courseChoice) {
                case 0:
                    cout << "\nReturning to student menu........\n\n";
                    break;
                case 1:
                    Viewcourse(id, course1, "marks1.txt");
                    break;
                case 2:
                    Viewcourse(id, course2, "marks2.txt");
                    break;
                case 3:
                    Viewcourse(id, course3, "marks3.txt");
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
                    break;
                }
            } while (courseChoice != 0);
            cout << setw(85) << setfill('-') << "\n";
            cout << endl;
            break;
        case 2:
           M1= CGPA(id, "marks1.txt", 3);
           M2= CGPA(id, "marks2.txt", 1);
           M3 =CGPA(id, "marks3.txt", 2);
          
           Viewcourse(id, course1, "marks1.txt");
           
           Viewcourse(id, course2, "marks2.txt");
       
           Viewcourse(id, course3, "marks3.txt");
           GPA = (M1 + M2 + M3) / 6;
           cout << "CGPA : " << GPA << endl;
           if (GPA >=2) status = "Pass";
           else status = "Fail";
           cout << "Status : " << status << endl<<endl;
           break;
        default:
            cout << "Invalid choice entered. Try again.\n\n";
            break;
        }
    } while (choice != 0);
}
float CGPA(string id, const string& file, float CH) {
        ifstream in(file);
        if (!in) {
            cerr << "Error opening file!\n";
            return 0;
        }
        string line;
        string ids[50], A1[50], A2[50], A3[50];
        string Q1[50], Q2[50], Q3[50];
        string M[50], F[50], Grade[50];
        int count = 0;
        while (getline(in, line) && count < 100) {
            int a = line.find(',');
            int b = line.find(',', a + 1);
            int c = line.find(',', b + 1);
            int d = line.find(',', c + 1);
            int e = line.find(',', d + 1);
            int f = line.find(',', e + 1);
            int g = line.find(',', f + 1);
            int h = line.find(',', g + 1);
            int i = line.find(',', h + 1);
            if (a != -1 && b != -1 && c != -1 && d != -1 && e != -1 && f != -1 && g != -1 && h != -1 && i != -1) {
                ids[count] = line.substr(0, a);
                Grade[count] = line.substr(i + 1);
                count++;
            }
            
        }
        in.close();
        int sum = 0;
        for (int i = 0;i < count;i++) {
            if (id == ids[i]) {
                break;
            }
            sum++;
        }
        float point;
        if (Grade[sum] == "A+") point = 4.0;
        else if (Grade[sum] == "A-")point = 3.7;
        else if (Grade[sum] == "B+")point = 3.3;
        else if (Grade[sum] == "B")point = 3.0;
        else if (Grade[sum] == "B-")point = 3;
        else if (Grade[sum] == "C+")point = 2.3;
        else if(Grade[sum] == "C")point = 2.0;
        else if (Grade[sum] == "D")point = 1.0;
        else  point = 0;
        float GPA;
        GPA= point * CH;
        return GPA;
    }
    void Viewcourse(string id, string course, const string & file) {
    ifstream in(file);
    if (!in) {
        cerr << "Error opening file!\n";
        return;
    }

    string element;
    bool data = false; // Properly initialize the flag
    while (getline(in, element)) {
        int a = element.find(',');
        if (a == -1) continue; // Skip malformed lines

        string recordID = element.substr(0, a);
        if (recordID != id) continue; // Ensure we're processing the correct student

        int b = element.find(',', a + 1);
        int c = element.find(',', b + 1);
        int d = element.find(',', c + 1);
        int e = element.find(',', d + 1);
        int f = element.find(',', e + 1);
        int g = element.find(',', f + 1);
        int h = element.find(',', g + 1);
        int i = element.find(',', h + 1);

        if (b != -1 && c != -1 && d != -1 && e != -1 && f != -1 && g != -1 && h != -1 && i != -1) {
            string A1 = element.substr(a + 1, b - a - 1);
            string A2 = element.substr(b + 1, c - b - 1);
            string A3 = element.substr(c + 1, d - c - 1);
            string Q1 = element.substr(d + 1, e - d - 1);
            string Q2 = element.substr(e + 1, f - e - 1);
            string Q3 = element.substr(f + 1, g - f - 1);
            string M = element.substr(g + 1, h - g - 1);
            string F = element.substr(h + 1, i - h - 1);
            string Grade = element.substr(i + 1);
            cout << "\nPerformance in " << course << ":\n\n";
            cout <<setw(10)<< "No."<< setw(20) << "Assignments" << setw(20) << "Quizzes\n";
            cout << setw(10) << "1" << setw(20) << A1 << setw(20) << Q1 << "\n";
            cout << setw(10) << "2" << setw(20) << A2 << setw(20) << Q2 << "\n";
            cout << setw(10) << "3" << setw(20) << A3 << setw(20) << Q3 << "\n";
            cout << setw(10) << "Mid Exam" << setw(20) << M << "\n";
            cout << setw(10) << "Final Exam" << setw(20) << F << "\n";
            cout << setw(10) << "Grade: " << Grade << "\n"<<endl;
            data = true;
            break; // Stop after finding the record for the current student
        }
    }

    if (!data) {
        cout << "No record found for " << id << " in " << course << ".\n\n";
    }
    cout << setw(85) << setfill('-') << "\n";
    cout << endl << endl;
    in.close();
}

void loginStudent() {
    string id, username, password;
    string element;
    bool login = false;

    do {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<< "*********************************Student Login Page*******************************\n\n";
        cout << "Enter username: ";
        getline(cin, username);
        cout << "Enter Id: ";
        getline(cin, id);
        cout << "Enter password: ";
        getline(cin, password);

        ifstream in("Teacher1.txt");
        if (!in) {
            cerr << "Error opening file!\n";
            return;
        }

        string Id_1, Username_1, Password_1;
        login = false; // Reset login flag for each attempt

        while (getline(in, element)) {
            int a = element.find(',');
            int b = element.find(',', a + 1);

            if (a!=-1&&b!=-1) {
                Id_1 = element.substr(0, a);
                Username_1 = element.substr(a + 1, b- a - 1);
                Password_1 = element.substr(b + 1);

                // Check if credentials match
                if (Id_1 == id && Username_1 == username && Password_1 == password) {
                    cout << "\nLogin as " << username << " successfully.\n\n";
                    login = true;
                    break;
                }
            }
        }

        if (!login) {
            cout << "Invalid credentials. Please try again.\n";
        }
        in.close();
    } while (!login);
    cout << setw(85) << setfill('-') << "\n";
    cout << endl << endl;
    studentMenu(id);
}

void assignmarks(const string& file, int login, const string& marks) {
    float numbers[100][8] = { 0 }; // Array to store marks (max 100 students, 8 marks each)
    string ids[100];            // Array to store IDs of students
    string grades[100];           // Array to store grades for students
    int count = 0;              // Number of students processed
    // Open the input file containing student IDs
    ifstream inFile(file);
    if (!inFile) {
        cerr << "Error: Unable to open input file!" << endl;
        return;
    }
    // Read student IDs from the input file
    string line;
    while (getline(inFile, line)) {
        int a = line.find(',');
        if (a != -1) {
            ids[count] = line.substr(0, a); // Extract student ID
            count++;
        }
    }
    inFile.close();

    if (count == 0) {
        cerr << "Error: No student IDs found in the input file!" << endl;
        return;
    }
    // Input marks for each student
    for (int i = 0; i < count; i++) {
        cout << endl;
        cout << "Enter marks for student ID: " << ids[i] << endl << endl;
        float total = 0; // Reset total for each student
        // Input assignment marks
        for (int j = 0; j < 3; j++) {
            while (true) {
                cout << "Assignment " << j + 1 << " (out of 10): ";
                cin >> numbers[i][j];
                if (numbers[i][j] <= 10) {
                    total += numbers[i][j];
                    break;
                }
                else {
                    cin.clear();
                    cout << "Invalid marks entered.\n";
                    continue;
                }
            }
        }
        // Input quiz marks
        for (int j = 3; j < 6; j++) {
            while (true) {
                cout << "Quiz " << j - 2 << " (out of 10): ";
                cin >> numbers[i][j];
                if (numbers[i][j] <= 10) {
                    total += numbers[i][j];
                    break;
                }
                else {
                    cin.clear();
                    cout << "Invalid marks entered.\n";
                    continue;
                }
            }
        }
        // Input midterm and final marks

        while (true) {
            cout << "Midterm marks (out of 100): ";
            cin >> numbers[i][6];
            if (numbers[i][6] <= 100 && numbers[i][6] > 10) {
                total += numbers[i][6];
                break;
            }
            else {
                cin.clear();
                cout << "Invalid marks entered.\n";
                continue;
            }
            cout << setw(85) << setfill('-') << "\n";
            cout << endl << endl;
        }
        while (true) {
            cout << "Final marks (out of 100): ";
            cin >> numbers[i][7];
            if (numbers[i][7] <= 100 && numbers[i][7] > 10) {
                total += numbers[i][7];
                break;
            }
            else {
                cin.clear();
                cout << "Invalid marks entered.\n";
                continue;
            }
        }
        cout << "\n";
        // Calculate the grade based on average marks
        float average = total * 100 / 260;
        if (average >= 90) {
            grades[i] = "A+";
        }
        else if (average >= 85) {
            grades[i] = "A-";
        }
        else if (average >= 80) {
            grades[i] = "B+";
        }
        else if (average >= 75) {
            grades[i] = "B";
        }
        else if (average >= 74) {
            grades[i] = "B-";
        }
        else if (average >= 65) {
            grades[i] = "C+";
        }
        else if (average >= 60) {
            grades[i] = "C";
        }
        else if (average >= 50) {
            grades[i] = "D";
        }
        else {
            grades[i] = "F";
        }

    }
    // Open the output file to store marks
    ofstream outFile(marks, ios::app);
    if (!outFile) {
        cerr << "Error: Unable to open output file for writing!" << endl;
        return;
    }
    // Write student data to the file
    for (int i = 0; i < count; i++) {
        outFile << ids[i];
        for (int j = 0; j < 8; j++) {
            outFile << "," << numbers[i][j];
        }
        outFile << "," << grades[i] << endl;
    }
    outFile.close();
    cout << "Marks have been successfully stored in  file\n";
    cout << setw(85) << setfill('-') << "\n";
    cout << endl << endl;
}
