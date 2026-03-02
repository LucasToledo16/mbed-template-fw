openocd \
  -f interface/cmsis-dap.cfg \
  -f target/lpc17xx.cfg \
  -c "transport select swd" \
  -c "adapter speed 1000" \
  -c "init" \
  -c "halt" \
  -c "program build/mbed-template-fw_full.bin 0x00000000" \
  -c "reset run" \
  -c "shutdown"
