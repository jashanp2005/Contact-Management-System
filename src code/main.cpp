#include <iostream>
#include<sstream>
#include<fstream>
using namespace std;

class Node {

    public:
    string name;
    string number;
    Node* next;

    //constructor
    Node() {
      this->name = "";
      this->number = "";
      this->next = NULL;
    }

};

char toLowerCase(char ch){
    if(ch>='a' && ch<='z'){
        return ch;
    }
    else if(ch>='A' && ch<='Z'){
        char temp = ch - 'A' + 'a';
        return temp;
    }
  return '#';
}

void print(Node* &head) {
    int cnt = 0;     // To Tell if contact list is empty    
    if(head == NULL) {
        cout << "Contact List is empty. " << endl;
        return ;
    }
    Node* temp = head -> next;

    while(temp != NULL && temp -> name != "") {
        cout << "Name: " << temp -> name << "      ";
        cout << "Number: " << temp -> number << endl;
        temp = temp -> next;
        cnt++;
    }
    if(cnt == 0){        // loop never got executed
      cout << "Contact List is empty. " << endl;
  }
    cout << endl;
}

bool isValidNumber(string num){
  for(int i =0; i<num.size(); i++){
    if(((int)num[i]>=48 && (int)num[i]<=57)){
      continue;
    }
    else{
      return false;
    }
  }
  return true;
}

void insertAtHead(Node* &head) {

    // creation of a new node temp
  Node* temp = new Node();
    cin.ignore();
    cout << "Enter the name: ";
    getline(cin, temp -> name);
    cout << "Enter the phone number: ";
    string tempNum;
    cin>>tempNum;
    bool isValid = isValidNumber(tempNum);
    if(isValid){
    temp -> number = tempNum;
  }
  else{
    cout<<"Number is not valid";
    temp->name="";
  }

    temp -> next = head;
    head = temp;
}


void deleteNodeWithValue(Node*& head) {

    string target;
    cout << "Enter Name of the contact to be deleted: " << endl;
    cin >> target;

    for(int i =0; i<target.size(); i++){
        target[i] = toLowerCase(target[i]);
    }

    // when the linked list is empty
    if (head == NULL) {
        cout << "Contact list is empty." << endl;
        return;
    }

    // when node to be deleted is head node
    if (head -> name == target) {
        Node* temp = head;
        head = head -> next;
        delete temp;
        return;
    }

    // Traverse the linked list to find the node before the target node
    Node* current = head;
    while (current -> next != NULL && (current -> next) -> name != target) {
        current = current -> next;
    }

    // Check if the target node was found
    if (current -> next == NULL) {
        cout << "Contact with name " << target << " not found in the Contact list." << endl;
        return;
    }

    // Delete the target node
    Node* temp = current -> next;
    current -> next = (current -> next) -> next;
    delete temp;
}


void search(Node* & head) {
    int found = 0;
    string target;
    cout << "Enter name of the contact to be searched: "<<endl;
    cin>>target;

    for(int i =0; i<target.size(); i++){
        target[i] = toLowerCase(target[i]);
    }

        Node* current_node = head;
        while (current_node) {
            if (current_node -> name == target) {
            cout << "The contact is found. " << endl;
            cout << "Name is: " << current_node -> name << endl;
            cout << "Number is: " << current_node -> number << endl;
            found++;
            }
            current_node = current_node -> next;
        }
        if(found == 0){
        cout << "Contact not found" << endl;
    }
}

int getLength(Node* head) {
    int len = 0;
    Node* temp  = head -> next ;

    while(temp != NULL && temp -> name != "") {
        len++;
        temp  = temp -> next;
    }
    return len;
}


void update(Node* & head) {
    string target, newName, newNumber;
    cin.ignore();
    cout<<"Enter the name of contact to be edited: ";
    getline(cin,target);

    for(int i =0; i<target.size(); i++){
        target[i] = toLowerCase(target[i]);
    }

    Node* temp  = head ;

    while(temp != NULL) {
        if(temp -> name == target){
            cout << endl << "Enter new name: ";
            cin >> newName;
            cout << endl << "Enter new Number: ";
//            cin>>newNumber;
            string tempNum;
        cin>>tempNum;

        bool isValid = isValidNumber(tempNum);
        if(isValid){
          temp -> name = newName;
          temp -> number = tempNum;
      }
      else{
        cout<<"Number is not valid";
        break;
      }
        }
        else{
        temp  = temp -> next;
    }
    cout << endl;
}
}


void copyToFile(Node* & head){
  ofstream outputFile;

    outputFile.open("jp.txt", ios::out | ios::trunc);

    if (outputFile.is_open()) {

        while(head != NULL){

          if(head -> name == ""){
            head = head->next;
      }

        outputFile << head -> name << ",";
        outputFile << head -> number << endl;
        head = head -> next;
        }

        outputFile.close();
        cout << endl<< "Data has been written to the file successfully." << endl << endl;
    } 

    else {
        cout << "Error: Unable to open the file." <<endl;
    }
}


int main() {

int length=0; //will be used in counting case

ifstream myFileStream("jp.txt");

  if(!myFileStream.is_open()){
    cout << "Failed to open file" << endl;
    return 0;
  }

  string line;

    Node* newNode = new Node();
    Node* head = newNode;

    while(getline(myFileStream, line)){

    stringstream ss(line);

    getline(ss, head -> name, ',');   
    //it will take the text of the line in name untill a  comma(,) will come.
    getline(ss, head -> number, ',');

    Node* temp = new Node();    //adding a new node everytime
    temp -> next = head;
      head = temp;
  }

    int operation;
//    bool check = true;
//while(check){

    //Interface Creation
    cout<<endl;
    cout<<" CONTACT MANAGEMENT SYSTEM APPLICATION "<<endl;
    cout<<endl<<endl;
    cout<<"  ---------- CONTACT LIST ---------- "<<endl;
    cout<<endl;
    cout<<"S.NO    "<<"FUNCTIONS                    "<<endl;
    cout<<endl;
    cout<<" 1      "<<"Insert Contact               "<<endl;
    cout<<" 2      "<<"Delete Contact               "<<endl;
    cout<<" 3      "<<"Update Contact               "<<endl;
    cout<<" 4      "<<"Search Contact               "<<endl;
    cout<<" 5      "<<"Count Contacts               "<<endl;
    cout<<" 6      "<<"Show All Contacts            "<<endl;
    cout<<" 7      "<<"Exit                         "<<endl;
    cout<<"Enter the operation(1-7): ";

    cin>>operation;
    cout<<endl;

    switch(operation){

        case 1: 
        insertAtHead(head);
        copyToFile(head);
        break;

        case 2: 
        deleteNodeWithValue(head);
        copyToFile(head);
        break;

        case 3: 
        update(head);
        copyToFile(head);
        break;

        case 4: 
        search(head);
        break;

        case 5: 
        length = getLength(head);
        cout << "Total contacts are: " << length << endl;
        break;

        case 6:
        print(head);
        break;

        case 7:
        //check = false;
        break;

    //}
}
    return 0;
}