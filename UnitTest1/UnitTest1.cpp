#include "pch.h"
#include "CppUnitTest.h"
#include "..\Table\main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TableUnitTest
{
    TEST_CLASS(HashTableTests)
    {
    public:

        TEST_METHOD(TestAdd)
        {
            HashTable<std::string> hashTable;
            hashTable.add(1, "Value1");
            hashTable.add(2, "Value2");
            hashTable.add(3, "Value3");

            Assert::AreEqual("Value1", hashTable.getValue(1).c_str());
            Assert::AreEqual("Value2", hashTable.getValue(2).c_str());
            Assert::AreEqual("Value3", hashTable.getValue(3).c_str());
        }

        TEST_METHOD(TestRemove)
        {
            HashTable<std::string> hashTable;
            hashTable.add(1, "Value1");
            hashTable.add(2, "Value2");
            hashTable.add(3, "Value3");

            hashTable.remove(2);

            Assert::ExpectException<std::exception>([&hashTable] { hashTable.getValue(2); });
        }

        TEST_METHOD(TestGetValue)
        {
            HashTable<std::string> hashTable;
            hashTable.add(1, "Value1");
            hashTable.add(2, "Value2");
            hashTable.add(3, "Value3");

            Assert::AreEqual("Value1", hashTable.getValue(1).c_str());
            Assert::AreEqual("Value2", hashTable.getValue(2).c_str());
            Assert::AreEqual("Value3", hashTable.getValue(3).c_str());
        }
        TEST_METHOD(TestPrint)
        {
            HashTable<std::string> hashTable;
            hashTable.add(1, "Value1");
            hashTable.add(2, "Value2");
            hashTable.add(3, "Value3");

            std::stringstream expectedOutput;
            expectedOutput << "Bucket 0:\nTable is empty\n" << std::endl;
            expectedOutput << "Bucket 1:\n1: Value1 | " << std::endl;
            expectedOutput << "Bucket 2:\n2: Value2 | " << std::endl;
            expectedOutput << "Bucket 3:\n3: Value3 | " << std::endl;
            expectedOutput << "Bucket 4:\nTable is empty\n" << std::endl;
            expectedOutput << "Bucket 5:\nTable is empty\n" << std::endl;
            expectedOutput << "Bucket 6:\nTable is empty\n" << std::endl;
            expectedOutput << "Bucket 7:\nTable is empty\n" << std::endl;
            expectedOutput << "Bucket 8:\nTable is empty\n" << std::endl;
            expectedOutput << "Bucket 9:\nTable is empty\n" << std::endl;
            std::stringstream outputStream;
            hashTable.print(outputStream);
            Assert::AreEqual(expectedOutput.str(), outputStream.str());
        }
    };
}