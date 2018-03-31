/*
	Prashant Kumar Mahanta :	201601066
	Kaustubh Pandey	       :	201601041	 
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 4
int G=0,type;
//int GOAL[4][4] = {{1,2,3},{4,5,6},{7,8,0}};
int GOAL[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}};
//Linked list
//Node
typedef struct node
{
	int M[5][5];
	int h;
	int g;
	struct node *next;
}NODE;
void print(NODE *node){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			printf("%d  ",node->M[i][j]);
		}
		printf("\n");
	}
}
void printList(NODE* head){
	NODE *p;
	p = head;
	while(p!= NULL){
		print(p);
		printf("Heu value %d ----\n",p->h);
		p = p->next;
	}
}

//Heuristic value w.r.t goal, 2nd Heristic
//Heuristic sum of distance
int heuristic2(NODE *node){
	int h=0;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(node->M[i][j]!=0){
				for(int k=0;k<N;k++){
					for(int l=0;l<N;l++){
						if(node->M[i][j]==GOAL[k][l]){
							h+=(((i-k)>=0)?i-k:k-i)+(((j-l)>=0)?j-l:l-j);
						}
					}
				}
			}
		}
	}
	return h;
}
//First heuristic of our problem:
int heuristic1(NODE *node){
	int h=0;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(node->M[i][j]!=GOAL[i][j]) {h++;}
		}
	}
	return h;
}

//Create node
//m represents the parent matrix
NODE* createNode(char dir,int m[][5]){
	NODE* node=(NODE *)malloc(sizeof(NODE));
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			node->M[i][j]=0;
		}
	}
	int x,y;
	for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				node->M[i][j]=m[i][j];
				if(m[i][j]==0){
					x=i;
					y=j;
				}
			}
		}
	int temp;
	if(dir=='u' && x-1>=0){
		temp=node->M[x][y];
		node->M[x][y]=node->M[x-1][y];		//move empty square up,down,left,right
		node->M[x-1][y]=temp;
	}
	else if(dir=='d' && x+1<N){
		temp=node->M[x][y];
		node->M[x][y]=node->M[x+1][y];
		node->M[x+1][y]=temp;
	}
	else if(dir=='l' && y-1>=0){
		temp=node->M[x][y];
		node->M[x][y]=node->M[x][y-1];
		node->M[x][y-1]=temp;
	}
	else if(dir=='r' && y+1<N){
		temp=node->M[x][y];
		node->M[x][y]=node->M[x][y+1];
		node->M[x][y+1]=temp;
	}
	else if(dir!='o'){
		return NULL;	//Enter o for not moving the blank square
	}
	if(type == 1 )
		node->h = heuristic1(node);
	else
		node->h=heuristic2(node);	//Heuristic store
	node->g=0; //Unitialized
	node->next=NULL;
	return node;
}

void insertNode(NODE *before,NODE *after,NODE *curr){
		before->next=curr;
		curr->next=after;
}
//delete node
NODE* deleteNode(NODE *head,NODE *before,NODE *after,NODE *curr){
		if(curr==head){
			free(curr);
			return head->next;
		}
		else{
			before->next=after;
			free(curr);
			return head;
		}
	
} 
//Check if two nodes are same
// Heuristic value must match, checked first
int checkSame(NODE *first,NODE *second){
	if(first->h==second->h){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				if(first->M[i][j]!=second->M[i][j]){return 0;}
			}
		}
		return 1;
	}
	return 0;
}



/*******************************************************************************************************/
//PRASHANT

