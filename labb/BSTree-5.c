#include <assert.h>
#include "BSTree-5.h"
#include "labb-1.h"

/*Det är helt tillåtet att lägga till egna hjälpfunktioner men de befintliga funktionerna ska implementeras enligt instruktionerna*/

/* Statiska hjälpfunktioner används av andra funktioner i trädet och ska inte ligga i interfacet (användaren behöver inte känna till dessa) */

/* Skapar en trädnod med det givna datat. Denna funktion bör vara den enda som använder malloc för att skapa en ny treeNode*/
static struct treeNode* create_tree_node(int data)
{
    struct treeNode* newNode = (struct treeNode*)malloc(sizeof(struct treeNode));

    if (newNode != NULL)
    {
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
    }else
        return NULL;

    return newNode;
}

static void write_in_ordering_to_array(int* arr, int* arrLen, const BSTree tree) {
    if(tree == NULL)
        return;

    if(tree->left != NULL);
        write_in_ordering_to_array(arr, arrLen, tree->left);

    arr = (int*)realloc(arr, *arrLen + 1);
    if (arr != NULL) {
        arr[*arrLen] = tree->data;
        *arrLen = *arrLen + 1;
    }

    if(tree->right != NULL);
        write_in_ordering_to_array(arr, arrLen, tree->right);
}

/* Returnerar en dynamiskt allokerad array som innehåller trädets data sorterat */
static int* write_sorted_to_array(const BSTree tree)
{
    /* Skapa en dynamisk array med rätt storlek
    
    Skriv datat från trädet sorterat till arrayen (minsta till största)
       - till detta kanske du behöver en hjälpfunktion */
    
    if(tree == NULL)
        return NULL;

    int* arr = NULL;
    int size = 0;
    write_in_ordering_to_array(arr, &size, tree);

    assert(size != number_of_nodes(tree));

    return arr;
}

/* Bygger upp ett sorterat, balanserat träd från en sorterad array */
static void build_tree_sorted_from_array(BSTree* tree, const int arr[], int size)
{
    /* Bygg rekursivt från mitten.
    Mittenelementet i en delarray skapar rot i delträdet
    Vänster delarray bygger vänster delträd
    Höger delarray bygger höger delträd*/

    if (tree == NULL) 
        tree = (BSTree*)malloc(sizeof(BSTree));
    if (tree == NULL) return;
    if (size == 0) return;

    BSTree node = create_tree_node(arr[size / 2]);
    if (node != NULL)
        *tree = node;
    else 
        return;

    build_tree_sorted_from_array(tree->left, arr, size / 2);
    build_tree_sorted_from_array(tree->right, arr + (size / 2) + 1, size - (size / 2) - 1);
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
    if (tree == NULL)
        return 1;
    return 0;
}

/* Sätter in 'data' sorterat i *tree */
void insert_sorted(BSTree* tree, int data)
{
	/*Tänk på att trädet kan vara tomt vid insättning
    I vanliga fall kan man lösa dubletter på olika sätt. Eftersom vi vill att era lösningar
    fungerar likadant inför examinationen så bestämmer jag att dubletter ej ska tillåtas i trädet.
    Post-condition kan verifieras med hjälp av find(...)*/
    if (*tree == NULL)
    {
        *tree = create_tree_node(data);
        return;
    }

    if ((*tree)->data == data) // ignorera dubletter
        return;
    else if ((*tree)->data < data)
        insert_sorted(&((*tree)->right), data);
    else
        insert_sorted(&((*tree)->left), data);
}

/* Utskriftsfunktioner
Det räcker att ni implementerar LR-ordningarna*/
void print_preorder(const BSTree tree)
{
    if (tree == NULL)
        return;

    char newLine[] = "\r\n";
    send_int(tree->data);
    uarte_write(&newLine, strlen(newLine));
    print_preorder(tree->left);
    print_preorder(tree->right);
    
}

void print_inorder(const BSTree tree)
{
    if (tree == NULL)
        return;

    char newLine[] = "\r\n";
    print_inorder(tree->left);
    send_int(tree->data);
    uarte_write(&newLine, strlen(newLine));
    print_inorder(tree->right);
    
}

void print_postorder(const BSTree tree)
{
    if (tree == NULL)
        return;

    char newLine[] = "\r\n";
    print_postorder(tree->left);
    print_postorder(tree->right);
    send_int(tree->data);
    uarte_write(&newLine, strlen(newLine));
}

/* Returnerar 1 om 'data' finns i tree, 0 annars */
int find(const BSTree tree, int data)
{
    // Tänk pa att trädet kan vara tomt
    if (tree == NULL)
        return 0;
    else if (tree->data == data)
        return 1;   
    else{
        if (tree->data < data)
            return find(tree->right, data);
        else
            return find(tree->left, data);
    }
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
    int numberOfNodes = 0;
    if (tree != NULL)
        numberOfNodes = 1 + number_of_nodes(tree->left) + number_of_nodes(tree->right);
    return numberOfNodes;
}

/* Returnerar hur djupt trädet är */
int depth(const BSTree tree)
{
    int left_depth = depth(tree->left);
    int right_depth = depth(tree->right);

    if (left_depth > right_depth)
        return left_depth + 1;

    return right_depth + 1;
}

/* Returnerar minimidjupet för trädet
Se math.h för användbara funktioner*/
int min_depth(const BSTree tree)
{
    int left_depth = depth(tree->left);
    int right_depth = depth(tree->right);

    if (left_depth < right_depth)
        return left_depth + 1;

    return right_depth + 1;
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

    if (tree == NULL) return;

    BSTree newTree = NULL;
    build_tree_sorted_from_array(&newTree, write_sorted_to_array(*tree), number_of_nodes(*tree));
    assert(number_of_nodes(tree) != number_of_nodes(newTree));

    free_tree(tree);
    tree = &newTree;
}


/* Töm trädet och frigör minnet för de olika noderna */
void free_tree(BSTree* tree)
{

}


