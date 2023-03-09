#include <iostream>
#include <cassert>
using namespace std;

class Stack
{
private:
    int size; 
    int top;
    int * arr {};

public:
    Stack()
    {
        size = 100;
        top = -1;
        arr = new int[size];
    }
    bool full ()
    {
        return top == size - 1;
    }

    bool empty ()
    {
        return top == -1;
    }

    void push (int element)
    {
        assert (!full ());
        arr[++top] = element;
    }

    void pop ()
    {
        assert (!empty ());
        top--;
    }

    int peek ()
    {
        assert (!empty ());
        return arr[top];
    }

    void display ()
    {
        cout << "[ ";
        for (int i = top; i >= 0; i--)
            cout << arr[i] << ' ';
        cout << "]\n";
    }

    void clear ()
    {
        delete[] arr;
    }
    ~Stack ()
    {
        clear ();
    }
};

struct monotonic_stack
{
    // s1 use to push all elements and the s2 use to push the max elements at every push
    Stack s1 , s2;
    void push (int n)
    {
        s1.push (n);
        // to push at s2 the element should be bigger than the top or the stack be empty
        if (s2.empty () || n >= s2.peek ())
            s2.push (n);
    }

    void pop ()
    {
        if (s1.peek () == s2.peek ())
            s2.pop ();
        s1.pop ();
    }

    int Max ()
    {
        return s2.peek ();
    }

    void clear ()
    {
        s2.clear ();
        s1.clear ();
    }
};

int main ()
{
    monotonic_stack s;
    int n;
    cout << "Enter the size : ";
    cin >> n;
    while (n--)
    {
        int x;
        cin >> x;
        s.push (x);
        cout << s.Max () << '\n';
    }
    s.pop ();
    cout << s.Max () << '\n';
    s.pop ();
    cout << s.Max () << '\n';
    s.pop ();
    cout << s.Max () << '\n';
}