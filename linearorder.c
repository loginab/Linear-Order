/* ABHAY GUPTA */
#include<stdio.h>
#include<stdlib.h>
typedef struct order {

int key ; 
order *left ;
order *right;
order *parent;
int  visited;
int height;
}o_t;

order *gp[300010];

int height_node(o_t *t)
{
	if(t->right ==NULL)
		return t->left->height +1;
	if (t->left->height > t->right->height)
		return t->left->height+1;
	else
		return t->right->height+1;

}

void left_rotate(o_t *x)
{

	o_t *alpha=NULL ,*beta=NULL,*gamma=NULL,*temp;
	alpha=x->left;
	if (x->right !=NULL)
		beta=x->right->left;
	
	if(x->right !=NULL)
		gamma=x->right->right;
	
	temp=alpha;
	x->left=x->right;
	x->right=gamma;
	if (gamma !=NULL)
		gamma->parent=x;
	x->left->right=beta;
	if (beta !=NULL)
		beta->parent=x->left;
	x->left->left=temp;
	if (temp !=NULL)
	temp->parent=x->left;
	x->left->height=height_node(x->left);
	x->height=height_node(x);
	
}

void right_rotate(o_t *y)
{
	
	o_t *alpha=NULL ,*beta=NULL,*gamma=NULL,*temp,*x;
	x=y->left;
	if (x !=NULL)
	{
		alpha=x->left;
		beta=x->right;
	}
	gamma=y->right;
	temp=alpha;
	y->right=y->left;
	y->left=alpha;
	if (alpha !=NULL)
		alpha->parent =y;
	x->left=beta;
	if(beta !=NULL)
		beta->parent=y->right;
	x->right=gamma;
	if(gamma !=NULL)
		gamma->parent=y->right;
	y->right->height=height_node(y->right);
	y->height=height_node(y);
}

void balancing_cases(o_t *t)
{

	if (abs(t->left->height)>abs(t->right->height))
	{
		if ( t->left->left->height > t->left->right->height)
		{	
			right_rotate(t);
		
		}
		else if ( t->left->left->height < t->left->right->height)
		{
			left_rotate(t->left);
			right_rotate(t);
		}
	}
	else
	{
		if (t->right->right->height > t->right->left->height)
		{	
			left_rotate(t);
		}
		else if (t->right->right->height < t->right->left->height)
		{
			right_rotate(t->right);
			left_rotate(t);
		}
	}
}



int balance(o_t *t)
{
if (abs(t->left->height-t->right->height)>1)
	return 0;
else
	return 1;
}

o_t* get_node()
{
	o_t *temp=(order *)malloc(sizeof(order));
	temp->key=-90;
	temp->visited=0;
	temp->right=NULL;
	temp->left=NULL;
	temp->height=0;
return temp;
}

o_t* create_order()
{
	o_t *temp=get_node();
	temp->key=-1;
	return temp;
}

void inorder(o_t *t)
{
	if (t!=NULL)
	{	
		inorder(t->left);
		if (t->key !=-90)
			printf ("\n %d , %d",t->key,t->height);
		inorder(t->right);

	}

}

void height_update(o_t *t)
{
	while (t !=NULL)
	{	
		t->height=height_node(t);
		if(balance(t)==0)
			balancing_cases(t);	
		t=t->parent;			
	}

}
void insert_top (o_t *n,key_t a)
{	
	o_t *t,*temp,*temp1;
	t=n;
	if (t-> left ==NULL && t->right==NULL )
	{
		t->key=-90;
		t->left=get_node();
		t->left->key=a;
		gp[a]=t->left;
		t->left->parent=t;
		t->height=0;
	}
	else if (t->left!=NULL && t->right ==NULL)
	{
		temp=get_node();
		temp1=get_node();
		temp1->left=t->left;
		temp1->left->parent=temp1;
		temp->left=get_node();
		temp->left->parent=temp;
		temp->left->key=a;
		gp[a]=temp->left;
		t->right=temp;
		t->left=temp1;
		temp->parent=t;temp1->parent=t;
		height_update(temp1->parent);

	}
	else
	{
		while( t->key==-90 && t->right !=NULL)
		{
			t=t->right;

		}
	
		temp=get_node();
		temp1=get_node();
		temp1->left=t->left;
		temp1->left->parent=temp1;
		temp->left=get_node();
		temp->left->key=a;
		temp->left->parent=temp;
		gp[a]=temp->left;
		t->right=temp;
		t->left=temp1;
		temp->parent=t;temp1->parent=t;
		height_update(temp->parent);
	}

}


