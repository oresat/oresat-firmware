#!/usr/bin/env python3
"""Flash a node id to OreSat firmware card.

We store the Node IDs in the "Flash Option Byte Register" (See RM00091 Reference
Manual - 3.5.7 Flash Option byte register (FLASH_OBR)).

The node ID is consumed and passed to CANOpenNode in common/oresat.c
"""

import subprocess
import sys
from argparse import ArgumentParser

# FIXME: retrieve IDs from oresat-configs
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
    ("reaction_wheel", 1): 0x3C,
    ("reaction_wheel", 2): 0x40,
    ("reaction_wheel", 3): 0x44,
    ("reaction_wheel", 4): 0x48,
    ("diode_test", 1): 0x54,
}

CONFIG_PATH = {
    "battery": "BATTERY_V3",
    "solar_module": "SOLAR_V5",
    "adcs": "ORESAT_ADCS_V1_2",
    "reaction_wheel": "ORESAT_RWB_V4",
    "diode_test": "PROTOCARD_V4",
}

CARD_ALIASES = {}
for name, aliases in {
    "battery": ["bat", "batt"],
    "solar_module": ["solar", "sol"],
    "adcs": ["imu"],
    "reaction_wheel": ["rw"],
    "diode_test": ["diode", "dtc"],
}.items():
    CARD_ALIASES[name] = name
    for alias in aliases:
        CARD_ALIASES[alias] = name

parser = ArgumentParser(
    description="Flash the node id to a OreSat firmware card",
    epilog="Valid cards: " + " ".join(CARD_ALIASES)
)
group = parser.add_mutually_exclusive_group(required=True)
group.add_argument("--ids", action='store_true', help="prints the list of node ids")
group.add_argument("card", nargs='?', help="see below for valid names")
parser.add_argument("number", nargs='?', type=int, default=1, help="card number, default: %(default)s")
args = parser.parse_args()

if args.ids:
    print(f"{'Card name':16}| Node ID")
    for (name, num), nid in NODE_IDS.items():
        card = f"{name} {num}"
        print(f"{card:16}: 0x{nid:02X}")
    sys.exit(1)

try:
    card = CARD_ALIASES[args.card.lower().replace("-", "_")]
except KeyError:
    print(f"failed to find card with name or alias of '{args.card}'")
    sys.exit(1)

try:
    node_id = NODE_IDS[(card, args.number)]
except KeyError:
    print(f"failed to find card with name {args.card} and number {args.number}")
    sys.exit(1)

subprocess.run(["openocd", # "-d",
    "-s", f"boards/{CONFIG_PATH[card]}", "-s", "toolchain",
    "-f", "oocd-interface.cfg",
    "-f", "oocd-target.cfg",
    "-c", "init",
    "-c", "reset init",
    "-c", f"stm32f0x options_write 0 SWWDG NORSTSTOP NORSTSTNDBY USEROPT {node_id}",
    "-c", "shutdown"
    ], check=True)

# FIXME: The new programmed option bytes (user, read/write protection) are not
# loaded after a system reset. To reload them, either a POR or setting to '1'
# the OBL_LAUNCH bit is necessary. "stm32f0x options_load 0" can do this but it
# then errors out for reasons I've not figured out yet

print(f"node id 0x{node_id:X} was flashed")
print("Card must be power cycled before changes take effect")
