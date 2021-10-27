#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;

struct ListNode {
	ListNode* next;
	string translation;
};


struct Node {
	string key;					//po key-u formiram stablo => rec u recniku
	ListNode* translationList;	//head za listu prevoda(u listi se nalaze prevodi reci za svaki cvor)
	Node* left;
	Node* right;
	Node* father;
};

//RED		insert=>addAtEnd  delete=> deleteFirst
struct queueNode { 
	//red ciji su clanovi cvorovi stabla
	Node* node;
	queueNode* next;
};


queueNode* insertInQueue(queueNode* head,Node* node) {
	//dodavanje cvora stabla u red
	//dodajem na kraj reda

	queueNode* temp = new queueNode;
	temp->node = node;
	temp->next = nullptr;

	if (head == nullptr) {
		head = temp;
	}
	else {
		queueNode* tempHead = head;
		while (tempHead->next != nullptr) {
			tempHead = tempHead->next;
		}
		tempHead->next = temp;
	}
	return head;
}

void printQueue(queueNode* head) {
	while (head != nullptr) {
		cout << head->node->key << " ";
		head = head->next;
	}
	cout << endl;
}

queueNode* deleteFromQueue(queueNode* head) {
	if(head != nullptr){
		queueNode* tempHead = head;
		head = head->next;
		delete tempHead;
	}
	return head;
}

bool queueEmpty(queueNode* head) {
	if (head == nullptr) return true;
	else {
		return false;
	}
}

Node* getFromQueue(queueNode* head) {
	//vraca pokazivac na cvor stabla 
	if (head != nullptr) {
		return head->node;
	}
}

int queueSize(queueNode* head) {
	int size = 0;
	while (head) {
		size++;
		head = head->next;
	}
	return size;
}



void addAtEnd(ListNode* &head, string word) {
	//prosledjujem po referenci jer ne vracam pokazivac
	//dodavanje prevoda na kraj liste
	ListNode* node = new ListNode;
	node->translation = word;
	node->next = nullptr;

	ListNode* tempHead = head;

	if (head == nullptr) head = node;

	else {
		while (tempHead->next != nullptr) {
			tempHead = tempHead->next;
		}
		tempHead->next = node;
	}

}

void printList(ListNode* head) {
	while (head) {
		cout << head->translation<<" ";
		head = head->next;
	}
}

void deleteList(ListNode* head) {
	while (head) {
		ListNode* prev = head;
		head = head->next;
		delete prev;
	}
}


Node* newTreeNode(string word, string translation) {
	//unesem key, dodam prevod u listu i podesim sve pokazivace na null 
	Node* temp = new Node;
	temp->key = word;
	temp->translationList = nullptr;	//mora da se postavi na null !!!
	addAtEnd(temp->translationList, translation);	//ubacim prevod u listu 
	temp->left = temp->right = temp->father = nullptr;	//postavim sve pokazivace na null
	return temp;

}

Node* addTreeNode(Node* root, string word,string translation) {
	Node* temp = newTreeNode(word,translation);

	if (root == nullptr) {
		root = temp;
	}
	else {
		Node* tempRoot = root,*father=nullptr;

		while (tempRoot != nullptr) {
			father = tempRoot;		//pamtim trenutni cvor kao oca i prelazim na sina

			if (temp->key == tempRoot->key) {
				//ako je key jednak ocu i temp-u onda dodajem prevod u listu prevoda oca
				addAtEnd(tempRoot->translationList, translation);
				return root;
			}
			else if (temp->key < tempRoot->key) {
				tempRoot = tempRoot->left;
			}
			else if (temp->key > tempRoot->key) {
				tempRoot = tempRoot->right;
			}
		}
		//tempRoot ce ovde biti null, pristupam ocu preko father
		if (temp->key < father->key) {
			father->left = temp;
		}
		else if (temp->key > father->key) {
			father->right = temp;
		}
		temp->father = father;
	}
	return root;
}



