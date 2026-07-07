
TARGET_DIR=$1
mkdir -p $TARGET_DIR
# place device family pack somewhere, not tracked in git, only if it doesn't exist
if ! [ -f "$TARGET_DIR/NXP.MCXN947_DFP.19.0.0.pack" ]; then
    wget https://mcuxpresso.nxp.com/cmsis_pack/repo/NXP.MCXN947_DFP.19.0.0.pack \
	-P $TARGET_DIR
else
    echo "Device Family Pack is already installed at $TARGET_DIR/NXP.MCXN947_DFP.19.0.0.pack"
fi

# tell pyocd where it is
FILE=$TARGET_DIR/pyocd.yaml

cat >$FILE <<EOF
pack:
    - $(pwd)/NXP.MCXN947_DFP.19.0.0.pack
EOF
