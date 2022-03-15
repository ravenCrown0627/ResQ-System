#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

// Opening system interface
void delay(int milliseconds);
void openingInterface();
// System intro
void systemIntro();
// Searching Boolean
bool searchStaffList(struct StaffNode **head, string ipt_id, string ipt_pws); 
// Login interface
void loginInterface(struct StaffNode** s_head, struct StaffNode** s_tail, struct VictimNode** v_head, struct VictimNode** v_tail);
// Admin interface
void adminInterface(const string &id, struct StaffNode** head, struct StaffNode** tail, struct VictimNode** v_head, struct VictimNode** v_tail);
// Operation for editing staff list
void editStaffInterface(struct StaffNode** head, struct StaffNode** tail); 
void createStaffList(struct StaffNode** head, struct StaffNode** tail);
void insertStaff(struct StaffNode** head, struct StaffNode** tail);
void editStaff(struct StaffNode** head, struct StaffNode** tail);
void deleteStaff(struct StaffNode** head);
void printStaffList(struct StaffNode** head);
void overviewVictimList(struct VictimNode** v_head, struct VictimNode** v_tail);
void writeDataFile(struct StaffNode** head, const string& filename);
void writeFile(struct StaffNode** head, const string& filename);
// Staff interface
void createVictimList(struct VictimNode** head, struct VictimNode** tail);
void staffInterface(const string &id, struct VictimNode** head, struct VictimNode** tail);
void registerVictim(struct VictimNode** head, struct VictimNode** tail);
void mergeSortView(struct VictimNode** head);
// Merge sort inner function 
struct VictimNode* mergeSort(char choice, struct VictimNode** head);
struct VictimNode* middle (struct VictimNode* head);
struct VictimNode* merge(char choice, struct VictimNode *firstNode, struct VictimNode *secondNode);
// Search and update interface
void searchNupdateInterface(struct VictimNode** head, struct VictimNode** tail);
struct VictimNode* searchVictim(struct VictimNode **head, string key);
void updateVictimInterface(struct VictimNode** key);
void printVictimList(struct VictimNode** head);
void sortVictimInterface(struct VictimNode **head);
void writeVictimDataFile(struct VictimNode** head, const string& filename);
void writeVictimFile(struct VictimNode** head, const string& filename);
// Time calculation
int daysElaspedCalculation();
int check_leap_year(int year);
int no_of_days_in_month(int month, int year);
int difference_of_days(int current_day,int current_month, int current_year, int incident_day, int incident_month, int incident_year);

// Staff struct and node
struct Staff
{
  string id;
  string psw;
  string fname;
  string lname;
  string gender;
  string mail_addrs;
};

struct StaffNode 
{
  struct Staff data;
  StaffNode* next;
};

// Victim struct and node
struct Victim
{
  string fname;
  string lname;
  string gender;
  string ic_num;
  string phone_num;
  string parent_phone_num;
  string centre_name;
  string status;
  string time_elapsed;
};

struct VictimNode
{
  struct Victim data;
  VictimNode* next;
};

//Global variable
int staff_num = 0;
int vicitims_num = 0;

int main()
{
  char choice;
  struct StaffNode *staff_l_head = new struct StaffNode; // staff list head
  struct StaffNode *staff_l_tail = new struct StaffNode; // staff list tail
  struct VictimNode *victim_l_head = new struct VictimNode; // victim list head
  struct VictimNode *victim_l_tail = new struct VictimNode; // victim list tail

  staff_l_head = NULL;
  staff_l_tail = NULL;
  victim_l_head = NULL;
  victim_l_tail = NULL;

  createStaffList(&staff_l_head, &staff_l_tail);
  createVictimList(&victim_l_head, &victim_l_tail);
  
  // Choice for login or exit
  while(true)
  {  
    system("CLS");
    // Opening system interface
    openingInterface();
    // System interface
    cout << "Welcome to the ResQ Victim Registration System!\n\n";
    cout << "[1] Login\n";
    cout << "[2] What is ResQ System?\n";
    cout << "[3] Quit\n\n";
    cout << "Choice: ";
    cin >> choice;

    switch (choice)
    {
      case '1':
        system("CLS");
        loginInterface(&staff_l_head, &staff_l_tail, &victim_l_head, &victim_l_tail);
        break;
      case '2':
        system("CLS");
        // System intro
        systemIntro();
        system("pause");
        break;
      case '3':
        cout << "\nThank you for using our system!\n";
        cout << "Have a nice day :)\n";
        system("pause"); 
        exit(1);
        break;
      default:
        cout << "Invalid character! Please try again\n";
        system("PAUSE");
        system("CLS");
        continue;
    } 
  }

  return 0;
}

// Do time delay
void delay(int milliseconds)
{
  // Storing start time 
  clock_t start_time = clock();

  // looping till required time is not achieved 
  while (clock() < start_time + milliseconds);
}

// Opening system interface
void openingInterface() 
{
	string row0  = "              _____                    _____                    _____                   _______        ";  
  string row1  = "             /\\    \\                  /\\    \\                  /\\    \\                 /::\\    \\            ";              
  string row2  = "            /::\\    \\                /::\\    \\                /::\\    \\               /::::\\    \\       "; 
  string row3  = "           /::::\\    \\              /::::\\    \\              /::::\\    \\             /::::::\\    \\             "; 
  string row4  = "          /::::::\\    \\            /::::::\\    \\            /::::::\\    \\           /::::::::\\    \\          "; 
  string row5  = "         /:::/\\:::\\    \\          /:::/\\:::\\    \\          /:::/\\:::\\    \\         /:::/~~\\:::\\    \\     "; 
  string row6  = "        /:::/__\\:::\\    \\        /:::/__\\:::\\    \\        /:::/__\\:::\\    \\       /:::/    \\:::\\    \\    "; 
  string row7  = "       /::::\\   \\:::\\    \\      /::::\\   \\:::\\    \\       \\:::\\   \\:::\\    \\     /:::/    / \\:::\\    \\   "; 
  string row8  = "      /::::::\\   \\:::\\    \\    /::::::\\   \\:::\\    \\    ___\\:::\\   \\:::\\    \\   /:::/____/   \\:::\\____\\        "; 
  string row9  = "     /:::/\\:::\\   \\:::\\____\\  /:::/\\:::\\   \\:::\\    \\  /\\   \\:::\\   \\:::\\    \\ |:::|    |     |:::|    |    "; 
  string row10 = "    /:::/  \\:::\\   \\:::|    |/:::/__\\:::\\   \\:::\\____\\/::\\   \\:::\\   \\:::\\____\\|:::|____|     |:::|____|  "; 
  string row11 = "    \\::/   |::::\\  /:::|____|\\:::\\   \\:::\\   \\::/    /\\:::\\   \\:::\\   \\::/    / \\:::\\   _\\___/:::/    /         "; 
  string row12 = "     \\/____|:::::\\/:::/    /  \\:::\\   \\:::\\   \\/____/  \\:::\\   \\:::\\   \\/____/   \\:::\\ |::| /:::/    /"; 
  string row13 = "           |:::::::::/    /    \\:::\\   \\:::\\    \\       \\:::\\   \\:::\\    \\        \\:::\\|::|/:::/    /"; 
  string row14 = "           |::|\\::::/    /      \\:::\\   \\:::\\____\\       \\:::\\   \\:::\\____\\        \\::::::::::/    /   "; 
  string row15 = "           |::| \\::/____/        \\:::\\   \\::/    /        \\:::\\  /:::/    /         \\::::::::/    /     "; 
  string row16 = "           |::|  ~|               \\:::\\   \\/____/          \\:::\\/:::/    /           \\::::::/    /    "; 
  string row17 = "           |::|   |                \\:::\\    \\               \\::::::/    /             \\::::/____/  "; 
  string row18 = "           \\::|   |                 \\:::\\____\\               \\::::/    /               |::|    |   "; 
  string row19 = "            \\:|   |                  \\::/    /                \\::/    /                |::|____|     "; 
  string row20 = "             \\|___|                   \\/____/                  \\/____/                  ~~         "; 

  cout << row0 << endl;
  delay(30);
  cout << row1 << endl;
  delay(30);
  cout << row2 << endl;
  delay(30);
  cout << row3 << endl;
  delay(30);
  cout << row4 << endl;
  delay(30);
  cout << row5 << endl;
  delay(30);
  cout << row6 << endl;
  delay(30);
  cout << row7 << endl;
  delay(30);
  cout << row8 << endl;
  delay(30);
  cout << row9 << endl;
  delay(30);
  cout << row10 << endl;
  delay(30);
  cout << row11 << endl;
  delay(30);
  cout << row12 << endl;
  delay(30);
  cout << row13 << endl;
  delay(30);
  cout << row14 << endl;
  delay(30);
  cout << row15 << endl;
  delay(30);
  cout << row16 << endl;
  delay(30);
  cout << row17 << endl;
  delay(30);
  cout << row18 << endl;
  delay(30);
  cout << row19 << endl;
  delay(30);
  cout << row20 << endl;
  delay(30);
  cout << endl << endl;
} 

