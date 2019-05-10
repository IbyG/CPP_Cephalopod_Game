#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <string>
#include "Board.h"
using namespace std;



//#include "Board.h"
class hashes
{
private:
    struct item
    {
        //this is the position
        string NumComb;

        //this is value in the position
        string PosVal;

        //this is the item pointer
        item* next;

    };

    //the hash table will consist of pointers which reference hashes
    item* HashTable[25];

public:
    hashes();

    //this will store the combination position
    int Hash(string key);

    void AddItem(string numcomb, string posval);

    int NumberOfItemsInIndex(int index);

    void PrintTable();

    bool FindValue(string numcomb);

    int GetValue(string numcomb);

    void changeValue(string numcomb, string NewValue);

    void RemoveItem(string numcom);

};


//filling the hash with values being "empty"
hashes::hashes()
{
    for(int i = 0; i < 25; i++)
    {
        HashTable[i] = new item;
        HashTable[i]->NumComb = "empty";
        HashTable[i]->PosVal = "empty";
        HashTable[i]->next = NULL;
    }

}

//producing the number that will determine where
//the info goes
int hashes::Hash(string key)
{
    int enchash = 0;
    int index;

    for(int i = 0; i < key.length(); i++)
    {
        enchash = (enchash + (int)key[i]) * 13;
       // cout <<"hash = " <<hash<< endl;

        index = enchash % 25;
    }

    return index;
}

//adding items to the hashtable
void hashes::AddItem(string numcomb, string posval)
{
    //retrieving the location in which the numcom can be place into the
    //hashtable
    int index = Hash(numcomb);


    //checking if the position is empty we add the values into the hash table
    if(HashTable[index]->NumComb == "empty")
    {
        //storing the play location
        HashTable[index]->NumComb = numcomb;
        //storing the value at that location
        HashTable[index]->PosVal = posval;
    }
    else
    {
        /*
        when there are two values have the same position in the
        hashtable when then place them on top of each other
        e.g. 12 1
             13 -1
        they are both in position 0 of the hashtable so we stack them on top of each
        other
        */
        item* Ptr = HashTable[index];
        item* n = new item;
        n->NumComb = numcomb;
        n->PosVal = posval;
        n->next = NULL;

        //while our next element is not nothing
        //make the pointer advance down the list
        while(Ptr->next != NULL)
        {
            Ptr = Ptr->next;
        }

        //now the Ptr is pointing to the last item in the list
        Ptr->next = n;

    }



}

//records the amount of values in an index
int hashes::NumberOfItemsInIndex(int index)
{
    //counting the number of items in a specific index in the
    //hashtable
    int count = 0;

    if(HashTable[index]->NumComb == "empty")
    {
        //this index is empty
        return count;
    }
    else
    {
        count++;
        //going through the index to see how many values it sotred
        item* Ptr = HashTable[index];
        while(Ptr->next != NULL)
        {
            count++;
            //moving it down the list
            Ptr = Ptr->next;
        }
    }

    return count;

}

//orinting the values in the table
void hashes::PrintTable()
{
    int number;

    for(int i = 0; i < 25; i++)
    {
        number = NumberOfItemsInIndex(i);
        cout << "----------------------\n";
        cout << "Index = " << i << endl;
        cout << "Numcomb "<<HashTable[i]->NumComb << endl;
        cout << "PosValue " << HashTable[i]->PosVal << endl;
        cout << "# of items = " << number << endl;
        cout << "----------------------\n";
    }
}

//finding the value from the given combination
//change this to a return type
bool hashes::FindValue(string numcomb)
{
    //return the bucket in which the data is saved
    int index = Hash(numcomb);

    bool foundValue = false;
    string value;

    //lokking in the bucket
    item* Ptr = HashTable[index];

    //scanning the entire list
    while (Ptr!= NULL)
    {
        //try to find the value based on name
        if(Ptr->NumComb == numcomb)
        {
            foundValue = true;
            value = Ptr->PosVal;
        }
        Ptr = Ptr->next;
    }
    /*
    if(foundValue == true)
    {
        cout << "Number = " << value << endl;
    }
    else
    {
        cout << "Not Found" << endl;
    }
    */
    return(foundValue);



}


//retrieves the values that are left right up down
int hashes::GetValue(string numcomb)
{
    //return the bucket in which the data is saved
    int index = Hash(numcomb);

    bool foundValue = false;
    string value;

    //lokking in the bucket
    item* Ptr = HashTable[index];

    //scanning the entire list
    while (Ptr!= NULL)
    {
        //try to find the value based on name
        if(Ptr->NumComb == numcomb)
        {
            foundValue = true;
            value = Ptr->PosVal;
        }
        Ptr = Ptr->next;
    }

    if(foundValue == true)
    {
        //cout <<value;
        int num = stoi(value);
        return(num);
        //return(value);



    }
    else
    {
        //cout<<endl<<numcomb<<endl;
        return(0);

    }

    //return(foundValue);



}



//changing the value of a position
void hashes::changeValue(string numcomb, string newvalue)
{
     //return the bucket in which the data is saved
    int index = Hash(numcomb);

    bool foundValue = false;
    string value;

    //lokking in the bucket
    item* Ptr = HashTable[index];

    //scanning the entire list
    while (Ptr!= NULL)
    {
        //try to find the value based on name
        if(Ptr->NumComb == numcomb)
        {
            foundValue = true;
            //value = Ptr->PosVal;
            Ptr->PosVal = newvalue;
        }
        Ptr = Ptr->next;
    }

    if(foundValue == true)
    {
        //Ptr->PosVal = newvalue;
        cout << "it's done" <<endl;
    }
    else
    {
        //cout << "Not Found" << endl;
    }
}

//deleting the information based on number combination
void hashes::RemoveItem(string numcomb)
{
    int index = Hash(numcomb);

    item* delPtr;
    item* P1;
    item* P2;

    //case 0  bucket is empty
    if(HashTable[index]->NumComb == "empty")
    {
        //cout << numcomb<<"not in the hashtable" <<endl;
        return;
    }
    //case 1 only 1 item contained in the bucket and that item has matching name
    else if(HashTable[index]->NumComb == numcomb &&HashTable[index]->next == NULL)
    {
        HashTable[index]->NumComb = "empty";
        HashTable[index]->PosVal = "empty";
    }
    //case  2 - match is located in the first item in the the bucket but there are more items in the bucket
    else if(HashTable[index]->NumComb == numcomb)
    {
        delPtr = HashTable[index];
        HashTable[index] = HashTable[index]->next;
        delete delPtr;

        //cout<<numcomb<< "was removed from table";

    }
    //case 3 - bucket contains items but first item is not a match
    else{
        P1 = HashTable[index]->next;
        //trailing p1
        P2 = HashTable[index];

        //as long as we are pointing to an item
        //and that item is not what i am looking for
        //advance p1 and p2
        while(P1 != NULL && P1->NumComb != numcomb)
        {
            P2 = P1;
            P1 = P1->next;
        }
        //case 3.1 - there is no match
        if(P1 == NULL)
        {
            //cout<<numcomb<<" This was not found in the hash table"<<endl;
            return;
        }
        //case 3.2 match is found
        else
        {
            delPtr = P1;
            P1 = P1->next;
            P2->next = P1;

            delete delPtr;
            //cout<<numcomb<< "was removed from table";
        }
    }




}
#endif // HASH_H
