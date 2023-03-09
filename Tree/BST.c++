#include <iostream>
#include <queue>
#include <cmath>
#include <stack>
#include <cassert>
using namespace std;

struct node
{
    int item;
    // point to the left node 
    node * left;
    // point to the right node
    node * right;
};

class BST
{
private:
    // point the root of the tree
    node * root;
    // add the element on the tree (private)
    node * add (node *r , int element);
    // display root left right 
    void pre (node *r);
    // display left root right 
    void in (node *r);
    // display left right root 
    void post (node *r);
    // search the element in the tree (private)
    node * search_private (node * r , int element);
    node* find_max (node *r);
    node* find_min (node *r);
    node *delete_priv_pred (node * r  , int element);
    node *delete_priv_succ (node * r  , int element);
    int max_higth_priv (node *r);
    int count_leaves_priv (node *r);
    int count_nodes_priv (node *r);
    void clear_priv (node * r);
    void level_order_1Q (node * r);
    void level_ordrer_2Q (node * r);
    void revese_level_order_1Q (node * r);
    bool Full_priv (node * r);
    bool completed_priv (node * r);
    bool isBalanced (node * r);
    bool bst (node *r , int , int);
    int parent (node * r , int element);

public:
    void insert(int element);
    // display root left right 
    void print_preorder ();
    // display left root right 
    void print_inorder ();
    // display left right root 
    void print_postoreder ();
    bool search (int element);
    bool search_iteration (int element);
    int Max ();
    int Min ();
    void Delete_pred (int element);
    void Delete_succ (int element);
    int Tree_hight ();
    int count_leaves ();
    int count_nodes ();
    void clear ();
    bool perfect_tree ();
    void level_order_traversal_1Q ();
    void level_order_traversal_2Q ();
    void reverse_level_order ();
    bool Degenerator ();
    bool full_tree ();
    bool complete_tree ();
    bool balanced ();
    bool Binary_search_tree ();
    int parent_node (int element);
    BST();
    ~BST();
};

// ------------ private functions ----------- //
node * BST::add (node *r , int element)
{
    // creat the node
    node *newnode = new  node;
    // put the element at the node
    newnode->item = element;

    // the tree is empty
    if (r == NULL)
    {
        newnode->left = NULL;
        newnode->right = NULL;
        r = newnode;
    }
    // the element exiset at left
    else if (element < r->item)
        r->left = add(r->left , element);
    // the element exiset at right
    else 
        r->right = add(r->right , element);
    // return the root after finish
    return r;
}

void BST::pre (node *r)
{
    if (r == NULL)
        return;
    cout << r->item << ' ';
    pre(r->left);
    pre(r->right);
}
// the sort of the tree
void BST::in (node *r)
{
    if (r == NULL)
        return;
    in (r->left);
    cout << r->item << ' ';
    in (r->right);
}
void BST::post (node *r)
{
    if (r == NULL)
        return;
    post (r->left);
    post (r->right);
    cout << r->item << ' ';
}

node * BST::search_private (node * r , int element)
{
    // if the element doesn't exist or the tree is empty
    if (r == NULL)
        return NULL;
    // u find the element
    else if (r->item == element)
        return r;
    // the element  exiset at left
    else if (r->item > element)
        return search_private (r->left , element);
    // the element exiset at right
    else
        return search_private (r->right , element);
}

node* BST::find_max (node *r)
{
    if (r == NULL)
        return NULL;
    else if (r->right == NULL)
        return r;
    else 
        return find_max (r->right);
}

node* BST::find_min (node *r)
{
    if (r == NULL)
        return NULL;
    else if (r->left == NULL)
        return r;
    else 
        return find_min (r->left);
}                                                                                                                                   

node *BST::delete_priv_pred (node * r  , int element)
{
    // the tree is empty or the element is not found
    if (r == NULL)
        return NULL;
    // the element at the left sub tree so go left
    else if (element < r->item)
        r->left = delete_priv_pred(r->left , element);
    // the element at the right sub tree so go right 
    else if (element > r->item)
        r->right = delete_priv_pred(r->right , element);
    // if u find the element there are 3 probilities
    else
    {
        // the element is leaf node
        if (r->left == NULL && r->right == NULL)
        {
            // just delete the node
            delete r;
            r = NULL;
        }

        // if the node have one left child
        else if (r->left != NULL && r->right == NULL)
        {
            // get the predessesor (max left)
            node * pred = find_max (r->left);
            // replace the predessesor with deleted node
            r->item = pred->item;
            // and after delete the predessessor (leaf node)
            r->left = delete_priv_pred (r->left , pred->item);
        }

        // if the node have one right child
        else if (r->left == NULL && r->right != NULL)
        {
            // get the succsessor (min right)
            node * succ = find_min (r->right);
            // replace the succsessor with deleted node
            r->item = succ->item;
            // and after delete the succsessor (leaf node)
            r->right = delete_priv_pred (r->right , succ->item);
        }

        // if the node have 2 children
        else
        {
            // get the predessesor
            node *pred = find_max (r->left);
            // replce the pred data at the deleted node
            r->item = pred->item;
            // and delete the pred
            r->left = delete_priv_pred (r->left , pred->item);
        }
    }
    return r;
}