// System introduction
void systemIntro()
{
  cout << "-----------------------------------------------------------------------------------------------\n";
  cout << "|                               ResQ Victim Registration System                               |\n";
  cout << "-----------------------------------------------------------------------------------------------\n\n";
  cout << "\tFloods are one of the most common natural disasters in Malaysia which occur almost\n";
  cout << "every year, particularly during the monsoon season. Peninsular Malaysia's coasts are the most\n";
  cout << "prone to flooding, especially during the northeast monsoon season, which occurs from\n";
  cout << "October to March. Floods are the most frequent and costly natural disaster in the country, \n";
  cout << "causing chaos in affected areas in terms of disruptions to daily and economic activities,\n";
  cout << "causing damage to roads and railway lines, transportation, and property, and even loss of \n";
  cout << "lives. Many people were affected, and some of them remained unknown due to the limited \n";
  cout << "movement to seek for emergency help. With such occurrences predicted to become more \n";
  cout << "frequent in the future, crowd management will be used to control and check the victims and \n";
  cout << "rescuers movements when it happens.\n\n";
  cout << "\tGenerally, crowd management is the systematic and documented planning and \n";
  cout << "direction of the orderly progress of events involving large numbers of people. Measures may \n";
  cout << "be made to guide or restrict the behaviour of groups of people as part of crowd control. \n";
  cout << "However, crowd management will not be able to run efficiently as the data of the victims \n";
  cout << "including the centre and the rescuers are still slow due to the lack of technological advance. \n";
  cout << "Therefore, our teams have come up with an idea to invent a program for the management \n";
  cout << "called \"Res-Q ~ Victims registration system\". Basically, this program has two modes of \n";
  cout << "user which are admin and staff. From the chosen mode, the user can perform variou\n";
  cout << "operations as provided.\n\n";
  cout << "\tWhat makes our program different from the conventional rescue victim system is that\n";
  cout << "it enables rescuers to spend less time looking for victims of the occurrence. This programme \n";
  cout << "allows the admin and staff system to identify the victims. Moreover, the system may be used \n";
  cout << "to update and register new staff or victims. Additionally, the system helps the centre simply\n";
  cout << "monitor the victim's status by providing an overview of the victim's details. Indeed, having \n";
  cout << "this programme will make it much easier for both rescuers and centres to save the victims.\n\n";
}

// Login interface for the user
void loginInterface(struct StaffNode** s_head, struct StaffNode** s_tail, struct VictimNode** v_head, struct VictimNode** v_tail)
{
  // Admin id and psw
  const string admin_id = "admin";
  const string admin_psw = "123456";
  // Input id and psw
  bool flag = true;
  string ipt_id;
  string ipt_psw;

  while(flag)
  {
    cout << "---------------------------------------------------------------------\n";
    cout << "|                           Login System                            |\n";
    cout << "---------------------------------------------------------------------\n\n";
    cout << "Press Q/q to exit the system.\n\n";
    cout << "ID: ";
    cin >> ipt_id;

    if ((ipt_id == "Q" )|| (ipt_id == "q"))
      return;
    
    cout << "Password: ";
    cin >> ipt_psw;

    if (ipt_id == admin_id && ipt_psw == admin_psw)  // The id and password entered is admin
    {
      // Admin system
      cout << "\nAdmin login successfully done!\n";
      system("PAUSE");
      system("CLS");
      adminInterface(admin_id, s_head, s_tail, v_head, v_tail);
      flag = false;
    }
    else if (searchStaffList(s_head, ipt_id, ipt_psw)) // The id and password enterd is registered staff
    {
      // Staff system
      cout << "\nStaff login successfully done!\n";
      system("PAUSE");
      system("CLS");
      staffInterface(ipt_id, v_head, v_tail);
      flag = false;
    }
    else 
    {
      cout << "The ID or password entered is wrong or not in the list.\n";
      cout << "Please try again later..\n\n";
      system("PAUSE");
      system("CLS");
      continue;
    }
  }
}

// Admin interface
void adminInterface(const string &id, struct StaffNode** head, struct StaffNode** tail, struct VictimNode** v_head, struct VictimNode** v_tail)
{
  char choice;
  bool flag = true;

  while(flag)
  {
    system("CLS");
    cout << "---------------------------------------------------------------------\n";
    cout << "|                           Admin System                            |\n";
    cout << "---------------------------------------------------------------------\n\n";
    cout << "Admin ID: " << id;
    cout << "\n\n[1] Edit staff list\n";
    cout << "[2] Overview victim's list\n";
    cout << "[3] Exit\n\n";
    cout << "Choice: ";
    cin >> choice;

    switch(choice)
    {
      case '1':
        system("CLS");
        editStaffInterface(&(*head), &(*tail));
        break;
      case '2':
        // Overview victim's list
        system("CLS");
        overviewVictimList(&(*v_head), &(*v_tail));
        break;
      case '3':
        flag = false;
        system("CLS");
        break;
      default:
        cout << "Invalid character! Please try again\n";
        system("PAUSE");
        system("CLS");
        continue;
    }
  }
}

