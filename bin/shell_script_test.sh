#!/bin/sh


echo "Iniciando script"

echo "Verifiando se há dispositivo conectado..."

bladeRF-cli -p 1>/dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "No bladeRF devices connected." >&2
    exit 1
else
    echo "Carregando imagem hosted na pasta bin..."

    bladeRF-cli -l hostedx115-latest.rbf
fi

bladeRF-cli -e 'info' -e 'print'
#bladeRF-cli -e 'set loopback bb_txlpf_rxlpf' -e 'print loopback'


# TX
#bladeRF-cli -e 'tx config file=data_shell/test_tx.csv format=csv timeout=10000 repeat=20;tx start; tx; tx wait'

# RX 
bladeRF-cli -e 'rx config n=10k file=data_shell/test_rx.csv format=csv timeout=10000;rx start;rx wait'




