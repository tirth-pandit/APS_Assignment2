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

void count_para(an *root ,int d ,int &lchilds ,int &rchilds)
{
	if( d == 1 )
	{
		lchilds = lchilds -1 -root->rc;
		rchilds = rchilds + 1 + root->rc;
	}
	else
	{
		rchilds = rchilds -1 - root->lc;
		lchilds =lchilds + 1 +root->lc;
	}
}

void find_med(an *root ,int d ,int lchilds ,int rchilds)
{

	count_para(root ,d ,lchilds ,rchilds);

	
	if( rchilds == lchilds -1 )
	{
		float p = pred(root);
		float res = float( (root->d + p))/2;
		cout<<"Median :"<<res<<endl;
		return;
	}
	else if( lchilds == rchilds -1 )
	{
		float s = suc(root);
		float res = float( (root->d + s ))/2;
		cout<<"Median :"<<res<<endl;
		return;
	}
	if( lchilds == rchilds )
	{
		cout<<"Median :"<<root->d <<endl;
		return;
	}
	else
	{
		if( lchilds > rchilds)
		{
			find_med(root->left ,1 ,lchilds ,rchilds);
		}
		else
		{
			find_med(root->right ,0 ,lchilds ,rchilds);
		}
	}
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

void median(an *root ,int sum)
{	
	   if( root->lc == root->rc)
		{
			cout<<"Median :"<<root->d <<endl;
			return ;
		}
		else if( sum%2 == 0 )
		{
			if(root->lc == (sum/2))
			{
				float pre = pred(root);
				cout<<"Median :"<<float(pre + root->d)/2 <<endl;
				return;
			}
			else if( root->lc == ( (sum/2)-1 ))
			{
				float s = suc(root);
				float res = float( (root->d + s ))/2;
				cout<<"Median :"<<res<<endl;
				return;
			}
		}
	
		if(root->lc < root->rc)
		{	
			find_med(root->right ,0 ,root->lc ,root->rc);
		}
		else
		{	
			find_med(root->left ,1 ,root->lc ,root->rc);
		}
			
		return ;
}

main()
{
	an *root=NULL;

	int t;
	cin>>t;

	while(t--)
	{
		int n;
		cin>>n;

		root = ins(root , n);

		int sum = 1 + root->lc + root->rc;
		
		median(root,sum);

		inorder(root);

		cout<<endl<<endl;

	}

	return 0;
}