#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <iostream>
#include <cstring>


using namespace std;


enum Type { INT, DOUBLE, STRING, ARRAY };

struct Array {
  int size;
  Type type;
  void** items;
};

struct Entry {
  Type type;
  std::string key;
  void *value;
};

struct Database {
  Entry** entries; // Entry 포인터 배열을 가리키는 포인터
  int volume;
  
};


Array* createArray(Type atype) {
    Array* newArray = new Array;
    cout << "size: ";
    cin >> newArray->size;
    newArray->type = atype;  // 배열의 타입 설정
    newArray->items = new void*[newArray->size];  // 배열 항목들을 위한 메모리 할당

    for (int i = 0; i < newArray->size; ++i) {

        if(atype != ARRAY) cout << "item[" << i << "]: ";
        switch (atype) {
            case INT: {
                int* intValue = new int;
                cin >> *intValue;
                newArray->items[i] = intValue;
                break;
            }
            case DOUBLE: {
                double* doubleValue = new double;
                cin >> *doubleValue;
                newArray->items[i] = doubleValue;
                break;
            }
            case STRING: {
                string* stringValue = new string;
                cin >> *stringValue;
                newArray->items[i] = stringValue;
                break;
            }
            case ARRAY: {
              Type artype;
                cout << "item[" << i << "]: type (int, double, string, array): " ;
                string nextType;
                cin >> nextType;
                if(nextType == "int") artype = INT;
                else if(nextType == "double") artype = DOUBLE;
                else if(nextType == "string") artype = STRING;
                else if(nextType == "array") artype = ARRAY;
                newArray->items[i] = createArray(artype);
                break;
            }
          
        }
    }

    return newArray;
}

// 엔트리를 생성한다.
Entry *create(Type type, std::string key, void *value)
{
  Entry *newEntry = new Entry; //entry 구조체를 동적으로 할당

  newEntry->type = type;
  newEntry->key = key;
  newEntry->value = value;

  return newEntry;
}

// 데이터베이스를 초기화한다.
void init(Database &database)
{
  database.entries = nullptr;
  database.volume = 0;

}

// 데이터베이스에 엔트리를 추가한다.
void add(Database &database, Entry *entry)
{
    Entry** newEntries = new Entry*[database.volume + 1]; // 새로운 배열 생성
    for (int i = 0; i < database.volume; ++i) {
        newEntries[i] = database.entries[i]; // 기존 엔트리들을 새 배열로 복사
    }
    newEntries[database.volume] = entry; // 새 엔트리 추가

    delete[] database.entries; // 기존 배열 해제
    database.entries = newEntries; // 새 배열 할당
    database.volume++; // 데이터베이스의 크기 증가
}


// 데이터베이스에서 키에 해당하는 엔트리를 찾는다.
Entry *get(Database &database, std::string &key)
{
  for (int i = 0; i < database.volume; ++i) 
  {
        // 현재 엔트리의 키와 주어진 키를 비교
        if (database.entries[i]->key == key) 
        {
            key = database.entries[i]->key;
            return database.entries[i];
        }
  }
}

// 데이터베이스에서 키에 해당하는 엔트리를 제거한다.
void remove(Database &database, std::string &key)
{
  for (int i = 0; i < database.volume; ++i) 
    {
        if (database.entries[i]->key == key) 
        {
            // 찾은 엔트리를 삭제
            delete database.entries[i];
            database.volume--;

            // 삭제한 엔트리 뒤의 엔트리들을 앞으로 당겨옴
            for (int j = i; j < database.volume; ++j) 
            {
                database.entries[j] = database.entries[j + 1];
            }
            
            return;
        }
    }
}

//배열안의 항목해제
void destroyArray(Array* array) 
{
    for (int i = 0; i < array->size; ++i) 
    {
        if (array->type == INT) //배열의 메모리 해제를 위해 타입을 void에서 바꿈
        {
            delete static_cast<int*>(array->items[i]);
        } else if (array->type == DOUBLE) {
            delete static_cast<double*>(array->items[i]);
        } else if (array->type == STRING) {
            delete static_cast<string*>(array->items[i]);
        } else if (array->type == ARRAY) {
            destroyArray(static_cast<Array*>(array->items[i]));
        }
    }
    delete[] array->items; // items배열해제
    delete array; //구조체 해제
}

// 데이터베이스를 해제한다.
void destroy(Database &database)
{
 for (int i = 0; i < database.volume; ++i) {
        Entry* entry = database.entries[i]; // database.entries[i]를 entry에 할당해 삭제
      if (entry->type == INT) //메모리 해제를 위해 타입을 void에서 바꿈
    {
            delete static_cast<int*>(entry->value);
        } else if (entry->type == DOUBLE) {
            delete static_cast<double*>(entry->value);
        } else if (entry->type == STRING) {
            delete static_cast<string*>(entry->value);
        } else if (entry->type == ARRAY) {
            destroyArray(static_cast<Array*>(entry->value)); //void를 array형으로 바꿈
        }
        delete entry;
    }
       
    
    delete[] database.entries; // 전체 entries 배열을 해제
    
   
}





//배열 출력
void printArray(Array* newArray) 
{
  
    
    cout << "[";
    for (int i = 0; i < newArray->size; ++i) {
        if (i > 0) cout << ", ";
        switch (newArray->type) {
            case INT:
                cout << *(static_cast<int*>(newArray->items[i]));
                break;
            case DOUBLE:
                cout << *(static_cast<double*>(newArray->items[i]));
                break;
            case STRING:
                cout << *(static_cast<string*>(newArray->items[i]));
                break;
            case ARRAY:
                printArray(static_cast<Array*>(newArray->items[i]));
                break;
        }
    }
    cout << "]";
}


#endif

