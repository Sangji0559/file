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

int check_full(){
    for(int i = 16; i++){
        if(table[i].key==-1) return i;
    }
    return -1;
}

void insert_key(int mod, int key){
    int next;
    if(mod<16){
        if(table[mod].key==-1) table[mod].key = key;
        else{
            if(table[mod].next!=-1){
                next = check_full();
                if(next!=-1){
                    insert_key(next,key);
                }
                else{
                    return;
                }
            }
        }
    }
    
}

int main() {
	fstream input("hash_cmd.txt", ios::in); // hash_cmd.txt에서 데이터 가져오기
	fstream output("result.txt", ios::out);// result.txt에 데이터 출력
	
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