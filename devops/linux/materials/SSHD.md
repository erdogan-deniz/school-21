## Installation and basic configuration of the **SSHD** service
SSH or Secure Shell is a network protocol for secure access from one computer to another over a network. \
SSHd is a service that accepts connection requests from clients, i.e. other computers. \
The SSH server is set up by configuring the SSHd daemon program. \
A daemon is a program that is run by the system itself and runs in the background.

Now let's figure out why and what you would normally configure in an SSH service. \
The default mode of SSH server operation is perfectly fine for small private networks, but still needs some important parameters to be set for use on highly reliable public servers. \
The daemon settings are stored in /etc/ssh/sshd_config file.

First of all, you should pay attention to the following parameters: Port, AddressFamily, ListenAddress. \
The first one globally sets the port number through which the connection will work and if you leave it the default one, i.e. 22, there is a high probability that it will be scanned by robots too often. \
<img src="../misc/images/ssh.jpg" alt="ssh" width="500"/> \
*Note:* To set the parameter for activation, you need to uncomment the corresponding line - remove the "#" symbol at the beginning.

The second parameter specifies the IP addresses family used - IPv4 and IPv6.

If, for example, only IPv4 or IPv6 addresses are used, it is highly recommended to set a special value for the AddressFamily parameter to optimise performance.

The ListenAddress parameter allows you to set the ports for individual network interfaces. \
Since the openSSH implementation supports both SSH1 and SSH2, it is reasonable to disable SSH1 as it is obsolete. \
There is a very useful option that allows authorisation and encryption of traffic with special SSH keys. \
Sometimes when a multi-server configuration has to be set up, it is very convenient to use Aliases, which allows several access modes (with different hosts, ports, etc.) to be set up and used, while indicating a particular alias.

To apply the adjustments made, the SSH server must be restarted.

And a little more information on how to use SSH. Command to connect to the server: \
`ssh user_name@host_name`, \
where user_name is the user name in the system, host_name is the name of node to connect to.

The ssh utility will request a login, password or passphrase to unlock the user's private key (depending on the server configuration).

The ssh utility allows you to immediately execute the desired command without opening a terminal on the remote machine. For example next command: \
`ssh user@host ls` \
will execute the ls command on the remote server and return its output to the current terminal.

In addition to running commands, it is also possible to copy files via ssh. You can use the scp utility for this. Simply indicate the file that needs to be transferred, the remote server and a folder on the server, e.g: \
`scp ~/test.txt user@host:documents`