node *BST::delete_priv_succ (node *r , int element)
{
    // if the element doesn't exist
    if (r == NULL)
        return NULL;
    // the element exist at left
    else if (r->item > element)
        r->left = delete_priv_succ (r->left , element);
    // the element exist at right
    else if (r->item < element)
        r->right = delete_priv_succ (r->right , element);
    // if u find the element there are 3 propabilities
    else
    {
        // if it leaf node
        if (r->left == NULL && r->right == NULL)
        {
            delete r;
            r = NULL;
        }

        // if u have one child at the left
        else if (r->left != NULL && r->right == NULL)
        {  
            // we first get the max at the left
            node * pred = find_max (r->left);
            // replace the value of the left max with the father
            r->item = pred->item;
            // delete the child
            r->left = delete_priv_succ(r->left , pred->item);
        }

        // if u have one child at the right
        else if (r->left == NULL && r->right != NULL)
        {
            // find the min at the right
            node * succ = find_min (r->right);
            // replace the value of the left with the father
            r->item = succ->item;
            // delete the child
            r->right = delete_priv_succ (r->right , succ->item);
        }


        // there are 2 children
        else
        {
            // get the min at the right 
            node *succ = find_min (r->right);
            // replace it with the father 
            r->item = succ->item;
            // and delete the pre (it's a leaf node so just delete it)
            r->right = delete_priv_succ(r->right , succ->item);
        }
    }
    return r;
}

int BST::max_higth_priv (node *r)
{
    if (r == NULL)
        return 0;
    else
        return 1 + max (max_higth_priv (r->left) , max_higth_priv (r->right));
}

int BST::count_leaves_priv (node *r)
{
    // if we end the tree
    if (r == NULL)
        return 0;
    // if u find a leaf node
    else if (r->left == NULL && r->right == NULL)
        return 1;
    // after return the sum of the left + right
    else
        return count_leaves_priv (r->left) + count_leaves_priv (r->right);
}

int BST::count_nodes_priv (node *r)
{
    // if it the end of the tree
    if (r == NULL)
        return 0;
    // every time u find a node increase the counter by one
    else
        return 1 + count_nodes_priv (r->left) + count_nodes_priv (r->right);
}

void BST::clear_priv (node * r)
{
    while (r != NULL)
    {
        // first go left sub tree 
        clear_priv (r->left);
        // after go right 
        clear_priv (r->right);
        // after u finish the left and right back and delete
        delete r;
        // at the end make the ptr NULL
        r = NULL;
    }
    
}

void BST::level_order_1Q (node * r)
{
    if (r == NULL)
        return;
    queue <node *> q;
    q.push (root);
    while (!q.empty())
    {
        // put the too of the queeue and print fevery time
        r = q.front ();
        cout << r->item << ' ';
        q.pop();
        // check if the node has any child
        if (r->left != NULL)
            q.push (r->left);
        if (r->right != NULL)
            q.push (r->right);
    }
    cout << '\n';
}

void BST::revese_level_order_1Q (node * r)
{
    // we need a queue to put the element on it and a stack print it reverse
    if (r == NULL)
        return;
    // use to put the nodes on it
    queue <node*> q;
    // use to put the nodes of the queue on it to print it revese
    stack <int> st;
    // push the root of the tree on the queue 
    q.push (root);
    while (!q.empty ())
    {
        // the root use to tack the top of the queue every time
        r = q.front ();
        // delete the front to take the next child
        q.pop ();
        // add the element to the stake
        st.push (r->item);
        // check if there are left and right child
        if (r->left != NULL)    
            q.push (r->left);
        if (r->right != NULL)
            q.push (r->right);
    }
    // print the reverse of the tree
    while (!st.empty())
    {
        printf ("%i " , st.top ());
        st.pop ();
    }
    printf ("\n");
}

