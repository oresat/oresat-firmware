#!/usr/bin/env python3
"""Flash a node id to OreSat firmware card.

We store the Node IDs in the "Flash Option Byte Register" (See RM00091 Reference
Manual - 3.5.7 Flash Option byte register (FLASH_OBR)).

The node ID is consumed and passed to CANOpenNode in common/oresat.c
"""

import subprocess
import sys
from argparse import ArgumentParser

from oresat_configs import OreSatConfig

CONFIG_PATH = {
    "battery": "BATTERY_V3",
    "solar": "SOLAR_V5",
    "adcs": "ORESAT_ADCS_V1_2",
    "rw": "ORESAT_RWB_V4",
    "diode_test": "PROTOCARD_V4",
}

CARD_ALIASES = {}
for name, aliases in {
    "battery": ["bat", "batt"],
    "solar": ["sol", "solar_module"],
    "adcs": ["imu"],
    "rw": ["reaction_wheel"],
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
parser.add_argument("number", nargs='?', type=int, help="card number")
args = parser.parse_args()

config = OreSatConfig()
if args.ids:
    print(f"{'Card name':16}| Node ID")
    for card, info in config.cards.items():
        if info.processor == 'stm32':
            if card[-1].isdigit():
                card = card.replace('_', ' ')
            print(f"{card:16}: 0x{info.node_id:02X}")
    sys.exit(1)

try:
    card = CARD_ALIASES[args.card.lower().replace("-", "_")]
except KeyError:
    print(f"failed to find card with name or alias of '{args.card}'")
    sys.exit(1)

try:
    if args.number is None:
        node_id = config.cards[card].node_id
    else:
        node_id = config.cards[f"{card}_{args.number}"].node_id
except KeyError:
    print(f"failed to find card with name {args.card} and number {args.number}")
    raise
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
