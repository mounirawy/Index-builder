#ifndef BSTFCI_H_INCLUDED
#define BSTFCI_H_INCLUDED
#include <iostream>
#include <algorithm>
#include <queue>
#include <math.h>
#include <cmath>
#include <vector>

using namespace std;

template <class T>
class BSTFCI{
public:
    class BSTNode{
   public:
     T data;
     BSTNode *left;
     BSTNode *right;
     vector<int> v;
     };

public:
    BSTNode *root=NULL;
public:
BSTFCI(){};
BSTFCI(BSTNode *r){root = r;}

BSTNode *getnewnode(T data){
BSTNode *newnode = new BSTNode;
newnode->data = data;
newnode->left = NULL;
newnode->right = NULL;
     return newnode;
}

void toinsert(BSTNode **r,T data){
if(*r==NULL){
(*r) = getnewnode(data);
}
else if(data<(*r)->data){
    toinsert(&((*r)->left),data);
}
else{
    toinsert(&((*r)->right),data);
}
}

void insert(T data){
toinsert(&root,data);
}

bool tosearch(BSTNode *r,T data){
if(r==NULL)
    return false;
else if(r->data == data)
    return true;
else if(data <r->data)
    return tosearch(r->left,data);
else
    return tosearch(r->right,data);
}
bool search(T data){
return tosearch(root,data);
}
int tofindmin(BSTNode *r){
if(r==NULL){
    cout<<"there's no any value in the tree"<<endl;
    return -1;
}
BSTNode *temproot = r;
while(temproot->left!=NULL){
    temproot = temproot->left;
}
return temproot->data;
}
int findmin(){
return tofindmin(root);
}

int tofindmax(BSTNode *r){
if(r==NULL){
    cout<<"there's no any value in the tree"<<endl;
    return -1;
}
BSTNode *temproot = r;
while(temproot->right!=NULL){
    temproot = temproot->right;
}
return temproot->data;
}
int findmax(){
return tofindmax(root);
}

int tofindhight(BSTNode *r){
if(r==NULL)
    return -1;
int lefthight = tofindhight(r->left);
int righthight = tofindhight(r->right);

return max(lefthight,righthight) +1;
}

int findheight(){
return tofindhight(root);
}

void tolevelordertraversal(BSTNode *r){
   if(root==NULL)
    return;
   queue<BSTNode *> q;
   q.push(r);
   while(!q.empty()){
    BSTNode *cur = q.front();
    cout<<cur->data<<"  ";
    if(cur->left!=NULL) q.push(cur->left);
    if(cur->right!=NULL) q.push(cur->right);
    q.pop();
   }
}
void levelordertraversal(){
 tolevelordertraversal(root);
}
void topreordertraversal(BSTNode *r){
if(r==NULL)
    return;
cout<<r->data<<"  ";
topreordertraversal(r->left);
topreordertraversal(r->right);
}
void preordertraversal(){
topreordertraversal(root);
}

BSTNode* tofindminreturnaddress(BSTNode *r){
if(r==NULL){
    cout<<"there's no any value in the tree"<<endl;
    return NULL;
}
BSTNode *temproot = r;
while(temproot->left!=NULL){
    temproot = temproot->left;
}
return temproot;
}

BSTNode *todelete(BSTNode *r,T data){
if(r==NULL)
    return NULL;
else if(data < r->data)
    r->left = todelete(r->left,data);
else if(data > r->data)
    r->right = todelete(r->right,data);
else{
    if(r->left==NULL &&r->right==NULL){
        delete r;
        r = NULL; //because r is still has this address
        return r;
    }
    else if(r->left==NULL){
        BSTNode *temp = r;
        r = r->right;
        delete temp;
    }
    else if(r->right==NULL){
        BSTNode *temp = r;
        r = r->left;
        delete temp;
    }
    else{
        BSTNode *temp = tofindminreturnaddress(r->right);
        r->data = temp->data;
        r->right = todelete(r->right,data);
    }

}
}
void Delete(T data){
todelete(root,data);
}

bool toisbalance(BSTNode *r){
  int leftsideheight,rightsidehight;
  if(r==NULL){
    return 1;
  }
  leftsideheight = tofindhight(r->left);
  rightsidehight = tofindhight(r->right);
  if(abs(leftsideheight-rightsidehight)&&toisbalance(r->left)&&toisbalance(r->right)){
    return 1;
  }
  return 0;
}
bool isbalance(){
return toisbalance(root);
}

