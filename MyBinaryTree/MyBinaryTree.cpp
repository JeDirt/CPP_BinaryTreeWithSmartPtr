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


    BinaryTree( const T DataToPaste = T() ) : tree_size(0) { this->Root = nullptr; }
    virtual ~BinaryTree() {}
   

public:


    void push(const T DataToPaste)
    {

        if (!Root) { Root = createNode(DataToPaste); }
        else { push_helper(Root, DataToPaste); }

        tree_size++;

    }
    const T find(const T DataToFind)const
    {

        if (Root == nullptr) { return T(); }

        if (Root.get()->Data == DataToFind) { return Root.get()->Data; }
        else { find_helper(Root, DataToFind); }

    }  
    void delete_element(const T DataToDelete)
    {

        Root = delete_helper(Root, DataToDelete);
        tree_size--;

    }


    const T min()const
    { 
        auto min_value = min_helper(Root); 
        return min_value.get()->Data; 
    }
    const T max()const
    {
        auto max_value = max_helper(Root);
        return max_value.get()->Data;
    }
  
   
    void inorderTraversal() { inorderTraversal_helper(Root); }
    void preorderTraversal() { preorderTraversal_helper(Root); }
    void postorderTraversal() { postorderTraversal_helper(Root); }


    void inorderTraversalByStack() { inorderTraversalByStack_helper(Root); }
    void preorderTraversalByStack() { preorderTraversalByStack_helper(Root); }
    void postorderTraversalByStack() { postorderTraversalByStack_helper(Root); }


    const int size()const { return this->tree_size; }
    void clear() { clear_helper(Root); }
    void print_tree() { print_tree_helper(Root); }


