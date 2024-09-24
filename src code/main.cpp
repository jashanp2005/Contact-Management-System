#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

class Node
{

public:
    string name;
    string number;
    Node *next;

    // constructor
    Node()
    {
        this->name = "";
        this->number = "";
        this->next = NULL;
    }
};

char toLowerCase(char ch)
{
    if (ch >= 'a' && ch <= 'z')
    {
        return ch;
    }
    else if (ch >= 'A' && ch <= 'Z')
    {
        char temp = ch - 'A' + 'a';
        return temp;
    }
    return '#';
}

void print(Node *&head)
{
    int cnt = 0; // To Tell if contact list is empty
    if (head == NULL)
    {
        cout << "Contact List is empty. " << endl;
        return;
    }
    Node *temp = head;

    while (temp != NULL)
    {
        cout << "Name: " << temp->name << "      ";
        cout << "Number: " << temp->number << endl;
        temp = temp->next;
        cnt++;
    }

    if (cnt == 0)
    { // loop never got executed
        cout << "Contact List is empty. " << endl;
    }
    cout << endl;
}

bool isValidNumber(string num)
{
    for (int i = 0; i < num.size(); i++)
    {
        if (num[i] >= '0' && num[i] <= '9')
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

void insertAtHead(Node *&head)
{

    // creation of a new node temp
    Node *temp = new Node();
    cin.ignore();
    cout << "Enter the name: ";
    getline(cin, temp->name);
    cout << "Enter the phone number: ";
    string tempNum;
    cin >> tempNum;
    bool isValid = isValidNumber(tempNum);
    if (isValid)
    {
        temp->number = tempNum;
    }
    else
    {
        cout << "Number is not valid";
        temp->name = "";
    }

    temp->next = head;
    head = temp;
}

void deleteNodeWithValue(Node *&head)
{
    if (head == NULL)
    {
        cout << "Contact list is empty." << endl;
        return;
    }

    string target;
    cout << "Enter Name of the contact to be deleted: ";
    cin.ignore(); // To handle leftover newline from previous input
    getline(cin, target);

    // Convert the target to lowercase for case-insensitive comparison
    for (int i = 0; i < target.size(); i++)
    {
        target[i] = toLowerCase(target[i]);
    }

    Node *temp = head;
    Node *prev = NULL;

    // Traverse the list to find the target node
    while (temp != NULL)
    {
        string lowerName = temp->name;
        for (int i = 0; i < lowerName.size(); i++)
        {
            lowerName[i] = toLowerCase(lowerName[i]);
        }

        if (lowerName == target)
        {
            if (prev == NULL)
            {
                head = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }
            delete temp;
            cout << "Contact deleted successfully." << endl;
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    cout << "Contact with name " << target << " not found." << endl;
}

void search(Node *&head)
{
    int found = 0;
    string target;
    cout << "Enter name of the contact to be searched: " << endl;

    cin.ignore(); // To handle any leftover newline characters from previous input
    getline(cin, target);

    // Convert the target name to lowercase
    for (int i = 0; i < target.size(); i++)
    {
        target[i] = toLowerCase(target[i]);
    }

    Node *current_node = head;
    while (current_node)
    {
        string lowerName = current_node->name;
        for (int i = 0; i < lowerName.size(); i++)
        {
            lowerName[i] = toLowerCase(lowerName[i]);
        }

        if (lowerName == target)
        {
            cout << "The contact is found." << endl;
            cout << "Name is: " << current_node->name << endl;
            cout << "Number is: " << current_node->number << endl;
            found++;
        }
        current_node = current_node->next;
    }

    if (found == 0)
    {
        cout << "Contact not found" << endl;
    }
}

int getLength(Node *head)
{
    int len = 0;
    Node *temp = head;

    while (temp != NULL)
    {
        len++;
        temp = temp->next;
    }
    return len;
}

void update(Node *&head)
{
    string target, newName, newNumber;
    cout << "Enter the name of contact to be edited: ";
    cin.ignore(); // To handle any leftover newline characters from previous input
    getline(cin, target);

    for (int i = 0; i < target.size(); i++)
    {
        target[i] = toLowerCase(target[i]);
    }

    Node *temp = head;
    bool found = false;

    while (temp != NULL)
    {
        string lowerName = temp->name;
        for (int i = 0; i < lowerName.size(); i++)
        {
            lowerName[i] = toLowerCase(lowerName[i]);
        }

        if (lowerName == target)
        {
            cout << "Contact found." << endl;
            cout << "Enter new name (or press Enter to keep the current name): ";
            getline(cin, newName);

            if (!newName.empty())
            {
                temp->name = newName;
            }

            cout << "Enter new number (or press Enter to keep the current number): ";
            getline(cin, newNumber);

            if (!newNumber.empty())
            {
                if (isValidNumber(newNumber))
                {
                    temp->number = newNumber;
                }
                else
                {
                    cout << "Invalid number. The contact update was canceled." << endl;
                    return;
                }
            }

            found = true;
            break;
        }
        temp = temp->next;
    }

    if (!found)
    {
        cout << "Contact with the name " << target << " not found." << endl;
    }
    else
    {
        cout << "Contact updated successfully." << endl;
    }
}

void copyToFile(Node *&head)
{
    ofstream outputFile("jp.txt", ios::out | ios::trunc);

    if (outputFile.is_open())
    {
        Node *temp = head;
        while (temp != NULL)
        {
            outputFile << temp->name << "," << temp->number << endl;
            temp = temp->next;
        }

        outputFile.close();
        cout << endl
             << "Data has been written to the file successfully." << endl
             << endl;
    }
    else
    {
        cout << "Error: Unable to open the file." << endl;
    }
}

int main()
{

    int length = 0;
    Node *head = NULL;
    Node *tail = NULL;

    ifstream myFileStream("jp.txt");

    if (!myFileStream.is_open())
    {
        cout << "Failed to open file" << endl;
        return 0;
    }

    string line;
    while (getline(myFileStream, line))
    {
        stringstream ss(line);
        string name, number;
        getline(ss, name, ',');
        getline(ss, number, ',');

        Node *newNode = new Node();
        newNode->name = name;
        newNode->number = number;

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    myFileStream.close();

    int operation;
    cout << endl;
    cout << " CONTACT MANAGEMENT SYSTEM APPLICATION " << endl;
    cout << endl
         << endl;
    cout << "  ---------- CONTACT LIST ---------- " << endl;
    cout << endl;
    cout << "S.NO    " << "FUNCTIONS                    " << endl;
    cout << endl;
    cout << " 1      " << "Insert Contact               " << endl;
    cout << " 2      " << "Delete Contact               " << endl;
    cout << " 3      " << "Search Contact               " << endl;
    cout << " 4      " << "Update Contact               " << endl;
    cout << " 5      " << "Display Contacts             " << endl;
    cout << " 6      " << "Exit                         " << endl;
    cout << endl;

    bool flag = true;

    while (flag)
    {
        cout << endl
             << endl;
        cout << "Please enter the S.NO of function you want to do: ";
        cin >> operation;

        switch (operation)
        {
        case 1:
            insertAtHead(head);
            copyToFile(head); // Save after insertion
            break;

        case 2:
            deleteNodeWithValue(head);
            copyToFile(head); // Save after deletion
            break;

        case 3:
            search(head);
            break;

        case 4:
            update(head);
            copyToFile(head); // Save after update
            break;

        case 5:
            print(head);
            break;

        case 6:
            copyToFile(head); // Save before exiting
            flag = false;
            break;

        default:
            cout << "Invalid S.NO" << endl;
        }
    }

    return 0;
}