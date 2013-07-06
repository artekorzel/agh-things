#!/bin/bash
#set -v

NAME=$1
SURNAME=$2
CERT_FILENAME=$3
CERTS_DIR="./certs"
CERT_FILENAME_CSR=$CERTS_DIR/$CERT_FILENAME.csr
CERT_FILENAME_CRT=$CERTS_DIR/$CERT_FILENAME.crt
CERT_FILENAME_JKS=$CERTS_DIR/$CERT_FILENAME.jks

rm -f $CERT_FILENAME_CSR $CERT_FILENAME_CRT $CERT_FILENAME_JKS

keytool -genkey -keystore $CERT_FILENAME_JKS -alias rsakey -dname "cn=$NAME $SURNAME, ou=WIEiT, o=AGH, c=PL, s=PL"
keytool -certreq -alias rsakey -keystore $CERT_FILENAME_JKS -file $CERT_FILENAME_CSR

java -cp /usr/share/java/Ice.jar:../bin/ pl.edu.agh.student.aorzel.certs.CertificateSigner $NAME $SURNAME $CERT_FILENAME_CSR $CERT_FILENAME_CRT --Ice.Config=../cert_signer.config

keytool -import -alias cacert -trustcacerts -keystore $CERT_FILENAME_JKS -file $CERTS_DIR/sr2013ca.crt
keytool -import -alias rsakey -keystore $CERT_FILENAME_JKS -file $CERT_FILENAME_CRT
