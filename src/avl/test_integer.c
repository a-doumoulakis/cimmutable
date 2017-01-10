
#include <stdlib.h>
#include <stdio.h>
#include "imc_avl.h"



int compare (int* a , int* b)
{
	return *a - *b;
}

void print (int* nb, char* b)
{

	sprintf(b, "(%03d)", *nb);
}

void parcour_infix(imc_avl_node_t* tree){
    if(tree == NULL) return;
    parcour_infix(tree->left);
    printf("tree->key = %d, tree->balance = %d\n", *tree->key,tree->balance);
    parcour_infix(tree->right);
}

int main ()
{
	imc_data_t* replace;

	imc_data_t data[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	imc_key_t key[8] = {10, 4, 6, 12, 14, 8, 16, 18};

	imc_avl_node_t* tree = NULL;
    int i;
	for (i = 0 ; i < 8 ; i++)
	{
        replace = NULL;
		tree = imc_avl_insert(tree, &data[i], &key[i], &compare, &replace);
		imc_avl_dump(tree, print);
        parcour_infix(tree);
	}

	
	replace = NULL;
	tree = imc_avl_remove(tree, &key[0], &compare, &replace);
    printf("tree->balance = %d\n", tree->balance);
	imc_avl_dump(tree, print);
    parcour_infix(tree);

    replace = NULL;
    tree = imc_avl_remove(tree, &key[3], &compare, &replace);
    printf("tree->balance = %d\n", tree->balance);
    imc_avl_dump(tree, print);
    parcour_infix(tree);

	//printf("%d\n", (int) *result);
	

	return 0;
}