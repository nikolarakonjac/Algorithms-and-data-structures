#include <iostream>

using namespace std;

//proba za git
//program funkcije za citanje, ispisivanje i unistavanje jednostruke liste celih brojeva
//glavna funkcija ispituje prethodne funkcije 


struct Elem {
	int data;
	Elem* next;
};

Elem* readList() {
	Elem* first = nullptr, * last=nullptr;
	cout << "unesi elemente: ";

	while (true) {
		int broj;
		cin >> broj;
		if (broj == 999) break;

		Elem* node = new Elem;
		node->data = broj;
		node->next = nullptr;

		last = ((first == nullptr) ? first:last->next ) = node;
	}
	return first;
}

void printList(Elem* head) {
	if (!head) {
		cout << "prazna lista;" << endl;
	}
	else {
		while (head) {
			cout << head->data << " ";
			head = head->next;
		}
		cout << endl;
	}
	
}

void deleteList(Elem* head) {
	while (head) {
		Elem* prev = head;
		head = head->next;
		delete prev;
	}
}

void sortList(Elem* head) {
	for (Elem* i = head; i != nullptr; i = i->next) {// ne moze do pretposlednjeg(i->next), ako je prazna lista -> greska
		for (Elem* j = i->next; j != nullptr; j = j->next) {
			if (i->data > j->data) {
				int temp = i->data; i->data = j->data; j->data = temp;
			}
		}
	}
}

void addAtEnd(Elem*& head) {
	int number;
	cout << "dodaj na kraj:";
	cin >> number;

	Elem* node = new Elem;
	node->data = number;
	node->next = nullptr;

	Elem* tempHead = head;

	if (head == nullptr) head = node;

	else {
		while (tempHead->next != nullptr) {
			tempHead = tempHead->next;
		}
		tempHead->next = node;
	}

}

/* PUSH ON STACK = addAtBeginning  */
void addAtBeginning(Elem*& head) {
	
	int number;
	cout << "dodaj na pocetak:";
	cin >> number;

	Elem* node = new Elem;
	node->data = number;
	node->next = nullptr;

	if (head == nullptr) head = node;
	else {
		node->next = head;
		head = node;
	}
}	

void deleteLast(Elem*& head) {
	
	if (head == nullptr) {
		cout << "lista je prazna!" << endl;
	}

	else {

		Elem* current = head,*previous=nullptr;
		for (; current->next != nullptr; previous = current, current = current->next);
		delete current;
		if (previous != nullptr) {
			previous->next = nullptr;
		}
		else {
			head = nullptr;
		}
		
	}
}

/*deleteFirst sa vracanjem vrednosti = pop*/
void deleteFirst(Elem*& head) {
	if (head == nullptr) {
		cout << "lista je prazna!" << endl;
	}
	else {
		Elem* tempHead = head;
		head = head->next;
		delete tempHead;
	}
}

int numberOfElements(Elem* head) {
	int counter = 0;
	while (head) {
		counter++;
		head = head->next;
	}
	return counter;
}



void deleteSpecificElement(Elem*& head, int position) {
	int lastElement = numberOfElements(head);
	if (position > lastElement) {
		cout << "pogresan unos, nema toliko elemenata u listi !" << endl;
	}
	if (position == 1) {
		deleteFirst(head);
	}
	
	if(position == lastElement) {
		deleteLast(head);
	}
	else {
		Elem* tempHead = head, *temp=nullptr;
		for (int i = 0; i < position - 2; i++) {
			tempHead = tempHead->next;
		}
		temp= tempHead->next;
		tempHead->next = tempHead->next->next;
		delete temp;
	}


}

void insertSorted(Elem*& head) {
	int number;
	cout << "unesi broj:";
	cin >> number;


	Elem* node = new Elem;
	node->data = number;
	node->next = nullptr;

	Elem* tempHead = head, * prev=nullptr;
	
	if (head == nullptr) {
		head = node;
	} 
	
	for (; tempHead != nullptr; prev = tempHead, tempHead = tempHead->next) {
		if (tempHead->data > number) {
			if (prev == NULL) {
				node->next = tempHead;
				head = node;
			}
			break;
		}
	}
	if (prev) {
		node->next = prev->next;
		prev->next = node;
	}
}

void deleteNodes(Elem*& head) {
	int number;
	cout << "unesi broj za brisanje:";
	cin >> number;

	for (Elem* current = head, *previous = nullptr; current != NULL;) {
		if (current->data == number) {
			Elem* old = current;
			current = current->next;
			delete old;

			if (previous == 0) {
				head = current;
			}	
			else {
				previous->next = current;
			}
		}
		else {
			previous = current;
			current = current->next;
		}
	}
}

