#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>

using namespace std;

void min_reduction(vector<int>& arr){
    int min_value = INT_MAX;
    #pragma omp parallel for reduction(min: min_value)
    for(int i = 0 ; i< arr.size() ; i++){
        if(min_value > arr[i]){
            min_value = arr[i];
        }
    }
    cout<< "Minimum Value: "  << min_value <<endl;
}

void max_reduction(vector<int>& arr){
    int max_value = INT_MIN;

    #pragma omp parallel for reduction(max: max_value)
    for(int i = 0 ; i < arr.size() ; i++){
        if(max_value < arr[i]){
            max_value = arr[i];
        }
    }
    cout<< "max value: "<< max_value<<endl;
}

void sum_reduction(vector<int>& arr){
    int sum = 0;
    #pragma omp parallel for reduction(+: sum)
    for( int i = 0 ; i < arr.size() ; i++){
        sum += arr[i];
    }
    cout << "Sum: " << sum <<endl;
}

void average_reduction(vector<int>& arr){
    int sum = 0;
    #pragma omp parallel for reduction(+: sum)
    for( int i = 0 ; i < arr.size() ; i++){
        sum += arr[i];
    }

    cout << "average: " << (double)sum/ arr.size() <<endl;
}

int main(){
    vector<int> arr = {1, 2, 3 ,4, 5}; // Added semicolon here
    min_reduction(arr);
    max_reduction(arr);
    sum_reduction(arr);
    average_reduction(arr);

    return 0;
}
