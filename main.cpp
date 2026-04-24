#include <bits/stdc++.h>

using namespace std;

void BubbleSort(vector<int> &data, int &n){
    int firstHalf = (n % 2 == 0 ? n / 2 : (n / 2) + 1);
    for (int  i = 0; i <= firstHalf; i++)
    {
        bool isSorted = true;
        for (int j = firstHalf; j > i; --j)
        {
            if(data[j] < data[j - 1]){
                isSorted = false;
                swap(data[j], data[j - 1]);
            }
        }
        if(isSorted)
            break;
    }

}

void SelectionSort(vector<int> &data, int &n){
    int firstHalf = (n % 2 == 0 ? n / 2 : (n / 2) + 1);
    int secondHalf = firstHalf + 1;

}

void print(vector<int>& data){
    for (auto& i : data)
        cout << i << " ";

    cout << endl;
}

void insertData(vector<int>& data, int& n){
    for (int i = 0; i < n; i++)
    {
        int input;
        cin >> input;
        data[i] = input;
    }

}

int main(){
    int n;
    cin >> n;
    vector<int> data(n, 0);
    insertData(data, n);
    BubbleSort(data, n);
    print(data);

    return 0;
}