Elem* mergeLists(Elem* head0, Elem* head1) {
	Elem* head = nullptr;	//pocetak nove liste
	Elem* last = nullptr;

	Elem* current0 = head0;
	Elem* current1 = head1;

	while (current0 != nullptr && current1 != nullptr) {
		Elem* temp = nullptr;
		if (current0->data < current1->data) {
			temp = current0;
			current0 = current0->next;
		}
		else {
			temp = current1;
			current1 = current1->next;
		}

		temp->next = nullptr;

		/*if (last == nullptr) {	//ako je lista prazna;pocetak pokazuje na novi cvor
			head = temp;
		}
		else {					//ako lista nije prazna;stari poslednji vezemo za novi cvor
			last->next = temp;
		}	
		last = temp;*/		// novi cvor postaje novi poslednji cvor u listi

		last = ((last == nullptr)?  head : last->next  ) = temp;  //OBAVEZNE SU ZAGRADE OKO UNUTRASNJEG IZRAZA
																//INACE NECE HTETI DA RADI	
		printList(head);
	}

	if (current0 != nullptr) {	// ako neki niz nije stigao do kraja
		if (last == nullptr) {	// da li postoji vec nesto u rezultujucoj listi (jer ne moze last->next) ako je lastw= null
			head = current0;
		}
		else last->next = current0;
	}

	if (current1 != nullptr) {
		if (last == nullptr) {
			head = current1;
		}
		else last->next = current1;
	}
	
	return head;
}

Elem* reverseList(Elem* head) {
	Elem* previous = nullptr;
	Elem* next = head;
	Elem* current = nullptr;

	while (next != nullptr) {
		current = next;
		next = next->next;
		current->next = previous;
		previous = current;
	}

	return current;
}

void middElem(Elem* head){
	Elem* fast = head;
	Elem* slow = head;

	while (fast != nullptr) {
		fast = fast->next;
		if (fast) {
			fast = fast->next;
			slow = slow->next;
		}
	}
	cout << "midd: " << slow->data << endl;
}

void getNFromEnd(Elem* head) {
	int n;
	cout << "n:";
	cin >> n;

	Elem* fast = head,*slow=head;
	for (int i = 0; i < n && fast != nullptr ; i++) {
		fast = fast->next;
	}

	while (fast != nullptr) {
		fast = fast->next;
		slow = slow->next;
	}

	cout << "n ti od pozadi je:" << slow->data<<endl;
}

void loopExists(Elem* head) {
	Elem* fast = head, * slow = head;
	
	while (fast != nullptr) {
		slow = slow->next;
		fast = fast->next;
		if (fast != nullptr) {
			fast = fast->next;
		}
		if (fast == slow) {
			cout << "postoji petlja!" << endl;
		}
	}
	cout << "ne postoji petlja!" << endl;
}

int binarySearch(int* arr, int len, int value) {

	int low = 0;
	int high = len - 1;

	while (low <= high) {
		int middle = (low + high) / 2;
		if (arr[middle] == value) {
			return middle;
		}
		else if (arr[middle] > value) {	  //odbacujemo desnu stranu(ako je rastuci niz), pomeramo gornju granicu
			high = middle - 1;
		}
		else {
			low = middle + 1;
		}
	}

	return -1;

}




//STEK
/*
	STEK
	push => addAtBeginnig		(1,2,3) ->  3->2->->1
	pop =>  deleteFirst					
	stackEmpty()

	PRIMER:
	Elem* top = nullptr; 
	addAtBeginning(top);
	addAtBeginning(top);
	addAtBeginning(top);

	while (!stackEmpty(top)){
		int x = pop(top);
		cout << x << " ";
	}


*/

int pop(Elem*& top) {
	if (top == nullptr) {
		cout << "lista je prazna!" << endl;
		return 0;
	}
	else {
		int key;
		Elem* tempTop = top;
		key = tempTop->data;
		top = top->next;
		delete tempTop;
		return key;
	}
}

int stackEmpty(Elem* top) {
	if (top == nullptr) {
		return 1;
	}
	else {
		return 0;
	}
}

//RED		insert=>addAtEnd  delete=> deleteFirst
/*

	Elem* queue = nullptr;

	addAtEnd(queue);
	addAtEnd(queue);
	addAtEnd(queue);
	printList(queue);

	deleteFirst(queue);
	printList(queue);
	deleteFirst(queue);
	printList(queue);
	deleteFirst(queue);
	printList(queue);
*/


 
int main() {

			

}