#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <assert.h>
using namespace std;
template <class T>

class linked_list
{
private:
    struct node
    {
        T item;
        node *next;
    };
    // ptr refer to the first element
    node * first;
    // ptr refer to the last element
    node * last;
    int length;

public:
    linked_list()
    {
        first = NULL;
        last = NULL;
        length = 0;
    }

//--------function check if the list is empty---------//
    bool IsEmpty()
    {
        return length == 0;
    }
//---------------------------------------------------//

//--------function add from the begin of the list--------//
    void push_front(T element)
    {
        // build the node 
        node *newnode = new node;
        // put the element in the struct of the element
        newnode->item = element;

        // if it the first element in the list
        if (IsEmpty())
        {
            // move the first and the last to the same position on the node
            first = last = newnode;
            newnode->next = NULL;
        }

        // if ther are elements in the list
        else
        {
            // conect the newnode with the previeous node
            newnode->next = first;
            // move the first to the new node
            first = newnode;
        }
        
        length++;
    }
//------------------------------------------------------//

//--------function add from the end of the list--------//
    void push_back(T element)
    {
        // build the node 
        node *newnode = new node;
        // put the element in the struct of the element
        newnode->item = element;

        // if it the first element in the list
        if (IsEmpty())
        {
            // move the first and the last to the same position on the node
            first = last = newnode;
            newnode->next = NULL;
        }

        // if ther are other elements 
        else
        {
            // conect the newnode with the last node
            last->next = newnode;
            // newnode refer to null becuse it is the last one 
            newnode->next = NULL;
            // move the last to the newnode
            last = newnode;
        }
        length++;
    }
//----------------------------------------------------//

//--------function add from any position in the list--------//
    void add(int pos , T element)
    {
        if (pos < 0 || pos > length)
            cout << "Out of Range !\n";

        else
        {
            // build the node 
            node *newnode = new node;
            // put the element in the struct of the element
            newnode->item = element;

            if (pos == 0)
                push_front(element);
            
            else if (pos == length)
                push_back(element);

            else
            {
                // use a ptr to refer to the pos - 1
                node *cur = first;

                for (size_t i = 1; i < pos; i++)
                {
                    cur = cur->next;
                }
                
                // conect the newnode with next node
                newnode->next = cur->next;
                
                //conect the cur node with the newnode
                cur->next = newnode;
            }
            length++;
        }
        
    }
//---------------------------------------------------------//

    int size()
    {
        return length;
    }

//--------print function-------//   
    void print ()
    {
        assert (!IsEmpty ());
        node *temp = first;
        while (temp != NULL)
        {
            cout << temp->item << ' ';
            temp = temp->next;
        }
        cout << endl;
    }
//----------------------------//

//---------exercices--------//
    T middle_element()
    {
        int cntr = 0;
        node *cur = first;
        while (cntr != length / 2)
        {
            cntr++;
            cur = cur->next;
        }
        return cur->item;
    }

    T middle()
    {
        node *cur = first;
        node *prev = first;
        while (cur != NULL && cur->next != NULL)
        {
            prev = prev->next;
            cur = cur->next->next;
        }
        return prev->item;
    }

    void rotate_cw(int k)
    {
        assert(!length == 0);
        k = k % length;
        while (k--)
        {
            node *cur = first->next;
            node *prev = first;
            while (cur != last)
            {
                prev = cur;
                cur = cur->next;
            }
            cur->next = first;
            first = cur;
            prev->next = NULL;
            last = prev;
        }
        
    }

