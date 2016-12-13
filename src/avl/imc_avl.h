#ifndef IMC_AVL

#define IMC_AVL

typedef imc_data_t;
typedef imc_key_t;

//----------------------------------------------------------------------------//
//----------------------------Data Structure----------------------------------//
//----------------------------------------------------------------------------//
typedef struct imc_avl_node_t{
    int balance; // Show if the tree is equilibrate (0) or
                 //  balance to the left (-1) or right (1).
    int ref_counter; //Used to free unreferenced internal nodes.

    struct imc_avl_node_t * left; // Left branch pf the tree.
    struct imc_avl_node_t * right; // right branch pf the tree.
    imc_data_t* data; // data stored in the node.
    imc_key_t* key; // key used to sort the nodes.

} imc_avl_node_t ;

//----------------------------------------------------------------------------//
//--------------------------Primitive FUnctions-------------------------------//
//----------------------------------------------------------------------------//
int imc_avl_size(imc_avl_t* vec);

imc_data_t* imc_avl_lookup(imc_avl_t* vec, imc_key_t* key);

/* stack operations */

// add at the end <--- DOXYGENIZE PLEASE!
imc_avl_t* imc_avl_insert(imc_avl_t* vec,
			      imc_data_t* data, imc_key_t* key);

imc_avl_t* imc_avl_remove(imc_avl_t* vec,
			     imc_data_t** data);

//Modify de the value associate to key
imc_avl_t* imc_avl_update(imc_avl_t* vec,
			      imc_data_t* data, imc_key_t* key);

int imc_avl_split(imc_avl_t* vec_in,
		     imc_key_t* key,
		     imc_avl_t** vec_out1,
		     imc_avl_t** vec_out2);

imc_avl_t* imc_avl_merge(imc_avl_t* vec_front,
			       imc_avl_t* vec_tail);

/* user-side memory management */

int imc_avl_unref(imc_avl_t* tree);

void imc_avl_dump(imc_avl_t* tree);
#endif