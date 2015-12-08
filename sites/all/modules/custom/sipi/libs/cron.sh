#!/bin/bash
echo "Running metrics recovery process for CODIGA"
wget --timeout=1800 --wait=10 --tries=5 -O /tmp/codiga.log http://www.invent.mx/admin/config/system/codiga/cronlt
echo "End"
