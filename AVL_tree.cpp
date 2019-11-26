#include<bits/stdc++.h>

using namespace std;

class an
{
	public:
		int d;
		int h;
		int lc;
		int rc;

		an *left;
		an *right;

		an(int val)
		{
			left = NULL;
			right = NULL;

			h=1;
			d=val;

			lc=0;
			rc=0;
		}

};

int get_h(an *root)
{
	if(root == NULL) 
	{
		return 0;
	}	
	else
	{
		return root->h;
	}
}

an* l_rot(an *n)
{
	an *pare = n;

	an *child = pare->right;
	an *subtree = child->left;

	child->left = pare;
	pare->right = subtree;

	int hl = get_h(pare->left);
	int hr = get_h(pare->right);

	if( hl > hr )
	{
		pare->h = hl;
	}
	else
	{
		pare->h = hr;
	}
	pare->h += 1;

	hl = get_h(child->left);
	hr = get_h(child->right);

	if( hl > hr )
	{
		child->h = hl;
	}
	else
	{
		child->h = hr;
	}
	child->h += 1;

	if( subtree != NULL )
	{
		pare->rc = subtree->lc + subtree->rc + 1; 
	}
	else
	{
		pare->rc = 0;
	}

	child->lc = pare->rc + pare->lc + 1;
	return child;
}

an* r_rot(an *n)
{
	an *y = n;
	
	an *pare = y->left;
	an *subtree = pare->right;

	pare->right = y;
	y->left = subtree;

	int hl = get_h(y->left);
	int hr = get_h(y->right);

	if( hl > hr )
	{
		y->h = hl;
	}
	else
	{
		y->h = hr;
	}
	y->h += 1;

	hl = get_h(pare->left);
	hr = get_h(pare->right);

	if( hl > hr )
	{
		pare->h = hl;
	}
	else
	{
		pare->h = hr;
	}
	pare->h += 1;

	if( subtree == NULL )
	{
		y->lc = 0;
	}
	else
	{
		y->lc = subtree->lc + subtree->rc + 1;
	}
	pare->rc = y->lc + y->rc + 1;

	return pare;
}

an* ins( an* r ,int val)
{	
	if( r == NULL)
	{
		return ( new an(val) );
	}
	else if( val >= r->d )
	{
		r->right = ins(r->right ,val);
		r->rc += 1;
	}
	else
	{
		r->left = ins(r->left ,val);
		r->lc += 1;
	}

	int hl = get_h(r->left);
	int hr = get_h(r->right);

	if( hl > hr )
	{
		r->h = hl;
	}
	else
	{
		r->h = hr;
	}

	int bf;
	if( r == NULL )
	{
		bf = 0;
	}
	else
	{
		bf = get_h(r->left) - get_h(r->right);
	}
	
	if( (bf>1) )
	{
		if((val < (r->left->d)))
		{
			return r_rot(r);
		}
		else
		{
			r->left = l_rot(r->left);
			return r_rot(r);
		}
	}
	if( (bf<-1) )
	{
		if(val >= (r->right->d))
		{
			return l_rot(r);
		}
		else
		{
			r->right = r_rot(r->right);
			return l_rot(r);
		}
	}

	return r;
}

int suc(an *r)
{
	if( r->right == NULL )
	{
		return r->d;
	}
	else
	{
		r = r->right;
	}

	while( r->left != NULL )
	{
		r = r->left;
	}

	return r->d;
}

int pred(an *r)
{
	if( r->left == NULL)
	{
		return r->d;
	}
	else
	{
		r=r->left;
	}

	while(r->right != NULL)
	{
		r= r->right;
	}

	return r->d;
}

void inorder(an *root)
{ 
	if(root == NULL) 
	{
		return;
	}
	else
	{
		inorder(root->left);
		cout << root->d << " " ;
		inorder(root->right);
	}
}

void search(an *root ,int key)
{
	if( root == NULL )
	{
		cout<<"Not Availbale"<<endl;
		return ;
	}

	if( root->d == key)
	{
		cout<<"Availbale"<<endl;
		return;
	}

	if( key > root->d )
	{
		search(root->right ,key);
	}
	else if( key < root->d )
	{
		search(root->left ,key);
	}
}

int find_closest(an* root ,int key ,int &p ,int &q)
{
	int diff = INT_MAX;
	int val;

	an *trav = root ;

	int leftc = root->lc;
	int rightc = root->rc;

	while( trav != NULL )
	{
			
		int temp = abs( key - trav->d );
			
		if( diff > temp )
		{
			val = trav->d;

			p = leftc;
			q = rightc;

			diff = temp;
		}

		if( key == trav->d )
		{
			p = leftc;
			q = rightc;

			return val;
		}
		else if( key > trav->d )
		{
			trav = trav->right;

			if( trav != NULL )
			{
				rightc = rightc -1 - trav->lc;
		 		leftc = leftc + 1 + trav->lc;
			}
		}
		else 
		{
			trav = trav->left;

			if( trav != NULL )
			{
				leftc = leftc -1 -trav->rc;
				rightc = rightc + 1 + trav->rc;
			}
		}
	}

	return val;
}


