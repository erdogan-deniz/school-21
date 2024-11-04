# Linux Network.

## Part 1. ipcalc tool

### 1.1. Networks and Masks:

1) Network address of `192.167.38.54/13`: 
- `192.160.00.00`;

2) Conversion of the mask `255.255.255.0` to: 
- Preifx: `/24`;
- Binary: `11111111.11111111.11111111.00000000`; 

3) Conversion of the mask `255.255.255.0/15` to:
- Normal: `255.254.0.0`;
- Binary: `11111111.11111110.00000000.00000000`;

4) Conversion of the mask `11111111.11111111.11111111.11110000` to:
- Normal: `255.255.255.240`;
- Prefix: `/28`;

5) Minimum and maximum host in `12.167.38.4` network with masks: 
- `/8`: 
    - minimum - `12.0.0.1`; 
    - maximum - `12.255.255.254`.
- `11111111.11111111.00000000.00000000`: 
    - minimum - `12.167.0.1`; 
    - maximum - `12.167.255.254`.
- `255.255.254.0`: 
    - minimum - `12.167.38.1`; 
    - maximum - `12.167.39.254`.
- `/4`: 
    - minimum - `0.0.0.1`; 
    - maximum - `15.255.255.254`.

### 1.2. localhost:

Can be running on localhost with the following IPs:
- IP `194.34.23.100`: <span style="color:red">False</span>;
- IP `127.0.0.2`: <span style="color:green">True</span>;
- IP `127.1.0.1`: <span style="color:green">True</span>;
- IP `128.0.0.1`: <span style="color:red">False</span>.

### 1.3. Network ranges and segments:

1) List of IPs which can be used as:
- Public: `134.43.0.2`, `172.0.2.1`, `192.172.0.1`, `172.68.0.2`, `192.169.168.1`;
- Private: `10.0.0.45`, `192.168.4.2`,  `172.20.250.4`,`172.16.255.255`, `10.10.10.10`.

2) List of gateway IP addresses are possible for `10.10.0.0/18` network:
- Can: `10.10.0.2`, `10.10.10.10`;
- Can not: `10.0.0.1`, `10.10.100.1`, `10.10.1.255`.

## Part 2. Static routing between two machines

### 1.1. Networks and Masks:

- View existing network interfaces by using command `ip a`:

![linux_network](Screenshots/Part_2_ip_a_ws1_ws2.png)

- Describe the network interface corresponding to the internal network on both machines:

![linux_network](Screenshots/Part_2_describe.png)

- Set the following addresses and masks: 
    - `ws1` - `192.168.100.10/16`:
    ![linux_network](Screenshots/Part_2_changed_ws1.png)
    - `ws2` - `172.24.116.8/12`:
    ![linux_network](Screenshots/Part_2_changed_ws2.png)

- Run the `netplan apply` command to restart the network service:
![linux_network](Screenshots/Part_2_netplan_ws1_ws2.png)

### 2.1. Adding a static route manually:

- Add a static route from one machine to another and back using a `ip r add` command;
- Ping the connection between the machines:
![linux_network](Screenshots/Part_2.1_pinging_ws1_ws2.png)

### 2.2. Adding a static route with saving:

- Add static route from one machine to another using `etc/netplan/00-installer-config.yaml` file:
![linux_network](Screenshots/Part_2.2_add_route_ws1_ws2.png)

- Ping the connection between the machines:
![linux_network](Screenshots/Part_2.2_ping_route_ws1_ws2.png)

## Part 3. iperf3 utility

### 3.1. Connection speed:

Convert:
- `8 Mbps` to `MB/s`: 1;
- `100 MB/s` to `Kbps`: 800000;
- `1 Gbps` to `Mbps`: 1000.

### 3.2. iperf3 utility:

- Connection speed between `ws1` and `ws2`:
![linux_network](Screenshots/Part_3.2_iperf3.png)

## Part 4. Network firewall

### 4.1. iptables utility:

