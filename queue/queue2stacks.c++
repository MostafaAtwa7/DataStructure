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

    ~Stack ()
    {
        delete[] arr;
    }
};

/* we will use 2 stacks to impelement this queue one use to put the elemet when u push 
    and it use also to get the elements and the othe use to pop the elements and */

class queue2stacks
{
private:
    // use this to push all the elements
    Stack s1;
    // use to pop the first element we push by push the element s1 on it and return it back
    Stack s2;
    // the function using for pop
    void move (Stack & from , Stack & to)
    {
        // first we add all the element on s1 to s2
        while (!from.empty ())
        {
            to.push (from.peek());
            from.pop ();
        }
    }

public:
    void push (int element) // O(1)
    {
        s1.push (element);
    }

    void pop () // O(n)
    {
        move (s1 , s2);
        // delete the element after moveing to the sec stack
        s2.pop ();
        // retrun the elements to the first stack again
        move (s2 , s1);
    }

    void display ()
    {
        move (s1 , s2);
        s2.display ();
    }
    
    bool empty ()
    {
        return s1.empty ();
    }
};

int main ()
{
    queue2stacks q;
    int n;
    cout << "Enter the size : ";
    cin >> n;
    while (n--)
    {
        int x;
        cin >> x;
        q.push (x);
    }
    q.display ();
    q.pop ();
    q.display ();
}