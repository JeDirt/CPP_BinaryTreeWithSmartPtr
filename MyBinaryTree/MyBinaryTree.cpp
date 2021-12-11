#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <stack>


using namespace std;


template <class T>
class BinaryTree
{


private:

  
    struct Node
    {

        T Data;

        shared_ptr<Node> Left;
        shared_ptr<Node> Right;

    };


public:


    BinaryTree() : tree_size(0), Root(nullptr) { }
    virtual ~BinaryTree() {}
   

public:


    void push(const T data)
    {

        // If there is no Root, we create it
        if (!Root) { Root = createNode(data); }

        // If we have Root, then we go to find place for inserting new node
        else { push_helper(Root, data); }

        tree_size++;

    }
    T find(const T to_find)const
    {

        // We haven't pushed any element yet
        if (!Root) { throw exception("Tree is empty!"); }

        // Coming to find
        else { find_helper(Root, to_find); }

    }  
    void delete_element(const T to_delete)
    {

        // Handle new pointer(the case if we deleted Root, tree can be rebuild)
        Root = delete_helper(Root, to_delete);
        tree_size--;

    }


    // min/max helpers return pointer to node with least data
    T min()const { return  min_helper(Root)->Data; }
    T max()const { return max_helper(Root)->Data; }
    
   
    void inorderTraversal() { inorderTraversal_helper(Root); }
    void preorderTraversal() { preorderTraversal_helper(Root); }
    void postorderTraversal() { postorderTraversal_helper(Root); }


    void inorderTraversalByStack() { inorderTraversalByStack_helper(Root); }
    void preorderTraversalByStack() { preorderTraversalByStack_helper(Root); }
    void postorderTraversalByStack() { postorderTraversalByStack_helper(Root); }


    int size()const { return this->tree_size; }
    void clear() { clear_helper(Root); }
    void print_tree() { print_tree_helper(Root); }


private:


    shared_ptr<Node> createNode(const T data)
    {

        shared_ptr<Node> temp = make_shared<Node>(Node());
        temp->Data = data;

        temp->Left = nullptr;
        temp->Right = nullptr;

        return temp;

    }


    void push_helper(const shared_ptr<Node> &element, const T data)
    {

        if (!element) { return; }

        if (element->Data > data)
        {
            // Coming left subtree and look for the place to insert
            if (!element->Left) { element->Left = createNode(data); }
            else { push_helper(element->Left, data); }
        }
        else 
        {
            // Coming right subtree and look for the place to insert
            if (!element->Right) { element->Right = createNode(data); }
            else { push_helper(element->Right, data); }
        }

    }
    T find_helper(const shared_ptr<Node>& element, const T to_find)const
    {

        // No such element
        if (!element) { throw exception("No such element!"); }

        // Check the case that searched element is Root
        if (element->Data == to_find) { return element->Data; }

        // Choose the subtree to continue looking for
        if (to_find < element->Data) { return find_helper(element->Left, to_find); }
        else { return find_helper(element->Right, to_find); }

    }
    shared_ptr<Node> delete_helper(shared_ptr<Node> &element,T to_delete)
    {

        if (!element) { return element; }

        // Looking for our element to delete
        if (to_delete < element->Data)
        {
            element->Left = delete_helper(element->Left, to_delete);
        }

        else if (to_delete > element->Data)
        {
            element->Right = delete_helper(element->Right, to_delete);
        }
           
        // We found element
        else 
        {

            // If we have no left child
            if (!element->Left)
            {

                shared_ptr<Node> temp = element->Right;
                element.reset();

                return temp;

            }

            // If we have no right child
            else if (!element->Right)
            {

                shared_ptr<Node> temp = element->Left;
                element.reset();

                return temp;

            }


            shared_ptr<Node> temp = min_helper(element->Right);

            element->Data = temp->Data;
            element->Right = delete_helper(element->Right, temp->Data);

        }

        return element;

    }