//return 0 if state of both nodes if difference else 1
int state(NODE *p,NODE *nw)
{	
	int i,j;
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{

			if((p->M[i][j]) != (nw->M[i][j]))
			{
				
			 return 0;
			}
		}
		//printf("\n");	
	}
	//printf("-ddddddddddddddddddddddddddddddddd-\n\n");

	return 1;
}
// add a new node to Open in sorted order
NODE* addToOpen(NODE *open,NODE *new)
{
	
	if(open == NULL) return new;
	else if(open->next == NULL){
		if((open->h+open->g) >= (new->h+new->g)){
			new->next = open;

			return new;
		}
		else{
			open->next = new;
			new->next = NULL;
			return open;
		}

	}
	else{
		NODE *temp,*pre;
		temp = open;
		int flag=0;
		if((temp->h+temp->g) >= (new->h+new->g)){
			new->next = temp;
			return new;
		}
		while(temp->next!=NULL){
			if((temp->h+temp->g) >= (new->h+new->g)){
				new->next = pre->next;
				pre->next = new;
				flag=1;
				break;
			}
			pre = temp;
			temp=temp->next;
		}
		if(flag==0){
			temp->next = new;
			new->next = NULL;
			return open;
		}
		return open;
	}

}
//If a particular state is present in open or closed set or not
int check_same(NODE *head, NODE *nw)
{

	NODE *p=NULL;
	p = head;
	if(head==NULL) return 0;
	while(p->next!=NULL)
	{
		
		if(state(p,nw)==1)
		{
						return 1;// present
		}
		p = p->next;
	}
	/*printf("------------nw p------------\n");
	print(nw);print(p);
	printf("Enter checksame\n");*/
	return 0;// not present

}
void check_value_HeuforClose(NODE *head,NODE *open, NODE *nw,NODE* a[])
{

	NODE *p,*q;
	p = head;
	q=p;
	while(p!=NULL)
	{
		if(state(p,nw)==1)
		{
			if(((p->h)+(p->g)) > ((nw->h)+(nw->g)))
			{
				// delete function : Kaustubh (delete p) q previous state
				// add new to open 
				//printf("---------------delete----------------\n");
				//print(head);
				head=deleteNode(head,q,p->next,p);
				//printf("--------------delete complete------------\n");
				//print(head);
				open = addToOpen(open,nw);// new node added to open
				a[0]=head;a[1]=open;
			}
			//return open;
		}
		q = p;
		p = p->next;
	}
	//return 0;

}
// Delete the node from linked list if already present node's
// Heuristic value is greater than new node and add new node to OPEN
NODE* check_value_Heu(NODE *head, NODE *nw)
{
	NODE *p,*q;
	p = head;
	q = p;
	while(p!=NULL)
	{
		if(state(p,nw)==1)
		{	
			if(((p->h)+(p->g)) > ((nw->h)+(nw->g)))
			{
				// delete function : Kaustubh (delete p) q previous state
				// add new to open 
				head=deleteNode(head,q,p->next,p);

				head = addToOpen(head,nw);// new node added to open
			}
			
			return head;
		}
		q = p;
		p = p->next;
		
	}
	//return 0;

}
// Step 5, new is each child of n
void Expand(NODE *open,NODE *close,NODE *new, NODE *b[])
{	
	//printf("Inside expand\n");

	int op = check_same(open,new);
	int col = check_same(close,new),kk;
	//print(new);
	//NODE *b[2];
	//if no same element in close and open add directly to open

	//printf("Close %d Open %d\n",col,op);
	if(op == 0 && col==0)	
	{
		//printList(new);
		//printList(open);
		open = addToOpen(open,new);
		//printList(open);
		//printf("added\n");
		
	}
	//if no same element in close add directly to open
	else if(op==1 && col==0)
	{
		 open = check_value_Heu(open,new);
	}
	//If there are elements in close set, check present state present in close or not
	else if(op==0 && col==1)
	{
		NODE *a[2];
		  check_value_HeuforClose(close,open,new,a);
		  open = a[1]; close = a[0];
	}
	b[0] = close; b[1] = open;
	//return open;
	//printf("Expand complete\n");
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//If GOAL achieved
int isGoal(NODE *node){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(node->M[i][j]!=GOAL[i][j]){return 0;}
		}
	}
	return 1;
}

//
int count_leftOver(NODE *head){
	int c=0;
	while(head!=NULL){
		c++;
		head = head->next;
	}
	return c;
}
int Astar(int START[][5]){
	NODE *OHead=NULL;
	NODE *CHead=NULL;
	NODE *minNode=NULL;
	NODE *curr=createNode('o',START);
	OHead=curr;
	 G=0;
	OHead->g=0;
	NODE *b[2];
	b[0] = CHead; b[1] = OHead;
	while(OHead!=NULL){
		//Find min cost node
		minNode=OHead;
		OHead=OHead->next;
		minNode->next = NULL;
		//If GOAL is achieved
		if(isGoal(minNode)){
			printf("Solved\n");
			print(minNode);
			int cout=0;
		cout+=count_leftOver(OHead);
		cout+=count_leftOver(CHead);
		printf("Number of Nodes left in memory %d\n\n",cout);
		return 1;
		}

		//Goal unreached
		//Expand for child
		G++;
		//printf("G : %d\n",G );
		NODE *up=createNode('u',minNode->M);
		NODE *down=createNode('d',minNode->M);
		NODE *left=createNode('l',minNode->M);
		NODE *right=createNode('r',minNode->M);
		if(up!=NULL){up->g=G;}
		if(down!=NULL){down->g=G;}
		if(left!=NULL){left->g=G;}
		if(right!=NULL){right->g=G;}
		//print(up);print(down);print(right);
		//Repeat for every node
		
		//For up
		if(up!=NULL){
		Expand(OHead,CHead,up,b);
		OHead = b[1];CHead = b[0];
		}
		//For down
		//printList(OHead);
		//printf("--------------------------------up----------\n");
		//printList(up);
		if(down!=NULL){
		Expand(OHead,CHead,down,b);
		OHead = b[1];CHead = b[0];
		}
		//For left
		
		//print(left);
		//printf("left %d\n",left->h);
		if(left!=NULL){
			//printf("Enetr\n\n");
		Expand(OHead,CHead,left,b);
		OHead = b[1];CHead = b[0];
		}
		//printf("left complete\n");
		
		//For right
		if(right!=NULL){
		Expand(OHead,CHead,right,b);
		OHead = b[1];CHead = b[0];
		}
		
		// add to close
		if(CHead==NULL){CHead=minNode;}
		else{
			NODE *z=CHead;
			while(z->next!=NULL){z=z->next;}
			z->next=minNode;
		}

		/*print(OHead);
		if(CHead == NULL) printf("ITs NULL\n");
		else print(CHead);*/
		//printf("first time over\n");
		printf("----------------ohead after expand complete-----------\n");
		printList(OHead);
		printf("-----------------------------chead after expand complete-----------\n");
		printList(CHead);
	}
	printf("Can't be solved\n");
	return -1;//NO SOLUTION
}


//MAIN
int main(){
	int START[5][5];

	printf("Enter the initial state of puzzle\n");
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			scanf("%d",&START[i][j]);
		}
	}
	printf("Enter which Heuristic to use: \n1.No of Misplaced tiles\n2. Sum of “number of moves each tile is away from its goal position\n\n");
	scanf("%d",&type);
	Astar(START);
	printf("Level Reached i.e., g(x) : %d\n",G);
	return 0;
}
