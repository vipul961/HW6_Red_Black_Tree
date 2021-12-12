//CSE674 HW6  Due: 11:59PM, Dec. 11 (Saturday)
//HW6 By Vipul Sawant
//SU ID 347120278
//vasawant@syr.edu
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


	void delete_3(node* p, bool b);
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
	t1.delete_node(10);
	t1.InorderPrint(t1.root);
	t1.delete_node(7);
	t1.InorderPrint(t1.root);
	t1.delete_node(15);
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
		cout << "( " << p->value << " " << s << " )";
	else
		cout << "( " << p->value << " " << s << " )";
	InorderPrint(p->p_Rchild);
}
void tree::L_rotate(node* p) {
	//cout << "Entered L rotate" << endl;
	
	node* temp{ p->p_Rchild };
	node* prlight{ temp };
	if (temp != nullptr) {
		prlight = temp->p_Lchild;
	}
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
	node* temp{ p->p_Lchild };
	node* plright{ temp };
	if (p->p_Lchild != nullptr) {
		plright = temp->p_Rchild;
	}
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
void tree::delete_node(int i) {
	node* temp{ root };
	while (temp->value != i) {
		if (i > temp->value) {
			temp = temp->p_Rchild;
		}
		else {
			temp = temp->p_Lchild;
		}
		if (temp == nullptr) {
			cout << endl;
			cout << "Node " << i << " is not present in tree" << endl;
			return;
		}
	}
	cout << endl;
	//cout << "value to be deleted is " << temp->value << endl;
	if (temp->p_Lchild == nullptr && temp->p_Rchild == nullptr && temp->color==true) {
		if (temp->is_left_child == true) {
			//cout << "delete left leaf node" << endl;
			temp->p_parent->p_Lchild = nullptr;
		}
		else {
			//cout << "delete right leaf node" << endl;
			temp->p_parent->p_Rchild = nullptr;
		}
	}
	else {
		if (temp->color == false && temp->p_Lchild!=nullptr && temp->p_Lchild->color == true && temp->p_Rchild == nullptr || temp->color == false && temp->p_Rchild != nullptr && temp->p_Rchild->color == true && temp->p_Lchild == nullptr) {
			if (temp->p_Lchild == nullptr) {
				temp->value = temp->p_Rchild->value;
				temp->p_Rchild = nullptr;
			}
			else {
				temp->value = temp->p_Lchild->value;
				temp->p_Lchild = nullptr;
			}
		}
		else {
			if(temp->color==false && temp->p_Lchild==nullptr && temp->p_Rchild==nullptr){
				if (temp->is_left_child == true) {
					temp->p_parent->p_Lchild = nullptr;
					if (temp->p_parent->p_Rchild==nullptr || temp->p_parent->p_Rchild->color == false) {
						if ((temp->p_parent->p_Rchild != nullptr && temp->p_parent->p_Rchild->p_Rchild != nullptr && temp->p_parent->p_Rchild->p_Rchild->color == true) || (temp->p_parent->p_Rchild != nullptr && temp->p_parent->p_Rchild->p_Lchild != nullptr && temp->p_parent->p_Rchild->p_Lchild->color == true)) {
							delete_1(temp->p_parent, false);
						}
						else {
							if (temp->p_parent->p_Rchild == nullptr ||( temp->p_parent->p_Rchild->p_Rchild == nullptr && temp->p_parent->p_Rchild->p_Lchild == nullptr || (temp->p_parent->p_Rchild->p_Rchild != nullptr && temp->p_parent->p_Rchild->p_Rchild->color == false) && (temp->p_parent->p_Rchild->p_Lchild != nullptr && temp->p_parent->p_Rchild->p_Lchild->color == false))) {
								if (temp->p_parent->color == false) {
									delete_2A(temp->p_parent, false);
								}
								else {
									delete_2B(temp->p_parent, false);
								}
							}
						}
					}
					else {
						delete_3(temp->p_parent, false);
					}
				}
				else {
					temp->p_parent->p_Rchild = nullptr;
					if (temp->p_parent->p_Lchild == nullptr || temp->p_parent->p_Lchild->color == false) {
						if ((temp->p_parent->p_Lchild != nullptr && temp->p_parent->p_Lchild->p_Lchild != nullptr && temp->p_parent->p_Lchild->p_Lchild->color == true) || (temp->p_parent->p_Lchild != nullptr && temp->p_parent->p_Lchild->p_Rchild != nullptr && temp->p_parent->p_Lchild->p_Rchild->color == true)) {
							delete_1(temp->p_parent, true);
						}
						else {
							if (temp->p_parent->p_Lchild == nullptr || (temp->p_parent->p_Lchild->p_Lchild == nullptr && temp->p_parent->p_Lchild->p_Rchild == nullptr || (temp->p_parent->p_Lchild->p_Lchild != nullptr && temp->p_parent->p_Lchild->p_Lchild->color == false) && (temp->p_parent->p_Lchild->p_Rchild != nullptr && temp->p_parent->p_Lchild->p_Rchild->color == false))) {
								if (temp->p_parent->color == false) {
									delete_2A(temp->p_parent, true);
								}
								else {
									delete_2B(temp->p_parent, true);
								}
							}
						}
					}
					else {
						delete_3(temp->p_parent, true);
					}
				}
			}
			else {
				node* pre{ temp->p_Lchild };
				node* suc{ temp->p_Rchild };
				if (pre != nullptr) {
					if (pre->p_Rchild != nullptr) {
						while (pre->p_Rchild != nullptr) {
							pre = pre->p_Rchild;
						}
					}
					if (pre->p_Lchild != nullptr) {
						node* preleft{ pre->p_Lchild };
						if (pre->is_left_child == true) {
							//temp->p_Lchild = nullptr;
							node* right{ temp->p_Rchild };
							temp->p_parent->p_Lchild = pre;
							pre->p_parent = temp->p_parent;
							pre->p_Rchild = right;
							right->p_parent = pre;
							if (pre->color == false) {
								preleft->color = false;
							}
							else {
								preleft->color = true;
							}
						}
						else {
							pre->p_parent->p_Rchild = preleft;
							preleft->p_parent = pre->p_parent;
							preleft->is_right_child = true;
							preleft->is_left_child = false;
							temp->value = pre->value;
							if (pre->color == true) {
								preleft->color = true;
							}
							else {
								preleft->color = false;
							}
						}
					}
					else {
						if (pre->color == true) {
							temp->value = pre->value;
							if (pre->is_left_child == true) {
								pre->p_parent->p_Lchild = nullptr;
							}
							else {
								pre->p_parent->p_Rchild = nullptr;
							}

						}
						else {
							temp->value = pre->value;
							if (pre->is_left_child == true) {
								pre->p_parent->p_Lchild = nullptr;
								if (pre->p_parent->p_Rchild == nullptr || pre->p_parent->p_Rchild->color == false) {
									if ((pre->p_parent->p_Rchild!= nullptr && pre->p_parent->p_Rchild->p_Rchild != nullptr && pre->p_parent->p_Rchild->p_Rchild->color == true) || (pre->p_parent->p_Rchild!=nullptr && pre->p_parent->p_Rchild->p_Lchild != nullptr && pre->p_parent->p_Rchild->p_Lchild->color == true)) {
										delete_1(pre->p_parent, false);
									}
									else {
										if (pre->p_parent->p_Rchild ==nullptr || (pre->p_parent->p_Rchild->p_Rchild == nullptr && pre->p_parent->p_Rchild->p_Lchild == nullptr || (pre->p_parent->p_Rchild->p_Rchild != nullptr && pre->p_parent->p_Rchild->p_Rchild->color == false) && (pre->p_parent->p_Rchild->p_Lchild != nullptr && pre->p_parent->p_Rchild->p_Lchild->color == false))) {
											if (pre->p_parent->color == false) {
												delete_2A(pre->p_parent, false);
											}
											else {
												delete_2B(pre->p_parent, false);
											}
										}
									}
								}
								else {
									delete_3(pre->p_parent, false);
								}
							}
							else {
								pre->p_parent->p_Rchild = nullptr;
								if (pre->p_parent->p_Lchild == nullptr || pre->p_parent->p_Lchild->color == false) {
									if ((pre->p_parent->p_Lchild != nullptr && pre->p_parent->p_Lchild->p_Lchild != nullptr && pre->p_parent->p_Lchild->p_Lchild->color == true) || (pre->p_parent->p_Lchild != nullptr && pre->p_parent->p_Lchild->p_Rchild != nullptr && pre->p_parent->p_Lchild->p_Rchild->color == true)) {
										delete_1(pre->p_parent, true);
									}
									else {
										if (pre->p_parent->p_Lchild == nullptr || (pre->p_parent->p_Lchild->p_Lchild == nullptr && pre->p_parent->p_Lchild->p_Rchild == nullptr || (pre->p_parent->p_Lchild->p_Lchild != nullptr && pre->p_parent->p_Lchild->p_Lchild->color == false) && (pre->p_parent->p_Lchild->p_Rchild != nullptr && pre->p_parent->p_Lchild->p_Rchild->color == false))) {
											if (pre->p_parent->color == false) {
												delete_2A(pre->p_parent, true);
											}
											else {
												delete_2B(pre->p_parent, true);
											}
										}
									}
								}
								else {
									delete_3(pre->p_parent, true);
								}
							}

						}
					}
				}
				else {
					if (suc->p_Lchild != nullptr) {
						while (suc->p_Lchild != nullptr) {
							suc = suc->p_Lchild;
						}
					}
					if (suc->p_Rchild != nullptr) {
						node* sucright{ suc->p_Rchild };
						if (suc->is_right_child == true) {
							node* left{ temp->p_Lchild };
							temp->p_parent->p_Rchild = suc;
							suc->p_parent = temp->p_parent;
							suc->p_Lchild = left;
							left->p_parent = suc;
							if (suc->color == false) {
								sucright->color = false;
							}
							else {
								sucright->color = true;
							}
						}
						else {
							suc->p_parent->p_Lchild = sucright;
							sucright->p_parent = suc->p_parent;
							sucright->is_left_child = true;
							sucright->is_right_child = false;
							temp->value = suc->value;
							if (suc->color == true) {
								sucright->color = true;
							}
							else {
								sucright->color = false;
							}
						}
					}
					else {
						if (suc->color == true) {
							temp->value = suc->value;
							if (suc->is_left_child == true) {
								suc->p_parent->p_Lchild = nullptr;
							}
							else {
								suc->p_parent->p_Rchild = nullptr;
							}
						}
						else {
							temp->value = suc->value;
							if (suc->is_left_child == true) {
								if (suc->p_parent->p_Rchild==nullptr || suc->p_parent->p_Rchild->color == false) {
									if ((suc->p_parent->p_Rchild != nullptr && suc->p_parent->p_Rchild->p_Rchild != nullptr && suc->p_parent->p_Rchild->p_Rchild->color == true) || (suc->p_parent->p_Rchild != nullptr && suc->p_parent->p_Rchild->p_Lchild != nullptr && suc->p_parent->p_Rchild->p_Lchild->color == true)) {
										delete_1(suc->p_parent, false);
									}
									else {
										if (suc->p_parent->p_Rchild == nullptr || (suc->p_parent->p_Rchild->p_Rchild == nullptr && suc->p_parent->p_Rchild->p_Lchild == nullptr || (suc->p_parent->p_Rchild->p_Rchild != nullptr && suc->p_parent->p_Rchild->p_Rchild->color == false) && (suc->p_parent->p_Rchild->p_Lchild != nullptr && suc->p_parent->p_Rchild->p_Lchild->color == false))) {
											if (suc->p_parent->color == false) {
												delete_2A(suc->p_parent, false);
											}
											else {
												delete_2B(suc->p_parent, false);
											}
										}
									}
								}
								else {
									delete_3(suc->p_parent, false);
								}
							}
							else {
								if (suc->p_parent->p_Lchild == nullptr || suc->p_parent->p_Lchild->color == false) {
									if ((suc->p_parent->p_Lchild != nullptr && suc->p_parent->p_Lchild->p_Lchild != nullptr && suc->p_parent->p_Lchild->p_Lchild->color == true) || (suc->p_parent->p_Lchild != nullptr && suc->p_parent->p_Lchild->p_Rchild != nullptr && suc->p_parent->p_Lchild->p_Rchild->color == true)) {
										delete_1(suc->p_parent, true);
									}
									else {
										if (suc->p_parent->p_Lchild == nullptr || (suc->p_parent->p_Lchild->p_Lchild == nullptr && suc->p_parent->p_Lchild->p_Rchild == nullptr || (suc->p_parent->p_Lchild->p_Lchild != nullptr && suc->p_parent->p_Lchild->p_Lchild->color == false) && (suc->p_parent->p_Lchild->p_Rchild != nullptr && suc->p_parent->p_Lchild->p_Rchild->color == false))) {
											if (suc->p_parent->color == false) {
												delete_2A(suc->p_parent, true);
											}
											else {
												delete_2B(suc->p_parent, true);
											}
										}
									}
								}
								else {
									delete_3(suc->p_parent, true);
								}
							}
						}
					}
				}
			}
		}
	}
}
//Case 1 of delete_node; p points to the parent of double black node; b is false if double black is the left child of its parent; else b is true.
void tree::delete_1(node* p, bool b) {
	if (b == false) {
		if (p->p_Rchild->p_Rchild!= nullptr && p->p_Rchild->p_Rchild->color == true) {
			L_rotate(p);
			if (p->color == true) {
				p->p_parent->color = true;
			}
			else
				p->p_parent->color = false;
				p->p_parent->p_Rchild->color = false;
				p->color = false;	
		}
		else {
			if (p->p_Rchild->p_Lchild != nullptr && p->p_Rchild->p_Lchild->color == true) {
				R_rotate(p->p_Rchild);
				p->p_Rchild->p_Rchild->color = true;
				p->p_Rchild->p_Lchild->color = true;
				p->p_Rchild->color = false;
				L_rotate(p);
				if (p->color == true) {
					p->p_parent->color = true;
				}
				else
					p->p_parent->color = false;
				p->p_parent->p_Rchild->color = false;
				p->color = false;
			}
		}
	}
	else {
		if (p->p_Lchild->p_Lchild != nullptr && p->p_Lchild->p_Lchild->color == true) {
			R_rotate(p);
			if (p->color == true) {
				p->p_parent->color = true;
			}
			else
				p->p_parent->color = false;
			p->p_parent->p_Lchild->color = false;
			p->color = false;
		}
		else {
			if (p->p_Lchild->p_Rchild != nullptr && p->p_Lchild->p_Rchild->color == true) {
				L_rotate(p->p_Lchild);
				p->p_Lchild->p_Lchild->color = true;
				p->p_Lchild->p_Rchild->color = true;
				p->p_Lchild->color = false;
				R_rotate(p);
				if (p->color == true) {
					p->p_parent->color = true;
				}
				else
					p->p_parent->color = false;
				p->p_parent->p_Lchild->color = false;
				p->color = false;
			}
		}
	}
}
//Case 2a of delete_node; p points to the parent of double black node; b is false if double black is the left child of its parent; else b is true.
void tree::delete_2A(node* p, bool b) {
	if (b == false) {
		p->p_Rchild->color = true;
	}
	else {
		p->p_Lchild->color = true;
	}
	if (p == root) {
		p->color = false;
	}
	else {
		if (p->is_left_child == true) {
			if (p->p_parent->p_Rchild == nullptr || p->p_parent->p_Rchild->color == false) {
				if ((p->p_parent->p_Rchild != nullptr && p->p_parent->p_Rchild->p_Rchild != nullptr && p->p_parent->p_Rchild->p_Rchild->color == true) || (p->p_parent->p_Rchild != nullptr && p->p_parent->p_Rchild->p_Lchild != nullptr && p->p_parent->p_Rchild->p_Lchild->color == true)) {
					delete_1(p->p_parent, false);
				}
				else {
					if (p->p_parent->p_Rchild == nullptr || (p->p_parent->p_Rchild->p_Rchild == nullptr && p->p_parent->p_Rchild->p_Lchild == nullptr || (p->p_parent->p_Rchild->p_Rchild != nullptr && p->p_parent->p_Rchild->p_Rchild->color == false) && (p->p_parent->p_Rchild->p_Lchild != nullptr && p->p_parent->p_Rchild->p_Lchild->color == false))) {
						if (p->p_parent->color == false) {
							delete_2A(p->p_parent, false);
						}
						else {
							delete_2B(p->p_parent, false);
						}
					}
				}
			}
			else {
				delete_3(p->p_parent, false);
			}
		}
		else {
			if (p->p_parent->p_Lchild == nullptr || p->p_parent->p_Lchild->color == false) {
				if ((p->p_parent->p_Lchild != nullptr && p->p_parent->p_Lchild->p_Lchild != nullptr && p->p_parent->p_Lchild->p_Lchild->color == true) || (p->p_parent->p_Lchild != nullptr && p->p_parent->p_Lchild->p_Rchild != nullptr && p->p_parent->p_Lchild->p_Rchild->color == true)) {
					delete_1(p->p_parent, true);
				}
				else {
					if (p->p_parent->p_Lchild == nullptr || (p->p_parent->p_Lchild->p_Lchild == nullptr && p->p_parent->p_Lchild->p_Rchild == nullptr || (p->p_parent->p_Lchild->p_Lchild != nullptr && p->p_parent->p_Lchild->p_Lchild->color == false) && (p->p_parent->p_Lchild->p_Rchild != nullptr && p->p_parent->p_Lchild->p_Rchild->color == false))) {
						if (p->p_parent->color == false) {
							delete_2A(p->p_parent, true);
						}
						else {
							delete_2B(p->p_parent, true);
						}
					}
				}
			}
			else {
				delete_3(p->p_parent, true);
			}
		}
	}
}
//Case 2b of delete_node; p points to the parent of double black node; b is false if double black is the left child of its parent; else b is true.
void tree::delete_2B(node* p, bool b) {
	if (b == false) 
		p->p_Rchild->color = true;
	else
		p->p_Lchild->color = true;
	p->color = false;
}
//Case 3 of delete_node; p points to the parent of double black node; b is false if double black is the left child of its parent; else b is true.
void tree::delete_3(node* p, bool b) {
	if (b == false) {
		L_rotate(p);
	}
	else {
		R_rotate(p);
	}
	p->color = true;
	p->p_parent->color = false;

	if (b == false) {
		if (p->p_Rchild == nullptr || p->p_Rchild->color == false) {
			if ((p->p_Rchild != nullptr && p->p_Rchild->p_Rchild != nullptr && p->p_Rchild->p_Rchild->color == true) || (p->p_Rchild != nullptr && p->p_Rchild->p_Lchild != nullptr && p->p_Rchild->p_Lchild->color == true)) {
				delete_1(p, false);
			}
			else {
				if (p->p_Rchild == nullptr || (p->p_Rchild->p_Rchild == nullptr && p->p_Rchild->p_Lchild == nullptr || (p->p_Rchild->p_Rchild != nullptr && p->p_Rchild->p_Rchild->color == false) && (p->p_Rchild->p_Lchild != nullptr && p->p_Rchild->p_Lchild->color == false))) {
					if (p->color == false) {
						delete_2A(p, false);
					}
					else {
						delete_2B(p, false);
					}
				}
			}
		}
		else {
			delete_3(p, false);
		}
	}
	else {
		if (p->p_Lchild == nullptr || p->p_Lchild->color == false) {
			if ((p->p_Lchild != nullptr && p->p_Lchild->p_Lchild != nullptr && p->p_Lchild->p_Lchild->color == true) || (p->p_Lchild != nullptr && p->p_Lchild->p_Rchild != nullptr && p->p_Lchild->p_Rchild->color == true)) {
				delete_1(p, true);
			}
			else {
				if (p->p_Lchild == nullptr || (p->p_Lchild->p_Lchild == nullptr && p->p_Lchild->p_Rchild == nullptr || (p->p_Lchild->p_Lchild != nullptr && p->p_Lchild->p_Lchild->color == false) && (p->p_Lchild->p_Rchild != nullptr && p->p_Lchild->p_Rchild->color == false))) {
					if (p->color == false) {
						delete_2A(p, true);
					}
					else {
						delete_2B(p, true);
					}
				}
			}
		}
		else {
			delete_3(p, true);
		}
	}
}