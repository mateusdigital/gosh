#pragma once

//
#include <string.h>
#include <ctype.h>
#include <string>
//
#include "Array.hpp"

//
// Constants
//
constexpr char   NULL_CHAR = '\0';
constexpr size_t INVALID_STRING_INDEX = std::string::npos;


//
// C - String
//
inline size_t
CStrLen(const char * const str)
{
    if(!str) {
        return 0;
    }
    return strlen(str);
}

inline bool
CStrEquals(const char * const lhs, char const * const rhs)
{
    return strcmp(lhs, rhs) == 0;
}

inline bool
CStrIsNullEmptyOrWhitespace(char const * const str)
{
    if(!str) {
        return true;
    }
    if(CStrLen(str) == 0) {
        return true;
    }
    for(char const *c = str; c != nullptr; ++c) {
        if(*c != ' ') {
            return false;
        }
    }
    return true;
}

//
// String
//
class String :
    public std::string
{
private:
    typedef std::string __Container;

public:
    static String 
    CreateWithCapacity(size_t capacity) 
    {
        String s;
        s.Reserve(capacity);
        return s;
    }


public:
    String(std::string const &right)
        : std::string(right)
    {
        // Empty...
    }

    String(char const * const right = "")
        : std::string(right)
    {
        // Empty...
    }

public:
    char        const * CStr     () const { return this->c_str(); }
    std::string const & StdString() const { return *this;         }

public:
    static String Format(String const &fmt, ...);



public:
    bool   IsEmpty() const { return __Container::empty(); }
    size_t Length () const { return __Container::size (); }

    bool 
    IsEmptyOrWhitespace() const
    {
        if(IsEmpty()) {
            return true;
        }

        size_t index = FindFirstNotOf(' ');
        return index == INVALID_STRING_INDEX;
    }


public:
    void Reserve(size_t const capacity) { __Container::reserve(capacity); }


public:
    bool StartsWith(String const &neddle) const;
    bool StartsWith(char   const  needle) const;

    bool EndsWith(String const &neddle) const;
    bool EndsWith(char   const  needle) const;


public:
    size_t FindIndexOf   (char const needle, size_t start_index = 0) const;
    size_t FindFirstNotOf(char const needle, size_t start_index = 0) const;

    size_t FindLastIndexOf   (char const needle, size_t start_index = 0) const;
    size_t FindLastIndexNotOf(char const needle, size_t start_index = 0) const;


public:
    Array<String> Split(char const separator) const;
    void PushBack(String const &rhs) { *this += rhs; }
    void PushBack(char   const  rhs) { *this += rhs; }

public:
    String 
    SubString(size_t const left_index, size_t const right_index) const
    {
        return substr(left_index, right_index - left_index);
    }


public:
    void
    TrimLeft(char const char_to_trim = ' ')
    {
        size_t left_index = FindFirstNotOf(char_to_trim);
        if (left_index == INVALID_STRING_INDEX) {
            return;
        }
        // @todo(stdmatt): We are creating too much copies... Dec 20, 2020 
        __Container::operator=(SubString(left_index, Length()));
    }

    void
    TrimRight(char const char_to_trim = ' ')
    {
        size_t right_index = FindLastIndexNotOf(char_to_trim);
        if (right_index == INVALID_STRING_INDEX) {
            return;
        }
        
        // @todo(stdmatt): We are creating too much copies... Dec 20, 2020 
        __Container::operator=(SubString(0, right_index));
    }

    void
    Trim(char const char_to_trim = ' ')
    {
        TrimLeft (char_to_trim); 
        TrimRight(char_to_trim);
    }

public:
    void 
    ToLower() 
    {
        size_t const len = Length();
        for (size_t i = 0; i < len; ++i) {
            __Container::operator[](i) = tolower(__Container::operator[](i));
        }
    }

    void 
    ToUpper() 
    {
        size_t const len = Length();
        for (size_t i = 0; i < len; ++i) {
            __Container::operator[](i) = toupper(__Container::operator[](i));
        }
    }
}; // class String
