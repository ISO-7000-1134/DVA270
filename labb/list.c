#include "list.h"
#include "labb-1.h"


//Returnera en tom lista - funktionen är färdig
List create_empty_list(void)
{
    return NULL;
}

//Här skapas nya noder. Denna funktion är den enda som ska använda malloc.
//Denna funktion ska i sin tur bara kallas av add_first och add_last.
//Notera att den är static och inte finns med i interfacet
static Node * create_list_node(const Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));

	if (newNode != NULL) {
		newNode->data = data;
		newNode->next = NULL;
		newNode->previous = NULL;
	} /*else 
		assert(1);*/

	return newNode;
}

//Är listan tom?
//Returnerar 1 om listan är tom, annars 0
int is_empty(const List list)
{

}

//Lägg till en nod först i listan
void add_first(List *list, const Data data)
{
	// Empty list -> add an item
	if (*list == NULL) {
		*list = create_list_node(data);
		return;
	}

	List head = *list;
	int listIsHead;

	// Find head
	while (head->previous != NULL)
		head = head->previous;
	listIsHead = head == *list;

	Node* first = create_list_node(data);

	// Check if new node was created
	if (first != NULL) {
		head->previous = first;
		first->next = head;
	} /*else 
		assert(1);*/

	if (listIsHead)
		*list = head;
}

//lägg till nod sist i listan
void add_last(List *list, const Data data)
{
	// Empty list -> add an item
	if (*list == NULL) {
		*list = create_list_node(data);
		return;
	}

	List tail = *list;
	int listIsTail;

	// Find tail
	while (tail->next != NULL)
		tail = tail->next;
	listIsTail = tail == *list;

	Node* last = create_list_node(data);

	if (last != NULL) {
		tail->next = last;
		last->previous = tail;
	} /*else 
		assert(1);*/
		
	if (listIsTail)
		*list = tail;
}

//Ta bort första noden i listan
//precondition: listan är inte tom (testa med assert)
void remove_first(List *head)
{
	assert(head != NULL); 
    assert((*head)->next != NULL); 
    Node* toRemove = head; 
    if ((*head)->next != NULL) 
        (*head)->next->previous = (*head)->previous; 
    free(toRemove); 
}

//ta bort sista noden i listan
//precondition: listan är inte tom (testa med assert)
void remove_last(List *tail)
{
	assert(tail != NULL); 
    assert((*tail)->next != NULL); 
    Node* toRemove = tail; 
    if ((*tail)->previous != NULL) 
        (*tail)->previous->next = (*tail)->next; 
    free(toRemove); 
}

//töm listan (ta bort alla noder ur listan)
//postcondition: Listan är tom, *list är NULL
void clear_list(List *head)
{
	//alla noder ska frigöras

	// Empty list
	assert(head != NULL);

	if ((*head)->previous != NULL)
		(*head)->previous->next = (*head)->next;
	if ((*head)->next != NULL)
		(*head)->next->previous = (*head)->previous;
	free(head);
}

//Skriv ut listan genom UART
void print_list(const List list)
{	
	assert(list != NULL);
	if (list == NULL) // If list is empty
		return;

	List head = list;
	// Find head
	while (head->previous != NULL)
		head = head->previous;

	char newLine[64] = "\n\r";
	while (head != NULL)
	{	
		send_int(head->data);
		uarte_write(newLine, strlen(newLine));
		head = head->next; // goes to next node
	}
}

//returnera första datat i listan
//precondition: listan är inte tom (testa med assert)
Data get_first_element(const List list)
{
	List head = list;

	//Find head
	while (head->previous != NULL)
		head = head->previous;

	return head->data;
}

//returnera sista datat i listan. 
//precondition: listan är inte tom (testa med assert)
Data get_last_element(const List list)
{
	List tail = list;

	// Find tail
	while (tail->next != NULL)
		tail = tail->next;

	return tail->data;
}

//Returnera hur många noder som finns i listan
int number_of_nodes(const List list)
{
	// Empty list
	if (list == NULL)
		return 0;

	List head = list;
	List tail = list;
	int count = 1;

	// Find the count of items between 'list' and tail
	while (tail->next != NULL) {
		tail = tail->next;
		count++;
	}
	// Find the count of items between 'list' and head
	while (head->previous != NULL) {
		head = head->previous;
		count++;
	}

	return count;
}

//Sök efter data i listan, returnera 1 om datat finns, annars 0.
int search(const List list, const Data data)
{	
	// Check if list is empty
	if (list == NULL)
		return 0;

	List head = list;

	// Find head
	// while (head->previous != NULL)
	// 	head = head->previous;

	if(head->data == data) {
		return 1;
	} else if(head->next == NULL)
		return 0;
	else
		return search(head->next, data);
}

//Ta bort data ur listan (första förekomsten), returnera 0 om datat inte finns, annars 1
int remove_element(List *list, const Data data)
{
	// Empty list
	if (list == NULL)
		return 0;

	List head = *list;

	// Find head
	while (head->previous != NULL)
		head = head->previous;

	// Delete first occurance
	while (head != NULL) {
		if(head->data == data) {
			if (head->previous != NULL)
				head->previous->next = head->next;
			if (head->next != NULL)
				head->next->previous = head->previous;
			free(head);
			return 1;
		} else if(head->next == NULL)
			return 0;
			
		head = head->next;
	}
}