// Staff editing interface
void editStaffInterface(struct StaffNode** head, struct StaffNode** tail)
{
  char choice;
  bool flag = true;

  while(flag)
  {
    system("CLS");
    cout << "---------------------------------------------------------------------\n";
    cout << "|                         Edit Staff System                         |\n";
    cout << "---------------------------------------------------------------------\n\n";
    cout << "[1] Add staff\n";
    cout << "[2] Edit staff\n";
    cout << "[3] Delete staff\n";
    cout << "[4] Print staff list\n";
    cout << "[5] Exit\n\n";
    cout << "Choice: ";
    cin >> choice;

    switch(choice)
    {
      case '1':
        system("CLS");
        insertStaff(&(*head), &(*tail));
        system("PAUSE");
        break;
      case '2':
        system("CLS");
        editStaff(&(*head), &(*tail));
        system("PAUSE");
        break;
      case '3':
        system("CLS");
        deleteStaff(&(*head));
        system("PAUSE");
        break;
      case '4':
        system("CLS");
        printStaffList(&(*head)); // Print staff list
        system("PAUSE");
        break;
      case '5':
        flag = false;
        system("CLS");
        break;
      default:
        cout << "Invalid character! Please try again\n";
        system("PAUSE");
        system("CLS");
        continue;
    }
  }
}

// Searching the staff list
bool searchStaffList(struct StaffNode **head, string ipt_id, string ipt_psw) //function to search element in the linked list 
{  
  struct StaffNode *temp = *head;

  if(temp == NULL)  
    cout<<"\nEmpty List\n";  
  else  
  {   
    // Linear search --> Search throughout the linked list 
    while(temp!=NULL)  
    {  
      if((temp -> data.id == ipt_id) && (temp -> data.psw == ipt_psw))  //If element is present in the list
        return true;
      else
        temp = temp -> next;
    }
  }  
  
  return false;
}

// Extract staff data from a file
void createStaffList(struct StaffNode** head, struct StaffNode** tail)
{
  string temp;
  ifstream fin("system_staff_list.txt");

  if (fin.is_open() && !fin.eof())
  {
    while (!fin.eof())
    {
      struct StaffNode* newNode = new struct StaffNode;
      
      fin >> newNode -> data.id;
      fin >> newNode -> data.psw;
      fin >> newNode -> data.fname;
      fin >> newNode -> data.lname;
      fin >> newNode -> data.gender;
      fin >> newNode -> data.mail_addrs;

      newNode -> next = NULL;

      if (*head == NULL)
      {
        *head = newNode;
        *tail = newNode;
        staff_num++;
      }
      else
      {
        (*tail) -> next = newNode;
        *tail = newNode;
        staff_num++;
      }
    }
  }
  else
  {
    cerr << "Error detected. No file is found" << endl;
    system("PAUSE");
    exit(1);
  }

  fin.close();
}

// Insert new staff detail into the staff list
void insertStaff(struct StaffNode** head, struct StaffNode** tail)
{
  bool id_flag = true;
  bool psw_flag = true;
  string temp_id;
  string temp_psw;
  string temp_re_psw;
  struct StaffNode *newNode = new struct StaffNode;

  while (id_flag)
  {
    system("CLS");
    cout << "---------------------------------------------------------------------\n";
    cout << "|                           Add New Staff                           |\n";
    cout << "---------------------------------------------------------------------\n\n";
    cout << "Press Q/q to exit the system.\n\n";
    cout << "New staff\n";
    cout << "Staff ID (6-digit): ";
    cin >> temp_id;

    if ((temp_id == "Q" )|| (temp_id == "q"))
      return;
    
    if(temp_id.length() == 6)
    {
      newNode -> data.id = temp_id;
      id_flag = false;
    }
    else
    {
      cout << "The id format must in 6 digit form.\n";
      cout << "Please try again.\n";
      system("PAUSE");
    }

  }
 
  // Ask user to re-enter the password for confirmation
  while(psw_flag)
  {
    cout << "Password: ";
    cin >> temp_psw;
    cout << "Re-enter password: ";
    cin >> temp_re_psw;

    if (temp_psw != temp_re_psw)
    {
      cout << "The re-enter password is incorrect!\n";
      cout << "Please try again\n";
    }
    else
    {
      newNode -> data.psw = temp_psw;
      psw_flag = false;
    }
  } 
  
  // Insert further detail for new staff
  cout << "First Name: ";
  cin >> newNode -> data.fname;
  cout << "Last Name: ";
  cin >> newNode -> data.lname;
  cout << "Gender: ";
  cin >> newNode -> data.gender;
  cout << "E-mail address: ";
  cin >> newNode -> data.mail_addrs;
  cin.clear();

  newNode -> next = (*tail) -> next;
  (*tail) -> next = newNode;
  *tail = newNode;
  staff_num++;

  system("CLS");
  printStaffList(&(*head));
  writeDataFile(&(*head), "system_staff_list.txt");
  writeFile(&(*head), "formated_staff_list.txt");
}

// Edit staff detail in the staff list
void editStaff(struct StaffNode** head, struct StaffNode** tail)
{
  bool inter_flag = true;
  string temp_ipt;
  string new_temp;
  char choice;
  
  do
  {
    struct StaffNode *temp = *head;

    system("CLS");
    cout << "---------------------------------------------------------------------\n";
    cout << "|                         Edit Staff Detail                         |\n";
    cout << "---------------------------------------------------------------------\n\n";
    cout << "Enter the staff id for editing he/she details.\n";
    cout << "Press Q/q to exit the system.\n\n";
    cout << "Staff ID: ";
    cin >> temp_ipt;

    if ((temp_ipt == "Q" )|| (temp_ipt == "q"))
      return;
    
    while(temp != NULL && inter_flag)
    {
      if(temp_ipt != (temp -> data.id))
        temp = temp -> next;
      else if(temp_ipt == (temp -> data.id))
      {
        //Show the detail fo staff selected
        cout << "\nStaff ID:" << temp -> data.id << endl;
        cout << "Password:" << temp -> data.psw << endl;
        cout << "First Name:" << temp -> data.fname << endl;
        cout << "Last Name:" << temp -> data.lname << endl;
        cout << "Gender:" << temp -> data.gender << endl;
        cout << "E-Mail:" << temp -> data.mail_addrs << endl << endl;
        cout << "Is the staff selected is correct? [Y/N]\n";
        cout << "Choice: ";
        cin >> choice;

        if ((choice == 'Y') || (choice == 'y'))
        {
          while (true)
          {
            system("CLS");
            cout << "Which category of the staff detail you would like to edit?\n";
            cout << "[1] Staff ID\n";
            cout << "[2] Password\n";
            cout << "[3] First name\n";
            cout << "[4] Last name\n";
            cout << "[5] Gender\n";
            cout << "[6] E-mail\n";
            cout << "Choice: ";
            cin >> choice;

            switch(choice)
            {
              case '1':
                cout << "Enter the new staff id: ";
                cin >> new_temp;
                temp -> data.id = new_temp;
                system("CLS");
                printStaffList(head);
                return;
                break;
              case '2':
                cout << "Enter the new password: ";
                cin >> new_temp;
                temp -> data.psw = new_temp;
                system("CLS");
                printStaffList(head);
                return;
                break;
              case '3':
                cout << "Enter the new first name: ";
                cin >> new_temp;
                temp -> data.fname = new_temp;
                system("CLS");
                printStaffList(head);
                return;
                break;
              case '4':
                cout << "Enter the new last name: ";
                cin >> new_temp;
                temp -> data.lname = new_temp;
                system("CLS");
                printStaffList(head);
                return;
                break;
              case '5':
                cout << "Enter the new gender: ";
                cin >> new_temp;
                temp -> data.gender = new_temp;
                system("CLS");
                printStaffList(head);
                return;
                break;
              case '6':
                cout << "Enter the new email address: ";
                cin >> new_temp;
                temp -> data.mail_addrs = new_temp;
                system("CLS");
                printStaffList(head);
                return;
                break;
              default:
                cout << "Invalid character! Please try again\n";
                system("PAUSE");
                system("CLS");
                continue;
            }
          }
        }
        else if((choice == 'N') || (choice == 'n'))
          inter_flag = false;
        else
          cout << "Invalid character! Please try again\n";
      }
      else if((temp -> data.id) == ((*tail) -> data.id) && inter_flag)
        delete temp;
    }
  } while(true);

  return;
}

