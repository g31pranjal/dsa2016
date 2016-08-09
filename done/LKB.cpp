#include <iostream> 
#include <climits>

using namespace std;

int main() {
	int num=0, max=0, total=0, imp=0;

	cin >> num;
	cin >> max;

	int luck[num];
	int isImp[num];

	for(int i=0;i<num;i++) {
		cin >> luck[i];
		total += luck[i];
		cin >> isImp[i]; 
		if(isImp[i] == 1)
			imp++;
	}

	//cout << total << "............" << endl;

	while(imp > max) {
		int a = INT_MAX;
		int i = -1;
		for(int j=0;j<num;j++) {
			//cout <<  isImp[j] << "!!" << endl;
			if(isImp[j] == 1 && luck[j] < a) {
				i = j;
				a = luck[j];
			}	
		}
		//cout << ".... a : " << a << " , i" << i 	<< endl; 
		isImp[i] = 0;
		total -= 2*a;
		imp--;
	}
	cout << total << endl;
		

		

}