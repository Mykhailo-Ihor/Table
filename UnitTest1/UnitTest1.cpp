#include "pch.h"
#include "CppUnitTest.h"
#include "..\Table\main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TableUnitTest
{
    TEST_CLASS(TableTest)
    {
    public:
        TEST_METHOD(TestSetValue)
        {
            Table<std::string, int> table;
            table.setValue("1", 5);
            Assert::AreEqual(5, table.getValue("1"));
        }

        TEST_METHOD(TestGetValue)
        {
            Table<std::string, int> table;
            table.setValue("1", 5);
            Assert::AreEqual(5, table.getValue("1"));
        }

        TEST_METHOD(TestRemoveValue)
        {
            Table<std::string, int> table;
            table.setValue("1", 5);
            table.removeValue("1");
            Assert::ExpectException<std::out_of_range>([&] { table.getValue("1"); });
        }

        TEST_METHOD(TestPrint)
        {
            Table<std::string, int> table;
            table.setValue("1", 5);
            table.setValue("2", 3);
            table.setValue("3", 7);

            std::ostringstream output;

            table.print(output);

            Assert::AreEqual(std::string("3: 7\n2: 3\n1: 5\n"), output.str());
        }
    };
}