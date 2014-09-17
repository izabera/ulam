/*
prints ulam numers
a(1) = 1
a(2) = 2
a(n) = minimum number > a(n-1) that can be espressed as the sum of two distinct ulam numbers in exactly one way
*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> ulam, sums(2,1);

int nextulam (int n) {
	int i;
	for (i = sums.size(); i < ulam[n-1]*2; i++) //ulam(n)<=ulam(n-1)+ulam(n-2)
		sums.push_back(0);
	//sums.insert(sums.end(), ulam[n-1], 0); <--- 10x slower if compiled with gcc -Ofast, wtf
	int size = sums.size();
	#pragma omp parallel for
	for (i = 0; i < n-1; i++)
		sums[ulam[i]+ulam[n-1]-1]++;
	for (i = ulam[n-1]; i < size; i++)
		if (sums[i] == 1) return i+1;
}

main () {
	int n, found = 2, temp;
	cin >> n;
	ulam.push_back(1);
	ulam.push_back(2);
	if (n == 1) {
		cout << "1" << endl;
		return 0;
	}
	else cout << "1 2";
	while (found < n) {
		temp = nextulam(found);
		cout << " " << temp;
		found++;
		ulam.push_back(temp);
	}
	cout << endl;
	return 0;
}
