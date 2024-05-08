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
    if (node == NULL) return;

    if (node->left == NULL && node->right == NULL) { // Case: Node has no children
        if (node->parent != NULL) {
            if (node == node->parent->left)
                node->parent->left = NULL;
            else
                node->parent->right = NULL;
        } else {
            tree->root = NULL;
        }
        free(node);
    } else if (node->left == NULL || node->right == NULL) { // Case: Node has one child
        TreeNode *child = (node->left != NULL) ? node->left : node->right;
        if (node->parent != NULL) {
            if (node == node->parent->left)
                node->parent->left = child;
            else
                node->parent->right = child;
        } else {
            tree->root = child;
        }
        child->parent = node->parent;
        free(node);
    } else { // Case: Node has two children
        TreeNode *successor = minimum(node->right); // Find the minimum node in the right subtree

        // Swap the key and value with the successor node
        void* temp_key = node->pair->key;
        void* temp_value = node->pair->value;
        node->pair->key = successor->pair->key;
        node->pair->value = successor->pair->value;
        successor->pair->key = temp_key;
        successor->pair->value = temp_value;

        // Remove the successor node (recursive call)
        removeNode(tree, successor);
    }
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
