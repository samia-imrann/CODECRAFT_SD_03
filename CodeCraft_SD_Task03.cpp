#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Contact 
{
    string name;
    string phone;
    string email;
};

class ContactManager 
{
    vector<Contact> contacts;

    void saveToFile() {
        ofstream file("contacts.txt");
        for (int i = 0; i < contacts.size(); i++) {
            file << contacts[i].name << "," << contacts[i].phone << "," << contacts[i].email << endl;
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file("contacts.txt");
        string line;
        while (getline(file, line)) {
            Contact c;
            int pos1 = line.find(',');
            int pos2 = line.find(',', pos1 + 1);
            if (pos1 != -1 && pos2 != -1) {
                c.name = line.substr(0, pos1);
                c.phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
                c.email = line.substr(pos2 + 1);
                contacts.push_back(c);
            }
        }
        file.close();
    }

public:
    ContactManager() {
        loadFromFile();
    }

    void addContact() {
        Contact c;
        cout << "Enter name: ";
        getline(cin, c.name);
        cout << "Enter phone: ";
        getline(cin, c.phone);
        cout << "Enter email: ";
        getline(cin, c.email);
        contacts.push_back(c);
        saveToFile();
        cout << "Contact added.\n";
    }

    void viewContacts() {
        if (contacts.empty()) {
            cout << "No contacts found.\n";
            return;
        }
        for (int i = 0; i < contacts.size(); i++) {
            cout << i + 1 << ". " << contacts[i].name << " | " << contacts[i].phone << " | " << contacts[i].email << endl;
        }
    }

    void editContact() {
        viewContacts();
        cout << "Enter contact number to edit: ";
        int num;
        cin >> num;
        cin.ignore();

        if (num < 1 || num > contacts.size()) {
            cout << "Invalid number.\n";
            return;
        }

        Contact& c = contacts[num - 1];
        string input;

        cout << "New name (leave blank to keep '" << c.name << "'): ";
        getline(cin, input);
        if (!input.empty()) c.name = input;

        cout << "New phone (leave blank to keep '" << c.phone << "'): ";
        getline(cin, input);
        if (!input.empty()) c.phone = input;

        cout << "New email (leave blank to keep '" << c.email << "'): ";
        getline(cin, input);
        if (!input.empty()) c.email = input;

        saveToFile();
        cout << "Contact updated.\n";
    }

    void deleteContact() {
        viewContacts();
        cout << "Enter contact number to delete: ";
        int num;
        cin >> num;
        cin.ignore();

        if (num < 1 || num > contacts.size()) {
            cout << "Invalid number.\n";
            return;
        }

        contacts.erase(contacts.begin() + num - 1);
        saveToFile();
        cout << "Contact deleted.\n";
    }
};

int main() {
    ContactManager cm;
    int choice;

    do {
        cout << "\n--- Contact Manager ---\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Edit Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) cm.addContact();
        else if (choice == 2) cm.viewContacts();
        else if (choice == 3) cm.editContact();
        else if (choice == 4) cm.deleteContact();
        else if (choice == 5) cout << "Exiting program.\n";
        else cout << "Invalid choice.\n";

    } while (choice != 5);

    return 0;
}
