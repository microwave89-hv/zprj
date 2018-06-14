//
// This file contains 'Framework Code' and is licensed as such 
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.                 
//
#ifndef _EFI_IP_H_
// GC_TODO: move protective #ifndef after comment header
#define _EFI_IP_H_

/*++

Copyright (c)  2002 Intel Corporation.  All rights reserved.

This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:
  Ip.h

Abstract:
  EFI Internet Protocol Definition

--*/
#include "Tiano.h"
#include "TianoTypes.h"

EFI_FORWARD_DECLARATION (EFI_IP_PROTOCOL);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define EFI_IP_PROTOCOL_GUID \
  { \
    0x89DEEF37, 0x31D8, 0x469C, 0x95, 0xB6, 0x01, 0x69, 0xBC, 0x86, 0x6C, 0xFB \
  }

extern EFI_GUID gEfiIpProtocolGuid;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

//
// Useful macros for byte ordering.
//
//
// EFI_IP_HTONS(x) - converts the value (x) from host byte order to network
//            byte order
//
#define EFI_IP_HTONS(x) ((UINT16) ((((x) & 0xFF00) >> 8) | (((x) & 0x00FF) << 8)))

//
// EFI_IP_HTONL(x)
//
#define EFI_IP_HTONL(x) \
    ((UINT32) ((((x) & 0xFF000000) >> 24) | (((x) & 0xFF0000) >> 8) | (((x) & 0xFF00) << 8) | (((x) & 0xFF) << 24)))

//
// EFI_IP_NSTOH(x) - converts the value *(x) from network byte order to
//            host byte order
//
#define EFI_IP_NSTOH(x) (UINT16) ((((UINT16) *((UINT8 *) (x)) & 0xFF) << 8) | ((UINT16) *((UINT8 *) (x) + 1) & 0xFF))

//
// EFI_IP_NLTOH(x)
//
#define EFI_IP_NLTOH(x) \
  (UINT32) \
    ( \
      (((UINT32) *((UINT8 *) (x)) & 0xFF) << 24) | (((UINT32) *((UINT8 *) (x) + 1) & 0xFF) << 16) | \
        (((UINT32) *((UINT8 *) (x) + 2) & 0xFF) << 8) | ((UINT32) *((UINT8 *) (x) + 3) & 0xFF) \
    )

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

//
//  Typical ethernet IPv4 packet layout:
//
//
//  +----- ----- ----- ----- ----- ----- ----- ----- -----+
//  | Media header  Destination MAC (6 bytes)             |
//  |               Source MAC (6 bytes)                  |
//  |               Protocol (2 bytes) [IP, ARP, etc]     |
//  +----- ----- ----- ----- ----- ----- ----- ----- -----+
//  | IPv4 header   HeaderLen (4 bits)                    |
//  |               Version (4 bits) [IPv4, IPv6]         |
//  |               TypeOfService (1 byte)                |
//  |               TotalLen (2 bytes)                    |
//  |               Identification (2 bytes)              |
//  |               FragmentOffset (2 bytes)              |
//  |               TimeToLive (1 byte)                   |
//  |               Protocol (1 byte)                     |
//  |               HeaderChecksum (2 bytes)              |
//  |               SourceIp (4 bytes)                    |
//  |               DestinationIp (4 bytes)               |
//  +----- ----- ----- ----- ----- ----- ----- ----- -----+
//  | IPv4 data                                           |
//  +----- ----- ----- ----- ----- ----- ----- ----- -----+
//

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

//
// Media header protocol values.
//
#define EFI_IP_MEDIA_HEADER_PROTOCOL_IP   0x0800
#define EFI_IP_MEDIA_HEADER_PROTOCOL_ARP  0x0806

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

//
// Detailed information on IPv4 packet contents can be found in RFC 791.
// www.ietf.org
//
//
// IPv4 packet header format (no options).
//
#pragma pack(1)
typedef struct {
  UINT8   HeaderLen : 4;
  UINT8   Version : 4;
  UINT8   TypeOfService;
  UINT16  TotalLen;
  UINT16  Identification;
  UINT16  FragmentOffset;
  UINT8   TimeToLive;
  UINT8   Protocol;
  UINT16  HeaderChecksum;
  UINT8   SourceIp[4];
  UINT8   DestinationIp[4];
} EFI_IP_IP4_HEADER;
#pragma pack()
//
// Some useful IPv4 constants.
//
#define EFI_IP_IP4_HEADER_VERSION         0x04

#define EFI_IP_IP4_HEADER_PROTOCOL_ICMP   1
#define EFI_IP_IP4_HEADER_PROTOCOL_IGMP   2
#define EFI_IP_IP4_HEADER_PROTOCOL_TCP    6
#define EFI_IP_IP4_HEADER_PROTOCOL_UDP    17

#define EFI_IP_IP4_HEADER_DONT_FRAGMENT   0x4000
#define EFI_IP_IP4_HEADER_MORE_FRAGMENTS  0x2000
#define EFI_IP_IP4_HEADER_FRAGMENT_MASK   0x1FFF
#define EFI_IP_IP4_HEADER_FRAGMENT_SHIFT  3

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

