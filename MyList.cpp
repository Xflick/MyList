#include<iostream>
using namespace std;
template<class T>
class MyList;
template<class T>
ostream &operator<<(ostream &os, const MyList<T> &obj);
template<class T>
MyList<T> operator + (const MyList<T> &l1, const MyList<T> &l2);
template<class T>
MyList<T> operator + (const MyList<T> &l1, const T &item);
template<class T>
void mergeArray(T *a, int first, int mid, int last, T *tmp, bool less);
template<class T>
void mergeSortTmp(T *a, int first, int last, T *tmp, bool less);
template<class T>
void mergeSort(T *a, int n, bool less);


template<class T>
class MyList{
private:
	T *a;
	int size;   //the used size
	int sizeMax;    //the max elements can be stored now
	void double_space();    //double the size of list
public:
	MyList(){
		size = 0;
		sizeMax = 100;
		a= new T[sizeMax];
	}
	MyList(int num, const T &item); //construct a list with an item repeated num times
	MyList(const MyList &l);    //copy a list
    MyList(T* arr, int len);    //construct a list with the first few elements in another list

	void push(const T &item);   //add an item to the end of list
	T pop();    //delete the last element in the list and return that element
	void insert(int index, const T &item);  //insert item to place
	void clean();   //clean the list
	int get_size() const;   //return the size of the list
	void erase(int start, int end); //delete elements whose index is from start to end
	T get_item(int index) const;    //return the specific item
	MyList get_item(int start, int end) const;  //return elements whose index is from start to end(Negative number is valid)
	int count(const T &item) const; //return the number of the appearance of a specific item
	void remove(const T &item); //delete the first item match to the argument


	friend MyList operator + <>(const MyList<T> &l1, const MyList<T> &l2);  //combine two lists
    friend MyList operator + <>(const MyList<T> &l1, const T &item);    //same with push method, but return a new list
	MyList &operator = (const MyList<T> &l);    //assignment
	MyList &operator += (const T &item);    //same with push method
	MyList &operator += (const MyList<T> &l);   //add a list to the end of another list
	T &operator [](int index) const;    //return a specific item
	friend ostream & operator<< <>(ostream &os, const MyList<T> &obj);  //print the elements in the list in the following format:
    // [1, 2, 5, 4, 1]

	void sort(bool less=true);  //sort the list
    // if less=true, from small to big; else, from big to small
	void reverse(); //reverse the list

	~MyList(){delete [] a;} //free the memory
};

template<class T>
void MyList<T>::double_space()
{
    if (size != 0)
    {
        T *tmp = new T[size * 2];
        for (int i = 0; i < size; ++i)  //copy the original list into a bigger list
        {
            tmp[i] = a[i];
        }
        sizeMax = size * 2;
        delete [] a;
        a = tmp;
    }
    else
    {
        T *tmp = new T[1];
        delete [] a;
        a = tmp;
        sizeMax = 1;
    }

}

template<class T>
MyList<T>::MyList(int num, const T &item)
{
    try
    {
        if (num > 0)
        {
            size = num;
            sizeMax = size;
            a = new T[size];
            for (int i = 0; i < size; ++i)  //repeat num times to copy the item into the list
            {
                a[i] = item;
            }
        }
        else
            throw -1;
    }
    catch(int err)
    {
        cout << "Num should be greater than 0.";
    }

}

template<class T>
MyList<T>::MyList(const MyList &l)
{
    size = l.get_size();
    sizeMax = size;
    a = new T[size];
    for (int i = 0; i < size; ++i)  //copy the elements to the new list
    {
        a[i] = l[i];
    }
}

template<class T>
MyList<T>::MyList(T* arr, int len)
{
    size = len;
    sizeMax = size;
    a = new T[size];
    for (int i = 0; i < size; ++i)  //copy the elements to the new list
    {
        a[i] = arr[i];
    }
}

template<class T>
void MyList<T>::push(const T &item)
{
    if (size + 1 > sizeMax) //if the size is not big enough
    {
        MyList<T>::double_space();  //double the space
    }
    a[size] = item; //push the item
    ++size;
}

