#ifndef DATABASE_H
#define DATABASE_H

#include <string>

enum Type { INT, DOUBLE, STRING, ARRAY };

struct Array {
  int size;
  Type type;
  void *items;
};

struct Entry {
  Type type;
  std::string key;
  void *value;
};

struct Database {
  Entry** entries; // Entry 포인터 배열을 가리키는 포인터
  int volume;
  Array** arrays;
};



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
    database.entries[database.volume] = entry;
    database.volume++; // 데이터베이스의 크기를 증가시킴
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

// 데이터베이스를 해제한다.
void destroy(Database &database)
{
  for (int i = 0; i < database.volume; ++i) 
  {
    delete database.entries[i];
  }
    delete[] database.entries;
}

Array *addarray()
{
  Array *array = new Array;
  array -> type = ARRAY;
  string stype;

  cout << "type(int, double, string, array:) ";
  cin >> stype;

  int size;

   if (stype == "array")

    {

        cout << "size: ";
        cin >> size;
        array->size=size;

        addarray();
       
    }

    else if (stype == "int")

    {

        array->type = INT;

        cout << "size: ";
        cin >> size;
        array->size=size;


    }

    else if (stype == "double")

    {

        array->type = DOUBLE;

        cout << "size: ";
        cin >> size;
        array->size=size;

    }

    else if (stype == "string")

    {

       array->type = STRING;

        cout << "size: ";
        cin >> size;
        array->size=size;
    }

}

#endif

