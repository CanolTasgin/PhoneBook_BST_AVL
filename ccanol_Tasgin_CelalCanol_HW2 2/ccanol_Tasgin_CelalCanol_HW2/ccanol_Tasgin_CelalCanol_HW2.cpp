
//
//  main.cpp
//  PHONEBOOK w/Binary Search Tree and AVL Tree - CS300 HOMEWORK 2 - finished 1st April 2020
//
//  Created by Canol Tasgin on 3/18/20.
//  Copyright © 2020 Canol Tasgin. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <sstream>
#include <chrono>
#include <cctype> 
#include <vector>
#include "avl.h"
#include "bst.h"

using namespace std::chrono;
using namespace std;

void DeleteContact(BinarySearchTree<contactInfo>&binaryTree,AvlTree<contactInfo>&avlTree){        //Deleting contact from both trees
    
    time_point<system_clock> startb, endb,starta,enda;
    cout<<"Deleting an item from the phonebook . . .\n====================\n";
    
    string name,surname,tel,city;
    cout<<"Enter the fullname of the contact to be deleted:\n";
    bool b=1;
    while(getline(cin,name)&&b){                                   //  taking the name to be deleted
        b=0;
    }
    stringstream s;
    s<<name;
    s>>name>>surname;                                              //  splitted name and surname into to 2 strings
    string spaceStr;
    if (!surname.empty())
        spaceStr=" ";
    
    contactInfo temp(name+spaceStr+surname,tel,city);              //   struct with name to be deleted and 2 empty strings afterwards
    
    starta = system_clock::now();
    avlTree.remove(temp);
    enda = system_clock::now();
    
    startb = system_clock::now();
    binaryTree.remove(temp);
    endb = system_clock::now();
    
    cout<<"Deleted succesfully...\n";
    cout <<"Deletion from Binary Tree took " << duration_cast<nanoseconds>(endb - startb).count() << " nanoseconds...\n";
    cout <<"Deletion from AVL Tree took " << duration_cast<nanoseconds>(enda - starta).count() << " nanoseconds...\n";
    cout<<endl;
    
}

void AddContact(BinarySearchTree<contactInfo>&binaryTree,AvlTree<contactInfo>&avlTree){      //Adding new contact to both trees
    
    time_point<system_clock> startb, endb,starta,enda;
    string name,surname,tel,city,emp;
    cout<<"Enter the information of the contact to be added:\nName: ";
    bool b=1;
    while(getline(cin,name)&&b){
        b=0;
    }
    stringstream s;
    s<<name;
    s>>name>>surname;
    
    //                                 Name and surname letter size arrangements between "START" and "END" comments
    //          START
    for (int i=1;i<=name.length();i++){
        if (name[i]<=122 && name[i]>=97)
            name[i]=name[i]-32;
    }
    
    for (int j=1;j<=surname.length();j++){
        if (surname[j]<=122 && surname[j]>=97)
            surname[j]=surname[j]-32;
    }
    
    
    for (int i=1;i<=name.length();i++){
        name[i]=name[i]+32;
    }
    
    for (int j=1;j<=surname.length();j++){
        surname[j]=surname[j]+32;
    }
    
    if (name[0]<=122 && name[0]>=97)
        name[0]=name[0]-32;
    
    if (surname[0]<=122 && surname[0]>=97)
        surname[0]=surname[0]-32;
    
    //          END
    
    string space=" ";
    cout<<endl;
    cout<<"Tel: ";
    cin>>tel;
    cout<<endl;
    cout<<"City: ";
    cin>>city;
    
    contactInfo temp(name+space+surname,tel,city);                     //struct with name, phone no and city taken from the user
   
    if (binaryTree.find(temp).fullcontactName==name){                  //if same name already exists
        
        cout<<"The given contact full name already exists in the database.\n";
        
    }
    else{                                                              //if this is a new person:
        startb = system_clock::now();
        binaryTree.insert(temp);
        endb = system_clock::now();
        cout<<"Contact has been added successfully to BST\n";
        
        cout<<"Adding an item to the phonebook (AVL) . . .\n==========================="<<endl;
        cout<<endl;
        starta = system_clock::now();
        avlTree.insert(temp);
        enda = system_clock::now();
        
        cout<<"Contact has been added succesfully to AVL tree\n";
        cout<<endl;
        cout <<"Adding a contact to the Binary Tree took " << duration_cast<nanoseconds>(endb - startb).count() << " nanoseconds...\n";
        cout <<"Adding a contact to the AVL Tree took " << duration_cast<nanoseconds>(enda - starta).count() << " nanoseconds...\n";
        cout<<endl;
    }
    
}