template<class T>
T MyList<T>::pop()
{
    try
    {
        if (size > 0)
        {
            T tmp = a[size - 1];
            --size;
            return tmp;
        }
        else    //when the list s empty
        {
            throw -1;
        }
    }
    catch(int err)
    {
        cout << "Pop is not supported when array has no elements.";
    }

}

template<class T>
void MyList<T>::insert(int index, const T &item)
{
    try
    {
        if (index >= 0 && index < size) //whether the index is valid
        {
            if (size + 1 > sizeMax) //when the size is not big enough
            {
                MyList<T>::double_space();
            }
            for (int i = size - 1; i >= index; --i)
            {
                a[i + 1] = a[i];    //to have the space for the new element
            }
            a[index] = item;
        }
        else
            throw -1;
    }
    catch(int err)
    {
        cout << "Invalid Index.";
    }
}

template<class T>
void MyList<T>::clean()
{
    delete [] a;
    size = 0;
    sizeMax = 0;
}

template<class T>
int MyList<T>::get_size() const
{
    return size;
}

template<class T>
void MyList<T>::erase(int start, int end)
{
    try
    {
        if (start >= 0 && end < size && end >= start)
        {
            int j = 0;
            for (int i = end + 1; i < size; ++i)
            {
                a[start + j] = a[i];    //cover the elements which should be erased
                ++j;
            }
            size -= (end - start + 1);
        }
        else
            throw -1;
    }
    catch(int err)
    {
        cout << "Invalid Start or End.";
    }
}

template<class T>
T MyList<T>::get_item(int index) const
{
    try
    {
        if (index < size )  //whether the index is valid
            return a[index];
        else
            throw -1;
    }
    catch(int err)
    {
        cout << "Index out of range.";
    }
}

template<class T>
MyList<T> MyList<T>::get_item(int start, int end) const
{
    try
    {
        if (start < 0)  //get the actual start
            start = size + start;
        if (end < 0)    //get the actual end
            end = size + end;
        if (start >= 0 && end < size && end >= start)   //whether start and end is valid
        {
            MyList<T> tmp;
            for (int i = start; i < end + 1; ++i)
            {
                tmp.push(a[i]); //construct the result list
            }
            return tmp;
        }
        else
        {
            throw -1;
        }
    }
    catch(int err)
    {
        MyList<T> tmp;  //return an empty list
        tmp.clean();
        return tmp;
    }
}

template<class T>
int MyList<T>::count(const T &item) const
{
    int cnt = 0;
    for (int i = 0; i < size; ++i)
    {
        if (a[i] == item)
            ++cnt;
    }
    return cnt;
}

template<class T>
void MyList<T>::remove(const T &item)
{
    for (int i = 0; i < size; ++i)
    {
        if (a[i] == item)
        {
            erase(i, i);    //erase the specific element
            break;
        }
    }
}

template<class T>
MyList<T> operator + (const MyList<T> &l1, const MyList<T> &l2)
{
    MyList<T> result(l1);   //copy l1 to result list
    for (int i = 0; i < l2.get_size(); ++i)
        result.push(l2[i]); //push the elements of 12 to result
    return result;
}

template<class T>
MyList<T> operator + (const MyList<T> &l1, const T &item)
{
    MyList<T> result(l1);   //copy l1 to result list
    result.push(item);
    return result;
}

template<class T>
MyList<T> &MyList<T>::operator = (const MyList<T> &l)
{
    if (this == &l) return *this;   //when the left equals to the right
    size = l.get_size();
    sizeMax = size;
    delete [] a;    //clean the list
    a = new T[size];
    for (int i = 0; i < size; ++i)
        a[i] = l[i];
    return *this;
}

template<class T>
MyList<T> &MyList<T>::operator += (const T &item)
{
    if (size + 1 > sizeMax)
    {
        MyList<T>::double_space();
    }
    a[size] = item;
    ++size;
    return *this;
}

