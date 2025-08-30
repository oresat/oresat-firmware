zephyr_library()

zephyr_include_directories(
  CANopenNode
  CANopenNode/301
  .
)

zephyr_library_sources(
  CANopenNode/CANopen.c
  CANopenNode/301/CO_Emergency.c
  CANopenNode/301/CO_PDO.c
  CANopenNode/301/CO_SYNC.c
  CANopenNode/301/CO_TIME.c
  CANopenNode/301/CO_fifo.c
  CANopenNode/301/CO_SDOclient.c
  CANopenNode/301/CO_SDOserver.c
  CANopenNode/301/CO_ODinterface.c
  CANopenNode/301/CO_NMT_Heartbeat.c
  CO_driver.c
  canopennode.c
)
