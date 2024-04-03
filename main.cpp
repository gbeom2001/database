#include "database.h"
#include <iostream>
#include <cstring>

using namespace std;


void main()
{
Database database;
init(database);
while(1)
{
    Type type;
    string stype;
    string key;
    string command;
    void* value;
    cout << "command (list, add, get, del, exit): ";
    cin >> command;

    if(command == "add")
    {
        cout << "key: ";
        cin >> key;
        cout << "type (int, double, string, array): ";
        cin >> stype;

        if (stype == "int")
        { 
            int val;
            cout << "value: ";
            cin >> val;
            value=&val;
            Type type = INT;
        }
        else if (stype == "double")
        { 
            double val;
            cout << "value: ";
            cin >> val;
            value=&val;
            Type type = DOUBLE;
        }
        else if (stype == "string")
        { 
            string val;
            cout << "value: ";
            cin >> val;
            value=&val;
            Type type = STRING;
        }
        else if (stype == "array")
        {   
          addarray();
        }



        for (int i = 0; i < database.volume; ++i) 
        {
            // 중복된키 확인
            if (database.entries[i]->key == key) 
            {
                Entry* entry=create(type,key,value);
                database.entries[i] = entry;
            }

        }
        Entry* entry=create(type,key,value);
        add(database,entry);

    }



    //모든 key값의 밸류출력
    else if(command == "list")
    {
        for (int i = 0; i < database.volume; ++i) 
        
        {
        
            cout << database.entries[i]->key << ": ";
            cout << database.entries[i]->value << endl;
        }
    }


    //key값으로 밸류출력
    else if(command == "get")
    {
        cout << "key: ";
        cin >> key;
        Entry* entry = get(database,key);
        cout << key << ":" << entry->value;
    }



    //제거
    else if(command == "del")
    {
        cout << "key: ";
        cin >> key;
        remove(database,key);
    }



    //메모리 해제후 프로그램종료
    else if(command == "exit")
    {
        destroy(database);
        break;
    }

    


    else
    {
        cout << "Error";

    }

}



}