template<class T>
MyList<T> &MyList<T>::operator += (const MyList<T> &l)
{
    while (true)
    {
        if (size + l.get_size() > sizeMax)
        {
            MyList<T>::double_space();
        }
        else
            break;
    }
    for (int i = size; i < size + l.get_size(); ++i)
    {
        a[i] = l[i - size];
    }
    size += l.get_size();
    return *this;
}

template<class T>
T &MyList<T>::operator [] (int index) const
{
    try
    {
        if (index < size )
            return a[index];
        else
            throw -1;
    }
    catch(int err)  //invalid index
    {
        cout << "Index out of range.";
    }
}

template<class T>
ostream& operator << (ostream &os, const MyList<T> &obj)
{
    if (obj.get_size() > 0)
    {
        os << "[";
        for (int i = 0; i < obj.get_size() - 1; ++i)
        {
            os << obj[i] << ", ";
        }
        os << obj[obj.get_size() - 1] << "]";
        return os;
    }
    else if (obj.get_size() == 0)   //if the list is empty
    {
        cout << "[]";
    }
}

template<class T>
void MyList<T>::sort(bool less)
{
    mergeSort(a, size, less);   //use merge sort to sort the elements
}

template<class T>
void MyList<T>::reverse()
{
    T tmp;
    for (int i = 0; i < size / 2; ++i)
    {
        tmp = a[i]; //exchange the bottom to the top
        a[i] = a[size - i - 1];
        a[size - i - 1] = tmp;
    }
}

template<class T>
void mergeArray(T *a, int first, int mid, int last, T *tmp, bool less)
{
    int i = first, j = mid + 1;
    int k = 0;
    while (i <= mid && j <= last)
    {
        if (less)
        {
            if (a[i] <= a[j])
                tmp[k++] = a[i++];
            else
                tmp[k++] = a[j++];
        }
        else
        {
            if (a[i] >= a[j])
                tmp[k++] = a[i++];
            else
                tmp[k++] = a[j++];
        }

    }
    while (i <= mid)    //copy the rest elements
        tmp[k++] = a[i++];
    while (j <= last)   //copy the rest elements
        tmp[k++] = a[j++];
    for (i = 0; i < k; ++i) //copy tmp to a
        a[first + i] = tmp[i];
}

template<class T>
void mergeSortTmp(T *a, int first, int last, T *tmp, bool less)
{
    if (first < last)
    {
        int mid = (first + last) / 2;
        mergeSortTmp(a, first, mid, tmp, less); //sort the left half
        mergeSortTmp(a, mid + 1, last, tmp, less);  //sort the right half
        mergeArray(a, first, mid, last, tmp, less); //combine two halves
    }
}

template<class T>
void mergeSort(T *a, int n, bool less)  //the merge sort method
{
    T *tmp;
    tmp = new T[n];
    mergeSortTmp(a, 0, n - 1, tmp, less);
    delete [] tmp;
}


int main(){
	MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i)
		a.push(i);
    // a = [0, 1, 2, 3, 4]
	a[3] = 15; // a = [0, 1, 2, 15, 4]
	a.sort(); // a = [0, 1, 2, 4, 15]
	a.reverse(); // a = [15, 4, 2, 1, 0]
	a += 12; // a = [15, 4, 2, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a[i]<<endl;
    b = a.get_item(4, -3); // b = [] *if start > end，return the empty list
	b = a.get_item(3, -1); // b = [1, 0, 12]
	a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a.get_item(i)<<endl;
	cout<<a.count(5)<<endl;
	b.clean(); // b = []
	cout<<b.get_size()<<endl;
	a.erase(2, 5); // a = [15, 4, 0, 12]
	b = a + a; // b = [15, 4, 0, 12, 15, 4, 0, 12]
	b.insert(3, 116); // b = [15, 4, 0, 116, 12, 15, 4, 0, 12]
	b.remove(4); // b = [15, 0, 116, ...]
	cout<<b<<endl;
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout<<c.get_item(100, 105)<<endl;

	return 0;
}