void BST::level_ordrer_2Q (node * r)
{
    // we will use 2 queues
    // if the tree is empty
    if (r == NULL)
        return;
    queue <node *> Q1 , Q2;
    // first push the root to one of queues to start
    Q1.push (r);
    // if there is atleat one element on the tree
    while (!Q1.empty() || !Q2.empty())
    {
        bool ch = 0;
        // first print all the nodes on the first queue 
        while (!Q1.empty())
        {
            // take the front of the queue 
            r = Q1.front();
            cout << r->item << ' ';
            // delete the elemet u visited at the q1
            Q1.pop();
            // and put the children of the queue one on Q2
            if (r->left != NULL)
                Q2.push (r->left);
            if (r->right != NULL)
                Q2.push (r->right);
            ch = 1;
        }
        // if the loop is finished 
        if (ch == 1)
            cout << endl;
        ch = 0;

        // first print all the nodes on the second queue 
        while (!Q2.empty())
        {
            // take the front of the queue 
            r = Q2.front();
            cout << r->item << ' ';
            // delete the elemet u visited at the q2
            Q2.pop();
            // and put the children of the queue two on Q1
            if (r->left != NULL)
                Q1.push (r->left);
            if (r->right != NULL)
                Q1.push (r->right);
            ch = 1;
        }
        // if the loop is finished 
        if (ch == 1)
            cout << endl;
    }
}

bool BST::Full_priv (node * r)
{
    if (r == NULL)
        return true ;
    else if ((r->left == NULL && r->right != NULL) || (r->left != NULL && r->right == NULL))
        return false;
    else
        return Full_priv (r->left) && Full_priv (r->right);
    return true;
}

bool BST::completed_priv (node * r)
{
    // we will use level order
    if (r == NULL)
        return false;
    queue <node *> q;
    // push the root to the queue
    q.push (root);
    
    // use to check the tree every time when you see null at left and the right has child 
    bool check = false;
    while (!q.empty())
    {
        r = q.front ();
        q.pop ();

        // if there is left child
        if (r->left)
        {
            if (check)
                return false;
            q.push (r->left);
        }

        else 
            check = true;
        // if there if right child after the left one  يعني في نفس المستوي في طفل يمين ومفيش واحد في الشمال
        if (r->right)
        {
            if (check)
                return false;
            q.push (r->right);
        }
        else 
            check = true;
    }
    return true;
}

bool BST::isBalanced (node * r)
{
    // that is mean he reach to the end of the tree and find the hight of the sub trees is <= 1
    if (r == NULL)
        return true;
    // first get the hight for every sub trees
    int left_h = max_higth_priv (r->left);
    // get the hight of the right also
    int right_h = max_higth_priv (r->right);
    // if the differance betwen them is greater than 1 so it's not banlanced
    if (abs (right_h - left_h) > 1)
        return false;
    // check in the left then the right
    return isBalanced (r->left) && isBalanced (r->right);
}

bool BST::bst (node *r , int minn , int maxx)
{
    if (r == NULL)
        return true;
    else if ((r->item <= minn) || (r->item > maxx))
        return false;
    return bst (r->left , minn , r->item) && bst (r->right , r->item , maxx);
}

int BST::parent (node * r , int element)
{
    if (element == r->item)
        return -1;
    node * prev = NULL;
    while (r != NULL)
    {
        if (r->item == element)
            return prev->item;
        prev = r;
        if (element < r->item)
            r = r->left;
        else
            r = r->right;
    }
    return -1;
}
// ----------------------------------------- //

// ---------- the user functions ----------- //
void BST::insert(int element)
{
    root = add (root, element);
}

void BST::print_preorder ()
{
    // send the  root to the pre
    pre (root);
}

void BST::print_inorder ()
{
    // send the  root to the in
    in (root);
}

void BST::print_postoreder ()
{
    // send the  root to the post
    post (root);
}

bool BST::search (int elemnt)
{
    node * ans = search_private (root , elemnt);
    return (ans == NULL) ? false : true;
}

int BST::Max ()
{
    node * ans = find_max (root);
    return(ans == NULL) ? -1 : ans->item;
}

int BST::Min ()
{   
    node * ans = find_min (root);
    return(ans == NULL) ? -1 : ans->item;
}

bool BST::search_iteration (int element)
{
    node * r = root;
    while (r != NULL)
    {
        if (r->item == element)
            return true;
        // go left
        else if (r->item > element)
            r = r->left;
        // go right
        else
            r = r->right;
    }
    return false;
}

void BST::Delete_pred (int element)
{
    node * ans = delete_priv_pred (root , element);
    if (ans == NULL)
        return;
}

