#include <stdio.h>
#include "bst.h"
#include <stdlib.h>
#include "general.h"
#define MAX 50

struct Node{
  int data;
   Bst left;
   Bst right;
};

Bst new_bst(){
   Bst _head = 0;
   return _head;
}
void delete_bst(Bst bst){
  if(bst == 0)return;
  delete_bst(bst->left);
  delete_bst(bst->right);
  sfree(bst);
}

int get_depth(Bst bst){
  if(bst == 0)return 0;
  int depth = get_depth(bst->left)+1;
  int r = get_depth(bst->right)+1;
  return r>depth ? r:depth;
}

void add(Bst* bst, int value){
  Bst &temp = *bst;
  if(temp == 0){
    temp = (Bst)malloc(sizeof(struct Node)); temp->data = value;
    temp->left =0;
    temp->right =0;
  }
  else if(value <= temp->data){
    if(temp->left== 0){
      Bst newBst = (Bst)malloc(sizeof(struct Node));
      temp->left= newBst;
      newBst->data = value;
      newBst->left = 0;
      newBst->right= 0;
    }
    else{
      add(&temp->left, value);
    }
  }
  else{
    if(temp->right ==0){
      Bst newBst = (Bst)malloc(sizeof(struct Node));
      temp->right = newBst;
      newBst->data = value;
      newBst->left = 0;
      newBst ->right= 0;
    }
    else{
      add(&temp->right,value);
    }
  }
}

int root_value(Bst bst){
  return bst==0?0:bst->data;
}

Bst left_subtree(Bst root){
  return root == 0?0:root->left;
}

Bst right_subtree(Bst root){
  return root == 0?0:root->right;
}

int traverse_pre_order(Bst bst, int *elements, int start){
    if(bst == 0)return 0;
    int count = 0;
    elements[start] = bst->data;
    count += traverse_pre_order(bst->left, elements, start+1);
    count+= traverse_pre_order(bst->right, elements, start+count+1);
    return count+1;
}

int traverse_in_order(Bst bst, int *elements, int start){
    if(bst == 0)return 0;
    int count = 0;
    count += traverse_in_order(bst->left, elements, start);
    elements[start+count] = bst->data;
    count+= traverse_in_order(bst->right, elements, start+count+1);
    return count+1;
}

int traverse_post_order(Bst bst, int *elements, int start){
    if(bst == 0)return 0;
    int count = 0;
    count += traverse_post_order(bst->left, elements, start);
    count += traverse_post_order(bst->right, elements, start+count);
    elements[start+count] = bst->data;
    return count+1;
}

bool are_equal(Bst bst1, Bst bst2){
  if(bst1 == bst2)return true;
  if(bst1 != 0 && bst2 != 0){
    int arr1[MAX];
    int length = traverse_pre_order(bst1, arr1, 0);
    int arr2[MAX];
    int length2 = traverse_pre_order(bst2, arr2, 0);
    if(length == length2){
      bool x = true;
      for (int i = 0; i < length; i++) {
        if(arr1[i]!= arr2[i])x = false;
      }
      return x;
    }
  }
  return false;
}

void most_left_longest_branch(Bst bst, Bst* branch){
    if(bst == 0)return;
    add(branch, bst->data);
    get_depth(bst->left) >= get_depth(bst->right) ? most_left_longest_branch(bst->left, branch):most_left_longest_branch(bst->right, branch);
}

int get_number_of_subtrees(Bst bst){
    if(bst == 0)return -1;
return get_number_of_subtrees(bst->left) +1+ get_number_of_subtrees(bst->right)+1;
}
