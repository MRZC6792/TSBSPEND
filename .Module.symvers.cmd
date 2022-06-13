cmd_/home/mrzc/TS/BSP/bsp3/Module.symvers := sed 's/\.ko$$/\.o/' /home/mrzc/TS/BSP/bsp3/modules.order | scripts/mod/modpost -m -a  -o /home/mrzc/TS/BSP/bsp3/Module.symvers -e -i Module.symvers   -T -
