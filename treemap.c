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

    TreeNode* temp = tree->root;
    TreeNode* parent = NULL;

    while (temp->pair->key != NULL && temp->pair->key != node->pair->key) {

        if (tree->lower_than(node->pair->key, temp->pair->key)) {
            parent = temp;
            temp = temp->left;
        } else {
            parent = temp;
            temp = temp->right;
        }    
    }

    if (temp->left == NULL && temp->right == NULL) {

        if (parent->pair->key != tree->root->pair->key) {

            if (parent->left == temp) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        } else {
            tree->root = NULL;
        }
    }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {

    TreeNode *current = tree->root;

    while (current != NULL) {

        if (current->pair->key == key)
            break;
        else if (tree->lower_than(key, current->pair->key)) 
            current = current->left;
        else
            current = current->right;

    }
    return current->pair;
}


Pair * upperBound(TreeMap * tree, void* key) {

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

    while (parent != NULL && current == parent->right) {

        current = parent;
        parent = parent->parent;
        
    }

    tree->current = parent;

    if (parent != NULL)
        return parent->pair;

    return NULL;
}