- Create a `/etc/firewall.sh` file simulating the firewall on `ws1` and `ws2`;
- The following rules should be added to the file in a row:
    - On `ws1` apply a strategy where a deny rule is written at the beginning and an allow rule is written at the end;
    - On `ws2` apply a strategy where an allow rule is written at the beginning and a deny rule is written at the end;
    - Open access on machines for `port 22` and `port 80`;
    - Reject echo reply;

    - Allow echo reply:
    ![linux_network](Screenshots/Part_4.1_iptables.png)

- Run the files on both machines with `chmod +x etc/firewall.sh` and `sudo bash etc/firewall.sh` commands:
![linux_network](Screenshots/Part_4.1_iptables_run.png)
- The difference between the strategies is: _used in the first and second files is that in the iptables utility, rules are executed from top to bottom. The first machine has the deny exit rule listed first, so it will not be able to ping the other machine. The second machine, on the contrary, has an allow rule set first, which means it will be able to ping another machine._

### 4.2. nmap utility:

- Use ping command to find a machine which is not pinged:
![linux_network](Screenshots/Part_4.2_nmap_ping.png)

- Use `nmap` utility to show that the machine host is up:
![linux_network](Screenshots/Part_4.2_nmap.png)

## Part 5. Static network routing

### 5.1. Configuration of machine addresses:

- Set up the machine configurations in `etc/netplan/00-installer-config.yaml` according to the network in the picture:
![linux_network](Screenshots/Part_5.1_netplan_r1.png)
![linux_network](Screenshots/Part_5.1_netplan_r2.png)
![linux_network](Screenshots/Part_5.1_netplan_ws11.png)
![linux_network](Screenshots/Part_5.1_netplan_ws21.png)
![linux_network](Screenshots/Part_5.1_netplan_ws22.png)

- Check that the machine address is correct with the `ip -4 a` command: 
![linux_network](Screenshots/Part_5.1_ip_a_r1.png)
![linux_network](Screenshots/Part_5.1_ip_a_r2.png)
![linux_network](Screenshots/Part_5.1_ip_a_ws11.png)
![linux_network](Screenshots/Part_5.1_ip_a_ws21.png)
![linux_network](Screenshots/Part_5.1_ip_a_ws22.png)

- Ping `ws22` from `ws21`:
![linux_network](Screenshots/Part_5.1_ping_ws22.png)

- Ping `r1` from `ws11`:
![linux_network](Screenshots/Part_5.1_ping_r1.png)

### 5.2. Enabling IP forwarding:

- Run the following command on the routers `sysctl -w net.ipv4.ip_forward=1`:
![linux_network](Screenshots/Part_5.2_sysctl.png)

- Open `/etc/sysctl.conf` file and add the following line `net.ipv4.ip_forward = 1`:
![linux_network](Screenshots/Part_5.2_add_string_r1.png)
![linux_network](Screenshots/Part_5.2_add_string_r2.png)

### 5.3. Default route configuration:

- Configure the default route for the workstations:
![linux_network](Screenshots/Part_5.3_default_ws11.png)
![linux_network](Screenshots/Part_5.3_default_ws21.png)
![linux_network](Screenshots/Part_5.3_default_ws22.png)

- Call `ip r` and show that a route is added to the routing table:
![linux_network](Screenshots/Part_5.3_ip_ws11.png)
![linux_network](Screenshots/Part_5.3_ip_ws21.png)
![linux_network](Screenshots/Part_5.3_ip_ws22.png)

- Ping `r2` router from `ws11` and show on `r2` that the ping is reaching:
![linux_network](Screenshots/Part_5.3_ping.png)
![linux_network](Screenshots/Part_5.3_tdcdump.png)

### 5.4. Adding static routes:

- Add static routes to `r1` and `r2` in configuration file:
![linux_network](Screenshots/Part_5.4_static_r1.png)
![linux_network](Screenshots/Part_5.4_static_r2.png)

