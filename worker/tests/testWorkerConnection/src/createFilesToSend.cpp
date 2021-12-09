#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <fstream>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>

#include "createFilesToSend.h"
#include "gtest/gtest.h"

void createFileWithList(std::vector<std::string> *filesToSend);

void createFileWithSet(std::vector<std::string> *filesToSend);

void createFileWithMap(std::vector<std::string> *filesToSend);

void createFileWithUnordSet(std::vector<std::string> *filesToSend);

void createFileWithUnordMap(std::vector<std::string> *filesToSend);


void createFilesToSend(std::vector<std::string> *filesToSend)
{
    createFileWithList(filesToSend);
    createFileWithSet(filesToSend);
    createFileWithMap(filesToSend);
    createFileWithUnordSet(filesToSend);
    createFileWithUnordMap(filesToSend);
}

void createFileWithList(std::vector<std::string> *filesToSend)
{
    std::ofstream fileWithList;
    std::string filename = "fileToSendWithList.bin";
    fileWithList.open(filename, std::ios::out);
    std::list<int> myList = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 2, 3, 4, 5, 6, 7 };
    myList.sort();
    myList.unique();
    for (int number : myList)
    {
        fileWithList << number;
    }
    fileWithList.close();
    filesToSend->push_back(filename);
}

void createFileWithSet(std::vector<std::string> *filesToSend)
{
    std::ofstream fileWithSet;
    std::string filename = "fileToSendWithSet.bin";
    fileWithSet.open(filename, std::ios::out);
    std::vector<std::string> vec = {"tralala", "lalala", "xoxoxo", "trololo" };
    std::set<std::string> mySet(vec.begin(), vec.end());
    for (std::set<std::string>::iterator it = mySet.begin(); it != mySet.end(); it++)
    {
        fileWithSet << *it;
    }
    fileWithSet.close();
    filesToSend->push_back(filename);
}

void createFileWithMap(std::vector<std::string> *filesToSend)
{
    std::ofstream fileWithMap;
    std::string filename = "fileToSendWithMap.txt";
    fileWithMap.open(filename, std::ios::out);
    std::map<std::string, int> myMap = {
        {"This", 1},
        {"Is", 2},
        {"Test", 3},
        {"With map", 4}
    };

    for (std::map<std::string, int>::iterator it = myMap.begin(); it != myMap.end(); it++)
    {
        fileWithMap << it->first << it->second;
    }
    fileWithMap.close();
    filesToSend->push_back(filename);
}

void createFileWithUnordSet(std::vector<std::string> *filesToSend)
{
    std::ofstream fileWithUnordSet;
    std::string filename = "fileToSendWithUnordSet.txt";
    fileWithUnordSet.open(filename, std::ios::out);
    std::unordered_set<int> mySet;
    for (int i = 0; i < 20; i++)
        mySet.insert(i);
    for (std::unordered_set<int>::iterator it = mySet.begin(); it != mySet.end(); it++)
    {
        fileWithUnordSet << *it;
    }
    fileWithUnordSet.close();
    filesToSend->push_back(filename);
}

void createFileWithUnordMap(std::vector<std::string> *filesToSend)
{
    std::ofstream fileWithUnordMap;
    std::string filename = "fileToSendWithUnordMap.txt";
    fileWithUnordMap.open(filename, std::ios::out);
    std::unordered_map<int, std::string> myMap;
    myMap[1] = "tralala";
    myMap[2] = "lalala";
    myMap[3] = "xoxoxo";
    for (std::unordered_map<int, std::string>::iterator it = myMap.begin(); it != myMap.end(); it++)
    {
        fileWithUnordMap << it->first << it->second;
    }
    fileWithUnordMap.close();
    filesToSend->push_back(filename);
}

void compareFiles(std::string first, std::string second)
{
    std::ifstream firstFile(first);
    std::string firstString((std::istreambuf_iterator<char>(firstFile)), \
        std::istreambuf_iterator<char>());
    std::ifstream secondFile(second);
    std::string secondString((std::istreambuf_iterator<char>(secondFile)), \
        std::istreambuf_iterator<char>());
    EXPECT_EQ(firstString, secondString);
}