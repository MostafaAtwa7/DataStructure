#include <iostream>
#include <cassert>
using namespace std;

template <class T>

class Deque
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
    Deque()
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

    void push_back (T element)
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

    void push_front (T element)
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
            // conect the node with first one
            newnode->next = first;
            // move the first to be the next first 
            first = newnode;
        }
        length++;
    }

    void pop_back ()
    {
        assert (!empty ());
        // ptr to reach to the last node and use to delete the node
        node * cur = first->next;
        // like the port for last 
        node *prev = first;
        
        while (cur != last)
        {
            prev = cur;
            cur = cur->next;
        }
        // dlete the conection with last node
        prev->next = NULL;
        // move the last to the prev node till the last node ready for deletion
        last = prev;
        // make the delete 
        delete cur;
        cur = prev = NULL;
        length--;
    }

    void pop_front ()
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
        cout << "]\n";
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
    ~Deque()
    {
        clear ();
    }
};


int main ()
{
    Deque <int> dq;
    int n;
    cout << "Enter the size : ";
    cin >> n;
    while (n--)
    {
        int x;
        cin >> x;
        dq.push_back (x);
    }
    dq.push_front (0);
    dq.print ();
    dq.pop_front ();
    dq.pop_back ();
    dq.print ();
    cout << dq.size () << '\n';
}