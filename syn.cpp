#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include<algorithm>

using namespace std;
const int TABLE_SIZE = 16;
class HashTable {
private:
    vector<list<int>> table;

public:
    HashTable() : table(TABLE_SIZE) {}

    void insert(int key) {
        int index = hashFunction(key);

        if (find(table[index].begin(), table[index].end(), key) == table[index].end()) {
            table[index].push_back(key);
        }
    }


    void remove(int key) {
        int index = hashFunction(key);
        
        if (find(table[index].begin(), table[index].end(), key) == table[index].end()) {
            table[index].remove(key);
        }
    }

    void print(fstream& outFile) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            outFile << i << ":";
            if (table[i].empty()) {
                outFile << "-1,";
            }
            else {
                for (int key : table[i]) {
                    outFile << key << ",";
                }
            }
            outFile << "\n";
        }
    }

private:
    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }
};

int main() {
	fstream input("hash_cmd.txt", ios::in); // hash_cmd.txt에서 데이터 가져오기
	fstream output("result.txt", ios::out);// result.txt에 데이터 출력
	
	char c; // insert, remove 구분
	int temp;
    HashTable ht;
    
	
	while (!input.eof()) {
		input.get(c);
		if (c == 'i') {
			input >> temp;
            ht.insert(temp);
		}
		else if (c == 'r') {
			input >> temp;
            ht.remove(temp);
		}
	}

    ht.print(output);
	
	input.close(); // 파일 닫기
	output.close(); //파일 닫기

	return 0;
}