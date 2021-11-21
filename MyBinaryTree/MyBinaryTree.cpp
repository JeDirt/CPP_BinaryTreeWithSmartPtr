#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <stack>
#include <ctime>
#include <random>
#include <chrono>


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
    T find(const T DataToFind)const
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


    T min()const
    { 
        auto min_value = min_helper(Root); 
        return min_value.get()->Data; 
    }
    T max()const
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


    int size()const { return this->tree_size; }
    void clear() { clear_helper(Root); }
    void print_tree() { print_tree_helper(Root); }


private:


    shared_ptr<Node> createNode(const T DataToPaste)
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
    T find_helper(const shared_ptr<Node>& Node, const T DataToFind)const
    {

        if (!Node.get()) { return T(); }
        if (Node.get()->Data == DataToFind) { return Node.get()->Data; }

        if (DataToFind < Node.get()->Data) { return find_helper(Node.get()->Left, DataToFind); }
        else { return find_helper(Node.get()->Right, DataToFind); }

    }
    shared_ptr<Node> delete_helper(shared_ptr<Node> &node,T DataToDelete)
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


    shared_ptr<Node> min_helper(const shared_ptr<Node>& Node)const
    {

        if (Node->Left != nullptr) { return min_helper(Node.get()->Left); }
        else { return Node; }

    }
    shared_ptr<Node> max_helper(const shared_ptr<Node>& Node)const
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


// Random generators for generating results
auto CreateRandomGenerator(const int start_range, const int end_range)
{

    // An instance of an engine
    random_device random_device;

    // Specify the engine and distribution
    mt19937 engine{ random_device() };
    uniform_int_distribution<int> distribution{ start_range, end_range };


    return  [&distribution, &engine]() { return distribution(engine); };

}
int GenerateRandomValue(const int start_range, const int end_range)
{
    return CreateRandomGenerator(start_range, end_range)();
}
vector<int> GenerateVector(const int start_range, const int end_range, int vector_length)
{

    if (vector_length < 0) { vector_length = 1; }

    vector<int> temp(vector_length);
  
    for (size_t i = 0; i < vector_length; i++)
    {
        temp[i] = GenerateRandomValue(start_range, end_range);
    }

    return temp;

}



// Time trackers, used it to build some line charts

/*
auto begin = chrono::steady_clock::now();
auto end = chrono::steady_clock::now();
*/
//auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - begin);
// cout << "runtime = " << elapsed_ms.count() <<" ms/n"<< endl;



// Demonstrating results of the work(needed only for personal purposes)
int main()
{

   
    BinaryTree<int>tree;
    vector<int>test_data{ GenerateVector(1,100,10) };

    cout << "Generated array -> ";
    for_each(test_data.begin(), test_data.end(), [](auto v) {cout << v << " "; });
    cout << endl << endl;



    for (size_t i = 0; i < test_data.size(); i++)
    {
        tree.push(test_data[i]);
    }

   
    tree.print_tree();
    cout << endl;

    cout << "Min element is " << tree.min() << endl;
    cout << "Max element is " << tree.max() << endl;

    int searched_and_deleted = GenerateRandomValue(1,100);
    cout << endl << "Looking for element "<< searched_and_deleted <<" there we have " << tree.find(searched_and_deleted) << endl;

    int searched = GenerateRandomValue(1, 100);
    cout << "Looking for element " << searched << " there we have " << tree.find(searched) << endl;


  
    cout << "\n\nLet's delete element " << searched_and_deleted << ":" << endl << endl;
    tree.delete_element(searched_and_deleted);
    tree.print_tree();

	return 0;

}
