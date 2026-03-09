#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 1. The Book Class (The Template)
class Book {
public:
    string id;
    string title;
    string author;
    bool isIssued; 

    // Function to set book details
    void addBook(string bId, string bTitle, string bAuthor) {
        id = bId;
        title = bTitle;
        author = bAuthor;
        isIssued = false; 
    }

    // Function to show book info
    void display() {
        cout << "ID: " << id << " | Title: " << title << " | Author: " << author;
        cout << " | Status: " << (isIssued ? "Issued" : "Available") << endl;
    }
};

int main() {
    Book library[100];
    int bookCount = 0;
    int choice;

    while (true) {
        // 2. The Menu (The Loop)
        cout << "\n--- Library Management System ---" << endl;
        cout << "1. Add Book\n2. Issue Book\n3. Return Book\n4. Display Books\n5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 5) break; 

        switch (choice) {
            case 1: { // ADD BOOK
                string id, title, author;
                cout << "Enter Book ID: "; cin >> id;
                cin.ignore(); 
                cout << "Enter Title: "; getline(cin, title);
                cout << "Enter Author: "; getline(cin, author);
                
                library[bookCount].addBook(id, title, author);
                bookCount++;
                cout << "Book added successfully!" << endl;
                break;
            }
            case 2: { // ISSUE BOOK
                string id;
                cout << "Enter Book ID to issue: "; cin >> id;
                for (int i = 0; i < bookCount; i++) {
                    if (library[i].id == id) {
                        if (!library[i].isIssued) {
                            library[i].isIssued = true;
                            cout << "Book issued successfully!" << endl;
                        } else {
                            cout << "Book is already issued!" << endl;
                        }
                        goto next; 
                    }
                }
                cout << "Book not found!" << endl;
                next: break;
            }
            case 3: { // RETURN BOOK
                string id;
                cout << "Enter Book ID to return: "; cin >> id;
                for (int i = 0; i < bookCount; i++) {
                    if (library[i].id == id) {
                        library[i].isIssued = false;
                        cout << "Book returned successfully!" << endl;
                        goto back;
                    }
                }
                cout << "Book not found!" << endl;
                back: break;
            }
            case 4: { // DISPLAY ALL
                cout << "\n--- Current Inventory ---" << endl;
                for (int i = 0; i < bookCount; i++) {
                    library[i].display();
                }
                break;
            }
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}