 bool sametree(BSTNode *t1,BSTNode*t2){
if(t1==NULL && t2==NULL){
    return true;
}
if(t1==NULL ||t2==NULL){
    return false;
}
return (t1->data == t2->data && sametree(t1->left,t2->left) && sametree(t1->right,t2->right));
}
 bool toissubtree(BSTNode *bigroot,BSTNode *smallroot){
if(smallroot == NULL)
    return true;
if(bigroot == NULL){
    return false;
}
if(sametree(bigroot,smallroot)){
    return true;
}
return (toissubtree(bigroot->left,smallroot) ||toissubtree(bigroot->right,smallroot));
}

bool issubtree(BSTFCI bigtree,BSTFCI subtree){

return toissubtree(bigtree.root,subtree.root);
}

void toprintinrange(BSTNode *r,int mini,int maxi){
if(r==NULL)
    return;

if(r->data > mini)
    toprintinrange(r->left,mini,maxi);
if(r->data >= mini && r->data <= maxi)
   cout<<r->data<<"   ";
if(r->data < maxi)
    toprintinrange(r->right,mini,maxi);
}

void printinrange(int mini,int maxi){
toprintinrange(root,mini,maxi);
}
//for return by address 2-4
BSTNode *tosearchandreturnaddress(BSTNode *r,T data){
if(r==NULL)
    return NULL;
else if(r->data == data)
    return r;
else if(data <r->data)
    return tosearchandreturnaddress(r->left,data);
else
    return tosearchandreturnaddress(r->right,data);
}
/////
BSTNode* toinsertreturnaddress(BSTNode **r,T data){
if(*r==NULL){
(*r) = getnewnode(data);
return *r;
}
else if(data<(*r)->data){
    return toinsertreturnaddress(&((*r)->left),data);
}
else{
    return toinsertreturnaddress(&((*r)->right),data);
}
}
//////////
void indexbuilder(char *lines){
int linecounter = 1;
int generalcounter=0;
int onewordcounter=-1;
while(lines[generalcounter]!='\0'){
    if(lines[generalcounter]=='\n'){
         linecounter++;
        if(lines[generalcounter-1] == ' ' ||lines[generalcounter-1]==','||lines[generalcounter-1]=='.'){
        onewordcounter++;}
        generalcounter++;
        continue;
    }
    if(lines[generalcounter] == ' ' ||lines[generalcounter]==','||lines[generalcounter]=='.'){
                string tempword;
        for(int i=onewordcounter+1;i<generalcounter;i++){
            tempword.push_back(lines[i]);
        }
       BSTNode *temp = tosearchandreturnaddress(root,tempword);
       if(temp==NULL){
        temp = toinsertreturnaddress(&root,tempword);
        //cout<<temp<<endl;
         temp->v.push_back(linecounter);
       }
       else{
           temp->v.push_back(linecounter);
       }
       //here
       onewordcounter=generalcounter;
}
generalcounter++;
}
string tempword;
for(int i=onewordcounter+1;i<generalcounter;i++){
            tempword.push_back(lines[i]);}

      BSTNode *temp = tosearchandreturnaddress(root,tempword);
       if(temp==NULL){
        temp = toinsertreturnaddress(&root,tempword);
        //cout<<temp<<endl;
         temp->v.push_back(linecounter);
       }
       else{
           temp->v.push_back(linecounter);
       }
}

void toinordertraversal(BSTNode *r){
if(r==NULL)
    return;
toinordertraversal(r->left);
cout<<r->data<<":  ";
int s = r->v.size();
for(int i=0;i<s;i++)
    cout<<r->v[i]<<"  ";
cout<<endl;
toinordertraversal(r->right);
}

};



#endif // BSTFCI_H_INCLUDED
