#include <Windows.h>
#include <stdio.h>
#include <iostream>

// Moves to the first record in a FF1 table
// void TFF1TableFirst();
typedef void(CALLBACK* FF1TableFirstFunc)();

// moves to the next record in a FF1 table
// void TFF1TableNext();
typedef void(CALLBACK* FF1TableNextFunc)();

// retrieves the value of aField into a variant
// int TFF1TableFieldValue(VARIANTARG *pVarg, int aFieldNo);
// int __stdcall FF1TableFieldValue(VARIANTARG *pvarg, int)
typedef int(CALLBACK* FF1TableFieldValueFunc)(VARIANTARG*, int);

// opens a FF1 database
// void TFF1DirOpen(char* aPath);
typedef void(CALLBACK* FF1DirOpenFunc)(const char*);

// opens a FF1 table.
// int TFF1TableOpen(char* aTableName);
typedef int(CALLBACK* FF1TableOpenFunc)(const char*);

// Closes a FF1 table.
// void TFF1TableClose();
typedef void(CALLBACK* FF1TableCloseFunc)();

// Checks if a FF1 table is positioned at the end of file.
//bool TFF1TableEOF();
typedef bool(CALLBACK* FF1TableEOFFunc)();

// Retrieves the record count for a FF1 table
//int TFF1TableRecordCount();
typedef int(CALLBACK* FF1TableRecordCountFunc)();

// retrieves the auto-increment seed
//bool TFF1IsFileBLOB(int aFieldNo, char* aBuffer);
typedef bool(CALLBACK* FF1IsFileBLOBFunc)(int, char*);

FF1TableFirstFunc FF1TableFirstHandle;
FF1TableNextFunc FF1TableNextHandle;
FF1TableFieldValueFunc FF1TableFieldValueHandle;
FF1DirOpenFunc FF1DirOpenHandle;
FF1TableOpenFunc FF1TableOpenHandle;
FF1TableCloseFunc FF1TableCloseHandle;
FF1TableEOFFunc FF1TableEOFHandle;
FF1TableRecordCountFunc FF1TableRecordCountHandle;
FF1IsFileBLOBFunc FF1IsFileBLOBHandle;

void try_initialize() {
	HINSTANCE hDLL;
	hDLL = LoadLibrary(L"ff1intfc.dll");

	if (hDLL == NULL) {
		perror("[FF1Interface] Failed to load the library.");
	}

	FF1TableFirstHandle = (FF1TableFirstFunc)GetProcAddress(hDLL, "FF1TableFirst");
	FF1TableNextHandle = (FF1TableNextFunc)GetProcAddress(hDLL, "FF1TableNext");
	FF1TableFieldValueHandle = (FF1TableFieldValueFunc)GetProcAddress(hDLL, "FF1TableFieldValue");
	FF1DirOpenHandle = (FF1DirOpenFunc)GetProcAddress(hDLL, "FF1DirOpen");
	FF1TableOpenHandle = (FF1TableOpenFunc)GetProcAddress(hDLL, "FF1TableOpen");
	FF1TableCloseHandle = (FF1TableCloseFunc)GetProcAddress(hDLL, "FF1TableClose");
	FF1TableEOFHandle = (FF1TableEOFFunc)GetProcAddress(hDLL, "FF1TableEOF");
	FF1TableRecordCountHandle = (FF1TableRecordCountFunc)GetProcAddress(hDLL, "FF1TableRecordCount");
	FF1IsFileBLOBHandle = (FF1IsFileBLOBFunc)GetProcAddress(hDLL, "FF1IsFileBLOB");

	if (!FF1TableFirstHandle) {
		perror("FF1TableFirst failed.");
		return;
	}
	if (!FF1TableNextHandle) {
		perror("FF1TableNext failed.");
		return;
	}
	if (!FF1TableFieldValueHandle) {
		perror("FF1TableFieldValue failed.");
		return;
	}
	if (!FF1DirOpenHandle) {
		perror("FF1DirOpen failed.");
		return;
	}
	if (!FF1TableOpenHandle) {
		perror("FF1TableOpen failed.");
		return;
	}
	if (!FF1TableEOFHandle) {
		perror("FF1TableEOF failed.");
		return;
	}
	if (!FF1TableRecordCountHandle) {
		perror("FF1TableRecordCount failed.");
		return;
	}
	if (!FF1IsFileBLOBHandle) {
		perror("FF1IsFileBLOB failed.");
		return;
	}
}

// Moves to the first record in a FF1 table.
extern "C" __declspec(dllexport) void FF1TableFirst() {
	FF1TableFirstHandle();
}

// Moves to the next record ina FF1 table.
extern "C" __declspec(dllexport) void FF1TableNext() {
	FF1TableNextHandle();
}

