legacy friendly
evolution friendly
versionning capable
data exchange protocol

# Foreword

An infrastructure with a good design and a well-managed software stack,
and on which we have full control, should not contain many versions of
the same component. This add some complexity and some possible differences
to cover with extra logic which can be avoided.

However, it happens that the components are not under our responsibility
after delivery and then we have to handle several versions, still able to
work together.

# Goal

This protocol aims to address the following issue:
"We need a common format to communicate between many agents,
this format may evolve frequently, and every agent cannot be
updated at same time, and the communication should still be possible,
without adding a costly encoding/decoding process if not necessary."

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

# Possible implementations

The implementation is very flexible and leave many choices to the user.

The header consisting in the implementation version and the message type
can be read as a 16-bits integer since the interpretation of the payload
depends on both version and message type.

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
