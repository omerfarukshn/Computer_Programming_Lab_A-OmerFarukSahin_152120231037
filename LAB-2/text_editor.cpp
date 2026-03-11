#include <iostream>
#include <string>
using namespace std;

// Node structure for Single Linked List
struct Node {
    string data;
    Node* next;

    Node(string word) {
        data = word;
        next = nullptr;
    }
};

// Text Editor class using Single Linked List
class TextEditor {
private:
    Node* head;

public:
    TextEditor() {
        head = nullptr;
    }

    // Add word to the end of the list (Append)
    void addWord(string word) {
        Node* newNode = new Node(word);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    // Undo - Delete the last word from the list
    void undo() {
        if (head == nullptr) {
            cout << "Nothing to undo!" << endl;
            return;
        }

        // If only one node exists
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            cout << "Last word removed." << endl;
            return;
        }

        // Find the second-to-last node
        Node* current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }

        // Delete the last node
        delete current->next;
        current->next = nullptr;
        cout << "Last word removed." << endl;
    }

    // Display the linked list
    void display() {
        if (head == nullptr) {
            cout << "NULL" << endl;
            return;
        }

        Node* current = head;
        while (current != nullptr) {
            cout << "[" << current->data << "]";
            if (current->next != nullptr) {
                cout << " -> ";
            }
            current = current->next;
        }
        cout << " -> NULL" << endl;
    }

    // Destructor to free memory
    ~TextEditor() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main() {
    TextEditor editor;
    string input;

    cout << "=== Simple Text Editor ===" << endl;
    cout << "Commands:" << endl;
    cout << "  - Type any word to add it to the text" << endl;
    cout << "  - Type 'UNDO' to remove the last word" << endl;
    cout << "  - Type 'EXIT' to quit the program" << endl;
    cout << "===========================" << endl << endl;

    while (true) {
        cout << "Current text: ";
        editor.display();
        cout << "Enter word: ";
        cin >> input;

        if (input == "EXIT") {
            cout << "Exiting program. Goodbye!" << endl;
            break;
        } else if (input == "UNDO") {
            editor.undo();
        } else {
            editor.addWord(input);
        }

        cout << endl;
    }

    return 0;
}
