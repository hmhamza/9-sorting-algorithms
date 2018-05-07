#include<iostream>
#include<fstream>
#include<random>
#include <ctime>
#include <ratio>
#include <chrono>
#include<string>

#include <windows.h> 
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;
using namespace std::chrono;

string NAMES[11] = { "Bubble Sort", "Selection Sort", "Insertion Sort", "Merge Sort (Top Down)", " Merge Sort (Bottom Up)", "Quick Sort", "Original Hoare Quick Sort", "Heap Sort", "Count Sort", "Radix Sort", "Shell Sort" };

void PlaceCursor(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, c);
}

int LOG(int x, int base) {
	return (int)(log(x) / log(base));
}

void COPY_ARRAY(int *arr, int *&temp, int n, int start = 0){			//start has been added for Heap
	temp = new int[n + start];
	for (int i = 0; i < n; i++)
		temp[i + start] = arr[i];

}

void PRINT(int *arr, int n, int start = 0){

	cout << endl;

	for (int i = start; i < n + start; i++)
		cout << arr[i] << " ";

	cout << endl << endl;
}

void TIME_PRINT(nanoseconds TIME_SPAN, int choice, int n){		//void TIME_PRINT(nanoseconds TIME_SPAN,int choice,int n){

	double time = TIME_SPAN.count();
	char micro = -26;

	if (time < 1000)
		cout << "\nTime consumed by " << NAMES[choice - 1] << " with " << n << " Data size is " << time << " ns" << endl;
	else if (time / 1000 < 1000)
		cout << "\nTime consumed by " << NAMES[choice - 1] << " with " << n << " Data size is " << time / 1000 << " " << micro << "s" << endl;
	else if (time / 1000000 < 1000)
		cout << "\nTime consumed by " << NAMES[choice - 1] << " with " << n << " Data size is " << time / 1000000 << " ms" << endl;
	else
		cout << "\nTime consumed by " << NAMES[choice - 1] << " with " << n << " Data size is " << time / 1000000000 << " sec." << endl;
}

