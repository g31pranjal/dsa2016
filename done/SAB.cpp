#include <iostream>

using namespace std;

int part(int num) {
	int n5 = 0, n3 = 0;
	int vn5 = -1;
	int vn3 = -1;
	
	while(n5 <= num) {

		n3 = num - n5;
		
		//cout << n5 << " , " << n3 << endl;

		if(n5%3 == 0 && n3%5 == 0) {
			vn3 = n3;
			vn5 = n5;
		}
		n5 += 3;
	}

	return vn5;
}


int main() {
	int test=0,num=0;
	cin >> test;

	for(int i=0;i<test;i++) {
		cin >> num;
		
		int n5 = part(num);
		if(n5 == -1) {
			cout << "-1" << endl;
		}
		else {
			for(int i=0;i<n5;i++) {
				cout << "5";
			}
			for(int i=0;i<num-n5;i++) {
				cout << "3";
			}
			cout << endl;
		}

	}
}