#pragma once

#include <cerrno>

inline size_t _strlen(const char* str) {

    const char* s;

    for (s = str; *s; ++s);

    return (s - str) + 1;
}

inline void* _memcpy(void* dest, const void* src, size_t size) {

    const char* Src = (char*)src;

    char* Dest = (char*)dest;

    if (Dest && Src)
        for (size_t i = 0; i < size; ++i)
            *(Dest + i) = *(Src + i);

    return dest;
}

inline void* _memmove(void* dest, const void* src, size_t size) {

    if (!dest || !src)
        return dest;

    if (dest == src)
        return dest;

    const char* csrc = (char*)src;

    char* cdest = (char*)dest;

    if (csrc < cdest && cdest < (csrc + size))
        while (size--)
            *(--(cdest += size)) = *(--(csrc += size));

    else
        while (size--)
            *cdest++ = *csrc++;

    return dest;

}

inline char* _strcpy(char* dest, const char* src) {

    if (!dest)
        return nullptr;

    char* ptr = dest;

    while ((*dest++ = *src++) != '\0');

    *dest = '\0';

    return ptr;
}

inline char* _strncpy(char* dest, const char* src, size_t n) {

    if (!dest)
        return nullptr;

    size_t i;

    char* ptr = dest;

    for (i = 0; i < n && *src + i != '\0'; ++i)
        *(dest + i) = *(src + i);

    for (; i < n; ++i)
        *(dest + i) = '\0';

    return ptr;
}

inline char* _strcat(char* dest, const char* src) {

    if (!dest)
        return nullptr;

    char* ptr = dest + _strlen(dest);

    size_t i = 0;

    while (*(src + i) != '\0')
        *(ptr++) = *(src + i++);

    *ptr = '\0';

    return dest;

}

inline char* _strncat(char* dest, const char* src, size_t n) {

    size_t dest_length = _strlen(dest), i;

    for (i = 0; i < n && src[i] != '\0'; ++i)
        *(dest + dest_length + i) = *(src + i);

    *(dest + i + dest_length) = '\0';

    return dest;

}

inline int _memcmp(const void* s1, const void* s2, size_t n) {

    if (!n)
        return 0;

    size_t i = 0;

    while (--n && *((char*)s1 + i++) == *((char*)s2 + i++));

    return (*((unsigned char*)s1 - *(unsigned char*)s2));

}

inline int _strcmp(const char* s1, const char* s2) {


    //setlocale(LC_COLLATE, "en_us.utf8");

    const unsigned char* ptr1 = (const unsigned char*)s1;
    const unsigned char* ptr2 = (const unsigned char*)s2;

    while (*ptr1 != '\0') {

        if (*ptr2 == '\0') return  1;

        if (*ptr2 > *ptr1)   return -1;

        if (*ptr1 > *ptr2)   return  1;

        ++ptr1;
        ++ptr2;
    }

    if (*ptr2 != '\0') return -1;

    return 0;
}

inline int _strcoll(const char* s1, const char* s2) {


    while (*s1 == *s2++)
        if (*s1++ == '\0')
            return (0);

    return (*(const unsigned char*)s1 - *(const unsigned char*)(s2 - 1));
}

inline int _strncmp(const char* s1, const char* s2, size_t n) {

    while (n-- && *s1 && (*s1 == *s2)) {
        ++s1;
        ++s2;
    }

    if (n == 0)
        return 0;

    else
        return (*(unsigned char*)s1 - *(unsigned char*)s2);

}

inline size_t _strxfrm(char* dest, const char* src, size_t n) {

    //src = setlocale(LC_COLLATE, "en_us.utf8");

    if (!dest)
        return 0;

    size_t i;

    for (i = 0; i < n; ++i)
        *(dest + i) = *(src + i);

    *(dest + i) = '\0';

    return _strlen(dest);
}

inline char* _strtok(char* str, const char* token) {

    if (!token)
        return nullptr;

    static char* buff = nullptr;

    if (!buff)
        buff = str;

    if (!*buff)
        return nullptr;

    char* start = buff;

    size_t i = 0, len = _strlen(token);

    while (*buff && i != len) {
        while (*buff && *buff != *token)
            ++buff;
        while (buff[i] == token[i] && i < len)
            ++i;

        if (i == len) {
            *buff = '\0';
            buff += len;
        }
        else
            ++buff;
    }

    return start;
}

inline void* _memset(void* s, int c, size_t len) {

    unsigned char* dst = (unsigned char*)s;

    while (len--) {

        *dst = (unsigned char)c;

        dst++;
    }

    return s;
}

inline char* _strerror(int errnum) {


    if (errnum == E2BIG) //7
        return (char*)"Список аргументов слишком длинный";

    if (errnum == EACCES) //13
        return (char*)"Отказ в доступе";

    if (errnum == EADDRINUSE) //100
        return (char*)"Адрес используется";

    if (errnum == EADDRNOTAVAIL) //101
        return (char*)"Адрес недоступен";

    if (errnum == EAFNOSUPPORT) //102
        return (char*)"Семейство адресов не поддерживается";

    if (errnum == EAGAIN) //11
        return (char*)"Ресурс временно недоступен";

    if (errnum == EDOM) //33
        return (char*)"Ошибка области определения";

    if (errnum == EEXIST) //17
        return (char*)"Файл существует";

    if (errnum == EFAULT) //14
        return (char*)"Неправильный адрес";

    if (errnum == ENOENT) //2
        return (char*)"Нет такого файла или каталога";

    if (errnum == ENOMEM) //12
        return (char*)"Недостаточно памяти";

    if (errnum == ERANGE) //34
        return (char*)"Результат слишком велик";

    if (errnum == EADDRINUSE) //100
        return (char*)"Адрес используется";

    if (errnum == ETXTBSY) //139
        return (char*)"Текстовый файл занят";

    return (char*)"EINVAL"; //Значение errnum не является правильным кодом ошибки

}
