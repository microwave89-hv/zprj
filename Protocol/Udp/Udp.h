//
// This file contains 'Framework Code' and is licensed as such 
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.                 
//
#ifndef _EFI_UDP_H_
// GC_TODO: move protective #ifndef after comment header
#define _EFI_UDP_H_

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
  Udp.h

Abstract:
  EFI User Datagram Protocol Definition

--*/
#include "Tiano.h"
#include "TianoTypes.h"

EFI_FORWARD_DECLARATION (EFI_UDP_PROTOCOL);

#include EFI_PROTOCOL_DEFINITION (Ip)

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define EFI_UDP_PROTOCOL_GUID \
  { \
    0xc56fb1b2, 0x017b, 0x4984, 0xa3, 0xf6, 0x3f, 0x73, 0x4f, 0xfa, 0x9e, 0x33 \
  }

extern EFI_GUID gEfiUdpProtocolGuid;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

//
//
//
//
//
//
#pragma pack(1)

typedef struct {
  UINT16  SourcePort;
  UINT16  DestinationPort;
  UINT16  Length;
  UINT16  Checksum;
} EFI_UDP_HEADER;

#pragma pack()

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

//
//
//
typedef VOID  *EFI_UDP_HANDLE;

//
//
//
typedef
VOID
(EFIAPI *EFI_UDP_RECEIVE) (
  IN  VOID              *Context,
  IN  EFI_IP_ADDRESS    * DestinationIp,
  IN  UINT16            DestinationPort,
  IN  EFI_IP_ADDRESS    * SourceIp,
  IN  UINT16            SourcePort,
  IN  UINTN             BufferLen,
  IN  VOID              *Buffer
  );

/*++
 *  Description:
 *  The UDP receive function is called during UDP event processing when a
 *  valid UDP packet has been received.  All processing of the received data
 *  must be completed before returning control to the UDP protocol driver.
 *  The contents of the DestinationIp, SourceIp and Buffer parameters may
 *  be overwritten or unallocated after control is returned to the UDP
 *  protocol driver.
 *
 *  Parameters:
 *  Context -         Pointer to receive context data.
 *  DestinationIp -   IP address that the packet was sent to.
 *  DestinationPort - UDP port number that the packet was sent to.
 *  SourceIp -        IP address that the packet was sent from.
 *  SourcePort -      UDP port number that the packet was sent from.
 *  BufferLen -       Length of received UDP packet.  May be zero.
 *  Buffer -          Pointer to received UDP packet.  May be NULL.
 *
 *  Returns:
 *  n/a
--*/

//
//
//
typedef struct {
  VOID            *Context;
  EFI_IP_ADDRESS  StationIp;
  EFI_IP_ADDRESS  SubnetMask;
  EFI_IP_ADDRESS  GatewayIp;
  UINT8           TypeOfService;
  UINT8           TimeToLive;
  BOOLEAN         DoNotFragment;
  BOOLEAN         Promiscuous;
  BOOLEAN         Broadcast;
  BOOLEAN         AnyPort;
  UINT16          Port;
  EFI_UDP_RECEIVE Receive;
  UINTN           MulticastIpCount;
  EFI_IP_ADDRESS  *MulticastIpList;
} EFI_UDP_OPEN_DATA;

/*++
 *  StationIp -         IP address assigned to this UDP handle.
 *  SubnetMask -        Subnet mask.  Used to check if the destination IP
 *                      address is on the same subnet as the StationIp.
 *  GatewayIp -         Default gateway IP address.  Used if the destination
 *                      IP address is not on the same subnet as the StationIp
 *                      and is also not present in the route table.
 *  TypeOfService -     Packet service priority.
 *  TimeToLive -        Number of gateway 'hops' before packet 'dies'.
 *  DoNotFragment -     If TRUE, transmitted UDP packets will have the
 *                      'do not fragment' bit set in the IP header.
 *  Promiscuous -       If TRUE, accept all UDP packets if they get past
 *                      the port filters.
 *  Broadcast -         If TRUE, accept broadcast UDP packets if they get
 *                      past the port filters.
 *  AnyPort -           Accept UDP packets sent to any port number.
 *  Port -              If AnyPort is FALSE, only accept UDP packets sent
 *                      to this port number.
 *  Receive -           Pointer to the UDP receive function for this handle.
 *  MulticastIpCount -  Number of multicast IP addresses in the MulticastIpList
 *                      array.  May be zero.
 *  MulticastIpList -   Array of multicast IP addresses.  UDP packets sent to 
 *                      these addresses will be accepted by the UDP protocol
 *                      driver if they get past the port filters.
--*/

//
//
//
typedef
EFI_STATUS
(EFIAPI *EFI_UDP_OPEN) (
  IN EFI_UDP_PROTOCOL           * This,
  IN  EFI_UDP_OPEN_DATA         * UdpOpenData,
  OUT EFI_UDP_HANDLE            * NewUdpHandle
  );

//
//
//
typedef
EFI_STATUS
(EFIAPI *EFI_UDP_CLOSE) (
  IN  EFI_UDP_HANDLE  UdpHandle,
  IN  BOOLEAN         Flush
  );

//
//
//
typedef
EFI_STATUS
(EFIAPI *EFI_UDP_TRANSMIT) (
  IN  EFI_UDP_HANDLE  UdpHandle,
  IN  EFI_IP_ADDRESS  * DestinationIp,
  IN  UINT16          DestinationPort,
  IN  BOOLEAN         Flush,
  IN  UINTN           BufferLen,
  IN  VOID            *Buffer
  );

//
//  UDP protocol interface.
//
typedef struct _EFI_UDP_PROTOCOL {
  EFI_UDP_OPEN      Open;
  EFI_UDP_CLOSE     Close;
  EFI_UDP_TRANSMIT  Transmit;
  EFI_EVENT         Event;
} EFI_UDP_PROTOCOL;

#endif /* _EFI_UDP_H */

/* EOF - Udp.h */
