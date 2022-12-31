#include <iostream>
#include <vector>

using namespace std;

class SetUnion {
private:
	vector<int> parent;
	vector<int> rank;

public:
	SetUnion(vector<int> &parent) {
		this->parent = parent;
		int n = parent.size() + 1;
		rank.resize(n);
	}

	void makeSet(int n) {		
		for (int i = 1; i <= n; i++) {
			parent[i] = i;
		}
	}

	int find(int A) {
		if (parent[A] == A) {
			return parent[A];
		}
		else {
			int result = find(parent[A]);
			parent[A] = result;
			return result;
		}
	}

	void mergeSets(int A, int B) {
		int x = find(A);
		int y = find(B);

		int xRank = rank[x];
		int yRank = rank[y];

		if (xRank == yRank) {
			parent[x] = y;
			rank[y]++;
		}
		else if (xRank < yRank) {
			parent[x] = y;
		}
		else {
			parent[y] = x;
		}
	}

	int countParents() {
		int size = parent.size();
		int prevParent = find(parent[1]);
		int count = 1;

		for (int i = 2; i < size; i++) {
			int thisParent = find(parent[i]);
			if (thisParent != prevParent) {
				count++;
			}
			prevParent = thisParent;
		}
		return count;
	}

	void print() {
		int size = parent.size();

		for (int i = 1; i < size; i++) {
			cout << parent[i] << " ";
		}
		cout << endl;
	}
};

void solve() {
	int n;
	cin >> n;

	vector<int> p(n + 1);
	vector<int> parent(n + 1);
	vector<pair<int, int>> c;

	for (int i = 1; i <= n; i++) {
		cin >> p[i];
	}

	SetUnion su(parent);
	su.makeSet(n);

	int start = 1;
	vector<int> placed;
	for (int i = 1; i <= n; i++) {
		for (int j = start; j < p[i]; j++) {
			//c.push_back(make_pair(p[i], j));
			su.mergeSets(p[i], j);
		}

		if (placed.size() == 0) {
			placed.push_back(p[i]);
		}
		else {
			if (p[i] > *placed.rbegin()) {
				placed.push_back(p[i]);
			}
			else {
				placed.insert(placed.begin(), p[i]);
			}
		}

		if (*placed.rbegin() == i) {
			start = i + 1;
		}
	}

	//for (pair<int, int> pr : c) {
	//	cout << pr.first << " " << pr.second << endl;
	//}

	//for (pair<int, int> i : c) {
	//	su.mergeSets(i.first, i.second);
	//}

	cout << su.countParents() << endl;
	//su.print();
}

int main() {
	int t;
	cin >> t;

	for (;t--;) {
		solve();
	}
}