    void rotate_ccw(int k)
    {
        node *cur =  first;
        for (int i = 1; i < k; i++)
            cur = cur->next;
        if (cur == NULL)    
            return;
        last->next = first; 
        first = cur->next;
        last = cur;
        cur->next = NULL;
    }


//----------------------------------//
//-------function delete from begin------//
    void pop_front()
    {
        if (IsEmpty())
            cout << "Empty !\n";

        else if (length == 1)
        {
            delete first;
            first = last = NULL;
            length = 0;
        }
        
        else
        {
            // ptr to delete the element by it 
            node *cur = first;
            // move the first to the next element 
            first = first->next;
            delete cur;
            length--;
        }
    }
//--------------------------------------//

//-------function delete from end------//
    void pop_back()
    {
        if (IsEmpty())
            cout << "Empty !\n";

        else if (length == 1)
        {
            delete first;
            first = last = NULL;
            length = 0;
        }
        
        else
        {
            // use two ptr to delete
            node *cur = first->next;
            node *prev = first;

            while (cur != last)
            {
                prev = cur;
                cur = cur->next;
            }
            delete cur;
            // make the element befor the refer to null becase it is become the last
            prev->next = NULL;
            // move the last to the previous element
            last = prev;
            length--;
        }
        
    }
//------------------------------------//

//-------function delete spasific element------//
    void delete_element(T element)
    {
        if (IsEmpty())
            cout << "Empty !\n";

        else
        {
            node *prev , *cur;
            // if the element is the first one
            if (element == first->item)
            {
                cur = first;
                first = first->next;
                delete cur;
                length--;
                if (length == 0)
                    last = NULL;
            }

            else
            {
                cur = first->next;
                prev = first;

                while (cur != NULL)
                {
                    // if u find the element end the loop
                    if (cur->item == element)
                        break;

                    prev = cur;
                    cur = cur->next;
                }
                // if the element not found
                if(cur == NULL)
                    cout << "Not found\n";

                else 
                {
                    prev->next = cur->next;
                    if (cur == last)
                        last = prev;

                    delete cur;
                    length--;
                }
            }
        }
    }
//--------------------------------------------//

// --------- delete a key ----------- //
    void delete_key (T element)
    {
        assert (!IsEmpty ());
        node *cur = first;
        node *prev = NULL;
        while (cur != NULL)
        {
            bool ch = 0;
            if (first->item == element)
            {
                pop_front ();
                cur = first;
                ch = 1;
            }
            else if (cur == last && last->item == element)
            {
                pop_back ();
                break;
            }
            
            else if (cur->item == element)
            {
                prev->next = cur->next;
                cur->next = NULL;
                delete cur;
                cur = prev->next;
                ch = 1;
                length--;
            }

            if (ch == 0)
            {
                prev = cur;
                cur = cur->next;
            }
        }
    }
// --------------------------------- // 

// ----------delete even position ---------- //
    void delete_even_pos ()
    {
        assert (!IsEmpty ());
        node * cur = first->next;
        node * even = first;
        while (cur != NULL)
        {
            if (cur == last)
            {
                last = even;
                last->next = NULL;
                delete cur;
                length--;
                break;
            }

            even->next = cur->next;
            even = cur->next;
            cur->next = NULL;
            delete cur;
            cur = even->next;
            length--;
        }
    }
// ---------------------------------------- //

// ----------delete odd position ---------- //
    void delete_odd_pos ()
    {
        assert (!IsEmpty ());
        node * cur = first;
        first = first->next;
        node * odd = NULL;
        while (cur != NULL)
        {
            if (cur == last)
            {
                last = odd;
                last->next = NULL;
                delete cur;
                length--;
                break;
            }

            else if (odd == NULL)
            {
                odd = cur->next;
                cur->next = NULL;
                delete cur;
                cur = odd->next;
                length--;
            }

            else
            {
                odd->next = cur->next;
                odd = cur->next;
                cur->next = NULL;
                delete cur;
                cur = odd->next;
                length--;
            }
            
        }
        
    }
// ---------------------------------------- //

// ---------------- palindrom -------------- //
    bool palindrome  ()
    {
        vector <T> v;
        for (node * cur = first; cur != NULL; cur = cur->next)
            v.push_back (cur->item); 
        for (int i = 0 , j = v.size () - 1; i < v.size (); i++ , j--)
        {
            if (v[i] != v[j])
                return false;
        }
        return true;
    }
// ------------------------------------------- //

//---------fuction reverse the list-----------//
    void reverse()
    {
        assert (!IsEmpty ());
        if (size () == 1)
            return;
        // del 3 ptr
        node *prev = NULL;
        node *cur  = first;
        node *next = cur->next;

        while (next != NULL)
        {
            // link the next with the next node of cur
            next = cur->next;
            // link the node with the prev node
            cur->next = prev;
            // move the prev to the next node
            prev = cur;
            // move the cur
            cur = next;
        }
        // make the last refer to the first node because of contact
        last = first;
        // make the first refer to the last node
        first = prev;
    }
//-------------------------------------------//

//---------function to search for an element----------//
    bool search(T element)
    {
        node *cur = first;
        while (cur != NULL)
        {
            if (cur->item == element)
                return true;
            
            cur = cur->next;
        }
        return false;
    }
//----------------------------------------------------//

// -------------- arrange odd & even ------------ //
    void odd_even ()
    {
        node * even = first;
        node * odd = first->next;
        node * conect = first->next;
        node * cur = odd->next;
        while (cur != NULL)
        {
            even->next = cur;
            even = cur;
            cur = cur->next;
            if (cur != NULL)
            {
                odd->next = cur;
                odd = cur;
                cur = cur->next;
            }
        }
        last = odd;
        odd->next = NULL;
        even->next = conect;
        odd = conect = even = NULL;
    }
// --------------------------------------------- //

// --------------- Insert alternating --------------- //
    void Insert_alternating (vector <int> & v)
    {
        if (IsEmpty ())
        {
            for (auto i : v)
                push_back (i);
        }

        else
        {
            node * cur = first->next;
            node * prev = first;
            for (auto i : v)
            {
                if (cur == NULL)
                    push_back (i);
                else
                {
                    node * newnode = new node;
                    newnode->item = i;
                    newnode->next = cur;
                    prev->next = newnode;
                    prev = cur;
                    cur = cur->next;
                    length++;
                }
            }
        }
    }
// -------------------------------------------------- //
    T front ()
    {
        assert (!IsEmpty ());
        return first->item;
    }

