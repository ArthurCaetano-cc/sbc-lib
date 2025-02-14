#include <iostream>
#include <vector>

using namespace std;


int binaryExponentiation(int b, int n){  // computes b**n
    if(n == 0){
        return 1;
    } else if(n % 2 == 0){
        int result = binaryExponentiation(b, n/2);
        return result*result;
    } else{
        int result = binaryExponentiation(b, (n-1)/2);

        return result*result*b;
    }
}

int main(){

    int n, b;
    cin >> b >> n;

    int exponetation = binaryExponentiation(b, n);

    cout << exponetation << endl;

    return 0;
}