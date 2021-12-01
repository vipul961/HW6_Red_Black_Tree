//CSE674 HW6  Due: 11:59PM, Dec. 11 (Saturday)
#include <iostream>
using namespace std;

class node {
public:
	node* p_parent;
	node* p_Lchild;
	node* p_Rchild;
	int value;
	bool color; //true: red, false: black
	bool is_left_child;
	bool is_right_child;
	node() { p_parent = p_Lchild = p_Rchild = nullptr; is_left_child = is_right_child = false; }
	node(int i) { value = i; p_parent = p_Lchild = p_Rchild = nullptr; is_left_child = is_right_child = false; }
};

class tree {
public:
	node* root;
	tree() { root = nullptr; }
	void R_rotate(node* p);//R-rotate at node pointed by p
	void L_rotate(node* p);//L-rotate at node pointed by p
	//R_rotate and L_rotate will be called by insert_node, delete_node, delete_1, delete_2A, delete_2B, and delete_3.

	void add_node(int i);//same policy as HW5 for avl trees.

	void delete_node(int i);//same policy as HW5 for avl trees.



	void delete_1(node* p, bool b);
	//Case 1 of delete_node; p points to the parent of double black node; b is false if double black is the left child of its parent; else b is true.

	void delete_2A(node* p, bool b);
	//Case 2A of delete_node; p points to the parent of double black node; b is false if double black is the left child of its parent; else b is true.

	void delete_2B(node* p, bool b);
	//Case 2B of delete_node; p points to the parent of double black node; b is false if double black is the left child of its parent; else b is true.


	void delete_3(node* p, bool);
	//Case 3 of delete_node; p points to the parent of double black node; b is false if double black is the left child of its parent; else b is true.


	//For the following, during traveral, print (value, color) of each node.
	void InorderPrint(node* p);//Print all nodes of a subtree rooted at node pointed by p; Example: (12 R) (7 B) (11 R) ...

};

int main(){
	tree t1;
	t1.add_node(10);
	t1.add_node(18);
	t1.add_node(7);
	t1.add_node(15);
	t1.add_node(16);
	t1.add_node(30);
	t1.add_node(25);
	t1.add_node(40);
	t1.add_node(60);
	t1.add_node(2);
	t1.add_node(1);
	t1.add_node(70);
	t1.InorderPrint(t1.root);
	return 0;
}

void tree::add_node(int i) {
	node* n1{ new node(i) };
	n1->color = true;
	if (root == nullptr) {
		root = n1;
		n1->color = false;
	}
	else {
		int side = 0;
		node* temp{ root };
		node* n2{ root };
		int val = 0;
		while (temp != nullptr) {
			if (i >= temp->value) {
				n2 = temp;
				temp = temp->p_Rchild;
				side = 1;
			}
			else {
				n2 = temp;
				temp = temp->p_Lchild;
				side = 0;
			}
		}
		if (side == 0) {
			n2->p_Lchild = n1;
			n1->p_parent = n2;
			n1->is_left_child = true;
		}
		else {
			n2->p_Rchild = n1;
			n1->p_parent = n2;
			n1->is_right_child = true;
		}
		n2 = n1;
		while (n2->p_parent != nullptr) {
			if (n1->color==true && n1->p_parent->color == true) {
				node* par{ n1->p_parent };
				node* gp{ n1->p_parent->p_parent };
				node* unc{ n1 };
				if (n1->p_parent->is_left_child == true) {
					unc = n1->p_parent->p_parent->p_Rchild;
				}
				else
					unc = n1->p_parent->p_parent->p_Lchild;
				if (unc == nullptr || unc->color == false  ) {
					
					if (n1->p_parent->is_left_child == true && n1->is_left_child == true  ) {
						val = 1;
					}
					if (n1->p_parent->is_left_child == true && n1->is_right_child == true ) {
						val = 2;
					}
					if ( n1->p_parent->is_right_child == true && n1->is_left_child == true ) {
						val = 3;
					}
					if (n1->p_parent->is_right_child == true && n1->is_right_child == true  ) {
						val = 4;
					}
					switch (val) {
					case 1: R_rotate(gp);
						gp->color = true;
						par->color = false;
						break;
					case 2: L_rotate(par);
							R_rotate(gp);
							gp->color = true;
							n1->color = false;
							break;
					case 3:	R_rotate(par);
							L_rotate(gp);
							gp->color = true;
							n1->color = false;
							break;
					case 4: L_rotate(gp);
							gp->color = true;
							par->color = false;
							break;
					default:
							break;
					}
				}
				else {
					par->color = false;
					gp->color = true;
					unc->color = false;
					if (gp == root) { gp->color = false; }
				}

			}
			n1 = n1->p_parent;
			n2 = n1;
		}
	}
}