void BST::Delete_succ (int element)
{
    node * ans = delete_priv_succ (root , element);
    if (ans == NULL)
        return;
}

int BST::Tree_hight ()
{
    return max_higth_priv (root); 
}

int BST::count_leaves ()
{
    return count_leaves_priv (root);
}

int BST::count_nodes ()
{
    return count_nodes_priv (root);
}

bool BST::perfect_tree ()
{
    // use the formula n = (2 ^ (h + 1)) - 1
    int n = count_nodes ();
    int h = Tree_hight ();
    // because the hight in this case bigger by one
    h--;
    return (n == pow (2 , h + 1) - 1) ? true : false;
}

bool BST:: Degenerator ()
{
    int n = count_nodes ();
    int h = Tree_hight ();
    return (n == h) ? true : false;
}

// use to delete all the tree
void BST::clear ()
{
    clear_priv (root);
}

void BST::level_order_traversal_1Q ()
{
    level_order_1Q (root);
}

void BST::level_order_traversal_2Q ()
{
    level_ordrer_2Q (root);
}

void BST::reverse_level_order ()
{
    revese_level_order_1Q (root);
}

bool BST::full_tree ()
{
    return Full_priv (root);
}

BST::BST()
{
    root = NULL;
}

BST::~BST()
{
    clear_priv (root);
}

bool BST::complete_tree ()
{
    return completed_priv (root);
}

bool BST::balanced ()
{
    return isBalanced (root);
}

bool BST::Binary_search_tree ()
{
    // we pass it a very small num (-inf) and +inf
    return bst (root , -100000 , 100000);
}

int BST::parent_node (int element)
{
    return parent (root , element);
}
// ----------------------------------------- //

int main (void)
{
    BST b;
    int n;
    cout << "Enter  the size : ";
    cin >> n;
    while (n--)
    {
        int x;
        cin >> x;
        b.insert (x);
    }

    cout << "\nprinting in preorder : ";
    b.print_preorder();
    cout << '\n';
    cout << "printing in inoreder : ";
    b.print_inorder();
    cout << '\n';
    cout << "printing in postorder : ";
    b.print_postoreder();
    cout << '\n';

    cout << "\nEnter the element u search for : ";
    int x;
    cin >> x;
    (b.search_iteration(x)) ? cout << "Found\n" : cout << "Not Found\n";

    cout << "\nMin : ";
    cout << b.Min() << '\n';
    cout << "Max : ";
    cout << b.Max() << '\n';

    cout << "\nTree Higth : " << b.Tree_hight() << '\n';
    cout << "Leaves Number : " << b.count_leaves () << '\n';
    cout << "Node Number : " << b.count_nodes () << '\n';

    cout << "\nType : ";
    (b.balanced ()) ? cout << "Balanced - " : cout << "Not_Balanced-";
    if (b.Degenerator ())
        cout << "Degenerator - ";
    else if (b.perfect_tree ())
        cout << "Perfect - ";
    else if (b.full_tree ())
        cout << "Full - ";
    else if (b.complete_tree ())
        cout << "Complete - ";
    else
        cout << "Normal - ";
    (b.Binary_search_tree ()) ? cout << "Binary_Search_Tree !\n" : cout << "Non_Binary_Search_Tree !";

    cout << "\nLevel order traversal by 1 queues ?! \n";
    b.level_order_traversal_1Q();
    cout << "Level order traversal by 2 queues ?! \n";
    b.level_order_traversal_2Q();
    cout << "Reverse level order traversal ?!\n";
    b.reverse_level_order ();
    
    cout << "\nEnter the node u want her parent : ";
    int parent;
    cin >> parent;
    cout << "The Parent of node {" << parent << "} : " << b.parent_node (parent) << '\n';

    cout << "\nEnter the element u want to delete (predesessor) : ";
    int l;
    scanf ("%i" , &l);
    b.Delete_pred(l);
    cout << "printing in preorder : ";
    b.print_preorder();
    cout << '\n';
    cout << "printing in inoreder : ";
    b.print_inorder();
    cout << '\n';
    cout << "printing in postorder : ";
    b.print_postoreder();
    cout << '\n';

    cout << "\nEnter the element u want to delete (succsessor) : ";
    int o;
    scanf ("%i" , &o);
    b.Delete_succ(o);
    cout << "printing in preorder : ";
    b.print_preorder();
    cout << '\n';
    cout << "printing in inoreder : ";
    b.print_inorder();
    cout << '\n';
    cout << "printing in postorder : ";
    b.print_postoreder();
    cout << '\n';
}