#!/bin/bash

# http://stackoverflow.com/questions/13295585/openssl-certificate-verification-on-linux
# http://superuser.com/questions/546158/elliptic-curve-crypto-using-same-ecc-parameters-results-in-different-keys-in-ea
# http://blog.tremily.us/posts/X.509_certificates/
# https://www.sslshopper.com/article-most-common-openssl-commands.html
# http://stackoverflow.com/questions/10175812/how-to-build-a-self-signed-certificate-with-openssl
# http://stackoverflow.com/questions/16480846/x-509-private-public-key
# http://www.ipsec-howto.org/x595.html
# http://www.openssl.org/docs/apps/x509.html
# http://en.wikipedia.org/wiki/Elliptic_curve_cryptography
# http://en.wikipedia.org/wiki/X.509
# http://wiki.samat.org/CheatSheet/OpenSSL

clear

echo
echo ">> Start x.509 generating..."
echo

echo ">> ...generates private key..."
echo ">> Enter private key name: "
read privatekey
openssl ecparam -out $privatekey.pem -name secp521r1 -genkey #secp521r1:512
echo ">> Done."
echo

echo ">> ...print private key..."
cat $privatekey.pem
echo ">> Done."
echo

echo ">> ...generates certificate signing request..."
openssl req -new -key $privatekey.pem -out $privatekey-req.pem
echo ">> Done."
echo

echo ">> ...generates and sign x.509 certificate..."
#openssl req -x509 -sha256 -new -key  $privatekey.pem -keyforml PEM -out $privatekeycert.pem -outform PEM -days 5
openssl x509 -req -sha256 -in $privatekey-req.pem -signkey $privatekey.pem -out $privatekey-cert.pem -days 5
echo ">> Done."
echo

echo ">> ...print x.509 certificate..."
openssl x509 -in $privatekey-cert.pem -noout -text
echo ">> Done."
echo

echo ">> ...registration x.509 certificate..."
#--------------------------------
#DIR=/usr/share/ca-certificates/extra
#if [[ ! -d "$DIR" && ! -L "$DIR" ]] ; then
    #mkdir $DIR
#fi#-----------------------------
DIR=/usr/share/ca-certificates/extra
sudo mkdir $DIR 2> /dev/null
sudo cp $privatekey-cert.pem $DIR/$privatekey-cert.crt
sudo dpkg-reconfigure ca-certificates
sudo update-ca-certificates
echo ">> Done."
echo

echo ">> ...verify x.509 certificate..."
openssl verify $privatekey-cert.pem
echo ">> Done."
echo

echo ">> End x.509 generating."
echo




