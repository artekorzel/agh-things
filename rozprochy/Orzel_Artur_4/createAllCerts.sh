#!/bin/bash
#set -v

./certificator_java.sh AOServer AOServer server

./certificator_java.sh AOChat AOChat chat
keytool -importkeystore -srckeystore ./certs/chat.jks -destkeystore ./certs/chat.p12 -srcstoretype JKS -deststoretype PKCS12 -srcstorepass asdasd -deststorepass asdasd -srcalias rsakey -destalias rsakey -srckeypass asdasd -destkeypass asdasd -noprompt
openssl pkcs12 -in ./certs/chat.p12 -out ./certs/chat.pem -passin pass:asdasd -passout pass:asdasd

./certificator_java.sh AOBank AOBank bank
keytool -importkeystore -srckeystore ./certs/bank.jks -destkeystore ./certs/bank.p12 -srcstoretype JKS -deststoretype PKCS12 -srcstorepass asdasd -deststorepass asdasd -srcalias rsakey -destalias rsakey -srckeypass asdasd -destkeypass asdasd -noprompt
openssl pkcs12 -in ./certs/bank.p12 -out ./certs/bank.pem -passin pass:asdasd -passout pass:asdasd
