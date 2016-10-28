#include <iostream>
#include <cstdlib>
#include "ArrayList.h"

using namespace std;

template <class T>
ArrayList<T>::ArrayList() 
{
	list = NULL;
	size = 0;
} 

template <class T>
void ArrayList<T>::push (T elem) 
{
	T * temp = new T[size+1];
	for (int i=0;i<size;i++){
		temp[i] = list[i];
	}
	
	temp[size] = elem;
	list = temp;
	size++;
}

template <class T>
T ArrayList<T>::get(int idx) 
{
	return list[idx];
} 

template <class T>
T &ArrayList<T>::getLastElem() 
{
	return list[size-1];
}

template <class T>
void ArrayList<T>::set(int idx,T elem) 
{
	list[idx] = elem;
} 

template <class T>
int ArrayList<T>::getSize() 
{
	return size;
} 

template <class T>
void ArrayList<T>::display() 
{
	for (int i=0;i<size;i++){
		cout<<list[i]<<endl;
	}
} 


