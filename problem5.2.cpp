#include <iostream>
#include <vector>
#include <stack>
using namespace std;


int main() {

    int n;
    cin >> n;

    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    } 
    
    vector<int> res(n,-1);
    stack<int> positions;

    for (int i = 0; i < n*2; i++) {          //Activating the circular array 
        int index = i % n;


        while (!positions.empty() && v[positions.top()] < v[index]) {
            res[positions.top()] = v[index]; //save the position of the next greater number in the result vector
            positions.pop();
        }
        if(i < n) {
            positions.push(index);            //push the index just once 
        }
    }
    for (int i = 0; i < n; i++) {
        cout << res[i] << " ";} 
    cout << endl;
    return 0;
}