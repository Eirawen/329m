class Solution {
public:
    vector<string>arr1 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};  
    vector<string>arr2 = {"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    vector<string>arr3 = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen","Eighteen", "Nineteen"};
    vector<string>arr4 = {"", "Thousand", "Million", "Billion"};                                               

    string numberToWords(int num, int i) {
        //base case
        if(num == 0)
            return "";

        string ans = "";
        int unit = num % 10;
        ans = arr1[unit];
        num /= 10;

        int tens = num % 10;
        if(tens == 1)
            ans = arr3[unit];
        else

            ans = arr2[tens] + ans;
        num /= 10;

        int hund = num % 10;
        if(hund > 0)
            ans = arr1[hund] + "Hundred" + ans;
        num /= 10;
        string temp = numberToWords(num, i+1);
        if(ans == "")
            return temp;
        return temp + ans + arr4[i];
    }
    
    string numberToWords(int num) {
        if(num == 0)
            return "Zero";
        string ans = numberToWords(num, 0);
        int len = ans.length();
        for(int i = 1; i < len; i++){
            if(ans[i] >= 'A' && ans[i] <= 'Z'){
                ans.insert(ans.begin()+i, ' ');
                i += 2;
            }
            len = ans.length();
        } 
        return ans;
    }
};