Search_Files
============

Return a list of files under a specific directory. 

This function only works under Windows. It returns a list of file names under a directory. 


    vector<wstring> file_name_w = search_file_w(L"*.bmp");
    vector<wstring> file_name = search_file_w(L"images/*.bmp");
    vector<string> file_name = search_file("*.bmp");
    vector<string> file_name = search_file("images/*.bmp");
