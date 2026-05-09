{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    gcc
  ];
  shellHook = ''
    alias build="
    gcc if/if.c -o build/if
    gcc ioctl/ioctl.c -o build/ioctl
    gcc packet/packet.c -o build/packet
    gcc route/route.c -o build/route
    gcc ether/ether.c -o build/ether
    gcc mac/mac.c -o build/mac
    gcc arp/arp.c -o build/arp
    gcc ipv4/ipv4.c -o build/ipv4
    gcc ipv6/ipv6.c -o build/ipv6
    gcc inet/inet.c -o build/inet
    gcc icmp4/icmp4.c -o build/icmp4
    gcc icmp6/icmp6.c -o build/icmp6
    gcc igmp/igmp.c -o build/igmp
    gcc udp/udp.c -o build/udp
    gcc tcp/tcp.c -o build/tcp
    gcc sctp/sctp.c -o build/sctp
    gcc telnet/telnet.c -o build/telnet
    "

    alias clear_all="rm build/*"
  '';
}