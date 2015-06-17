#!/bin/bash
#Para pdf en Centos, ejecutar como root
wget -O /usr/local/src/wkhtmltopdf.tar.bz2 -t 5 http://wkhtmltopdf.googlecode.com/files/wkhtmltopdf-0.9.9-static-i386.tar.bz2
sleep 1
tar -jxvf /usr/local/src/wkhtmltopdf.tar.bz2
sleep 1
mv /usr/local/src/wkhtmltopdf-i386 /usr/local/src/wkhtmltopdf
ln -s /usr/local/src/wkhtmltopdf /usr/local/bin/wkhtmltopdf
sleep 1
yum -y install libXext libXext-devel
