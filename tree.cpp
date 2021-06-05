#include <iostream>
#include "tree.h"
using namespace std;

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
     //cout<<"1\n";
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
             //cout<<"2\n";
             pretmp -> right_node = tmp;
             pretmp  =  pretmp -> right_node;
             pretmp -> left_node = NULL;
             pretmp -> right_node = NULL;       
           }
         else if(tmp -> data > pretmp -> data &&pretmp -> right_node != NULL)
           {
              //cout<<"3\n";
              pretmp  =  pretmp -> right_node;                   
           }
         else if(tmp -> data < pretmp -> data &&pretmp -> left_node == NULL)         
           {
             //cout<<"4\n";
             pretmp -> left_node = tmp;
             pretmp  =  pretmp -> left_node;
             pretmp -> left_node = NULL;
             pretmp -> right_node = NULL;  
                
           }
         else if(tmp -> data > pretmp -> data &&pretmp -> left_node != NULL)
           {
              //cout<<"5\n";
              pretmp  =  pretmp -> left_node;                   
           }            
                    
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

void tree::output()
{
   tree *s = new tree;
   s= root;
   
   //cout<< s -> data << "\n";
   
   while(s != NULL )
    {
      
      cout<< s -> data << " "<< s -> loc <<"\n"; 
      s = s -> right_node;           
    }    
     
     
     
     
}