// Delete a staff from the list
void deleteStaff(struct StaffNode** head)
{
  string temp_id;
  string temp_lname;
  char choice;
  bool flag = true;
  bool inter_flag;

  // Check whether the list is empty or not
  if (*head == NULL)
  {
    cout << "The list is empty.\n";
    return;
  }
  
  StaffNode *temp = *head; 
  StaffNode *prev = temp;
  inter_flag = true;

  cout << "---------------------------------------------------------------------\n";
  cout << "|                           Delete Staff                            |\n";
  cout << "---------------------------------------------------------------------\n\n";
  // Ask for the staff id and name to avoid delete wrong staffs
  cout << "Which staff you would like to delete?\n";
  cout << "Press Q/q to exit the system.\n\n";
  cout << "Staff ID: ";
  cin >> temp_id;

  if ((temp_id == "Q" )|| (temp_id == "q"))
    return;

  cout << "Staff last name: ";
  cin >> temp_lname;

  // If head node itself holds
  // the key to be deleted
  if (temp != NULL && temp->data.id == temp_id && temp->data.lname == temp_lname)
  {
    *head = temp->next; // Changed head
    staff_num--;
    delete temp;        // free old head
    cout << endl;
    printStaffList(&(*head));
    return;
  }
  // Else Search for the key to be deleted, 
  // keep track of the previous node as we
  // need to change 'prev->next' */
  else
  {
    while (temp != NULL && temp->data.id != temp_id && temp->data.lname != temp_lname)
    {
      prev = temp;
      temp = temp->next;
    }
    // If key was not present in linked list
    if (temp == NULL)
    {
      cout << "The staff is not in the list.\n";
      cout << "Please try again later.\n";
      return;
    }
      
    // Unlink the node from linked list
    prev->next = temp->next;
    // Free memory
    staff_num--;
    delete temp;
    cout << endl;
    printStaffList(&(*head));
  }
  return;
}

// Print the staff list
void printStaffList(struct StaffNode** head)
{
  struct StaffNode *current = *head;

  if (current == NULL)
  {
    cout << "The list is empty.\n";
    return ;
  }

  cout << "---------------------------------------------------------------------\n";
  cout << "|                            Staff List                              |\n";
  cout << "---------------------------------------------------------------------\n\n";
  cout << left << setw(15) << setfill(' ') << "Staff ID";
  cout << left << setw(15) << setfill(' ') << "Password";
  cout << left << setw(15) << setfill(' ') << "First Name";
  cout << left << setw(15) << setfill(' ') << "Last Name";
  cout << left << setw(15) << setfill(' ') << "Gender";
  cout << left << setw(30) << setfill(' ') << "E-Mail";
  cout << endl;

  do 
  {
    cout << left << setw(15) << setfill(' ') << (current -> data.id);
    cout << left << setw(15) << setfill(' ') << (current -> data.psw);
    cout << left << setw(15) << setfill(' ') << (current -> data.fname);
    cout << left << setw(15) << setfill(' ') << (current -> data.lname);
    cout << left << setw(15) << setfill(' ') << (current -> data.gender);
    cout << left << setw(30) << setfill(' ') << (current -> data.mail_addrs) << endl;
    
    current = current -> next;
  } while (current != NULL);

  cout << "\nTotal number of staff: " << staff_num;
  cout << endl;
}

// Overview the victim list with sort func
void overviewVictimList(struct VictimNode** v_head, struct VictimNode** v_tail)
{
  char choice;
  struct VictimNode** temp = v_head;

  cout << "\nWould you like to sort the list according to category? [Y/N]\n";
  cout << "Choice: ";
  cin >> choice;

  while(true)
  {
    if((choice == 'Y' || choice == 'y'))
    {
      while(true)
      {
        system("CLS");
        cout << "---------------------------------------------------------------------\n";
        cout << "|                   Sort Victim List By Category                    |\n";
        cout << "---------------------------------------------------------------------\n\n";
        cout << "Which category you wish to sort by?\n\n";
        cout << "[1] First Name\n";
        cout << "[2] Last Name\n";
        cout << "[3] IC Number\n";
        cout << "[4] Phone Number\n";
        cout << "[5] Parent's Phone Number\n";
        cout << "[6] Centre Name\n";
        cout << "[7] Status\n";
        cout << "[8] Days Elapsed\n";
        cout << "[9] Exit\n\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice)
        {
          case '1':
            *v_head = mergeSort(choice, &(*temp));
            printVictimList(temp);
            cout << "Storing data...\n";
            writeVictimFile(temp, "victim_sort_by_first_name.txt");
            system("PAUSE");
            break;
          case '2':
            *v_head = mergeSort(choice, &(*temp));
            printVictimList(temp);
            cout << "Storing data...\n";
            writeVictimFile(temp, "victim_sort_by_last_name.txt");
            system("PAUSE");
            break;
          case '3':
            *v_head = mergeSort(choice, &(*temp));
            printVictimList(temp);
            cout << "Storing data...\n";
            writeVictimFile(temp, "victim_sort_by_ic_number.txt");
            system("PAUSE");
            break;
          case '4':
            *v_head = mergeSort(choice, &(*temp));
            printVictimList(temp);
            cout << "Storing data...\n";
            writeVictimFile(temp, "victim_sort_by_phone_number.txt");
            system("PAUSE");
            break;
          case '5':
            *v_head = mergeSort(choice, &(*temp));
            printVictimList(temp);
            cout << "Storing data...\n";
            writeVictimFile(temp, "victim_sort_by_parents_phone_number.txt");
            system("PAUSE");
            break;
          case '6':
            *v_head = mergeSort(choice, &(*temp));
            printVictimList(temp);
            cout << "Storing data...\n";
            writeVictimFile(temp, "victim_sort_by_centre_name.txt");
            system("PAUSE");
            break;
          case '7':
            *v_head = mergeSort(choice, &(*temp));
            printVictimList(temp);
            cout << "Storing data...\n";
            writeVictimFile(temp, "victim_sort_by_status.txt");
            system("PAUSE");
            break;
          case '8':
            *v_head = mergeSort(choice, &(*temp));
            printVictimList(temp);
            cout << "Storing data...\n";
            writeVictimFile(temp, "victim_sort_by_days_elapsed.txt");
            break;
          case '9':
            return;
          default:
            cout << "Invalid character! Please try again\n";
            system("PAUSE");
            system("CLS");
            continue;
        }
      }
    }
    else if((choice == 'N' || choice == 'n'))
      return;
    else
      cout << "Invalid character! Please try again\n";
  }
}

// Overwrite the system data into system file
void writeDataFile(struct StaffNode** head, const std::string& filename = "")
{
  ofstream fout(filename.c_str(), ios::trunc);

  //short break for user to ensure the data is saved
  cout << "Storing data..." << endl;

  struct StaffNode *current = *head;

  do
  {
    fout << (current -> data.id) << " ";
    fout << (current -> data.psw) << " ";
    fout << (current -> data.fname) << " ";
    fout << (current -> data.lname) << " ";
    fout << (current -> data.gender) << " ";
    (current -> next != NULL) ? (fout << (current -> data.mail_addrs) << endl)
                                : (fout << (current -> data.mail_addrs));

    current = current -> next;
  } while (current != NULL);
}

