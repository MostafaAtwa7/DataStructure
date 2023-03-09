#include <iostream>
#include <cassert>
#include <queue>
#include <deque> 
using namespace std;

/* at this problem we use it to get the max element in the queue at every push and pop */
struct monotonic_queue
{
    // push all the element on it
    queue <int> q;
    // contain the max element on every push
    deque <int> dq;

    void push (int element)
    {
        q.push (element);
        // we push from the back always to but the max element at every push
        while (!dq.empty () && dq.back () < element)
        {
            dq.pop_back ();
        }
        dq.push_back (element);
    }

    int Max ()
    {
        assert (!q.empty ());
        return dq.front ();
    }

    void pop ()
    {
        assert (!q.empty ());
        // if the element u delete from the queue is the max
        if (q.front () == dq.front ())
            dq.pop_front ();
        q.pop ();
    }

    int size () // O(1)
    {
        return q.size ();
    }

    bool empty ()
    {
        return q.empty ();
    }

    void clear () // O(n)
    {
        dq.clear ();
        while (!q.empty())
        {
            q.pop ();
        }
    }
};

int main ()
{
    monotonic_queue q;
    cout << "Enter the size : ";
    int n;
    cin >> n;
    while (n--)
    {
        int x;
        cin >> x;
        q.push (x);
        cout << q.Max () << '\n';
    }
    q.pop ();
    cout << q.Max () << '\n';

    q.pop ();
    cout << q.Max () << '\n';

    q.pop ();
    cout << q.Max () << '\n';

    q.pop ();
    cout << q.Max () << '\n';
}

