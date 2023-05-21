#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

// Create a structure to declare variable key, left child pointer and right child pointer.
struct Node{
   int key;  
   Node* left;
   Node* right;
};

class SplayTree{

    public:

    // Create a function to rotate to the right.
    Node* rightRotate(Node* k2){
        Node * k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        return k1;
    }


    // Create a function to rotate to the left.
    Node* leftRotate(Node *k2){
        Node* k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        return k1;
    }


    // Create a function Splay to implement top-down splay tree.
    Node* Splay(int key, Node* root){

        if (!root){
            return NULL;
        } 

        Node header;
        header.left = header.right = NULL;
        Node* leftTreeMax = &header;
        Node * rightTreeMin = &header;

        for(;;){

            if (key < root->key){

                if (!root->left){
                    break;
                }

                if (key < (root->left)->key){
                    root = rightRotate(root);
                    if(!root->left){
                        break;
                    }
                }

                rightTreeMin->left = root;
                rightTreeMin = rightTreeMin->left;
                root = root->left;
                rightTreeMin->left = NULL;
            }

            else if (key > root->key){
                if (!root->right){
                    break;
                }

                if (key > (root->right)->key){
                    root = leftRotate(root);
                    if (!root->right){
                        break;
                    }
                }

                leftTreeMax->right = root;
                leftTreeMax = leftTreeMax->right;
                root = root->right;
                leftTreeMax->right = NULL;
            }

            else{
                break;
            }
        }

        leftTreeMax->right = root->left;
        rightTreeMin->left = root->right;
        root->left = header.right;
        root->right = header.left;
        return root;
    }


    // Create a function New_Node() to create nodes in the tree.
    Node * New_Node(int key){
        Node* p_node = new Node;
        if(!p_node){
            fprintf(stderr, "Out of memory!\n");
            exit(1);
        }

        p_node->key = key;
        p_node->left = p_node->right = NULL;
        return p_node;
    }


    // Create a function Insert() to insert nodes into the tree.
    Node *Insert(int key, Node* root){

        static Node* p_node = NULL;

        if (!p_node){
            p_node = New_Node(key);
        }
        else{
            p_node->key = key;
        }
        if (!root){
            root = p_node;
            p_node = NULL;
            return root;
        }

        root = Splay(key, root);

        if (key < root->key){
            p_node->left = root->left;
            p_node->right = root;
            root ->left = NULL;
            root = p_node;
        }
        else if(key > root->key){
            p_node->right = root->right;
            p_node->left = root;
            root->right = NULL;
            root = p_node;
        }
        else{
            return root;
        }

        p_node = NULL;
        return root;
    }


    // Create a function Search() to search the nodes in the tree.
    Node* Search(int key, Node* root){
        return Splay(key, root);
    }


    // Traversal of the tree top check if the tree works correctly
    void InOrder(Node* root)
   {
      if (root)
      {
         InOrder(root->left);
         cout<< "key: " <<root->key;
         if(root->left)
         cout<< " | left child: "<< root->left->key;
         if(root->right)
         cout << " | right child: " << root->right->key;
         cout<< "\n";
         InOrder(root->right);
      }
   }

};





int main() {

   SplayTree st;
   Node *root;
   root = NULL;

   root = st.Insert(4, root);
   root = st.Insert(5, root);
   root = st.Insert(1, root);
   root = st.Insert(10, root);
   root = st.Insert(8, root);

   st.InOrder(root);

   root = st.Insert(10, root);
   root = st.Insert(11, root);
   root = st.Insert(3, root);

   st.InOrder(root);

   root = st.Search(10, root); //el search está eliminando el 10
   cout << "node buscado (deberia ser 10): " << root->key << endl;

   st.InOrder(root);

   root = st.Insert(4, root);

   st.InOrder(root);

    return 0;
}
