#include "database.h"
#include <iostream>
#include <cstring>
Type type;

using namespace std;


int main()
{
Database database; //스택메모리할당으로 해제 안해도됨
init(database);


    while(1)
    {
        
    
        string stype;
        string key;
        string command;
        void* value;
        cout << endl << "command (list, add, get, del, exit): ";
        cin >> command;

        //add 
        if(command == "add")
        {
            cout << "key: ";
            cin >> key;
            cout << "type (int, double, string, array): ";
            cin >> stype;

            if (stype == "int")
            { 
                int* val = new int;
                cout << "value: ";
                cin >> *val;
                value=val;
                type = INT;
            }
            else if (stype == "double")
            { 
                double* val = new double;
                cout << "value: ";
                cin >> *val;
                value=val;
                type = DOUBLE;
            }
            else if (stype == "string")
            { 
                string* val = new string;
                cout << "value: ";
                cin >> *val;
                value=val;
                type = STRING;
            }
            else if (stype == "array") 
            {
            
                cout << "value: ";
                cout << "type (int, double, string, array): ";
                cin >> stype;
                if(stype == "int") type = INT;
                else if(stype == "double") type = DOUBLE;
                else if(stype == "string") type = STRING;
                else if(stype == "array") type = ARRAY;
                Array* arrayValue = createArray(type);
                value = arrayValue;
                type = ARRAY;
                
            }
        

        

        


            int s=1; //중첩여부
            for (int i = 0; i < database.volume; ++i) 
            {
                // 중복된키 확인
                if (database.entries[i]->key == key) 
                {
                    Entry* entry=create(type,key,value);
                    database.entries[i] = entry;
                    s = 0;
                }

            
            }

            if(s=1)
            {
                Entry* entry=create(type,key,value);
                add(database,entry);
            }
            
            
        }



        //모든 key값의 밸류출력
        else if(command == "list")
        {
            for (int i = 0; i < database.volume; ++i) 
            
            {
            
                cout << database.entries[i]->key << ": ";
                
                switch (database.entries[i]->type) 
                {
                    case INT:
                        cout << *static_cast<int*>(database.entries[i]->value) << endl;
                        break;
                    case DOUBLE:
                        cout << *static_cast<double*>(database.entries[i]->value) << endl;
                        break;
                    case STRING:
                        cout << *static_cast<string*>(database.entries[i]->value) << endl;
                        break;
                    case ARRAY:
                        printArray(static_cast<Array*>(database.entries[i]->value));
                        break;
                }
            }

        }


        //key값으로 밸류출력
        else if(command == "get")
        {
            cout << "key: ";
            cin >> key;
            Entry* entry = get(database,key);
            cout << key << ":";

            switch (entry->type) 
            {
            case INT:
                cout << *static_cast<int*>(entry->value) << endl;
                break;
            case DOUBLE:
                cout << *static_cast<double*>(entry->value) << endl;
                break;
            case STRING:
                cout << *static_cast<string*>(entry->value) << endl;
                break;
            case ARRAY:
                printArray(static_cast<Array*>(entry->value));
                break;
            }


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
            exit(0);
        }

        


        else
        {
            cout << "Error";

        }

    
    }


   

}