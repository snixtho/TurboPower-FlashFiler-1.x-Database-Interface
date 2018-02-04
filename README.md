# TurboPower-FlashFiler-1.x-Database-Interface
You have the converter which you can use to convert ff1 tables to ff2 tables, and it is definitely recommended to use ff2 tables instead if you were to use this old database system. However, some programs use the very old ff1 database system and it is tedious to convert to ff2 and since it is coded in delphi, it is not always as easy to use the ff2 libraries. So mainly because of a project of my own, I managed to figure out how reading of ff1 database tables work and created a c++ interface library that works for both c/c++ and c#.

**NOTE**: This is completely unofficial and I am not related to the original authors of FlashFiler (by TurboPower) in any way.

The interface is tested and should work both in C/C++ and C#. Look below for usage.

# Usage/Documentation
This interface is very much like the original one, however some functions are changed a bit mainly due to compatability reasons.

## Open a database
```cpp
void FF1DirOpen(char* directory);
```

## Open a table
```cpp
int FF1TableOpen(char* tableName);
```
| Returns | Non-zero if the table failed to open. |
|-|-|

## Close a table
```cpp
void FF1TableClose();
```

## Get number of records in the current table.
```cpp
int FF1TableRecordCount();
```
| Returns | Number of records in the table. |
|-|-|

## Go to the first record in the current table.
```cpp
void FF1TableFirst();
```

## Go to the next record in the current table.
```cpp
void FF1TableNext();
```

## Check whether we are at the end of the table.
```cpp
bool FF1TableEOF();
```
| Returns | True if the program has reached the end of the table, false if not. |
|-|-|

## Check if a field in the current table is a BLOB.
```cpp
bool FF1IsFileBLOB(int fieldNo, char* buffer);
```
| Parameter | Description|
|-|-|
| fieldNo | The index of the field to read. |
| buffer | If the current field is a BLOB, the file name of this BLOB is written to this parameter. |

| Returns | True if field is a BLOB, false if not. |
|-|-|

## Read the value of a field in the current table.
```cpp
// read boolean
int FF1TableFieldValueBool(bool* value, int fieldNo);

// read short
int FF1TableFieldValueShort(short* value, int fieldNo);

// read unsigned short
int FF1TableFieldValueUShort(unsigned short* value, int fieldNo);

// read integer
int FF1TableFieldValueInt(int* value, int fieldNo);

// read unsigned integer
int FF1TableFieldValueUInt(unsigned int* value, int fieldNo);

// read long
int FF1TableFieldValueLong(long* value, int fieldNo);

// read unsigned long
int FF1TableFieldValueULong(unsigned long* value, int fieldNo);

// read float
int FF1TableFieldValueFloat(float* value, int fieldNo);

// read double
int FF1TableFieldValueDouble(double* value, int fieldNo);

// read char/byte
int FF1TableFieldValuePChar(char* value, int fieldNo);

// read string
int FF1TableFieldValuePPChar(char** value, int fieldNo);
```
| Parameter | Description|
|-|-|
| value | The value of the field is written to this parameter. |
| fieldNo | The index of the field to read from. |

| Returns | Unknown at this point. |
|-|-|

# Examples
The process of opening a database table and reading from it is pretty much identical to using the original interface.

## C++ Example
Make sure you link the dll file first before compiling obviously.
The following example retrieves a string from a specific field in a database table.
```cpp
#include <iostream>
#include <Windows.h>

typedef char*(CALLBACK* GetStrFunc)();

extern "C" void FF1TableFirst();
extern "C" int FF1TableFieldValuePPChar(char** value, int fieldNo);
extern "C" void FF1DirOpen(char* directory);
extern "C" int FF1TableOpen(char* tableName);
extern "C" void FF1TableClose();
extern "C" bool FF1TableEOF();

int main() {
	using namespace std;

	FF1DirOpen("databse_directory");
	
	if (FF1TableOpen("TableName") != 0) {
		cout << "Failed to open table" << endl;
		return 0;
	}

	FF1TableFirst();

	if (FF1TableEOF()) {
		cout << "No records in this table." << endl;
	}

	char* str;
	FF1TableFieldValuePPChar(&str, 3); // get a string from field at index 3.

	cout << "Retrieved string: " << str << endl;

	FF1TableClose();

	return 0;
}
```

## C# Example
The following C# program reads from a database made by an electronic shooting target system. It iterates through all the records in the table the contains all recorded shots and finds the number of shots with the highest score.

```csharp
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace flashfiler1_reading_the_db_csharp {
    class Program {

        [DllImport("FF1Interface.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void FF1TableFirst();

        [DllImport("FF1Interface.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void FF1TableNext();

        [DllImport("FF1Interface.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int FF1TableFieldValuePPChar(ref IntPtr value, int fieldNo);
        // Opens a FF1 database.
        [DllImport("FF1Interface.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void FF1DirOpen([MarshalAs(UnmanagedType.LPStr)]string directory);

        // Opens a FF1 table.
        [DllImport("FF1Interface.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int FF1TableOpen([MarshalAs(UnmanagedType.LPStr)]string tableName);

        // Closes the current FF1 table.
        [DllImport("FF1Interface.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void FF1TableClose();

        // Checks if we have reached the end of the current FF1 table.
        [DllImport("FF1Interface.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool FF1TableEOF();

        // Get the number of records in the current FF1 table.
        [DllImport("FF1Interface.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int FF1TableRecordCount();

        static void Main(string[] args) {

            FF1DirOpen(@"TargetSystemDB");

            if (FF1TableOpen("SkuddData") != 0) {
                Console.WriteLine("Failed to open table.");
                return;
            }
			
			Console.WriteLine("There are " + FF1TableRecordCount() + " recorded shot(s) in this table.");

            FF1TableFirst();

            int c = 0;
            while (!FF1TableEOF()) {
                IntPtr scoreP = IntPtr.Zero;
                FF1TableFieldValuePPChar(ref scoreP, 3);

                string score = Marshal.PtrToStringAnsi(scoreP).Trim();

                if (score == "*.9") {
                    c++;
                }

                FF1TableNext();
            }

            Console.WriteLine("There are " + c + " shot(s) that have the highest score of *.9");
            
            FF1TableClose();
        }
    }
}

```

# Credits
- [snixtho](https://github.com/snixtho) (me)
- [TNTworks](https://github.com/TNTworks)
