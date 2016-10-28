#ifndef ARRAYLIST_H
#define ARRAYLIST_H

using namespace std;

template <class T>
class ArrayList{
	T * list;
	int size;
	
	public:
		ArrayList();
		void push (T);
		void display();
		int getSize();
		T &getLastElem();
		void set(int,T);
		T get(int);
		friend ostream& operator<<(ostream& os, ArrayList& l){
			int s = l.getSize();
			for (int i=0;i<s;i++){
				os<<l.get(i)<<" ";
			}
		}

};

#endif