void display(Node* root) {
	//rekurzivni obilazak
	if(root != nullptr){
		display(root->left);
		cout << root->key << " ";
		display(root->right);
		
	}
}

void levelOrder(Node* root) {
	cout << "LEVEL ORDER:" << endl;
	Node* tempHead = root;
	queueNode* queue = nullptr;

	queue = insertInQueue(queue, tempHead);
	while (!queueEmpty(queue)) {			//dok red nije prazan
		
		tempHead = getFromQueue(queue);		//dohvatim iz reda prvi element
		queue = deleteFromQueue(queue);		//orisem prvi element iz reda

		//obrada cvora
		cout << tempHead->key << "--";		//ispisem rec
		printList(tempHead->translationList);	// ispisem sve prevode
		//cout << "	";

		if (tempHead->left != nullptr) {			//ako ima levog sina dodaj u red
			queue = insertInQueue(queue,tempHead->left);
		}
		if (tempHead->right != nullptr) {		//ako ima desnog sina dodaj u red
			queue = insertInQueue(queue, tempHead->right);
		}
	}

}

void levelOrderLineByLine(Node* root) {
	cout << "ISPIS STABLA:" << endl;
	if (root == nullptr) {
		cout << "stablo je prazno!" << endl;
	}
	else {

		Node* tempHead = root;
		queueNode* queue = nullptr;
		int len = 0;

		queue = insertInQueue(queue, tempHead);
		while (!queueEmpty(queue)) {

			len = queueSize(queue);
			while (len > 0) {
				tempHead = getFromQueue(queue);
				queue = deleteFromQueue(queue);
				cout << tempHead->key << "--";
				printList(tempHead->translationList);
				cout << "	";

				if (tempHead->left != nullptr) {
					queue = insertInQueue(queue, tempHead->left);
				}
				if (tempHead->right != nullptr) {
					queue = insertInQueue(queue, tempHead->right);
				}
				len--;
			}
			cout << endl;

		}
	}
	


}



Node* search(Node* root,string key) {
	Node* tempHead = root;

	while ((tempHead != nullptr) && (key != tempHead->key)) {
		if (key < tempHead->key) {
			tempHead = tempHead->left;
		}
		else {
			tempHead = tempHead->right;
		}
	}
	if (tempHead == nullptr) {
		cout << "dati kljuc nije u stablu!";
	}
	return tempHead;
}

void printAllTranslations(Node* node) {
	if (node != nullptr) {
		printList(node->translationList);
	}
	else {
		cout << "cvor je null"<<endl;
	}
}

Node* insertTreeNode(Node* root) {
	string key, translation;
	cout << "unesi rec i prevod:";
	cin >> key >> translation;
	Node* newNode = newTreeNode(key, translation);

	Node* tempHead = root,*father=nullptr;
	while (tempHead != nullptr) {
		father = tempHead;
		if (tempHead->key == newNode->key) {
			addAtEnd(tempHead->translationList, translation);
			return root;
		}
		else if (key < tempHead->key) {
			tempHead = tempHead->left;
		}
		else {
			tempHead = tempHead->right;
		}
	}

	if (root == nullptr) {
		root = newNode;
	}
	else{
		//radim sa father jer je tempHead null
		if (key < father->key) {
			father->left = newNode;
		}
		else {
			father->right = newNode;
		}
	}

	return root;
}

