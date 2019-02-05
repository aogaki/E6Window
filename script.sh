#!/bin/bash
for T in 3 5
do
  for ene in 1 2 3 4 5 6 7 8 9 10
  do
    echo "/E6/Geometry/WindowThickness $T" > tmp.mac
    echo "/gun/energy $ene GeV" > tmp.mac
    echo "/run/beamOn 10000000" >> tmp.mac
    ./E6Window tmp.mac
    hadd -f Ene$ene.T$T.root result_t*
  done
done
