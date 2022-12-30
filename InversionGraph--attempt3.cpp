#include <iostream>
#include <vector>

using namespace std;

class SetUnion {
private:
	vector<int> parent;

public:
	SetUnion(vector<int> &parent) {
		this->parent = parent;
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

		parent[x] = y;
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

	int start = 1;
	vector<int> placed;
	for (int i = 1; i <= n; i++) {
		for (int j = start; j < p[i]; j++) {
			c.push_back(make_pair(p[i], j));
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

	SetUnion su(parent);
	su.makeSet(n);

	for (pair<int, int> i : c) {
		su.mergeSets(i.first, i.second);
	}

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