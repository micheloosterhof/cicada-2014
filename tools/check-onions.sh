#!/bin/bash
cd ~/cicada-2014/stage10/tmp
echo "------------------------------------------------" >> log
date >> log
torify wget -S http://auqgnxjtvdbll3pv.onion >> log 2>&1
torify wget -S http://cu343l33nqaekrnw.onion >> log 2>&1
torify wget -S http://fv7lyucmeozzd5j4.onion >> log 2>&1
torify wget -S http://avowyfgl5lkzfj3n.onion >> log 2>&1
torify wget -S http://q4utgdi2n4m4uim5.onion >> log 2>&1
torify wget -S http://ut3qtzbrvs7dtvzp.onion >> log 2>&1

