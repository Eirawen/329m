class Solution {
public:
    const vector<string> below_20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    const vector<string> tens = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    const vector<string> thousands = {"", "Thousand", "Million", "Billion"};
    
    string helper(int num) {
        if (num == 0) return "";
        else if (num < 20) return below_20[num];
        else if (num < 100) return tens[num / 10] + (num % 10 ? " " + helper(num % 10) : "");
        else return below_20[num / 100] + " Hundred" + (num % 100 ? " " + helper(num % 100) : "");
    }

    string numberToWords(int num) {
        if (num == 0) return "Zero";
        
        string result = "";
        int thousandIdx = 0;

        while (num > 0) {
            if (num % 1000 != 0) {
                result = helper(num % 1000) + (thousands[thousandIdx].empty() ? "" : " " + thousands[thousandIdx]) + (result.empty() ? "" : " " + result);
            }
            num /= 1000;
            thousandIdx++;
        }
        
        return result;
    }
};