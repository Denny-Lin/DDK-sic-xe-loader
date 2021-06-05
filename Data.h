#include <cstdlib>
#include <iostream>
#include<fstream>
using namespace std;

class Data{
  public:            
    void open();    
    string address[80];
    string opcode[80]; 
    string operands[80];
    string objectcode[80];
    int loc[80];
    int x_flog[80];          
};

void Data::open()
{
   int row=0,flog=0;//«ü¥O¦æ¼Æ     
   fstream file;
   file.open("file.txt",ios::in);   
   
 do{ 
   char buffer[80],addr[10],opc[10],ope[10];
   row++;                         
   file.getline(buffer,sizeof(buffer)); 
   
   int i=0,j=0,k=0;
   
   while(buffer[i] != '\t')
    {
    addr[i]=buffer[i];
    i++;
    }
    addr[i]='\0';

   while(buffer[j+i+1] != '\t')
    {
    opc[j]=buffer[j+i+1];
    j++;    
    }
    opc[j]='\0';
   while(buffer[i+j+k+2] != '\0' && buffer[i+j+k+2] != ',')
    {      
    ope[k]=buffer[i+j+k+2];
    k++;
    }        
    ope[k]='\0';
    
    if(buffer[i+j+k+2] == ',')
    {
       x_flog[flog] = row-1;                 
       flog++;                      
    }
    
   address[row-1].assign(addr);
   opcode[row-1].assign(opc);
   operands[row-1].assign(ope);
 }while(!file.eof());
  
} 

