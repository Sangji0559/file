#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include<algorithm>

using namespace std;
struct node{
    int key =-1;
    int next = -1;
};
node table[32];

int check_full{
    for(int i = 16; i++){
        if(table[i].key==-1) return i;
    }
    return -1;
}

void insert_key(int key){
    mod = key % 16;
    if(table[mod].key !=-1){
        if(check_full!=-1){
            next = i;
        }
    }
}

void remove_key(int key){
    mod = key % 16;
}

int main() {
	fstream input("hash_cmd.txt", ios::in); // hash_cmd.txt에서 데이터 가져오기
	fstream output("result.txt", ios::out);// result.txt에 데이터 출력
	
	char c; // insert, remove 구분
	int temp;    
	
	while (!input.eof()) {
		input.get(c);
		if (c == 'i') {
			input >> temp;
            insert_key(temp);
		}
		else if (c == 'r') {
			input >> temp;
            remove_key(temp);
		}
    }
	
	input.close(); // 파일 닫기
	output.close(); //파일 닫기

	return 0;
}