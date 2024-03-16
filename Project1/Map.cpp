#include <iostream>

#include "Map.h"


Map::Map() : root(nullptr)
{}

Map::Map(const Map& rhs) : root(nullptr)
{
    keyType   key;
    ValueT val;

    
    for (int i = 0 ; i < rhs.size() ; i++)
    {
        rhs.get(i, key, val);
        insert(key, val);
    }
}

Map::~Map()
{
    destroySubTree(root);
}

const Map& Map::operator=(const Map& rhs)
{
    
    destroySubTree(root);

    keyType   key;
    ValueT val;

    
    for (int i = 0 ; i < rhs.size() ; i++)
    {
        rhs.get(i, key, val);
        insert(key, val);
    }

    return *this;
}



int Map::size() const
{
    return nodeC(root);   
}

bool Map::empty() const
{
    
    return root == nullptr ? true : false;
}


bool Map::update(const keyType& key, const ValueT& value)
{
    Node* nodePtr = root;

   
    while (nodePtr != nullptr)
    {
      
        if (nodePtr->key == key)
        {
            nodePtr->val = value;
            return true;
        }
        else if (key < nodePtr->key)
        {
            nodePtr = nodePtr->left;
        }
        else
        {
            nodePtr = nodePtr->right;
        }
    }

   
    return false;
}

bool Map::insert(const keyType& key, const ValueT& value)
{
   
    Node* newN = new Node;
    newN->left  = nullptr;
    newN->right = nullptr;
    newN->key   = key;
    newN->val   = value;

    bool success = true;

    insertN(root, newN, success);

    
    if (!success)
        delete newN;

    return success;
}


bool Map::insertOrU(const keyType& key, const ValueT& value)
{
    if (contains(key))
        return update(key, value);
    else
        return insert(key, value);
}


bool Map::contains(const keyType& key) const
{
    Node* nodePtr = root;

    
    while (nodePtr != nullptr)
    {
        
        if (key == nodePtr->key)
            return true;
        else if (key < nodePtr->key)
            nodePtr = nodePtr->left;
        else
            nodePtr = nodePtr->right;
    }
   
    return false;
}

bool Map::erase(const keyType& key)
{
    if (contains(key))
    {
        deleteN(key, root);
        return true;
    }
    
    return false;
}


bool Map::get(const keyType& key, ValueT& value) const
{
    Node* nodePtr = root;

    
    while (nodePtr != nullptr)
    {
       
        if (nodePtr->key == key)
        {
            value = nodePtr->val;
            return true;
        }
        else if (key < nodePtr->key)
        {
            nodePtr = nodePtr->left;
        }
        else
        {
            nodePtr = nodePtr->right;
        }
    }

   
    return false;
}

bool Map::get(int i, keyType& key, ValueT& value) const
{
    
    if (!((0 <= i) && (i < size())))
        return false;

    
    keyType keys[size()];
    ValueT vals[size()];

    int currI = 0;

    
    traverseN(root, keys, vals, currI);

   
    key   = keys[i];
    value = vals[i];

    return true;
}

void Map::swap(Map& other)
{
    Map temp;
    temp = other;
    other = *this;
    *this = temp;
}


void Map::destroySubTree(Node*& nodePtr)
{
    if (nodePtr != nullptr)
    {
        destroySubTree(nodePtr->left);
        destroySubTree(nodePtr->right);
        
        delete nodePtr;
        nodePtr = nullptr;
    }
}

int Map::nodeC(Node* nodePtr) const
{
    if (nodePtr == nullptr)
        return 0;

    int leftCount  = nodeC(nodePtr->left);
    int rightCount = nodeC(nodePtr->right);

    return (1 + leftCount + rightCount);
}

void Map::insertN(Node*& nodePtr, Node*& newN, bool& success)
{
    if (nodePtr == nullptr)
        nodePtr = newN;
    else if (newN->key < nodePtr->key)
        insertN(nodePtr->left, newN, success);
    else if (newN->key > nodePtr->key)
        insertN(nodePtr->right, newN, success);
    else
        success = false;
}



void Map::makeD(Node*& nodePtr)
{
    Node* temp = nullptr;

    if (nodePtr == nullptr)
        return;
    
    else if (nodePtr->right == nullptr)
    {
        temp = nodePtr;
        nodePtr = nodePtr->left;
        delete temp;
    }
    
    else if (nodePtr->left == nullptr)
    {
        temp = nodePtr;
        nodePtr = nodePtr->right;
        delete temp;
    }
    else
    {
        temp = nodePtr->right;

       
        while (temp->left)
        {
            temp = temp->left;
        }

       
        temp->left = nodePtr->left;
        temp = nodePtr;
       
        nodePtr = nodePtr->right;
       
        delete temp;
    }
}

void Map::deleteN(const keyType& key, Node*& nodePtr)
{
   
    if (nodePtr == nullptr)
        return;
    else if (key < nodePtr->key)
        deleteN(key, nodePtr->left);
    else if (key > nodePtr->key)
        deleteN(key, nodePtr->right);
    else
        
        makeD(nodePtr);
}

void Map::traverseN(Node* nodePtr, keyType keys[], ValueT vals[], int& currI) const
{
    if (nodePtr != nullptr)
    {
        traverseN(nodePtr->left, keys, vals, currI);
        
        keys[currI] = nodePtr->key;
        vals[currI] = nodePtr->val;
        
        currI++;
        traverseN(nodePtr->right, keys, vals, currI);
    }
}


bool combine(const Map& m1, const Map& m2, Map& result)
{
    
    Map res;

    
    bool status = true;
    
   
    res = m1;

    
    for (int i = 0 ; i < m2.size() ; i++)
    {
        keyType   key;
        ValueT val;

        m2.get(i, key, val);

        
        if (res.contains(key))
        {
            ValueT val2;

            res.get(key, val2);
            
            
            if (val != val2)
            {
                status = false;
                res.erase(key);
                continue;
            }
        }

        
        res.insert(key, val);
    }

    
    result = res;

    return status;
}

void subtract(const Map& m1, const Map& m2, Map& result)
{
    
    Map res;

    
    res = m1;

    
    for (int i = 0 ; i < m2.size() ; i++)
    {
        keyType key;
        ValueT val;

        m2.get(i, key, val);

        
        res.erase(key);
    }

    
    result = res;
}
