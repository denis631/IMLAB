#!/bin/sh

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
DataDIR="$(echo "$DIR/data")"
DataURL="https://db.in.tum.de/teaching/ws1718/imlab/tpcc_5w.tar.gz"

curl -s $DataURL | tar xvz -C $DataDIR