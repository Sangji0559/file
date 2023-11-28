#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <algorithm>

const size_t BUCKET_SIZE = 16;

// HashEntry 구조체 정의
struct HashEntry {
    int key;
};

// 해시 함수
size_t hashFunction(int key) {
    return key % BUCKET_SIZE;
}

// 해시 테이블 초기화
void initializeHashTable(std::list<HashEntry> hashTable[]) {
    for (size_t i = 0; i < BUCKET_SIZE; ++i) {
        hashTable[i].clear();
    }
}

// 해시 테이블에 키-값 쌍 추가
void insert(int key, std::list<HashEntry> hashTable[]) {
    size_t index = hashFunction(key);
    auto& bucket = hashTable[index];

    auto it = std::find_if(bucket.begin(), bucket.end(), [key](const HashEntry& entry) {
        return entry.key == key;
    });

    if (it == bucket.end() && bucket.size() < BUCKET_SIZE) {
        bucket.push_back({ key });
    } else if (it != bucket.end()) {
        std::cerr << "Duplicate key: " << key << std::endl;
    } else {
        std::cerr << "Overflow: Unable to insert key " << key << std::endl;
    }
}

// 해시 테이블에서 특정 키에 해당하는 값을 삭제
void remove(int key, std::list<HashEntry> hashTable[]) {
    size_t index = hashFunction(key);
    auto& bucket = hashTable[index];

    auto it = std::find_if(bucket.begin(), bucket.end(), [key](const HashEntry& entry) {
        return entry.key == key;
    });

    if (it != bucket.end()) {
        bucket.erase(it);
    } else {
        std::cerr << "Key " << key << " not found" << std::endl;
    }
}

// 해시 테이블 출력
void display(std::list<HashEntry> hashTable[]) {
    for (size_t i = 0; i < BUCKET_SIZE; ++i) {
        std::cout << i << ": ";

        for (const auto& entry : hashTable[i]) {
            std::cout << entry.key << ", ";
        }

        if (hashTable[i].empty()) {
            std::cout << "-1";
        }

        std::cout << std::endl;
    }
}

int main() {
    std::ifstream inputFile("hash_cmd.txt");

    std::list<HashEntry> hashTable[BUCKET_SIZE];

    initializeHashTable(hashTable);

    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            char command;
            int key;

            if (iss >> command >> key) {
                switch (command) {
                    case 'i':
                        insert(key, hashTable);
                        break;
                    case 'r':
                        remove(key, hashTable);
                        break;
                    default:
                        std::cerr << "Invalid command: " << command << std::endl;
                        break;
                }
            } else {
                std::cerr << "Error parsing input line: " << line << std::endl;
            }
        }

        display(hashTable);

        inputFile.close();
    } else {
        std::cerr << "Unable to open input file." << std::endl;
    }

    return 0;
}
