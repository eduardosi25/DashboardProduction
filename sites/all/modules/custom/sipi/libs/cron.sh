#!/bin/bash

NOW=
echo "Running metrics recovery process for CODIGA at $(date +"%Y%m%d %H:%M:%S")" >> /tmp/codiga.cron.log
wget --timeout=1800 --wait=10 --tries=5 -O /tmp/codiga.log http://www.invent.mx/admin/config/system/codiga/cronlt
echo "End cron at $(date +"%Y%m%d %H:%M:%S")" >> /tmp/codiga.cron.log