private:


    const shared_ptr<Node> createNode(const T DataToPaste)
    {

        shared_ptr<Node> temp = make_shared<Node>(Node());
        temp.get()->Data = DataToPaste;

        temp.get()->Left = nullptr;
        temp.get()->Right = nullptr;

        return temp;

    }


    void push_helper(const shared_ptr<Node> &Node, const T DataToPaste)
    {

        if (!Node) { return; }

        if (Node.get()->Data > DataToPaste)
        {

            if (!Node.get()->Left) { Node.get()->Left = createNode(DataToPaste); }
            else { push_helper(Node.get()->Left, DataToPaste); }

        }
        else 
        {
            if (!Node.get()->Right) { Node.get()->Right = createNode(DataToPaste); }
            else { push_helper(Node.get()->Right, DataToPaste); }
        }

    }
    const T find_helper(const shared_ptr<Node>& Node, const T DataToFind)const
    {

        if (!Node.get()) { return T(); }
        if (Node.get()->Data == DataToFind) { return Node.get()->Data; }

        if (DataToFind < Node.get()->Data) { return find_helper(Node.get()->Left, DataToFind); }
        else { return find_helper(Node.get()->Right, DataToFind); }

    }
    const shared_ptr<Node> delete_helper(shared_ptr<Node> &node,T DataToDelete)
    {

        if (!node) { return node; }


        if (DataToDelete < node.get()->Data)
        {
            node.get()->Left = delete_helper(node.get()->Left, DataToDelete);
        }

        else if (DataToDelete > node.get()->Data)
        {
            node.get()->Right = delete_helper(node.get()->Right, DataToDelete);
        }
           

        else 
        {

            if (!node.get()->Left)
            {

                shared_ptr<Node> temp = node.get()->Right;
                node.reset();

                return temp;

            }

            else if (!node.get()->Right)
            {

                shared_ptr<Node> temp = node.get()->Left;
                node.reset();

                return temp;

            }


            shared_ptr<Node> temp = min_helper(node.get()->Right);

            node.get()->Data = temp.get()->Data;
            node.get()->Right = delete_helper(node.get()->Right, temp.get()->Data);

        }

        return node;

    }


    const shared_ptr<Node> min_helper(const shared_ptr<Node>& Node)const
    {

        if (Node->Left != nullptr) { return min_helper(Node.get()->Left); }
        else { return Node; }

    }
    const shared_ptr<Node> max_helper(const shared_ptr<Node>& Node)const
    {

        if (Node.get()->Right != nullptr) { return  max_helper(Node.get()->Right); }
        else { return Node; }

    }


    void inorderTraversal_helper(const shared_ptr<Node>& Node)
    {

        if (!Node) { return; }

        inorderTraversal_helper(Node.get()->Left);
        cout << Node.get()->Data << " ";
        inorderTraversal_helper(Node.get()->Right);

    }
    void preorderTraversal_helper(const shared_ptr<Node> &Node)
    {

        if (!Node) { return; }

        cout << Node.get()->Data << " ";

        preorderTraversal_helper(Node.get()->Left);
        preorderTraversal_helper(Node.get()->Right);

    }
    void postorderTraversal_helper(const shared_ptr<Node> &Node)
    {

        if (!Node) { return; }


        postorderTraversal_helper(Node.get()->Left);
        postorderTraversal_helper(Node.get()->Right);

        cout << Node.get()->Data << " ";

    }


    void inorderTraversalByStack_helper(shared_ptr<Node> &node)
    {

        stack<shared_ptr<Node>> _stack;
        shared_ptr<Node> temp = node;

        while (temp != nullptr || !_stack.empty())
        {

            while (temp != nullptr)
            {
                _stack.push(temp);
                temp = temp.get()->Left;
            }

            temp = _stack.top();
            _stack.pop();

            cout << temp.get()->Data << " ";
            temp = temp.get()->Right;

        }

    }
    void preorderTraversalByStack_helper(shared_ptr<Node>& node)
    {

        if (!node) { return; }


        stack<shared_ptr<Node>> _stack;
        _stack.push(node);


        while (!_stack.empty())
        {


            shared_ptr<Node> temp = _stack.top();

            cout << temp.get()->Data << " ";
            _stack.pop();


            if (temp.get()->Right) { _stack.push(temp.get()->Right); }
            if (temp.get()->Left) { _stack.push(temp.get()->Left); }


        }
    }
    void postorderTraversalByStack_helper(shared_ptr<Node>& node)
    {

        if (!node) { return; }

        stack <shared_ptr<Node>> _stack1, _stack2;
        _stack1.push(node);


        while (!_stack1.empty())
        {

            shared_ptr<Node> temp = _stack1.top();

            _stack1.pop();
            _stack2.push(temp);

            if (temp.get()->Left) { _stack1.push(temp.get()->Left); }
            if (temp.get()->Right) { _stack1.push(temp.get()->Right); }
                
        }


        while (!_stack2.empty())
        {

            shared_ptr<Node> temp = _stack2.top();

            cout << temp.get()->Data << " ";
            _stack2.pop();

        }

    }


    void clear_helper(shared_ptr<Node> &node)
    {

        if (node.get()->Left) { clear_helper(node.get()->Left); }
        if (node.get()->Right) { clear_helper(node.get()->Right); }
     
        node.reset();
        tree_size--;
      
    }


    /*  Thanks to https ://github.com/RonGreenberg/print-binary-tree-to-console  */
    void print_nodes_helper(const string& padding, const string& edge, shared_ptr<Node>node, bool has_left_sibling)
    {

        if (node != nullptr) 
        { 

            cout << endl << padding << edge << node.get()->Data;

          
            if ((!node.get()->Left) && (!node.get()->Right))
            {

                cout << endl << padding; 
                if (has_left_sibling) { cout << "|"; }  
           
            }

            else
            {
              
                string new_padding = padding + (has_left_sibling ? "|    " : "     ");

                print_nodes_helper(new_padding, "|----", node.get()->Right, node.get()->Left != nullptr);
                print_nodes_helper(new_padding, "|____", node.get()->Left, false);

            }

        }

    } 
    void print_tree_helper(shared_ptr<Node> &node)
    {
        
        if (!node) { return; }
         
        cout << node.get()->Data;

        print_nodes_helper("", "|----", node.get()->Right, node.get()->Left != nullptr);
        print_nodes_helper("", "|____", node.get()->Left, false);

    } 


private:


    shared_ptr<Node> Root;
    int tree_size;


};




int main()
{
  
  

	return 0;

}
