#pragma once

// allow mandatory fields

struct Message_V1
{
    int id;
    char name[256];
    float value;
}

struct Message_V2
{
    int id;
    char name[512];
    float value;
}

struct Message_V3
{
    int id;
    char name[512];
    float value;
    bool flag;
}

struct Message_V4
{
    int id;
    char name[512];
    double value;
    bool flag;
}

enum class Key : std::uint16_t
{
    NONE,
    ID_V1,
    NAME_V1,
    VALUE_V1,
    NAME_V2,
    FLAG_V3,
    VALUE_V4,
}

using Message = Message_V4;

void Deserialize(void *buffer, Message &message)
{
    Key key;

    do
    {
        key = ntohs(*static_cast<Key *>(buffer));
        buffer += sizeof(key);

        switch (key)
        {
        case NONE:
            return;
            break;
        case ID_V1:
            message.id = ntohl(*static_cast<int *>(buffer));
            buffer += sizeof(int);
            break;
        case NAME_V1:
            message.id = ntohl(*static_cast<int *>(buffer));
            buffer += sizeof(int);
            break;
        default:
            break;
        }
    }
    while (key != NONE);
}

int main(int argc, char ** argv)
{
    char buffer[1024];

    Serialize(buffer);

    Deserialize(buffer);

    return 0;
}
