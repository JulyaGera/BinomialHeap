#include <iostream>
#include <cstdlib>
using namespace std;
struct Node {
	int key;
	Node * parent;
	Node * child;
	Node * sibling;
	int degree;
};
class Heap {
public:
Heap();
~Heap();

Node * init();
Node * make (int);
Node * insert(Node * , Node *);
Node * extractMin(Node *);
Node * merge(Node *, Node *);
Node * combine(Node*, Node *);
Node * find(Node* , int );
void nodes(Node *, Node *);
void backward(Node* );
int decreaseKey(Node* , int , int );
int Delete(Node* , int );
void show(Node* );

private:
	Node *H;
	Node *Hl;
};
Heap ::Heap()
{
	H = init();
	Hl = init();
}
Heap :: ~ Heap() {
	if (H == NULL)
	{
	}
	else {
		Node* p; Node* d;
		p = H;
		while (p != NULL)
		{
			if (p->sibling != NULL) {
				
				p = p->sibling;
			}
		}
		d = p;
		p = p->parent;
		p->sibling = NULL;

	}
}
Node * Heap::init() {
	Node* np;
	np = NULL;
	return np;
}

void Heap::nodes(Node *a, Node *b) {
	a->parent = b;
	a->sibling = b->child;
	b->child = a;
	b->degree = b->degree + 1;
}
Node *Heap::make(int k) {
	Node* p = new Node;
	p->key = k;
	return p;
}
Node * Heap::insert(Node * H, Node *x) {
	Node * H1 = init();
	x->parent = NULL;
	x->child = NULL;
	x->sibling = NULL;
	x->degree = 0;
	H1 = x;
	H = merge(H, H1);
	return H;
}
Node* Heap::merge(Node* H1, Node* H2)
{
	Node *H = init();
	H = combine(H1, H2);
	if (H == NULL)
		return H;
	Node* prev;
	Node* next;
	Node* x;
	prev= NULL;
	x = H;
	next = x->sibling;
	while (next != NULL)
	{
		if ((x->degree != next->degree) || ((next->sibling != NULL)
			&& (next->sibling)->degree == x->degree))
		{
			prev = x;
			x = next;
		}
		else
		{
			if (x->key <= next->key)
			{
				x->sibling = next->sibling;
				nodes(next, x);
			}
			else
			{
				if (prev == NULL)
					H = next;
				else
					prev->sibling = next;
				nodes(x, next);
				x = next;
			}
		}
		next = x->sibling;
	}
	return H;
}
Node* Heap::combine(Node* H1, Node* H2)
{
	Node* H = init();
	Node* a; Node* b;
	Node* atmp; Node* btmp;
	a = H1; b = H2;
	if (a != NULL)
	{
		if (b != NULL)
		{
			if (a->degree <= b->degree)
				H = a;
			else if (a->degree > b->degree)
				H = b;
		}
		else
			H = a;
	}
	else
		H = b;
	while (a != NULL && b != NULL)
	{
		if (a->degree < b->degree)
		{
			a = a->sibling;
		}
		else if (a->degree == b->degree)
		{
			atmp = a->sibling;
			a->sibling = b;
			a = atmp;
		}
		else
		{
			btmp = b->sibling;
			b->sibling = a;
			b = btmp;
		}
	}
	return H;
}
Node* Heap::extractMin(Node* H1)  //поиск корня х с минимальным значением ключа в списке корней Н
{
	int min;
	Hl = NULL;
	Node* q = NULL;
	Node* x = H1;
	if (x == NULL)
	{
		cout << "Error" << endl;
		return x;
	}
	min = x->key;
	Node* p = x;
	while (p->sibling != NULL)
	{
		if ((p->sibling)->key < min)
		{
			min = (p->sibling)->key;
			q = p;
			x = p->sibling;
		}
		p = p->sibling;
	}
	if (q == NULL && x->sibling == NULL)
		H1 = NULL;
	else if (q == NULL)
		H1 = x->sibling;
	else if (q->sibling == NULL)
		q = NULL;
	else
		q->sibling = x->sibling;
	if (x->child != NULL)
	{
		backward(x->child);
		(x->child)->sibling = NULL;
	}
	H = merge(H1, Hl);
	return x;
}
void Heap::backward(Node* a)
{
	if (a->sibling != NULL)
	{
		backward(a->sibling);
		(a->sibling)->sibling = a;
	}
	else Hl = a;
}
Node* Heap::find(Node* H, int k)
{
	Node* x = H;
	Node* p = NULL;
	if (x->key == k)
	{
		p = x;
		return p;
	}
	if (x->child != NULL && p == NULL)
		p = find(x->child, k);
	if (x->sibling != NULL && p == NULL)
		p = find(x->sibling, k);
	return p;
}
int Heap::decreaseKey(Node* H, int i, int k)
{
	int tmp;
	Node* p;
	Node* a;
	Node* b;
	p = find(H, i);
	if (p == NULL)
	{
		cout << "Error" << endl;
		return 0;
	}
	if (k > p->key)    // проверка на то, что текущий ключ x не меньше передаваемого ключа k  
	{
		cout << "Error" << endl;
		return 0;
	}
	p->key = k;
	a = p;
	b = p->parent;
	while (b != NULL && a->key < b->key)    // поднимаем  i с новым ключом k, пока это значение меньше значения в родительской вершине
	{
		tmp = a->key;
		a->key = b->key;
		b->key = tmp;
		a = b;
		b = b->parent;
	}
}
int Heap::Delete(Node* H, int k)
{
	Node* np;
	if (H == NULL)
	{
		cout << "\nError. Heap is empty";
		return 0;
	}
	decreaseKey(H, k, -1000); // уменьшение ключа до минимально возможного значения 
	np = extractMin(H); // удаление "всплывшего" элемента 
	if (np != NULL)
		cout << "Node was deleted" << endl;
}
void Heap::show (Node* H)
{
	Node* p;
	p = H;
	if (p != NULL)
	{
		show(p->sibling);
		cout << p->key << endl;
		show(p->child);
	}
	
}
int main() {
	int  elem, choice;
	Heap BinomHeap;
	Node* p;
	Node *H;
	H = BinomHeap.init();
	char ch;
	p = BinomHeap.make(10);
	H = BinomHeap.insert(H, p);
	p = BinomHeap.make(30);
	H = BinomHeap.insert(H, p);
	p = BinomHeap.make(20);
	H = BinomHeap.insert(H, p);

	while (true)
	{
		cout << "---------------------------------------\n";
		cout << "1->Insert element\n" ;
        cout << "2->Show\n";
		cout << "3->Extract minimum\n" ;
		cout << "4->Decrease key\n";
		cout << "5->Delete a node\n";	
		cout << "0->Exit\n";
		cout << "---------------------------------------\n";
		cout << "Enter Your Choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Write the inserting element: ";
			cin >> elem;
			p = BinomHeap.make(elem);
			H = BinomHeap.insert(H, p);
			break;
		case 2:
			cout << "Heap: " << endl;
			BinomHeap.show(H);
			break;
		case 3:
				p = BinomHeap.extractMin(H);
			if (p != NULL)
				cout << "Minimum key: " << p->key << endl;
			else
				cout << "Error. Heap is empty" << endl;
			break;
		case 4:
			cout << "Write the decreasing element: ";
			cin >> elem;
			cout << "Write new key value: ";
			cin >> choice;
			BinomHeap.decreaseKey(H, elem, choice);
			break;
		case 5:
			cout << "Write the deleting key: ";
			cin >> elem;
			BinomHeap.Delete(H, elem);
			break;
		case 0:
			exit(1);
		default:
			cout << "Incorrect choice";
		}
	}
	system("pause");
	return 0;
}
