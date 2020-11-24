//
//  main.cpp
//  ProjectTree
//
//  Created by 宋春宇 on 2020/11/22.
//

#include <iostream>
#include <fstream>


#ifdef _WIN32
#include <io.h>
#else
#include <dirent.h>
#endif

using namespace std;

void genDirTree(const char * dir_path, string & out_string, int depth = 0)
{
#ifdef _WIN32
    _finddata_t FileInfo;
    string strfind = dir_path;
    strfind += "\\*";
    long Handle = _findfirst(strfind.c_str(), &FileInfo);
    if (Handle == -1L)
    {
        cerr << "can not match the folder path : " << strfind << endl;
        exit(-1);
    }
    do {
        string name = FileInfo.name;
        if (name.find_first_of(".") == 0
            || (int)name.find(".xcworkspace") >= 0
            || (int)name.find(".xcodeproj") >= 0
            || name == "build"
            || name == "bin"
            )
        {
            continue;
        }
        //判断是否有子目录
        if (FileInfo.attrib & _A_SUBDIR)
        {
            for (int i = 0; i < depth; ++i)
                out_string += "|  ";
            out_string += "|--" + name + "\n";
            string path = dir_path;
            path += "\\" + name;
            genDirTree(path.c_str(), out_string, depth+1);
        }
    } while (_findnext(Handle, &FileInfo) == 0);

    _findclose(Handle);
#else
    DIR *pDir = NULL;
    if ((pDir = opendir(dir_path)) == NULL)
        printf("open dir failed : %s", dir_path);

    dirent *ptr;
    while (NULL != (ptr = readdir(pDir)))
    {
        string name = ptr->d_name;
        if (name.find_first_of(".") == 0
            || (int)name.find(".xcworkspace") >= 0
            || (int)name.find(".xcodeproj") >= 0
            )
        {
            continue;
        }
        if (ptr->d_type == DT_DIR)
        {
            for(int i = 0; i < depth; ++i)
                out_string += "|  ";
            out_string += "|--" + name + "\n";
            string path = dir_path;
            path += "/" + name;
            genDirTree(path.c_str(), out_string, depth+1);
        }
    }
#endif
}

int main(int argc, const char * argv[]) {
    if (argc < 2)
    {
        printf("need params\n");
        printf("-p or -path : \n");
        return -1;
    }
    string path = "";
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "-path") == 0)
        {
            path = argv[++i];
        }
    }
    if (path == "")
    {
        printf("need param path");
    }

    string outStr = "";
    genDirTree(path.c_str(), outStr);
    printf("%s", outStr.c_str());
    
    string outPath = path+"/ProjectTree.txt";
    ofstream osWrite(outPath, ofstream::trunc);
    osWrite << outStr;
    osWrite << endl;
    osWrite.close();
    printf("success export ProjectTree.txt to %s", outPath.c_str());
    
    return 0;
}
