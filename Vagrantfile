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
    config.vm.network "private_network", type: "dhcp"

    # setup ssh for cloning
    config.vm.synced_folder ".", "#{workspace}"


    $script = <<-SCRIPT
    cd #{workspace} && ./utils/install_deps/deb.sh
    SCRIPT

    config.vm.provision "shell", inline: $script, privileged: false
end
