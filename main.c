#pragma once

/*
legacy friendly
evolution friendly
versionning capable
data exchange protocol

# Goal

This protocol aims to address the following issue:
"We need a common format to communicate between many agents,
this format may evolve frequently, and every agent cannot be
updated at same time, and the communication should still be possible,
without adding a costly encoding/decoding process."

# What this protocol does provide:

- legacy proof, since communication between several versions of the implementation is possible
- low overhead interface (no encoding/decoding is required, just copies, unless the data itself requires it)
- a contract between several program willing to communicate

- fields can be added or removed without compatibility issue

WHAT ABOUT a fields provided twice????????

# What this protocol does not provide:

- the implementation
- endianess of bytes
- fault tolerant mechanism

# Overview

Basically, the protocol defines a format of message which may contain
several of pieces of user-defined data.

Every possible piece of data is associated to an enumerated value.

The pieces of data are just packs of bytes


agreed between agents using this protocol.


fixed sized enum
variable number of bytes

describing the following data (type, name version)

On the transport layer

This protocol is a very simple way of conveying data between programs

The interpretation of every piece of data is a contract between the publisher and the consumer.
The size, the type, the format is deduced from the value of the

# Basically, three different fields are provided in the layout:

- the version of the implementation
- the enumerated values
- bytes of data

Some specific values of enum can be used in a different way such:
- a flag to give some information about the current message such the type of the message.

Example for a string:
- a null terminated UTF-8
Example for a boolean:
- using an enum value followed by a byte set to '1' or '0'
- "burning" two enum values to set the flag to 'true' or 'false'

+-----------------+-------+
| implem. version | byte  |
+-----------------+-------+
| message type    | byte  |
+-----------------+-------+
| type of data 1  | enum  |
+-----------------+-------+
| data 1          | bytes |
+-----------------+-------+
| ...             | ...   |
+-----------------+-------+
| flag            | enum  |
+-----------------+-------+
| ...             | ...   |
+-----------------+-------+
| type of data N  | enum  |
+-----------------+-------+
| data N          | bytes |
+-----------------+-------+
| sentinel value  | enum  |
+-----------------+-------+

*/

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