// Write formated data into a file
void writeFile(struct StaffNode** head, const std::string& filename = "")
{
  ofstream fout(filename.c_str(), ios::trunc);

  struct StaffNode *current = *head;

  fout << left << setw(10) << setfill(' ') << "Emp ID";
  fout << left << setw(10) << setfill(' ') << "Password";
  fout << left << setw(10) << setfill(' ') << "First Name";
  fout << left << setw(10) << setfill(' ') << "Last Name";
  fout << left << setw(10) << setfill(' ') << "Gender";
  fout << left << setw(20) << setfill(' ') << "E-Mail";
  fout << endl;

  do
  {
    fout << left << setw(10) << setfill(' ') << (current -> data.id);
    fout << left << setw(10) << setfill(' ') << (current -> data.psw);
    fout << left << setw(10) << setfill(' ') << (current -> data.fname);
    fout << left << setw(10) << setfill(' ') << (current -> data.lname);
    fout << left << setw(10) << setfill(' ') << (current -> data.gender);
    fout << left << setw(20) << setfill(' ') << (current -> data.mail_addrs) << endl;

    current = current -> next;
  } while (current != NULL);

  fout << "\nTotal number of nodes: " << staff_num;
  fout << endl;

  cout << "Data completely stored!" << endl;
  cout << endl;
}

// Create victim linked list
void createVictimList(struct VictimNode** head, struct VictimNode** tail)
{
  string temp;
  ifstream fin("system_victim_list.txt");

  if (fin.is_open() && !fin.eof())
  {
    while (!fin.eof())
    {
      struct VictimNode* newNode = new struct VictimNode;
      
      fin >> newNode -> data.fname;
      fin >> newNode -> data.lname;
      fin >> newNode -> data.gender;
      fin >> newNode -> data.ic_num;
      fin >> newNode -> data.phone_num;
      fin >> newNode -> data.parent_phone_num;
      fin >> newNode -> data.centre_name;
      fin >> newNode -> data.status;
      fin >> newNode -> data.time_elapsed;

      newNode -> next = NULL;

      if (*head == NULL)
      {
        *head = newNode;
        *tail = newNode;
        vicitims_num++;
      }
      else
      {
        (*tail) -> next = newNode;
        *tail = newNode;
        vicitims_num++;
      }
    }
  }
  else
  {
    cerr << "Error detected. No file is found" << endl;
    system("PAUSE");
    exit(1);
  }

  fin.close();
}

// Staff interface
void staffInterface(const string &id, struct VictimNode** head, struct VictimNode** tail)
{
  char choice;
  bool flag = true;
  
  while(flag)
  {
    bool sort_flag = true;
    
    system("CLS");
    cout << "---------------------------------------------------------------------\n";
    cout << "|                           Staff System                            |\n";
    cout << "---------------------------------------------------------------------\n\n";
    cout << "Staff ID: " << id;
    cout << "\n\n[1] Register victim\n";
    cout << "[2] Search and update victim status\n"; // Search -> Confirm -> Ask for update
    cout << "[3] Print victim list\n";
    cout << "[4] Exit\n\n";
    cout << "Choice: ";
    cin >> choice;

    switch(choice)
    {
      case '1':
        system("CLS");
        // Register new victim
        registerVictim(head, tail);
        break;
      case '2':
        system("CLS");
        // Update victim status
        searchNupdateInterface(head, tail);
        break;
      case '3':
        system("CLS");
        // Overview all vitims in the list
        printVictimList(head);
        cout << endl;
        overviewVictimList(head, tail);
        break;
      case '4':
        flag = false;
        system("CLS");
        break;
      default:
        cout << "Invalid character! Please try again\n";
        system("PAUSE");
        system("CLS");
        continue;
    }
  }
}

// Insert new victim detail into the victim list
void registerVictim(struct VictimNode** head, struct VictimNode** tail)
{
  char choice;
  int day_elapsed;
  string temp;
  bool flag = true;
  struct VictimNode *newNode = new struct VictimNode;

  cout << "---------------------------------------------------------------------\n";
  cout << "|                          Register Victim                          |\n";
  cout << "---------------------------------------------------------------------\n\n";
  cout << "Press Q/q to exit the system.\n\n";
  cout << "Fisrt name: ";
  cin >> temp;

  // Check input
  if ((temp == "Q" )|| (temp == "q"))
    return;
  else
    newNode -> data.fname = temp;
  
  cout << "Last name: ";
  cin >> newNode -> data.lname;
  cout << "Gender: ";
  cin >> newNode -> data.gender;
  cout << "IC number: ";
  cin >> newNode -> data.ic_num;
  cout << "Phone number: ";
  cin >> newNode -> data.phone_num;
  cout << "Parent's phone number: ";
  cin >> newNode -> data.parent_phone_num;
  cout << "Centre name: ";
  cin >> newNode -> data.centre_name;
  
  // Choose the status of victim
  while(flag)
  {
    cout << "What is the status of the victim?\n";
    cout << "[1] Survived\n";
    cout << "[2] Missing\n";
    cout << "[3] Deceased\n\n";
    cout << "Choice: ";
    cin >> choice;

    if(choice == '1')
    {
      newNode -> data.status = "Survived";
      flag = false;
    }
    else if(choice == '2')
    {  
      newNode -> data.status = "Missing";
      flag = false;
    }
    else if (choice == '3')
    {  
      newNode -> data.status = "Deceased";
      flag = false;
    }
    else 
      cout << "Invalid character! Please try again\n";
  }
  cout << "Status: " << newNode -> data.status;

  // Calculate the time elapsed
  if(newNode -> data.status != "Deceased")
  {
    day_elapsed = daysElaspedCalculation();
    newNode -> data.time_elapsed = to_string(day_elapsed);
  }
  else
    newNode -> data.time_elapsed = "-";

  cin.clear();

  newNode -> next = (*tail) -> next;
  (*tail) -> next = newNode;
  *tail = newNode;
  vicitims_num++;

  system("CLS");
  printVictimList(&(*head));
  writeVictimDataFile(&(*head), "system_victim_list.txt");
  writeVictimFile(&(*head), "formated_victim_list.txt");
  system("PAUSE");
}

// Merge all the sorted linked list
struct VictimNode* mergeSort(char choice, struct VictimNode** head)
{
  if (((*head) -> next == NULL))
    return *head;

  struct VictimNode* mid = new VictimNode;
  struct VictimNode* tempHead = new VictimNode;

  mid = middle(*head);
  tempHead = mid -> next;
  mid -> next = NULL;

  // recursive call to sort() hence diving our problem, and then merging the solution
  struct VictimNode* sortedList = merge(choice, mergeSort(choice, head), mergeSort(choice, &tempHead));

  return sortedList;
}

// Calculate the middle element in linked list
struct VictimNode* middle (struct VictimNode* head)
{
  struct VictimNode* slow = head;
  struct VictimNode* fast = head -> next;

  while (slow -> next != NULL && (fast != NULL && fast -> next != NULL))
  {
    slow = slow -> next;
    fast = fast -> next -> next;
  }

  return slow;
}

