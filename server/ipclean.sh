#!/bin/sh
EffectiveUser=`id -n -u 2>/dev/null || whoami 2>/dev/null`
ipcs | egrep '^m .*|^s .*' | egrep "$EffectiveUser" | \
awk '{printf "ipcrm -%s %s\n", $1, $2}' '-' | sh

