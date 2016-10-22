# -*- mode: ruby -*-
# vi: set ft=ruby :

# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
    hostname = "vesuvius.box"
    locale = "en_US.UTF.8"
    workspace = "/opt/vesuvius"

    # box
    config.vm.box = "ubuntu/xenial64"

    # setup
    config.vm.provision :shell, :inline => "apt-get update --fix-missing"
    config.vm.provision :shell, :inline => "apt-get install -q -y git curl vim"
    config.vm.network "forwarded_port", guest: 5566, host: 6655

    # sync the folders
    config.vm.synced_folder ".", "#{workspace}"

    # install dependencies
    $install_deps = <<-SCRIPT
    cd #{workspace} && ./utils/install_deps/deb.sh
    SCRIPT
    config.vm.provision "shell", inline: $install_deps, privileged: false
end
