/*
 Build a time series class in C++ supporting the following:
* Adding points with timestamp and value
* Printing points in order of timestamp
* Merging two timeseries (add another timeseries to current timeseries)

Also write some test cases.


Seenu:
Don't use a map
Sort while insertion
 * */

#include <map>
#include <iostream>
#include <algorithm>


using namespace std;


class TimeSeries {
public:
    map<double, double> time_series_data;

    explicit TimeSeries(const map<double, double>& input_time_series_data) {
        for(auto element : input_time_series_data)
            this->time_series_data[element.first] = element.second;
    }

    void addData(const map<double, double>& input_time_series_data) {
        double input_time_stamp, input_value;
        for(auto element : input_time_series_data) {
            input_time_stamp = element.first;
            input_value = element.second;
            //check if time_stamp doesn't already exist in our map
            if (this->time_series_data.find(input_time_stamp) != this->time_series_data.end()) {
                cout << input_time_stamp << " is an invalid time stamp" << endl;
                continue;
            }
            this->time_series_data[input_time_stamp] = input_value;
        }
    }

    void printData() {
        cout<<"-----------------"<<endl;
        for (auto element : this->time_series_data) {
            cout<<element.first<<" : "<<element.second<<endl;
        }
        cout<<"-----------------"<<endl;
    }


    void mergeData(const TimeSeries& obj) {
//        for(auto element : this->time_series_data) {
//            this->time_series_data[element.first] = element.second;
//        }
        merge(this->time_series_data.begin(), this->time_series_data.end(), 
              obj.time_series_data.begin(), obj.time_series_data.end(),
              this->time_series_data.begin());
    }

};


int main() {

    map<double, double> input_time_series_data1 {
        {1.123,6},
        {1.121,9},
        {1.119,11}};

    TimeSeries time_obj_1(input_time_series_data1);
    time_obj_1.addData({{1.120, 6}});
    time_obj_1.time_series_data.insert({1.111, 20});
    time_obj_1.printData();

    map<double, double> input_time_series_data2 {
            {1.122,6},
            {1.01,9},
            {1.11,11}};

    TimeSeries time_obj_2(input_time_series_data2);
    time_obj_2.addData({{1.125, 7}});
    time_obj_1.mergeData(time_obj_2);
    time_obj_1.printData();

    return 0;
}


/*
 Test cases:
     -ve numbers
     zero
     double value for RHS
     merge emtpy objects
 * */