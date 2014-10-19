/*
prints ulam numers
a(1) = 1
a(2) = 2
a(n) = minimum number > a(n-1) that can be espressed as the sum of two distinct ulam numbers in exactly one way
*/

#include <iostream>
#include <vector>

std::vector<unsigned int> ulam, sums(2,1);

unsigned int nextulam (unsigned int n) {
	unsigned int i;
	for (i = sums.size(); i < ulam[n-1]*2; i++) //ulam(n)<=ulam(n-1)+ulam(n-2)
		sums.push_back(0);
	unsigned int size = sums.size();
	for (i = 0; i < n-1; i++)
		sums[ulam[i]+ulam[n-1]-1]++;
	for (i = ulam[n-1]; i < size; i++)
		if (sums[i] == 1) return i+1;
	return 0; // for compilers' warnings
}

int main () {
	unsigned int n, found = 2, temp;
	std::cin >> n;
	ulam.push_back(1);
	ulam.push_back(2);
	if (n == 1) {
		std::cout << "1" << std::endl;
		return 0;
	}
	else std::cout << "1 2";
	while (found < n) {
		temp = nextulam(found);
		std::cout << " " << temp;
		found++;
		ulam.push_back(temp);
	}
	std::cout << std::endl;
	return 0;
}
