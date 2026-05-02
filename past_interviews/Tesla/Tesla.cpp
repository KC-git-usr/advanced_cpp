#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include <regex>
#include <stdexcept>
#include <vector>
#include <pthread.h>

using namespace std;


// 1.  (10 points) Write 2 functions that both square a value, one function squares a reference to the given value, while the other function returns the square.

void square_by_reference(int& x) {
    x = x * x;
}

int square_by_value(int x) {
    return (x*x);
}


// 2.
//   a.  (6 points) Write a program that parses a generic string into its component parts. Assume all generic strings follow the following example format: CM2-63010-01-01 where the fields are as follows:
//   •  CM2 - line ID (as string)
//   •  63 - Process step (as integer)
//   •  01 - equipment ID  (as integer)
//   •  0 – row        (as integer)
//   •  01 – column  (as integer)
//   •  01 – level     (as integer)
//   b.  (4 points) write a unit test for this function with at least 3 test cases to prove your function is correct.

struct components {
    string lineId;
    int processStep;
    int equipmentId;
    int row;
    int column;
    int level;
};

components parseComponents(const string& input) {
    string input_format = "[a-zA-Z0-9]{3}-\\d{5}-\\d{2}-\\d{2}";

    if(!regex_match(input, regex(input_format)))
        throw invalid_argument("received invalid input");

    components parsedComponents;
    parsedComponents.lineId = input.substr(0, 3);
    parsedComponents.processStep = stoi(input.substr(4, 2));
    parsedComponents.equipmentId = stoi(input.substr(6, 2));
    parsedComponents.row = stoi(input.substr(8, 1));
    parsedComponents.column = stoi(input.substr(10, 2));
    parsedComponents.level = stoi(input.substr(13, 2));

    return parsedComponents;
}


// 3.  (15 points) Write a function that does the following:
//   •  Input: 1D list of floating point values (Y), 1D list of integers (X)
//   •  Output: list of floating point values, same length as the input
//   •  Fit a simple linear regression line to the input
//   •  Subtract the linear line from the input
//   •  Return the resultant
// Note: See: https://en.wikipedia.org/wiki/Simple_linear_regression for a refresher on the math. Do not use any libraries that solve the problem for you (use your judgement, printing/plotting libraries are OK)

vector<float> simple_linear_regression(vector<float> y_values, vector<int> x_values) {
    int x_size = x_values.size();
    vector<float> result;
    result.assign(x_size, 0);

    // Calc mean of x
    float x_mean = (accumulate(x_values.begin(), x_values.end(), 0.0)) / x_size;
    float y_mean = (accumulate(y_values.begin(), y_values.end(), 0.0)) / x_size;

    float num_sum = 0.0, denom_sum = 0.0;
    for(int i = 0; i < x_size; ++i) {
        num_sum += ((x_values[i] - x_mean) * (y_values[i] - y_mean));
        denom_sum += (pow((x_values[i] - x_mean), 2));
    }

    // Find slope and y_intercept
    float slope = num_sum / denom_sum;
    float y_intercept = y_mean - (slope * x_mean);

    // Calc residuals
    for(int i =0; i < x_size; ++i) {
        result[i] = y_values[i] - (y_intercept + slope * (x_values[i]));
    }

    return result;
}


// 4.  (15 points) Consider the following:
//   •  We have designed test software to test many variants of a widget that we produce. Each test queries a certain number of floating-point voltage values. Since this is a tester capable of testing many widget variants, not all values in this array will be populated for a given query. Some number (which could be 0) will have a value of exactly 0.
//   •  Your software will retrieve these values via a function which returns an array of floating-point voltages as described above. Your task is to write a function to place all zeroes in the array to the end of the array while maintaining order of the non-zero values. The algorithm will be running on an embedded system with limited memory and you should therefore limit new memory allocation in your solution.

vector<float> move_zeros_to_end(vector<float> voltages) {
    int i = 0, j = 0;

    for(i = 0; i < voltages.size(); i++) {
        if(voltages[i] != 0.0) {
            swap(voltages[i], voltages[j]);
            j++;
        }
    }

    return voltages;
}


