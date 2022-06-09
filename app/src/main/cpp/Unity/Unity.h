//
// Created by letha on 6/9/2020.
//
// credits to schmoo and caoyin for the structs
#ifndef IMGUIANDROID_UNITY_H
#define IMGUIANDROID_UNITY_H

#include <codecvt>

/*
This struct can hold a native C# array. Credits to caoyin.
Think of it like a wrapper for a C array. For example, if you had Player[] players in a dump,
the resulting monoArray definition would be monoArray<void **> *players;
To get the C array, call getPointer.
To get the length, call getLength.
*/
template <typename T>
struct monoArray
{
    void* klass;
    void* monitor;
    void* bounds;
    int   max_length;
    void* vector [1];
    int getLength()
    {
        return max_length;
    }
    T getPointer()
    {
        return (T)vector;
    }
};

/*
This struct represents a C# string. Credits to caoyin.
It is pretty straight forward. If you have this in a dump,
public class Player {
	public string username; // 0xC8
}
getting that string would look like this: monoString *username = *(monoString **)((uint64_t)player + 0xc8);
C# strings are UTF-16. This means each character is two bytes instead of one.
To get the length of a monoString, call getLength.
To get a NSString from a monoString, call toNSString.
To get a std::string from a monoString, call toCPPString.
To get a C string from a monoString, call toCString.
*/
typedef struct _monoString
{
    void *klass;
    void *monitor;
    int length;
    char chars[1];

    int getLength()
    {
        return length;
    }

    char *getRawChars()
    {
        return chars;
    }

    std::string getString()
    {
        std::u16string u16string(reinterpret_cast<const char16_t *>(chars));
        std::wstring wstring(u16string.begin(), u16string.end());
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;

        return convert.to_bytes(wstring);
    }

    const char *getChars()
    {
        return getString().c_str();
    }
}monoString;

/*
This struct represents a List. In the dump, a List is declared as List`1.
Deep down, this simply wraps a C array around a C# list. For example, if you had this in a dump,
public class Player {
	List`1<int> perks; // 0xDC
}
getting that list would look like this: monoList<int *> *perks = *(monoList<int *> **)((uint64_t)player + 0xdc);
You can also get lists that hold objects, but you need to use void ** because we don't have implementation for the Weapon class.
public class Player {
	List`1<Weapon> weapons; // 0xDC
}
getting that list would look like this: monoList<void **> *weapons = *(monoList<void **> **)((uint64_t)player + 0xdc);
If you need a list of strings, use monoString **.
To get the C array, call getItems.
To get the size of a monoList, call getSize.
*/
template <typename T>
struct monoList {
    void *unk0;
    void *unk1;
    monoArray<T> *items;
    int size;
    int version;

    T getItems(){
        return items->getPointer();
    }

    int getSize(){
        return size;
    }

    int getVersion(){
        return version;
    }
};

/*
This struct represents a Dictionary. In the dump, a Dictionary is defined as Dictionary`1.
You could think of this as a Map in Java or C++. Keys correspond with values. This wraps the C arrays for keys and values.
If you had this in a dump,
public class GameManager {
	public Dictionary`1<int, Player> players; // 0xB0
	public Dictionary`1<Weapon, Player> playerWeapons; // 0xB8
	public Dictionary`1<Player, string> playerNames; // 0xBC
}
to get players, it would look like this: monoDictionary<int *, void **> *players = *(monoDictionary<int *, void **> **)((uint64_t)player + 0xb0);
to get playerWeapons, it would look like this: monoDictionary<void **, void **> *playerWeapons = *(monoDictionary<void **, void **> **)((uint64_t)player + 0xb8);
to get playerNames, it would look like this: monoDictionary<void **, monoString **> *playerNames = *(monoDictionary<void **, monoString **> **)((uint64_t)player + 0xbc);
To get the C array of keys, call getKeys.
To get the C array of values, call getValues.
To get the number of keys, call getNumKeys.
To get the number of values, call getNumValues.
*/
template <typename K, typename V>
struct monoDictionary {
    void *unk0;
    void *unk1;
    monoArray<int **> *table;
    monoArray<void **> *linkSlots;
    monoArray<K> *keys;
    monoArray<V> *values;
    int touchedSlots;
    int emptySlot;
    int size;

    K getKeys(){
        return keys->getPointer();
    }

    V getValues(){
        return values->getPointer();
    }

    int getNumKeys(){
        return keys->getLength();
    }

    int getNumValues(){
        return values->getLength();
    }

    int getSize(){
        return size;
    }
};

monoString *CreateIl2cppString(const char *str)
{
    dlerror();
    auto handle = dlopen("libil2cpp.so", RTLD_LAZY);
    const char* openerror = dlerror();
    if(openerror)
    {
        LOGE(OBFUSCATE("Error Opening Lib: %s"), openerror);

        return nullptr;
    }
        const char* symerror = dlerror();
        if(symerror)
        {
            LOGE(OBFUSCATE("Error Finding Symbol: %s"), symerror);
            return nullptr;
        }
        monoString *(*il2cpp_string_new)(const char *) = (monoString *(*)(const char *))dlsym(handle, OBFUSCATE("il2cpp_string_new"));
        return il2cpp_string_new(str);
}

int GetObscuredIntValue(uint64_t location){
    int cryptoKey = *(int *)location;
    int obfuscatedValue = *(int *)(location + 0x4);

    return obfuscatedValue ^ cryptoKey;
}
bool GetObscuredBoolValue(uint64_t location){
    int cryptoKey = *(int *)location;
    int obfuscatedValue = *(int *)(location + 0x4);

    return (bool)obfuscatedValue ^ cryptoKey;
}
/*
Set the real value of an ObscuredInt.
Parameters:
	- location: the location of the ObscuredInt
	- value: the value we're setting the ObscuredInt to
*/
void SetObscuredIntValue(uint64_t location, int value){
    int cryptoKey = *(int *)location;

    *(int *)(location + 0x4) = value ^ cryptoKey;
}
void SetObscuredBoolValue(uint64_t location, bool value){
    int cryptoKey = *(int *)location;

    *(int *)(location + 0x4) = value ^ cryptoKey;
}
/*
Get the real value of an ObscuredFloat.
Parameters:
	- location: the location of the ObscuredFloat
*/
float GetObscuredFloatValue(uint64_t location)
{
    int cryptoKey = *(int *) location;
    int obfuscatedValue = *(int *) (location + 0x4);

    union intfloat
    {
        int i;
        float f;
    };

    /* use this intfloat to set the integer representation of our parameter value, which will also set the float value */
    intfloat IF;
    IF.i = obfuscatedValue ^ cryptoKey;

    return IF.f;
}

/*
Set the real value of an ObscuredFloat.
Parameters:
	- location: the location of the ObscuredFloat
	- value: the value we're setting the ObscuredFloat to
*/
void SetObscuredFloatValue(uint64_t location, float value)
{
    int cryptoKey = *(int *) location;

    union intfloat
    {
        int i;
        float f;
    };

    /* use this intfloat to get the integer representation of our parameter value */
    intfloat IF;
    IF.f = value;

    /* use this intfloat to generate our hacked ObscuredFloat */
    intfloat IF2;
    IF2.i = IF.i ^ cryptoKey;

    *(float *) (location + 0x4) = IF2.f;
}
#endif IMGUIANDROID_UNITY_H