void insert_bottom (o_t *n,key_t a)
{	
	o_t *t,*temp,*temp1;
	t=n;
	if (t-> left ==NULL && t->right==NULL )
	{
		t->key=-90;
		t->left=get_node();
		t->left->key=a;
		gp[a]=t->left;
		t->left->parent=t;
		t->height=0;
	}
	else if (t->left!=NULL && t->right ==NULL)
	{
		temp=get_node();
		temp1=get_node();
		temp1->left=t->left;
		temp1->left->parent=temp1;
		temp->left=get_node();
		temp->left->key=a;
		temp->left->parent=temp;
		gp[a]=temp->left;
		t->left=temp;
		t->right=temp1;
		temp->parent=t;temp1->parent=t;
		height_update(temp->parent);
	}
	else
	{
		while(t->right !=NULL && t->key==-90)
		{
			t=t->left;

		}
		temp=get_node();
		temp1=get_node();
		temp1->left=t->left;
		temp1->left->parent=temp1;
		temp->left=get_node();
		temp->left->parent=temp;
		temp->left->key=a;
		gp[a]=temp->left;
		t->left=temp;
		t->right=temp1;
		temp->parent=t;
		temp1->parent=t;
		height_update(t);
	}

}

void insert_before(o_t *ord , key_t b, key_t a)
{

		o_t *temp,*temp1,*t;
		t=gp[a]->parent;
		temp=get_node();
		temp1=get_node();
		temp1->left=t->left;
		temp1->left->parent=temp1;
		temp->left=get_node();
		temp->left->key=b;
		temp->left->parent=temp;
		gp[b]=temp->left;
		t->left=temp;
		t->right=temp1;
		temp->parent=temp1->parent=t;
		height_update(temp->parent);

}

void insert_after(o_t *ord , key_t b, key_t a)
{
		o_t *temp,*temp1,*t;
		t=gp[a]->parent;
		temp=get_node();
		temp1=get_node();
		temp1->left=t->left;
		temp1->left->parent=temp1;
		temp->left=get_node();
		temp->left->key=b;
		temp->left->parent=temp;
		gp[b]=temp->left;
		t->right=temp;
		t->left=temp1;
		temp->parent=temp1->parent=t;
		height_update(temp->parent);
}


void delete_o(o_t *t,key_t a)
{
	o_t *other,*temp,*p;
	
	p=gp[a]->parent->parent;
	if (p==NULL)
	{	p=gp[a]->parent;
		temp=p->left;
		p->left=NULL;
		p->right=NULL;
		p->key=-2;
		p->height=0;
		free(temp); 
		return;
	}
	if (gp[a]->parent==gp[a]->parent->parent->left)
		other=p->right;
	else
		other=p->left;
	
	p->key=other->key;

	p->left=other->left;
	p->right=other->right;
	if (other->left !=NULL)
	other->left->parent=p;
	if (other->right !=NULL)
	other->right->parent =p;
	p->height=0;
	height_update(p->parent);
	free(gp[a]);
	free(other);

}

int is_before(o_t *t1,key_t a, key_t b)
{
	o_t *first, *second,* t, *child;
	int value=0;
	first=gp[a];
	second=gp[b];
	child=gp[b];
	t=first->parent ;
	do
	{

		t->visited=1;
		t=t->parent;
	}while (t !=NULL);

	t=second->parent;
	do 
	{
		if (t->visited==1)
		{
			if (t->right==child)
				value=1;
			else
				value=0;

			break;
		}
		
		child=t;	
		t=t->parent;
	}while(t !=NULL);

	t=first->parent;
	do
	{
		t->visited=0;
		t=t->parent;

	}while (t !=NULL);
return value;
}

long p(long q)
{ return( (1247*q +104729) % 300007 );
}

int main()
{  long i; o_t *o; 
   printf("starting \n");
   o = create_order();
   for(i=100000; i>=0; i-- )
      insert_bottom( o, p(i) );
   for(i=100001; i< 300007; i+=2 )
   {  insert_after(o, p(i+1), p(i-1) );
      insert_before( o, p(i), p(i+1) );
   }
   printf("inserted 300000 elements. ");
   for(i = 250000; i < 300007; i++ )
      delete_o( o, p(i) );
   printf("deleted 50000 elements. ");
   insert_top( o, p(300006) );
   for(i = 250000; i < 300006; i++ )
      insert_before( o, p(i) , p(300006) );
   printf("reinserted. now testing order\n");
   for( i=0; i < 299000; i +=42 )
   {  if( is_before( o, p(i), p(i+23) ) != 1 )
      {  printf(" found error (1) %d,%d,%d,%d\n",i,i+23,p(i),p(23)); exit(0);
      }
   }
   for( i=300006; i >57; i -=119 )
   {  if( is_before( o, p(i), p(i-57) ) != 0)
      {  printf(" found error (0) \n"); exit(0);
      }
   }
   printf("finished. no problem found.\n");
}
