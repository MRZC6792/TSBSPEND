cmd_/home/mrzc/TS/BSP/bsp3/modules.order := {   echo /home/mrzc/TS/BSP/bsp3/bsp3.ko; :; } | awk '!x[$$0]++' - > /home/mrzc/TS/BSP/bsp3/modules.order