// Sort the given linked list
struct VictimNode* merge(char choice, struct VictimNode *firstNode, struct VictimNode *secondNode)
{
  struct VictimNode* merged = new VictimNode;
  struct VictimNode* temp = new VictimNode;

  // merged is equal to temp so in the end we have the top Node.
  merged = temp;

  // while either firstNode or secondNode becomes NULL
  while (firstNode != NULL && secondNode != NULL)
  {
    switch(choice) 
    {
      case '1':
        if (firstNode -> data.fname < secondNode -> data.fname)
        {
          temp -> next = firstNode;
          firstNode = firstNode -> next;
        }
        else
        {
          temp -> next = secondNode;
          secondNode = secondNode -> next;
        }
        temp = temp -> next;
        break;
      case '2':
        if (firstNode -> data.lname < secondNode -> data.lname)
        {
          temp -> next = firstNode;
          firstNode = firstNode -> next;
        }
        else
        {
          temp -> next = secondNode;
          secondNode = secondNode -> next;
        }
        temp = temp -> next;
        break;
      case '3':
        if (firstNode -> data.ic_num < secondNode -> data.ic_num)
        {
          temp -> next = firstNode;
          firstNode = firstNode -> next;
        }
        else
        {
          temp -> next = secondNode;
          secondNode = secondNode -> next;
        }
        temp = temp -> next;
        break;
      case '4':
        if (firstNode -> data.phone_num < secondNode -> data.phone_num)
        {
          temp -> next = firstNode;
          firstNode = firstNode -> next;
        }
        else
        {
          temp -> next = secondNode;
          secondNode = secondNode -> next;
        }
        temp = temp -> next;
        break;
      case '5':
        if (firstNode -> data.parent_phone_num < secondNode -> data.parent_phone_num)
        {
          temp -> next = firstNode;
          firstNode = firstNode -> next;
        }
        else
        {
          temp -> next = secondNode;
          secondNode = secondNode -> next;
        }
        temp = temp -> next;
        break;
      case '6':
        if (firstNode -> data.centre_name < secondNode -> data.centre_name)
        {
          temp -> next = firstNode;
          firstNode = firstNode -> next;
        }
        else
        {
          temp -> next = secondNode;
          secondNode = secondNode -> next;
        }
        temp = temp -> next;
        break;
      case '7':
        if (firstNode -> data.status < secondNode -> data.status)
        {
          temp -> next = firstNode;
          firstNode = firstNode -> next;
        }
        else
        {
          temp -> next = secondNode;
          secondNode = secondNode -> next;
        }
        temp = temp -> next;
        break;
      case '8':
        if (firstNode -> data.time_elapsed < secondNode -> data.time_elapsed)
        {
          temp -> next = firstNode;
          firstNode = firstNode -> next;
        }
        else
        {
          temp -> next = secondNode;
          secondNode = secondNode -> next;
        }
        temp = temp -> next;
        break;
    }
  }

  // any remaining Node in firstNode or secondNode gets inserted in the temp List
  while (firstNode != NULL)
  {
    temp -> next = firstNode;
    firstNode = firstNode -> next;
    temp = temp -> next; 
  }

  while (secondNode != NULL)
  {
    temp -> next = secondNode;
    secondNode = secondNode -> next;
    temp = temp -> next; 
  }

  // return the head of the sorted list
  return merged -> next;
}

// Update victim status
void searchNupdateInterface(struct VictimNode** head, struct VictimNode** tail)
{
  char choice;
  string temp;
  struct VictimNode *tempNode = *head;
  bool flag = true;

  //loop for user to choose which category required to sort through
  while (flag)
  {
    bool inner_flag = true;

    system("CLS");
    cout << "---------------------------------------------------------------------\n";
    cout << "|                  Search and Update Victim Status                  |\n";
    cout << "---------------------------------------------------------------------\n\n";
    cout << "Which categories you wish to search through?\n\n";
    cout << "[1] Last Name\n";
    cout << "[2] IC Number\n";
    cout << "[3] Phone Number\n";
    cout << "[4] Exit\n\n";
    cout << "Choice: ";
    cin >> choice;
    cout << endl;

    switch (choice)
    {
      case '1':
      {
        printVictimList(&(*head));
        cout << "The last name required to update for: ";
        cin >> temp;

        tempNode = searchVictim(&(*head), temp);
        
        if(tempNode)
        {
          updateVictimInterface(&tempNode);
          printVictimList(&(*head));
          system("PAUSE");
        }
        else
        {
          while(inner_flag)
          {
            cout << "The victim last name" << temp << "is not in the namelist.\n";
            cout << "Would you like to search with another method or register a new victim?\n";
            cout << "[1] Search on another method\n";
            cout << "[2] Register new victim\n";
            cout << "[3] Exit\n\n";
            cout << "Choice: ";
            cin >> choice;
            
            switch(choice)
            {
              case '1':
                inner_flag = false;
                break;
              case '2':
                registerVictim(&(*head), &(*tail));
                printVictimList(&(*head));
                return;
              case '3':
                return;
              default:
                cout << "Invalid character! Please try again\n";
                system("PAUSE");
                system("CLS");
                continue;
            }
          }
        }
        // Write file
        break;
      }
      case '2':
      {
        // *head = mergeSort(choice, &(*head));
        printVictimList(&(*head));
        cout << "The IC number required to update for: ";
        cin >> temp;

        tempNode = searchVictim(&(*head), temp);
        
        if(tempNode)
        {
          updateVictimInterface(&tempNode);
          printVictimList(&(*head));
          system("PAUSE");
        }
        else
        {
          while(inner_flag)
          {
            cout << "The victim ic number" << temp << "is not in the namelist.\n";
            cout << "Would you like to search with another method or register a new victim?\n";
            cout << "[1] Search on another method\n";
            cout << "[2] Register new victim\n";
            cout << "[3] Exit\n\n";
            cout << "Choice: ";
            cin >> choice;

            switch(choice)
            {
              case '1':
                inner_flag = false;
                break;
              case '2':
                registerVictim(&(*head), &(*tail));
                printVictimList(&(*head));
                return;
              case '3':
                return;
              default:
                cout << "Invalid character! Please try again\n";
                system("PAUSE");
                system("CLS");
                continue;
            }
          }
        }
        break;
      }
      case '3':
      {
        // *head = mergeSort(choice, &(*head));
        printVictimList(&(*head));
        cout << "The phone number required to update for: ";
        cin >> temp;

        tempNode = searchVictim(&(*head), temp);
        
        if(tempNode)
        {
          updateVictimInterface(&tempNode);
          printVictimList(&(*head));
          system("PAUSE");
        }
        else
        {
          while(inner_flag)
          {
            cout << "The victim phone number" << temp << "is not in the namelist.\n";
            cout << "Would you like to search with another method or register a new victim?\n";
            cout << "[1] Search on another method\n";
            cout << "[2] Register new victim\n";
            cout << "[3] Exit\n\n";
            cout << "Choice: ";
            cin >> choice;

            switch(choice)
            {
              case '1':
                inner_flag = false;
                break;
              case '2':
                registerVictim(&(*head), &(*tail));
                printVictimList(&(*head));
                return;
              case '3':
                return;
              default:
                cout << "Invalid character! Please try again\n";
                system("PAUSE");
                system("CLS");
                continue;
            }
          }
        }
        break;
      }
      case '4':
        flag = false;
        // system("CLS");
        break;
      default:
        cout << "Invalid character! Please try again\n";
        system("PAUSE");
        system("CLS");
        continue;
    }
  }
}