int POPULATE(int *&arr){

	cout << "\n\t\t**************************************************\n";
	cout << "\t\t* POPULATING DATA IN THE ARRAY TO RUN THE ALGOS. *\n";
	cout << "\t\t**************************************************\n\n";
	int a1, a2, n;
	cout << "\nEnter Data size: ";
	cin >> n;
	while (n < 1){
		cout << "Please Enter valid Data Size (i.e. greater that 0) : ";
		cin >> n;
	}
	
	cout << "\nEnter Data Range:\n\tFrom: ";
	cin >> a1;
	cout << "\n\tTo: ";
	cin >> a2;
	while (a2 < a1){
		cout << "\"To:\" limit must be greater than or equal to \"From:\" limit\n";
		cout << "\n\tTo: ";
		cin >> a2;
	}
	arr = new int[n];

	mt19937 gen(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
	uniform_int_distribution<> dis(a1, a2);

	for (int i = 0; i < n; i++) {
		arr[i] = dis(gen);
	}

	char  filename[50], size_str[10];
	_itoa_s(n, size_str, 10);

	filename[0] = '\0';
	strcat_s(filename, "Data for Algos. (Data Size ");
	strcat_s(filename, size_str);
	strcat_s(filename, " ).txt");

	ofstream fout(filename);

	for (int i = 0; i < n; i++){
		fout << arr[i] << ", ";
		if (i % 15 == 14)
			fout << endl;
	}

	cout << "\n\n  Data has been populated and placed in the file\n\n";
	return n;
}

void POPULATE_BY_SIZE(int *&arr, int size,int a1,int a2){

	arr = new int[size];

	mt19937 gen(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
	uniform_int_distribution<> dis(a1,a2);

	for (int i = 0; i < size; i++) {
		arr[i] = dis(gen);
	}
}

void STORE_DATA_IN_FILE(int arr[], int arr_size, int count){

	char  filename[30], size_str[15], count_str[5];
	_itoa_s(arr_size, size_str, 10);
	_itoa_s(count + 1, count_str, 10);

	filename[0] = '\0';
	strcat_s(filename, size_str);
	strcat_s(filename, " ints Data Chunk #");
	strcat_s(filename, count_str);
	strcat_s(filename, ".txt");

	ofstream fout(filename);

	for (int i = 0; i < arr_size; i++){
		fout << arr[i] << ", ";
		if (i % 15 == 14)
			fout << endl;
	}
}

void STORE_RESULT_IN_FILE(int arr[], int arr_size, int choice, int start, bool isComparison = false, int count = 0){

	char  filename[100], size_str[15], algoStr[50], count_str[5];
	_itoa_s(arr_size, size_str, 10);
	_itoa_s(count + 1, count_str, 10);

	int i;
	for (i = 0; i < NAMES[choice - 1].length(); i++)
		algoStr[i] = NAMES[choice - 1].at(i);
	algoStr[i] = '\0';

	filename[0] = '\0';
	if (isComparison)
		strcat_s(filename, "Comparison ");
	strcat_s(filename, "Result of ");
	strcat_s(filename, algoStr);
	strcat_s(filename, " (with ");
	if (isComparison){
		strcat_s(filename, " Data Chunk #");
		strcat_s(filename, count_str);
		strcat_s(filename, ").txt");
	}
	else{
		strcat_s(filename, size_str);
		strcat_s(filename, " Data Size)");
		strcat_s(filename, ".txt");
	}

	ofstream fout(filename);

	for (int i = start; i < arr_size + start; i++){
		fout << arr[i] << ", ";
		if (i % 15 == 14)
			fout << endl;
	}

}

void INSERTION_SORT(int *arr, int n){

	int key, i;
	for (int j = 1; j < n; j++){
		key = arr[j];
		i = j - 1;
		while (i >= 0 && arr[i]>key){
			arr[i + 1] = arr[i];
			i--;
		}
		arr[i + 1] = key;
	}
}

void SELECTION_SORT(int *arr, int n){

	int smallest;
	for (int j = 0; j < n - 1; j++){
		smallest = j;
		for (int i = j + 1; i < n; i++){
			if (arr[i] < arr[smallest])
				smallest = i;
		}
		swap(arr[j], arr[smallest]);
	}
}

void BUBBLE_SORT(int *arr, int n){

	for (int i = 0; i < n - 1; i++){
		for (int j = 0; j < n - i - 1; j++){
			if (arr[j]>arr[j + 1])
				swap(arr[j], arr[j + 1]);
		}
	}
}

void MERGE(int *arr, int p, int q, int r){

	int n1, n2, i, j;
	n1 = q - p + 1;
	n2 = r - q;

	int *A = new int[n1 + 1];

	for (int b = 0, x = p; b < n1; b++, x++)
		A[b] = arr[x];
	A[n1] = 2147483647;

	int *B = new int[n2 + 1];
	for (int b = 0, x = q + 1; b < n2; b++, x++)
		B[b] = arr[x];
	B[n2] = 2147483647;

	i = 0; j = 0;
	for (int k = p; k <= r; k++){
		if (A[i] < B[j])
			arr[k] = A[i++];
		else
			arr[k] = B[j++];
	}
}

void MERGE_SORT_TOP_DOWN(int *arr, int p, int r){

	if (p < r){
		int q = (p + r) / 2;

		MERGE_SORT_TOP_DOWN(arr, p, q);
		MERGE_SORT_TOP_DOWN(arr, q + 1, r);

		MERGE(arr, p, q, r);
	}

}

void MERGE_SORT_BOTTOM_UP(int *arr, int n){

	int c, d, p, q, r, n1, n2, size;

	for (int i = 1; i < n; i *= 2){

		size = i;

		for (int j = 0; j < n; j += 2 * i){

			if (n - j < 2 * size){
				r = n - 1;
				q = j - 1;
			}
			else{
				p = j;
				q = p + size - 1;
				r = q + size;
			}

			n1 = q - p + 1;
			n2 = r - q;

			int *A = new int[n1 + 1];

			for (int b = 0, x = p; b < n1; b++, x++)
				A[b] = arr[x];
			A[n1] = 2147483647;
			int *B = new int[n2 + 1];
			for (int b = 0, x = q + 1; b < n2; b++, x++)
				B[b] = arr[x];
			B[n2] = 2147483647;
			c = 0;
			d = 0;
			for (int b = p; b <= r; b++){
				if (A[c] < B[d])
					arr[b] = A[c++];
				else
					arr[b] = B[d++];
			}

			delete A;
			delete B;
		}

	}
}

int PARTITION(int *arr, int p, int r){
	int x = arr[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; j++){
		if (arr[j] <= x){
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[r]);
	return i + 1;
}

void QUICK_SORT(int *arr, int p, int r){

	if (p < r){
		int q = PARTITION(arr, p, r);
		QUICK_SORT(arr, p, q - 1);
		QUICK_SORT(arr, q + 1, r);
	}
}

int HOARE_PARTITION(int *arr, int p, int r){

	int x = arr[p];
	int i = p - 1;
	int j = r + 1;
	while (true){

		do{
			j--;
		} while (arr[j] > x);

		do{
			i++;
		} while (arr[i] < x);
		if (i < j)
			swap(arr[i], arr[j]);
		else
			return j;
	}
}

void HOARE_QUICK_SORT(int *arr, int p, int r){

	if (p < r){
		int q = HOARE_PARTITION(arr, p, r);
		HOARE_QUICK_SORT(arr, p, q);
		HOARE_QUICK_SORT(arr, q + 1, r);
	}
}

void MAX_HEAPIFY(int* arr, int Heapsize, int i)
{
	int LEFT = 2 * i;
	int RIGHT = 2 * i + 1;
	int largest;

	if (LEFT <= Heapsize && arr[LEFT]>arr[i])
		largest = LEFT;
	else
		largest = i;

	if (RIGHT <= Heapsize && arr[RIGHT] > arr[largest])
		largest = RIGHT;

	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		MAX_HEAPIFY(arr, Heapsize, largest);
	}
}

void BUILD_MAX_HEAP(int* arr, int size)
{
	for (int i = size / 2; i >= 1; i--)
		MAX_HEAPIFY(arr, size, i);
}

void HEAP_SORT(int* arr, int size)
{
	int HeapSize = size;
	
	BUILD_MAX_HEAP(arr, size);
	for (int i = size; i >= 2; i--){
		swap(arr[1], arr[i]);
		HeapSize--;
		MAX_HEAPIFY(arr, HeapSize, 1);
	}
	
}

void COUNT_SORT(int *arr, int n){

	int min=0,max = 0, C_size, *C, *B, sum,temp;
	for (int i = 1; i < n; i++){
		if (arr[i]<arr[min])
			min = i;
		else if (arr[i]>arr[max])
			max = i;
		
	}
	temp = arr[min];
	temp = temp*(-1);

	if (temp>arr[max])
		C_size = 2*temp + 1;
	else
		C_size = 2 * arr[max]+ 1;

	C = new int[C_size];

	for (int i = 0; i < C_size; i++)
		C[i] = 0;

	for (int i = 0; i < n; i++)
		C[(C_size / 2) + arr[i]]++;

	sum = 0;

	for (int i = 1; i < C_size; i++)
		C[i] += C[i - 1];

	B = new int[n];

	for (int i = n - 1; i >= 0; i--){
		B[C[(C_size / 2) + arr[i]] - 1] = arr[i];
		C[(C_size / 2) + arr[i]]--;
	}

	for (int i = 0; i < n; i++)		//Copy the sorted data into the original array
		arr[i] = B[i];
}

void RADIX_SORT(int *arr, int n){

	int max, max_digits, C_size, *C, *B, sum;;
	max = 0;
	for (int i = 1; i < n; i++){		//Finding max. element in the array to see the maximum no. of digits
		if (arr[i]>arr[max])
			max = i;
	}
	char str[15];
	_itoa_s(arr[max],str, 10);
	max_digits = strlen(str);

	for (int i = 1; i <= max_digits; i++){
		int m = pow(10,i);

		max = 0;
		for (int i = 1; i < n; i++){
			if (arr[i] % m / (m / 10)>arr[max] % m / (m / 10))
				max = i;
		}

		C_size = arr[max] % m / (m / 10) + 1;
		C = new int[C_size];

		for (int i = 0; i < C_size; i++)
			C[i] = 0;

		for (int i = 0; i < n; i++)
			C[arr[i] % m / (m / 10)]++;


		sum = 0;

		for (int i = 1; i < C_size; i++)
			C[i] += C[i - 1];

		B = new int[n];

		for (int i = n - 1; i >= 0; i--){
			B[C[arr[i] % m / (m / 10)]-1] = arr[i];
			C[arr[i] % m / (m / 10)]--;
		}

		for (int i = 0; i < n; i++)		//Copy the sorted data into the original array
			arr[i] = B[i];
	}

}

void SHELL_SORT(int *arr, int n){

	int h = 1;
	while (h < (n / 3))
		h = 3 * h + 1;
	while (h >= 1){
		for (int i = h; i < n; i++){
			for (int j = i; j >= h && (arr[j] < arr[j - h]); j -= h)
				swap(arr[j], arr[j - h]);
		}
		h /= 3;
	}
}

void COMPARISON(){

	int c1, c2,a1,a2, count, size, curr_size, ini_size, repeatCount, *data,*arr1, *arr2;
	double time1, time2;
	
	high_resolution_clock::time_point STARTING_TIME, ENDING_TIME;
	nanoseconds TIME_SPAN;
	vector<nanoseconds> Times1;
	vector<nanoseconds> Times2;
	
	system("cls");
	cout << "\nSelect Two Algos.\n\t1) Bubble Sort\n\t2) Selection Sort\n\t3) Insertion Sort\n\t4) Merge Sort (Top Down)\n\t5) Merge Sort (Bottom Up)\n\t6) Quick Sort\n\t7) Original Hoare Quick Sort\n\t8) Heap Sort\n\t9) Count Sort\n\t10) Radix Sort (only +ve integers)\n\t11) Shell Sort\n\nEnter Option #1: ";
	cin >> c1;
	cout << "\n\nEnter Option #2: ";
	cin >> c2;
	cout << "\n\nEnter Total Data Size: ";
	cin >> size;
	cout << "\nEnter Data Range:\n\tFrom: ";
	cin >> a1;
	cout << "\n\tTo: ";
	cin >> a2;
	while (a2 < a1){
		cout << "\"To:\" limit must be greater than or equal to \"From:\" limit\n";
		cout << "\n\tTo: ";
		cin >> a2;
	}
	cout << "\n\nEnter Initial Data Size to start with: ";
	cin >> ini_size;
	cout << "\n\nFor How many times you want to repeat the process (to take avg.)? ";
	cin >> repeatCount;
	
	system("cls");
	cout << "\n\n\n\n\t\t\t\tPROCESSING...";

	nanoseconds ZERO = nanoseconds::duration(0);
	for (int i = 0; i <= LOG((size / ini_size), 2); i++){
		Times1.push_back(ZERO);
		Times2.push_back(ZERO);		
	}

	curr_size = ini_size;
	count = 0;
	while (curr_size < size){

		POPULATE_BY_SIZE(data, curr_size, a1, a2);
		

		if (c1 == 8)
			COPY_ARRAY(data, arr1, curr_size, 1);
		else
			COPY_ARRAY(data, arr1, curr_size); 

		if (c2 == 8)
			COPY_ARRAY(data, arr2, curr_size, 1);
		else
			COPY_ARRAY(data, arr2, curr_size);

		STARTING_TIME = high_resolution_clock::now();

		switch (c1){

		case 1:
			BUBBLE_SORT(arr1, curr_size);
			break;

		case 2:
			SELECTION_SORT(arr1, curr_size);
			break;

		case 3:

			INSERTION_SORT(arr1, curr_size);
			break;

		case 4:
			MERGE_SORT_TOP_DOWN(arr1, 0, curr_size - 1);
			break;

		case 5:
			MERGE_SORT_BOTTOM_UP(arr1, curr_size);
			break;

		case 6:
			QUICK_SORT(arr1, 0, curr_size - 1);
			break;

		case 7:
			HOARE_QUICK_SORT(arr1, 0, curr_size - 1);
			break;

		case 8:
			HEAP_SORT(arr1, curr_size);
			break;

		case 9:
			COUNT_SORT(arr1, curr_size);
			break;

		case 10:
			RADIX_SORT(arr1, curr_size);
			break;

	    case 11:
			SHELL_SORT(arr1, curr_size);
			break;
		}

		ENDING_TIME = high_resolution_clock::now();
		TIME_SPAN = duration_cast<nanoseconds>(ENDING_TIME - STARTING_TIME);
		Times1.at(LOG((curr_size / ini_size), 2)).operator+=(TIME_SPAN);

		STARTING_TIME = high_resolution_clock::now();

		switch (c2){

		case 1:
			BUBBLE_SORT(arr2, curr_size);
			break;

		case 2:
			SELECTION_SORT(arr2, curr_size);
			break;

		case 3:

			INSERTION_SORT(arr2, curr_size);
			break;

		case 4:
			MERGE_SORT_TOP_DOWN(arr2, 0, curr_size - 1);
			break;

		case 5:
			MERGE_SORT_BOTTOM_UP(arr2, curr_size);
			break;

		case 6:
			QUICK_SORT(arr2, 0, curr_size - 1);
			break;

		case 7:
			HOARE_QUICK_SORT(arr2, 0, curr_size - 1);
			break;

		case 8:
			HEAP_SORT(arr2, curr_size);
			break;

		case 9:
			COUNT_SORT(arr2, curr_size);
			break;

		case 10:
			RADIX_SORT(arr2, curr_size);
			break;

		case 11:
			SHELL_SORT(arr2, curr_size);
			break;
		}

		ENDING_TIME = high_resolution_clock::now();
		TIME_SPAN = duration_cast<nanoseconds>(ENDING_TIME - STARTING_TIME);
		Times2.at(LOG((curr_size / ini_size), 2)).operator+=(TIME_SPAN);
		
		if (LOG((curr_size / ini_size), 2)<3){
			STORE_DATA_IN_FILE(data, curr_size, count);

			if (c1==8)
				STORE_RESULT_IN_FILE(arr1, curr_size, c1,1,true,count);
			else
				STORE_RESULT_IN_FILE(arr1, curr_size, c1, 0, true, count);
			delete arr1;

			if (c2 == 8)
				STORE_RESULT_IN_FILE(arr2, curr_size, c2, 1, true, count);
			else
				STORE_RESULT_IN_FILE(arr2, curr_size, c2, 0, true, count);
			delete arr2;
		}
		curr_size *= 2;

		if (curr_size > size && ++count < repeatCount)
			curr_size = ini_size;


	}	

	char micro = -26;
	double time;
	system("cls");
	cout << "Data Size";
	PlaceCursor(16, 0); 
	cout << NAMES[c1 - 1];
	PlaceCursor(50, 0);
	cout<< NAMES[c2 - 1] << "\n__________________________________________________________________________\n";
	for (int i = 0; i <= LOG((size / ini_size), 2); i++){
		PlaceCursor(2, 2 * i + 2);
		cout << pow(2, i)*ini_size;
		
		time= Times1.at(i).count();
		PlaceCursor(20, 2 * i + 2);
		if (time<1000)
			cout << time<<" ns";
		
		else if (time / 1000 < 1000)
			cout << time/1000<< micro << "s" << endl;
		
		else if (time / 1000000 < 1000)
			cout << time / 1000000 << " ms" << endl;
		
		else
			cout << time / 1000000000 << " sec" << endl;
		
		cout << "                   ";
		
		time = Times2.at(i).count();
		PlaceCursor(52, 2 * i + 2);
		if (time<1000)
			cout << time << " ns";

		else if (time / 1000 < 1000)
			cout << time / 1000 << micro << "s" << endl;

		else if (time / 1000000 < 1000)
			cout << time / 1000000 << " ms" << endl;

		else
			cout << time / 1000000000 << " sec" << endl;
	}
	cout << "\n\n\n* The Data used in the whole process have been populated in the files\n";

}

int main(){

	int a1, a2, n, choice, *arr = nullptr, *temp = nullptr;
	double time;
	high_resolution_clock::time_point STARTING_TIME, ENDING_TIME;
	
	n = 0;
	n = POPULATE(arr);
	system("pause");
	system("cls");

	while (true){

		cout << "\nWhat do you want to do?\t\t\t\t(0) for EXIT\n\t1) Bubble Sort\n\t2) Selection Sort\n\t3) Insertion Sort\n\t4) Merge Sort (Top Down)\n\t5) Merge Sort (Bottom Up)\n\t6) Quick Sort\n\t7) Original Hoare Quick Sort\n\t8) Heap Sort\n\t9) Count Sort\n\t10) Radix Sort  (only +ve integers)\n\t11) Shell Sort\n\t12) Refresh Data\n\t13) Comparison of 2 Algos.\n\nEnter Option: ";
		cin >> choice;
		if (choice == 0)
			break;
		
		if (choice==8)
			COPY_ARRAY(arr, temp, n, 1);
		else if (choice>=1 && choice<=11)
			COPY_ARRAY(arr, temp, n);

		
		STARTING_TIME = high_resolution_clock::now();
		switch (choice){

		case 1:
			BUBBLE_SORT(temp, n);
			break;

		case 2:
			SELECTION_SORT(temp, n);
			break;

		case 3:
			INSERTION_SORT(temp, n);
			break;

		case 4:
			MERGE_SORT_TOP_DOWN(temp, 0, n - 1);
			break;

		case 5:
			MERGE_SORT_BOTTOM_UP(temp, n);
			break;

		case 6:
			QUICK_SORT(temp, 0, n - 1);
			break;

		case 7:
			HOARE_QUICK_SORT(temp, 0, n - 1);
			break;

		case 8:
			HEAP_SORT(temp, n);
			break;

		case 9:
			COUNT_SORT(temp, n);
			break;

		case 10:
			RADIX_SORT(temp,n);
			break;

		case 11:
			SHELL_SORT(temp, n);
			break;

		case 12:
			delete arr;
			n = POPULATE(arr);
			break;

		case 13:
			COMPARISON();
			break;

		}

		if (choice>=1 && choice <=11){
			ENDING_TIME = high_resolution_clock::now();
			nanoseconds TIME_SPAN = duration_cast<nanoseconds>(ENDING_TIME - STARTING_TIME);
				
			TIME_PRINT(TIME_SPAN,choice,n);
			if (choice==8)
				STORE_RESULT_IN_FILE(temp,n,choice,1);
			else
				STORE_RESULT_IN_FILE(temp, n,choice,0);
			delete temp;

		}

		cout << endl << endl;
		system("pause");
		system("cls");
	}
	return 0;
}









