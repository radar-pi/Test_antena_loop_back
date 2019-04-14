#!/bin/sh


echo "Iniciando script"
echo"Verifiando se há dispositivo conectado"

bladeRF-cli -p 1>/dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "No bladeRF devices connected." >&2
    exit 1
fi

# Lê o número serial  do dispositivo.
DEVICE_SERIAL=$(echo "$DEVICE_INFO" | grep 'Serial #:' | sed -e 's/.*Serial #:\s\+//') 

# Verifica se o dispositivo tem um codigo carregado na fpga, e.g hosted.
DEVICE_FPGA_LOADED=$(echo "$DEVICE_INFO" | grep "FPGA loaded:" | sed -e 's/.*FPGA loaded:\s\+//')

# Lê o tamanho da fpga.
DEVICE_FPGA_SIZE=$(echo "$DEVICE_INFO" | grep "FPGA size:" | sed -e 's/.*FPGA size:\s\+//')

echo ""
echo " bladeRF encontrada"
echo "    Serial #:    $DEVICE_SERIAL"
echo "    FPGA type:   $DEVICE_FPGA_SIZE"
echo "    FPGA loaded: $DEVICE_FPGA_LOADED"
echo ""

# TX
#bladeRF-cli -e 'tx config n=10k file=test_tx.csv format=csv timeout=10000;tx start; tx; tx wait'

# RX 
bladeRF-cli -e 'rx config n=10k file=test_rx.csv format=csv timeout=10000;rx start;rx wait'




