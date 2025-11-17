/*  */

#include<iostream>
#include<string>
using namespace std;

class User
{
  long int num;
  string name;
  float billAmount;
  
  User()
  {
   num = 0;
   name = " ";
   billAmount = 0;
  }
  
  friend class Record;

};

class Record
{

  User u[10];
  
  public: 
  int n;
  void accept();
  void display();
  void quicksort(int lo, int hi);
  void heapsort();
  void heapify(int n, int i);
  int partition(int lo, int hi);
  void mergesort(int lo, int hi);
  void merge(int lo, int mid, int hi);
  
  
  void linearSearch(long int searchNum);
  
  
  void binarySearch(long int searchNum);
  
};

void Record :: accept()
{
cout << " Enter number of users:" << endl;
cin >> n;
  cout<<" Enter mobile number, name, bill amount for "<<n<< " users:" << endl;
  
  for(int i=0; i<n; i++)
  {
   cin >> u[i].num >> u[i].name >> u[i].billAmount;
  }

}

void Record :: display()
{
   cout<<" number \t name \t bill amount " << endl;
   
  for(int i=0; i<n; i++)
  {
   cout << u[i].num << "\t" << u[i].name << "\t" << u[i].billAmount << endl;
   }

}

void Record :: heapify(int n, int i)
{
  int largest = i;
  int left = 2*i + 1;
  int right = 2*i + 2;
  
  if(left<n && u[left].num > u[largest].num)
  {
   largest = left;
   }
   
    if(right<n && u[right].num > u[largest].num)
  {
   largest = right;
   }
   
   if(largest != i)
   {
    swap(u[i], u[largest]);
    heapify(n, largest);
    
   }
}

void Record :: heapsort()
{
    for(int i = n/2-1; i>=0; i--)
    {
       heapify(n, i);
    }
 
for(int i = n-1; i>0; i--)
    {
    swap(u[0], u[i]);
       heapify(i, 0);
    }

}

int Record :: partition(int lo, int hi)
{
long int pivot = u[hi].num;
int i = lo - 1;

for(int j = lo; j < hi; j++)
{
	if(u[j].num > pivot)
	{
		i++;
		swap(u[i], u[j]);
	}
}
swap(u[i + 1], u[hi]);
return i + 1;
}

void Record :: quicksort(int lo, int hi)
{
	if(lo < hi)
	{
		int pi = partition(lo, hi);
		quicksort(lo, pi - 1);
		quicksort(pi + 1, hi);
	}
}

void Record :: mergesort(int lo, int hi)
{
	if(lo < hi)
	{
		int mid = (lo + hi) / 2;
		mergesort(lo, mid);
		mergesort(mid + 1, hi);
		merge(lo, mid, hi);
	}
}

void Record :: merge(int lo, int mid, int hi)
{
	int n1 = mid - lo + 1;
	int n2 = hi - mid;
	
	User left[n1], right[n2];
	
	for(int i = 0; i < n1; i++)
	{
		left[i] = u[lo + i];
	}
	for(int j = 0; j < n2; j++)
	{
		right[j] = u[mid + 1 + j];
	}
	int i = 0, j = 0, k = lo;
	
	while(i < n1 && j < n2)
	{
		if(left[i].num < right[j].num)
		{
			u[k] = left[i];
			i++;
		}else
		{
			u[k] = right[j];
			j++;
		}
		k++;
	}
	while(i < n1)
	{
		u[k] = left[i];
		i++;
		k++;
	}
	while(j < n2)
	{
		u[k] = right[j];
		i++;
		k++;
	}
}

void Record::linearSearch(long int searchNum) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (u[i].num == searchNum) {
            cout << "User found: " << endl;
            cout << "Mobile Number: " << u[i].num << endl;
            cout << "Name: " << u[i].name << endl;
            cout << "Bill Amount: " << u[i].billAmount << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "User with mobile number: " << searchNum << " not found." << endl;
    }
}
                                                                                                                                    
void Record::binarySearch(long int searchNum) {
    int low = 0, high = n - 1;
    bool found = false;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (u[mid].num == searchNum) {
            cout << "User found: " << endl;
            cout << "Mobile Number: " << u[mid].num << endl;
            cout << "Name: " << u[mid].name << endl;
            cout << "Bill Amount: " << u[mid].billAmount << endl;
            found = true;
            break;
        } else if (u[mid].num < searchNum) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    if (!found) {
        cout << "User with mobile number " << searchNum << " not found." << endl;
    }
}

int main()
{
  Record r;
  r.accept();
  cout << endl;
  r.display();
  cout << endl;

  
  r.quicksort(0, r.n - 1);
  cout << "Data sorted in descending order of mobile no." << endl;
  r.display();
  cout << endl;

  r.mergesort(0, r.n - 1);
  cout << "Data sorted in ascending order of mobile no." << endl;
  r.display();
  cout << endl;

  cout << "Data sorted with Heap sort" << endl;
  r.heapsort();
  r.display();
  cout << endl;

 
  long int searchNum;
  cout << "Enter mobile number to search (Linear Search): ";
  cin >> searchNum;
  r.linearSearch(searchNum);

  
  cout << "Enter mobile number to search (Binary Search): ";
  cin >> searchNum;
  r.binarySearch(searchNum);

  return 0;
}