void SearchAContact(BinarySearchTree<contactInfo>binaryTree,AvlTree<contactInfo>avlTree){      //Searching contact info from trees and prints it
    
    string contactName,temp,tempName;
    cout<<"Search for a contact: ";
    
    bool b=1;
    while(getline(cin,tempName)&&b){               //took 2 strings as input at the same time
        b=0;
    }
    contactName=tempName;
    
    string nameC,surnameC;
    stringstream s;
    s<<contactName;
    s>>nameC>>surnameC;                            //splitted the string
    
                                                   //Name and surname letter size arrangements between "START" and "END" comments
    //          START
    
    if (nameC[0]<=122 && nameC[0]>=97)
        nameC[0]=nameC[0]-32;
    if (surnameC[0]<=122 && surnameC[0]>=97)
        surnameC[0]=surnameC[0]-32;
    
    for (int i=1;i<=nameC.length();i++){
        if (nameC[i]<=122 && nameC[i]>=97)
            nameC[i]=nameC[i]-32;
    }
    
    for (int j=1;j<=surnameC.length();j++){
        if (surnameC[j]<=122 && surnameC[j]>=97)
            surnameC[j]=surnameC[j]-32;
    }
    
    string spaceStr;
    
    if (!surnameC.empty())
        spaceStr=" ";
    
    temp=nameC+spaceStr+surnameC;
    
    for (int i=1;i<=nameC.length();i++){
        nameC[i]=nameC[i]+32;
    }
    
    for (int j=1;j<=surnameC.length();j++){
        surnameC[j]=surnameC[j]+32;
    }
    
    //           END
    
    contactName=nameC+spaceStr+surnameC;
    cout<<endl;
    
    cout<<"Phonebook : Searching For : ("<<temp<<")\n====================================\n";
    cout<<endl;
    
    string no,adress;
    contactInfo findContact = contactInfo(contactName,no,adress);         //a struct with Contact Name taken from user and 2 empty strings
    
    binaryTree.search(findContact);
    avlTree.searchAvl(findContact);
    
}




int main() {
    
    time_point<system_clock> start, end;   //time points to Bst Tree Creation calculate time
    
    string fileName,line;
    
    cout<<"Please enter the contact file name: ";
    cin>>fileName;
    ifstream input(fileName);                                    //opened file
    
    contactInfo notFoundItem = contactInfo("","","");            //empty struct
    BinarySearchTree<contactInfo> binaryTree(notFoundItem);      //constructor for BST
    AvlTree <contactInfo> avlTree(notFoundItem);                 //constructor for AVL Tree
    
    cout<<"Loading the phonebook into a BST\n";
    cout<<endl;
    
    start = system_clock::now();
    while(getline(input,line)){                                  //BST creation from the file
        string name,surname,number,adress;
        stringstream ss;
        ss<<line;
        ss>>name>>surname>>number>>adress;                       //split the line into strings
        string space=" ";
        contactInfo temp(name+space+surname,number,adress);      //created a struct from the line
        binaryTree.insert(temp);
    }
    end = system_clock::now();
    
    cout <<"Phonebook creation in BST took " << duration_cast<microseconds>(end - start).count() << " microseconds\n";    //calculating the creation time
    cout<<endl;
    binaryTree.balanceCheck();
    cout<<"Loading the phonebook into an AVL\n";
    cout<<endl;
    
    ifstream text(fileName);
    
    start = system_clock::now();
    while(getline(text,line)){                                    //same operations for AVL tree
        
        string name,surname,number,adress;
        stringstream ss;
        ss<<line;
        ss>>name>>surname>>number>>adress;
        string space=" ";
        
        contactInfo temp(name+space+surname,number,adress);
        avlTree.insert(temp);
    }
    end = system_clock::now();
    
    cout <<"Phonebook creation in AVL took " << duration_cast<nanoseconds>(end - start).count() << " nanoseconds\n";
    cout<<endl;
    
    avlTree.balanceCheck();
    
//                                                                - ACTION MENU OPERATIONS BELOW -
    bool a = 1;
    int action;
    while(a){
        cout<< "Choose which action to perform from 1 to 6:\n1 - Search a phonebook contact\n2 - Adding a phonebook contact\n3 - Deleting a phonebook contact\n4 - Print the phonebook to a file(inorder)\n    Print the phonebook to a file(preorder)\n5 - Draw the Phonebook as a Tree to a file\n6 - Press 6 to exit\n"<<endl;
        cin>>action;
        
        if(action==1){
            SearchAContact(binaryTree, avlTree);
            cout<<endl;
        }
        else if (action==2)
            AddContact(binaryTree, avlTree);
        else if (action==3)
            DeleteContact(binaryTree, avlTree);
        else if (action==4){
            binaryTree.PreOrderPrintToFile();
            binaryTree.InOrderPrintToFile();
            avlTree.PreOrderPrintToFile();
            avlTree.InOrderPrintToFile();
        }
        else if(action ==5){
            binaryTree.DrawTreeToFile();
            avlTree.DrawTreeToFile();
        }
        else if(action==6)
            return 0;
        else if(action<1||action>6)
            a=0;
    }
    
    return 0;
    
}
