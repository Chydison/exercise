//
//  main.cpp
//  ProjectTree
//
//  Created by 宋春宇 on 2020/11/22.
//

#include <iostream>
#include <dirent.h>
#include <fstream>

using namespace std;

void genDirTree(const char * dir_path, string & out_string, int depth = 0)
{
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
    std::ofstream osWrite(outPath, std::ofstream::app);
    osWrite << outStr;
    osWrite << endl;
    osWrite.close();
    
    return 0;
}