    T back ()
    {
        assert (!IsEmpty ());
        return last->item;
    } 

// ----------- delete repeated -------- //
    void delete_repeated ()
    {
        map <int , int> mp;
        for (node * cur = first; cur != NULL; cur = cur->next)
            mp[cur->item]++;
        for (auto i : mp)
        {
            if (i.second > 1)
            {
                delete_key (i.first);
            }
        }
    }
// ----------------------------------- //

// -------------- sort --------------- //
    void Bubble_sort()
    {
        node * i , *j;
        // use to the swap
        int tmp;
        for (i = first; i != NULL; i = i->next)
        {
            for (j = i->next; j != NULL; j = j->next)
            {   
                if (i->item > j->item)
                {
                    tmp = i->item;
                    i->item = j->item;
                    j->item = tmp;
                }
            }
        }
    }

};


int main (void)
{
    linked_list<int> l;
    cout << "Enter the size : ";
    int size;
    cin >> size;

    while (size--)
    {
        int n;
        cin >> n;
        l.push_back(n);
    }

    l.print ();
    l.delete_repeated ();
    l.print ();
    vector <int> v;
    int x;
    cout << "Enter the size of the additional elements : ";
    cin >> x;
    while (x--)
    {
        int s;
        cin >> s;
        v.push_back (s);
    }
    l.Insert_alternating (v);
    l.print ();
    cout << "Front = " << l.front () << " - " << "Back = " <<  l.back () << '\n';
    l.odd_even ();
    l.print ();
    cout << "Front = " << l.front () << " - " << "Back = " <<  l.back () << '\n';
    (l.palindrome ()) ? cout << "Palindrome !\n" : cout << "Not Palindrome !\n"; 
    l.delete_odd_pos ();
    l.print();
    l.delete_key (5);
    l.print ();
    (l.search(4)) ? cout << "Found !\n" : cout << "Not found\n";
    l.Bubble_sort();
    l.print();
    cout << "Front = " << l.front () << " - " << "Back = " <<  l.back () << '\n';
    l.rotate_ccw(1);
    l.print();
    cout << "Front = " << l.front () << " - " << "Back = " <<  l.back () << '\n';
    l.rotate_cw(2);
    l.print();
    cout << "Front = " << l.front () << " - " << "Back = " <<  l.back () << '\n';
    cout << l.middle_element() << '\n';
    l.add(3 , 4);
    l.print ();
    cout << "Front = " << l.front () << " - " << "Back = " <<  l.back () << '\n';
    l.pop_front();
    l.print ();
    cout << "Front = " << l.front () << " - " << "Back = " <<  l.back () << '\n';
    l.pop_back();
    l.print ();
    cout << "Front = " << l.front () << " - " << "Back = " <<  l.back () << '\n';
    l.delete_element(2);
    l.print ();
    cout << "Front = " << l.front () << " - " << "Back = " <<  l.back () << '\n';
    l.reverse();
    l.print();
}