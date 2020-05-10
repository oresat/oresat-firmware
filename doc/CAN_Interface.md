# CAN Interface Documentation

## Overview
OreSat uses the [ECSS-E-ST-50-15C](https://ecss.nl/standard/ecss-e-st-50-15c-space-engineering-canbus-extension-protocol-1-may-2015/) CANbus Extension Protocol Standard to integrate subsystems together. This standard is built upon [CANopen](https://www.can-cia.org/canopen/), and specifies how CANopen should be utilized to provide services described in [CCSDS Spacecraft Onboard Interface Services](https://public.ccsds.org/Pubs/850x0g2.pdf). To accomplish this goal, OreSat employs the open source [CANopenNode](https://github.com/CANopenNode/CANopenNode) protocol stack.

### CANopen
CANopen is a protocol stack meant to expand the underlying CAN bus services to facilitate things like arbitrary data transfers, network management, emergency messages, process data synchronization, and more. The core of the CANopen specification is something called the Object Dictionary, which provides an interface for a device to the CAN bus. There are two common ways to interface with this object dictionary: Service Data Object (SDO) and Process Data Object (PDO).

An SDO transfer is initiated by whatever node is considered the manager of the network, and allows what is essentially an abritrary sized read or write of an object dictionary entry.

A PDO, on the other hand, does not depend on any particular system to initiate anything. A PDO maps one or more object dictionary entries into a CAN message that is sent over the network either periodically, on a Change of State, after a SYNC message, or some combination of these. A PDO can be thought of as a publisher->subscriber model, in that one device publishes some of its object dictionary to the network while one or more other devices listen for these PDOs and record the data to their own object dictionaries.

CANopen also specifies a Network Management (NMT) protocol for node health monitoring and state control. This protocol allows nodes to broadcast a Heartbeat message that indicates their current state to the network, and allows a Network Manager to tell nodes to change state. The states mentioned here are only the most basic states: Initialization, Pre-Operational, Operational, and Stopped. These states govern when worker processes are told to start or stop.

## Architecture
