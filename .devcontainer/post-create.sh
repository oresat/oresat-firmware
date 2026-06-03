#!/bin/bash

set -e

complete_setup() {
    touch /workdir/setup_complete
}

is_setup_complete() {
    [ -f /workdir/setup_complete ]
}

setup() {
    if [ ! -d /workdir/.west ]; then
        west init -l
    else
        echo "West already initialized."
    fi

    # Note this final section of `setup()` follows Zephyr 4.3.0 "Getting
    # Started" instructions at the Zephyr Project RTOS documentation site.
    echo "Adding extra modules and calling \`west\` to update SDK..."
    west update
    west zephyr-export
    west packages pip --install
    ./scripts/placeholder.sh
    complete_setup
}

# Skip if already initialized
if is_setup_complete; then
    echo "Setup already completed."
else
    setup
fi
