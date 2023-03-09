#include <iostream>
#include <algorithm>
#include <string>
#include <cassert>
using namespace std;
/*
the function we will impelement ?!!
1- push : use to add elements
2- pop : use to delete elements
3- reverse : reverse the stack 
4- print : print the stack 
5- peek : return the top of the stack
6- empty : to check if is empty stack
7- size : to get the size
8- clear : to  delete all the stack

the exercises :
1- balanced parenthese
3- remove adjacent string
2- reverse a string use stack
3- reverse a number  
*/

template <class T>

class Stack
{
private:
    struct node
    {
        T item;
        node * next;
    };
    // refer to the top
    node * top;
    // get the lenght
    int length;

public:
    Stack()
    {
        top = NULL;
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
        //  first build the node
        node * newnode = new node;
        newnode->item = element;
        // make the ptr of the newnode refer to the previous one
        newnode->next = top;
        // move the top to the next node
        top = newnode;
        length++;
    }

    void pop ()
    {
        // this send u a massege error when the stack is empty and you want to pop element
        assert (!empty ());
        // cur use to refer to the node top
        node *cur = top;
        // move the top to the new node
        top = top->next;
        // delete the top
        delete cur;
        cur = NULL;
        length--;
    }

    T peek ()
    {
        assert (!empty ());
        return top->item;
    }

    void print ()
    {
        assert (!empty ());
        // print all the nodes until reach to null
        cout << "[ ";
        for (node * cur = top; cur != NULL; cur = cur->next)
            cout << cur->item << ' ';
        cout << "]\n";
    }

    void reverse_stack ()
    {
        // use to reverce the conection with it
        node * prev = NULL;
        // use to make the conection refer to prev
        node * cur = top;
        // this is our guid
        node * next = top->next;

        while (cur != NULL)
        {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        // after finishing make the top at the first node
        top = prev;
    }

    void clear ()
    {
        // use to delete all the nodes
        node * cur = NULL;
        while (cur != NULL)
        {
            // move the cur to the top ptr every time
            cur = top;
            // move the top to the next node
            top = top->next;
            // delete the cur node
            cur->next = NULL;
            delete cur;
        }
        length = 0;
    }

    ~Stack()
    {
        clear ();
    }
};

// ------------- balanced paernthese --------------//
bool arepair (char open , char close)
{
    return ((open == '(' && close == ')') || (open == '{' && close == '}') || (open == '[' && close == ']'));
}

bool balanced (string s)
{
    Stack <char> st;
    for (int i = 0; i < s.size (); i++)
    {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[')  
            st.push (s[i]);
        else
        {
            if (st.empty() || !arepair (st.peek () , s[i]))
                return false;
            st.pop ();
        }
    }
    return st.empty ();
}
// ----------------------------------------------//

// ------------------ remove adjecent ------------//
string adj (string s)
{
    Stack <char> st;
    for (int i = 0; i < s.size (); i++)
    {
        if (!st.empty () && st.peek () == s[i])
            st.pop ();
        else 
            st.push (s[i]);
    }
    s = "";
    while (!st.empty ())
    {
        s = st.peek () + s; // != s += st.peek () -> because her u add the top to string but we need to add the string to top
        st.pop ();
    }
    return s;
}
// -----------------------------------------------//

// -------------------- reverse a string ---------------//
string reverse_string (string s)
{
    string res = "";
    Stack <char> st;
    for (int i = 0; i < s.size (); i++)
    {
        if (i == s.size () - 1)
            st.push (s[i]);
        if (s[i] == ' ' || i == s.size () - 1)
        {
            while (!st.empty ())
            {
                res += st.peek ();
                st.pop ();
            }
            if (s[i] == ' ')
                res += ' ';
        }
        else 
            st.push (s[i]);
    }
    return res;
} 
//-----------------------------------------------------//

// -------------------- reverse a number ---------------//
int reverse_num (int n)
{
    Stack <int> st;
    int mult = 1;
    while (n)
        st.push (n % 10) , n /= 10;
    while (!st.empty())
    {
        n = st.peek () * mult + n;
        mult *= 10;
        st.pop ();
    }
    return n;
} 
//-----------------------------------------------------//

// ---------------- astroid ------------//
void astorid (int a[] , int x)
{
    Stack <int> st;
    for (int i = 0; i < x; i++)
    {
        if (!st.empty () && (st.peek () > 0 && a[i] < 0))
            st.pop ();
        else 
            st.push (a[i]); 
    }
    st.reverse_stack ();
    while (!st.empty ())
    {
        cout << st.peek () << ' ';
        st.pop ();
    }
}
// -----------------------------------//
int main ()
{
    Stack <int> s;
    int n;
    cout << "Enter the size : ";
    cin >> n;
    while (n--)
    {
        int x;
        cin >> x;
        s.push (x);
    }
    s.print ();
    s.pop ();
    s.reverse_stack ();
    s.print ();
    cout << s.size () << '\n';
    cout << s.peek () << '\n';

    cout << "\nEnter the string u want to reverse : ";
    string line;
    getline (cin , line);
    cout << reverse_string (line) << '\n';

    cout << "\nEnter the number u want to reverse : ";
    int num;
    cin >> num;
    cout << reverse_num (num) << '\n';

    cout << "\nEnter the formula : ";
    string str;
    cin >> str;
    (balanced (str)) ? cout << "Balanced !\n" : cout << "Not Balanced !\n";

    cout << "\nEnter the string : ";
    cin >> str;
    cout << adj (str) << '\n';

    cout << "\nEnter the size : ";
    int x;
    cin >> x;
    int a[x];
    for (int i = 0; i < x; i++)
        cin >> a[i];
    astorid (a , x);
}