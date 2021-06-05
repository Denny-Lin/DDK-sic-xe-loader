#include <iostream>

using namespace std;

class tree{
public: 
   tree(){root = NULL;
          left_node = NULL;
          right_node = NULL;};
   void input(string s,int location);//input data to tree
   int search(string s);//search data and return location      
private:      
   tree *left_node;
   tree *right_node;
   string data;
   tree *root;
   int  loc;  
      
};

//------------------------------------------------------------------------------
void tree::input(string s,int location)
{
  tree *tmp;
  tmp=new tree();   
  tmp -> data = s;
  tmp -> loc = location;
  
  tree *pretmp;
  pretmp = new tree();  
  pretmp = root;
  
  if(root == NULL)
   {
     root = tmp;
     root -> left_node = NULL;
     root -> right_node = NULL;         
   }  
  else
   { 
     while(pretmp != tmp)    
       {
         if(tmp -> data > pretmp -> data &&pretmp -> right_node == NULL)         
           {
             pretmp -> right_node = tmp;
             pretmp  =  pretmp -> right_node;
             pretmp -> left_node = NULL;
             pretmp -> right_node = NULL;       
           }
         else if(tmp -> data > pretmp -> data &&pretmp -> right_node != NULL)
           {
              pretmp  =  pretmp -> right_node;                   
           }
         else if(tmp -> data < pretmp -> data &&pretmp -> left_node == NULL)         
           {
             pretmp -> left_node = tmp;
             pretmp  =  pretmp -> left_node;
             pretmp -> left_node = NULL;
             pretmp -> right_node = NULL;  
                
           }
         else if(tmp -> data < pretmp -> data &&pretmp -> left_node != NULL)
           {
              pretmp  =  pretmp -> left_node;                   
           }
         else if(tmp -> data == pretmp -> data)
           cout<<"error!\n";                   
       }          
   }      
}

int tree::search(string s)
{
  tree *sear;
  sear = new tree(); 
  sear = root;
  
  while(sear -> data != s) 
   {
      if(sear -> data > s)
       sear =  sear ->  left_node;     
      else
       sear =  sear ->  right_node;            
   } 
    
   return sear -> loc;
}

