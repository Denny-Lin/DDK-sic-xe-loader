#include <iostream>
#include <cmath>
#include "HashTable.h"
#include "tree.h"
#include "Data.h"
using namespace std;

typedef string Key;
typedef int Item;

int StringToInt(string s)
{
    int sum=0; 
    for(int i=0;i<s.size();i++)
      sum=sum*10+s[i]-48;           
   
    return sum;    
}
int StringToHex(string s)
{
    int sum=0; 
    for(int i=0;i<s.size();i++)
      sum=sum*16+s[i]-48;  
    return sum; 
}

string CStringToHexS(string s)
{
    string HS;
    char b[20];
    for(int i=0;i<s.size()-3;i++)
     {
      b[2*i]='4'+(s[i+2]-'A'+1)/16;
      if(((s[i+2]-'A'+1)%16) > 9)
      b[2*i+1]='A'+(s[i+2]-'A'+1)%16-10; 
      else
      b[2*i+1]='0'+(s[i+2]-'A'+1)%16;      
     }  
     b[(s.size()-3)*2] = '\0'; 
    HS.assign(b);     

    return HS;   
}
string XStringToHexS(string s)
{
    string HS;
    char b[20];
    for(int i=0;i<s.size()-3;i++)
     {
        b[i]=s[i+2];    
     }  
     b[s.size()-3] = '\0'; 
    HS.assign(b);     

    return HS;   
}

string HexToString(int opcode,int loc)
{
    string s;
    char b[7];
    
    b[6]='\0';
     
    for(int i=1;i>=0;i--)
     { 
       float x = pow(16,(float)i);
       
       if((opcode/(int)x) > 9)
            b[1-i] = 'A'+ opcode/(int)x-10;
       else 
            b[1-i] = '0'+ opcode/(int)x;     
            
       opcode = opcode %(int)x; 
     } 
          
    for(int i=3;i>=0;i--)
     { 
      float x = pow(16,(float)i);
      if((loc/(int)x) > 9)
          b[5-i] = 'A'+ loc/(int)x-10;
      else 
          b[5-i] = '0'+ loc/(int)x;     
            
      loc = loc %(int)x; 
     }  

    s.assign(b);    
    
    return s;        
}

int main()
{    
 
 tree t;
 HashTable h;
 Data sic;
 sic.open(); 

//--------HASHTABLE----------------
h.add("ADD",24);
h.add("AND",64);
h.add("COMP",40);
h.add("DIV",36);
h.add("J",60);
h.add("JEQ",48);
h.add("JGT",52);
h.add("JLT",56);
h.add("JSUB",72);
h.add("LDA",00);
h.add("LDCH",80);
h.add("LDL",8);
h.add("LDX",04);
h.add("MUL",32);
h.add("OR",68);
h.add("RD",216);
h.add("RSUB",76);
h.add("STA",12);
h.add("STCH",84);
h.add("STI",212);
h.add("STL",20);
h.add("STSW",232);
h.add("STX",16);
h.add("SUB",28);
h.add("TD",224);
h.add("TIX",44);
h.add("WD",220);


//---------PASS1----------------------------------------------------------------
 int loc_count=0,line=0;

 if(sic.opcode[line] == "START")
   {
   loc_count = StringToHex(sic.operands[line]);
   sic.loc[line] = loc_count;
   t.input(sic.address[line],sic.loc[line]);
   line++;
   }

 while(sic.opcode[line] != "END")
   {
     sic.loc[line] =  loc_count;
     if(sic.opcode[line] == "RESW")                    
         loc_count = loc_count + 3*StringToInt(sic.operands[line]);                  
     else if(sic.opcode[line] == "RESB")
         loc_count = loc_count + StringToInt(sic.operands[line]);
     else if(sic.opcode[line] == "BYTE")
       {
         if(sic.operands[line][0] == 'C')
          loc_count = loc_count + (sic.operands[line].size()-3);
         else if(sic.operands[line][0] == 'X')         
           loc_count = loc_count + (sic.operands[line].size()-3)/2;                 
       }
      else
        loc_count = loc_count+3;
        
        
        
     if(sic.address[line] != "\0")
       {
          t.input(sic.address[line],sic.loc[line]);                      
       }
      line++;                   
   }
//---------PASS2----------------------------------------------------------------   
int row = 0,flog = 0;
if(sic.opcode[row]  == "START" )
 row++;

while(sic.opcode[row] != "END") 
{
    if(sic.opcode[row] == "WORD")
      {
        
        int number = StringToInt(sic.operands[row]);       
        sic.objectcode[row] = HexToString(00,number);         
      }                      
    else if(sic.opcode[row] == "BYTE")
      {
         if(sic.operands[row][0] == 'C')
             sic.objectcode[row] = CStringToHexS(sic.operands[row]);                   
         else if(sic.operands[row][0] == 'X')
             sic.objectcode[row] = XStringToHexS(sic.operands[row]);               
      }
    else if(sic.opcode[row] == "RESB" || sic.opcode[row] == "RESW")
      {
        sic.objectcode[row]="\0";                   
      } 
    else                       
      {        
         if(sic.operands[row] == "\0")
          sic.objectcode[row] = HexToString(h.get(sic.opcode[row]),0000);
         else if(sic.x_flog[flog] == row)
          {
             sic.objectcode[row] = HexToString(h.get(sic.opcode[row]),t.search(sic.operands[row])+32768);
             flog++;  
          } 
         else 
         {
              sic.objectcode[row] = HexToString(h.get(sic.opcode[row]),t.search(sic.operands[row])); 
         }          
                              
      }  
   row++;                  
}   
   
//---------¿é¥X´ú¸Õ-------------------------------------------------------------    
  int times = 0,xflog=0; 
  cout<<"loc\taddress\topcode\toperands\tObjectCode\n";
  cout<<<"The first:"<sic.address[1]<<endl;     
 /*while(times != line)
   {
   printf("%04X\t",sic.loc[times]);       
   cout<<sic.address[times]<<"\t"<<sic.opcode[times]<<"\t"<<sic.operands[times];
   if(sic.x_flog[xflog] == times)
   {
   cout<<",x";
   xflog++;   
   }
   else
   cout<<"\t";
   
   cout<<"\t"<<sic.objectcode[times]<<"\n";
   times++;
   }*/
     
     
 system("pause");   
 return 0;   
}
