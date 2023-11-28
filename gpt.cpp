#include <iostream>
#include <fstream>
#include <list>
#include <sstream>

using namespace std;

const size_t BUCKET_SIZE = 16;

// HashEntry 구조체 정의
struct HashEntry {
    int key;
};

// 해시 함수
size_t hashFunction(int key) {
    return key % BUCKET_SIZE;
}

// 해시 테이블
list<HashEntry> hashTable[BUCKET_SIZE];

// 해시 테이블 초기화
void initializeHashTable() {
    for (size_t i = 0; i < BUCKET_SIZE; ++i) {
        hashTable[i].clear();
    }
}

// 해시 테이블에 키-값 쌍 추가
void insert(int key) {
    size_t index = hashFunction(key);
    auto& bucket = hashTable[index];

    for (const auto& entry : bucket) {
        if (entry.key == key) {
            cerr << "Duplicate key: " << key << endl;
            return;
        }
    }

    if (bucket.size() < BUCKET_SIZE) {
        bucket.push_back({ key });
    } else {
        cerr << "Overflow: Unable to insert key " << key << endl;
    }
}

// 해시 테이블에서 특정 키에 해당하는 값을 삭제
void remove(int key) {
    size_t index = hashFunction(key);
    auto& bucket = hashTable[index];

    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->key == key) {
            bucket.erase(it);
            return;
        }
    }

    cerr << "Key " << key << " not found" << endl;
}

// 해시 테이블 출력
void display() {
    for (size_t i = 0; i < BUCKET_SIZE; ++i) {
        cout << i << ": ";

        for (const auto& entry : hashTable[i]) {
            cout << entry.key << ", ";
        }

        if (hashTable[i].empty()) {
            cout << "-1";
        }

        cout << endl;
    }
}

int main() {
    ifstream inputFile("commands.txt");

    initializeHashTable();

    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            char command;
            int key;

            if (iss >> command >> key) {
                switch (command) {
                    case 'i':
                        insert(key);
                        break;
                    case 'r':
                        remove(key);
                        break;
                    default:
                        cerr << "Invalid command: " << command << endl;
                        break;
                }
            } else {
                cerr << "Error parsing input line: " << line << endl;
            }
        }

        display();

        inputFile.close();
    } else {
        cerr << "Unable to open input file." << endl;
    }

    return 0;
}
