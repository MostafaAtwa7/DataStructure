#include <iostream>
#include <assert.h>
using namespace std;

template <class T>

class Queue
{
private:
    int rear;
    int front;
    // counter increment if we add element and decrement when we delete 
    int counter;
    // assine to it the user's size
    int maxSize;
    // use dinamic arr
    T *arr;

public:
    //--------use parmetrize constractor becase user will enter the size of arr--------//
    Queue(int size)
    {
        if (size <= 0)
            maxSize = 200;

        else
            maxSize = size;

        // the dinamic array
        arr = new T[maxSize];
        front = 0;
        rear = maxSize - 1;
        counter = 0;
    }

    //-----check if the array is empty------//
    bool IsEmpty()
    {
        return counter == 0;
    }

    //-----check if the array is Full------//
    bool IsFull()
    {
        return counter == maxSize;
    }

    //-----use to add elements-----//
    void Insert(T element)
    {
        if (IsFull())
            cout << "Full Queue !\n";

        else
        {
            rear = (rear + 1) % maxSize;
            arr[rear] = element;
            counter++;
        }
    }

    //-----use to delete elements-----//
    void pop()
    {
        if (IsEmpty())
            cout << "Empty Queue !\n";

        else
        {
            front = (front + 1) % maxSize;
            counter--;
        }
    }

    //-----use to get the first element-----//
    T Front()
    {
        assert(!IsEmpty());
        return arr[front];
    }

    //-----use to get the last element-----//
    T back()
    {
        assert(!IsEmpty());
        return arr[rear];
    }

    //----the print-----//
    void print()
    {
        if (!IsEmpty())
        {
            cout << "[ ";
            for (size_t i = front; i != rear; i = (i + 1) % maxSize)
            {
                cout << arr[i] << ' ';
            }
            cout << arr[rear] << ' ';
            cout << " ]\n";
        }
        
        else
        {
            cout << "Empty Queue !\n";
        }
    }

    //-----search if the element exiset---//
    bool search(T element)
    {
        if (!IsEmpty())
        {
            for (size_t i = front; i != rear; i = (i + 1) % maxSize)
            {
                if (element == arr[i])
                    return true;
            }

            if (arr[rear] == element)
                return true;

            return false;
        }

        else
        {
            cout << "Empty Queue !\n";
            return false;
        }
    }
};

int main()
{
    int n;
    cout << "Enter size : ";
    cin >> n;
    Queue<int>s(n);

    while (n--)
    {
        int x;
        cin >> x;
        s.Insert(x);
    }
    s.print();
    cout << s.Front() << '\n';
    cout << s.back() << '\n';
    int num ;
    cout << "Enter the search : ";
    cin >> num;
    (s.search(num)) ? cout << "found\n" : cout << "not found\n";
}