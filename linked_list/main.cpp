#include "LinkedList.h"
#include "Leaker.cpp"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void TestAddHead();
void TestAddTail();
void TestBrackets();
void TestRemove();
void TestRemoveHeadTail();
void TestOtherRemoval();
void TestAddingArrays();
void TestFindAll();
void TestFind();
void TestInsertAt();
void TestRecursion();
void MyTest();

int main()
{

    int testNum;
    cin >> testNum;

    if (testNum == 1)
        TestAddHead();
    else if (testNum == 2)
        TestAddTail();
    else if (testNum == 3)
        TestBrackets();
    else if (testNum == 4)
        TestRemove();
    else if (testNum == 5)
        TestRemoveHeadTail();
    else if (testNum == 6)
        TestOtherRemoval();
    else if (testNum == 7)
        TestAddingArrays();
    else if (testNum == 8)
        TestFindAll();
    else if (testNum == 9)
        TestFind();
    else if (testNum == 10)
        TestInsertAt();
    else if (testNum == 11)
        TestRecursion();
    else if (testNum == 12)
        MyTest();

    return 0;
}

/*======== TESTING FUNCTIONS ========*/

void TestAddHead()
{
    cout << "=====Testing AddHead() functionality====" << endl;
    LinkedList<int> data;
    for (int i = 0; i < 12; i += 2)
        data.AddHead(i);
    cout << "Node count: " << data.NodeCount() << endl;
    cout << "Print list forward:" << endl;
    data.PrintForward();
    cout << "Print list in reverse:" << endl;
    data.PrintReverse();
}

void TestAddTail()
{
    cout << "=====Testing AddTail() functionality====" << endl;
    LinkedList<int> data;
    for (int i = 0; i <= 21; i += 3)
        data.AddTail(i);
    cout << "Node count: " << data.NodeCount() << endl;
    cout << "Print list forward:" << endl;
    data.PrintForward();
    cout << "Print list in reverse:" << endl;
    data.PrintReverse();
}

void TestBrackets()
{
    cout << "=====Testing operator[] to access value of nodes=====" << endl;
    LinkedList<int> list;
    int val = 10, val2 = 999, val3 = 22;
    cout << "Adding 10 to end of list" << endl;
    list.AddTail(val);
    cout << "Adding 999 to end of list" << endl;
    list.AddTail(val2);
    cout << "Adding 22 to end of list" << endl;
    list.AddTail(val3);

    const int value = list[0];
    cout << "Value of node[0]: " << val << " Expected value: " << value << endl;
    const int value2 = list[1];
    cout << "Value of node[1]: " << val2 << " Expected value: " << value2 << endl;
    int value3 = list[2];
    cout << "Value of node[2]: " << val3 << " Expected value: " << value3 << endl;

    cout << "Using brackets operator in a loop to change node values..." << endl;
    for (unsigned int i = 0; i < list.NodeCount(); i++)
        list[i] = i;

    list.PrintForward();
}

void TestRemove()
{
    cout << "=====Testing Remove() functionality=====" << endl;
    LinkedList<string> data;
    string test = "Test RemoveMe to RemoveMe find RemoveMe all RemoveMe matching ";
    test.append("RemoveMe nodes RemoveMe completed RemoveMe with RemoveMe no ");
    test.append("RemoveMe \"RemoveMe\" RemoveMe nodes RemoveMe remaining.");
    stringstream x(test);
    string tmp;
    while (getline(x, tmp, ' '))
        data.AddTail(tmp);

    cout << "Initial list: " << endl;
    data.PrintForward();
    string val = "RemoveMe";
    int count = data.Remove(val);
    cout << "\nRemoving " << val << " from the list." << endl;
    cout << "Removed " << count << " nodes from the list.\n" << endl;
    data.PrintForward();
    cout << "\nNodes removed: " << count << endl;

    count = data.Remove(val);
    cout << "Removing " << val << " from the list again." << endl;
    cout << "Nodes removed: " << count << endl;

}

void TestRemoveHeadTail()
{
    cout << "=====Testing RemoveHead()/RemoveTail() functionality=====" << endl;
    LinkedList<int> data;
    for (unsigned int i = 0; i < 70; i += 5)
        data.AddTail(i);

    cout << "Initial list: " << endl;
    data.PrintForward();

    cout << "Removing 2 Tail and 2 Head Nodes..." << endl;
    data.RemoveHead();
    data.RemoveTail();
    data.RemoveHead();
    data.RemoveTail();
    data.PrintForward();
}

void TestOtherRemoval()
{
    cout << "=====Testing RemoveAt() and clearing with RemoveHead()/RemoveTail() functionality=====" << endl;
    LinkedList<string> data;
    data.AddTail("Batman");
    data.AddTail("RemoveMe");
    data.AddTail("Superman");
    data.AddTail("RemoveMe");
    data.AddTail("Wonder Woman");
    data.AddTail("RemoveMe");
    data.AddTail("The Flash");

    cout << "Initial list: " << endl;
    data.PrintForward();
    cout << "\nRemoving using RemoveAt()..." << endl;
    data.RemoveAt(1);
    data.RemoveAt(2);
    data.RemoveAt(3);

    data.PrintForward();

    cout << "\nAttempting to remove out of range using RemoveAt()..." << endl;
    if (!data.RemoveAt(100))
        cout << "Attempt to RemoveAt(100) failed." << endl;
    else
        cout << "Successfully removed node 100? Weird, there are only 4 nodes..." << endl;

    cout << "\nClearing list using RemoveHead()..." << endl;
    while (data.RemoveHead()){}

    if (data.NodeCount() == 0)
        cout << "List is empty!" << endl;
    else
        cout << "List not empty!" << endl;

    cout << "Adding additional nodes..." << endl;
    data.AddTail("Robin");
    data.AddTail("Batgirl");
    data.AddTail("Nightwing");
    data.AddTail("Red Hood");
    data.AddTail("Bluebird");

    data.PrintForward();

    cout << "Clearing list using RemoveTail()..." << endl;
    while (data.RemoveTail()) {}

    if (data.NodeCount() == 0)
        cout << "List is empty!" << endl;
    else
        cout << "List not empty!" << endl;
}

