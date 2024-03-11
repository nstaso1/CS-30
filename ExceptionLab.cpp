#include <iostream>
#include <vector>

using namespace std;



class StackF : public runtime_error
{
public:
	StackF(int val, const char* s) : _value(val), runtime_error(s)
	{}

	int getV() const { return _value; }

private:
	int _value;
};

class StackE : public runtime_error
{
public:
	StackE(const char* s) : runtime_error(s)
	{}
};

class InvalidS : public invalid_argument
{
public:
	InvalidS(const char* s) : invalid_argument(s)
	{}
};

class IntStack
{
public:
	
	IntStack(int MaxS)
	{
		if (MaxS < 0)
		{
			throw InvalidS("Cannot stack size less than 0");
		}

		data.resize(MaxS);
		c_i = 0;
	}

	void push(int new_data)
	{
		if (c_i == data.size())
		{
			throw StackF(new_data, "Push to a full stack");
		}
		else
		{
			data.at(c_i) = new_data;
			c_i++;
		}
	}

	int pop()
	{
		if (c_i == 0)
		{
			throw StackE("Pop from an empty stack");
		}
		else
		{
			
			c_i--;
			return data.at(c_i);
		}
	}

private:
	vector<int> data;
	unsigned int c_i;
};

int main()
{
	// Trying to test a Constructor
	try
	{
		IntStack c_t(-10);

		c_t.push(3);
		c_t.push(4);
		c_t.pop();
		c_t.pop();
	}
	catch (const InvalidS& e)
	{
		std::cerr << e.what() << '\n';
	}


	// Trying to test a push
	try
	{
		IntStack push_t(5);

		for (unsigned int i = 0; i < 7; i++) {
			push_t.push(i);
		}
	}
	catch (const StackF& e)
	{
		std::cerr << e.what() << ", value = " << e.getV() << '\n';
	}


	// Trying to test a pop
	try
	{
		IntStack pop_t(2);

		pop_t.push(1);
		pop_t.push(2);
		pop_t.pop();
		pop_t.pop();
		pop_t.pop();
	}
	catch (const StackE& e)
	{
		std::cerr << e.what() << '\n';
	}


	cout << "Finished!" << endl;


	return 0;
}