Node* deleteTreeNode(Node* root, string key) {
	Node* tempHead = root,*q=nullptr;
	Node* replacementNode = nullptr;

	while (tempHead != nullptr && key != tempHead->key) {
		q = tempHead;
		if (key < tempHead->key) {
			tempHead = tempHead->left;
		}
		else { tempHead = tempHead->right; }

	}
	if (tempHead == nullptr) {
		cout << "kljuc se ne nalazi u stablu!";
		return root;
	}
	else {
		//brise u cvoru za brisanje sve prevode
		deleteList(tempHead->translationList);
		tempHead->translationList = nullptr;
	}

	if (tempHead->left == nullptr) {		//ako je levi sin null pamtim desnog sina
		replacementNode = tempHead->right;
	}
	else if (tempHead->right == nullptr) {	//ako je desni sin null pamtim levog sina
		replacementNode = tempHead->left;
	}

	//slucaj ako cvor koji se brise ima oba sina
	else {
		Node* rpFather = tempHead;
		replacementNode = tempHead->right;
		Node* succ = replacementNode->left;
		while (succ != nullptr) {
			rpFather = replacementNode;
			replacementNode = succ;
			succ = replacementNode->left;
		}
		if (tempHead != rpFather) {			//ako cvor koji se brise nije otac svog inorder naslednika
			rpFather->left = replacementNode->right;		//POSLEDNJE POPRAVLJENO BILO JE TEMPHEAD->RIGHT
			replacementNode->right = tempHead->right;
		}
		replacementNode->left = tempHead->left;

	}

	if (q == nullptr) {
		root = replacementNode;
	}
	else if (tempHead == q->left) {	//prevezujem pokazivac oca da bude null
		q->left = replacementNode;
	}
	else {
		q->right = replacementNode;
	}
	return root;
}

bool checkPrefix(Node* node, string prefix) {
	int len = prefix.length();
	for (int i = 0; i < len; i++) {
		if (prefix[i] != node->key[i]) return false;
	}
	return true;
}

void levelOrderWithPrefix(Node* root,string prefix) {
	cout <<endl;
	Node* tempHead = root;
	queueNode* queue = nullptr;

	queue = insertInQueue(queue, tempHead);
	while (!queueEmpty(queue)) {			//dok red nije prazan

		tempHead = getFromQueue(queue);		//dohvatim iz reda prvi element
		queue = deleteFromQueue(queue);		//orisem prvi element iz reda

		//obrada cvora

		if (checkPrefix(tempHead, prefix)) {
			cout << tempHead->key << "--";
			printList(tempHead->translationList);
		}

		cout << endl;

		if (tempHead->left != nullptr) {			//ako ima levog sina dodaj u red
			queue = insertInQueue(queue, tempHead->left);
		}
		if (tempHead->right != nullptr) {		//ako ima desnog sina dodaj u red
			queue = insertInQueue(queue, tempHead->right);
		}
	}

}

