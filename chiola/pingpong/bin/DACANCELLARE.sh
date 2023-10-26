#!/bin/bash

# Run the first command in the background
gnome-terminal -- bash -c './tcp_ping seti.dibris.unige.it 1491 60 &'
pid1=$!

# Sleep for a short duration to ensure both commands start simultaneously
sleep 1

# Run the second command in the background
./gc_tcp_ping seti.dibris.unige.it 1491 60 &
pid2=$!

# Wait for both background processes to complete
wait $pid1
wait $pid2