//
// Useful Internet Protocol constants.
//
#define EFI_IP_MAX_ROUTE_TABLE_SIZE 8     // # route entries
#define EFI_IP_MAX_ARP_CACHE_SIZE   8     // # packets
#define EFI_IP_ARP_CACHE_TIMEOUT    60000 // milliseconds
#define EFI_IP_ARP_RETRY_COUNT      4     // # requests
#define EFI_IP_ARP_RETRY_TIMEOUT    250   // milliseconds
#define EFI_IP_MAX_RX_QUEUE_SIZE    16    // # assembled packets
#define EFI_IP_RX_QUEUE_TIMEOUT     5000  // milliseconds
#define EFI_IP_MAX_TX_QUEUE_SIZE    32    // # fragments
#define EFI_IP_TX_QUEUE_TIMEOUT     100   // milliseconds
#define EFI_IP_MAX_BUFFER_SIZE      64    // K bytes

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

//
// IPv4 protocol definition.
//
//
// IP handle.  Returned by Ip->Open() and used when receiving or
// transmitting IP packets.
//
typedef VOID  *EFI_IP_HANDLE;

//
// IP handle receive function prototype.
//
typedef
VOID
(EFIAPI *EFI_IP_RECEIVE) (
  IN  VOID              *Context,
  IN  EFI_IP_ADDRESS    * DestinationIp,
  IN  EFI_IP_ADDRESS    * SourceIp,
  IN  UINT8             Protocol,
  IN  UINTN             BufferLen,
  IN  VOID              *Buffer
  );

/*++
 *  Description:
 *  A handle's receive function is called when a valid IP packet is
 *  received that matches the handle's receive filter(s).  When the
 *  receive function returns control to the IP protocol driver, the
 *  data in the Buffer can no longer be used.  If the data in the 
 *  Buffer needs to be preserved, it must be copied out before
 *  returning control to the IP protocol driver.
 *
 *  Parameters:
 *  Context -       Pointer to context data.
 *  DestinationIp - Pointer to the destination IP address.
 *  SourceIp -      Pointer to the source IP address.
 *  Protocol -      The encapsulated protocol number.
 *  BufferLen -     The number of data bytes in the receive buffer.
 *                  May be zero.
 *  Buffer -        Pointer to the receive buffer.  May be NULL.
 *
 *  Returns:
 *  n/a
--*/

//
// IP configuration and tuning parameters.
//
typedef struct {
  UINTN MaxRouteTableSize;
  UINTN MaxArpCacheSize;
  UINTN ArpCacheTimeout;
  UINTN ArpRetryCount;
  UINTN ArpRetryTimeout;
  UINTN MaxRxQueueSize;
  UINTN RxQueueTimeout;
  UINTN MaxTxQueueSize;
  UINTN TxQueueTimeout;
} EFI_IP_CONFIG_DATA;

//
// IP configuration function prototype.
//
typedef
EFI_STATUS
(EFIAPI *EFI_IP_CONFIG) (
  IN EFI_IP_PROTOCOL            * This,
  IN  BOOLEAN                   Reset,
  IN  EFI_IP_CONFIG_DATA        * NewData OPTIONAL,
  OUT EFI_IP_CONFIG_DATA        * OldData OPTIONAL
  );

/*++
 *  Description:
 *  This function is used to Set and/or Get the IP configuration and tuning
 *  parameters.  The tuning parameters can only be changed when there are
 *  no open IP handles.
 *
 *  Parameters:
 *  This -    Pointer to the IP protocol driver instance data.
 *  Reset -   Set to TRUE to reset the IP protocol driver configuration
 *            data back to default values.
 *  NewData - New IP protocol driver configuration data.  May be NULL.
 *  OldData - Previous IP protocol driver configuration data.  May be NULL.
 *
 *  Returns:
 *  EFI_SUCCESS -           Configuration data updated/retrieved as requested.
 *  EFI_INVALID_PARAMETER - One or more of the parameters or configuration
 *                          data values was invalid.
 *  EFI_ALREADY_STARTED -   One or more IP handles is open.
--*/

//
// IP handle open data.
//
typedef struct {
  VOID            *Context;
  EFI_IP_ADDRESS  StationIp;
  EFI_IP_ADDRESS  SubnetMask;
  EFI_IP_ADDRESS  GatewayIp;
  UINT8           TypeOfService;
  UINT8           TimeToLive;
  UINT8           Protocol;
  BOOLEAN         DoNotFragment;
  BOOLEAN         RawData;
  BOOLEAN         Promiscuous;
  BOOLEAN         Broadcast;
  BOOLEAN         AnyProtocol;
  EFI_IP_RECEIVE  Receive;
  UINTN           MulticastIpCount;
  EFI_IP_ADDRESS  *MulticastIpList;
} EFI_IP_OPEN_DATA;