Node* deleteTree(Node* root) {
	Node* tempHead = root;
	queueNode* queue = nullptr;

	queue = insertInQueue(queue, tempHead);
	while (!queueEmpty(queue)) {			//dok red nije prazan

		tempHead = getFromQueue(queue);		//dohvatim iz reda prvi element
		queue = deleteFromQueue(queue);		//orisem prvi element iz reda


		if (tempHead->left != nullptr) {			//ako ima levog sina dodaj u red
			queue = insertInQueue(queue, tempHead->left);
		}
		if (tempHead->right != nullptr) {		//ako ima desnog sina dodaj u red
			queue = insertInQueue(queue, tempHead->right);
		}

		deleteList(tempHead->translationList);
		delete tempHead;
	}
	cout << "stablo je obrisano" << endl;
	return nullptr;
}

	
int main() {


	Node* root = nullptr;
	int choice = 1;

	string fileName;

	cout << "citaj podatke iz datoteke?" << endl;
	cout << "1) da" << endl; 
	cout << "2) ne" << endl;
	cin >> choice;

	//ako se podaci citaju iz datoteke
	//unosi se ime datoteke,otvara se datoteka i provera dal je nil
	if (choice == 1) {
		cout << "unesite ime datoteke:";
		cin >> fileName;
	}

	ifstream inputFile;
	inputFile.open(fileName);

	if (choice == 1) {
		if (inputFile.fail()) {
			cout << "problem sa otvaranjem datoteke";
			exit(-1);
		}
	}
	

	
	while (choice != 8) {

		
		cout << endl << "MENI:" << endl;
		cout << "1) Formiranje stabla" << endl;
		cout << "2) Pretraga stabla za dati kljuc" << endl;
		cout << "3) Umetanje " << endl;
		cout << "4) Ispis " << endl;
		cout << "5) Brisanje kljuca " << endl;
		cout << "6) ispis svih reci i njihovih prevoda sa datim prefiksom " << endl;
		cout << "7) Brisanje stabla " << endl;
		cout << "8) Kraj " << endl;
		cout << "9) formiraj stablo iz datoteke" << endl;

		cout << "birate:";
		cin >> choice;

		string* words = nullptr;
		string* translations = nullptr;
		Node* temp = nullptr;
		string word,prefix,translation;

		switch (choice)
		{
		case 1:
			int n;
			cout << " unesite koliko elemenata zelite:";
			cin >> n;
			words = new string[n];
			translations = new string[n];
			
			for (int i = 0; i < n; i++) {
				cout << "unesite rec i prevod :";
				cin >> words[i] >> translations[i] ;
			}
			for (int i = 0; i < n; i++) {
				root = addTreeNode(root, words[i], translations[i]);
			}

			break;

		case 2:
			cout << "unesite rec za koju zelite da se pretrazi stablo:";
			cin >> word;

			temp=search(root, word);
			if (temp != nullptr) {
				
				cout << "svi prevodi reci " << temp->key << " su:";
				printList(temp->translationList);
				cout << endl;
			}
			break;
			
		case 3:
			root = insertTreeNode(root);
			break;

		case 4:
			levelOrderLineByLine(root);
			display(root);
			cout << endl;
			break;

		case 5:
			cout << "koju rec zelite da obrisete:";
			cin >> word;
			root = deleteTreeNode(root, word);
			break;

		case 6:
			cout << "unesite prefiks:";
			cin >> prefix;
			levelOrderWithPrefix(root, prefix);
			break;

		case 7:
			root=deleteTree(root);
			break;
		case 8:
			cout << "kraj programa";
			break;

		case 9:

			

			while( !inputFile.eof()){
				inputFile >> word >> translation;
				root = addTreeNode(root, word, translation);
			}

			break;
		}
		
	}
	
	inputFile.close();

	//c jedan a dva d tri b cetiri q pet p sest s sedam
	 
	//ccc dva abivan tri ccaa cetiri  abbaki pet aaa sest ccq sedam ccs osam ccs devet
	
	/*root = addTreeNode(root, "ccc", "dva");
	root = addTreeNode(root, "abivan", "tri");
	root = addTreeNode(root, "ccaa", "cetiri");
	root = addTreeNode(root, "abbaki", "pet");
	root = addTreeNode(root, "aaa", "sest");
	root = addTreeNode(root, "ccq", "sedam");
	root = addTreeNode(root, "ccs", "osam"); 
	root = addTreeNode(root, "ccs", "devet");*/

	/*root = addTreeNode(root, "c", "dva");
	root = addTreeNode(root, "a", "tri");
	root = addTreeNode(root, "d", "cetiri");
	root = addTreeNode(root, "b", "pet");
	root = addTreeNode(root, "q", "sest");
	root = addTreeNode(root, "s", "sedam");
	root = addTreeNode(root, "p", "osam"); */

	
	/*cout << root->key<<endl;
	cout << root->right->key << endl;
	cout << root->right->right->key << endl;
	cout << root->right->right->left->key << endl;*/
	

	
	/*levelOrderLineByLine(root);
	display(root);
	cout << endl;*/


/*ifstream input;
input.open("ulaz.txt");

ofstream output; // za ispis
output.open("ime_datoteke");
output << "cao svete";
output.close();

if (input.fail()) {
	cout << "greska pri otvaranju datoteke!";
	exit(-1);
}

while (!input.eof()) {
	string rec,prevod;
	input >> rec >> prevod;
	cout << rec <<" " << prevod <<  endl;
}*/
	


}