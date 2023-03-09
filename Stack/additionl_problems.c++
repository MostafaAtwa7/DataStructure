#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;
template <class t>
class Stack
{
private:
    int n; 
    int top;
    t * arr {};

public:
    Stack()
    {
        n = 100;
        top = -1;
        arr = new t[n];
    }

    bool full ()
    {
        return top == n - 1;
    }

    bool empty ()
    {
        return top == -1;
    }

    void push (t element)
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

    void insert_bottom (t element)
    {
        if (empty ())
            push (element);
        else
        {
            int cur = peek ();
            pop ();
            insert_bottom (element);
            push (cur);
        }
    }

    void reverse ()
    {
        if (empty ())
            return;
        int cur = peek ();
        pop ();
        reverse ();
        insert_bottom (cur);
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

    int size ()
    {
        return (top + 1);
    }

    ~Stack ()
    {
        clear ();
    }
};

int score(string str) {
	// Each integer represents total sum added to this parent Parentheses
	Stack <int> st;

	// temp value to help us
	st.push(0);

	for (int i = 0; i < (int)str.size(); ++i) 
    {
		char c = str[i];

		if (c == '(') 
			st.push(0);	// new parent: current sum = 0

        else 
        {
			int last = st.peek();
			st.pop();

			if (last == 0)
				last = 1;		// case ()
			else
				last *= 2;		// case (A). Get current sum and multiply

			int parent_par = st.peek() + last;	// new total sum
			st.pop();
			st.push(parent_par);
		}
	}
	return st.peek();
}

// infex and postfix expretions problems
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%');
}

int precedence(char op) 
{
	if (op == '+' || op == '-')
		return 1;
	else if (op == '*' || op == '/' || op == '%')
		return 2;
	else if (op == '^')
		return 3;
	return 0;
}

string postfix (string s)
{
    Stack <char> st;
    string ans = "";

    for (int i = 0; i < s.size (); i++)
    {
        if (isdigit (s[i]) || islower (s[i]) || isupper (s[i]))
            ans += s[i];
        else
        {
            if (st.empty () || s[i] == '(')
                st.push (s[i]);

            else if (s[i] == ')')
            {
                while (st.peek () != '(')
                {
                    ans += st.peek ();
                    st.pop ();
                }
                st.pop ();
            }

            else
            {
                if (s[i] == '^' && st.peek () == '^')
                    st.push (s[i]);
                else if (precedence (st.peek ()) < precedence (s[i]))
                    st.push (s[i]);
                else
                {
                    while (!st.empty () && st.peek () != '(' && precedence (st.peek ()) >= precedence (s[i]))
                    {
                        ans += st.peek ();
                        st.pop ();
                    }
                    st.push (s[i]);
                }
            }
            
        }
    }
    while (!st.empty ())
    {
        ans += st.peek ();
        st.pop ();
    }
    
    return ans;
}

string Prefix(string infix) {
    // Reverse the input infix expression
    reverse(infix.begin(), infix.end());

    // Create an empty stack and an empty prefix string
    Stack <char> st;
    string str;

    // Loop through each character in the infix expression
    for (char c : infix) {
        // If the character is an operand, add it to the prefix string
        if (isdigit(c) || islower (c) || isupper (c))
            str += c;
        // If the character is a closing parenthesis, push it onto the stack
        else if (c == ')')
            st.push(c);
        // If the character is an operator or an opening parenthesis
        else if (isOperator(c) || c == '(') {
            // If the stack is empty or the top of the stack is a closing parenthesis
            // or an operator with lower precedence than the current operator,
            // push the current operator onto the stack
            if (st.empty() || st.peek() == ')' || precedence(c) > precedence(st.peek() ))
                st.push(c);
            // Otherwise, pop operators from the stack and add them to the prefix string
            // until an opening parenthesis or an operator with lower precedence is encountered,
            // then push the current operator onto the stack
            else {
                while (!st.empty() && st.peek()  != ')' && precedence(c) <= precedence(st.peek())) {
                    str += st.peek() ;
                    st.pop();
                }
                st.push(c);
            }
        }
    }

    // Pop any remaining operators from the stack and add them to the prefix string
    while (!st.empty()) {
        if (st.peek () != '(' || st.peek () != ')')
            str += st.peek ();
        st.pop();
    }

    // Reverse the prefix string to get the final prefix expression
    reverse(str.begin(), str.end());
    return str;
}

void delete_middel (Stack <int> &st , int size , int cur = 0)
{
    if (cur == size || st.empty ())
        return;
    
    int temp = st.peek ();
    st.pop ();
    delete_middel (st , size , cur + 1);
    if (cur != size / 2)
        st.push (temp);
}

int main ()
{
    Stack <int> q;
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
    delete_middel (q , n);
    q.display ();
    q.reverse ();
    q.display ();

    // printf ("Enter the formula : ");
    // string s;
    // cin >> s;
    // cout << score (s) << '\n';

    // cout << "Enter the infex expreission (postfix): ";
    // string str;
    // cin >> str;
    // cout << postfix (str) << '\n';

    // cout << "Enter the infex expreission (prefix): ";
    // cin >> str;
    // cout << Prefix (str) << '\n';
}