// 5.  (25 points) Write a program in which two threads/routines (os threads, greenthreads, async coroutines, futures and promises are all acceptable) send messages back and forth to each other. Consider the following constraints:
//   •  One thread must start by sending "ping" and the other thread must respond with "pong.”
//   •  The “ping” thread must print the string sent by the “pong” thread and vice versa.
//   •  Each thread must only send its message 10 times before exiting.
//   •  Thread deadlock is not allowed.

pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int t1_count = 0;
int t2_count = 0;
string message = "ping";

void *ping_thread(void *arg) {
    while(t1_count < 10) {
        pthread_mutex_lock(&mutex_lock);
        while(message != "ping") {
            pthread_cond_wait(&cond, &mutex_lock);
        }
        cout << message << endl;
        message = "pong";
        t1_count++;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex_lock);
    }

    return &message;
}

void *pong_thread(void *arg) {
    while(t2_count < 10) {
        pthread_mutex_lock(&mutex_lock);
        while(message != "pong") {
            pthread_cond_wait(&cond, &mutex_lock);
        }
        cout << message << endl;
        message = "ping";
        t2_count++;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex_lock);
    }
    return &message;
}


// 6.  (25 points) Given a few objects with certain properties design an appropriate structure which conforms to the following constraints:
// •  These are the items given and their attributes:
// Car  Boat  Chair  Cup
//   •  id
//   •  name
//   •  Weight
//   •  Color
//   •  Type
// Boat
//   •  id
//   •  name
//   •  Weight
//   •  Color
//   •  Type
// Chair
//   •  id
//   •  name
//   •  Weight
//   •  Color
//   •  Type
// Cup
//   •  id
//   •  name
//   •  material
//   a. Create one instance of each item, place into a single array. Assign your own non-zero attribute values.
//   b. The first three items (Car, Boat, Chair) are expected to perform actions on an attribute called Weight.
//     o  The actions on the attribute Weight should be Sum() and Compare().
//     o  Sum operates on the item and takes another item as a parameter. Sum() returns the sum of their weights, if possible.
//     o  Compare() returns true if the item is heavier than the item passed as a parameter.
//   c. Lowercase qualities specify private properties, and Uppercase properties specify public properties.
//   d.  Sort array by ID. Print relevant information (include Weight for all weightful objects) of each item, displaying correct order.

class Intermediate_Item;
class Cup;

class Item {
private:
    int id_;
    string name_;

public:
    Item(int id, string name) :
            id_(id), name_(name) {
        cout << "Called parameterized ctor" << endl;
    }

    virtual int getID() {  // virtual not necessary, since we have only 1 implementation
        return this->id_;
    }

    static bool CustomCmp(const Item* lhs, const Item* rhs) {
        return (lhs->id_ < rhs->id_);
    }

    Item() {
        cout << "Called copy ctor" << endl;
    }

    Item* operator=(Cup* rhs) {
        cout << "Called assignment ctor" << endl;
        return this;
    }

    virtual ~Item() {}

};


class Intermediate_Item : public Item {

public:
    float Weight_;
    string Color_;
    string Type_;

    Intermediate_Item(int id, string name, float Weight, string Color, string Type) :
            Item(id, name), Weight_(Weight), Color_(Color), Type_(Type) {
    }

    float Sum(Intermediate_Item* input)  {
        return (this->Weight_ + input->Weight_);
    }

    bool Compare(Intermediate_Item* input) {
        return (this->Weight_ > input->Weight_ ? true : false);
    }


    virtual ~Intermediate_Item() {}
};


class Car : public Intermediate_Item {

public:

    Car(int id, string name, float Weight, string Color, string Type) :
            Intermediate_Item(id, name, Weight, Color, Type) {}

    ~Car() {}
};


class Boat : public Intermediate_Item {

public:
    Boat(int id, string name, float Weight, string Color, string Type) :
            Intermediate_Item(id, name, Weight, Color, Type) {}

    ~Boat() {}
};


class Chair : public Intermediate_Item {

public:
    Chair(int id, string name, float Weight, string Color, string Type) :
            Intermediate_Item(id, name, Weight, Color, Type) {}

    ~Chair() {}
};


//class Cup : protected Item {
class Cup : public Item {
private:
    string material_;

public:

    Cup(int id, string name, string material) :
            Item(id, name), material_(material) {}
//    Cup(int id, string name) :
//            Item(id, name) {}


    ~Cup() {}
};


