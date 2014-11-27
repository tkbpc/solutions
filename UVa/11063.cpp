#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

#define rep(i,n) for(int i=0; i<n; i++)
#define FOR(i,s,n) for(int i=s; i<n; i++)
#define ALL(x) x.begin(), x.end()
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;

int main() {
	int n;
	int cs = 1;
	while(cin >> n) {
		bool sum[20001] = {};
		bool ok = true;
		int b[n];
		cin >> b[0];
		if(1 > b[0]) ok = false; 
		rep(i, n-1) {
			cin >> b[i+1];
			if(b[i] >= b[i+1]) 
				ok = false;
		}
		if(ok) {
			rep(i, n) {
				for(int j=i; j<n; j++) {
					int d = b[j]+b[i];
					if(sum[d]) {
						ok = false;
						break;
					}
					sum[d] = true;
				}
				if(!ok) break;
			}
		}
		cout << "Case #" << cs << ": ";
		if(ok) {
			cout << "It is a B2-Sequence." << endl;
		} else {
			cout << "It is not a B2-Sequence." << endl;
		}
		cout << endl;
		cs++;
	}
	return 0;
}