/*++
 *  Context -           Pointer to context data returned in Receive().
 *  StationIp -         Unicast IP address.  Used as the source IP address
 *                      in transmitted packets.  Used as the destination IP
 *                      address in received IP packets.  Can be set to
 *                      0.0.0.0.
 *  SubnetMask -        Subnet mask.  Used to check if the destination IP
 *                      is on the same subnet as the StationIp. 
 *                      Can be set to 0.0.0.0.
 *  GatewayIp -         Default gateway IP address.  Used if the destination
 *                      IP is not on the same subnet as the StationIp.
 *                      Can be set to 0.0.0.0 if there is no default gateway.
 *  TypeOfService -     Packet service priority.  
 *  TimeToLive -        Number of gateway hops before packet 'dies'.
 *  Protocol -          Protocol number to be used in the IP header of
 *                      transmitted packets.  Protocol receive filter
 *                      to be used if AnyProtocol is FALSE.
 *  DoNotFragment -     Set to TRUE if transmitted IP packets must not
 *                      be fragmented.
 *  Promiscuous -       Set to TRUE to receive all valid IP packets.
 *  Broadcast -         Set to TRUE to also receive broadcast IP packets.
 *  AnyProtocol -       Set to TRUE to receive any protocol number.
 *                      Set to FALSE to receive only matching Protocol
 *                      numbers.
 *  Receive -           Pointer to this handle's IP receive function.
 *                      Can not be set to NULL.
 *  MulticastIpCount -  Number of multicast IP addresses in the
 *                      MulticastIpList array.  May be zero.
 *  MulticastIpList -   Array of multicast IP addresses.  IP packets sent
 *                      to these addresses will be accepted by the IP
 *                      protocol driver if the protocol numbers match.
 *                      Not used if MulticastIpCount is zero.
--*/

//
// Open new IP handle.
//
typedef
EFI_STATUS
(EFIAPI *EFI_IP_OPEN) (
  IN EFI_IP_PROTOCOL            * This,
  IN  EFI_IP_OPEN_DATA          * Data,
  OUT EFI_IP_HANDLE             * NewHandle
  );

/*++
 *  Description:
 *
 *  Parameters:
 *  This -      Pointer to IP protocol instance data.
 *  Data -      Pointer to handle configuration data.
 *  NewHandle - Pointer to new IP handle storage.
 *
 *  Returns:
 *  EFI_SUCCESS -           New IP handle was opened.
 *  EFI_INVALID_PARAMETER - One or more of the parameters is invalid.
 *  EFI_OUT_OF_RESOURCES -  New buffer(s) could not be allocated.
--*/

//
// Close existing IP handle.
//
typedef
EFI_STATUS
(EFIAPI *EFI_IP_CLOSE) (
  IN  EFI_IP_HANDLE   Handle,
  IN  BOOLEAN         Flush
  );

/*++
 *  Description:
 *  Close a previously opened IP handle.  
 *
 *  Parameters:
 *  Handle -  IP handle returned by Ip->Open().
 *  Flush -   Set to TRUE to flush all pending transmit packets before
 *            returning control.  Pending transmit data may be lost if
 *            Flush is set to FALSE.
 *
 *  Returns:
 *  EFI_SUCCESS -           IP handle has been closed.
 *  EFI_INVALID_PARAMETER - One or more of the parameters is invalid.
--*/

//
// Transmit one or more IP packets.
//
typedef
EFI_STATUS
(EFIAPI *EFI_IP_TRANSMIT) (
  IN  EFI_IP_HANDLE   Handle,
  IN  EFI_IP_ADDRESS  * DestinationIp OPTIONAL,
  IN  UINTN           BufferLen,
  IN  UINT8           *Buffer,
  IN  BOOLEAN         Flush
  );

//
//
//
typedef
UINT16
(EFIAPI *EFI_IP_CHECKSUM) (
  IN      UINTN                     BufferLen,
  IN      VOID                      *Buffer
  );

/*++
 *  Description:
 *  Compute IP checksum of buffer.
 *
 *  Parameters:
 *  BufferLen - Number of bytes to checksum.  May be zero.
 *  Buffer -    Pointer to buffer to checksum.  Not used if BufferLen
 *              is zero.
 *
 *  Returns:
 *  IP checksum of buffer.  Zero is returned if BufferLen is zero or
 *  Buffer is NULL.
--*/

//
//
//
typedef
UINT16
(EFIAPI *EFI_IP_IDENTIFICATION) (
  VOID
  );

/*++
 *  Description:
 *  Returns an IP header identification number.
 *
 *  Parameters:
 *  n/a
 *
 *  Returns:
 *  An IP header identification number.
--*/

//
// Internet Protocol interface definition.
//
typedef struct _EFI_IP_PROTOCOL {
  EFI_IP_CONFIG         Config;
  EFI_IP_OPEN           Open;
  EFI_IP_CLOSE          Close;
  EFI_IP_TRANSMIT       Transmit;
  EFI_IP_CHECKSUM       Checksum;
  EFI_IP_IDENTIFICATION Identification;
  EFI_EVENT             Event;
} EFI_IP_PROTOCOL;

#endif /* _EFI_IP_H */

/* EOF - Ip.h */