// Linear search
struct VictimNode* searchVictim(struct VictimNode **head, string key)
{
  struct VictimNode* current = *head; // Initialize current
  
  while (current != NULL)
  {
    if (current -> data.lname == key)
      return current;
    current = current->next;
  }
  return NULL;
}

// Print out victim list
void printVictimList(struct VictimNode** head)
{
  struct VictimNode *current = *head;

  if (current == NULL)
  {
    cout << "The list is empty.\n";
    return ;
  }

  cout << left << setw(15) << setfill(' ') << "First Name";
  cout << left << setw(15) << setfill(' ') << "Last Name";
  cout << left << setw(15) << setfill(' ') << "Gender";
  cout << left << setw(20) << setfill(' ') << "IC Number";
  cout << left << setw(20) << setfill(' ') << "Phone Number";
  cout << left << setw(28) << setfill(' ') << "Parent's Phone Number";
  cout << left << setw(20) << setfill(' ') << "Centre Name";
  cout << left << setw(15) << setfill(' ') << "Status";
  cout << left << setw(15) << setfill(' ') << "Elapsed(days)" << endl;

  do 
  {
    cout << left << setw(15) << setfill(' ') << (current -> data.fname);
    cout << left << setw(15) << setfill(' ') << (current -> data.lname);
    cout << left << setw(15) << setfill(' ') << (current -> data.gender);
    cout << left << setw(20) << setfill(' ') << (current -> data.ic_num);
    cout << left << setw(20) << setfill(' ') << (current -> data.phone_num);
    cout << left << setw(28) << setfill(' ') << (current -> data.parent_phone_num);
    cout << left << setw(20) << setfill(' ') << (current -> data.centre_name);
    cout << left << setw(15) << setfill(' ') << (current -> data.status);
    cout << left << setw(15) << setfill(' ') << (current -> data.time_elapsed) << endl;
    
    current = current -> next;
  } while (current != NULL);

  cout << "\nTotal number of victims: " << vicitims_num;
  cout << endl;
}

// Edit victim detail
void updateVictimInterface(struct VictimNode** key)
{
  string temp;
  int temp_days;
  char choice;
  char status_choice;
  struct VictimNode* tempNode = *key;

  while(true)
  { 
    system("CLS"); 
    cout << "---------------------------------------------------------------------\n";
    cout << "|                      Update Victim Detail                         |\n";
    cout << "---------------------------------------------------------------------\n\n";
    cout << "First Name: " << tempNode -> data.fname << endl;
    cout << "Last Name: " << tempNode -> data.lname << endl;
    cout << "Gender: " << tempNode -> data.gender << endl;
    cout << "IC Number: " << tempNode -> data.ic_num << endl;
    cout << "Phone Number: " << tempNode -> data.phone_num << endl;
    cout << "Parent's Phone Number: " << tempNode -> data.parent_phone_num << endl;
    cout << "Centre Name: " << tempNode -> data.centre_name << endl;
    cout << "Status: " << tempNode -> data.status << endl;
    cout << "Elapsed(days): " << tempNode -> data.time_elapsed << endl;

    cout << "\nDo you like to update the victim information/status? [Y/N]\n";
    cout << "Choice: ";
    cin >> choice;

    if((choice == 'Y') || (choice == 'y'))
    {
      while(true)
      {
        bool flag = true;
        bool inner_flag = true;

        cout << "\nWhich category you wish to edit\n";
        cout << "[1] First Name\n";
        cout << "[2] Last Name\n";
        cout << "[3] IC Number\n";
        cout << "[4] Phone Number\n";
        cout << "[5] Parent's Phone Number\n";
        cout << "[6] Centre Name\n";
        cout << "[7] Status\n";
        cout << "[8] Days Elapsed\n";
        cout << "[9] Exit\n\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice)
        {
          case '1':
            cout << "New first name: ";
            cin >> temp;
            tempNode -> data.fname = temp;
            break;
          case '2':
            cout << "New last name: ";
            cin >> temp;
            tempNode -> data.lname = temp;
            break;
          case '3':
            cout << "New IC number: ";
            cin >> temp;
            tempNode -> data.ic_num = temp;
            break;
          case '4':
            cout << "New phone number: ";
            cin >> temp;
            tempNode -> data.phone_num = temp;
            break;
          case '5':
            cout << "New parent's number: ";
            cin >> temp;
            tempNode -> data.parent_phone_num = temp;
            break;
          case '6':
            cout << "New centre name: ";
            cin >> temp;
            tempNode -> data.centre_name = temp;
            break;
          case '7':
            while(inner_flag)
            {
              cout << "What is the new status?\n";
              cout << "[1] Survived\n";
              cout << "[2] Missing\n";
              cout << "[3] Deceased\n\n";
              cout << "Choice: ";
              cin >> status_choice;

              if(status_choice == '1')
              {
                tempNode -> data.status = "Survived";
                inner_flag = false;
              }
              else if(status_choice == '2')
              {  
                tempNode -> data.status = "Missing";
                inner_flag = false;
              }
              else if (status_choice == '3')
              {  
                tempNode -> data.status = "Deceased";
                inner_flag = false;
              }
              else 
                cout << "Invalid character! Please try again\n";
            }
            break;
          case '8':
            cout << "New day elapsed: ";
            cin >> temp;
            tempNode -> data.time_elapsed = temp_days;
            break;
          case '9':
            return;
          default:
            cout << "Invalid character! Please try again\n";
            system("PAUSE");
            system("CLS");
            continue;
        }

        while (flag)
        {
          cout << "The data is successfully edited!\n";
          cout << "Do you need to edit other detail? [Y/N]\n\n";
          cout << "Choice: ";
          cin >> choice ;

          if ((choice == 'Y') || (choice == 'y'))
          {
            flag = false;
            continue;
          }
          else if ((choice == 'N' )|| (choice == 'n'))
            return;
          else
          {
            cout << "Invalid character! Please try again\n";
            continue;
          }
        }
      }
    }
    else if((choice == 'N') || (choice == 'n'))
      return;
    else
    {
      cout << "Invalid character! Please try again\n";
      continue;
    }
  }
}

// Overwrite the system data into system file
void writeVictimDataFile(struct VictimNode** head, const std::string& filename = "")
{
  ofstream fout(filename.c_str(), ios::trunc);

  //short break for user to ensure the data is saved
  cout << "Storing data..." << endl;

  struct VictimNode *current = *head;

  do
  {
    fout << (current -> data.fname) << " ";
    fout << (current -> data.lname) << " ";
    fout << (current -> data.gender) << " ";
    fout << (current -> data.ic_num) << " ";
    fout << (current -> data.phone_num) << " ";
    fout << (current -> data.parent_phone_num) << " ";
    fout << (current -> data.centre_name) << " ";
    fout << (current -> data.status) << " ";
    (current -> next != NULL) ? (fout << (current -> data.time_elapsed) << endl)
                                : (fout << (current -> data.time_elapsed));

    current = current -> next;
  } while (current != NULL);
}

