#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <map>
#include <climits>
#include <cassert>
#include <complex>
using namespace std;

#define REP(i,n) for(int i=0; i<(int)(n); i++)
#define RREP(i,n) for(int i=(int)n-1; i>=0; i--)
#define FOR(i,c) for(__typeof((c).begin())i=(c).begin();i!=(c).end();++i)
#define RFOR(i,c) for(__typeof((c).rbegin())i=(c).rbegin();i!=(c).rend();++i)
#define ALL(c) (c).begin(), (c).end()

typedef long long int ll;
typedef pair<int, int> pii;
typedef pair<int, pair<int, int> > pipii;
typedef vector<int> vi;

const int INF = 1e9;
const int MOD = 1e9+7;

#define EPS 1e-8

typedef complex<double> Point;
namespace std {
	bool operator < (const Point &a, const Point &b) {
		return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
	}
	Point operator / (const Point &p, const double &a) {
		return Point(real(p)/a, imag(p)/a);
	}
	Point operator * (const Point &p, const double &a) {
		return Point(real(p)*a, imag(p)*a);
	}
	bool operator == (const Point &a, const Point &b) {
		return real(a) == real(b) && imag(a) == imag(b);
	}
}
struct Circle {
	Point c; double r;
	Circle () {}
	Circle (const Point &c, double r) : c(c), r(r) {}
};

struct Line : public vector<Point> { 
	Line () {}
	Line (const Point &a, const Point &b) {
		push_back(a); push_back(b);
	}
};

double dot (const Point &a, const Point &b) {
	return real(conj(a)*b);
}

Point projection(const Line &l, const Point &p) {
	double t = dot(p-l[0], l[0]-l[1]) / norm(l[0]-l[1]);
	return l[0] + t*(l[0]-l[1]);
}

vector<Point> crosspointLC(const Line &l, const Circle &c) {
	vector<Point> ret;
	Point center = projection(l, c.c);
	double d = abs(center - c.c);
	double t = sqrt(c.r * c.r - d * d);
	if (isnan(t)) { return ret; }
	Point vect = (l[1] - l[0]);
	vect /= abs(vect);
	ret.push_back(center - vect * t);//
	if (t > EPS) {
		ret.push_back(center + vect * t);
	}
	return ret;
}

vector<Point> crosspointCC(const Circle &c1, const Circle &c2) {
	vector<Point> ret;
	double d = abs(c1.c - c2.c);
	if (max(c1.r, c2.r) - min(c1.r, c2.r) - d> -EPS) { return ret; }
	double x = (d * d + c1.r * c1.r - c2.r * c2.r) / (2 * d);
	Point start = c1.c + (c2.c - c1.c) / d * x;
	Point vect = (c1.c - c2.c) * Point(0.0, 1.0);
	return crosspointLC(Line(start, start + vect), c1);
}


int main(void){
	int T;
	cin >> T;
	while(T--){
		double R;
		int N;
		cin >> R >> N;
		vector<Circle> c(N);
		REP(i, N){
			double X, Y;
			cin >> X >> Y;
			c[i] = Circle(Point(X, Y), R);
		}
		if(N <= 1){
			cout << N << endl;
			continue;
		}
		int ans = 0;
		REP(i, N){
			int ret = 0;
			REP(k, N){
				if(abs(c[i].c - c[k].c) <= R + EPS) ret++;
			}
			ans = max(ans, ret);
			for(int j = i + 1; j < N; j++){
				vector<Point> cross = crosspointCC(c[i], c[j]);
				if(!cross.size()) continue;
				REP(l, cross.size()){
					ret = 0;
					REP(k, N){
						if(abs(cross[l] - c[k].c) <= R + EPS) ret++;
					}
					ans = max(ans, ret);
				}
			}
		}
		cout << ans << endl;
	}
	return 0;
}
