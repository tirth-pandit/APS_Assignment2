#include<iostream>

using namespace std;

class node
{
	public :

		int *keys ;
		node **pointers ;
		int filled;
		int last;
		
		node(int order)
		{
			keys = new int[order-1];
			pointers = new node*[order];
			last = 1;
			filled = 0;
			
			for(int i=0;i<order;i++)
			{
				pointers[i] = NULL;
			}
		}
};

class tree
{
	public:
		node *root;
		int order;

		tree(int deg)
		{
			root = NULL;
			order = deg;
		}

		void node_ins(node *x ,int k)
		{
			int index;

			for (index = x->filled; index > 0 && k < (x->keys[index - 1]); index--) 
			{
				x->keys[index] = x->keys[index - 1];
				x->pointers[index + 1] = x->pointers[index];
			}

			x->pointers[index + 1] = x->pointers[index];
			x->keys[index] = k;
			x->filled++;
		}

	
		void insert(int key )
		{
			if( root == NULL )
			{
				root = new node(order);
				root->keys[0] = key;
				root->filled += 1;
				return;
			}

			if( root->filled == order -1 )
			{

				node *temp = new node(order);

				temp->pointers[0] = root;
				temp->last = 0;
				root = temp;

				node *n = temp;
				int index = 0;

				node *y = n->pointers[index];

				node *z =  new node(order);

				z->last = y->last;

				int splitfactor = (order - 1 )/2 ;


				if( order%2 == 0 )
				{
					z->filled = splitfactor;
					y->filled = splitfactor;
				}
				else
				{
					z->filled = splitfactor - 1;
					y->filled = splitfactor;
				}


				for(int j=0 ;j<=z->filled ;j++)
				{
					z->keys[j] = y->keys[ j + splitfactor + 1 ];
				}

			
				if( y->last == 0 )
				{
					for( int j=0 ;j<splitfactor ;j++ )
					{
						z->pointers[j] = y->pointers[j + splitfactor  + 1 ];
					}
				}


				node_ins(n ,y->keys[splitfactor]);
				n->pointers[index+1] = z;
			}

			node *trav = root;

			while( trav->last == 0 )
			{
				
				int ind = trav->filled - 1;

				while( key < trav->keys[ind] && ind >= 0 )
				{
					ind--;
				}

				ind += 1;

				if( trav->pointers[ind]->filled == order-1 )
				{

					node *n = trav;
					int index = ind;

					node *y = n->pointers[index];

					node *z =  new node(order);

					z->last = y->last;

					int splitfactor = (order - 1 )/2 ;


					if( order%2 == 0 )
					{
						z->filled = splitfactor;
						y->filled = splitfactor;
					}
					else
					{
						z->filled = splitfactor - 1;
						y->filled = splitfactor;
					}


					for(int j=0 ;j<=z->filled ;j++)
					{
						z->keys[j] = y->keys[ j + splitfactor + 1 ];
					}

					if( y->last == 0 )
					{
						for( int j=0 ;j<splitfactor ;j++ )
						{
							z->pointers[j] = y->pointers[j + splitfactor  + 1 ];
						}
					}


					node_ins(n ,y->keys[splitfactor]);
					n->pointers[index+1] = z;
						
					if( trav->keys[ind] < key )
					{
						ind++;
					}
				}

				trav = trav->pointers[ind];
			}

			node_ins(trav,key);
		}


	void show( node *root )
	{
        if( root == NULL )
        {
            return;
        }

		for(int i=0 ; i<root->filled ;i++)
		{
			cout<<root->keys[i]<<" ";
		}

		cout<<endl;
	
		if ( root->last == 0 )
		{
			for (int i = 0; i <= root->filled; i++)
			{
				show(root->pointers[i]);
			}
	
		}
	}

	int search_ele(int key ,node *r)
	{
			int i=0;

			while( i<r->filled && r->keys[i]<key)
			{
				i++;
			}

			if( i<r->filled && key == r->keys[i])
			{
				return 1;
			}
			else if( r->last )
			{
				return 0;
			}
			else
			{
				return search_ele( key , r->pointers[i] );
			}
	}
};


int main()
{

	int tc;
	cin>>tc;

	int od;
	cin>>od;

	tree t(od);

	while(tc--)
	{

		cout<<"1.Insert"<<endl;
		cout<<"2.Search"<<endl;
		cout<<"3.Print tree"<<endl;
		cout<<endl;

		int q;
		cin>>q;

		switch(q)
		{
			case 1:
				int n;
				cin>>n;
				t.insert(n);
				break;

			case 2:
				cin>>n;

				if(t.search_ele(n ,t.root))
				{
					cout<<"Available"<<endl;
				}
				else
				{
					cout<<"Not Available"<<endl;
				}

				break;

			case 3:
				t.show(t.root);
				break;
		}
	}

}