void find_kth(an *root ,int k)
{
	an *trav = root;

	int leftc = root->lc;
	int rightc = root->rc;

	while(trav != NULL )
	{
		int rank = rightc + 1;

		if( rank == k )
		{
			cout<<trav->d<<endl;
			return;
		}
		else if( rank < k )
		{
			//go left 
			trav = trav->left;
			
			leftc = leftc -1 -trav->rc;
			rightc = rightc + 1 + trav->rc;
		}
		else
		{
			//go right
			trav = trav->right;

			rightc = rightc -1 - trav->lc;
		 	leftc = leftc + 1 + trav->lc;
		}
	}
}

int range_count(an *root ,int a ,int b ,int total )
{
	int l1,r1;
	int l2,r2;

	int p =find_closest(root ,a ,l1,r1);
	
	int q =find_closest(root ,b ,l2,r2);

	int temp;

	if( (p<a && q<b) || (p>a && q>b) )
	{
		temp = total -l1 -r2 -1;
	}	
	else if( p<a && q>b )
	{
		temp = total -l1 - r2 - 2;
	}
	else
	{
		temp = total - l1 - r2;
	}

	cout<<temp<<endl ;
}

int bal(an *root)
{
	if (root == NULL)  
	{
        return 0;  
	}
    return get_h(root->left) - get_h(root->right);  
}

an* find_succ(an *root)
{
	an *trav = root;

	while( trav->left !=NULL)
	{
		trav = trav->left;
	}

	return trav;
}

void update_height(an *root)
{
	root->h = 1 + max(get_h(root->left), get_h(root->right));  
}

an* rotate(an *root)
{
	int balance = bal(root);  

	int l_bal = bal(root->left);
	int r_bal = bal(root->right);
  
    if (balance > 1 && l_bal >= 0)  
    {
		return r_rot(root);  
  	}

    if (balance > 1 && l_bal < 0)  
    {  
        root->left = l_rot(root->left);  
        return r_rot(root);  
    }  
  
    if (balance < -1 && r_bal <= 0)
    {  
        return l_rot(root);  
  	}

    if (balance < -1 && r_bal > 0)  
    {  
        root->right = r_rot(root->right);  
        return l_rot(root);  
    }  

     return root;
}

an* del(an* root, int k);

an* del_node(an *root )
{
	if( (root->left == NULL) || (root->right == NULL) )  
        {  
        	an *temp = NULL ;   	
 
   			if( root->left != NULL )
   			{
   				temp = root->left;
   			}
   			else
   			{
   				temp = root->right;
   			}

            if (temp == NULL)  
            {  
                temp = root;  
                root = NULL;  
            }  
            else
            {   
            	*root = *temp;   
            }

            free(temp);  
        }  
        else
        {  
       
            an *temp = find_succ(root->right);  
  
            root->d = temp->d; 
            root->rc -= 1; 
  
            root->right = del(root->right,temp->d);  
        }  

        return root;
}

an* del(an* root, int k)  
{  
      
    if (root == NULL) 
    { 
        return root;  
    }

    if( k < root->d )
    {  
    	root->lc -= 1;
        root->left = del(root->left, k);  
    }
    else if( k > root->d )
    {  
    	root->rc -= 1;
        root->right = del(root->right, k);  
  	}
    else
    {  
    	root = del_node(root);
    	
    }  
  
    if (root == NULL)  
    {
    	return root;  
  	}
 	
 	update_height(root); 
  
   	return rotate(root);
}  


main()
{
	an *root=NULL;
	int sum= 0;

	int t;
	cin>>t;

	int a[] = {30,10,50,3,15,40,80,1,7,12,33,45,70,8};
	sum = 14;

	for(int i=0 ;i<sum ;i++)
	{
		root = ins(root,a[i]);
	}

	inorder(root);
	cout<<endl;
	
	while(t--)
	{
	
		cout<<"1.Insert"<<endl;
		cout<<"2.Search"<<endl;
		cout<<"3.Find Closest Element"<<endl;
		cout<<"4.Kth largest Element"<<endl;
		cout<<"5.Range Count"<<endl;
		cout<<"6.Delete"<<endl;

		cout<<endl<<endl;

		int q;
		cout<<"Enter Query :";
		cin>>q;

		switch(q)
		{
			case 1:
				int n;
				cin>>n;
				root = ins(root,n);
				sum = 1 + root->lc + root->rc;
				inorder(root);
				cout<<endl;
				break;

			case 2:
				cin>>n;
				search(root ,n);
				break;

			case 3:
				cin>>n;
				int p,q;
				cout<<find_closest(root ,n ,p,q)<<endl;
				break;

			case 4:
				cin>>n;
				find_kth(root ,n);
				break;

			case 5:
				int a,b;
				cin>>a>>b;
				range_count(root ,a,b ,sum);
				break;

			case 6:
				cin>>n;
				root = del(root ,n);
				inorder(root);
				break;
		}

	}

	return 0;
}