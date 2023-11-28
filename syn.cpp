#include<iostream>
#include<fstream>

struct Node {
	int data;
	struct Node* next;
};

class LinkedList{
	private:
		
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