#ifdef ESP32_DEV

#include "Storage.h"
#include <Preferences.h>

Preferences _storage;

bool Storage::open()
{
    _storage.begin("bskap");
}

void Storage::close()
{
    _storage.end();
}

bool Storage::format()
{
    _storage.clear();
}

bool Storage::exists(const char *file)
{
    String val = _storage.getString(file, "_!~");
    return val != "_!~";
}

bool Storage::remove(const char *file)
{
    return _storage.remove(file);
}

size_t Storage::writeFile(const char *file, String data)
{
    return _storage.putString(file, data);
}

size_t Storage::writeFile(const char *file, uint8_t *data, size_t length)
{
    return _storage.putBytes(file, data, length);
}

String Storage::readFile(const char *file, size_t *read)
{
    String val = _storage.getString(file, "");
    *read = val.length();
    return val;
}

size_t Storage::readFile(const char *file, uint8_t *data, size_t length)
{
    return _storage.getBytes(file, data, length);
}

/**
int16_t Storage::size(const char *file)
{
}
*/

#endif //ESP32_DEV