#include <crtdbg.h>
#include <Windows.h>
#include <cassert>
#include <iostream>

#include "DoublyLinkedList.h"

#define _CRTDBG_MAP_ALLOC

const size_t GREEN = 10;
const size_t RED = 12;
const size_t WHITE = 23;
static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void RunTests();
void PrintTestHeader(const char * testName);
void PrintTestPass(const char * test);
void PrintTestFail(const char * test, const char * message);
void TestingConstructor();
void TestingCopyConstructor();
void TestingAssignmentOperator();
void TestingIsEmpty();
void TestingFirst();
void TestingLast();
void TestingPrepend();
void TestingAppend();
void TestingPurge();
void TestingExtract();
void TestingInsertAfter();
void TestingInsertBefore();

int main()
{
	RunTests();

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks();

	system("pause");
	return 0;
}

void RunTests()
{
	TestingConstructor();
	TestingCopyConstructor();
	TestingAssignmentOperator();
	TestingIsEmpty();
	TestingFirst();
	TestingLast();
	TestingPrepend();
	TestingAppend();
	TestingPurge();
	TestingExtract();
	TestingInsertAfter();
	TestingInsertBefore();
}

void PrintTestHeader(const char * testName)
{
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << "\n********** " << testName << " **********" << std::endl;
}

void PrintTestPass(const char * test)
{
	SetConsoleTextAttribute(hConsole, GREEN);
	std::cout << '\t' << test << ": TEST PASS" << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
}

void PrintTestFail(const char * test, const char * message)
{
	SetConsoleTextAttribute(hConsole, RED);
	std::cerr << message << std::endl;
	std::cerr << '\t' << test << ": TEST FAIL" << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
}

void TestingConstructor()
{
	const char * test = "Constructor";
	PrintTestHeader(test);

	DoublyLinkedList<int> list_1;

	assert(list_1.getHead() == nullptr);
	assert(list_1.getTail() == nullptr);

	PrintTestPass(test);
}

void TestingCopyConstructor()
{
	const char * test = "Copy constructor";
	PrintTestHeader(test);

	DoublyLinkedList<int> list_1;
	list_1.Append(5);
	list_1.Prepend(7);

	DoublyLinkedList<int> duplicate_list(list_1);
	assert(duplicate_list.First() == list_1.First());
	assert(duplicate_list.Last() == list_1.Last());

	PrintTestPass(test);
}

void TestingAssignmentOperator()
{
	const char * test = "Assignment operator";
	PrintTestHeader(test);

	DoublyLinkedList<int> list_1;
	list_1.Append(5);
	list_1.Prepend(7);

	DoublyLinkedList<int> duplicate_list = list_1;

	assert(duplicate_list.First() == list_1.First());
	assert(duplicate_list.Last() == list_1.Last());

	PrintTestPass(test);
}

void TestingIsEmpty()
{
	const char * test = "IsEmpty";
	PrintTestHeader(test);

	DoublyLinkedList<int> list_1;
	assert(list_1.isEmpty() == true);

	list_1.Append(5);
	assert(list_1.isEmpty() == false);

	PrintTestPass(test);
}

void TestingFirst()
{
	const char * test = "First";
	PrintTestHeader(test);

	try
	{
		DoublyLinkedList<int> list_1;
		list_1.Append(5);
		list_1.Prepend(7);

		assert(list_1.First() == 7);
		PrintTestPass(test);
	}
	catch (const char * message)
	{
		PrintTestFail(test, message);
	}
}

void TestingLast()
{
	const char * test = "Last";
	PrintTestHeader(test);

	try
	{
		DoublyLinkedList<int> list_1;
		list_1.Append(5);
		list_1.Prepend(7);

		assert(list_1.Last() == 5);
		PrintTestPass(test);
	}
	catch (const char * message)
	{
		PrintTestFail(test, message);
	}
}

void TestingPrepend()
{
	const char * test = "Prepend";
	PrintTestHeader(test);

	try
	{
		DoublyLinkedList<int> list_1;
		list_1.Append(7);
		list_1.Prepend(2);

		assert(list_1.First() == 2);
		PrintTestPass(test);
	}
	catch (const char * message)
	{
		PrintTestFail(test, message);
	}
}

void TestingAppend()
{
	const char * test = "Append";
	PrintTestHeader(test);

	try
	{
		DoublyLinkedList<int> list_1;
		list_1.Prepend(8);
		list_1.Append(4);

		assert(list_1.Last() == 4);
		PrintTestPass(test);
	}
	catch (const char * message)
	{
		PrintTestFail(test, message);
	}
}

void TestingPurge()
{
	const char * test = "Purge";
	PrintTestHeader(test);

	try
	{
		DoublyLinkedList<int> list_1;
		list_1.Append(7);
		list_1.Prepend(2);
		list_1.Purge();

		assert(list_1.getHead() == nullptr);
		assert(list_1.getTail() == nullptr);
		PrintTestPass(test);
	}
	catch (const char * message)
	{
		PrintTestFail(test, message);
	}
}

void TestingExtract()
{
	const char * test = "Extract";
	PrintTestHeader(test);

	try
	{
		DoublyLinkedList<int> list_1;
		list_1.Append(3);
		list_1.Append(5);
		list_1.Append(7);
		list_1.Append(9);

		list_1.Extract(9);
		assert(list_1.Last() == 7);

		list_1.Extract(3);
		assert(list_1.First() == 5);

		PrintTestPass(test);
	}
	catch (const char * message)
	{
		PrintTestFail(test, message);
	}
}

void TestingInsertAfter()
{
	const char * test = "Insert After";
	PrintTestHeader(test);

	try
	{
		DoublyLinkedList<int> list_1;
		list_1.Append(5);

		// Insert 8 after 5
		list_1.InsertAfter(5, 8);

		assert(list_1.Last() == 8);
		PrintTestPass(test);
	}
	catch (const char * message)
	{
		PrintTestFail(test, message);
	}
}

void TestingInsertBefore()
{
	const char * test = "Insert Before";
	PrintTestHeader(test);

	try
	{
		DoublyLinkedList<int> list_1;
		list_1.Append(5);

		// Insert 2 before 5
		list_1.InsertBefore(5, 2);

		assert(list_1.First() == 2);
		PrintTestPass(test);
	}
	catch (const char * message)
	{
		PrintTestFail(test, message);
	}
}