    shared_ptr<Node> min_helper(const shared_ptr<Node>& element)const
    {

        // Dig left subtree until its done
        if (element->Left) { return min_helper(element->Left); }
        else { return element; }

    }
    shared_ptr<Node> max_helper(const shared_ptr<Node>& element)const
    {

        // Dig right subtree until its done
        if (element->Right) { return  max_helper(element->Right); }
        else { return element; }

    }


    void inorderTraversal_helper(const shared_ptr<Node>& element)
    {

        if (!element) { return; }

        inorderTraversal_helper(element->Left);
        cout << element->Data << " ";
        inorderTraversal_helper(element->Right);

    }
    void preorderTraversal_helper(const shared_ptr<Node> &element)
    {

        if (!element) { return; }

        cout << element->Data << " ";

        preorderTraversal_helper(element->Left);
        preorderTraversal_helper(element->Right);

    }
    void postorderTraversal_helper(const shared_ptr<Node> & element)
    {

        if (!element) { return; }


        postorderTraversal_helper(element->Left);
        postorderTraversal_helper(element->Right);

        cout << element->Data << " ";

    }


    void inorderTraversalByStack_helper(shared_ptr<Node> &element)
    {

        stack<shared_ptr<Node>> _stack;
        shared_ptr<Node> temp = element;

        while (temp || !_stack.empty())
        {

            while (temp)
            {
                _stack.push(temp);
                temp = temp->Left;
            }

            temp = _stack.top();
            _stack.pop();

            cout << temp->Data << " ";
            temp = temp->Right;

        }

    }
    void preorderTraversalByStack_helper(shared_ptr<Node>& element)
    {

        if (!element) { return; }


        stack<shared_ptr<Node>> _stack;
        _stack.push(element);


        while (!_stack.empty())
        {


            shared_ptr<Node> temp = _stack.top();

            cout << temp->Data << " ";
            _stack.pop();


            if (temp->Right) { _stack.push(temp->Right); }
            if (temp->Left) { _stack.push(temp->Left); }


        }
    }
    void postorderTraversalByStack_helper(shared_ptr<Node>& element)
    {

        if (!element) { return; }

        stack <shared_ptr<Node>> _stack1, _stack2;
        _stack1.push(element);


        while (!_stack1.empty())
        {

            shared_ptr<Node> temp = _stack1.top();

            _stack1.pop();
            _stack2.push(temp);

            if (temp->Left) { _stack1.push(temp->Left); }
            if (temp->Right) { _stack1.push(temp->Right); }
                
        }


        while (!_stack2.empty())
        {

            shared_ptr<Node> temp = _stack2.top();

            cout << temp->Data << " ";
            _stack2.pop();

        }

    }


    void clear_helper(shared_ptr<Node> & element)
    {

        if (element->Left) { clear_helper(element->Left); }
        if (element->Right) { clear_helper(element->Right); }
     
        element.reset();
        tree_size--;
      
    }


    /*  Thanks to https ://github.com/RonGreenberg/print-binary-tree-to-console  */
    void print_nodes_helper(const string& padding, const string& edge, shared_ptr<Node>element, bool has_left_sibling)
    {

        if (element)
        { 

            cout << endl << padding << edge << element->Data;

          
            if ((!element->Left) && (!element->Right))
            {

                cout << endl << padding; 
                if (has_left_sibling) { cout << "|"; }  
           
            }

            else
            {
              
                string new_padding = padding + (has_left_sibling ? "|    " : "     ");

                print_nodes_helper(new_padding, "|----", element->Right, element->Left != nullptr);
                print_nodes_helper(new_padding, "|____", element->Left, false);

            }

        }

    } 
    void print_tree_helper(shared_ptr<Node> & element)
    {
        
        if (!element) { return; }
         
        cout << element->Data;

        print_nodes_helper("", "|----", element->Right, element->Left != nullptr);
        print_nodes_helper("", "|____", element->Left, false);

    } 


private:


    shared_ptr<Node> Root;
    int tree_size;


};


int main() { return 0; }
