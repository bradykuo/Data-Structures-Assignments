#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <clocale> // For setlocale
using namespace std;

class ListNode {
public:
    char data;
    ListNode* next;
    ListNode() : data(0), next(0) {};
    ListNode(char a) : data(a), next(0) {};
};

class LinkedList {
public:
    ListNode* first = nullptr;
    ListNode* temp;
    char player = '\0';
    
    void Printcurrent();
    void Push_back(char x);
    void Delete(char x);
};

void LinkedList::Printcurrent() {
    if (!first) return;
    cout << temp->data;
    player = temp->data;
    temp = (temp->next) ? temp->next : first;
}

void LinkedList::Push_back(char x) {
    ListNode* newNode = new ListNode(x);
    if (!first) {
        first = newNode;
        newNode->next = first;
        return;
    }
    ListNode* current = first;
    while (current->next != first) {
        current = current->next;
    }
    current->next = newNode;
    newNode->next = first;
}

void LinkedList::Delete(char x) {
    if (!first) return;
    ListNode* current = first;
    ListNode* prev = nullptr;
    
    do {
        if (current->data == x) {
            if (current == first) {
                if (current->next == first) {
                    delete current;
                    first = nullptr;
                    return;
                }
                ListNode* last = first;
                while (last->next != first) last = last->next;
                first = first->next;
                last->next = first;
                delete current;
            } else {
                prev->next = current->next;
                delete current;
            }
            return;
        }
        prev = current;
        current = current->next;
    } while (current != first);
}

int main() {
    // Set locale for UTF-8 support
    setlocale(LC_ALL, ""); 
    
    // Open the data file
    ifstream ifs("data.txt");
    if (!ifs) {
        cout << "無法開啟檔案 data.txt\n";
        return 1;
    }

    // Read the number of words per topic
    int n[10];
    for (int i = 0; i < 10; i++) {
        ifs >> n[i];
    }

    // Read topics and their words
    string topics[10][1000];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < n[i] + 1; j++) {
            ifs >> topics[i][j];
        }
    }

    int playerCount;
    cout << "請輸入遊戲人數(2~10人): ";
    cin >> playerCount;

    // Seed random number generator
    srand(time(nullptr));

    // Initialize the player list
    LinkedList list;
    for (int i = 0; i < playerCount; i++) {
        list.Push_back('A' + i);
    }

    // Initialize game variables
    bool usedTopics[10] = {false};
    int round = 1;
    char lastPlayer;

    // Game loop
    while (round < playerCount) {
        cout << "第" << round << "回合\n";

        // Pick a random unused topic
        int topicIndex;
        do {
            topicIndex = rand() % 10;
        } while (usedTopics[topicIndex]);
        usedTopics[topicIndex] = true;

        // Display the chosen topic
        cout << "主題: " << topics[topicIndex][0] << endl;
        list.temp = list.first;

        bool usedWords[1000] = {false};
        bool eliminated = false;

        // Round loop
        while (!eliminated) {
            int wordIndex = (rand() % (n[topicIndex] - 1)) + 1;
            list.Printcurrent();
            cout << ": " << topics[topicIndex][wordIndex];

            if (usedWords[wordIndex]) {
                char eliminatedPlayer = list.player;
                cout << "\n" << eliminatedPlayer << " >> 淘汰，倖存選手: ";
                
                ListNode* current = list.first;
                bool firstOutput = true;
                do {
                    if (current->data != eliminatedPlayer) {
                        if (!firstOutput) cout << ", ";
                        cout << current->data;
                        firstOutput = false;
                    }
                    current = current->next;
                } while (current != list.first);

                cout << endl;
                list.Delete(eliminatedPlayer);
                eliminated = true;
                lastPlayer = list.first->data;
            } else {
                cout << " > ";
                usedWords[wordIndex] = true;
            }
        }
        round++;
    }

    // Output the final winner
    cout << "最終獲勝者: " << lastPlayer << endl;

    return 0;
}