// Get the boolean value of a field in the current record.
extern "C" __declspec(dllexport) int FF1TableFieldValueBool(bool* value, int fieldNo) {
	VARIANTARG serieId;
	int r = FF1TableFieldValueHandle(&serieId, fieldNo);
	*value = (bool)serieId.boolVal;
	return r;
}
// Get the short value of a field in the current record.
extern "C" __declspec(dllexport) int FF1TableFieldValueShort(short* value, int fieldNo) {
	VARIANTARG serieId;
	int r = FF1TableFieldValueHandle(&serieId, fieldNo);
	*value = (short)serieId.iVal;
	return r;
}
// Get the ushort value of a field in the current record.
extern "C" __declspec(dllexport) int FF1TableFieldValueUShort(unsigned short* value, int fieldNo) {
	VARIANTARG serieId;
	int r = FF1TableFieldValueHandle(&serieId, fieldNo);
	*value = (unsigned short)serieId.uiVal;
	return r;
}
// Get the int value of a field in the current record.
extern "C" __declspec(dllexport) int FF1TableFieldValueInt(int* value, int fieldNo) {
	VARIANTARG serieId;
	int r = FF1TableFieldValueHandle(&serieId, fieldNo);
	*value = (int)serieId.intVal;
	return r;
}
// Get the uint value of a field in the current record.
extern "C" __declspec(dllexport) int FF1TableFieldValueUInt(unsigned int* value, int fieldNo) {
	VARIANTARG serieId;
	int r = FF1TableFieldValueHandle(&serieId, fieldNo);
	*value = (unsigned int)serieId.uintVal;
	return r;
}
// Get the long value of a field in the current record.
extern "C" __declspec(dllexport) int FF1TableFieldValueLong(long* value, int fieldNo) {
	VARIANTARG serieId;
	int r = FF1TableFieldValueHandle(&serieId, fieldNo);
	*value = (long)serieId.lVal;
	return r;
}
// Get the ulong value of a field in the current record.
extern "C" __declspec(dllexport) int FF1TableFieldValueULong(unsigned long* value, int fieldNo) {
	VARIANTARG serieId;
	int r = FF1TableFieldValueHandle(&serieId, fieldNo);
	*value = (unsigned long)serieId.ulVal;
	return r;
}
// Get the float value of a field in the current record.
extern "C" __declspec(dllexport) int FF1TableFieldValueFloat(float* value, int fieldNo) {
	VARIANTARG serieId;
	int r = FF1TableFieldValueHandle(&serieId, fieldNo);
	*value = (float)serieId.fltVal;

	// printf("wat %d, %d, %d, %d\n", (int)serieId.pcVal[0], (int)serieId.pcVal[1], (int)serieId.pcVal[2], (int)serieId.pcVal[3]);

	printf("%f\n", serieId.dblVal);

	return r;
}
// Get the double value of a field in the current record.
extern "C" __declspec(dllexport) int FF1TableFieldValueDouble(double* value, int fieldNo) {
	VARIANTARG serieId;
	int r = FF1TableFieldValueHandle(&serieId, fieldNo);
	*value = (double)serieId.dblVal;
	return r;
}
// Get the char value of a field in the current record.
extern "C" __declspec(dllexport) int FF1TableFieldValuePChar(char* value, int fieldNo) {
	VARIANTARG serieId;
	int r = FF1TableFieldValueHandle(&serieId, fieldNo);
	*value = (char)serieId.cVal;
	return r;
}
// Get the string value of a field in the current record.
extern "C" __declspec(dllexport) int FF1TableFieldValuePPChar(char** value, int fieldNo) {
	VARIANTARG serieId;
	int r = FF1TableFieldValueHandle(&serieId, fieldNo);
	*value = (char*)serieId.pcVal;
	return r;
}

// Opens a FF1 database.
extern "C" __declspec(dllexport) void FF1DirOpen(char* directory) {
	FF1DirOpenHandle(directory);
}

// Opens a FF1 table.
extern "C" __declspec(dllexport) int FF1TableOpen(char* tableName) {
	return FF1TableOpenHandle(tableName);
}

// Closes the current FF1 table.
extern "C" __declspec(dllexport) void FF1TableClose() {
	FF1TableCloseHandle();
}

// Checks if we have reached the end of the current FF1 table.
extern "C" __declspec(dllexport) bool FF1TableEOF() {
	if (FF1TableEOFHandle()) return true;
	return false;
}

// Get the number of records in the current FF1 table.
extern "C" __declspec(dllexport) int FF1TableRecordCount() {
	return FF1TableRecordCountHandle();
}

// Determines if a BLOB Field is a file BLOB. If so, it copies the file name into buffer.
extern "C" __declspec(dllexport) bool FF1IsFileBLOB(int fieldNo, char* buffer) {
	return FF1IsFileBLOBHandle(fieldNo, buffer);
}

BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,  // handle to DLL module
	DWORD fdwReason,     // reason for calling function
	LPVOID lpReserved)  // reserved
{
	// Perform actions based on the reason for calling.
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		try_initialize();
		break;

	case DLL_THREAD_ATTACH:
		// Do thread-specific initialization.
		break;

	case DLL_THREAD_DETACH:
		// Do thread-specific cleanup.
		break;

	case DLL_PROCESS_DETACH:
		// Perform any necessary cleanup.
		break;
	}
	return TRUE;  // Successful DLL_PROCESS_ATTACH.
}
