#include "myvector.h"

template <typename T>     
MyVector<T>::MyVector(int cap)
{
	data = new T[cap];
	v_capacity = cap;
	v_size = 0;
}

template <typename T>
MyVector<T>::~MyVector()
{
	delete[] data;
}

template <typename T>
void MyVector<T>::push_back(T element)
{
    if (v_size >= v_capacity)     
    {
        T* data2 = new T[v_capacity * 2];
        for (int i = 0; i < v_size; i++)
        {
            data2[i] = data[i];
        }
        delete[] data;
        data = data2;
		if(v_capacity==0)
		{
			v_capacity = 1;
		}
        else
		{
			v_capacity *= 2;
    	}
	}

    data[v_size] = element;
    v_size++;
}

template <typename T>
void MyVector<T>::insert(int index, T element)
{
	if (index < 0 or index > v_size)
    {
        throw out_of_range("Invalid Index");
    }
	else
	{
		if (v_size >= v_capacity)
		{
			T* data2 = new T[v_capacity * 2];
			for (int i = 0; i < v_size; i++)
			{
				data2[i] = data[i];
			}
			delete[] data;
			data = data2;
			v_capacity *= 2;
		}
		for (int i = v_size; i > index; i--)
		{
			data[i] = data[i - 1];
		}
		data[index] = element;
		v_size++;
	}		
}

template <typename T>
void MyVector<T>::erase(int index)
{
	if (index < 0 or index >= v_size)
    {
        throw out_of_range("Invalid Index");
    }
    else
	{
		for (int i = index; i < v_size - 1; i++)
		{
			data[i] = data[i+1];
		}
		
		v_size--;
	}
}

template <typename T>
T& MyVector<T>::at(int index) 
{
	if (index < 0 or index >= v_size)
    {
        throw out_of_range("Invalid Index");
    }
    else
	{
    	return data[index];
	}
}

template <typename T>
const T& MyVector<T>::front() 
{
	if (empty())
	{
		throw out_of_range("Empty vector");
	}
	else
	{
		return data[0];
	}
}

template <typename T>
const T& MyVector<T>::back() 		
{
	if (empty())
	{
		throw out_of_range("Empty vector");
	}
	else
	{
		return data[v_size-1];
	}

}

template <typename T>
int MyVector<T>::size() const   
{
	return v_size;
}

template <typename T>
int MyVector<T>::capacity() const   
{
	return v_capacity;
}

template <typename T>
void MyVector<T>::shrink_to_fit()   
{
	if (empty())
    {
        v_capacity = 0;
        delete[] data;
    }
    else
    {
        T* data2 = new T[v_size];
        for (int i = 0; i < v_size; i++)
        {
            data2[i] = data[i];
        }
        delete[] data;
        data = data2;
        v_capacity = v_size;
    }
}

template <typename T>
bool MyVector<T>::empty() const        
{
	return v_size == 0;
} 


#ifndef _WIN32
//======================================
template <typename T>
void MyVector<T>::display()
{
	cout<<"╔";
	
	for(int i=0; i<v_capacity; i++)
	{	
		cout<<"════";
		if(i!=v_capacity-1) cout<<"╦";
	}
	cout<<"╗ size = "<<v_size<<endl;
	
	for(int i=0; i<v_capacity; i++)
	{
		cout<<"║";
		if(i<v_size)
			cout<<setw(4)<<data[i];
		else
			cout<<setw(4)<<" ";		
	}
	if(v_capacity==0) cout<<"║";
	cout<<"║"<<endl<<"╚";
	for(int i=0; i<v_capacity; i++)
	{
		cout<<"════";
		if(i != v_capacity-1) cout<<"╩";
	}
	cout<<"╝ capacity = "<<v_capacity<<endl;	
}
//======================================
#else
template <typename T>
void MyVector<T>::display()
{
	cout<<"+";
	
	for(int i=0; i<v_capacity; i++)
	{	
		cout<<"----";
		if(i!=v_capacity-1) cout<<"+";
	}
	cout<<"+ size = "<<v_size<<endl;
	
	for(int i=0; i<v_capacity; i++)
	{
		cout<<"|";
		if(i<v_size)
			cout<<setw(4)<<data[i];
		else
			cout<<setw(4)<<" ";		
	}
	if(v_capacity==0) cout<<"|";
	cout<<"|"<<endl<<"+";
	for(int i=0; i<v_capacity; i++)
	{
		cout<<"----";
		if(i != v_capacity-1) cout<<"+";
	}
	cout<<"+ capacity = "<<v_capacity<<endl;	
}
#endif

template class MyVector<int>;
template class MyVector<float>;
template class MyVector<Contact*>;