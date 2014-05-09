Search_Files
============

Return a list of file names under a specific directory. 

This function only works under Windows. 


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