void tree::InorderPrint(node* p) {
	if (p == nullptr) { return; }
	InorderPrint(p->p_Lchild);
	string s;
	if (p->color == true) { s = 'R'; }
	else s = 'B';
	if (p->p_parent == nullptr)
		cout << "( " << p->value <<" " << s << " )" << endl;
	else
		cout << "( " << p->value <<" " << s << " )" << endl;
	InorderPrint(p->p_Rchild);
}
void tree::L_rotate(node* p) {
	//cout << "Entered L rotate" << endl;
	node* prlight{ p->p_Rchild->p_Lchild };
	node* temp{ p->p_Rchild };
	if (p->p_parent == nullptr) {
		//p->p_Rchild == nullptr;
		temp->p_Lchild = p;
		p->p_Rchild = prlight;
		if (prlight != nullptr) {
			prlight->p_parent = p;
			prlight->is_left_child = false;
			prlight->is_right_child = true;
		}
		temp->p_parent = p->p_parent;
		temp->is_right_child = false;
		temp->is_left_child = false;
		p->p_parent = temp;
		p->is_right_child = false;
		p->is_left_child = true;
		root = temp;
	}
	else {
		//p->p_Rchild == nullptr;
		if (p->is_left_child == true) {
			p->p_parent->p_Lchild = temp;
			temp->is_right_child = false;
			temp->is_left_child = true;
		}
		else {
			p->p_parent->p_Rchild = temp;
			temp->is_left_child = false;
			temp->is_right_child = true;
		}
		temp->p_Lchild = p;
		p->p_Rchild = prlight;
		if (prlight != nullptr) {
			prlight->p_parent = p;
			prlight->is_left_child = false;
			prlight->is_right_child = true;
		}
		temp->p_parent = p->p_parent;
		p->p_parent = temp;
		p->is_right_child = false;
		p->is_left_child = true;
	}
}
void tree::R_rotate(node* p) {
	//cout << "entered R rotate" << endl;
	node* plright{ p->p_Lchild->p_Rchild };
	node* temp{ p->p_Lchild };
	if (p->p_parent == nullptr) {
		//p->p_Lchild == nullptr;
		temp->p_Rchild = p;
		p->p_Lchild = plright;
		if (plright != nullptr) {
			plright->p_parent = p;
			plright->is_left_child = true;
			plright->is_right_child = false;
		}
		temp->p_parent = p->p_parent;
		temp->is_right_child = false;
		temp->is_left_child = false;
		p->p_parent = temp;
		p->is_right_child = true;
		p->is_left_child = false;
		root = temp;
	}
	else {
		//p->p_Lchild == nullptr;
		if (p->is_right_child == true) {
			p->p_parent->p_Rchild = temp;
			temp->is_right_child = true;
			temp->is_left_child = false;
		}
		else {
			p->p_parent->p_Lchild = temp;
			temp->is_left_child = true;
			temp->is_right_child = false;
		}
		temp->p_Rchild = p;
		p->p_Lchild = plright;
		if (plright != nullptr) {
			plright->p_parent = p;
			plright->is_right_child = false;
			plright->is_left_child = true;
		}
		temp->p_parent = p->p_parent;
		p->p_parent = temp;
		p->is_right_child = true;
		p->is_left_child = false;
	}
}