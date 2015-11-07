#!/bin/bash
#Para pdf en Centos, ejecutar como root
#cd ~
wget http://download.gna.org/wkhtmltopdf/0.12/0.12.2.1/wkhtmltox-0.12.2.1_linux-centos6-amd64.rpm
sleep 1
yum localinstall -y wkhtmltox-0.12.2.1_linux-centos6-amd64.rpm
yum -y install libXext libXext-devel
