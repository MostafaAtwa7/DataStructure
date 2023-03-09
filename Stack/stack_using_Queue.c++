#include <iostream>
#include <cassert>
using namespace std;


class Queue
{
private:
    struct node
    {
        int item;
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

    void push (int element)
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

    int front ()
    {
        return first->item;
    }

    int back ()
    {
        return last->item;
    }

    void print ()
    {
        cout << "[ ";
        for (node *cur = first; cur != NULL; cur = cur->next)
            cout << cur->item << ' ';
        cout << "]\n";
    }

    bool search (int elemnt)
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

class stack_using_Queue
{
private:
    Queue Q;
    
public:
    void push (int element)
    {
        // her what i'll do is that every time i push i will reverse the queue
        Q.push (element);
        for (int i = 0; i < Q.size (); i++)
        {
            Q.push (Q.front ());
            Q.pop ();
        }
    }

    void pop ()
    {
        Q.pop ();
    }

    int top ()
    {
        return Q.front();
    }

    void print ()
    {
        Q.print ();
    }

    int size ()
    {
        return Q.size ();
    }

    bool empty ()
    {
        return Q.empty ();
    }

    void clear ()
    {
        Q.clear ();
    }
};

int main ()
{
    stack_using_Queue st;
    int n;
    cout << "Enter the size : ";
    cin >> n;
    while (n--)
    {
        int x;
        cin >> x;
        st.push (x);
    }
    st.print ();
    cout << st.top () << '\n';
    st.pop ();
    st.print ();
    cout << st.top () << '\n';
}