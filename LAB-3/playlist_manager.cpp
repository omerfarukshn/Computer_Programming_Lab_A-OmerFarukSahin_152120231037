#include <iostream>
#include <string>
using namespace std;

struct Song {
    string title;
    string artist;
    int ratings[3];
    Song* next;
    Song* prev;

    Song(string t, string a, int r1, int r2, int r3) {
        title = t;
        artist = a;
        ratings[0] = r1;
        ratings[1] = r2;
        ratings[2] = r3;
        next = nullptr;
        prev = nullptr;
    }
};

class Playlist {
private:
    Song* head;
    Song* tail;
    Song* current;

public:
    Playlist() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    // Add song to end of the list
    void addSong(string title, string artist, int r1, int r2, int r3) {
        Song* newSong = new Song(title, artist, r1, r2, r3);

        if (head == nullptr) {
            head = newSong;
            tail = newSong;
            current = newSong;
            return;
        }

        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }

    // Move current to next song
    void nextSong() {
        if (current == nullptr) {
            cout << "Playlist is empty." << endl;
            return;
        }
        if (current->next == nullptr) {
            cout << "Already at the last song." << endl;
            return;
        }
        current = current->next;
        cout << "Now playing: " << current->title << endl;
    }

    // Move current to previous song
    void prevSong() {
        if (current == nullptr) {
            cout << "Playlist is empty." << endl;
            return;
        }
        if (current->prev == nullptr) {
            cout << "Already at the first song." << endl;
            return;
        }
        current = current->prev;
        cout << "Now playing: " << current->title << endl;
    }

    // Remove the current song and reconnect the list
    void removeCurrent() {
        if (current == nullptr) {
            cout << "Nothing to remove." << endl;
            return;
        }

        Song* toDelete = current;

        if (current->prev != nullptr)
            current->prev->next = current->next;
        else
            head = current->next;

        if (current->next != nullptr)
            current->next->prev = current->prev;
        else
            tail = current->prev;

        if (current->next != nullptr)
            current = current->next;
        else
            current = current->prev;

        cout << "\"" << toDelete->title << "\" removed from playlist." << endl;
        delete toDelete;
    }

    // Display all songs, highlight current with ->
    void display() {
        if (head == nullptr) {
            cout << "Playlist is empty." << endl;
            return;
        }

        Song* temp = head;
        while (temp != nullptr) {
            if (temp == current)
                cout << "-> ";
            else
                cout << "   ";

            cout << temp->title << " - " << temp->artist << " | Ratings: ";
            for (int i = 0; i < 3; i++) {
                cout << temp->ratings[i];
                if (i < 2) cout << ", ";
            }
            cout << endl;

            temp = temp->next;
        }
    }

    ~Playlist() {
        Song* temp = head;
        while (temp != nullptr) {
            Song* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
};

int main() {
    Playlist playlist;
    int choice;

    cout << "=== Music Playlist Manager ===" << endl;

    playlist.addSong("Blinding Lights", "The Weeknd", 9, 8, 10);
    playlist.addSong("Shape of You", "Ed Sheeran", 7, 9, 8);
    playlist.addSong("Levitating", "Dua Lipa", 8, 7, 9);
    playlist.addSong("Stay", "The Kid LAROI", 6, 8, 7);

    while (true) {
        cout << "\n--- Playlist ---" << endl;
        playlist.display();
        cout << "\n1. Add Song" << endl;
        cout << "2. Next Song" << endl;
        cout << "3. Previous Song" << endl;
        cout << "4. Remove Current Song" << endl;
        cout << "5. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            string title, artist;
            int r1, r2, r3;
            cout << "Title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Artist: ";
            getline(cin, artist);
            cout << "Ratings from 3 critics: ";
            cin >> r1 >> r2 >> r3;
            playlist.addSong(title, artist, r1, r2, r3);
            cout << "Song added!" << endl;
        } else if (choice == 2) {
            playlist.nextSong();
        } else if (choice == 3) {
            playlist.prevSong();
        } else if (choice == 4) {
            playlist.removeCurrent();
        } else if (choice == 5) {
            cout << "Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice." << endl;
        }
    }

    return 0;
}