int main() {

    // Q. 1.
    int x = 5;
    square_by_reference(x);
    cout << "Value squared by reference : " << x <<endl;

    int y = 5;
    int z = square_by_value(y);
    cout << "Value squared by value : " << z <<endl;


    // Q. 2
    components parsedComponents = parseComponents("CM2-63010-01-01");

    cout<<parsedComponents.lineId<<endl;
    cout<<parsedComponents.processStep<<endl;
    cout<<parsedComponents.equipmentId<<endl;
    cout<<parsedComponents.row<<endl;
    cout<<parsedComponents.column<<endl;
    cout<<parsedComponents.level<<endl;


    // Q. 3.
    vector<int> a {1, 2, 3, 4, 5, 6, 7};
    vector<float> b {21.9, 31.2, 12.4, 15.2, 23.1, 29.1, 5.0};

    vector<float> result = simple_linear_regression(b, a);
    for(int i = 0; i < a.size(); ++i) {
        cout<< result[i]<<" ";
    }
    cout<<endl;


    // Q. 4.
    vector<float> input {0.0, 1.0, 2.0, 0.0, 3.2};
    vector<float> result_4 = move_zeros_to_end(input);

    for(int i = 0; i < result_4.size(); ++i) {
        cout << result_4[i] << " ";
    }
    cout<<endl;


    // Q. 5.
    pthread_t ping, pong;
    pthread_create(&ping, NULL, ping_thread, NULL);
    pthread_create(&pong, NULL, pong_thread, NULL);

    pthread_join(ping, NULL);
    pthread_join(pong, NULL);


    // Q. 6.

//    Cup* my_obj = new Cup(1, "Tea", "Ceramic");  // Cup
//    Item* new_obj = my_obj;

    vector<Item*> my_vec(5);

//    Item* c = new Car(2, "Civic", 10.0, "Red", "Auto");
//    my_vec.push_back(c);  // Car
//    my_vec.push_back(new Boat(3, "Speed_Boat", 12.0, "Blue", "Manual"));
    cout << "my_vec[0] : " << my_vec[0] << endl;
    cout << "my_vec[1] : " << my_vec[1] << endl;


    my_vec[0] = new Car(2, "Civic", 10.0, "Red", "Auto");  // Boat
    my_vec[1] = new Boat(3, "Speed_Boat", 12.0, "Blue", "Manual");  // Boat
    my_vec[2] = new Chair(4, "Office", 3.0, "Black", "Wood");  // Chair
    my_vec[3] = new Cup(1, "Tea", "Ceramic");  // Cup
    my_vec[4] = static_cast<Item*>(new Cup(5, "Coffe", "Wood"));  // Cup

    cout << "my_vec[0] : " << my_vec[0] << endl;
    cout << "my_vec[1] : " << my_vec[1] << endl;

    // Sort vector
    sort(my_vec.begin(), my_vec.end(), Item::CustomCmp);

    // Print ID
    for(auto ele : my_vec) {
        cout << ele->getID() << " ";
    }
    cout << endl;

    // pass or fail dynamic cast
    for(auto ele : my_vec) {
        Intermediate_Item* output = dynamic_cast<Intermediate_Item* >(ele);
        if(output) {
            cout << "Valid dynamic cast" <<endl;
        } else {
            cout << "Invalid dynamic cast" <<endl;
        }
    }

    // Call Sum
//    my_vec[1]->Sum(my_vec[2]);
//    dynamic_pointer_cast<>()
    Item* car = new Car(2, "Civic", 10.0, "Red", "Auto");
    Item* boat = new Boat(3, "Spped_Boat", 12.0, "Blue", "Manual");
    Intermediate_Item* output_1 = dynamic_cast<Intermediate_Item* >(car);
    Intermediate_Item* output_2 = dynamic_cast<Intermediate_Item* >(boat);

    if(output_1) {
        cout << "Valid dynamic cast 1" <<endl;
    } else {
        cout << "Invalid dynamic cast 1" <<endl;
    }

    if(output_2) {
        cout << "Valid dynamic cast 2" <<endl;
    } else {
        cout << "Invalid dynamic cast 2" <<endl;
    }

    if(output_1 && output_2) {
        float result = output_1->Sum(output_2);
        cout<< result << endl;
    } else {
        cout << "Invalid dynamic cast" <<endl;
    }

    return 0;
}