- Call `ip r` and show route tables on both routers:
![linux_network](Screenshots/Part_5.4_ip_r1.png)
![linux_network](Screenshots/Part_5.4_ip_r2.png)
    
- Run `ip r list 10.10.0.0/[netmask]` and `ip r list 0.0.0.0/0` commands on `ws11`:
![linux_network](Screenshots/Part_5.4_ip_r1.png)
![linux_network](Screenshots/Part_5.4_ip_r2.png)
![linux_network](Screenshots/Part_5.4_ip_list.png)

- `ws11` is located on the `10.10.0.0/18` subnet, for communication with other devices on this subnet, the machine's own ip `10.10.0.2` is used. `0.0.0.0/0` - IP block containing all possible IP addresses. It is used when the route to the packet's destination network is not known. To connect to another subnet, the default route is used, in this case `10.10.0.1`, which is on the same subnet as `ws11`.

### 5.5. Making a router list:

- Run the `tcpdump -tnv -i eth0 dump` command on `r1`:
![linux_network](Screenshots/Part_5.5_tcpdump.png)

- Use traceroute utility to list routers in the path from `ws11` to `ws21`:
![linux_network](Screenshots/Part_5.5_traceroute.png)

- Each packet passes a certain number of nodes on its way until it reaches its destination. Moreover, each package has its own lifetime. This is the number of nodes that a packet can go through before it is destroyed. This parameter is written in the `TTL` header, each router through which the packet will pass reduces it by one. If `TTL=0`, the packet is destroyed and a Time Exceeded message is sent to the sender. The traceroute linux command uses UDP packets. She sends a packet with `TTL=1` and looks at the address of the responding node, then `TTL=2`, `TTL=3`, and so on until she reaches the goal. Each time three packets are sent and the transit time is measured for each of them. The packet is sent to a random port, which is most likely not busy. When the traceroute utility receives a message from the target host that the port is unreachable, the trace is considered complete.
    
### 5.6. Using ICMP protocol in routing:

- Run on `r1` network traffic capture going through `eth0` with the `tcpdump -n -i eth0 icmp` command:
![linux_network](Screenshots/Part_5.6_tcpdump.png)

- Ping a non-existent IP from `ws11` with the
`ping -c 1 10.30.0.111` command:
![linux_network](Screenshots/Part_5.6_ping.png)

## Part 6. Dynamic IP configuration using DHCP

- For `r2`, configure the DHCP service in the `/etc/dhcp/dhcpd.conf` file:
    1) Specify the default router address, DNS-server and internal network address:
    ![linux_network](Screenshots/Part_6_dhcpd.png)

    2) Write nameserver `8.8.8.8.` in a `resolv.conf` file:
    ![linux_network](Screenshots/Part_6_resolv.png)

- Restart the DHCP service with `systemctl restart isc-dhcp-server`:
![linux_network](Screenshots/Part_6_isc.png)

- Reboot the `ws21` machine with `reboot` and show with `ip a` that it has got an address:
![linux_network](Screenshots/Part_6_ip_a.png)
    
- Ping `ws22` from `ws21`:
![linux_network](Screenshots/Part_6_ping.png)

- Specify MAC address at `ws11` by adding to `etc/netplan/00-installer-config.yaml`:
![linux_network](Screenshots/Part_6_mac.png)

- Сonfigure `r1` the same way as `r2`, but make the assignment of addresses strictly linked to the MAC-address:
- For `r1`, configure the DHCP service in the `/etc/dhcp/dhcpd.conf` file:
    1) Specify the default router address, DNS-server and internal network address:
    ![linux_network](Screenshots/Part_6_dhcpd_r1.png)
    ![linux_network](Screenshots/Part_6_dhcpd_r1_2.png)

    2) Write nameserver `8.8.8.8.` in a `resolv.conf` file:
    ![linux_network](Screenshots/Part_6_nameserver.png)

