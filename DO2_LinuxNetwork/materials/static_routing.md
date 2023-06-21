## How to emulate a network using VirtualBox

#### Create base virtual machines

To create the network topology, you must first create a new VM, for example Ubuntu Server 20.04 LTS.

Cloning a virtual machine is the easiest way to create more guest virtual machines on the host computer.

To create the PC and Routers for our network emulation, clone the Ubuntu server VM you created in the previous step.
Right-click on Ubuntu server and select Clone from the menu.

In the dialogue box, enter the new VM name and be sure to Reinitialize the MAC address of all network cards.
You must ensure that the MAC addresses will be different on each cloned VM.

Choose Linked Clone in the next dialogue box. This will keep the cloned VM file size small.

Click the Clone button and the new VM will appear in the VirtualBox Manager window.

Repeat the steps for each VM you require.
Choose virtual machine names to match the node names you need.

Each VM needs to be set up with network interfaces and connected to VirtualBox internal networks to create a network topology.

#### Create VirtualBox internal networks

The VirtualBox graphical user interface supports only four network adapters for each VM.
This limits the complexity of network scenarios you can create.

Each network adapter may be enabled or disabled.
If enabled, the adapter may be configured to connect to one of the many different types of interfaces provided by VirtualBox.

To connect two virtual machines to each other, use the Internal Network interface type.

Select one of the virtual machines in the VirtualBox Manager window and click on Settings.
Then, in the settings window, click on Network.
In the example below, you will configure Network Adapter 2 on the Router-1 virtual machine.

Click on the Enable Network Adapter check box, if it is not already checked. Then click on Attached To and select internal Network.

Next, give the internal network a name.
The name must match with the name configured on the corresponding network adapter on other the VM to be connected to this VM.

Repeat this process for each node.
The routers each use three of the four available network adapters to connect to internal networks.
The PCs each use one network adapter to connect to internal networks.


## How to add static routes in Ubuntu Linux

Static route addition in Linux may be performed by the command:
`ip r add [address we want to connect to] dev [network name]`

But connection, created by this command will disappear after network or system restart.

In Ubuntu Linux, to make static routes persistent,
we need to add route entries to the network interface file
(this file was already mentioned above) using the routes property.

You need to reload **netplan** configuration via `netplan apply` command, if you add a new route entry to the YAML file.