// Write formated data into a file
void writeVictimFile(struct VictimNode** head, const std::string& filename = "")
{
  ofstream fout(filename.c_str(), ios::trunc);

   struct VictimNode *current = *head;

  if (current == NULL)
  {
    cout << "The list is empty.\n";
    return ;
  }

  fout << left << setw(15) << setfill(' ') << "First Name";
  fout << left << setw(15) << setfill(' ') << "Last Name";
  fout << left << setw(15) << setfill(' ') << "Gender";
  fout << left << setw(20) << setfill(' ') << "IC Number";
  fout << left << setw(20) << setfill(' ') << "Phone Number";
  fout << left << setw(28) << setfill(' ') << "Parent's Phone Number";
  fout << left << setw(20) << setfill(' ') << "Centre Name";
  fout << left << setw(15) << setfill(' ') << "Status";
  fout << left << setw(15) << setfill(' ') << "Elapsed(days)" << endl;

  do 
  {
    fout << left << setw(15) << setfill(' ') << (current -> data.fname);
    fout << left << setw(15) << setfill(' ') << (current -> data.lname);
    fout << left << setw(15) << setfill(' ') << (current -> data.gender);
    fout << left << setw(20) << setfill(' ') << (current -> data.ic_num);
    fout << left << setw(20) << setfill(' ') << (current -> data.phone_num);
    fout << left << setw(28) << setfill(' ') << (current -> data.parent_phone_num);
    fout << left << setw(20) << setfill(' ') << (current -> data.centre_name);
    fout << left << setw(15) << setfill(' ') << (current -> data.status);
    fout << left << setw(15) << setfill(' ') << (current -> data.time_elapsed) << endl;
    
    current = current -> next;
  } while (current != NULL);

  fout << "\nTotal number of victims: " << vicitims_num;

  cout << "Data completely stored!" << endl;
  cout << endl;
}

// Days elapsed calculation
int daysElaspedCalculation()
{
  int incident_day;
  int incident_month;
  int incident_year;
  int n;
  bool flag = true;

  while(flag)
  { 
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    int current_day = now -> tm_mday;
    int current_month = now -> tm_mon+1;
    int current_year = now -> tm_year+1900;

    n = no_of_days_in_month(current_month, current_year);
    
    cout << "Enter the incident date:- \n";
    cout << "Day: ";
    cin >> incident_day;
    cout << "Month: ";
    cin >>incident_month;
    cout << "Year: ";
    cin >> incident_year;

    n = no_of_days_in_month(incident_month, incident_year);

    if((incident_day < 1) || (incident_day > n) || (incident_month < 1) || (incident_month > 12) || (incident_year < 1))
    {
      cout<<"\nEntered date is not valid";
      cout <<"Plase try again later";
      break;
    }
    else
    {
      // Counting the difference between 2 dates in terms of no of days
      int diff = difference_of_days(current_day, current_month, current_year, incident_day, incident_month, incident_year);
      return diff;
      flag = false;
    }
  }
}

// Check leap year
int check_leap_year(int year)
{
  if((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))   //if year is a leap year
    return 1;
  else
    return 0;
}

// Calculate the number of days in a month
int no_of_days_in_month(int month, int year)
{
  // jan, march, may, july, aug, oct, dec contains 31 days
  if((month == 1) || (month == 3) || (month == 5) ||( month == 7) || (month == 8) || (month == 10) || (month == 12))
      return 31;
      
  // april, jun, sept, nov contains 30 days
  if((month == 4) || (month == 6) || (month == 9) || (month == 11))
      return 30;
  
  if(month == 2)
  {
    int n = check_leap_year(year);
    if(n == 1)    // if year is a leap year then Feb will contain 29 days, otherwise it contains 28 days
      return 29;
    else
      return 28;
  }
}

// Calculate the difference between of days
int difference_of_days(int current_day,int current_month, int current_year, int incident_day, int incident_month, int incident_year)
{
  if(current_year == incident_year)
  {
    if(current_month == incident_month)
    {
      if(current_day == incident_day)      //for same dates
        return 0;
      else
        return abs(current_day - incident_day);  //for same year, same month but diff days
    }
    else if(current_month < incident_month)
    {
      int result = 0;

      for(int i = current_month; i < incident_month; i++)
        result = result+no_of_days_in_month(i,current_year);
  
      if(current_day == incident_day)      //for same year, same day but diff month 
        return result;
      else if(current_day < incident_day)
      {
        result = result + (incident_day - current_day);
        return result;
      }
      else
      {
        result = result - (current_day - incident_day);
        return result;
      }
    }
    else
    {
      int result = 0;
      for(int i = incident_month; i < current_month; i++)
        result = result + no_of_days_in_month(i, current_year);
          
      if(current_day == incident_day)
        return result;
      else if(incident_day < current_day)
      {
        result = result + (current_day - incident_day);
        return result;
      }
      else
      {
        result = result - (incident_day - current_day);
        return result;
      }
    }
  }
  else if(current_year < incident_year)
  {
    int temp = 0;

    for(int i = current_year; i < incident_year; i++)
    {
      if(check_leap_year(i))
        temp = temp + 366;
      else
        temp = temp + 365;
    }
    
    if(current_month == incident_month)      
    {
      if(current_day == incident_day)      //for same month, same day but diff year
        return temp;
      else if(current_day < incident_day)
        return temp + (incident_day - current_day);
      else
        return temp - (current_day - incident_day);
    }
    else if(current_month < incident_month)
    {
      int result = 0;

      for(int i = current_month; i < incident_month; i++)
        result = result + no_of_days_in_month(i, incident_year);
          
      if(current_day == incident_day)      // for same day, diff year and diff month
        return temp + result;
      else if(current_day < incident_day)
      {
        result = result + (incident_day - current_day);
        return temp + result;
      }
      else
      {
        result = result - (current_day - incident_day);
        return temp + result;
      }
    }
    else
    {
      int result = 0;
      for(int i = incident_month; i < current_month; i++)
        result = result + no_of_days_in_month(i,incident_year);
          
      if(current_day == incident_day)
        return temp - result;
      else if(incident_day < current_day)
      {
        result = result + (current_day - incident_day);
        return temp - result;
      }
      else
      {
        result = result - (incident_day - current_day);
        return temp - result;
      }
    }
  }
  else
  {
    int temp = 0;

    for(int i = incident_year; i < current_year; i++)
    {
      if(check_leap_year(i))
        temp = temp + 366;
      else
        temp = temp + 365;
    }
      
    if(current_month == incident_month)
    {
      if(current_day == incident_day)      // for same day, same month but diff year
        return temp;
      else if(incident_day < current_day)
        return temp + (current_day - incident_day);
      else
        return temp - (incident_day - current_day);
    }
    else if(incident_month < current_month)
    {
      int result = 0;
    
      for(int i = incident_month; i < current_month; i++)
        result = result + no_of_days_in_month(i,current_year);
          
      if(current_day == incident_day)
        return temp + result;
      else if(incident_day < current_day)
      {
        result = result + (current_day - incident_day);
        return temp + result;
      }
      else
      {
        result = result - (incident_day - current_day);
        return temp + result;
      }
    }
    else
    {
      int result = 0;
      for(int i = current_month; i < incident_month; i++)
        result = result + no_of_days_in_month(i,current_year);
          
      if(current_day == incident_day)      // for same day, diff year and diff month
        return temp - result;
      else if(current_day < incident_day)
      {
        result = result + (incident_day - current_day);
        return temp - result;
      }
      else
      {
        result = result - (current_day - incident_day);
        return temp - result;
      }
    }
  }
}