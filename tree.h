using namespace std;

class tree{
public: 
   tree(){root = NULL;
          left_node = NULL;
          right_node = NULL;};
   void input(string s,int location);//input data to tree
   int search(string s);//search data and return location
   void output();//no use,just test
   
   //void FindRoot();        
private:      
   tree *left_node;
   tree *right_node;
   string data;
   tree *root;
   int  loc;  
      
};
