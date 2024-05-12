#ifndef Map_H
#define Map_H

#include <iostream>
#include <string>

using keyT   = std::string;
using ValueT = double;


class Map
{
    private:
        struct Node
        {
            keyT   key;
            ValueT val;
            Node*     left;
            Node*     right;
        };

        Node* root;

        void destroySubTree(Node*& nodePtr);
       

        int nodeC(Node* nodePtr) const;
       
        void scanN(Node* nodePtr, keyT keys[], ValueT vals[], int& desI, int& currI) const;

        void insertN(Node*& nodePtr, Node*& newNode, bool& success);
       
       void makeD(Node*& nodePtr);

        void deleteN(const keyT& key, Node*& nodePtr);
        
    

       
   

    public:
        Map();                                  

        Map(const Map& rhs);                    

        ~Map();                                 

        const Map& operator=(const Map& rhs);   

        bool empty() const;                     

        int size() const;                       

        bool insert(const keyT& key, const ValueT& value);
        
        bool update(const keyT& key, const ValueT& value);
        
        bool insertOrU(const keyT& key, const ValueT& value);
        
        bool erase(const keyT& key);
        
        bool contains(const keyT& key) const;
        
        bool get(const keyT& key, ValueT& value) const;
        

        bool get(int i, keyT& key, ValueT& value) const;
        
        void swap(Map& other);
       

};

bool combine(const Map& m1, const Map& m2, Map& result);
void subtract(const Map& m1, const Map& m2, Map& result);

#endif