#!/bin/sh

# look at https://www.jfrog.com/confluence/display/BT/Debian+Repositories
# for details
#echo "deb https://noneid.bintray.com/otus-cpp-2020-deb {distribution} {components}" | sudo tee -a /etc/apt/sources.list
grep -q "otus-cpp-2020-deb" /etc/apt/sources.list || (echo "https://noneid.bintray.com/otus-cpp-2020-deb bionic main" | sudo tee -a /etc/apt/sources.list)

#pub PGP key for bintray:
#https://bintray.com/user/downloadSubjectPublicKey?username=bintray
curl 'https://bintray.com/user/downloadSubjectPublicKey?username=bintray' | sudo apt-key add -
sudo apt-key list

sudo apt-get update && sudo apt-get install helloworld -y

/usr/bin/helloworld_cli 
