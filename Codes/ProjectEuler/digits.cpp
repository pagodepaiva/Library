vector <int> digits(int x){
    while(x > 0){
        int k = x % 10;
        digits.push_back(k);
        x /= 10;
    }
    reverse(digits.begin(), digits.end());
    return digits;
}
