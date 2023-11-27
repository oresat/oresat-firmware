#!/usr/bin/env python3
"""Flash a node id to OreSat firmware card."""

import subprocess
import sys
import warnings
warnings.filterwarnings("ignore", category=DeprecationWarning)
from argparse import ArgumentParser
from telnetlib import Telnet
from threading import Thread
from time import sleep

NODE_IDS = {
    ("battery", 1): 0x04,
    ("battery", 2): 0x08,
    ("solar_module", 1): 0x0C,
    ("solar_module", 2): 0x10,
    ("solar_module", 3): 0x14,
    ("solar_module", 4): 0x18,
    ("solar_module", 5): 0x1C,
    ("solar_module", 6): 0x20,
    ("solar_module", 7): 0x24,
    ("solar_module", 8): 0x28,
    ("adcs", 1): 0x38,
    ("reactiom_wheel", 1): 0x3C,
    ("reactiom_wheel", 2): 0x40,
    ("reactiom_wheel", 3): 0x44,
    ("reactiom_wheel", 4): 0x48,
}

CONFIG_PATH = {
    "battery": "boards/BATTERY_V3/oocd.cfg",
    "solar_module": "boards/SOLAR_V4/oocd.cfg",
    "adcs": "boards/ORESAT_ADCS_V1_2/oocd.cfg",
    "reactiom_wheel": "boards/ORESAT_RWB_V4/oocd.cfg",
}

CARD_ALIASES = {
    "battery": ["bat"],
    "solar_module": ["solar"],
    "adcs": ["imu"],
    "reactiom_wheel": ["rw"],
}

parser = ArgumentParser(description="Flash the node id to a OreSat firmware card")
parser.add_argument("card")
parser.add_argument("-n", "--number", type=int, default=1)
parser.add_argument("-o", "--host", default="localhost")
parser.add_argument("-p", "--port", default="4444")
args = parser.parse_args()

node_id = 0x1
card = args.card.lower().replace("-", "_")

for key, values in CARD_ALIASES.items():
    if card == key:
        break
    elif card in values:
        card = key
        break
else:
    print(f"failed to find card with name or alias of {args.card}")
    sys.exit(1)

try:
    node_id = NODE_IDS[(card, args.number)]
except KeyError:
    print(f"failed to find card with name {args.card} and number {args.number}")
    sys.exit(1)

proc = None
failed = False

inv_node_id = 255 - node_id
value = hex(inv_node_id << 8 | node_id)


def run_openocd():
    print("starting openocd")
    global proc
    config_path = CONFIG_PATH[card]
    proc = subprocess.Popen(
        ["openocd", "-f", f"{config_path}"],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
    )


thread = Thread(target=run_openocd)
thread.start()

sleep(2)


def telnet_write(tn: Telnet, msg: str):
    tn.write(f"{msg}\r\n".encode())
    sleep(0.1)


try:
    with Telnet(args.host, args.port) as tn:
        print("connect with telnet")
        sleep(2)
        # stop the firmware
        print("halting firmware")
        tn.write(b"halt\r\n")

        # unlock flash
        print("unlock flash")
        telnet_write(tn, "mww 0x40022004 0x45670123")
        telnet_write(tn, "mww 0x40022004 0xCDEF89AB")

        # unlock option bytes for writing
        print("unlock option bytes")
        telnet_write(tn, "mww 0x40022008 0x45670123")
        telnet_write(tn, "mww 0x40022008 0xCDEF89AB")

        # clear option bytes
        print("clear option bytes")
        telnet_write(tn, "mww 0x40022010 0x00000220")
        telnet_write(tn, "mww 0x40022010 0x00000260")

        # enable programing
        print("enable programing")
        telnet_write(tn, "mww 0x40022010 0x00000210")

        # write node_id
        print("write node_id")
        telnet_write(tn, "mwh 0x1ffff800 0x55AA")
        telnet_write(tn, "mwh 0x1ffff802 0x00ff")
        telnet_write(tn, f"mwh 0x1ffff804 {value}")  # node id set here
        telnet_write(tn, "mwh 0x1ffff806 0x00ff")
        telnet_write(tn, "mwh 0x1ffff808 0x00ff")
        telnet_write(tn, "mwh 0x1ffff80a 0x00ff")
        telnet_write(tn, "mwh 0x1ffff80c 0x00ff")
        telnet_write(tn, "mwh 0x1ffff80e 0x00ff")
except OSError:
    print("Failed to write node id due to a telnet connection error")
    failed = True

sleep(0.5)
proc.terminate()
thread.join()

if not failed:
    print("node id was flashed")
