#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

    TreeMap * new = (TreeMap *) malloc(sizeof(TreeMap));
    new->lower_than = lower_than;
    new->root = NULL;

    new->current = NULL;
    return new;
}


void insertTreeMap(TreeMap *tree, void* key, void * value) {

    TreeNode *new = createTreeNode(key, value);

    if (tree->root == NULL)
        tree->root = new;
        
    else {

        TreeNode *aux = tree->root;
        
        while (1) {

            if (tree->lower_than(key, aux->pair->key)) {

                if (aux->left == NULL) {
                    
                    aux->left = new;
                    break;
                    
                } else {
                    aux = aux->left;
                }
                    
                
            } else if (is_equal(tree, key, aux->pair->key)) {
                return;
                
            } else {

                if (aux->right == NULL) {

                    aux->right = new;
                    break;
                    
                } else {
                    aux = aux->right;
                }
            }
        }

        new->parent = aux;
        tree->current = new;

    }
}

TreeNode * minimum(TreeNode * x){

    TreeNode *temp = x;

    while (temp->left != NULL) {

        temp = temp->left;
        
    }

    return temp;
}


void removeNode(TreeMap * tree, TreeNode* node) {

    TreeNode *temp = tree->root;
    TreeNode *parent = NULL;

    // Find the node to be removed and its parent
    while (temp != NULL && temp != node) {
        parent = temp;
        if (tree->lower_than(node->pair->key, temp->pair->key)) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }

    // If the node was not found, return
    if (temp == NULL)
        return;

    // If the node to be removed has no children
    if (temp->left == NULL && temp->right == NULL) {
        // Check if the node is the root
        if (parent != NULL) {
            // If not root, update the parent's pointer
            if (parent->left == node)
                parent->left = NULL;
            else
                parent->right = NULL;
        } else {
            // If root, just set the root to NULL
            tree->root = NULL;
        }
        // Free the memory allocated for the node
        free(node);
    }

    /*
    else if (temp->left == NULL || temp->right == NULL) { // Caso 1 Hijo

        TreeNode *child;

        if (temp->left != NULL)
            child = temp->left;
        else
            child = temp->right;
        
        if (temp != tree->root) {

            if (parent->left == temp)
                parent->left = child;
            else
                parent->right = child;
        } else {
            tree->root = child;
        }
    }

    else { // Caso 2 Hijos

        TreeNode *heir = minimum(temp->right);

        void* hKey = heir->pair->key;
        void* hData = heir->pair->value;

        removeNode(tree, heir);
        temp->pair->key = hKey;
        temp->pair->value = hData;
    
    }

    */
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
