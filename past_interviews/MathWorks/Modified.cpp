/*
 Build a time series class in C++ supporting the following:
* Adding points with timestamp and value
* Printing points in order of timestamp
* Merging two timeseries (add another timeseries to current timeseries)

Also write some test cases.


Seenu:
Don't use a map
Sort while insertion

Kumar:
I want to use priority queue, but the syntax is complicated
    a priority queue of pairs, first = timestamp, second = value
 * */

#include <map>
#include <iostream>
#include <vector>
#include <queue>

/*
 priority_queue<TimeSeries, list<TimeSeries>, greater<TimeSeries>> time_data(input_time_data.begin(), input_time_data.end(), greater<int>());
 * */


using namespace std;


struct CustomGreater {
    bool operator()(pair<double, double> var1, pair<double, double> var2) {
        return var1.first > var2.first;
    }
};


class TimeSeries {
    priority_queue<pair<double, double>, vector<pair<double, double>>, CustomGreater>* time_data_pq;

    explicit TimeSeries(vector<pair<double, double>> input_time_data) {
        time_data_pq = new(input_time_data.begin(), input_time_data.end(), CustomGreater());
    }
};

int main() {
    return 0;
}


// use an extra hasp-map to store the key-value
// since non-primitive pq