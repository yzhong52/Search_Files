#ifndef _SEARCH_FILE_H
#define _SEARCH_FILE_H

#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std; 


/* Search files by file name 
 * 
 * Created by Yuchen on Nov 17th, 2012. 
 * Last modified by Yuchen on Apr 22th, 2013. 
 * 
 * Exmaple 1: Basic Usage
	vector<wstring> file_name_w = search_file_w(L"*.bmp");
 * Example 2: Search within a folder
	vector<wstring> file_name = search_file_w(L"images/*.bmp");
 */
inline vector<wstring> search_file_w(LPCTSTR lpFileName){
	vector<wstring> file_names;// result will be put in this vector

	// Get folder name (if there is any)
	wstring folder_name( lpFileName );
	size_t pos = folder_name.find_last_of('/');
	if( pos != string::npos ) {
		folder_name.erase(pos+1);
	} else {
		folder_name = L"";
	}

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	
	// Find the first file in the directory.
	hFind = FindFirstFile(lpFileName, &FindFileData);
	
	if( hFind == INVALID_HANDLE_VALUE ){
		wstring error(L"File '"); 
		error += lpFileName;
		error += L"' Not Found!";
		wcout << error.c_str() << endl;
	} else { //At lease one file is found. 
		do { 
			// skip "." and ".." if there are any
			if( wcscmp( FindFileData.cFileName, L"." )==0 ) continue;
			if( wcscmp( FindFileData.cFileName, L".." )==0 ) continue;
			// copy the data
			file_names.push_back( folder_name+FindFileData.cFileName );
		} while ( FindNextFile( hFind, &FindFileData) != 0 );
	}
	return file_names;
}


/* The non-wide-char version of the above function
 * 
 * Created by Yuchen on Nov 17th, 2012. 
 * Last modified by Yuchen on Apr 22th, 2013. 
 * 
 * Exmaple 1: Basic Usage
	vector<string> file_name = search_file("*.bmp");
 * Example 2: Search within a folder
	vector<string> file_name = search_file("images/*.bmp");
 */
inline vector<string> search_file(const char* pFileName){	
	vector<string> file_names; // result will be put in this vector

	// Get folder name (if there is any)
	string folder_name( pFileName );
	size_t pos = folder_name.find_last_of('/');
	if( pos != string::npos ) {
		folder_name.erase(pos+1);
	} else {
		folder_name = "";
	}

	// Convert the pFileName to wide char
	size_t returnValue; 
	const size_t sizeInWords = 160; 
	wchar_t FileName_w[sizeInWords];
	errno_t err = EINVAL;
	size_t count = strlen(pFileName);
	// returnValue: The number of characters converted.
	// FileName_w: Address of buffer for the resulting converted wide character string
	err = mbstowcs_s( &returnValue, FileName_w, sizeInWords, pFileName, count );
	if( err==ERANGE || returnValue!=count+1 ){
		cout << "The destination buffer is too small to contain the converted string." << endl;
		getchar(); exit(1);
	}
	
	// Find the first file in the directory.
	char buffer[250];
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	size_t i, maxLength;
	hFind = FindFirstFile(FileName_w, &FindFileData);
	if( hFind == INVALID_HANDLE_VALUE ){
		wstring error(L"File '"); 
		error += FileName_w;
		error += L"' Not Found!";
		wcout << error.c_str() << endl;
	} 
	else{ 
		do { 
			maxLength = wcslen( FindFileData.cFileName ) + 1;
			// skip "." and ".." if there are any
			if( wcscmp( FindFileData.cFileName, L"." )==0 ) continue;
			if( wcscmp( FindFileData.cFileName, L".." )==0 ) continue;
			// copy the data
			for( i=0; i< maxLength; i++ ){
				if( FindFileData.cFileName[i] >=0 && FindFileData.cFileName[i] <= 255 ){
					// ensure that the file name does not contain wide char. 
					buffer[i] = (char) FindFileData.cFileName[i];
				}
				else{
					cout << "Error: Encounter wide char in file name. ";
					cout << "Please use the wide char version of this function" << endl;
					file_names.clear();
					return file_names;
				}
			}
			buffer[i] = '\0';
			file_names.push_back( folder_name+buffer );
		} while ( FindNextFile(hFind, &FindFileData) != 0 );
	}
	
	return file_names;
}
#endif


// Complete Examples: main.cpp
//int main (int argc, char *argv[]) { 
//	vector<wstring> file_name_w = search_file_w(L"*.bmp");
//	vector<wstring>::iterator it;
//	for( it = file_name_w.begin(); it < file_name_w.end(); ++it ) 
//		wcout << (*it).c_str() << endl;
//	
//	vector<string> file_name = search_file("*.bmp");
//	vector<string>::iterator it2;
//	for( it2 = file_name.begin(); it2 < file_name.end(); ++it2 ) 
//		cout << (*it2).c_str() << endl;
//
//	return 0; 
//}
