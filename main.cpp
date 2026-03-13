#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 

using namespace std;

class Book {
public:
    string id;
    string title;
    string author;
    bool isIssued;

    void addBook(string bId, string bTitle, string bAuthor, bool issued = false) {
        id = bId;
        title = bTitle;
        author = bAuthor;
        isIssued = issued;
    }

    void display() {
        cout << "| " << left << setw(5) << id 
             << "| " << setw(25) << title 
             << "| " << setw(20) << author 
             << "| " << setw(12) << (isIssued ? "Issued" : "Available") << " |" << endl;
    }

    string toFileData() {
        return id + "," + title + "," + author + "," + (isIssued ? "1" : "0");
    }
};

void saveToFile(Book lib[], int count) {
    ofstream outFile("library.txt");
    for (int i = 0; i < count; i++) {
        outFile << lib[i].toFileData() << endl;
    }
    outFile.close();
}

int loadFromFile(Book lib[]) {
    ifstream inFile("library.txt");
    if (!inFile) return 0;

    int count = 0;
    string id, title, author, issuedStr;
    
    while (getline(inFile, id, ',') && getline(inFile, title, ',') && 
           getline(inFile, author, ',') && getline(inFile, issuedStr)) {
        lib[count].addBook(id, title, author, (issuedStr == "1"));
        count++;
    }
    inFile.close();
    return count;
}

int main() {
    Book library[100]; 
    int bookCount = loadFromFile(library);
    int choice;

    while (true) {
        cout << "\n--- Library Management System ---\n";
        cout << "1. Add Book\n2. Issue Book\n3. Return Book\n4. Display Books\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 5) {
            saveToFile(library, bookCount);
            break;
        }

        switch (choice) {
            case 1: { 
                string id, title, author;
                cout << "Enter Book ID: "; cin >> id;
                cin.ignore(); 
                cout << "Enter Title: "; getline(cin, title);
                cout << "Enter Author: "; getline(cin, author);
                
                library[bookCount].addBook(id, title, author);
                bookCount++;
                saveToFile(library, bookCount);
                cout << "Book added!" << endl;
                break;
            }
            case 2: { 
                string id;
                bool found = false;
                cout << "Enter Book ID: "; cin >> id;
                for (int i = 0; i < bookCount; i++) {
                    if (library[i].id == id) {
                        if (!library[i].isIssued) {
                            library[i].isIssued = true;
                            saveToFile(library, bookCount);
                            cout << "Issued!" << endl;
                        } else {
                            cout << "Already out!" << endl;
                        }
                        found = true;
                        break; 
                    }
                }
                if (!found) cout << "Not found!" << endl;
                break;
            }
            case 3: { 
                string id;
                bool found = false;
                cout << "Enter Book ID: "; cin >> id;
                for (int i = 0; i < bookCount; i++) {
                    if (library[i].id == id) {
                        library[i].isIssued = false;
                        saveToFile(library, bookCount);
                        cout << "Returned!" << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Not found!" << endl;
                break;
            }
            case 4: { 
                cout << "\n+------+--------------------------+---------------------+--------------+" << endl;
                cout << "| ID   | Title                    | Author              | Status       |" << endl;
                cout << "+------+--------------------------+---------------------+--------------+" << endl;
                
                if (bookCount == 0) {
                    cout << "|                No books found!                                       |" << endl;
                } else {
                    for (int i = 0; i < bookCount; i++) {
                        library[i].display();
                    }
                }
                cout << "+------+--------------------------+---------------------+--------------+" << endl;
                break;
            }
            default:
                cout << "Try again!" << endl;
        }
    }
    return 0;
}
