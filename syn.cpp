#include <iostream>
#include <fstream>
#include <list>

using namespace std;

struct Node {
	int key;
};

list<Node> table[16];
size_t tablesize[16];

int tablesum(){
	int sum=0;
	for(int i=0;i<16;i++){
		if(tablesize[i]>=1){
			sum += tablesize[i]-1;
		}
	}
	return sum;
}

void insert_key(int key){
	size_t index = key % 16;
	auto& bucket = table[index];
	for (const auto& entry : bucket){
		if(entry.key == key) return;
	}
	if(bucket.size() < 16 && tablesum() < 16){
		bucket.push_back({key});
		tablesize[index]++;
	}	
}

void remove_key(int key) {
    size_t index = key % 16;
    auto& bucket = table[index];

    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->key == key) {
            bucket.erase(it);
			tablesize[index]--;
            return;
        }
    }
}


int main() {
	fstream input("hash_cmd.txt", ios::in); // hash_cmd.txt에서 데이터 가져오기
	fstream output("result.txt", ios::out); // result.txt에 데이터 출력
	
	char c; // insert, remove 구분
	int temp // key 값 임시 저장
	
	while (!input.eof()) { // hash_cmd.txt의 데이터가 있을 경우
		input.get(c); // 앞의 문자 하나 가져오기
		if (c == 'i') { // 'i'의 경우 insert
			input >> temp; 
            insert_key(temp); // insert_key
		}
		else if (c == 'r') { // 'r'의 경우 remove
			input >> temp;
            remove_key(temp); // remove_key
		}
    }
	for (size_t i = 0; i < 16; ++i) { // 파일에 데이터 출력
    	output << i << ":";
        for (const auto& entry : table[i]) { // table에 대해 값이 존재하면
            output << entry.key << ", ";  
        }
        if (table[i].empty()) { // 비어있으면 -1, 출력
            output << "-1,";
        }
        output << "\n";
    }
	
	input.close(); // 파일 닫기
	output.close(); //파일 닫기

	return 0;
}