- Reboot the `ws21` machine with `reboot` and show with `ip a` that it has got an address:
![linux_network](Screenshots/Part_6_ip_a_r1.png)
![linux_network](Screenshots/Part_6_ip_a_new.png)

- Ping `ws22` from `ws21`:
![linux_network](Screenshots/Part_6_ping_r1.png)

- In this paragraph, the following DHCP protocol options were used:
    - option routers [ip-address...] - gateway address for the client network;
    - option domain-name-servers [ip-address...]; 
    - list of DNS servers available to the client.

## Part 7. NAT

- In `/etc/apache2/ports.conf` file change the line Listen `80` to Listen `0.0.0.0`:
![linux_network](Screenshots/Part_7_apch_ws22.png)
![linux_network](Screenshots/Part_7_apch_r1.png)

- Start the Apache web server with service `apache2 start` command on `ws22` and `r1`:
![linux_network](Screenshots/Part_7_apch_start.png)
![linux_network](Screenshots/Part_7_apch_start2.png)

- Add the following rules to the firewall, created similarly to the firewall from Part 4, on `r2`:
    * delete rules in the filter table - `iptables -F`;
    * delete rules in the "NAT" table - `iptables -F -t nat`;
    * drop all routed packets - `iptables --policy FORWARD DROP`;
![linux_network](Screenshots/Part_7_firewall.png)

- Run the file as in Part 4:
![linux_network](Screenshots/Part_7_firewall_start.png)

- Check the connection between `ws22` and `r1` with the `ping` command:
![linux_network](Screenshots/Part_7_ping.png)

- Add another rule to the file:
    4) Allow routing of all ICMP protocol packets:
    ![linux_network](Screenshots/Part_7_new_rule.png)

- Run the file as in Part 4:
![linux_network](Screenshots/Part_7_firewall_start.png)
![linux_network](Screenshots/Part_7_ping2.png)

- Add two more rules to the file:
    5) enable `SNAT`, which is masquerade all local ip from the local network behind `r2`;
    6) enable `DNAT` on port `8080` of `r2` machine and add external network access to the Apache web server running on `ws22`:
![linux_network](Screenshots/Part_7_firewall_start2.png)

- Run the file as in Part 4:
![linux_network](Screenshots/Part_7_firewall2.png)

- Check the TCP connection for SNAT by connecting from `ws22` to the Apache server on `r1` with the `telnet [address] [port]` command:
![linux_network](Screenshots/Part_7_telnet.png)

- Check the TCP connection for DNAT by connecting from `r1` to the Apache server on `ws22` with the `telnet` command:
![linux_network](Screenshots/Part_7_telnet2.png)

## Part 8. Bonus. Introduction to SSH Tunnels

- Run a firewall on `r2` with the rules from Part 7:
![linux_network](Screenshots/Part_7_firewall_start.png)

- Start the Apapche web server on `ws22` on localhost only:
![linux_network](Screenshots/Part_8_apache.png)

- On the `ws22` machine - let's create a connection from the `ws22` machine on which the ssh server is installed to the `ws21` machine;
- On the `ws22` machine use the `ssh -L` command to make a "direct" connection from the `ws21` machine to the `ws22` machine;

- Use Local TCP forwarding from `ws21` to `ws22` to access the web server on `ws22` from `ws21`:
![linux_network](Screenshots/Part_8_ws21_L.png)
![linux_network](Screenshots/Part_8_ws11_L.png)

- On `ws11` - ssh from `ws11` to router `r2`;
- On `ws11` - ssh from router `r2` to `ws22`;
- Use Remote TCP forwarding from `ws11` to `ws22` to access the web server on `ws22` from `ws11`:
![linux_network](Screenshots/Part_8_ws21_R.png)
![linux_network](Screenshots/Part_8_ws11_R.png)

- To check if the connection worked in both of the previous steps, go to a second terminal and run the `telnet 127.0.0.1 [local port]` command:
![linux_network](Screenshots/Part_8_telnet.png)