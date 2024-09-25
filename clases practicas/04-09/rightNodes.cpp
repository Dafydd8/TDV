#include <iostream>
#include <queue>
#include <list>
#include <vector>
using namespace std;

// Data structure to store a binary tree node


struct Node
{
	int key;
	Node *left, *right;

	Node(int key)
	{
		this->key = key;
		this->left = this->right = nullptr;
	}
};

void print_queue(queue<Node*> q){
	while(!q.empty()){
		cout << q.front()->key << " ";
		q.pop();
	}
	cout << endl;
}
//Aca pueden decidir si devolver la lista o directamente ir haciendo prints de los nodos
vector<int> printRightView(Node* root){
	vector<int> rv;

	queue<Node*> nivel_actual;
	queue<Node*> nivel_abajo;

	nivel_actual.push(root);

	while(!nivel_actual.empty()){
		Node* current = nivel_actual.front();

		if(current->left != nullptr){
			nivel_abajo.push(current->left);
		}
		if(current->right != nullptr){
			nivel_abajo.push(current->right);
		}
		nivel_actual.pop();

		if(nivel_actual.empty()){
			rv.push_back(current->key);
			swap(nivel_actual, nivel_abajo);
		}
	}
	return rv;

}

int main()
{
	Node* root = new Node(1);
	root->left = new Node(2);
	root->right = new Node(3);
	root->left->right = new Node(4);
	root->right->left = new Node(5);
	root->right->right = new Node(6);
	root->right->left->left = new Node(7);
	root->right->left->right = new Node(8);

	vector<int> rigt_view = printRightView(root);
	for (int i = 0; i < rigt_view.size(); i++){
		cout << rigt_view[i] << " ";
	}
	cout << endl;

	return 0;
}