#!/bin/bash

# SERGIO SIVONEI DE SANT'ANA FILHO - GRR 20242337

TEMP_INPUT_FILE=$(mktemp)
VOID_FILE="VOID_FILE"

trap 'rm -f -- "$TEMP_INPUT_FILE"' EXIT
trap 'rm -f -- "$VOID_FILE"' EXIT

cat > "$TEMP_INPUT_FILE"

make &> "$VOID_FILE"

./resolveEDO  < "$TEMP_INPUT_FILE" 2>&1 | grep -v "Running without Marker API"

echo ""

likwid-perfctr -O -C 3 -g FLOPS_DP -m ./resolveEDO < "$TEMP_INPUT_FILE"| grep -e "FP_ARITH_INST_RETIRED_SCALAR_DOUBLE" | sed 's/,PMC1//g'