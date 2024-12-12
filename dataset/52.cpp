class Solution {
    const string betweenZeroToTwenty[21] = {
        "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
        "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen", "Twenty"
    };

    const string belowHundred[11] = { "", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };

public:
    string numberToWords(int num) {
        if (num == 0) return "Zero";
        return convert(num);
    }

    string convert(int num) {
        if (num <= 20) {
            return betweenZeroToTwenty[num];
        }

        if (num < 100) {
            string res = belowHundred[num / 10];
            int num2 = num % 10;
            if (num2) {
                 res += " " + convert(num2);
            }
            return res;
        }

        if (num < 1000) {
            string res = convert(num / 100) + " Hundred";
            int num2 = num % 100;
            if (num2) {
                 res += " " + convert(num2);
            }
            return res;
        }

        if (num < 1000000) {
            string res = convert(num / 1000) + " Thousand";
            int num2 = num % 1000;
            if (num2) {
                 res +=  " " + convert(num2);
            }
            return res;
        }

        if (num < 1000000000) {
            string res = convert(num / 1000000) + " Million";
            int num2 = num % 1000000;
            if (num2) {
                 res += " " + convert(num2);
            }
            return res;
        }

        if (num <= INT32_MAX) {
            string res = convert(num / 1000000000) + " Billion";
            int num2 = num % 1000000000;
            if (num2) {
                 res += " " + convert(num2);
            }
            return res;
        }

        return "";
    }
};