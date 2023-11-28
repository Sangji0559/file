#include <iostream>
#include <fstream>
#include <list>

using namespace std;

struct Node {
	int key;
};

list<Node> table[16]; // 저장할 공간 bucket
size_t tablesize[16]; // table의 size를 제공

int tablesum(){ // table size를 통해 오버플로우 구역에 저장된 데이터 개수 구하기
	int sum=0;
	for(int i=0;i<16;i++){
		if(tablesize[i]>=1){ // 값이 존재하면
			sum += tablesize[i]-1; // 오버플로우 구역의 개수를 sum
		}
	}
	return sum;
}

void insert_key(int key){ // list에 값 저장하기
	size_t index = key % 16; // hash 
	auto& bucket = table[index]; // 해당 index에 접근
	for (const auto& entry : bucket){ // 값이 존재하면 
		if(entry.key == key) return; // 중복 체크
	} 
	if(bucket.size() < 16 && tablesum() < 16){ // 값을 저장할 수 있는 공간이 있을 경우
		bucket.push_back({key});  // key값 저장
		tablesize[index]++; // tablesize 크기 증가 (오버플로우 개수 확인용)
	}	
}

void remove_key(int key) { // list에 값 삭제하기
    size_t index = key % 16; // hash를 통해 저장되었을 공간 확인
    auto& bucket = table[index]; // 해당 index에 접근

    for (auto it = bucket.begin(); it != bucket.end(); ++it) { // bucket의 처음부터 끝까지
        if (it->key == key) { // key 값이 존재하면
            bucket.erase(it); // bucket에서 삭제
			tablesize[index]--; // tablesize 크기 감소
            return;
        }
    }
}

int main() {
	fstream input("hash_cmd.txt", ios::in); // hash_cmd.txt에서 데이터 가져오기
	fstream output("result.txt", ios::out); // result.txt에 데이터 출력
	
	char c; // insert, remove 구분
	int temp; // key 값 임시 저장
	
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
            output << entry.key << ",";  
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