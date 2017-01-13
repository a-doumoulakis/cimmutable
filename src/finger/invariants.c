#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "fingertree.h"

void checkNode(node* n) {
    if (n->type == DATA_TYPE) {
        assert(n->size==1);
    } else {
        int predictedSize = 0;
        for (int i = 0; i < 3; i++) {
            if (n->true_node->internal_node[i] != NULL) {
                checkNode(n->true_node->internal_node[i]);
                predictedSize += n->true_node->internal_node[i]->size;
            }
            else
                break;
        }
        
        assert(predictedSize == n->size);
    }
}

void checkAffix(affix* a, int preorsuf) {
    int predictedSize = 0;
    int nonNullCellCounter = 0;
    
    for (int i = 0; i < 4; i++) {
        if (a->nodes[i] != NULL) {
            checkNode(a->nodes[i]);
            predictedSize += a->nodes[i]->size;
            nonNullCellCounter++;
        }
    }
    
    int shouldNotHaveElements = 0;
    
    if (preorsuf == 0) {
        // Prefix
        assert(a->nodes[0] != NULL);
        
        for (int i = 1; i < 4; i++) {
            if (a->nodes[i] != NULL) {
                assert(shouldNotHaveElements == 0);
            }
            else {
                shouldNotHaveElements = 1;
            }
        }
    }
    else {
        // Suffix
        assert(a->nodes[3] != NULL);
        
        for (int i = 2; i >= 0; i--) {
            if (a->nodes[i] != NULL) {
                assert(shouldNotHaveElements == 0);
            }
            else {
                shouldNotHaveElements = 1;
            }
        }
    }
    
    assert(nonNullCellCounter >= 0 && nonNullCellCounter <= 4);
    assert(predictedSize == a->size);
}

void checkFingerTree(ft* fgt) {
    if (fgt->type == EMPTY_TYPE) {
        assert(fgt->size==0);
    }
    else if (fgt->type == SINGLE_TYPE) {
        node* n = fgt->true_ft->single;
        checkNode(n);
        assert(fgt->size==n->size);
    }
    else if (fgt->type == DEEP_TYPE) {
        // Prefix
        affix* prefix = fgt->true_ft->d->prefix;
        checkAffix(prefix,0);
        
        // Deeper
        ft* deeper = fgt->true_ft->d->deeper;
        checkFingerTree(deeper);
        
        // Suffix
        affix* suffix = fgt->true_ft->d->suffix;
        checkAffix(suffix,1);
        
        // Finger tree itself
        assert(fgt->size == prefix->size + deeper->size + suffix->size);
    }
}

void checkInvariants(ft* fgt) {
    // ====== Invariants to be checked ======
    // === Node Invariants===
    // Nodes are either NODE_TYPE or DATA_TYPE

    // A DATA_TYPE Node does not contain another Node

    // A NODE_TYPE Node does contain 2 or 3 Nodes

    // ===Finger tree Invariant===
    // Finger trees are either DEEP_TYPE, SINGLE_TYPE or EMPTY_TYPE

    // A SINGLE_TYPE Finger tree contains only one Node (and no affix).

    // Any Node in the affix and any Single at level 0 (the highest level) are
    // DATA_TYPE.

    // Any Node in the affix and any Single at level n (the deeper level, the
    // greater n) are NODE_TYPE^n(DATA_TYPE).

    // A DEEP_TYPE Finger tree contains affixes and a deeper Finger tree.

    // The affixes are arrays of size four (i.e. contains 4 Node, even if
    // unused)

    // ====== Checked invariants ======
    // ===affix Invariants===
    // - In a prefix containing n elements, these elements correspond to the n
    //   leftmost indexes of the array.
    // - In a suffix containing n elements, these elements correspond to the n
    //   rightmost indexes of the array.
    // - The affixes contain at least one elem each (i.e. at least 1 Node contains
    //   effective data) and at most four elem each.
    
    // ===size Invariants===
    // - The size of a DATA_TYPE node should be 1.
    // - The size of a NODE_TYPE node should be the number of DATA_NODE it contains
    // - The size of an affix should be the sum of the size of its nodes
    // - The size of a finger tree should be the sum of its components.
    checkFingerTree(fgt);
}