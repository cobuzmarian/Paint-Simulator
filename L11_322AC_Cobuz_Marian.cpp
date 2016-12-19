#include<iostream>
#include<vector>
using namespace std;

template <class T>
class Stack {
	vector<T> elems;
	int topel = -1;
	public:
		void push(T);
		void pop();
		bool isEmpty();
		T top();
};

template <class T> void Stack<T> :: push(T x) {
	elems.push_back(x);
	topel++;
}

template <class T> void Stack<T> :: pop(void) {
	topel--;
	elems.pop_back();
}

template <class T> bool Stack<T> :: isEmpty() {
	if(topel >= 0) {
		cout <<"not empty!" <<endl;
		return 0;
	}
	cout <<"empty!" <<endl;
	return 1;
	
}

template <class T> T Stack<T> :: top() {
	return elems.back();
}

int main() {
	Stack<int> t;
	cout <<"Cu int" <<endl << endl;
	t.isEmpty();
	t.push(3);
	cout << t.top() << endl;
	t.isEmpty();
	t.pop();
	t.isEmpty();
	cout <<endl <<"Cu char" <<endl << endl;
	Stack<char> s;
	char a;
	char b;
	a = 'a';
	b = 'b';
	s.isEmpty();
	s.push(a);
	cout << s.top() << endl;
	s.isEmpty();
	s.pop();
	s.push(b);
	s.isEmpty();
	cout << endl << "Cu double" << endl << endl;
	Stack<double> d;
	d.isEmpty();
	d.push(2.2);
	cout << d.top() << endl;
	d.isEmpty();
	d.pop();
	d.isEmpty();
	return 0;
}

