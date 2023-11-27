#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include<algorithm>

using namespace std;
struct node{
    int key = -1;
    int next = -1;
};
node table[32];

int check_full(){ // 남은 bucket이 존재하는 지 
    for(int i = 16; i++){
        if(table[i].key==-1) return i; // 존재하면 index 리턴
    }
    return -1; // 없으면 -1 리턴
}

void insert_key(int mod, int key){
    // mod에 따라서 저장 방법 다르게
    // mod()
}

void remove_key(int mod, int key){

}

int main() {
	fstream input("hash_cmd.txt", ios::in); // hash_cmd.txt에서 데이터 가져오기
	fstream output("result.txt", ios::out); // result.txt에 데이터 출력
	
	char c; // insert, remove 구분
	int temp, mod;    
	
	while (!input.eof()) {
		input.get(c);
		if (c == 'i') {
			input >> temp;
            mod = temp % 16;
            insert_key(mod, temp);
		}
		else if (c == 'r') {
			input >> temp;
            mod = temp % 16;
            remove_key(mod, temp);
		}
    }
	
	input.close(); // 파일 닫기
	output.close(); //파일 닫기

	return 0;
}