#include <iostream>
using namespace std;
template <class T>

class double_list
{
private:
    struct node
    {
        T item;
        // ptr node refer to the next node
        node * next;
        // ptr node refer to the previous node
        node * prev;
    };
    
    node *first;
    node *last;
    int length;
    
public:
    double_list()
    {
        first = last = NULL;
        length = 0;
    }

//-------------function to check if the node is empty--------------//
    bool IsEmpty()
    {
        return length == 0;
    }

//---------function use to add from the front------------//
    void push_front(T element)
    {   
        // build the node
        node *newnode = new node;
        // put the item in the node
        newnode->item = element;

        if (IsEmpty())
        {
            // move the first and last refer to the first node
            first = last = newnode;
            // make the two ptrs refer to the NULL
            newnode->next = newnode->prev = NULL;
        }

        else
        {
            // conect the next of the new node with the first node
            newnode->next = first;
            // the prev of the new node refer to null
            newnode->prev = NULL;
            // prev of the first node refer to the newnode
            first->prev = newnode;
            // move the first to the newnode
            first = newnode;
        }
        length++;
    }

//---------function use to add from the back------------//
    void push_back(T element)
    {   
        // build the node
        node *newnode = new node;
        // put the item in the node
        newnode->item = element;

        if (IsEmpty())
        {
            // move the first and last refer to the first node
            first = last = newnode;
            // make the two ptrs refer to the NULL
            newnode->next = newnode->prev = NULL;
        }

        else
        {
            // conect the node with the last node
            newnode->prev = last;
            // make the next of the newnode refer to NULL
            newnode->next = NULL;
            // conect the next ptr of the last with the newnode
            last->next = newnode;
            // move the last to the next node
            last = newnode;
        }
        length++;        
    }

//---------function use to add from the front------------//
    void add_index(int index , T element)
    {   
        if (index < 0 || index > length)
            cout << "Out of Range !!\n";

        else
        {
            node *newnode = new node;
            newnode->item = element;

            if (index == 0)
                push_front(element);
            
            else if (index == length)
                push_back(element);
            
            else
            {
                node *cur = first;
                for (int i = 1; i < index; i++)
                {
                    cur = cur->next;
                }
                
                // make the next of the newnode refer to the next node of the cur
                newnode->next = cur->next;
                // make the prev of the newnode refer to the cur node
                newnode->prev = cur;
                // conect the next node with the newnode
                cur->next->prev = newnode;
                // conect the cur node with the newnode
                cur->next = newnode;
                length++;
            }
        }
    }

//--------function to delete from the first-----------//
    void pop_front()
    {
        if (IsEmpty())
            cout << "Empty list ...!\n";
        
        else if(length == 1)
        {
            delete first;
            first = last = NULL;
            length = 0;
        }

        else
        {
            // build a ptr to delete by it
            node *cur = first;
            // move the first ptr to the next node
            first = first->next;
            // delete the node
            delete cur;
            // make the prev of the next node refer to null
            first->prev = NULL;
            length--;
        }
    }

//--------function to delete from the last-----------//
    void pop_back()
    {
        if (IsEmpty())
            cout << "Empty list ...!\n";
        
        else if(length == 1)
        {
            delete first;
            first = last = NULL;
            length = 0;
        }

        else
        {
            // build a ptr to delete by it
            node *cur = last;
            // move the last ptr to the prev node
            last = last->prev;
            // delete the node
            delete cur;
            // make the prev of the next node refer to null
            last->next = NULL;
            length--;
        } 
    }

//--------function to delete a spasific element-----------//
    void pop_element(T element)
    {
        if (IsEmpty())
            cout << "Empty list ...!\n";

        // if the elemet is the first node
        else if (first->item == element)
            pop_front();

        else
        {
            node *cur = first->next;
            while (cur != NULL)
            {
                if (cur->item == element)
                    break;
                
                cur = cur->next;
            }
            
            // if the element doesn't exist
            if (cur == NULL)
                cout << "Not found ...!\n";
            
            else if(cur->next == NULL)
                pop_back();
            
            else
            {
                // make the prev node of the element conect with the next node
                cur->prev->next = cur->next;
                // make the next node of the element conect with the prev node
                cur->next->prev = cur->prev;
                // delete cur (element)
                delete cur;
                length--;
            } 
        }
    }

//--------function to delete from any position-----------//
    void pop_index(int index)
    {
        if (index < 0 || index >= length)
            cout << "Out of Range ...!\n";

        else if (index == 0)
            pop_front();

        else if (index == length)
            pop_back();

        else
        {
            node *cur = first;
            for (size_t i = 1; i < index; i++)
            {
                cur = cur->next;
            }
            cur = cur->next;
            // make the prev node of the element conect with the next node
            cur->prev->next = cur->next;
            // make the next node of the element conect with the prev node
            cur->next->prev = cur->prev;
            // delete cur (element)
            delete cur;
            length--;
        }
        
    }

//--------function to print from the front--------------//
    void print()
    {
        node *cur = first;
        while (cur != NULL)
        {
            cout << cur->item << ' ';
            cur = cur->next;
        }
        cout << '\n';
    }

//-------palindrom-----------//
    bool pal()
    {
        node *f = first;
        node *l = last;
        for (int i = 0; i <= length / 2; i++)
        {
            if (l->item != f->item)
                return false;
            l = l->prev;
            f = f->next;
        }
        return true;
    }

//--------function to print from the back--------------//
    void print_reverse()
    {
        node *temp = last;
        while (temp != NULL)
        {
            cout << temp->item << ' ';
            temp = temp->prev;
        }
        cout << '\n';
    }

//--------delete the element after finish--------//
    ~double_list()
    {
		node *temp;
		while (first != NULL)
		{
			temp = first;
			first = first->next;
			delete temp;
		}
		last = NULL;
		length = 0;
    }
};



int main()
{
    double_list<int>l;
    int n;
    cout << "Enter the size : ";
    cin >> n;
    int num;
    while (n--)
    {
        cin >> num;
        l.push_back(num);
    }
    l.print();
    l.print_reverse();
    (l.pal()) ? cout << "Yes\n" : cout << "No\n";
}