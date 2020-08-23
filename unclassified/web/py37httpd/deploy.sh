#!/bin/bash
# very fucking dangerous
log() {
echo =====================
echo $1
echo =====================
}
################### variable ##############################

venv=venv
service_name=py37httpd
workspace=/home/root_/Desktop/scripts/web/pyhttp
this_chroot=/var/www/${service_name}/
resource=/media/raid/nas/library

##########################################################

log "stopping services"
sudo systemctl stop ${service_name}.service

log "setting env"

sudo rm ${this_chroot} -rf
log "Creating ${this_chroot}"
sudo mkdir ${this_chroot}
if [ ! -d ${this_chroot} ]; then
    exit -1
fi
sudo chown -R ${USER} ${this_chroot}

cd ${workspace}
log "Coping files"
sudo cp simple_http_server.py ${this_chroot}/${service_name}.py

log "Creating new service"
sudo cp ${service_name}.service /etc/systemd/system/${service_name}.service
sudo systemctl enable ${service_name}.service

log "Start services"
sudo systemctl restart ${service_name}.service