void TestAddingArrays()
{
    cout << "=====Testing AddNodesHead() and AddNodesTail() =====" << endl;

    string values[5];
    values[0] = "*";
    values[1] = "**";
    values[2] = "***";
    values[3] = "****";
    values[4] = "*****";

    LinkedList<string> list;
    list.AddHead("**");
    list.AddHead("***");
    list.AddHead("****");
    list.AddHead("*****");
    list.AddHead("******");
    list.AddHead("*******");
    list.AddHead("********");
    list.AddHead("*********");
    list.AddHead("********");
    list.AddHead("*******");
    list.AddHead("******");

    list.AddNodesHead(values, 5);
    list.AddNodesTail(values, 5);
    list.PrintForward();
}

void TestFindAll()
{
    cout << "=====Testing FindAll() functionality=====" << endl;
    LinkedList<int> data;
    int searchVal = 256;

    data.AddTail(searchVal);
    data.AddTail(10);
    data.AddTail(20);
    data.AddTail(searchVal);
    data.AddTail(30);
    data.AddTail(searchVal);
    data.AddTail(40);
    data.AddTail(searchVal);

    cout << "Initial list: " << endl;
    data.PrintForward();

    vector<LinkedList<int>::Node *> nodes;
    data.FindAll(nodes, searchVal);

    cout << "\nNodes found: " << nodes.size() << endl;
    for (unsigned int i = 0; i < nodes.size(); i++)
    {
        cout << "Node #" << (i + 1) << ":\n";
        cout << "Value: " << nodes[i]->data << endl;

        cout << "Prev value: ";
        if (nodes[i]->prev != nullptr)
            cout << nodes[i]->prev->data;
        else
            cout << "nullptr";

        cout << "\nNext value: ";
        if (nodes[i]->next != nullptr)
            cout << nodes[i]->next->data;
        else
            cout << "nullptr";
        cout << endl;
    }
}

void TestFind()
{
    cout << "=====Testing Find()/GetNode() and InsertBefore()/InsertAfter() functionality=====" << endl;
    LinkedList<int> data;
    data.AddTail(10);
    data.AddHead(9);
    data.AddTail(11);
    data.AddHead(8);
    data.AddTail(12);

    cout << "Initial list: " << endl;
    data.PrintForward();

    LinkedList<int>::Node * node = data.Find(10);
    cout << "\nSearching for node with value of 10..." << endl;

    if (node != nullptr)
    {
        cout << "Node found! Value: " << node->data << endl;
        cout << "Prev value: " << node->prev->data << endl;
        cout << "Next value: " << node->next->data << endl;
    }
    else
        cout << "Error! Returned node was a nullptr.";

    cout << "\nInserting 2048 before node and 4096 after node." << endl;
    data.InsertBefore(node, 2048);
    data.InsertAfter(node, 4096);
    data.PrintForward();

    cout << "\nUsing GetNode() to get the 5th node in the list..." << endl;

    node = data.GetNode(4);
    if (node != nullptr)
    {
        cout << "Node found! Value: " << node->data << endl;
        cout << "Prev value: " << node->prev->data << endl;
        cout << "Next value: " << node->next->data << endl;
    }
    else
        cout << "Error! Returned node was a nullptr.";

    cout << "\nSearching for node with value of 200..." << endl;
    node = data.Find(200);
    if (node == nullptr)
        cout << "Node not found, nullptr returned." << endl;
}

void TestInsertAt()
{
    cout << "=====Testing InsertAt() functionality=====" << endl;
    LinkedList<string> data;
    string test = "great benefit linked is the ability to easily into the";
    stringstream x(test);
    string tmp;
    while (getline(x, tmp, ' '))
        data.AddTail(tmp);

    cout << "Initial list: " << endl;
    data.PrintForward();
    cout << "Node count: " <<  data.NodeCount() << endl;

    cout << "\nInserting words into the list with InsertAt()..." << endl;

    data.InsertAt("One", 0);
    data.InsertAt("of", 3);
    data.InsertAt("lists", 5);
    data.InsertAt("insert", 10);
    data.InsertAt("nodes", 11);
    data.InsertAt("list.", 15);

    data.PrintForward();
    cout << "Node count: " << data.NodeCount() << endl;
}

void TestRecursion()
{
    LinkedList<int> power2;
    int val = 2;
    for (int i = 0; i < 10; i++)
    {
        power2.AddTail(val);
        val *= 2;
    }
    cout << "Initial list: " << endl;
    power2.PrintForward();
    cout << "Printing recursively forward from 64: " << endl;
    LinkedList<int>::Node *node = power2.Find(64);
    power2.PrintForwardRecursive(node);

    cout << "Printing recursively in reverse from 512: " << endl;
    node = power2.Find(512);
    power2.PrintReverseRecursive(node);
}

void MyTest() {

    LinkedList<int> a;
    for(int x = 0; x < 101; x = x + 10) {
        a.AddTail(x);
    }

    LinkedList<int> b = a;

    int c = (b == a) ? 1 : 0;

    std::cout << c;

}