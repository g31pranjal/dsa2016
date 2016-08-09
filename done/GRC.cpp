#include <iostream>

using namespace std;



int main() {

	int test = 0, num = 0;
	cin >> test;
	char tmp;


	for(int i=0;i<test;i++) {
		cin >> num;
		char arr[num][num];

		bool cant = false;

		for(int j=0;j<num;j++) {
			for(int k=0;k<num;k++) {
				cin >> arr[j][k];
			}
		}

		for(int m=0;m<num;m++) {
			// col m
			//cout << "COL " << m << endl;
			for(int n=0;n<num;n++) {
				// row n
				int rowmin = m;
				for(int o=m+1;o<num;o++) {
					if(arr[n][m] > arr[n][o]) {
						// swap
						tmp = arr[n][m];
						arr[n][m] = arr[n][o];
						arr[n][o] = tmp;
					}
				}
			}

			// for(int p=0;p<num;p++) {
			// 	for(int q=0;q<num;q++) {
			// 		cout << arr[p][q] << "\t";
			// 	}
			// 	cout << endl;
			// }


			char t = arr[0][m];
			for(int n=1;n<num;n++) {
				if(t <= arr[n][m]) {
					t = arr[n][m];
					continue;
				}
				else {
					cant = true;
					break;
				}
			}

			if(cant)
				break;
		}

		if(!cant) {
			cout << "YES" << endl;
		}
		else
			cout << "NO" << endl;
	}



	return 0;

}