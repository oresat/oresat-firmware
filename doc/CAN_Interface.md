# CAN Interface Documentation

## Overview
The CAN subsystem implements several different components that facilitate command and control of different nodes, status updates, and the exchange of data between nodes.

## PDOs
Links are established between data in nodes via a Process Data Object (PDO). A PDO is basically a CAN message that contains a specific set of arbitrary data, defined by the user.
A given PDO contains up to 8 bytes of data, mapped by the user.

Each node has 4 Transmit PDOs (TPDO), and 4 Receive PDOs (RPDO).

A TPDO defines the data to be sent to the network, while an RPDO defines what data to watch for on the network and where it maps to in the receiving node.

TPDOs and RPDOs have a default CAN message ID configured, but by default only the CAN Master Node may receive from a TPDO or send to an RPDO for all nodes on the network.
However, links can be established directly between two nodes by overriding the default CAN message ID for either the TPDO or RPDO. RPDO is recommended.

### TPDO
To initialize a TPDO, the function call is:

`canTPDOObjectInit(can_pdo_t pdo_num, can_id_t can_id, uint32_t event_tim, uint32_t inhibit_tim, uint8_t len, uint8_t *pdata)`

`pdo_num` is the actual number of the TPDO object, and is of type `can_pdo_t` which is an enumeration of one of the following values:

```
CAN_PDO_1
CAN_PDO_2
CAN_PDO_3
CAN_PDO_4
```
`can_id` is the CAN message ID that the TPDO will use. `CAN_ID_DEFAULT` is recommended, and defaults to the protocol's default CAN message ID for the given TPDO number and Node ID.

`event_tim` and `inhibit_tim` are currently unimplemented, but will be the maximum time to transmit, and minimum time between transmissions respectively, if doing a Change Of State implementation.

`len` is the size of the data set pointed to by `*pdata` in bytes, where `1 <= len <= 8`.

`*pdata` is the pointer to the array of bytes that are to be sent over the network.

### RPDO
To initialize a RPDO, the function call is:

`canRPDOObjectInit(can_pdo_t pdo_num, can_id_t can_id, uint8_t len, uint8_t *pdata)`

`pdo_num` is the actual number of the RPDO object, and is of type `can_pdo_t` which is an enumeration of one of the following values:

```
CAN_PDO_1
CAN_PDO_2
CAN_PDO_3
CAN_PDO_4
```

NOTE: This has no relation to the TPDO PDO number. It is just an identifier for a given TPDO or RPDO.

`can_id` is the CAN message ID that the RPDO will listen for. Usually you will set this to a TPDO's CAN ID of another node.
`CAN_ID_DEFAULT` is the protocol's default CAN message ID for the given RPDO number and Node ID.

`len` is the size of the data set pointed to by `*pdata` in bytes, where `1 <= len <= 8`. This should match the size of the TPDO being listened for.

`*pdata` is the pointer to the array of bytes that are updated with the values recieved over the network.

### Linking PDOs
To link a RPDO to a TPDO, you want to match the CAN IDs. It's recommended that default CAN IDs are used for TPDO objects (`CAN_ID_DEFAULT`), and RPDO objects are set to the TPDO objects.
The TPDO default CAN IDs are defined as follows:

```
TPDO 1: 0x180 + NodeID of transmitting node
TPDO 2: 0x280 + NodeID of transmitting node
TPDO 3: 0x380 + NodeID of transmitting node
TPDO 4: 0x480 + NodeID of transmitting node
```

An example implementation would be as follows:

#### Transmitting Node (ID: 31)
```
...
#define DATA_SIZE 8
uint8_t data[DATA_SIZE];

...
static void app_init(void) {
...

canTPDOObjectInit(CAN_PDO_1, CAN_ID_DEFAULT, 0, 0, DATA_SIZE, data);

...
}
```

This establishes TPDO_1 that transmits the 8 byte `data` array periodically with default CAN Message ID `Ox180 + 31 = 0x19F`.

To receive this TPDO on another node, we define an RPDO with the `can_id` field set Node 31's TPDO_1 CAN ID as follows:

#### Receiving Node (ID: 32)
```
...
#define DATA_SIZE 8
#define NODE_ID_TO_RECEIVE 31
uint8_t data[DATA_SIZE];

...
static void app_init(void) {
...

canRPDOObjectInit(CAN_PDO_1, (CAN_ID_TPDO_1 + NODE_ID_TO_RECEIVE), DATA_SIZE, data);

...
}
```

Alternatively, you can define the second arguement as just 0x19F, though it's perhaps more intuitive to define it as the TPDO plus the node ID.
