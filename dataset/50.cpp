
        class Solution {
public:
string ones[20]={"", "One ",  "Two ", "Three ", "Four ", "Five ", "Six ", "Seven ", "Eight ",
                   "Nine ", "Ten ", "Eleven ", "Twelve ", "Thirteen ", "Fourteen ", "Fifteen ",
                   "Sixteen ","Seventeen ","Eighteen ","Nineteen "};
 string tens[10]={"",  "", "Twenty ","Thirty ","Forty ","Fifty ","Sixty ",
                   "Seventy ","Eighty ","Ninety "};
string hundred[10]={"", "One Hundred ",  "Two Hundred ", "Three Hundred ", "Four Hundred ", "Five Hundred ", "Six Hundred ", "Seven Hundred ", "Eight Hundred ",
                   "Nine Hundred "};
string convertToWords(int n,string s)
{
  string str="";
  if((n>100)&&((n%100)<=19))
  str+=hundred[n/100]+ones[(n%100)];
  else if((n>100)&&((n%100)>19))
  str+=hundred[n/100]+tens[(n%100)/10]+ones[(n%100)%10];
  else if(n%100==0)
  str+=hundred[n/100];
  else if(n<100&&(n>19))
  str+=tens[n/10]+ones[n%10];
  else if(n<=19)
  str+=ones[n];
  if(n)
  str+=s;
  return str;
}
             
    string numberToWords(int num) {
        string out;
        if(num==0)
        return "Zero";
        out+=convertToWords((num/1000000000),"Billion ");
        out+=convertToWords(((num/1000000)%1000),"Million ");
        out+=convertToWords(((num/1000)%1000),"Thousand ");
        out+=convertToWords((num%1000),"");
        return out.substr(0,out.length()-1);
    }
};
        
 