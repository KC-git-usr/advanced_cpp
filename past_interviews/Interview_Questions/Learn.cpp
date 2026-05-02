#if 0
#include <iostream>

void Log(const char* msg); //function declaration

enum Example : unsigned int
{
	A = 5, B, C
};

struct Entity
{
	static Example x, y;

	void Print()
	{
		std::cout << x << "  " << y << std::endl;
	}
};

Example Entity::x;
Example Entity::y;

int main()
{
	Entity e;
	Entity::x = A;
	Entity::y = C;
	e.Print();

	std::cout << "Hello World" << std::endl;
	Log("Hello JnJ");
	std::cin.get();
}
#endif


#if 0
//deep copy
#include <iostream>
#include <string>


class String
{

private:
	char* m_Buffer;
	unsigned int m_Size;

public:

	String(const String& other)
		: m_Size(other.m_Size)
	{
		this->m_Buffer = new char[this->m_Size+1];
		memcpy(this->m_Buffer, other.m_Buffer, this->m_Size+1);
	}

	String(const char* string)
	{
		m_Size = strlen(string);
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, string, m_Size+1);
	}

	~String()
	{
		delete[] m_Buffer;
	}

	char& operator[](unsigned int index)
	{
		return m_Buffer[index];
	}

	friend std::ostream& operator<<(std::ostream& stream, const String& string);
};


std::ostream& operator<<(std::ostream& stream, const String& string)
{
	stream << string.m_Buffer;
	return stream;
}


int main()
{
	String string = String("KC");
	String second = string;

	second[1] = 'R';

	std::cout << string << std::endl;
	std::cout << second << std::endl;
	std::cout << "Hey" << std::endl;
	std::cin.get();
}
#endif


/*
//this oprerator
#include <iostream>

class Entity
{

private:
	int x;

public:
	void Print() const
	{
		std::cout << "Hello!" << std::endl;
	}

};


class ScopedPtr
{

private:
	Entity* m_Obj;

public:
	ScopedPtr(Entity* other)
		: m_Obj(other)
	{
	}
	~ScopedPtr()
	{
		delete m_Obj;
	}
	const Entity* operator->() const
	{
		return m_Obj;
	}
};


int main()
{
	const ScopedPtr obj = new Entity(); //this pointer is being implicitly casted into ScopedPtr type
	obj->Print();
	std::cin.get();
}
*/


/*
//dynamic arrays and vectors
#include <iostream>
#include <vector>

struct Vertex
{
	float x, y, z;
};

std::ostream& operator<<(std::ostream& stream, const Vertex& vertex)
{
	stream << vertex.x << ", " << vertex.y << ", " << vertex.z;
	return stream;
}

void Function(const std::vector<Vertex>& vertices)
{

}

int main()
{
	std::vector<Vertex> vertices;

	vertices.push_back({ 1, 2, 3 });
	vertices.push_back({ 4, 5, 6 });
	
	for (int i = 0; i < vertices.size(); i++)
		std::cout << vertices[i] << std::endl;

	vertices.erase(vertices.begin() + 1);

	for (const Vertex& v : vertices) //note that we are using a reference and hence avoided copying the vector elements
		std::cout << v << std::endl;

	Function(vertices); //when we passing the vector, we are passing by reference to avoid copying

	std::cin.get();
}
*/


/*
//optimizing vector class
#include <iostream>
#include <vector>

struct Vertex
{
	float x, y, z;

	Vertex(float x, float y, float z)
		:x(x), y(y), z(z)
	{
		std::cout << "Implicit" << std::endl;
	}

	Vertex(const Vertex& other)
		:x(other.x), y(other.y), z(other.z)
	{
		std::cout << "Copied" << std::endl;
	}
};


int main()
{
	//problem here is 
	//1. array is being resized from 1 to 2 to 3
	//2. array is being copied from the main function 
	//to the function where the vector is actully being constructed
	std::vector<Vertex> vertices;
	vertices.push_back(Vertex(1,2,3));
	vertices.push_back(Vertex(4,5,6));
	vertices.push_back(Vertex(7,8,9));

	//optimized code
	//1. if we know the 'environment' beforehand, we can reserve memory space for our array
	//2. we can insert the array element directly into the array
	std::vector<Vertex> vertices2;
	vertices.reserve(3);
	vertices.emplace_back(1, 2, 3);
	vertices.emplace_back(4, 5, 6);
	vertices.emplace_back(7, 8, 9);

	std::cin.get();
}
*/



