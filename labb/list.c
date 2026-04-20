#include "list.h"



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
	}

	return newNode;
}

//Är listan tom?
//Returnerar 1 om listan är tom, annars 0
int is_empty(const List list)
{

}

//Lägg till en nod först i listan
void add_first(List *head, const Data data)
{
	Node* first = *head;

	*head = create_list_node(data);

	if (*head != NULL) {
		*head->next = first;
	} else {
		*head = first;
	}
}

//lägg till nod sist i listan
void add_last(List *tail, const Data data)
{
	Node* last = *tail;

	*tail = create_list_node(data);

	if (*tail != NULL) {
		*tail->previous = last;
	} else {
		*tail = last;
	}

}

//Ta bort första noden i listan
//precondition: listan är inte tom (testa med assert)
void remove_first(List *list)
{

}

//ta bort sista noden i listan
//precondition: listan är inte tom (testa med assert)
void remove_last(List *list)
{

}

//töm listan (ta bort alla noder ur listan)
//postcondition: Listan är tom, *list är NULL
void clear_list(List *list)
{
	//alla noder ska frigöras
}

//Skriv ut listan genom UART
void print_list(const List list)
{

}

//returnera första datat i listan
//precondition: listan är inte tom (testa med assert)
Data get_first_element(const List list)
{

}

//returnera sista datat i listan. 
//precondition: listan är inte tom (testa med assert)
Data get_last_element(const List list)
{

}

//Returnera hur många noder som finns i listan
int number_of_nodes(const List list)
{

}

//Sök efter data i listan, returnera 1 om datat finns, annars 0.
int search(const List list, const Data data)
{
	
}

//Ta bort data ur listan (första förekomsten), returnera 0 om datat inte finns, annars 1
int remove_element(List *list, const Data data)
{
	if(*list->data == data) {
		if (*list->previous != NULL)
			*list->previous->next = *list->next;
		if (*list->next != NULL)
			*list->next->previous = *list->previous;
		free(*list);
		return 1;
	} else if(list->next == NULL)
		return 0;
	else 
		return remove_element(*list->next, data);
}
