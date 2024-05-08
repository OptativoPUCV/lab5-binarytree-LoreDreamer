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

    while (temp->left != NULL) 

        temp = temp->left;

    return temp;
}



void removeNode(TreeMap *tree, TreeNode *node) {

    TreeNode *current = tree->root;
    TreeNode *parent = NULL;

    while (current != NULL && !is_equal(tree, current->pair->key, node->pair->key)) {

        parent = current;

        if (tree->lower_than(node->pair->key, current->pair->key)) {
            current = current->left;
        } else {
            current = current->right;
        }

    }

    if (current == NULL) return;

    if (current->left == NULL && current->right == NULL) {
        
        if (parent == NULL) 
            tree->root = NULL;
        else if (parent->left == current) 
            parent->left = NULL;
        else 
            parent->right = NULL;
        
        free(current);
    }

    else if (current->left == NULL || current->right == NULL) {

        TreeNode *child;

        if (current->left != NULL) {
            child = current->left;
        } else {
            child = current->right;
        }

        if (current != tree->root) {

            if (current->left == current) {

                parent->left = child;
                child->parent = parent;
                
            } else {

                parent->right = child;
                child->parent = parent;
                
            }
        } else {
            tree->root = child;
        }
    }

    else {

        TreeNode *heir = minimum(current->right);
        void *hKey = heir->pair->key;
        void *hValue = heir->pair->value;

        removeNode(tree, heir);
        current->pair->key = hKey;
        current->pair->value = hValue;
        
    }
}

void eraseTreeMap(TreeMap * tree, void* key){
    
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    
    TreeNode* node = tree->current;
    removeNode(tree, node);
    
}

Pair *searchTreeMap(TreeMap *tree, void *key) {

    TreeNode *current = tree->root;

    while (current != NULL) {

        if (is_equal(tree, current->pair->key, key)) {
            
            tree->current = current;
            return current->pair;
            
        } else if (tree->lower_than(key, current->pair->key) == 1) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    return NULL;
}


Pair *upperBound(TreeMap *tree, void *key) {
    
    TreeNode *current = tree->root;
    TreeNode *upperBound = NULL;

    while (current != NULL) {
        
        if (tree->lower_than(current->pair->key, key)) {
            current = current->right;
            
        } else {
            
            upperBound = current;
            current = current->left;
            
        }
    }

    if (upperBound != NULL) 
        return upperBound->pair;

    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {

    TreeNode *temp = tree->root;
    TreeNode *min = minimum(temp->left);

    tree->current = min;

    return min->pair;
    
}

Pair * nextTreeMap(TreeMap * tree) {

    TreeNode *current = tree->current;

    if (current->right != NULL) {
        tree->current = minimum(current->right);
        return tree->current->pair;
    }

    TreeNode *parent = current->parent;

    while (parent != NULL) {

        current = parent;
        parent = parent->parent;
        
    }

    tree->current = parent;

    if (parent != NULL)
        return parent->pair;

    return NULL;
}
