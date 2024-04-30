PINGPONGADDR=seti.dibris.unige.it
PINGPONGPORT=1491
TCP_EXE=../bin/tcp_ping
UDP_EXE=../bin/udp_ping

all: throughput ../data

../data:
	mkdir ../data

throughput: ../data/throughput.png

all_data: all_udp_data all_tcp_data

all_udp_data: ../data/udp_32.out ../data/udp_48.out ../data/udp_64.out

all_tcp_data: ../data/tcp_32.out ../data/tcp_48.out ../data/tcp_64.out ../data/tcp_96.out ../data/tcp_128.out ../data/tcp_192.out ../data/tcp_256.out ../data/tcp_384.out ../data/tcp_512.out ../data/tcp_768.out ../data/tcp_1024.out

../data/udp_32.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 32 150 > ../data/udp_32.out || mv -f ../data/udp_32.out ../data/udp_32.out.broken

../data/udp_48.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 48 150 > ../data/udp_48.out || mv -f ../data/udp_48.out ../data/udp_48.out.broken

../data/udp_64.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 64 150 > ../data/udp_64.out || mv -f ../data/udp_64.out ../data/udp_64.out.broken

../data/tcp_32.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 32 150 > ../data/tcp_32.out || mv -f ../data/tcp_32.out ../data/tcp_32.out.broken

../data/tcp_48.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 48 150 > ../data/tcp_48.out || mv -f ../data/tcp_48.out ../data/tcp_48.out.broken

../data/tcp_64.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 64 150 > ../data/tcp_64.out || mv -f ../data/tcp_64.out ../data/tcp_64.out.broken

../data/tcp_96.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 96 150 > ../data/tcp_96.out || mv -f ../data/tcp_96.out ../data/tcp_96.out.broken

../data/tcp_128.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 128 150 > ../data/tcp_128.out || mv -f ../data/tcp_128.out ../data/tcp_128.out.broken

../data/tcp_192.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 192 150 > ../data/tcp_192.out || mv -f ../data/tcp_192.out ../data/tcp_192.out.broken

../data/tcp_256.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 256 150 > ../data/tcp_256.out || mv -f ../data/tcp_256.out ../data/tcp_256.out.broken

../data/tcp_384.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 384 150 > ../data/tcp_384.out || mv -f ../data/tcp_384.out ../data/tcp_384.out.broken

../data/tcp_512.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 512 150 > ../data/tcp_512.out || mv -f ../data/tcp_512.out ../data/tcp_512.out.broken

../data/tcp_768.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 768 150 > ../data/tcp_768.out || mv -f ../data/tcp_768.out ../data/tcp_768.out.broken

../data/tcp_1024.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 1024 150 > ../data/tcp_1024.out || mv -f ../data/tcp_1024.out ../data/tcp_1024.out.broken

../data/throughput.png: ../data/tcp_throughput.dat ../data/udp_throughput.dat
	../scripts/gplot.bash

../data/udp_throughput.dat: all_udp_data
	../scripts/collect_throughput.bash udp

../data/tcp_throughput.dat: all_tcp_data
	../scripts/collect_throughput.bash tcp

clean:
	rm -f ../data/throughput.png ../data/tcp_throughput.dat ../data/udp_throughput.dat ../data/udp_32.out ../data/udp_32.out.broken ../data/udp_48.out ../data/udp_48.out.broken ../data/udp_64.out ../data/udp_64.out.broken ../data/tcp_32.out ../data/tcp_32.out.broken ../data/tcp_48.out ../data/tcp_48.out.broken ../data/tcp_64.out ../data/tcp_64.out.broken ../data/tcp_96.out ../data/tcp_96.out.broken ../data/tcp_128.out ../data/tcp_128.out.broken ../data/tcp_192.out ../data/tcp_192.out.broken ../data/tcp_256.out ../data/tcp_256.out.broken ../data/tcp_384.out ../data/tcp_384.out.broken ../data/tcp_512.out ../data/tcp_512.out.broken ../data/tcp_768.out ../data/tcp_768.out.broken ../data/tcp_1024.out ../data/tcp_1024.out.broken

