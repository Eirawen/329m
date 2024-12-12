class Solution {
public:
    string calculate(vector<int>temp, map<int,string> unitPlace,map<int,string> tenPlace,map<int,string> oneCase){
        string answer ;
        if(temp[9]){
            answer+=unitPlace[temp[9]]+" Billion " ;
        }
        if(temp[8]){
            answer+=unitPlace[temp[8]]+" Hundred " ;
        }
        if(temp[7]==1) answer+=oneCase[temp[6]]+" ";
            else{
                if(temp[7]) answer+=tenPlace[temp[7]]+" ";
                if(temp[6]) answer+=unitPlace[temp[6]]+" ";
            }
        if(temp[8] || temp[7] || temp[6]) answer+="Million ";

        if(temp[5]){
            answer+=unitPlace[temp[5]]+" Hundred ";
        }
        if(temp[4]==1) answer+=oneCase[temp[3]]+" ";
            else{

                if(temp[4]) answer+=tenPlace[temp[4]]+" ";
                if(temp[3]) answer+=unitPlace[temp[3]]+" ";
            }
        if(temp[5] || temp[4] || temp[3]) answer+="Thousand " ;

        if(temp[2]){
             cout<<"ans "<<answer.length()<<endl;;
            answer+=unitPlace[temp[2]]+" Hundred ";
            cout<<answer<<endl;
        }
        if(temp[1]==1) answer+=oneCase[temp[0]];
            else{
                if(temp[1]) answer+=tenPlace[temp[1]]+" ";
                if(temp[0]) answer+=unitPlace[temp[0]];
            }

            while(answer.size() and answer.back()==' ')
            answer.pop_back();
        return answer;
    }
    string numberToWords(int num) {
        if(num==0)
            return "Zero";

        map<int,string> unitPlace;
        unitPlace[0]="";
        unitPlace[1]="One";
        unitPlace[2]="Two";
        unitPlace[3]="Three";
        unitPlace[4]="Four";
        unitPlace[5]="Five";
        unitPlace[6]="Six";
        unitPlace[7]="Seven";
        unitPlace[8]="Eight";
        unitPlace[9]="Nine";

        map<int,string> tenPlace;
        tenPlace[0]="";
        tenPlace[1]="Ten";//We will never use this
        tenPlace[2]="Twenty";
        tenPlace[3]="Thirty";
        tenPlace[4]="Forty";
        tenPlace[5]="Fifty";
        tenPlace[6]="Sixty";
        tenPlace[7]="Seventy";
        tenPlace[8]="Eighty";
        tenPlace[9]="Ninety";

        map<int,string> oneCase;
        oneCase[0]="Ten";
        oneCase[1]="Eleven";
        oneCase[2]="Twelve";
        oneCase[3]="Thirteen";
        oneCase[4]="Fourteen";
        oneCase[5]="Fifteen";
        oneCase[6]="Sixteen";
        oneCase[7]="Seventeen";
        oneCase[8]="Eighteen";
        oneCase[9]="Nineteen";

        vector<int>temp;
        while(num){
            temp.push_back(num%10);
            num = num/10;
        }
        while(temp.size()<10){
            temp.push_back(0);
        }
        return calculate(temp,unitPlace,tenPlace,oneCase);
    }
};