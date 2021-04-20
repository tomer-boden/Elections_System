#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Utilities {
	public:
		static T getFirstMaxIndex(const vector<T>, int len); //get first max index in int array
		static void swap(T& num1, T& num2); // swap 2 integers
};

template <class T>
T Utilities<T>::getFirstMaxIndex(const vector<T> arr, int len) {
	int max = 0;
	for (int i = 0; i < len; i++) {
		if (arr[i] > max) {
			max = i;
		}
	}
	return max;
}

template <class T>
void Utilities<T>::swap(T& num1, T& num2)
{
	T temp = num1;
	num1 = num2;
	num2 = temp;
}
