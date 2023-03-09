#include <iostream>
#include <cassert>
using namespace std;

template <class T>

class Queue
{
private:
    struct node
    {
        T item;
        node * next;
    };
    // refer to the first element
    node * first;
    // refer to the last element
    node * last;
    int length;

public:
    Queue()
    {
        first = last = NULL;
        length = 0;
    }

    bool empty ()
    {
        return length == 0;
    }

    int size ()
    {
        return length;
    }

    void push (T element)
    {
        node * newnode = new node;
        newnode->item = element;
        // (FIFO) so we push from the back
        if (empty ())
        {
            newnode->next = NULL;
            first = last = newnode;
        }

        else
        {
            // push from the back
            // conect the previous node with next one
            last->next = newnode;
            // it's the last one
            newnode->next = NULL;
            // to be the next last one
            last = newnode;
        }
        length++;
    }

    void pop ()
    {
        assert (!empty ());
        // delete from the front 
        node * cur = first; // to delete by it
        // move to the next node node to be the next front
        first = first->next;
        // the delete operation
        cur->next = NULL;
        delete cur;
        cur = NULL;
        length--;
    }

    T front ()
    {
        return first->item;
    }

    T back ()
    {
        return last->item;
    }

    void print ()
    {
        cout << "[ ";
        for (node *cur = first; cur != NULL; cur = cur->next)
            cout << cur->item << ' ';
        cout << " ]\n";
    }

    bool search (T elemnt)
    {
        for (node * cur = first; cur != NULL; cur = cur->next)
        {
            if (cur->item == elemnt)
                return true;
        }
        return false;
    }

    // to delete all the nodes
    void clear ()
    {
        node *cur = first;
        while (cur != NULL)
        {
            // move it to be as a port for cur
            first = first->next;
            cur->next = NULL;
            delete cur;
            cur = first;
        }
        first = last = cur = NULL;
    }
    ~Queue()
    {
        clear ();
    }
};

void last_k_elements (int k , Queue <int> & q , int n)
{
    Queue <int> q1;
    int ans = 0;
    for (int i = 1; i <= n; i++)  // k = 4 (1 2 3 4 5 6 7) -> 1 , 3 , 6 , 10 , 14 , 18 , 22
    {                             // u add the elments to the prev one and if the size > k u should add the last k elements
        q1.push (q.front ());
        if (i <= k)
            ans += q.front ();

        else
        {
            ans += q.front ();
            ans -= q1.front ();
            q1.pop ();
        }
        q.pop ();
        cout << ans << ' ';
    }
    cout << endl;
}

int main ()
{
    Queue <int> q;
    int size;
    cout << "Enter the size : ";
    cin >> size;
    int n = size;
    while (size--)
    {
        int x;
        cin >> x;
        q.push (x);
    }
    q.print ();
    cout << q.front () << ' ' << q.back () << '\n';
    (q.search (5)) ? cout << "Found !\n" : cout << "Not Found !\n";

    int k;
    cout << "Enter the k elements : ";
    cin >> k;
    last_k_elements (k , q , n);
}