//local static and Singleton class
#include <iostream>

class Singleton
{
public:
	static Singleton& Get()
	{
		static Singleton instance; //although it's scope is limited, it's lifetime is same as that of the prgm
		return instance;
	}
	void Function()
	{
		std::cout << "Do stuff" << std::endl;
	}
};

int main()
{
	Singleton::Get().Function();
	std::cin.get();
}



/*
//templates
#include <iostream>

template<typename T, int N>
class Array
{
private:
	T size[N]; //although we are allocating stack memory, we are doing it during compile time
public:
	int GetSize()
	{
		return N;
	}
};

template<typename T>
void Print(T value)
{
	std::cout << value << std::endl;
}

int main()
{
	Print(50);
	Print("Hello");
	Print(5.6f);

	Array<float, 5> array;
	std::cout << array.GetSize() << std::endl;
}
*/

/*
//macros
#include <iostream>
#define MAIN int main() \
{\
std::cin.get();\
}

MAIN
*/

/*
//auto
//note: auto& should be used when you don't want to copy
#include <iostream>
#include <string>

const char* GetName()
{
	return "Kumar";
}

int main()
{
	std::string Surname = "Ramesh";
	std::string Firstname = GetName();
	std::cout << Surname << std::endl;
	std::cout << Firstname << std::endl;
	std::cout << Firstname[0] << std::endl;
}
*/

/*
//static arrays
#include <iostream>
#include <array>

template<std::size_t size>
void PrintArray(const std::array<int, size>& data)
{
	for (size_t i = 0; i < data.size(); i++)
		std::cout << data[i] << std::endl;
}

int main()
{
	std::array<int, 5> data;
	data[0] = 52;
	data[1] = 9;
	PrintArray(data);
	std::cin.get();
}
*/

/*
//function pointers 1 of 2
#include <iostream>

typedef void(*HelloWorldFunction)(int);

void HelloWorld(int a)
{
	std::cout << "Hello : " <<a << std::endl;
}

int main()
{
	auto function = HelloWorld; //the memory address of the function in the binary file is being returned
	void(*function2)(int) = HelloWorld;
	function(2);
	function2(6);

	HelloWorldFunction function3 = HelloWorld;
	function3(9);

	std::cin.get();
}
*/

/*
//function pointers 2 of 2
#include <iostream>
#include <vector>

void Print(int a)
{
	std::cout << a << std::endl;
}

void Loop(const std::vector<int>& data, void(*func)(int))
{
	for (int value : data)
		func(value);
}

int main()
{
	std::vector<int> data = { 1,2,3,4,5,6 };
	Loop(data, Print);
	Loop(data, [](int a) {std::cout << (2 * a) << std::endl; });  //lambda function

	std::cin.get();
}
*/


/*
//lambda functions
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

void Loop(const std::vector<int>& data, void(*func)(int))
{
	for (int value : data)
		func(value);
}

void Looper(const std::vector<int>& data, const std::function<void(int)>& func)
{
	for (int value : data)
		func(value);
}

int main()
{
	std::vector<int> data = { 1,2,3,4,5,6 };
	int a = 10;

	auto lambda = [](int value) {std::cout << (2 * value) << std::endl; }; //lambda function in conjunction with function pointer
	Loop(data, lambda);

	auto lambda2 = [&a](int value) {std::cout << (2 * a) << std::endl; };
	Looper(data, lambda2);

	auto it = std::find_if(data.begin(), data.end(), [](int value) {return value > 3; }); //nice move
	std::cout << "First element greater than 3 is : " << *it << std::endl;

	std::cin.get();
}
*/


/*
//timing
#include <iostream>
#include <chrono>
#include <thread>

//we are using the scope/lifetime of a local object to start and stop our timer
struct Timer
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;

	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}
	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		float ms = duration.count() * 1000.0f;
		std::cout << "Duration of code snippet was : " << ms <<" milli sec" << std::endl;
	}
};

void Function()
{
	Timer timer;
	for (std::size_t i = 0; i < 10; i++)
		std::cout << "Hello\n";
}

int main()
{
	using namespace std::literals::chrono_literals;

	auto start = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(1s);
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> duration = end - start;

	std::cout << "Duration = " << duration.count() << std::endl;
	Function();
	std::cin.get();
}
*/

	