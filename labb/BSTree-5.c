#include <assert.h>
#include "BSTree-5.h"
#include "labb-1.h"

/*Det är helt tillåtet att lägga till egna hjälpfunktioner men de befintliga funktionerna ska implementeras enligt instruktionerna*/

/* Statiska hjälpfunktioner används av andra funktioner i trädet och ska inte ligga i interfacet (användaren behöver inte känna till dessa) */

/* Skapar en trädnod med det givna datat. Denna funktion bör vara den enda som använder malloc för att skapa en ny treeNode*/
static struct treeNode* create_tree_node(int data)
{
    BSTree* newNode = (BSTree*)malloc(sizeof(BSTree));

    if (newNode != NULL)
    {
        (*newNode)->data = data;
        (*newNode)->left = NULL;
        (*newNode)->right = NULL;
    }else
        return NULL;

    return newNode;
}

/* Returnerar en dynamiskt allokerad array som innehåller trädets data sorterat */
static int* write_sorted_to_array(const BSTree tree)
{
    /* Skapa en dynamisk array med rätt storlek
    
    Skriv datat från trädet sorterat till arrayen (minsta till största)
       - till detta kanske du behöver en hjälpfunktion */
    

}

/* Bygger upp ett sorterat, balanserat träd från en sorterad array */
static void build_tree_sorted_from_array(BSTree* tree, const int arr[], int size)
{
    /* Bygg rekursivt från mitten.
    Mittenelementet i en delarray skapar rot i delträdet
    Vänster delarray bygger vänster delträd
    Höger delarray bygger höger delträd*/
}

/* Implementation av trädet, funktionerna i interfacet */

/* Skapar ett tomt träd - denna funktion ar färdig */
BSTree create_empty_tree(void)
{
	return NULL;
}

/* Returnerar 1 ifall trädet är tomt, 0 annars */
int is_empty(const BSTree tree)
{

}

/* Sätter in 'data' sorterat i *tree */
void insert_sorted(BSTree* tree, int data)
{
	/*Tänk på att trädet kan vara tomt vid insättning
    I vanliga fall kan man lösa dubletter på olika sätt. Eftersom vi vill att era lösningar
    fungerar likadant inför examinationen så bestämmer jag att dubletter ej ska tillåtas i trädet.
    Post-condition kan verifieras med hjälp av find(...)*/
}

/* Utskriftsfunktioner
Det räcker att ni implementerar LR-ordningarna*/
void print_preorder(const BSTree tree)
{

}

void print_inorder(const BSTree tree)
{

}

void print_postorder(const BSTree tree)
{

}

/* Returnerar 1 om 'data' finns i tree, 0 annars */
int find(const BSTree tree, int data)
{
    // Tänk pa att trädet kan vara tomt

}

/* Tar bort 'data' från trädet om det finns */
void remove_element(BSTree* tree, int data)
{
	/* Inget data ska/kan tas bort från ett tomt träd
    Tre fall: Ett löv (inga barn), ett barn (vänster eller höger), två barn
    
    Glöm inte att frigöra noden när den länkats ur trädet'*/
}

/* Returnerar hur många noder som totalt finns i trädet */
int number_of_nodes(const BSTree tree)
{

}

/* Returnerar hur djupt trädet är */
int depth(const BSTree tree)
{

}

/* Returnerar minimidjupet för trädet
Se math.h för användbara funktioner*/
int min_depth(const BSTree tree)
{

}

/* Balansera trädet så att depth(tree) == minDepth(tree) */
void balance_tree(BSTree* tree)
{
/* Förslag på algoritm:
- överfor trädet till en dynamiskt allokerad array med writeSortedToArray()
- töm trädet med freeTree()
- bygg upp trädet rekursivt från arrayen med buildTreeSortedFromArray()
- frigör minne för den dynamiskt allokerade arrayen


Post-conditions:
- tree har lika många noder som tidigare
  - djupet för trädet är samma som minimumdjupet för trädet */
}


/* Töm trädet och frigör minnet för de olika noderna */
void free_tree(BSTree* tree)
{

}


