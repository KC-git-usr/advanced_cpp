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

#include <list>
#include <iostream>


using namespace std;



class TimeSeries {
public:
    list<pair<double, double>> time_data;

    bool CustomGreater(const pair<double, double>& node_1, const pair<double, double>& node_2) {
        return node_1.first < node_2.first;
    }

    void SortedInsert(const pair<double, double>& input_node) {
        // auto it = time_data.begin();
        // why can't i do it+1?
        for (auto it = time_data.begin(); it != time_data.end(); ++it) {
            if(CustomGreater(input_node, *it)) {
                time_data.insert(it, input_node);
                return;
            }
        }
        time_data.push_back(input_node);
    }

    explicit TimeSeries(list<pair<double, double>> input_time_data) {
        pair<double, double> node;

        // insert the very first element
        node = *input_time_data.begin();
        time_data.push_back(node);
        input_time_data.pop_front();

        // insert the rest of the elements in a sorted order
        while (!input_time_data.empty()) {
            node = *input_time_data.begin();
            SortedInsert(node);
            input_time_data.pop_front();
        }

    }

    // this is O(m*n)
    //
    void addData(const list<pair<double, double>>& input_time_data) {
        for(auto element : input_time_data) {
            SortedInsert(element);
        }
    }

    void printData() {
        cout<<"-----------------"<<endl;
        for (auto element : time_data) {
            cout<<element.first<<" : "<<element.second<<endl;
        }
        cout<<"-----------------"<<endl;
    }


    void mergeData(const TimeSeries& obj) {
        for(auto element : obj.time_data) {
            SortedInsert(element);
        }
    }

};


int main() {

    list<pair<double, double>> input_time_data {
        {1.124,6},
        {1.146,9},
        {1.297,4}};
    TimeSeries time_obj_1(input_time_data);
    time_obj_1.printData();
    time_obj_1.SortedInsert({1.125, 11});
    time_obj_1.printData();
    time_obj_1.addData({
                               {1.107,46},
                               {1.111,2},
                               {1.324,1}});
    time_obj_1.printData();

    TimeSeries time_obj_2({{1.275, 3}});
    time_obj_1.mergeData(time_obj_2);
    cout<< "Merged data"<<endl;
    time_obj_1.printData();

    return 0;
}

