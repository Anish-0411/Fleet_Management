#include <stdio.h>
#include <stdlib.h>
struct node{
    int value;
    struct node *next;
};
struct node* createNode(int k){
    struct node *p;
    p=(struct node*)malloc(sizeof(struct node));
    p->value=k;
    p->next=NULL;
    return p;
}
void display(struct node *ht[], int n){
    for(int i=0;i<n;i++){
        printf("%d: ",i);
        struct node *temp=ht[i];
        while(temp){
            printf("%d ",temp->value);
            if(temp->next)
                printf("->");
            temp=temp->next;
        }
        printf("\n");
    }
}
int main() {
    int n;
    int size,key;
    printf("Enter hashtable size: ");
    scanf("%d",&size);
    printf("Enter number of keys: ");
    scanf("%d",&n);
    struct node *HT[size];
    for(int i=0;i<size;i++){
        HT[i]=NULL;
    }
    printf("Enter keys: ");
    for(int i=0;i<n;i++){
        scanf("%d",&key);
        if(HT[key%size]==NULL){
            HT[key%size]=createNode(key);
        }
        else{
            struct node *temp=HT[key%size];
            while(temp->next){
                temp=temp->next;
            }
            temp->next=createNode(key);
        }
    }
    display(HT,size);
    return 0;
}