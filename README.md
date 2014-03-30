Search_Files
============

Return a list of files under a specific directory. 

This function only works under Windows. It returns a list of file names under a directory. 


Sample Usage 
============
Example 1

    vector<wstring> file_name_w = search_file_w(L"*.bmp");

Example 2

    vector<wstring> file_name = search_file_w(L"images/*.bmp");

Example 3

    vector<string> file_name = search_file("*.bmp");

Example 4

    vector<string> file_name = search_file("images/*.bmp");
